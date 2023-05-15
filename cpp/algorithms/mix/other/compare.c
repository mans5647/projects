#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

typedef struct String
{
    int8_t * str;
    size_t length;
} String;


void allocate_string(String *s, char * text)
{
    s->str = (char*)malloc(strlen(text) * sizeof(char*));
    s->length = strlen(text);
    strcpy(s->str, text);
    return;
}

void DeleteString(String *s)
{
    free(s->str);
    return;
}

void append_string(String *dest, String *src)
{
    size_t old_size = dest->length;
    char * tmp = (char*)malloc(dest->length * sizeof(char*));
    strcpy(tmp, dest->str);
    DeleteString(&*dest);

    size_t lng = strlen(src->str);

    dest->length += lng;

    dest->str = (char*)malloc(sizeof(char*) * dest->length);

    strcpy(dest->str, tmp);
    free(tmp);
    size_t start = 0;
    for (size_t i = old_size; i < dest->length - 1; i++)
    {
        dest->str[i] = src->str[start++];
    }

}


bool compare(String* str, String* str1)
{
    if (strlen(str->str) != strlen(str1->str)) return false;
    bool s = true;
    while (*str->str != '\0' & *str1->str != '\0')
    {
        if (*str->str == *str1->str)
        {
            s = true;
        }
        else 
        {
            s = false;
            break;
        }
        *str->str++;
        *str1->str++;
    }
    return s;
}

int main()
{
    String s;
    String s1;
    allocate_string(&s1, "World");
    allocate_string(&s, "Hello");
    printf("%s", s.str);
    append_string(&s, &s1);
    printf("%s", s.str);
}