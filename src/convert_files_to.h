#include <stdlib.h>
#include <stdio.h>

/**
 *  Convierte todos los archivos con rutas en FILEPATHS al formato OUTPUT_FORMAT y los guarda en ./ conservando los nombres.
 *  @param filepaths Rutas de los archivos a convertir
 *  @param output_format Formato al cual convertir, sin el punto. Los formatos soportados vienen determinados por la instalación de soffice
 */
void convert_files_to(char *filepaths[], char *output_format) {

    char command[512];

    for (int i = 0; filepaths[i] != NULL; i++) {
        snprintf(command, sizeof(command), "soffice --headless --convert-to %s --outdir . \"%s\"", output_format, filepaths[i]);
        
        system(command);
        //    fprintf(stderr, "La conversión falló\nAsegúrese de que LibreOffice está instalado y verifique las rutas proporcionadas");
        //    exit(EXIT_FAILURE);
        //}
    }
        
    
    
}