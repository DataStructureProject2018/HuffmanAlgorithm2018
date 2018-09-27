//
// Created by paulo on 26/09/2018.
//

#ifndef HUFFMAN_MINUNIT_H
#define HUFFMAN_MINUNIT_H

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); \
                                if (message) return message; } while (0)

#endif //HUFFMAN_MINUNIT_H
