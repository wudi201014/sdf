#include "kerosene.i"
int LG=1;
int kerosene(int v, int br, int k) {
if (v>1 || br==0) {
k=k/v;
}
if (v==2 || k>1) {
k=k+1;
LG= 0;
}
return k;
}

