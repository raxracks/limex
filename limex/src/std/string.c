#include "std/string.h"

size_t strlen(const char *s)
{
    size_t count = 0;
    while(*s!='\0')
    {
        count++;
        s++;
    }
    return count;
}

char* strcpy(char* destination, const char* source)
{
    if (destination == NULL) return NULL;
    char *ptr = destination;
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    return ptr;
}

char* strcat(char* destination, const char* source)
{
    if (destination == NULL) return NULL;
    char *ptr = destination + strlen(destination);
    while (*source != '\0') *ptr++ = *source++;
    return destination;
}