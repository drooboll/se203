#include <stdint.h>

uint8_t i = 0;
int main()
{
    while (1)
    {
        if (i < 100)
            i++;
        else
            i = 0;
    }

    return 0;
}