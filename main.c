#include "linkedlist.h"
#include "parser.h"
#include <stdio.h>


int main(void) {
    linkedlist* ll = parse("cars.txt", 0x3b);
    if (!ll) {
        fprintf(stderr, "Something went wrong...\n");
    }
    else {
        printf("File parsed successfully\n");
        print_list(ll);
    }
    free_list(ll);
}