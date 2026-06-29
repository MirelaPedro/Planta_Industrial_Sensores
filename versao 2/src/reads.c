#include <string.h>
#include <stdio.h>
#include "../include/prototypes.h"

// .................... READs
//listar
void listar_setores(setor_t *lista_setores)
{
    while(lista_setores)
    {
        mostrar_setor(lista_setores);
        lista_setores = lista_setores->proximo;
    }
}

void listar_sensores(sensor_un_t *lista_sensores)
{

}

void listar_tipos_sensores(sensor_t *lista_tipos)
{

}

void listar_categorias_sensores(categoria_sensor_t *lista_categorias)
{

}

void listar_leituras(leitura_t *lista_leituras)
{

}

void listar_leituras_sensor(sensor_un_t *sensor)
{

}

void listar_sensores_setor(setor_t *setor)
{
    if(setor->qtd_sensores_instalados > 0)
    {
        fprintf(stdout, "Sensores Instalados\n");
        sensor_un_t *sensor = setor->lista_sensores_un;
        while(sensor)
        {
            if(sensor->id_setor == setor->id){
                mostrar_sensor(sensor);
            }
            sensor = sensor->proximo;
        }
    }
    else
    {
        fprintf(stdout, "Nenhum sensor instalado nesse setor.\n");
    }
}


//mostrar
void mostrar_setor(setor_t *setor)
{
    fprintf(stdout, "ID: %d\n", setor->id);
    fprintf(stdout, "Nome: %s\n", setor->nome);
    fprintf(stdout, "Descrição: %s\n", setor->descricao);
    fprintf(stdout, "Quantidade de sensores instalados: %d\n", setor->qtd_sensores_instalados);
    listar_sensores_setor(setor);
}

void mostrar_sensor(sensor_un_t *sensor)
{

}

void mostrar_tipo_sensor(sensor_t *tipo, listas_t listas)
{
    fprintf(stdout, "ID: %i\n", tipo->id);
    fprintf(stdout, "Nome: %s\n", tipo->nome);
    fprintf(stdout, "Categoria: %s\n", pesquisar_nome_categoria(tipo->id_categoria, listas));
    fprintf(stdout, "Faixa de valores: %i a %i %s\n", tipo->faixa.inicio, tipo->faixa.fim, tipo->faixa.un_medida);
}

void mostrar_categoria_sensor(categoria_sensor_t *categoria)
{

}

void mostrar_leitura(leitura_t leitura, string un_medida)
{

}

void mostrar_data(struct tm date_time)
{

}

void mostrar_hora(struct tm date_time)
{

}

//cadastrados - sintese
void mostrar_categorias_cadastradas(categoria_sensor_t *lista_categorias)
{

}

void mostrar_tipos_sensores_cadastrados(sensor_t *lista_tipos)
{

}

void mostrar_sensores_cadastrados(sensor_un_t *lista_sensores)
{

}

void mostrar_setores_cadastrados(setor_t *lista_setores)
{

}

// .................... RELATORIOs
void relatorio_setores(listas_t listas)
{

}

void relatorio_sensores(listas_t listas)
{

}

void relatorio_leituras(listas_t listas)
{

}

// imprimir relatorios
void imprimir_relatorio_setor_geral(listas_t listas)
{

}

void imprimir_relatorio_setor_detalhado(listas_t listas)
{

}

void imprimir_relatorio_sensor_geral(listas_t listas)
{

}

void imprimir_relatorio_sensor_por_tipo(listas_t listas)
{

}

void imprimir_relatorio_sensor_por_setor(listas_t listas)
{

}

void imprimir_relatorio_leitura_geral(listas_t listas)
{

}

void imprimir_relatorio_leitura_setor(listas_t listas)
{

}

void imprimir_relatorio_leitura_sensor(listas_t listas)
{

}
