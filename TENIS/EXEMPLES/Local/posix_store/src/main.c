#include "store.h"

#ifdef POUT
#include <stdio.h>


void p_stock(int stock_restant){
   printf ("Remplissage du stock de %d articles !\n",stock_restant);
}

void p_client_action(int nb_elmt, int stock_restant){
   printf ("Un client prend %d du stock, reste %d en stock !\n",nb_elmt, stock_restant);
}
#endif // POUT

int main(void){

   store_t *store;

#ifdef POUT
   init_store(&store,&p_stock,&p_client_action);
#else
   init_store(&store,NULL,NULL);
#endif // POUT

#ifdef POUT
   printf ("\n=== Ouverture du magasin ===\n\n");
#endif // POUT

   simulate_store(store);

#ifdef POUT
   printf ("\n=== Fermeture du magasin ===\n");
#endif // POUT

   free_store(store);

   return 0;
}
