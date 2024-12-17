#define STB_IMAGE_IMPLEMENTATION
#define BMP_HEADER_SIZE_IN_BYTES 40

#include "./stb_image.h"
#include "./string_utils.h"

#include <stdlib.h>
#include <stdio.h>



void convert(char *filepaths[], char *output_format);
static void soffice_convert(char *filepath, char *output_format);
static void png_to_ico(char *filepath);



#pragma pack(push, 1)
typedef struct {
    uint16_t reserved;
    uint16_t type;
    uint16_t image_count;
} ICOHeader;

typedef struct {
    uint8_t width_in_px;
    uint8_t height_in_px;
    uint8_t color_count;
    uint8_t reserved;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    uint32_t image_data_size;
    uint32_t offset_to_image_data;
} ICONDIRENTRY;
#pragma pack(pop)







/**
 *  Convierte todos los archivos con rutas en FILEPATHS al formato OUTPUT_FORMAT y los guarda en ./ conservando los nombres.
 *  @param filepaths Rutas de los archivos a convertir.
 *  @param output_format Formato al cual convertir (sin el punto).
 */
void convert(char *filepaths[], char *output_format) {

    to_lowercase_string(output_format);

    for (size_t i = 0; filepaths[i] != NULL; i++) {

        if (strcmp(output_format, "ico") == 0 && ends_with(filepaths[i], ".png"))
            png_to_ico(filepaths[i]);

        else
            soffice_convert(filepaths[i], output_format);
    }  
}





static void soffice_convert(char *filepath, char *output_format) {
    char command[512];
    snprintf(command, sizeof(command), "soffice --headless --convert-to %s --outdir . \"%s\"", output_format, filepath);
    system(command);
}




static void png_to_ico(char *filepath) {

    int width, height, channels;
    stbi_uc *image_data = stbi_load(filepath, &width, &height, &channels, 4);

    if (!image_data) {
        fprintf(stderr, "Error al cargar imagen: %s\n", stbi_failure_reason());
        exit(EXIT_FAILURE);
    }

    replace_suffix(filepath, "png", "ico");


    FILE *file_pointer = fopen(filepath, "wb");
    ICOHeader ico_header = {0, 1, 1};
    fwrite(&ico_header, sizeof(ICOHeader), 1, file_pointer);


    ICONDIRENTRY ico_directory_entry;
    ico_directory_entry.width_in_px =           (width >= 256) ? 0 : width;
    ico_directory_entry.height_in_px =          ico_directory_entry.width_in_px;
    ico_directory_entry.color_count =           0;
    ico_directory_entry.reserved =              0;
    ico_directory_entry.color_planes =          1;
    ico_directory_entry.bits_per_pixel =        32;
    ico_directory_entry.image_data_size =       BMP_HEADER_SIZE_IN_BYTES + (width * height * 4);
    ico_directory_entry.offset_to_image_data =  sizeof(ICOHeader) + sizeof(ICONDIRENTRY);
    fwrite(&ico_directory_entry, sizeof(ICONDIRENTRY), 1, file_pointer);

    
    uint8_t bmp_header[BMP_HEADER_SIZE_IN_BYTES] = {0};
    *(uint32_t *)   &bmp_header[0] = BMP_HEADER_SIZE_IN_BYTES;
    *(int32_t *)    &bmp_header[4] = width;
    *(int32_t *)    &bmp_header[8] = height * 2;
    *(uint16_t *)   &bmp_header[12] = 1;
    *(uint16_t *)   &bmp_header[14] = 32;
    fwrite(bmp_header, sizeof(bmp_header), 1, file_pointer);

    
    for (int y = height - 1; y >= 0; y--)
        fwrite(&image_data[y * width * 4], 1, width * 4, file_pointer);

    fclose(file_pointer);
    
}