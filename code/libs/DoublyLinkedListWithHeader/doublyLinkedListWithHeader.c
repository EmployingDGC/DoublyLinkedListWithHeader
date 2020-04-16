#include <stdlib.h>

typedef struct editableValue
{
    int value_int;
    float value_float;
    char value_char;
} Value;


typedef struct element
{
    Value value;
    unsigned int posX;
    struct element *next;
    struct element *previous;
} EList;


typedef struct header
{
    unsigned int len;
    EList *first_element;
    EList *last_element;
} List;


/*
 * Função para criar uma nova lista
 * 
 * return List *: se conseguir criar a lista
 * return NULL: se não foi possivel criar a lista
*/
List *newList()
{
    List *new = (List *) malloc(sizeof(List));

    if (new == NULL)
        return new;
    
    new -> first_element = NULL;
    new -> last_element = NULL;
    new -> len = 0;

    return new;
}
