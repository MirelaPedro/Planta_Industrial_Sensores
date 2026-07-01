#include "../include/prototypes.h"

// perguntar para o Anderson
void* pesquisar_ponteiro(int id, void *lista)
{
    while (lista)
    {
        if(lista->id == id)
        {
            return lista;
        }
        lista = lista->proximo;
    }
    return NULL;
}
