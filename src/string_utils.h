#include <string.h>
#include <ctype.h>
#include <stdbool.h>


bool ends_with(const char *str, const char *suffix);
void replace_suffix(char *str, const char *old_suffix, const char *new_suffix);
void to_lowercase_string(char *s);


bool ends_with(const char *str, const char *suffix) {
    if (strlen(suffix) > strlen(str))
        return false;

    return strcmp(str + strlen(str) - strlen(suffix), suffix) == 0;
}


void replace_suffix(char *str, const char *old_suffix, const char *new_suffix) {
    str[strlen(str) - strlen(old_suffix)] = '\0';
    strcat(str, new_suffix);
}

void to_lowercase_string(char *s) {
    for (size_t i = 0; i < strlen(s); i++)
        s[i] = tolower(s[i]);
}