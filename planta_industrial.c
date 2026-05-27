#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define T_STRING 100
#define MAX_SENSORES 3
#define MAX_SETORES 10
#define MAX_SENSORES_ESTOQUE 20
#define FIM 0
#define CONTINUE -1

// DECLARANDO MAIS TIPOS PARA USAR
typedef char String[T_STRING];

// tipos simples ( HORA E DATA)
typedef struct date
{
    int dia;
    int mes;
    int ano;
} date_t;

typedef struct hora{
    int hora;
    int minuto;
    int segundo;
} horas_t;


//o tipo leitura_t já considera que serão duas leituras diárias
typedef struct leitura // posso importar uma biblioteca para fazer as datas e horas
{
    int modulo; // valor da leitura
    horas_t hora;
    date_t data;
}leitura_t[2];


struct faixa_valores{
    // valores de início de fim incluídos
    int inicio; 
    int fim;
    String un_medida;
};

// SENSOR E SETOR
typedef struct sensor
{
    String id;
    String nome;
    String tipo;
    struct faixa_valores faixa;
    leitura_t leitura_dia; // leitura do dia atual
} sensor_t;

typedef struct setor
{
    String id;
    String nome;
    String descricao;
    int qtd_sensores_instalados;
    int id_sensores_instalados[MAX_SENSORES];
} setor_t;

// VARIAVEIS GLOBAIS
sensor_t sensores[MAX_SENSORES*MAX_SETORES + MAX_SENSORES_ESTOQUE]; // o que determina a quantidade máxima de sensores ao todo é a quantidade de setores (agora 30)
setor_t setores[MAX_SETORES];
int qtd_sensores = 0, qtd_setores = 0;

// FUNCOES AUXILIARES - PROTOTIPOS

// MENUS
int menu_principal();
int menu_setores();
int menu_sensores();
int menu_relatorios();
int menu_pesquisa();

// CADASTROS
sensor_t cadastro_sensor();
setor_t cadastro_setor();

// READS
void listar_setores();
void listar_sensores();
void mostrar_setor(setor_t setor);
void mostrar_sensor(sensor_t sensor);
void mostrar_leitura(leitura_t leitura, String un_medida);
// relatórios
void imprimir_relatorio_setores();
void imprimir_relatorio_sensores();
void imprimir_relatorio_leituras();

// UPDATES
void editar_sensor(int id_sensor);
void editar_setor(int id_setor);

// DELETES
void deletar_sensor(int id_sensor);

// PESQUISA
void pesquisar_por_tipo();
void pesquisar_descricao();
void pesquisa_geral();

// FORMATAÇÃO
void aviso(String msg);
void retirar_enter(String str);
void formatar_string_nome(String str);
void formatar_string_texto(String str);

