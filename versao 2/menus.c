#include "prototypes.h"

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

