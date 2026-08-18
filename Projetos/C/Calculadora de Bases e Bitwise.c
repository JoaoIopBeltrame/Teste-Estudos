#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h>
#include <limits.h>


// Protótipos das funções
void troca_base(void);
void op_bitwise(void);
void menu_modo(void);
unsigned long long int ler_e_limpar_input(int base_ou_op);
void transforma_em_binario(unsigned long long int numero);


int main(void) {
    int op;
    int base_ou_op;

    while(1) {
        menu_modo();
        printf("Escolha a opcao: ");
        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n');
            continue;
        }
        
        switch(op) {
            case 1:
                troca_base();
                printf("Digite a base desejada\n>> ");
                scanf("%d", &base_ou_op);

                transforma_em_binario(ler_e_limpar_input(base_ou_op));
                break; 
                
            case 2:
                op_bitwise();
                printf("Digite a operacao desejada: ");
                scanf("%d", &base_ou_op);
                
                transforma_em_binario(ler_e_limpar_input(base_ou_op));
                break; 

            case 0:
                printf("Encerrando sistema\n");
                return 0; 
                
            default:
                printf("Digite uma opcao valida!\n\n");
                break; 
        }
    }
}

void menu_modo(void) {
    printf("=========================================\n");
    printf("            MENU PRINCIPAL               \n");
    printf("=========================================\n");
    printf("  [ 1 ]  Troca de Bases                  \n");
    printf("  [ 2 ]  Operacoes Bitwise               \n");
    printf("  [ 0 ]  Sair                            \n");
    printf("=========================================\n");
}

void troca_base(void) {
    printf("=========================================\n");
    printf("      BASES SUPORTADAS PARA ENTRADA      \n");
    printf("=========================================\n");
    printf("  [ 2  ]  Binario                        \n");
    printf("  [ 8  ]  Octal                          \n");
    printf("  [ 10 ]  Decimal                        \n");
    printf("  [ 16 ]  Hexadecimal                    \n");
    printf("  [ 32 ]  Base32                         \n");
    printf("=========================================\n");
}

void op_bitwise(void) {
    printf("=========================================\n");
    printf("           OPERACOES BITWISE             \n");
    printf("=========================================\n");
    printf("  [ 1 ]  AND (&)                         \n");
    printf("  [ 2 ]  OR (|)                          \n");
    printf("  [ 3 ]  XOR (^)                         \n");
    printf("  [ 4 ]  NOT (~)                         \n");
    printf("  [ 5 ]  Shift Left (<<)                 \n");
    printf("  [ 6 ]  Shift Right (>>)                \n");
    printf("=========================================\n");
}

unsigned long long int ler_e_limpar_input(int base_ou_op) {
    char buffer[250];
    printf("Digite o valor/numero: ");
    if(fgets(buffer, sizeof(buffer), stdin) != NULL){

        
        int i = 0, j = 0;
        
        while(buffer[i] != '\0') { 
        if(isdigit((unsigned char)buffer[i])) { 
            buffer[j++] = buffer[i]; 
        }
        i++;
    }
    buffer[j] = '\0';
    
    unsigned long long int resultado = strtoull(buffer, NULL, 10);
    printf("Valor digitado: %llu\n", resultado);
    
    return resultado;
    }
    else{
        printf("Digite uma opcao valida\n");
        return 1; 
    }
}

void transforma_em_binario(unsigned long long int numero) {
    printf("[Valor em Binario]: ");

    if (numero == 0) {
        printf("0\n\n");
        return;
    }

    int iniciou = 0;
    int total_bits = sizeof(numero) * CHAR_BIT;

    for (int bit = total_bits - 1; bit >= 0; bit--) {
        int val = (numero >> bit) & 1;

        if (val == 1) {
            iniciou = 1;
        }

        if (iniciou) {
            putchar(val + '0');
        }
    }
    printf("\n\n");
}
