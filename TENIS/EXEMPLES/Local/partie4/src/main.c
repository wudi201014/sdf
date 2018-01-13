
#include "kerosene.h"
#include <stdio.h>

int main (void)
{
		int v = 3;
		int br = 0;
		int k = 3;
		int res = kerosene(v,br,k);
		v= 2;
		br=1;
		k = 1;
		res = kerosene(v,br,k);
	
		printf("res =  %d\n",res);
        return 0;
}
