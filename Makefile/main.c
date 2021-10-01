#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "t1.h"
#include "t2.h"

int main()
{
    srand(42); 
    bar(pow(foo(), 1.23));
    return EXIT_SUCCESS;
}
