#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void menu_modo(void);
void troca_base(void);
void op_bitwise(void);

void acessarMenuFunc(void (*menu)(void), unsigned int tamanho_sizeof, const unsigned int opcaoDentroIgual[], unsigned int* opcao);

int main(){

    const unsigned int menu1[] = {1, 2, 3};
    const unsigned int menu2_3[] = {1, 2, 3, 4, 5, 6};

    unsigned int opcao1 = 0;
    unsigned int opcao2 = 0;
    
    do{
        acessarMenuFunc(menu_modo, sizeof(menu1)/sizeof(menu1[0]), menu1, &opcao1);
        switch(opcao1){
            case 1:
                puts("Opcao 1");
                acessarMenuFunc(troca_base, sizeof(menu2_3)/ sizeof(menu2_3[0]), menu2_3, &opcao2);
                printf("DEUCERTRO\n");
                break;
            case 2:
                puts("Opcao 2");
                acessarMenuFunc(op_bitwise, sizeof(menu2_3)/ sizeof(menu2_3[0]), menu2_3, &opcao2);
                printf("DEUCERTRO\n");
                break;
            case 3:
                puts("Opcao 3");
                break;
            default:
                puts("Numero do mal\n");
                continue;
        }

    }while(1);




    return 0;
}


void acessarMenuFunc(void (*menu)(void), unsigned int tamanho_sizeof, const unsigned int opcaoDentroIgual[], unsigned int* opcao){
    char buffer[100];
    char buffer2[10];
    char *endptr = NULL;
    int i = 0, j = 0;
    do{
        if(menu == NULL) continue;
        menu();
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        buffer[strcspn(buffer, "\n")] = '\0';
        if(buffer[0] == '\0') continue;
        
        for(int j = 0; j < tamanho_sizeof; j++){
            for(int i = 0; buffer[i] != '\0'; i++){
                if(isdigit(buffer[i]) && (buffer[i] - '0') == opcaoDentroIgual[j]){
                    buffer2[0] = buffer[i];
                    break;
                }
            }
        }
        buffer2[1] = '\0';
        
        long valor = strtol(buffer2, &endptr, 10);
        *opcao = (int)valor;
        break;

    }while(1);
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
         "  [ 1 ]  Binario                        \n"
         "  [ 2 ]  Octal                          \n"
         "  [ 3 ]  Decimal                        \n"
         "  [ 4 ]  Hexadecimal                    \n"
         "  [ 5 ]  Base32                         \n"
         "  [ 6 ]  Criar Base                     \n"
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
