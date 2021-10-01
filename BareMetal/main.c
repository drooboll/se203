#include <stdint.h>

uint8_t i = 0;

uint_fast32_t fibo(uint_fast32_t n)
{
    if (!n)
    {
        return 0;
    }
    
    if (n == 1)
    {
        return 1;
    }

    return fibo(n - 1) + fibo(n - 2);
}

int main()
{
    uint_fast32_t test = fib(8);

    while(1){}

    return 0;
}