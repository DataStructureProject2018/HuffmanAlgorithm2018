//
// Created by paulo on 17/09/2018.
//

#ifndef HUFFMAN_UTILITIES_H
#define HUFFMAN_UTILITIES_H

unsigned char is_bit_i_set(unsigned char c, int i){

    unsigned char mask = 1 << i;
    return mask & c;
}

#endif //HUFFMAN_UTILITIES_H
