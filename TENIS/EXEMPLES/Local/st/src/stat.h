#ifndef STAT_H
#define STAT_H


int Seed;
int ArrayA[10], ArrayB[10];
int SumA, SumB;
int Coef;

void InitSeed ();

void Calc_Sum_Mean(int Array[], int *Sum, int *Mean);

int Square(int x);

void Calc_Var_Stddev(int Array[], int Mean, int *Var, int *Stddev);

void Calc_LinCorrCoef(int ArrayA[],int ArrayB[],int MeanA,int MeanB /*, *Coef*/);

void Initialize(int Array[]);

int RandomInteger();


#endif /* STAT_H */
