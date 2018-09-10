//
// Created by paulo on 08/09/2018.
//

#include <stdio.h>
#include "./compress/compress.h"
#include "TADs/heap.h"


int main()
{

    FILE *in = fopen("teste.txt", "rb");

    HashTable *ht = get_frequency(in);

    print_table(ht);

    printf("Printando a Heap:\n");

    Heap *heap = create_heap();
    heap = ht_to_heap(ht, heap);

    print_heap(heap);

    // Teste
    int i = 1;
    while(heap->size > 1 || i == 1){
        printf("\n%d: Removeu os 2 menores nos\nAdicionou um novo no\n", i++);
        remove_node(heap);
        print_heap(heap);
    }

    fclose(in);

    return 0;
}
