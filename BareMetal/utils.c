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

void* memcpy(void* dst, const void* src, size_t n)
{
    if (src == dst)
    {
        return (void*) dst;
    }

    size_t index = 0;

    if (n != 0 && n > 16)
    {
        for (; index < n >> 2; ++index)
        {
            *((uint32_t*) dst + index) = *((uint32_t*) src + index);
        }

        index *= 4;
    }

    for (; index < n; ++index)
    {
        *((char*) dst + index) = *((char*) src + index);
    }

    return (void*) dst;
}

void* memmove(void* dst, const void* src, size_t n)
{
    if (dst == src)
    {
        return dst;
    }

    if (dst > src)
    {
        if (src + n > dst)
        {
            size_t diff = src + n - dst;

            memcpy(dst + diff, src + diff, n - diff);
            return memcpy(dst, src, diff);
        }
    }
    else
    {
        if (dst + n > src)
        {
            size_t diff = src + n - dst;

            void* result = memcpy(dst, src, n - diff);
            memcpy(dst + n - diff, src + n - diff, diff);

            return result;
        }
    }

    return memcpy(dst, src, n);
}

void* memset(void* dst, int c, size_t n)
{
    // Use lower byte on ARM
    uint8_t pattern = (uint8_t) c;

    size_t index = 0;

    if (n != 0 && n > 16)
    {
        uint32_t pattern32 = pattern << 24 | pattern << 16 | pattern << 8 | pattern;

        for (; index < n >> 2; ++index)
        {
            *((uint32_t*) dst + index) = pattern32;
        }

        index *= 4;
    }

    for (; index < n; ++index)
    {
        *((uint8_t*) dst + index) = pattern;
    }

    return dst;
}

