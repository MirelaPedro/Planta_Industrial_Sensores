#include <stdio.h>
#include <stdlib.h>
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
    float modulo; // valor da leitura
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
    int id;
    String nome;
    String tipo;
    struct faixa_valores faixa;
    leitura_t leitura_dia; // leitura do dia atual
} sensor_t;

typedef struct setor
{
    int id;
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
int menu_editar_setor();
int menu_editar_setor_sensores();
int menu_relatorio_setores();
int menu_relatorio_sensores();
int menu_relatorio_leituras();

// CADASTROS
sensor_t cadastro_sensor();
setor_t cadastro_setor();
void cadastrar_leitura(int id_sensor);
void cadastrar_sensor_ao_setor(int id_setor, int id_sensor);
struct leitura adicionar_leitura(int minimo, int maximo);

// READS
void listar_setores();
void listar_sensores();
void mostrar_setor(setor_t setor);
void mostrar_sensor(sensor_t sensor);
void mostrar_leitura(leitura_t leitura, String un_medida);
void mostrar_data(date_t data);
void mostrar_hora(horas_t hora);
void mostrar_sensores_cadastrados();
void mostrar_setores_cadastrados();
// relatórios
void relatorio_setores();
void relatorio_sensores();
void relatorio_leituras();
// imprimir relatorios
void imprimir_relatorio_setor_geral();
void imprimir_relatorio_setor_detalhado();
void imprimir_relatorio_sensor_geral();
void imprimir_relatorio_sensor_por_tipo();
void imprimir_relatorio_sensor_por_setor();
void imprimir_relatorio_leitura_geral();
void imprimir_relatorio_leitura_setor();
void imprimir_relatorio_leitura_sensor();

// UPDATES
void editar_sensor(int id_sensor);
void editar_setor(int id_setor);

// PESQUISA
void pesquisar_por_tipo(String tipo);
void pesquisar_sensor_setor(int id_setor);
void pesquisar_descricao(String descricao);

// FORMATAÇÃO
void aviso(String msg);
void retirar_enter(String str);
void formatar_string_nome(String str);
void formatar_string_texto(String str);
void limpar_tela();

// Verificação
int verificar_sensor_no_setor(int id_sensor, int id_setor);
int verificar_sensor_todos_setores(int id_sensor);
int verificar_sensor_no_estoque(int id_sensor);

//          MAIN 
int main()
{
    int op, id;

    do{
        limpar_tela();
        
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
                        printf("\n");
                        break;
                    //Editar
                    case 3:
                        printf("-------------------------\n");
                        printf("|   EDIÇÃO DE SETOR   |\n");
                        printf("-------------------------\n\n");
                        mostrar_setores_cadastrados();
                        printf("Id do setor que deseja editar: ");
                        scanf("%i", &id);
                        getchar();

                        editar_setor(id);

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

                //Mostrar
                case 3:
                    printf("-------------------------\n");
                    printf("|   ADICIONAR LEITURA   |\n");
                    printf("-------------------------\n\n");
                    mostrar_sensores_cadastrados();
                    printf("Id do sensor que deseja adiocionar a leitura: ");
                    scanf("%i", &id);

                    int verify = verificar_sensor_no_estoque(id);

                    if(verify == 1) cadastrar_leitura(id);

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
                        relatorio_setores();
                        break;

                    // Sensores
                    case 2:
                        relatorio_sensores();
                        break;
                    
                    // Leituras
                    case 3:
                        relatorio_leituras();
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
                String tipo, descricao;
                op = menu_pesquisa();

                switch (op)
                {    
                    case 0: break; //sai direto do programa
                    
                    // Tipo
                    case 1:
                        printf("Tipo: ");
                        fgets(tipo, T_STRING, stdin);
                        retirar_enter(tipo);

                        pesquisar_por_tipo(tipo);

                        break;

                    // Descricao
                    case 2:
                        printf("descricao: ");
                        fgets(descricao, T_STRING, stdin);
                        retirar_enter(descricao);

                        pesquisar_descricao(descricao);

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
        printf("1. Cadastrar Setor\n");
        printf("2. Mostrar setores\n");
        printf("3. Editar Setor\n");
        printf("0. Voltar ao Menu\n");
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
        printf("1. Cadastrar sensor\n");
        printf("2. Mostrar sensores\n");
        printf("3. Adicionar Leitura\n");
        printf("0. Voltar ao Menu\n");
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
        printf("1. Relatório dos Sentores\n");
        printf("2. Relatório dos Sensores\n");
        printf("3. Relatório de Leitura\n");
        printf("0. Voltar ao Menu\n");
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
        printf("1. Pesquisar Sensor por Tipo\n");
        printf("2. Pesquisar Setor por Descrição\n");
        printf("0. Voltar ao Menu\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        if(op < 0 || op > 2) aviso("OPÇÃO INVÁLIDA!");
        
    } while(op < 0 || op > 2);
    
    return op;
}

int menu_editar_setor()
{
    int op;

    do{
        printf("|   Editar Setor    |\n");
        printf("1.Nome\n");
        printf("2.Descrição\n");
        printf("3.Sensores\n");
        printf("0.Voltar\n");
        printf("op: ");
        scanf("%i", &op);
        getchar();

        printf("\n");

    } while (op < 0 || op > 3);
    
    return op;
}

int menu_editar_setor_sensores()
{
    int op;
    printf("-------------------------\n");
    printf("|   SENSORES DO SETOR   |\n");
    printf("-------------------------\n");
    printf("1. Adicionar sensor ao setor\n");
    printf("2. Adicinar leitura de um sensor so setor\n");
    printf("0.Voltar\n");
    scanf("%i", &op);
    getchar();
    printf("\n");

    return op;
}

int menu_relatorio_setores()
{
    int op;

    do{
        printf("----------------------------------------\n");
        printf("|       MENU RELATÓRIOS SETORES        |\n");
        printf("----------------------------------------\n\n");
        printf("1. Relatório Geral\n");
        printf("2. Relatório Detalhado\n");
        printf("0. Voltar ao Menu\n");
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
        printf("3. Relatório por Setor\n");
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

// CADASTROS
sensor_t cadastro_sensor()
{
    int id = qtd_sensores + 1;
    sensor_t sensor;

    sensor.id = id;

    printf("    CADASTRANDO SENSOR %i   \n", id);
    printf("Nome: ");
    fgets(sensor.nome, T_STRING, stdin);
    retirar_enter(sensor.nome);

    printf("Tipo: ");
    fgets(sensor.tipo, T_STRING, stdin);
    retirar_enter(sensor.tipo);

    printf("Faixa de Valores\n");
    printf("Menor valor a ser registrado (início): ");
    scanf("%i", &sensor.faixa.inicio);
    getchar();

    printf("Maior valor a ser registrado (fim): ");
    scanf("%i", &sensor.faixa.fim);
    getchar();

    printf("Unidade de leitura: ");
    fgets(sensor.faixa.un_medida, T_STRING, stdin);
    retirar_enter(sensor.faixa.un_medida);

    for (int i = 0; i < 2; i++)
    {
        sensor.leitura_dia[i].modulo = 0;

        sensor.leitura_dia[i].data.ano = 0;
        sensor.leitura_dia[i].data.mes = 0;
        sensor.leitura_dia[i].data.dia = 0;

        sensor.leitura_dia[i].hora.hora = 0;
        sensor.leitura_dia[i].hora.minuto = 0;
        sensor.leitura_dia[i].hora.segundo = 0;
    }
    
    return sensor;
}

setor_t cadastro_setor()
{
    int id = qtd_setores + 1;
    setor_t setor;

    setor.id = id;

    printf("CADASTRANDO SETOR %i\n", id);
    printf("Nome: ");
    fgets(setor.nome, T_STRING, stdin);
    retirar_enter(setor.nome);

    printf("Descrição: ");
    fgets(setor.descricao, T_STRING, stdin);
    retirar_enter(setor.descricao);

    // zerando os sensores no setor(pois não tem nenhum instalado ainda)
    setor.qtd_sensores_instalados = 0;

    // quando for mostrado os sensores nos setores será verificado a quantidade primeiro
    for (int i = 0; i < 3; i++){
        setor.id_sensores_instalados[i] = 0;
    }

    return setor;
}

void cadastrar_sensor_ao_setor(int id_setor, int id_sensor)
{
    // para verificar se o sensor já não foi cadastrado em nenhum setor
    int verify = verificar_sensor_todos_setores(id_sensor);

    printf("\nVerify: %i\n", verify);

    if(verify == 0){
        setor_t setor = setores[id_setor - 1];
        // verificando a quantidade de sensores instalados no setor
        if(setor.qtd_sensores_instalados == 3){
            char decisao;
            printf("Já há 3 sensores cadastrados neste setor!\n");
            printf("Deseja retirar um sensor e casdastrar outro no lugar (s/n)? ");
            scanf("%c", &decisao);
            getchar();

            if(decisao == 's'){
                int id_sensor_mudar;
                pesquisar_sensor_setor(id_setor);

                printf("Id do sensor que deseja trocar: ");
                scanf("%i", &id_sensor_mudar);

                for (int i = 0; i < 3; i ++){
                    if(setor.id_sensores_instalados[i] == id_sensor_mudar) setor.id_sensores_instalados[i] = id_sensor;
                }

                pesquisar_sensor_setor(id_setor);
            }
        } else{
            printf("[casdtrar_sensor_setor] -> Entrando certo\n");
            setor.id_sensores_instalados[setor.qtd_sensores_instalados] = id_sensor;
            setor.qtd_sensores_instalados +=1;

            // adicionando as alterações no setor
            setores[id_setor - 1] = setor;

            pesquisar_sensor_setor(id_setor);
        }
    } else {
        printf("Esse sensor já está cadastrado em um setor!\n");
        pesquisar_sensor_setor(verify);
    }
}

void cadastrar_leitura(int id_sensor)
{
    int op;
    struct  leitura leitura_atual;    

    do{
        printf("1 - para primeira leitura do dia\n");
        printf("2 - para segunda leitura do dia\n");
        printf("op: ");
        scanf("%i", &op);
    } while (op < 1 || op > 2);

    leitura_atual = adicionar_leitura(sensores[id_sensor - 1].faixa.inicio, sensores[id_sensor - 1].faixa.fim);

    sensores[id_sensor - 1].leitura_dia[op - 1] = leitura_atual;
    
}

struct leitura adicionar_leitura(int minimo, int maximo)
{
    struct leitura leitura_atual;
    
    do{
        printf("Mínimo: %i \tMáximo: %i\n", minimo, maximo);
        printf("Valor: ");
        scanf("%f", &leitura_atual.modulo);
    } while(leitura_atual.modulo < minimo || leitura_atual.modulo > maximo);

    printf("Data\n");
    printf("Dia: ");
    scanf("%i", &leitura_atual.data.dia);
    printf("Mês: ");
    scanf("%i", &leitura_atual.data.mes);
    printf("Ano: ");
    scanf("%i", &leitura_atual.data.ano);

    printf("Hora\n");
    printf("Hora: ");
    scanf("%i", &leitura_atual.hora.hora);
    printf("Minuto: ");
    scanf("%i", &leitura_atual.hora.minuto);
    printf("Segundo: ");
    scanf("%i", &leitura_atual.hora.segundo);

    return leitura_atual;
}

// READS
void listar_setores()
{
    printf("\n|        LISTA DE SETORES       |\n\n");
    for(int i = 0; i < qtd_setores; i++){
        mostrar_setor(setores[i]);
    }
}

void listar_sensores()
{
    printf("\n|        LISTA DE SENSORES       |\n\n");
    for(int i = 0; i < qtd_sensores; i++){
        mostrar_sensor(sensores[i]);
    }
}

void mostrar_setor(setor_t setor)
{
    printf("----- %s -----\n", setor.nome);
    printf("Id: %i\n", setor.id);
    printf("%s\n", setor.descricao);
    printf("Sensores Instalados: %i\n", setor.qtd_sensores_instalados);

    // mostrando os sensores instalados de acordo com a qtd instalada
    if(setor.qtd_sensores_instalados != 0){
        for(int i = 0; i < setor.qtd_sensores_instalados; i++){
            printf("Sensor: %s - id: %i\n", sensores[setor.id_sensores_instalados[i]].nome, setor.id_sensores_instalados[i]);
        }
    }
    
}

void mostrar_sensor(sensor_t sensor)
{
    printf("----- %s ----- \n", sensor.nome);
    printf("Id: %i\n", sensor.id);
    printf("Tipo: %s\n", sensor.tipo);
    printf("Faixa de Leitura: %i - %i %s\n", sensor.faixa.inicio, sensor.faixa.fim, sensor.faixa.un_medida);

    if(sensor.leitura_dia[0].data.ano != 0){
        mostrar_leitura(sensor.leitura_dia, sensor.faixa.un_medida);
        printf("\nnt.: caso todos os valores estejam zerados, significa que ainda não foi cadastrada uma leitura\n");  
    } 
}

void mostrar_leitura(leitura_t leitura, String un_medida)
{
    for(int i = 0 ; i < 2; i++){
        printf("[");
        mostrar_data(leitura[i].data);
        mostrar_hora(leitura[i].hora);
        printf("] -> Leitura: %2.f %s\n", leitura[i].modulo, un_medida);
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

void mostrar_sensores_cadastrados()
{
    for(int i = 0; i < qtd_sensores; i++){
        printf("Sensor: %s \tId: %i\n", sensores[i].nome, sensores[i].id);
    }
    printf("\n");
}

void mostrar_setores_cadastrados()
{
    for(int i = 0; i < qtd_setores; i++){
        printf("Setor: %s \tId: %i\n", setores[i].nome, setores[i].id);
    }
    printf("\n");
}

// relatórios
void relatorio_setores()
{
    int op;
    
    do {
        op = menu_relatorio_setores();

        switch (op)
        {
        //Geral
        case 1:
            imprimir_relatorio_setor_geral();
            break;
        
        //Detalhado
        case 2:
            imprimir_relatorio_setor_detalhado();
            break;
        
        default:
            break;
        }
    } while(op != 0);
    op = CONTINUE;
}

void relatorio_sensores()
{
    int op;
    
    do {
        op = menu_relatorio_sensores();

        switch (op)
        {
        //Geral
        case 1:
            imprimir_relatorio_sensor_geral();
            break;
        
        //por tipo
        case 2:
            imprimir_relatorio_sensor_por_tipo();
            break;
        
        //por setor
        case 3:
            imprimir_relatorio_sensor_por_setor();
            break;
        
        default:
            break;
        }
    } while(op != 0);
    op = CONTINUE;
}

void relatorio_leituras()
{
    int op;
    
    do {
        op = menu_relatorio_leituras();

        switch (op)
        {
        //Geral
        case 1:
            imprimir_relatorio_leitura_geral();
            break;
        
        //por setor
        case 2:
            imprimir_relatorio_leitura_setor();
            break;
        
        //por sensor
        case 3:
            imprimir_relatorio_leitura_sensor();
            break;
        
        default:
            break;
        }
    } while(op != 0);
    op = CONTINUE;
}

// imprimir Relatórios
void imprimir_relatorio_setor_geral()
{
    printf("--------------------------------------------\n");
    printf("|       RELATÓRIO GERAL DOS SETORES        |\n");
    printf("--------------------------------------------\n\n");

    printf("\nQuantidade de setores cadastrados........: \n");
    printf("Média de sensores por setor.................: \n\n");
    
    for(int i = 0; i < qtd_setores; i++){
        setor_t setor = setores[i];

        printf("--- SETOR %s ---\n", setor.nome);
        printf("ID.......................................: %i\n", setor.id);
        printf("Quantidade de sensores cadastrados.......: \n");
        printf("Maior variação de leitura................:  - \n");
        printf("Menor variação de leitura................:  - \n");
        printf("Quantidade de tipo de sensores no setor..: \n");
    }
}

void imprimir_relatorio_setor_detalhado()
{
    printf("------------------------------------------------\n");
    printf("|       RELATÓRIO DETALHADO DOS SETORES        |\n");
    printf("------------------------------------------------\n\n");

    printf("\nQuantidade de setores cadastrados........: \n");
    printf("Média de sensores por setor.................: \n\n");
    
    listar_setores();
}

void imprimir_relatorio_sensor_geral()
{
    printf("---------------------------------------------\n");
    printf("|       RELATÓRIO GERAL DOS SENSORES        |\n");
    printf("---------------------------------------------\n\n");

    printf("\nQuantidade de sensores cadastrados........: \n");
    printf("\nQuantidade de sensores em setor...........: \n");
    printf("\nQuantidade de sensores em estoque.........: \n");
    printf("Média de sensores por setor.................: \n\n");
    
    listar_sensores();
}

void imprimir_relatorio_sensor_por_tipo()
{
    printf("------------------------------------------------\n");
    printf("|       RELATÓRIO POR TIPO DOS SENSORES        |\n");
    printf("------------------------------------------------\n\n");

    printf("-------- TIPO \n");
    printf("\nQuantidade de sensores cadastrados........: \n");
    printf("\nQuantidade de sensores em setor...........: \n");
    printf("\nQuantidade de sensores em estoque.........: \n");
    printf("Média de sensores por setor.................: \n");
    printf("Média de leituras...........................: \n");
    printf("Média da variação de leitura................: \n\n");
    
    listar_sensores(); //mudar para tipo
}

void imprimir_relatorio_sensor_por_setor()
{
    printf("------------------------------------------------\n");
    printf("|       RELATÓRIO POR SETOR DOS SENSORES        |\n");
    printf("------------------------------------------------\n\n");

    printf("-------- SETOR \n");
    printf("\nQuantidade de sensores cadastrados........: \n");    
    listar_sensores(); //mudar para tipo
}

void imprimir_relatorio_leitura_geral()
{
    printf("---------------------------------------------\n");
    printf("|       RELATÓRIO GERAL DAS LEITURAS        |\n");
    printf("---------------------------------------------\n\n");

    printf("\nQuantidade de leituras cadastradas........: \n");
    printf("\nMaior leitura cadastrada..................: \n");
    printf("\nMenor leitura cadastrada..................: \n");
    printf("\nMaior variação de leitura cadastrada......: \n");
    printf("\nMenor variação de leitura cadastrada......: \n");
}

void imprimir_relatorio_leitura_setor()
{
    printf("-------------------------------------------------\n");
    printf("|       RELATÓRIO DAS LEITURAS POR SETOR        |\n");
    printf("-------------------------------------------------\n\n");

    printf("\nQuantidade de leituras cadastradas........: \n");
    printf("\nMaior leitura cadastrada..................: \n");
    printf("\nMenor leitura cadastrada..................: \n");
    printf("\nMaior variação de leitura cadastrada......: \n");
    printf("\nMenor variação de leitura cadastrada......: \n");

}

void imprimir_relatorio_leitura_sensor()
{
    printf("--------------------------------------------------------\n");
    printf("|       RELATÓRIO GERAL DAS LEITURAS POR SENSOR        |\n");
    printf("--------------------------------------------------------\n\n");

    printf("\nQuantidade de leituras cadastradas........: \n");
    printf("\nMaior leitura cadastrada..................: \n");
    printf("\nMenor leitura cadastrada..................: \n");
    printf("\nMaior variação de leitura cadastrada......: \n");
    printf("\nMenor variação de leitura cadastrada......: \n");

}

// UPDATES
void editar_sensor(int id_sensor)
{

}

void editar_setor(int id_setor)
{
    int op;

    do {
        printf("--------------\n");
        op = menu_editar_setor();

        printf("Op : %i\n", op);

        switch (op)
        {
            // Nome
            case 1:
                printf("Nome atual: %s\n", setores[id_setor - 1].nome);
                printf("Novo nome: ");
                fgets(setores[id_setor - 1].nome, T_STRING, stdin);
                retirar_enter(setores[id_setor - 1].nome);
            
                break;
            
            // Descrição
            case 2:
                printf("Descrição atual: %s\n", setores[id_setor - 1].descricao);
                printf("Novo descrição: ");
                fgets(setores[id_setor - 1].descricao, T_STRING, stdin);
                retirar_enter(setores[id_setor - 1].descricao);
            
                break;
            
            // Sensores
            case 3:
                do {
                    int id;

                    op = menu_editar_setor_sensores();
                    printf("op : %i\n", op);

                    switch (op)
                    {
                        // Adicionar sensor ao setor
                        case 1:
                            mostrar_sensores_cadastrados();
                            printf("Id do sensor que deseja cadastrar ao setor: ");
                            scanf("%i", &id);
                            cadastrar_sensor_ao_setor(id_setor, id);
                        
                            break;
                        
                        // Adicionar leitura de um sensor do setor
                        case 2:
                            if(setores[id_setor - 1].qtd_sensores_instalados == 0){
                                printf("Nenhum sensor cadastrado neste setor!\n");
                            } else{
                                pesquisar_sensor_setor(id_setor);
                        
                                printf("Id do sensor que deseja adicionar a leitura: ");
                                scanf("%i", &id);

                                cadastrar_leitura(id);
                            }                            

                            break;
                    default:
                        break;
                    }
                    printf("op : %i\n", op);
                } while(op != 0);
                break;
            
            default: break;
        }
    } while (op != FIM);

    op = CONTINUE;
}

// PESQUISA
void pesquisar_por_tipo(String tipo)
{
    for(int i = 0; i < qtd_sensores; i ++){
        if(!strcmp(sensores[i].tipo, tipo)) mostrar_sensor(sensores[i]);
    }
}

void pesquisar_sensor_setor(int id_setor)
{
    setor_t setor;
    setor = setores[id_setor - 1];

    if(setor.qtd_sensores_instalados != 0){
        printf("SENSORES CADASTRADOS NO SETOR \n");

        for (int i = 0; i <setor.qtd_sensores_instalados; i ++){
            mostrar_sensor(sensores[setor.id_sensores_instalados[i] - 1]);
        }
    } else{
        printf("Não há nenhum sensor cadastrado neste setor\n");
    }
}

void pesquisar_descricao(String descricao)
{
    for(int i = 0; i < qtd_setores; i ++){
        if(!strcmp(setores[i].descricao, descricao)) mostrar_setor(setores[i]);
    }
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

void limpar_tela()
{
    system("cls");
}

// Verificação
int verificar_sensor_no_setor(int id_sensor, int id_setor)
{
    setor_t setor = setores[id_setor - 1];
    
    if(setor.qtd_sensores_instalados != 0){
        for(int i = 0; i < setor.qtd_sensores_instalados; i++){
            if(setor.id_sensores_instalados[i] == id_sensor) return 1;
        }
    }

    return 0;
}

int verificar_sensor_todos_setores(int id_sensor)
{
    int verify;

    for(int i = 0; i < qtd_setores; i ++){
        verify = verificar_sensor_no_setor(id_sensor, setores[i].id); 
        if (verify == 1) return setores[i].id;
    }

    return verify;
}

int verificar_sensor_no_estoque(int id_sensor)
{
    int verify = verificar_sensor_todos_setores(id_sensor);

    if(verify == 0){
        printf("O sensor está no estoque!\n");
        return 0;
    }

    return 1;
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
