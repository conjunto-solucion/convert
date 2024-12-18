#include <string.h>
#include <ctype.h>
#include <stdbool.h>


bool ends_with(char *str, char *suffix);
const void replace_suffix(char *str, const char *old_suffix, const char *new_suffix);
const void to_lowercase_string(char *s);
bool strings_are_equal(char *s, char *t);
char* get_file_extension(char *file_path);


bool ends_with(char *str, char *suffix) {
    if (strlen(suffix) > strlen(str))
        return false;

    return strings_are_equal(str + strlen(str) - strlen(suffix), suffix);
}


const void replace_suffix(char *str, const char *old_suffix, const char *new_suffix) {
    str[strlen(str) - strlen(old_suffix)] = '\0';
    strcat(str, new_suffix);
}

const void to_lowercase_string(char *s) {
    for (size_t i = 0; i < strlen(s); i++)
        s[i] = tolower(s[i]);
}

bool strings_are_equal(char *s, char *t) {
    return strcmp(s, t) == 0;
}


char* get_file_extension(char *file_path) {
    char *dot = strrchr(file_path, '.');
    return (!dot || dot == file_path)? "" : dot + 1;
}