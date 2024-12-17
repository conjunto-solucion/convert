#include <stdio.h>
#include <stdlib.h>
#include "./convert.h"



int main(int argc, char **argv) {

    if (argc < 3) {
        fprintf(stderr, "Uso:\nconvert <formato> <archivo 1> <archivo 2>...<archivo n>\nEjemplo: convert odt ./test.docx ./test2.docx\n");
        return EXIT_FAILURE;
    }
    
    
    convert(&argv[2], argv[1]);
    return EXIT_SUCCESS;
}