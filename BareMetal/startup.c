extern char __bss_start, __bss_end;

void __init_bss()
{
    char* current = &__bss_start;
    while(current < &__bss_end)
    {
        *(current++) = 0;
    }
}