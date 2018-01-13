#include "counter.i"
unsigned char counter;
unsigned char set_counter(unsigned char val_init)
{
  /* this service permit to set the counter value at any time */
if (val_init>=254) {
	counter = 0;
} else
{
	counter = val_init+1;
}
return counter; 
}

