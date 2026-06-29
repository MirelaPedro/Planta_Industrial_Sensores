#include "../include/prototypes.h"

// .................... VERIFICACAO
int verificar_sensor_no_setor(int id_sensor, int id_setor, listas_t listas)
{
    setor_t *lista_setores = listas.lista_setores;
    while(lista_setores)
    {
        if(lista_setores->id == id_setor) {
            sensor_un_t *lista_sensores_un = lista_setores->lista_sensores_un;
            while(lista_sensores_un)
            {
                if(lista_sensores_un->id_sensor_tipo == id_sensor) {
                    return 1; // True
                }
                lista_setores->lista_sensores_un = lista_setores->lista_sensores_un->proximo;
            }
            return 0; // False
        }
        lista_setores = lista_setores->proximo;
    }
    return 0; // False
}

char *verificar_sensor_todos_setores(int id_sensor, listas_t listas) // retorna '0' para estoque e o inicio de um vetor do id do setor se estiver em um setor
{

}

int confirmar(string pergunta) // retorna 1 para sim e 0 para não
{

}

int verificar_categoria_existente(string nome_categoria, categoria_sensor_t *lista_categorias)
{

}

int verificar_tipo_existente(string nome_tipo, sensor_t *listas_tipos)
{

}

int verificar_setor_existente_nome(string nome_setor, setor_t *lista_setores)
{
    while(lista_setores)
    {
        if(!strcmp(lista_setores->nome, nome_setor)) {
            return 1; // True
        }
        lista_setores = lista_setores->proximo;
    }
    return 0; // False
}

int verificar_setor_existente_id(int id_setor, setor_t *lista_setores)
{
    while(lista_setores)
    {
        if(lista_setores->id == id_setor) {
            return 1; // True
        }
        lista_setores = lista_setores->proximo;
    }
    return 0; // False
}
