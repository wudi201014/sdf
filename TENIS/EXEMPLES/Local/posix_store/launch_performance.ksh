#!/usr/bin/ksh

#####   VARIABLES
##################################################################################

CC="gcc"
CC_OPT="-g -gstabs"
CC_INCL="-Isrc"
CC_LIB="-lpthread"
CC_OPT_PREPRO="-std=c99 -pedantic -E"
RM="rm -f"
TENIS="../../TENIS/bin/linux/./tenis"
TENIS_POST_PRO="../../TENIS_POSTPRO/bin/linux/tenis_postpro"
TEST_PTU="test/posix_store.ptu"

#On peut utiliser Vim (ou autres) pour les plus nuls d'entre vous.
READER="emacs"


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
    ${RM} tmp/user_debug.gdb
    ${RM} tmp/maintenis_tmp.c
    #Fichiers issus de precédentes génération de rapport de couverture
    ${RM} couv.log
    ${RM} src/store.c.out
    ${RM} tmp/all_record_couv.log
    ${RM} tmp/analyse_stat.txt
    ${RM} tmp/prepro_src.c
    ${RM} rapport_couverture.txt
}


compile(){
    ${CC} ${CC_DEFINE} ${CC_OPT} ${CC_INCL} -o bin/prog $* ${CC_LIB}
}


run_TENIS_script_GDB(){
    export LC_NUMERIC="C"
    gdb --batch --command=/tmp/user_debug.gdb --args bin/./prog
}

getTime(){
    duration=0

    for i in {1..5}
    do
        start=$(date +%s.%N)
        $*
        duration=$(echo "$(date +%s.%N) - $start + $duration" | bc)
    done
    duration=$(echo "$duration * 0.2 " | bc)
    sum=$(echo "$duration + $sum" | bc)

    echo "${duration}" >> rapport_performance.log
}

#####   EXECUTION SCRIPT
##################################################################################

${RM} rapport_performance.log

##1## Recupération du temps pour programme seule
clean_all_useless_file
compile src/main.c src/store.c
printf "  o  Execution binaire seul             :   " >> rapport_performance.log
getTime "bin/./prog"


##2## Recupération du temps pour execution TENIS sans couv
sum=0
clean_all_useless_file
printf "\n  o  TENIS sans couverture              :   " >> rapport_performance.log
getTime "${TENIS} ${TEST_PTU}"

##2## Recupération du temps pour execution programme dans gdb avec test sans couv
compile /tmp/maintenis_tmp.c src/store.c
printf "     Execution sous GDB                 :   " >> rapport_performance.log
getTime "run_TENIS_script_GDB"

##2## Recupération du temps pour execution TENIS_POSTPRO sans couv
printf "     TENIS_POST_PRO sans couverture     :   " >> rapport_performance.log
getTime "${TENIS_POST_PRO} test_result.log"

##2## Recupération du temps pour execution total sans couv
printf "     Total                              :   %s\n" "$sum" >> rapport_performance.log

##3## Recupération du temps pour execution TENIS avec couv
sum=0
clean_all_useless_file
generate_prepro_file src/store.c
printf "\n  o  TENIS avec couverture              :   " >> rapport_performance.log
getTime "${TENIS} ${TEST_PTU} -c src/store.c.out"

##3## Recupération du temps pour execution programme dans gdb avec test et couv
compile /tmp/maintenis_tmp.c src/store.c
printf "     Execution sous GDB                 :   " >> rapport_performance.log
getTime "run_TENIS_script_GDB"

##3## Recupération du temps pour execution TENIS_POSTPRO avec couv
printf "     TENIS_POST_PRO avec couverture     :   " >> rapport_performance.log
getTime "${TENIS_POST_PRO} test_result.log -c couv.log -a /tmp/analyse_stat.txt"

##3## Recupération du temps pour execution total avec couv
printf "     Total                              :   %s\n" "$sum" >> rapport_performance.log

##4## Affichage du rapport de performance généré
${READER} rapport_performance.log
