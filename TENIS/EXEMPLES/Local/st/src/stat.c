#include "stat.h"
#include "math.h"

/*
 * Initializes the seed used in the random number generator.
 */
void InitSeed ()
{
        Seed = 0;
}

void Calc_Sum_Mean(int Array[], int *Sum, int *Mean)
{
        int i;

        if(Array){
                *Sum = 0;
                for (i = 0; i < 10; i++)
                        *Sum += Array[i];
                if (*Sum == 0){
                        *Mean = 0;
                }else if (*Sum > 0){
                        *Mean = *Sum / 10;
                        if(*Mean > 10){
                                for (i = 0; i < 10; i++){
                                        *Mean += 1000;
                                        *Mean -= 1000;
                                }
                        }else{
                                *Mean += 3000;
                                *Mean -= 3000;
                        }
                }else{
                        *Mean = -(*Sum / 10);
                        *Mean = -(*Mean);
                }
        }
}

void Calc_Var_Stddev(int Array[], int Mean, int *Var, int *Stddev)
{
        int i;
        int diffs;

        diffs = 0.0;
        for (i = 0; i < 10; i++)
                diffs += Square(Array[i] - Mean);
        *Var = diffs/10;
        *Stddev = racine(*Var);
}


void Calc_LinCorrCoef(int ArrayA[],int ArrayB[],int MeanA,int MeanB /*, *Coef*/)
{
        int i;
        double numerator, Aterm, Bterm;

        numerator = 0.0;
        Aterm = Bterm = 0.0;
        for (i = 0; i < 10; i++) {
                numerator += (ArrayA[i] - MeanA) * (ArrayB[i] - MeanB);
                Aterm += Square(ArrayA[i] - MeanA);
                Bterm += Square(ArrayB[i] - MeanB);
        }

        /* Coef used globally */
        Coef = numerator / (racine(Aterm) * racine(Bterm));
}

/*
 * Intializes the given array with random integers.
 */
        void Initialize(int Array[])
        {
                register int i;

                for (i=0; i < 10; i++)
                        Array [i] = i + RandomInteger ()/8095;
        }

/*
 * Generates random integers between 0 and 8095
 */
        int RandomInteger()
        {
                Seed = ((Seed * 133) + 81) % 8095;
                return (Seed);
        }
