#ifndef STORE_H
#define STORE_H

#include <pthread.h>
#include <stdlib.h>

#define INITIAL_STOCK   20
#define NB_CLIENTS      5
#define MAX_COMMANDE    4

/* Structure stockant les informations des threads clients et du magasin. */
typedef struct
{
   int stock;
   int commande;

   pthread_t thread_store;
   pthread_t thread_clients [NB_CLIENTS];

   pthread_mutex_t *mutex_stock;
   pthread_mutex_t *mutex_commande;

   void (*print_stock)(int);
   void (*print_client_action)(int,int);
} store_t;

void init_store(store_t **store,void (*p_stock)(int), void (*p_client_action)(int,int));
void free_store(store_t *store);
int simulate_store(store_t *store);

#endif /* STORE_H */
