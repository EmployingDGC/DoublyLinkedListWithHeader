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
    unsigned int pos_x;
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
    
    new -> pos_x = 0;
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
            aux -> pos_x += 1;
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
    new -> pos_x = lenList(list);
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
 * param pos_x: posição a ser adicionado o elemento
 * 
 * return true: se conseguir adicionar
 * return false: se não conseguir adicionar
*/
Bool addIndexList(List *list, Value value, int pos_x)
{
    if (listIsEmpty(list))
        return addFirstList(list, value);
    
    if (pos_x < 0)
    {
        pos_x += lenList(list);
        
        if (pos_x < 0)
            pos_x = 0;
    }
    
    if (pos_x == 0)
        return addFirstList(list, value);
    
    if (pos_x >= lenList(list))
        return addLastList(list, value);
    
    EList *new = (EList *) malloc(sizeof(EList));

    if (new == NULL)
        return false;

    new -> pos_x = pos_x;
    new -> value = value;

    EList *aux;
    if (pos_x > lenList(list) / 2)
        for (aux = list -> last_element; aux != pos_x; aux = aux -> previous);
    else
        for (aux = list -> first_element; aux != pos_x; aux = aux -> next);
    
    new -> previous = aux -> previous;
    new -> next = aux;

    aux -> previous -> next = new;
    aux -> previous = new;

    for (aux; aux != NULL; aux = aux -> next)
        aux -> pos_x += 1;
    
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

/*
 * Função para remover um elemento do fim da lista
 * 
 * param list: ponteiro para uma lista
 * 
 * return true: se conseguir remover
 * return false: se não conseguir remover
*/
Bool delLastList(List *list)
{
    if (listIsEmpty(list))
        return false;
    
    EList *aux = list -> last_element;

    if (aux -> previous != NULL)
        aux -> previous -> next = NULL;
    else
        list -> first_element = NULL;

    list -> last_element = aux -> previous;

    free(aux);

    list -> len -= 1;

    return true;
}

/*
 * Função para remover um elemento de uma posição da lista
 * 
 * param list: ponteiro para uma lista
 * param pos_x: posição a ser removida
 * 
 * return true: se conseguir remover
 * return false: se não conseguir remover
*/
Bool delIndexList(List *list, int pos_x)
{
    if (listIsEmpty(list) || pos_x >= lenList(list))
        return false;
    
    if (pos_x < 0)
    {
        pos_x += lenList(list);
        
        if (pos_x < 0)
            return false;
    }
    
    if (pos_x == 0)
        return delFirstList(list);
    
    if (pos_x == lenList(list) - 1)
        return delLastList(list);
    
    EList *aux;
    if (pos_x > lenList(list) / 2)
        for (aux = list -> last_element; aux != pos_x; aux = aux -> previous);
    else
        for (aux = list -> first_element; aux != pos_x; aux = aux -> next);
    
    aux -> previous -> next = aux -> next;
    aux -> next -> previous = aux -> previous;

    free(aux);

    list -> len -= 1;

    return true;
}

/*
 * Função para adicionar os elementos da segunda lista no fim da primeira
 * 
 * param list1: ponteiro para a primeira lista
 * param list2: ponteiro para a segunda lista
 * 
 * return unsigned int: quantos elementos foram adicionados com sucesso
*/
unsigned int extendList(List *list1, List *list2)
{
    unsigned int qty_add = 0;

    if (listIsEmpty(list2))
        return qty_add;
    
    for (EList *aux = list2 -> first_element; aux != NULL && qty_add != lenList(list2); aux = aux -> next)
    {
        if (!addLastList(list1, aux -> value))
            return qty_add;
        
        qty_add += 1;
    }
    
    return qty_add;
}

/*
 * Função para pegar um elemento de uma lista de acordo com a posição
 * 
 * param list: ponteiro para uma lista
 * param pos_x: posição a ser buscada
 * 
 * return Elist *: se achou o elemento
 * return NULL: se não achou o elemento
*/
EList *getElementList(List *list, int pos_x)
{
    if (listIsEmpty(list) || pos_x >= lenList(list))
        return NULL;
    
    if (pos_x < 0)
    {
        pos_x += lenList(list);
        
        if (pos_x < 0)
            return NULL;
    }

    EList *aux;
    if (pos_x > lenList(list) / 2)
        for (aux = list -> last_element; aux != pos_x; aux = aux -> previous);
    else
        for (aux = list -> first_element; aux != pos_x; aux = aux -> next);
    
    return aux;
}

/*
 * Função para pegar o próximo elemento de uma lista
 * 
 * param list: ponteiro para uma lista
 * param element: ponteiro para um elemento de lista, caso NULL retornara o primeiro elemento da lista
 * 
 * return EList *: se tiver próximo elemento
 * return NULL: se não tiver próximo elemento
*/
EList *getNextElementList(List *list, EList *current)
{
    if (listIsEmpty(list))
        return NULL;
    
    if (current == NULL)
        return list -> first_element;
    
    return current -> next;
}
