#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define BMP_HEADER_SIZE_IN_BYTES 40

#include "./stb_image.h"
#include "./stb_image_write.h"
#include "./string_utils.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>




void convert(char *file_paths[], char *output_format);
static void soffice_convert(char *file_path, char *output_format);
static void png_to_ico(char *file_path);
static bool is_supported_stb_image_format(char *format);
static void stbi_convert(char *file_path, char *output_format);



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
 *  Convierte todos los archivos con rutas en FILE_PATHS al formato OUTPUT_FORMAT y los guarda en ./ conservando los nombres.
 *  @param file_paths Rutas de los archivos a convertir.
 *  @param output_format Formato al cual convertir (sin el punto).
 */
void convert(char *file_paths[], char *output_format) {

    to_lowercase_string(output_format);

    for (size_t i = 0; file_paths[i] != NULL; i++) {

        if (strings_are_equal(output_format, "ico") && ends_with(file_paths[i], ".png")) {
            png_to_ico(file_paths[i]);
            continue;
        }


        if (is_supported_stb_image_format(output_format) && is_supported_stb_image_format(get_file_extension(file_paths[i]))) {
            stbi_convert(file_paths[i], output_format);
            continue;
        }
            
        else {
            soffice_convert(file_paths[i], output_format);
        }
            
    }  
}





static void soffice_convert(char *file_path, char *output_format) {
    char command[512];
    snprintf(command, sizeof(command), "soffice --headless --convert-to %s --outdir . \"%s\"", output_format, file_path);
    system(command);
}



static void png_to_ico(char *file_path) {

    int width, height, channels;
    stbi_uc *image_data = stbi_load(file_path, &width, &height, &channels, 4);

    if (!image_data) {
        fprintf(stderr, "Error al cargar imagen: %s\n", stbi_failure_reason());
        exit(EXIT_FAILURE);
    }

    replace_suffix(file_path, "png", "ico");


    FILE *file_pointer = fopen(file_path, "wb");
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




static bool is_supported_stb_image_format(char *format) {
    return (
        strings_are_equal(format, "jpeg") ||
        strings_are_equal(format, "jpg") ||
        strings_are_equal(format, "png") ||
        strings_are_equal(format, "tga") ||
        strings_are_equal(format, "bmp")
    );
}

static void stbi_convert(char *file_path, char *output_format) {


    int width, height, channels;
    stbi_uc *image_data = stbi_load(file_path, &width, &height, &channels, 0);

    if (!image_data) {
        fprintf(stderr, "Error al cargar imagen: %s\n", stbi_failure_reason());
        exit(EXIT_FAILURE);
    }


    replace_suffix(file_path, get_file_extension(file_path), output_format);


    if (strings_are_equal(output_format, "jpeg") || strings_are_equal(output_format, "jpg"))
        stbi_write_jpg(file_path, width, height, channels, image_data, 90);

    else if (strings_are_equal(output_format, "png"))
        stbi_write_png(file_path, width, height, channels, image_data, width * channels);

    else if (strings_are_equal(output_format, "tga"))
        stbi_write_tga(file_path, width, height, channels, image_data);
    
    else if (strings_are_equal(output_format, "bmp"))
        stbi_write_bmp(file_path, width, height, channels, image_data);
    

    stbi_image_free(image_data);

}