#include <string.h>
#include <stdio.h>
#include "prototypes.h"

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

}

void cadastrar_sensor_ao_setor(string id_setor, string id_sensor, listas_t listas)
{

}

void cadastrar_leitura(string id_sensor, sensor_un_t *sensor)
{

}

leitura_t adicionar_leitura(int minimo, int maximo)
{

}

struct tm cadastrar_data_hora()
{

}
