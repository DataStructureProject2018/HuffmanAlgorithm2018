//
// Created by paulo on 08/09/2018.
//

#include <stdio.h>
#include "./compress/compress.h"
#include "./decompress/decompress.h"
#include "./TADs/heap.h"
// TODO Mudar o createkey =, ele não e necessario pq podemos usar o proprio byte como key
int main()
{
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
