#include "../include/prototypes.h"

// .................... PESQUISAs
void pesquisar_por_tipo(int tipo, listas_t listas)
{
    
}

void pesquisar_sensores_setor(int id_setor, listas_t listas)
{

} 

void pesquisar_descricao(string descricao, listas_t listas)
{

}

char *pesquisar_nome_sensor(int id_sensor, listas_t listas)
{
    sensor_t *sensor = listas.lista_sensores_tipos;
    while(sensor){
        if(sensor->id == id_sensor){
            return sensor->nome;
        }
        sensor = sensor->proximo;
    }
    return NULL;
}

char *pesquisar_nome_setor(int id_setor, listas_t listas)
{
    setor_t *setor = listas.lista_setores;
    while(setor){
        if(setor->id == id_setor){
            return setor->nome;
        }
        setor = setor->proximo;
    }
    return NULL;
}

char *pesquisar_nome_categoria(int id_categoria, listas_t listas)
{
    categoria_sensor_t *categoria = listas.lista_categoria_sensores;
    while(categoria){
        if(categoria->id == id_categoria){
            return categoria->nome;
        }
        categoria = categoria->proximo;
    }
    return NULL;
}
