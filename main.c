//
// Created by paulo on 08/09/2018.
//

#include <stdio.h>
#include "./compress/compress.h"
#include "./decompress/decompress.h"
#include "./TADs/heap.h"
#include "./tests/Main_Test.h"

int main()
{

    if(runTests() == 0) {
        printf("All tests done!\n");
    } else {
        printf("Failed Tests, exiting program...");
        return 0;
    }

    int opcao;

    printf("Digite sua escolha:\n(1) Comprimir\n(2) Descomprimir\n(Outro) Sair\n");

    scanf("%d", &opcao);

    if(opcao == 1) {
        start_compression();
    } else if(opcao == 2) {
        start_decompression();
    } else {
        printf("Saindo do programa...\n");
    }

    return 0;
}
