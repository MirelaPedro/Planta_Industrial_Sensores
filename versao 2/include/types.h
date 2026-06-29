#ifndef _TYPES_H_
#define _TYPES_H_

#include <time.h>

#define T_STRING 100

typedef char string[T_STRING];

typedef struct leitura
{
    int id;  // primary key
    float modulo; // valor da leitura
    struct tm date_time;
    int id_sensor_un; // foreign key
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
    int id;
    string nome;
    string descricao;
    struct categoria_sensor *proximo;
    sensor_t *lista_sensores; // lista de sensores que pertencem a essa categoria    
} categoria_sensor_t;

// é o tipo do sensor HDR04...
typedef struct sensor
{
    int id;
    string nome;
    int id_categoria; //foreign key
    struct faixa_valores faixa;
    struct sensor *proximo;
    sensor_un_t *lista_sensores_un; // lista de sensores que pertencem a esse tipo
} sensor_t;

// é o sensor em si
typedef struct sensor_un{
    int id;
    int id_sensor_tipo;  //foreign key
    int id_setor; // default -> estoque ID_ESTOQUE
    leitura_t *leituras; // leituras do sensor
    struct sensor_un *proximo; // unidades específicas do sensor
} sensor_un_t;

typedef struct setor
{
    int id;
    string nome;
    string descricao;
    int qtd_sensores_instalados;
    sensor_un_t *lista_sensores_un; // sensores instalados nesse setor
    struct setor *proximo;
} setor_t;

typedef struct listas{
    sensor_t *lista_sensores_tipos;
    sensor_un_t *lista_sensores_un;
    categoria_sensor_t *lista_categoria_sensores;
    setor_t *lista_setores;
} listas_t;

#endif