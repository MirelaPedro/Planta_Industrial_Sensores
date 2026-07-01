#include <string.h>
#include <stdio.h>
#include "../include/prototypes.h"

// .................... READs
//listar
void listar_setores(setor_t *lista_setores, listas_t listas)
{
    while(lista_setores)
    {
        mostrar_setor(lista_setores, listas);
        lista_setores = lista_setores->proximo;
    }
}

void listar_sensores(sensor_un_t *lista_sensores, listas_t listas)
{
    while(lista_sensores)
    {
        mostrar_sensor(lista_sensores, listas);
        lista_sensores = lista_sensores->proximo;
    }
}

void listar_tipos_sensores(sensor_t *lista_tipos, listas_t listas)
{
    while(lista_tipos)
    {
        mostrar_tipo_sensor(lista_tipos, listas);
        lista_tipos = lista_tipos->proximo;
    }
}

void listar_categorias_sensores(categoria_sensor_t *lista_categorias, listas_t listas)
{
    while(lista_categorias)
    {
        mostrar_categoria_sensor(lista_categorias);
        lista_categorias = lista_categorias->proximo;
    }
}

void listar_leituras(leitura_t *lista_leituras)
{

}

// verificar erros no pesquisar ponteiro
void listar_leituras_sensor(sensor_un_t *sensor, listas_t listas)
{
    leitura_t *(leitura) = sensor->leituras;
    while(leitura)
    {
        mostrar_leitura(*(leitura), pesquisar_ponteiro(sensor->id_sensor_tipo, listas.lista_sensores_tipos)->faixa.un_medida);
        leitura = leitura->proximo;
    }
}

void listar_sensores_setor(setor_t *setor, listas_t listas)
{
    if(setor->qtd_sensores_instalados > 0)
    {
        fprintf(stdout, "Sensores Instalados\n");
        sensor_un_t *sensor = setor->lista_sensores_un;
        while(sensor)
        {
            if(sensor->id_setor == setor->id){
                mostrar_sensor(sensor, listas);
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
void mostrar_setor(setor_t *setor, listas_t listas)
{
    fprintf(stdout, "ID: %d\n", setor->id);
    fprintf(stdout, "Nome: %s\n", setor->nome);
    fprintf(stdout, "Descrição: %s\n", setor->descricao);
    fprintf(stdout, "Quantidade de sensores instalados: %d\n", setor->qtd_sensores_instalados);
    listar_sensores_setor(setor, listas);
}

void mostrar_sensor(sensor_un_t *sensor, listas_t listas)
{
    fprintf(stdout, "ID: %i\n", sensor->id);
    fprintf(stdout, "Tipo: %s\n", pesquisar_nome_tipo(sensor->id_sensor_tipo, listas));

    if(!pesquisar_nome_setor(sensor->id_setor, listas) == NULL){
        fprintf(stdout, "Setor: %s\n", pesquisar_nome_setor(sensor->id_setor, listas));
    }
    else{
        fprintf(stdout, "Setor: Estoque\n");
    }

    listar_leituras_sensor(sensor, listas);
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
    fprintf(stdout, "ID: %i\n", categoria->id);
    fprintf(stdout, "Nome: %s\n", categoria->nome);
    fprintf(stdout, "Descrição: %s\n", categoria->descricao);
}

void mostrar_leitura(leitura_t leitura, string un_medida)
{
    fprintf(stdout, "Id: %i\n", leitura.id);
    fprintf(stdout, "Modulo: %.2f %s\n", leitura.modulo, un_medida);
    fprintf(stdout, "Data: %i/%i/%i\n", leitura.date_time.tm_mday, leitura.date_time.tm_mon + 1, leitura.date_time.tm_year + 1900);
    fprintf(stdout, "Hora: %i:%i:%i\n", leitura.date_time.tm_hour, leitura.date_time.tm_min, leitura.date_time.tm_sec);
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
    while(lista_categorias)
    {
        fprintf(stdout, "Id: %i - %s\n", lista_categorias->id, lista_categorias->nome);
        lista_categorias = lista_categorias->proximo;
    }
}

void mostrar_tipos_sensores_cadastrados(sensor_t *lista_tipos)
{
    while(lista_tipos)
    {
        fprintf(stdout, "Id: %i - %s\n", lista_tipos->id, lista_tipos->nome);
        lista_tipos = lista_tipos->proximo;
    }
}

void mostrar_sensores_cadastrados(sensor_un_t *lista_sensores)
{
    while(lista_sensores)
    {
        //fprintf(stdout, "Id: %i - %s - %s\n", lista_sensores->id, pesquisar_nome_sensor(lista_sensores->id_sensor_tipo), pesquisar_nome_setor(lista_sensores->id_setor));
        lista_sensores = lista_sensores->proximo;
    }
}

void mostrar_setores_cadastrados(setor_t *lista_setores)
{
    while(lista_setores)
    {
        fprintf(stdout, "Id: %i - %s\n", lista_setores->id, lista_setores->nome);
        lista_setores = lista_setores->proximo;
    }
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
