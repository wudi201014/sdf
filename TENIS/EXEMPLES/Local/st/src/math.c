#include "math.h"

double sqrt_aux(double x, double last)
{
        double next;

        next = (last+x/last) / 2;

        if ((next - last) < 1E-16 && (next - last) > -1E-16)
                return next;

        else
                return sqrt_aux(x, next);

}

double racine(double x)
{
        if (x<0)
                return 0;

        return sqrt_aux(x, x);
}

int Square(int x)
{
        return x*x;
}
