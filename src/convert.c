#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./convert_files_to.h"


int main(int argc, char **argv) {

    if (argc >= 3) {
        convert_files_to(&argv[2], argv[1]);
        return EXIT_SUCCESS;
    }
        
    fprintf(stderr,
    "Uso:\nconvert <formato> <archivo 1> <archivo 2>...<archivo n>\nEjemplo: convert odt ./test.docx ./test2.docx\n");

    return EXIT_FAILURE;
}












/*
#include <stdio.h>
#include <stdlib.h>
#include "./docx_to_pdf.h"
#include "./wps_docx_to_google_docs_compatible_docx.h"


//#include <zip.h>
//#include "libharu/hpdf.h" 


*/