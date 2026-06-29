#ifndef _TYPES_H_
#define _TYPES_H_

#include <time.h>

#define T_STRING 100

typedef char string[T_STRING];

typedef struct leitura
{
    float modulo; // valor da leitura
    struct tm date_time;
    struct leitura *proximo; // assim posso adicionar diferentes leituras
} leitura_t;

struct faixa_valores{
    // valores de início de fim incluídos
    int inicio; 
    int fim;
    string un_medida;
};

// ............ SENSOR E SETOR
// é a categoria do sensor (distancia, pressão...)
typedef struct categoria_sensor{
    string id;
    string nome;
    string descricao;
    struct categoria_sensor *proximo;    
} categoria_sensor_t;
// é o tipo do sensor HDR04...
typedef struct sensor
{
    string id;
    string nome;
    string id_categoria; //foreign key
    struct faixa_valores faixa;
    struct sensor *proximo;
} sensor_t;
// é o sensor em si
typedef struct sensor_un{
    string id;
    string id_sensor_tipo;  //foreign key
    string id_setor; // default -> estoque ID_ESTOQUE
    leitura_t leituras; 
    struct sensor_un *proximo;
} sensor_un_t;

typedef struct setor
{
    string id;
    string nome;
    string descricao;
    int qtd_sensores_instalados;
    struct setor *proximo;
} setor_t;

typedef struct listas{
    sensor_t *lista_sensores_tipos;
    sensor_un_t *lista_sensores_un;
    categoria_sensor_t *lista_categoria_sensores;
    setor_t *lista_setores;
} listas_t;

#endif