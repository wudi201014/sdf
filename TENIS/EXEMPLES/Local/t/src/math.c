#include "math.h"

int maximum(int x, int y)
{

        if (x>y){
                return x;
        } else  if (x<y){
                return y;
        } else {
                return 0;
        }
}

int valeur_milieu(int a, int b, int c)
{
        if(b > a){
                if(a > c){
                        return a;
                }else if (c > b){
                        return b;
                }else{
                        return c;
                }
        }else{
                if(b > c){
                        return b;
                }else if (c > a){
                        return a;
                }else{
                        return c;
                }
        }
}
