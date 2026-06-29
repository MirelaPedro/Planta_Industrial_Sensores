#ifndef _PROTOTYPES_H
#define _PROTOTYPES_H

#include "types.h"


// .................................... PROTÓTIPO DAS FUCOES ................................
// .................... MENUs
int menu_principal();
int menu_setores();
int menu_sensores();
int menu_relatorios();
int menu_pesquisa();
// menus secundarios
int menu_editar_setor();
int menu_editar_sensores();
int menu_editar_categoria();
int menu_editar_tipo();
int menu_editar_sensor_un();
int menu_editar_setor_sensores();
//relatorios
int menu_relatorio_setores();
int menu_relatorio_sensores();
int menu_relatorio_leituras();

// .................... CADASTROs
sensor_un_t *cadastro_sensor_un(listas_t listas);
sensor_t *cadastro_sensor(string nome, categoria_sensor_t *categoria_sensor); // verifica-se se o tipo de sensor já existe e se não existe, cria um novo
categoria_sensor_t *cadastro_categoria_sensor(string nome); // verifica-se se a categoria já existe e se não existe, cria uma nova
setor_t *cadastro_setor();
void cadastrar_sensor_ao_setor(string id_setor, string id_sensor, listas_t listas); // perguntar-se realmente deseja cadastrar
void cadastrar_leitura(string id_sensor, sensor_un_t *sensor);
leitura_t adicionar_leitura(int minimo, int maximo);
struct tm cadastrar_data_hora();

// .................... READs
//listar
void listar_setores(setor_t *lista_setores);
void listar_sensores(sensor_un_t *lista_sensores);
void listar_tipos_sensores(sensor_t *lista_tipos);
void listar_categorias_sensores(categoria_sensor_t *lista_categorias);
//mostrar
void mostrar_setor(setor_t *seto8r);
void mostrar_sensor(sensor_un_t *sensor);
void mostrar_tipo_sensor(sensor_t *tipo);
void mostrar_categoria_sensor(categoria_sensor_t *categoria);

void mostrar_leitura(leitura_t leitura, string un_medida);
void mostrar_data(struct tm date_time);
void mostrar_hora(struct tm date_time);
//cadastrados - sintese
void mostrar_categorias_cadastradas(categoria_sensor_t *lista_categorias);
void mostrar_tipos_sensores_cadastrados(sensor_t *lista_tipos);
void mostrar_sensores_cadastrados(sensor_un_t *lista_sensores);
void mostrar_setores_cadastrados(setor_t *lista_setores);

// .................... RELATORIOs
void relatorio_setores(listas_t listas);
void relatorio_sensores(listas_t listas);
void relatorio_leituras(listas_t listas);
// imprimir relatorios
void imprimir_relatorio_setor_geral(listas_t listas);
void imprimir_relatorio_setor_detalhado(listas_t listas);
void imprimir_relatorio_sensor_geral(listas_t listas);
void imprimir_relatorio_sensor_por_tipo(listas_t listas);
void imprimir_relatorio_sensor_por_setor(listas_t listas);
void imprimir_relatorio_leitura_geral(listas_t listas);
void imprimir_relatorio_leitura_setor(listas_t listas);
void imprimir_relatorio_leitura_sensor(listas_t listas);

// .................... UPDATEs
void editar_setor(string id_setor, setor_t *lista_setores);
void editar_sensor(string id_sensor, sensor_un_t *lista_sensores);
void editar_tipo(string id_tipo, sensor_t *lista_tipos);
void editar_categoria(string id_categoria, categoria_sensor_t *lista_categorias);

// .................... PESQUISAs
void pesquisar_por_tipo(string tipo, listas_t listas);
void pesquisar_sensores_setor(string id_setor, listas_t listas); //pesquisa todos os sensores de um setor
void pesquisar_descricao(string descricao, listas_t listas);

// .................... DELETEs
void deletar_setor(string id_setor, setor_t *lista_setores);
void deletar_sensor_geral(string id_sensor, listas_t listas);
void deletar_sensor_setor(string id_sensor, listas_t listas);
void deletar_categoria(string id_categoria, listas_t listas); // mudar todos os sensores que possuem esta categoria para 'undefined'
void deletar_tipo_sensor(string id_tipo, listas_t listas); // não permitir a mudança caso hava algum sensor com este nome cadastrado

// .................... FORMATACAO
void aviso(string msg);
void retirar_enter(string str);
void formatar_string_nome(string str);
void formatar_string_texto(string str);
void limpar_tela();
char *criar_id(char tipo); // st - setor/ss - sensor/ct - categoria/tp - tipo

// .................... VERIFICACAO
int verificar_sensor_no_setor(string id_sensor, string id_setor, listas_t listas);
char *verificar_sensor_todos_setores(string id_sensor, listas_t listas); // retorna '0' para estoque e o inicio de um vetor do id do setor se estiver em um setor
int confirmar(string pergunta); // retorna 1 para sim e 0 para não
int verificar_categoria_existente(string nome_categoria, categoria_sensor_t *lista_categorias);
int verificar_tipo_existente(string nome_tipo, sensor_t *listas_tipos);

// .................... ARQUIVOs

// .................... ALOCACAO DINAMICA

// .................... CALCULOs
// gerais
float media_quantidade(int *valores, int qtd);
float maior(float *valores, int qtd);
float menor(float *valores, int qtd);
float media_sensores_por_setor();

// relatorios de LEITURA
int qtd_leituras_cadastradas();
int qtd_leituras_cadastradas_setor(int id_setor);
int qtd_leituras_cadastradas_sensor_nome(string nome);

float media_leituras_tipos(string tipo);
//maiores e menores
float maior_leitura_geral();
float maior_leitura_setor(setor_t setor);
float maior_leitura_sensor_nome(string nome);
float menor_leitura_geral();
float menor_leitura_setor(setor_t setor);
float menor_leitura_sensor_nome(string nome);
float maior_leitura_sensor(leitura_t leitura);
float menor_leitura_sensor(leitura_t leitura);

//variacao
float variacao_leitura(leitura_t leitura);
float media_variacao(float *valores, int qtd);
float media_variacao_tipo(string tipo);
float maior_variacao_geral();
float menor_varicao_geral();
float maior_variacao_setor(setor_t setor);
float menor_variacao_setor(setor_t setor);
float maior_variacao_sensor_nome(string nome);
float menor_variacao_sensor_nome(string nome);
float variacao_total_setor(setor_t setor);
float variacao_total_sensor(string nome);
float media_leitura_sensor_nome(string nome);
float media_variacao_sensor_nome(string nome);

#endif