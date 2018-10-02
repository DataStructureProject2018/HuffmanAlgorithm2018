//
// Created by paulo on 08/09/2018.
//

#include <stdio.h>
#include "./compress/compress.h"
#include "./decompress/decompress.h"
#include "./TADs/heap.h"
#include "./tests/teste.h"

int main()
{

    int opcao;

    printf("Type your choice:\n(1) Compress\n(2) Decompress\n(3) Run Unit Tests\n(Other) Quit\n");

    scanf("%d", &opcao);

    if(opcao == 1) {
        start_compression();
    } else if(opcao == 2) {
        start_decompression();
    } else if(opcao == 3) {
        start_tests();
    } else {
        printf("Saindo do programa...\n");
    }

    return 0;
}
