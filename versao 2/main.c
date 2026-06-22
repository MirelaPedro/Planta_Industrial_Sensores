#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define T_STRING 100
#define FIM 0
#define CONTINUE -1
#define ANO_INICIAL 1900
#define ID_ESTOQUE {'e','s','t','0','\0'}


// .................................... ESTRUTURA DE DADOS ................................
//
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
    setor_t *lista_setores
} listas_t;

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

// .................................... MAIN ................................
int main()
{
    int op;
    string id;
    // criando todas as listas e aterrando todos os ponteiros
    listas_t listas;
    listas.lista_categoria_sensores = NULL;
    listas.lista_sensores_tipos = NULL;
    listas.lista_sensores_un = NULL;
    listas.lista_setores = NULL;

    do{
        limpar_tela();
        op = menu_principal();

        switch (op)
        {
        case 0: break; //sai direto do programa
        //  ......................... SETORES
        case 1:
            do{
                op = menu_setores();
                switch (op)
                {    
                    case 0: break;
                    //Cadastro
                    case 1:
                        printf("-------------------------\n");
                        printf("|   CADASTRO DE SETOR   |\n");
                        printf("-------------------------\n\n");

                        //setores[qtd_setores] = cadastro_setor();
                        //qtd_setores++;
                        break;

                    //Mostrar
                    case 2:
                        printf("------------------------------\n");
                        printf("|   INFORMAÇÕES DOS SETORES   |\n");
                        printf("------------------------------\n\n");
                        listar_setores(listas.lista_setores);
                        printf("\n");
                        break;
                    //Editar
                    case 3:
                        printf("-------------------------\n");
                        printf("|   EDIÇÃO DE SETOR   |\n");
                        printf("-------------------------\n\n");
                        //mostrar_setores_cadastrados();
                        printf("Id do setor que deseja editar: ");
                        scanf("%i", &id);
                        getchar();

                        //editar_setor(id);

                        break;
                    default:
                        break;
                }

            } while(op != FIM);
            op = CONTINUE; // recebe um valor diferente de zero para continuar dentro do programa
            break;

        //  SENSORES
        case 2:
            do{
                op = menu_sensores();

                switch (op)
                {    
                case 0: break; //sai direto do programa
                
                //Cadastro
                case 1:
                    printf("-------------------------\n");
                    printf("|   CADASTRO DE SENSOR   |\n");
                    printf("-------------------------\n\n");

                    //sensores[qtd_sensores] = cadastro_sensor();
                    //qtd_sensores++;

                    break;
                
                //Mostrar
                case 2:
                    printf("--------------------------------\n");
                    printf("|   INFORMAÇÕES DOS SENSORES   |\n");
                    printf("--------------------------------\n\n");
                    //listar_sensores();

                    break;

                //Mostrar
                case 3:
                    printf("-------------------------\n");
                    printf("|   ADICIONAR LEITURA   |\n");
                    printf("-------------------------\n\n");
                    //mostrar_sensores_cadastrados();
                    printf("Id do sensor que deseja adiocionar a leitura: ");
                    scanf("%i", &id);

                    int verify = verificar_sensor_no_estoque(id);

                    //if(verify == 1) cadastrar_leitura(id);

                    break;

                default:
                    break;
                }

            } while(op != FIM);
            op = CONTINUE; // recebe um valor diferente de zero para continuar dentro do programa
            break;

        //  RELATÓRIOS
        case 3:
            do{
                op = menu_relatorios();

                switch (op)
                {    
                    case 0: break; //sai direto do programa
                    
                    // Setores
                    case 1:
                        //relatorio_setores();
                        break;

                    // Sensores
                    case 2:
                        //relatorio_sensores();
                        break;
                    
                    // Leituras
                    case 3:
                        //relatorio_leituras();
                        break;
                    
                    default:
                        break;
                }

            } while(op != FIM);
            op = CONTINUE; // recebe um valor diferente de zero para continuar dentro do programa
            break;

        //  PESQUISA
        case 4:
            do{
                string tipo, descricao;
                op = menu_pesquisa();

                switch (op)
                {    
                    case 0: break; //sai direto do programa
                    
                    // Tipo
                    case 1:
                        printf("Tipo: ");
                        fgets(tipo, T_STRING, stdin);
                        retirar_enter(tipo);

                        //pesquisar_por_tipo(tipo);

                        break;

                    // Descricao
                    case 2:
                        printf("descricao: ");
                        fgets(descricao, T_STRING, stdin);
                        retirar_enter(descricao);

                        //pesquisar_descricao(descricao);

                        break;
                    
                    default:
                        break;
                }

            } while(op != FIM);
            op = CONTINUE; // recebe um valor diferente de zero para continuar dentro do programa
            break;

        default: // se cair aqui tem algo errado
            break;
        }

    } while(op != FIM);

    return 0;
}

