#include <stdlib.h>

typedef struct editableValue
{
    int value_int;
    float value_float;
    char value_char;
} Value;


typedef struct elements
{
    Value value;
    unsigned int posX;
    struct elements *next;
    struct elements *previous;
} EList;


typedef struct header
{
    unsigned int len;
    EList *first_element;
    EList *last_element;
} List;