//          MAIN 
int main()
{
    int op;

    do{
        op = menu_principal();

        switch (op)
        {

        case 0: break; //sai direto do programa

        //  SETORES
        case 1:
            do{
                op = menu_setores();

                switch (op)
                {    
                case 0: break; //sai direto do programa

                //Cadastro
                case 1:
                    printf("-------------------------\n");
                    printf("|   CADASTRO DE SETOR   |\n");
                    printf("-------------------------\n\n");

                    setores[qtd_setores] = cadastro_setor();
                    qtd_setores++;
                    break;

                //Mostrar
                case 2:
                    printf("------------------------------\n");
                    printf("|   INFORMAÇÕES DOS SETORES   |\n");
                    printf("------------------------------\n\n");
                    listar_setores();
                    break;
                //Editar
                case 3:
                    printf("-------------------------\n");
                    printf("|   EDIÇÃO DE SETOR   |\n");
                    printf("-------------------------\n\n");
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

                    sensores[qtd_sensores] = cadastro_sensor();
                    qtd_sensores++;

                    break;
                
                //Mostrar
                case 2:
                    printf("--------------------------------\n");
                    printf("|   INFORMAÇÕES DOS SENSORES   |\n");
                    printf("--------------------------------\n\n");
                    listar_sensores();

                    break;
                //Deletar
                case 3:
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
                
                case 1:
                    /* code */
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
                op = menu_pesquisa();

                switch (op)
                {    
                case 0: break; //sai direto do programa
                
                case 1:
                    /* code */
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

// FUNCOES AUXILIARES - IMPLEMENTACAO
int menu_principal()
{
    int op;

    do{
        printf("---------------------------------\n");
        printf("|              MENU             |\n");
        printf("---------------------------------\n\n");
        printf("1. Menu de Setores\n");
        printf("2. Menu de Sensores\n");
        printf("3. Relatórios\n");
        printf("4. Pesquisar\n");
        printf("0. Fechar Programa\n");
        printf("opção: ");
        scanf("%i", &op);

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
        printf("1. Cadastrar Setor\n");
        printf("2. Mostrar setores\n");
        printf("3. Editar Setor\n");
        printf("0. Voltar ao Menu\n");
        printf("opção: ");
        scanf("%i", &op);

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
        printf("1. Cadastrar sensor\n");
        printf("2. Mostrar sensores\n");
        printf("3. Deletar sensor\n");
        printf("0. Voltar ao Menu\n");
        printf("opção: ");
        scanf("%i", &op);

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
        printf("1. Relatório dos Sentores\n");
        printf("2. Relatório dos Sensores\n");
        printf("3. Relatório de Leitura\n");
        printf("0. Voltar ao Menu\n");
        printf("opção: ");
        scanf("%i", &op);

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
        printf("1. Pesquisar Sensor por Tipo\n");
        printf("2. Pesquisar Setor por Descrição\n");
        printf("3. Pesquisa Geral\n");
        printf("0. Voltar ao Menu\n");
        printf("opção: ");
        scanf("%i", &op);

        if(op < 0 || op > 3) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 3);
    
    return op;
}

// CADASTROS
sensor_t cadastro_sensor()
{
    int id = qtd_sensores + 1;
    sensor_t sensor;

    printf("    CADASTRANDO SENSOR %i   \n", id);
    printf("Nome: ");
    fgets(sensor.nome, T_STRING, stdin);
    printf("Tipo: ");
    fgets(sensor.tipo, T_STRING, stdin);
    printf("Faixa de Valores\n");
    printf("Menor valor a ser registrado (início): ");
    scanf("%f", &sensor.faixa.inicio);
    printf("Maior valor a ser registrado (fim): ");
    scanf("%f", &sensor.faixa.fim);
    printf("Unidade de leitura: ");
    fgets(sensor.faixa.un_medida, T_STRING, stdin);

    return sensor;
}

setor_t cadastro_setor()
{
    int id = qtd_setores + 1;
    setor_t setor;

    printf("CADASTRANDO SETOR %i\n", id);
    printf("Nome: ");
    fgets(setor.nome, T_STRING, stdin);
    printf("Descrição: ");
    fgets(setor.descricao, T_STRING, stdin);

    return setor;
}

// READS
void listar_setores()
{
    printf("|        LISTA DE SETORES       |");
    for(int i = 0; i < qtd_setores; i++){
        mostrar_setor(setores[i]);
    }
}

void listar_sensores()
{
    printf("|        LISTA DE SENSORES       |");
    for(int i = 0; i < qtd_sensores; i++){
        mostrar_sensor(sensores[i]);
    }
}

void mostrar_setor(setor_t setor)
{
    printf("    %s\n", setor.nome);
    printf("%s\n", setor.descricao);
    printf("Sensores Instalados (%i)\n", setor.qtd_sensores_instalados);

    if(setor.qtd_sensores_instalados != 0){
        for(int i = 0; i < setor.qtd_sensores_instalados; i++){
            printf("Sensor: %s - id: %i\n", sensores[setor.id_sensores_instalados[i]].nome, setor.id_sensores_instalados[i]);
        }
    }
    
}

void mostrar_sensor(sensor_t sensor)
{
    printf("    %s\n", sensor.nome);
    printf("Id: %i\n", sensor.id);
    printf("Tipo: %s\n", sensor.tipo);
    printf("Leitura: %i - %i %s\n", sensor.faixa.inicio, sensor.faixa.fim, sensor.faixa.un_medida);
}

void mostrar_leitura(leitura_t leitura, String un_medida)
{
    for(int i = 0 ; i < 2; i++){
        printf("[");
        mostrar_data(leitura[i].data);
        mostrar_hora(leitura[i].hora);
        printf("] -> Leitura: %f %s\n", leitura[i].modulo, un_medida);
    }
}

void mostrar_data(date_t data)
{
    printf(" %i/%i/%i ", data.dia, data.mes, data.ano);
}

void mostrar_hora(horas_t hora)
{
    printf(" %i:%i:%i ", hora.hora, hora.minuto, hora.segundo);
}

// relatórios
void imprimir_relatorio_setores()
{
    printf("|       RELATÓRIO DE SETORES        |\n");
    printf("-------------------------------------");
    
    for(int i = 0; i < qtd_setores; i++){
        setor_t setor = setores[i];

        printf("--- SETOR %s ---\n", setor.nome);
        printf("ID: %i\n", setor.id);
        printf("Quantidade de sensores cadastrdos: \n");
        printf("Maior variação de leitura:  - \n");
        printf("Menor variação de leitura:  - \n");
        printf("Quantidade de tipo de sensores no setor: \n");
    }
}

void imprimir_relatorio_sensores()
{
    printf("|       RELATÓRIO DE SENSORES        |\n");
    printf("--------------------------------------");
    
    for(int i = 0; i < qtd_sensores; i++){
        sensor_t sensor = sensores[i];

        printf("--- SENSOR %s ---\n", sensor.nome);
        printf("ID: %i\n", sensor.id);
        printf("Tipo: %i\n", sensor.tipo);
        printf("Variação de Leitura do dia: \n");
    }
}

void imprimir_relatorio_leituras()
{
    printf("|       RELATÓRIO DE LEITURAS        |\n");
    printf("-------------------------------------");

    printf("Média de variação por tipo: \n");
    printf("Leituras por setor \n");

}

// UPDATES
void editar_sensor(int id_sensor)
{

}

void editar_setor(int id_setor)
{
    String opcao;
    do{
        printf("o que deseja editar (nome, descricao ou sensores)? ");
        fgets(opcao, T_STRING, stdin);
    } while (!strcmp(opcao, 'nome') || !strcmp(opcao, 'descricao') || !strcmp(opcao, 'sensores'));
    
    
}

// DELETES
void deletar_sensor(int id_sensor)
{
    for(int i = 0; i < (MAX_SENSORES * MAX_SETORES + MAX_SENSORES_ESTOQUE);i++){
        if (sensores[i].id == id_sensor){
            // sensores[i].id = id_sensor * (-1);
            break;
        }
    }
}

// PESQUISA
void pesquisar_por_tipo()
{

}

void pesquisar_descricao()
{

}

void pesquisa_geral()
{
    
}

// FORMATAÇÃO
// Formatações
void aviso(String msg)
{
    printf("\n\033[35m%s\033[0m\n");
    getchar();
}

void retirar_enter(String str)
{
    int tamanho = strlen(str);
    if(str[tamanho - 1] == '\n') str[tamanho - 1] = '\0';
    if(str[tamanho - 1] == ' ') str[tamanho - 1] = '\0';
}

void formatar_string_nome(String str)
{
    
}

void formatar_string_texto(String str)
{
    for(int i = 0; i < strlen(str); i ++){
        str[i] = tolower(str[i]);
    }
}


/*
Setores
Sensores
Menus para cada 
no máximo 3 sensores por setor

SENSOR
id
nome
tipo
valores (faixa)
unidade de medida
leituras -> 2 por dia, definir hora (como sera essa entrada de dados?)

SETOR
id
nome
Sensores instalados
descricao

Leitura de dados -> todos, por setor, por tipo 
Pesquisar -> por descricao, por nome, por id
Fazer um vetor que guarde tipos, assim quando for cadastrar um sensor, apenas pesquisar o tipo 
Posso coloccar categorias também, assim cada sensor se enquadra em um tipo que se enquandra em uma ccategoria.
Se quiser mudar a quantidade de leituras diarias, será necessário fazer de outra maneira
ao iniciar o programa se deve pedir a data atual

o sensor deve conter um  status que será atribuído se está em um setor ou no depósito
quando houver a criação de um setor, os seus sensores serão inicializados como null (0), pois não haverá nenhum sensor cadastrado naquele setor

deve haver a possibilidade de alterar as informações de cada setor ou sensor
os sensores poderão ser removido(seu id mudará para o respectivo número negativo), indicando que existia, porém foi excluído do sistema
o cadastro de sensores seguirá uma ordem, onde será cadastrado no último espaço vazio (padrão) e caso não exista mais espaços vazios,deve se verficar se não existem sensores "removidos", se existir, o sensor a ser cadastrado será alocado no primeirro sensor removido (será necessário uma mensagem de confirmação), senão, deve mostar uma mensagem de espaço cheio e pedir para remover um sensor
*/
/*
        RELATÓRIOS A SEREM GERADOS
    • Relatório de sensores (geral e por tipo);
    • Relatório de setores;
    • Relatório de leituras (por local e por todos os locais);
    • Relatório de variação de leitura (por setor e por sensor);
    • Relatório de médias de leitura por sensor considerando todos os setores.

        PESQUISA
    • Pesquisar sensor por tipo;
    • Pesquisar setor por descrição.

*/
