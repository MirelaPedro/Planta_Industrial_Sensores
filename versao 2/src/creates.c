#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/prototypes.h"

// .................... CADASTROs
sensor_un_t *cadastro_sensor_un(listas_t listas)
{
    sensor_un_t *sensor = calloc(sizeof(sensor_un_t), 1);

    string aux;

    printf("    CADASTRANDO SENSOR     \n");
    printf("Nome: ");
    fgets(aux, T_STRING, stdin);
    retirar_enter(aux);
    formatar_string_texto(aux);

    // adicionando o nome ao nomes

    
    return sensor;
}

sensor_t *cadastro_sensor(string nome, categoria_sensor_t *categoria_sensor)
{

}

categoria_sensor_t *cadastro_categoria_sensor(string nome)
{

}

setor_t *cadastro_setor()
{
    setor_t *setor = calloc(sizeof(setor_t), 1);

    printf("    CADASTRANDO SETOR     \n");
    printf("Nome: ");
    fgets(setor->nome, T_STRING, stdin);
    retirar_enter(setor->nome);
    formatar_string_texto(setor->nome);

    printf("Descrição: ");
    fgets(setor->descricao, T_STRING, stdin);
    retirar_enter(setor->descricao);
    formatar_string_texto(setor->descricao);

    setor->qtd_sensores_instalados = 0;
    setor->lista_sensores_un = NULL;
    setor->proximo = NULL;
    
    return setor;
}

void cadastrar_sensor_ao_setor(int id_setor, int id_sensor, listas_t listas)
{

}

void cadastrar_leitura(int id_sensor, sensor_un_t *sensor)
{

}

leitura_t adicionar_leitura(int minimo, int maximo)
{

}

struct tm cadastrar_data_hora()
{

}
