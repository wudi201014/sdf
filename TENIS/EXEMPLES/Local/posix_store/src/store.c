#include "store.h"


/* Fonction pour tirer un nombre au sort entre 0 et max. */
static int get_random (int max){
   double val;

   val = (double) max * rand ();
   val = val / (RAND_MAX + 1.0);

   return ((int) val);
}


/* Fonction pour le thread du magasin. */
static void * fn_store (void * p_data)
{
   store_t *store = (store_t*) p_data;

   while (store->commande > 0){

/* Debut de la zone protegee. */
      pthread_mutex_lock (store->mutex_stock);
      if(store->stock == 0){
         store->stock = INITIAL_STOCK;
         if(store->print_stock){
            store->print_stock(store->stock);
         }
         //printf ("Remplissage du stock de %d articles !\n", store->stock);
         pthread_mutex_lock(store->mutex_commande);
         store->commande--;
         pthread_mutex_unlock (store->mutex_commande);
      }
      pthread_mutex_unlock (store->mutex_stock);
      /* Fin de la zone protegee. */

      //Attente de de 0 à 500ms
      usleep (get_random (5)*100000);
   }
   return NULL;
}


/* Fonction pour les threads des clients. */
   static void * fn_clients (void * p_data)
   {
      store_t *store = (store_t*) p_data;
      int val;

      while (store->commande != 0 || store->stock >0){

         /* Debut de la zone protegee. */
         pthread_mutex_lock (store->mutex_stock);

         if(store->stock > 0){

            if(store->stock <=3){
               val = 1+get_random (store->stock-1);
            }else{
               val = 1+get_random (3);
            }

            store->stock = store->stock - val;
            if(store->print_client_action){
               store->print_client_action(val, store->stock);
            }
         }
         pthread_mutex_unlock (store->mutex_stock);
         /* Fin de la zone protegee. */

         //Attente de de 0 à 300ms
         usleep (get_random (3)*100000);
      }
      return NULL;
   }

void init_store(store_t **store,void (*p_stock)(int), void (*p_client_action)(int,int)){

   *store = (store_t*) malloc (sizeof(store_t));

   (*store)->stock = INITIAL_STOCK;
   (*store)->commande = MAX_COMMANDE;
   ( *store)->mutex_stock = malloc(sizeof(pthread_mutex_t));
   (*store)->print_stock = p_stock;
   (*store)->print_client_action = p_client_action;

   pthread_mutex_init((*store)->mutex_stock, NULL);
   (*store)->mutex_commande = malloc(sizeof(pthread_mutex_t));
   pthread_mutex_init((*store)->mutex_commande, NULL);

}

void free_store(store_t *store){
   free(store->mutex_stock);
   free(store->mutex_commande);
   free(store);
}


int simulate_store(store_t *store){
   int i = 0;
   int ret = 0;


/* Creation des threads. */
         //printf ("Le magasin ouvre ses portes!\n");
         ret = pthread_create (
            & store->thread_store, NULL,
            fn_store, (void *) store
            );

/* Creation des threads des clients si celui du magasinn a reussi. */
         if (! ret)
         {
            //printf ("Les clients  entre dans le magasin!\n\n");
            for (i = 0; i < NB_CLIENTS; i++)
            {
               ret = pthread_create (
                  & store->thread_clients [i], NULL,
                  fn_clients, (void *) store);

            }
         }

/* Attente de la fin des threads. */
         i = 0;
         for (i = 0; i < NB_CLIENTS; i++)
         {
            pthread_join (store->thread_clients [i], NULL);
         }
         pthread_join (store->thread_store, NULL);
         //printf ("\nLe magasin ferme.");

         return EXIT_SUCCESS;
      }
