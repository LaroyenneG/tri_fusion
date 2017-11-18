//
// Created by guillaume on 17/11/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "tri_fusion.h"

void fusion_secession(int *tab, size_t start, size_t finish, size_t finish2) {

    int *copyTab;
    size_t deb2 = finish + 1;
    size_t count = start;
    size_t count2 = deb2;


    copyTab = malloc((finish - start + 1) * sizeof(int));
    if (copyTab == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    for (size_t i = start; i <= finish; i++) {
        copyTab[i - start] = tab[i];
    }

    for (size_t i = start; i <= finish2; i++) {
        if (count == deb2) {
            break;
        } else if (count2 == (finish2 + 1)) {
            tab[i] = copyTab[count - start];
            count++;
        } else if (copyTab[count - start] < tab[count2]) {
            tab[i] = copyTab[count - start];
            count++;
        } else {
            tab[i] = tab[count2];
            count2++;
        }
    }

    free(copyTab);
}


void tri_fusion_recursive(int *tab, size_t start, size_t finish) {

    if (start == finish) {
        return;
    }

    size_t middle = (finish + start) / 2;
    tri_fusion_recursive(tab, start, middle);
    tri_fusion_recursive(tab, middle + 1, finish);
    fusion_secession(tab, start, middle, finish);
}

void tri_fusion(int *tab, size_t size) {

    if (size == 0) {
        return;
    }

    tri_fusion_recursive(tab, 0, size - 1);
}