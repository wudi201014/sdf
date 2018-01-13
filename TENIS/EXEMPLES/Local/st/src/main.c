/* Statistics Program:
 * This program computes for two arrays of numbers the sum, the
 * mean, the variance, and standard deviation.  It then determines the
 * correlation coefficient between the two arrays.
 */

#include "stat.h"

#ifdef POUT
#include <stdio.h>
#endif // POUT

int main ()
{
        double MeanA, MeanB, VarA, VarB, StddevA, StddevB;

        InitSeed ();

        Initialize(ArrayA);
        Calc_Sum_Mean(ArrayA, &SumA, &MeanA);
        Calc_Var_Stddev(ArrayA, MeanA, &VarA, &StddevA);

        Initialize(ArrayB);
        Calc_Sum_Mean(ArrayB, &SumB, &MeanB);
        Calc_Var_Stddev(ArrayB, MeanB, &VarB, &StddevB);
        Calc_LinCorrCoef(ArrayA, ArrayB, MeanA, MeanB);

#ifdef POUT
        printf ("\n   *** Statictics TEST ***\n\n");
        printf("     Sum A = %12.4f,      Sum B = %12.4f\n", SumA, SumB);
        printf("    Mean A = %12.4f,     Mean B = %12.4f\n", MeanA, MeanB);
        printf("Variance A = %12.4f, Variance B = %12.4f\n", VarA, VarB);
        printf(" Std Dev A = %12.4f, Variance B = %12.4f\n", StddevA, StddevB);
        printf("\nLinear Correlation Coefficient = %f\n", Coef);
#endif // POUT

        return 0;
}