// .................................... IMPLEMENTAÇÃO DAS FUCOES ................................
// .................... MENUs
int menu_principal()
{
    int op;

    do{
        printf("--------------------------------------\n");
        printf("|                 MENU               |\n");
        printf("--------------------------------------\n\n");
        printf("1.Menu de Setores\n");
        printf("2.Menu de Sensores\n");
        printf("3.Relatórios\n");
        printf("4.Pesquisar\n");
        printf("0.Fechar Programa\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        if(op < 0 || op > 4) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 4);
    
    return op;
}

int menu_setores()
{
    int op;

    do{
        printf("-----------------------------\n");
        printf("|       MENU SETORES        |\n");
        printf("-----------------------------\n\n");
        printf("1.Cadastrar Setor\n");
        printf("2.Mostrar setores\n");
        printf("3.Editar Setor\n");
        printf("0.Voltar ao Menu\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        if(op < 0 || op > 3) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 3);
    
    return op;
}

int menu_sensores()
{
    int op;

    do{
        printf("------------------------------\n");
        printf("|       MENU SENSORES        |\n");
        printf("------------------------------\n\n");
        printf("1.Cadastrar sensor\n");
        printf("2.Mostrar sensores\n");
        printf("3.Adicionar Leitura\n");
        printf("0.Voltar ao Menu\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        if(op < 0 || op > 3) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 3);
    
    return op;
}

int menu_relatorios()
{
    int op;

    do{
        printf("--------------------------------\n");
        printf("|       MENU RELATÓRIOS        |\n");
        printf("--------------------------------\n\n");
        printf("1.Relatórios dos Sentores\n");
        printf("2.Relatórios dos Sensores\n");
        printf("3.Relatórios de Leitura\n");
        printf("0.Voltar ao Menu\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        if(op < 0 || op > 3) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 3);
    
    return op;
}

int menu_pesquisa()
{
    int op;

    do{
        printf("------------------------------\n");
        printf("|       MENU PESQUISA        |\n");
        printf("------------------------------\n\n");
        printf("1.Pesquisar Sensor por Tipo\n");
        printf("2.Pesquisar Setor por Descrição\n");
        printf("0.Voltar ao Menu\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        if(op < 0 || op > 2) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 2);
    
    return op;
}

// menus secundários
int menu_editar_setor()
{
    int op;

    do{
        printf("-------------------------\n");
        printf("|      Editar Setor     |\n");
        printf("-------------------------\n\n");
        printf("1.Editar nome\n");
        printf("2.Editar descrição\n");
        printf("3.Editar sensores do setor\n");
        printf("0.Voltar\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        printf("\n");

    } while (op < 0 || op > 3);
    
    return op;
}

int menu_editar_sensor()
{
    int op;

    do{
        printf("-------------------------\n");
        printf("|      Editar Sensor     |\n");
        printf("-------------------------\n\n");
        printf("1.Editar categorias\n");
        printf("2.Editar tipos de sensores\n");
        printf("3.Editar sensor específico\n");
        printf("0.Voltar\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        printf("\n");

    } while (op < 0 || op > 3);
    
    return op;

}

int menu_editar_categoria()
{
    int op;
    do {
        printf("------------------------------\n");
        printf("|   CATEGORIAS DE SENSORES   |\n");
        printf("------------------------------\n");
        printf("1.Alterar nome\n");
        printf("2.Alterar descrição\n");
        printf("0.Voltar\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();
        printf("\n");    
    } while (op < 0 || op > 2);

    return op;
}

int menu_editar_tipo()
{
    int op;
    do {
        printf("-------------------------\n");
        printf("|   TIPOS DE SENSORES   |\n");
        printf("-------------------------\n");
        printf("1.Alterar nome\n");
        printf("2.Alterar faixa de valores\n");
        printf("0.Voltar\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();
        printf("\n");    
    } while (op < 0 || op > 2);

    return op;
}

int menu_editar_sensor_un()
{
    int op;
    do {
        printf("-------------------------\n");
        printf("|   UNIDADE DE SENSOR   |\n");
        printf("-------------------------\n");
        printf("1.Alterar tipo\n");
        printf("2.Alterar leitura\n");
        printf("0.Voltar\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();
        printf("\n");    
    } while (op < 0 || op > 2);

    return op;

}

int menu_editar_setor_sensores()
{
    int op;
    do {
        printf("-------------------------\n");
        printf("|   SENSORES DO SETOR   |\n");
        printf("-------------------------\n");
        printf("1.Adicionar sensor ao setor\n");
        printf("2.Adicinar leitura de um sensor do setor\n");
        printf("0.Voltar\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();
        printf("\n");    
    } while (op < 0 || op > 2);

    return op;
}

int menu_relatorio_setores()
{
    int op;

    do{
        printf("----------------------------------------\n");
        printf("|       MENU RELATÓRIOS SETORES        |\n");
        printf("----------------------------------------\n\n");
        printf("1.Relatório Geral\n");
        printf("2.Relatório Detalhado\n");
        printf("0.Voltar ao Menu\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        if(op < 0 || op > 2) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 3);
    
    return op;
}

int menu_relatorio_sensores()
{
    int op;

    do{
        printf("-----------------------------------------\n");
        printf("|       MENU RELATÓRIOS SENSORES        |\n");
        printf("-----------------------------------------\n\n");
        printf("1. Relatório Geral\n");
        printf("2. Relatório por Tipo\n");
        printf("0. Voltar ao Menu\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        if(op < 0 || op > 3) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 3);
    
    return op;
}

int menu_relatorio_leituras()
{
    int op;

    do{
        printf("-----------------------------------------\n");
        printf("|       MENU RELATÓRIOS LEITURAS        |\n");
        printf("-----------------------------------------\n\n");
        printf("1. Relatório Geral\n");
        printf("2. Relatório por Setor\n");
        printf("3. Relatório por Sensor\n");
        printf("0. Voltar ao Menu\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        if(op < 0 || op > 3) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 3);
    
    return op;
}

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

// .................... READs
//listar
void listar_setores(setor_t *lista_setores)
{

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


//mostrar
void mostrar_setor(setor_t *setor)
{

}

void mostrar_sensor(sensor_un_t *sensor)
{

}

void mostrar_tipo_sensor(sensor_t *tipo)
{

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

// .................... UPDATEs
void editar_setor(string id_setor, setor_t *lista_setores)
{

}

void editar_sensor(string id_sensor, sensor_un_t *lista_sensores)
{

}

void editar_tipo(string id_tipo, sensor_t *lista_tipos)
{

}

void editar_categoria(string id_categoria, categoria_sensor_t *lista_categorias)
{

}

// .................... PESQUISAs
void pesquisar_por_tipo(string tipo, listas_t listas)
{

}

void pesquisar_sensores_setor(string id_setor, listas_t listas)
{

} 

void pesquisar_descricao(string descricao, listas_t listas)
{

}

// .................... DELETEs
void deletar_setor(string id_setor, setor_t *lista_setores)
{

}

void deletar_sensor_geral(string id_sensor, listas_t listas)
{

}

void deletar_sensor_setor(string id_sensor, listas_t listas)
{

}

void deletar_categoria(string id_categoria, listas_t listas) // mudar todos os sensores que possuem esta categoria para 'undefined'
{

}

void deletar_tipo_sensor(string id_tipo, listas_t listas) // não permitir a mudança caso hava algum sensor com este nome cadastrado
{

}

// .................... FORMATACAO
void aviso(string msg)
{
    printf("\n\033[35m%s\033[0m\n", msg);
    getchar();
}

void retirar_enter(string str)
{
    int tamanho = strlen(str);
    if(str[tamanho - 1] == '\n') str[tamanho - 1] = '\0';
    if(str[tamanho - 1] == ' ') str[tamanho - 1] = '\0';
}

void formatar_string_texto(string str)
{
    for(int i = 0; i < strlen(str); i ++){
        str[i] = tolower(str[i]);
    }
}

void limpar_tela()
{
    system("clear");
}

void formatar_string_nome(string str)
{

}

char *criar_id(char tipo)
{

}

// .................... VERIFICACAO
int verificar_sensor_no_setor(string id_sensor, string id_setor, listas_t listas)
{

}

char *verificar_sensor_todos_setores(string id_sensor, listas_t listas) // retorna '0' para estoque e o inicio de um vetor do id do setor se estiver em um setor
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

