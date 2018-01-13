#! /bin/bash
set -x
#####   VARIABLES
##################################################################################

CC="gcc"
CC_OPT="-Wall -g -gstabs"
CC_INCL="-Isrc"
CC_LIB=""
CC_OPT_PREPRO="-std=c99 -pedantic -E"
#CC_DEFINE="-nostartfiles -Wl,-emainRTRT"
#"-DPOUT" 
#"-Wl,-emainRTRT"
RM="rm -f"
TENIS="/home/dwu/Bureau/TP_INSA_2018/TENIS/TENIS/bin/linux/tenis"
TENIS_POST_PRO="/home/dwu/Bureau/TP_INSA_2018/TENIS/TENIS_POSTPRO/bin/linux/tenis_postpro"
TEST_PTU="test/stat.ptu"

#On peut utiliser Vim (ou autres) pour les plus nuls d'entre vous.
READER="pluma"


#####   FUNCTIONS
###################################################################################

generate_prepro_file(){
    ${CC} ${CC_OPT_PREPRO} $1 -o $1.out
}


#Un simple clean pas forcément nécessaire mais il permet de connaitre
#les différents fichiers généré par TENIS et TENIS POST PRO.
clean_all_useless_file(){
    #Fichiers issus de precédentes génération de rapport de test
    ${RM} test_result.log
    ${RM} rapport_test.txt
    ${RM} /tmp/user_debug.gdb
    ${RM} /tmp/maintenis_tmp.c
    #Fichiers issus de precédentes génération de rapport de couverture
    ${RM} couv.log
    ${RM} src/stat.out
    ${RM} src/triangle.out
    ${RM} /tmp/all_record_couv.log
    ${RM} /tmp/analyse_stat.txt
    ${RM} /tmp/prepro_src.c
    ${RM} rapport_couverture.txt
}


compile(){
    ${CC} ${CC_DEFINE} ${CC_OPT} ${CC_INCL} -o bin/prog $* ${CC_LIB}
}


run_TENIS_script_GDB(){
    export LC_NUMERIC="C"
    echo "--------+------------------------------------------------------------------------------"
    echo "        |"
    echo "        |                   EXECUTION BINAIRE DE TEST DANS GDB"
    echo "        |"
    echo "--------+------------------------------------------------------------------------------"
    gdb --batch -x /tmp/user_debug.gdb --args bin/prog
 
}


#####   EXECUTION SCRIPT
###################################################################################

set -x
## Lance le binaire avec print sans aucuns tests pour voir son utilité.
if [[ ( "$1" == "NO_TEST" ) || ( $1 -eq '1' ) ]]
    then
    clean_all_useless_file
    compile src/main.c src/triangle.c
    bin/prog

    ## Lance le binaire sans print et sans aucuns tests pour voir son utilité.
elif [[ ( "$1" = "NO_TEST_NO_PRINT" ) || ( $1 -eq '2' ) ]]
then
    clean_all_useless_file
    compile src/main.c src/triangle.c
    bin/prog

    ## Lance un test en utilisant TENIS sans couverture de code
elif [[ ( "$1" == "NO_COUV" ) || ( $1 -eq '3' ) ]]
then
    clean_all_useless_file
    ${TENIS} ${TEST_PTU} # -b main
    #sed -i 's#mainRTRT/main/' /tmp/maintenis_tmp.c 
   # sed -i '139,/end/s/end\nrun//' /tmp/user_debug.gdb	
   # sed -i 's/end/end\nrun/4' /tmp/user_debug.gdb	
    compile /tmp/maintenis_tmp.c src/triangle.c
    run_TENIS_script_GDB
    ${TENIS_POST_PRO} test_result.log
    ${READER} rapport_test.txt

    ## Lance un test en utilisant TENIS avec couverture de code du fichier src/triangle.c
elif [[ ( "$1" == "COUV_math" ) || ( $1 -eq '5' ) ]]
then
    clean_all_useless_file
    generate_prepro_file src/triangle.c
    ${TENIS} ${TEST_PTU} -c src/triangle.c.out
    compile /tmp/maintenis_tmp.c src/triangle.c
   # var=`grep -n end /tmp/user_debug.gdb | awk -F ':' '{print $1}' | tail -1` 
  #  sed -i "$var,$ s#end#end\nrun#" /tmp/user_debug.gdb		
    run_TENIS_script_GDB
    ${TENIS_POST_PRO} test_result.log -c couv.log -a /tmp/analyse_stat.txt
    ${READER} rapport_test.txt rapport_couverture.txt

    ## Supprime tous les fichiers générés par TENIS.
elif [[ ( "$1" == "CLEAN" ) ||  ( $1 -eq '6' ) ]]
then
    clean_all_useless_file

    ## Sinon il manque un argument ou argument(s) faux!
else
    echo "Appelle ./launch_test avec des arguments"
    echo "-------------------------------------------------------------"
    echo "1) NO_TEST: binaire sans aucuns tests"
    echo "2) NO_TEST_NO_PRINT: binaire sans affichage sans aucuns tests"
    echo "3) NO_COUV: test en utilisant TENIS sans couverture de code"
    echo "5) COUV_triangle.c: test avec couverture de code de src/triangle.c"
    echo "6) CLEAN: supprime fichiers générés par TENIS"
fi
