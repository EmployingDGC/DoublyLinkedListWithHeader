#include <stdlib.h>
#include "../Bool/bool.c"

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

/*
 * Função para obter o tamanho da lista
 * 
 * param list: ponteiro para uma lista
 * 
 * return unsigned int: tamanho da lista
*/
unsigned int lenList(List *list)
{
    return list -> len;
}

/*
 * Função para saber se uma lista está vazia
 * 
 * param list: ponteiro para uma lista
 * 
 * return true: se a lista estiver vazia
 * return false: se a lista não estiver vazia
*/
Bool listIsEmpty(List *list)
{
    if (list -> first_element == NULL && list -> last_element == NULL && list -> len == 0)
        return true;
    
    return false;
}

/*
 * Função para adicionar um elemento no início da lista
 * 
 * param list: ponteiro para uma lista
 * param value: valor do elemento que deseja adicionar
 * 
 * return true: se conseguir adicionar
 * return false: se não conseguir adicionar
*/
Bool addFirstList(List *list, Value value)
{
    EList *new = (EList *) malloc(sizeof(EList));

    if (new == NULL)
        return false;
    
    new -> posX = 0;
    new -> value = value;
    new -> previous = NULL;
    
    if (listIsEmpty(list))
    {
        new -> next = NULL;
        list -> last_element = new;
    }
    else
    {
        new -> next = list -> first_element;
        new -> next -> previous = new;

        for (EList *aux = new -> next; aux != NULL; aux = aux -> next)
            aux -> posX += 1;
    }

    list -> first_element = new;

    list -> len += 1;

    return true;
}

/*
 * Função para adicionar um elemento no fim da lista
 * 
 * param list: ponteiro para uma lista
 * param value: valor do elemento que deseja adicionar
 * 
 * return true: se conseguir adicionar
 * return false: se não conseguir adicionar
*/
Bool addLastList(List *list, Value value)
{
    if (listIsEmpty(list))
        return addFirstList(list, value);
    
    EList *new = (EList *) malloc(sizeof(EList));

    if (new == NULL)
        return false;
    
    new -> value = value;
    new -> posX = lenList(list);
    new -> next = NULL;
    new -> previous = list -> last_element;

    new -> previous -> next = new;

    list -> last_element = new;
    list -> len += 1;
    
    return true;
}

/*
 * Função para adicionar um elemento na posição X da lista
 * 
 * param list: ponteiro para uma lista
 * param value: valor do elemento que deseja adicionar
 * param posX: posição a ser adicionado o elemento
 * 
 * return true: se conseguir adicionar
 * return false: se não conseguir adicionar
*/
Bool addIndexList(List *list, Value value, int posX)
{
    if (listIsEmpty(list))
        return addFirstList(list, value);
    
    if (posX < 0)
    {
        posX += lenList(list);
        
        if (posX < 0)
            posX = 0;
    }
    
    if (posX == 0)
        return addFirstList(list, value);
    
    if (posX >= lenList(list))
        return addLastList(list, value);
    
    EList *new = (EList *) malloc(sizeof(EList));

    if (new == NULL)
        return false;

    new -> posX = posX;
    new -> value = value;

    EList *aux;
    if (posX > lenList(list) / 2)
        for (aux = list -> last_element; aux != posX; aux = aux -> previous);
    else
        for (aux = list -> first_element; aux != posX; aux = aux -> next);
    
    new -> previous = aux -> previous;
    new -> next = aux;

    aux -> previous -> next = new;
    aux -> previous = new;

    for (aux; aux != NULL; aux = aux -> next)
        aux -> posX += 1;
    
    list -> len += 1;

    return true;
}

/*
 * Função para remover um elemento do início da lista
 * 
 * param list: ponteiro para uma lista
 * 
 * return true: se conseguir remover
 * return false: se não conseguir remover
*/
Bool delFirstList(List *list)
{
    if (listIsEmpty(list))
        return false;
    
    EList *aux = list -> first_element;

    if (aux -> next != NULL)
        aux -> next -> previous = NULL;
    else
        list -> last_element = NULL;

    list -> first_element = aux -> next;

    free(aux);

    list -> len -= 1;

    return true;
}
