#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "./include/prototypes.h"
#include "./include/types.h"

#define T_STRING 100
#define FIM 0
#define CONTINUE -1
#define ANO_INICIAL 1900
#define ID_ESTOQUE {'e','s','t','0','\0'}

// .................................... MAIN ................................
int main()
{
    int op;
    int id;
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

