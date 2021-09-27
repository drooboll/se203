#include <stdio.h>
#include <malloc.h>

void * getStackAddr(){
    void *p = &p;
    // Do not try this at home!
    return p;
}

void * getHeapAddr(){
    void *p = malloc(1);
    return p;
}

int main(){
    void * heap;

    printf("Test pointers:\n");
    printf("Stack: %p, Heap: %p", getStackAddr(), heap = getHeapAddr());
    
    free(heap);
}