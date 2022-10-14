#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "parser.h"
#include "linkedlist.h";


void remove_char(char* s, char c)
{
    int writer = 0, reader = 0;

    while (s[reader])
    {
        if (s[reader] != c)
        {
            s[writer] = s[reader];
            writer++;
        }

        reader++;
    }

    s[writer] = 0;
}

/**
* sanitizes given input by removing ",\,\r,\n
*/
char* sanitize(char* in) {
    remove_char(in, 34);
    remove_char(in, 92);
    remove_char(in, 13);
    remove_char(in, 10);
    return in;
}

/**
* Parses a file of elements seperated by a specified char into a linked list
* 
* @params:
* fd : file discriptor
* seperator: char seperating the elements
*/
linkedlist* parse(char* filename, char seperator) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    char buf[MAX_LIST_ELEM_SIZE];
    char elem[MAX_LIST_ELEM_SIZE+1]; // avoid buffer overflow
    size_t offset = 0;
    size_t i;
    linkedlist* ll = create_list();
    while (1) {
        if (fseek(file, offset, SEEK_SET)) {
            fprintf(stderr, "An Error has occured while seeking\n");
            return NULL;
        }
        memset(buf, 0, MAX_LIST_ELEM_SIZE);
        size_t read = fread(buf, sizeof(char), MAX_LIST_ELEM_SIZE, file);
        memset(elem, 0, MAX_LIST_ELEM_SIZE+1);
        if (!read) {
            return ll;
        }
        for (i = 0; i < read; ++i) {
            //EOF reached or seperator found
            if (buf[i] == EOF || buf[i] == seperator) {
                break;
            }
            elem[i] = buf[i];
        }
        // didnt find the seperator
        if (i > MAX_LIST_ELEM_SIZE) {
            fprintf(stderr, "Element size to big. Maximum size: %d\n", MAX_LIST_ELEM_SIZE);
            return NULL;
        }
        list_add(ll, sanitize(elem));
        if (buf[i] == EOF) {
            return ll;
        }
        offset += i+1;
    }
    



}


