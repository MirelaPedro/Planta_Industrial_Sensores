#include "prototypes.h"

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