//
// Created by paulo on 08/09/2018.
//

#include <stdio.h>
#include "./compress/compress.h"
#include "TADs/heap.h"


int main()
{

    FILE *in = fopen("../teste.txt", "rb");

    HashTable *ht = get_frequency(in);

    print_table(ht);

    printf("Printando a Heap:\n");

    Heap *heap = create_heap();
    heap = add_heap(ht, heap);

    print_heap(heap);

    fclose(in);

    return 0;
}

//teste