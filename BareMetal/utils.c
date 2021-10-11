#include "utils.h"

void strrev(char* str)
{
	size_t len = strlen(str);

    for (size_t i = 0; i < len / 2; ++i)
    {
        uint8_t temp = str[i];

        str[i] = str [len - i - 1];

        str [len - i - 1] = temp;
    }
}

size_t strlen(const char* str)
{
	const char* start = str;

	while (*(str++));

	return str - start - 1;
}

void itoa(char* dst, uint32_t x)
{
	// 2^32 = 4.3E+9
	for (uint32_t i = 0; i < 10; ++i)
	{
		uint8_t digit = x % 10;
		x /= 10;

		dst[i] = '0' + digit;
	}

    for (size_t i = 10; i > 0; i--)
    {
        if (dst[i] == '0' && dst[i-1] != '0')
        {
            dst[i] = 0;
            break;
        }
    }

	strrev(dst);
}