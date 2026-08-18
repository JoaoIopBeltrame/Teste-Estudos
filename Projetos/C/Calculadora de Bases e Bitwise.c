#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void menu_modo(void);
void troca_base(void);
void op_bitwise(void);
void opcao_acessar_modo(void (*hud)(void), unsigned int* opcao, int tamanho_array, const int opcao_menu[]);


int main(){
    const int opcoes_menu_principal[] = {0, 1, 2};
    const int opcoes_troca_base[] = {2, 8, 10, 16, 32};
    const int opcoes_bitwise[] = {1, 2, 3, 4, 5, 6};

    unsigned int opcao_principal = 0;
    unsigned int opcao_sub = 0;

    opcao_acessar_modo(menu_modo, &opcao_principal, sizeof(opcoes_menu_principal) / sizeof(opcoes_menu_principal[0]), opcoes_menu_principal);

    switch (opcao_principal) {
        case 1:
            opcao_acessar_modo(troca_base, &opcao_sub, sizeof(opcoes_troca_base) / sizeof(opcoes_troca_base[0]), opcoes_troca_base);
            printf("Voce selecionou a base: %u\n", opcao_sub);
            break;

        case 2:
            opcao_acessar_modo(op_bitwise, &opcao_sub, sizeof(opcoes_bitwise) / sizeof(opcoes_bitwise[0]), opcoes_bitwise);
            printf("Voce selecionou a operacao bitwise: %u\n", opcao_sub);
            break;

        case 0:
            printf("Saindo do programa...\n");
            break;

        default:
            printf("Opcao invalida.\n");
            break;
    }
    return 0;
}


////// colocar so uma func pra bases ddferenetes coloacar tpo um const"0123456789ABCDEF" que acessa os valores pelo indice ja que isso é um array
#include <stdio.h>
#include <string.h>

int main(){

    int opcao = 5;
    char buffer[100];
    int i = 0;
    while (opcao > 0){
        buffer[i] = (opcao % 2) + '0';
        opcao /= 2;
        i++;
    }
    buffer[i] = '\0';
    strrev(buffer);
    printf("%s", buffer);
    return 0;



}













void opcao_acessar_modo(void (*hud)(void), unsigned int* opcao, int tamanho_array, const int opcao_menu[]){
    char buffer[100];
    char buffer_limpo[100];
    int numero;
    bool numero_tem;
    bool fim = false;

    do {
        if (hud != NULL) {
            hud();
        }
        printf("Escolha uma opcao: ");

        numero_tem = false;
        unsigned int j = 0;

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';

            if (buffer[0] == '\0') {
                printf("\nEntrada vazia! Tente novamente.\n\n");
                continue;
            }

            for (unsigned int i = 0; buffer[i] != '\0'; i++) {
                if (isdigit((unsigned char)buffer[i])) {
                    buffer_limpo[j++] = buffer[i];
                }
            }
            buffer_limpo[j] = '\0';

            if (buffer_limpo[0] == '\0') {
                printf("\nNenhum digito valido encontrado! Tente novamente.\n\n");
                continue;
            }

            numero = (int)strtol(buffer_limpo, NULL, 10);

            for (int k = 0; k < tamanho_array; k++) {
                if (numero == opcao_menu[k]) {
                    numero_tem = true;
                    break; 
                }
            }

            if (numero_tem) {
                *opcao = (unsigned int)numero;
                fim = true;
            } else {
                printf("\nOpcao %d incorreta! Escolha uma opcao valida do menu.\n\n", numero);
            }
        }
    } while (!fim);
}

void menu_modo(void) {
    puts("=========================================\n"
         "             MENU PRINCIPAL              \n"
         "=========================================\n"
         "  [ 1 ]  Troca de Bases                  \n"
         "  [ 2 ]  Operacoes Bitwise               \n"
         "  [ 3 ]  Sair                            \n"
         "=========================================");
}

void troca_base(void) {
    puts("=========================================\n"
         "      BASES SUPORTADAS PARA ENTRADA      \n"
         "=========================================\n"
         "  [ 2  ]  Binario                        \n"
         "  [ 8  ]  Octal                          \n"
         "  [ 10 ]  Decimal                        \n"
         "  [ 16 ]  Hexadecimal                    \n"
         "  [ 32 ]  Base32                         \n"
         "=========================================");
}

void op_bitwise(void) {
    puts("=========================================\n"
         "           OPERACOES BITWISE             \n"
         "=========================================\n"
         "  [ 1 ]  AND (&)                         \n"
         "  [ 2 ]  OR (|)                          \n"
         "  [ 3 ]  XOR (^)                         \n"
         "  [ 4 ]  NOT (~)                         \n"
         "  [ 5 ]  Shift Left (<<)                 \n"
         "  [ 6 ]  Shift Right (>>)                \n"
         "=========================================");
}
