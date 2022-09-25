#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *pBuffer;
int n_pessoas = 0;
int tamanho = 0;
int tamanho_inicial = (sizeof(char)*10 + sizeof(int) + sizeof(int));

void leitura();
void apaga();
void escrita();

void main(){
    int opcao;
    do{
    printf("\tQual operacao desejas fazer?\n");
    printf("\t\t-1. Inserir pessoa\n");
    printf("\t\t-2. Apagar pessoa\n");
    printf("\t\t-3. Ver pessoas\n");
    printf("\t\t-4. Sair\n");
    scanf("%i",&opcao);
    switch(opcao){
        case 1:
            leitura();
        break;
        case 2:
            if(tamanho == 0){
                printf("\n\n\t\t\t########  NAO TEM NINGUEM NA AGENDA!!! ########\n\n\n");
                break;
            }
            apaga();
        break;
        case 3:
            escrita();
        break;
        case 4:
            return;
        break;
        default:
            printf("digite novamente: \n");
            break;
    }
}while(opcao != 4);
}
void leitura(){

    tamanho += tamanho_inicial;
    pBuffer = realloc(pBuffer,(tamanho));

    printf("nome: ");
    scanf("%s", (char*)(pBuffer + n_pessoas*tamanho_inicial));
    printf("idade: ");
    scanf("%i", (int*)(pBuffer + n_pessoas*tamanho_inicial + (sizeof(char)*10)));
    printf("telefone: ");
    scanf("%i", (int*)(pBuffer + n_pessoas*tamanho_inicial + (sizeof(char)*10) + (sizeof(int))));

    n_pessoas++;
}
void apaga(){
    
    char pessoa_apagada [10]; 
    printf("Qual pessoa desejas apagar?  ");
    scanf("%s", pessoa_apagada);

    int y = 0;
    int n = 0;
    int sai_do_loop;
    sai_do_loop = 0;
    
    while((pessoa_apagada[y]!='\0')&&(*((char*)pBuffer+y+n*tamanho_inicial)!='\0')&&(sai_do_loop == 0)){
        if(pessoa_apagada[y] == *((char*)pBuffer+y+n*tamanho_inicial)){
            y++;
        }
        else{
            y=0;
            if(n<n_pessoas){
                n++;
            }
            else{
                sai_do_loop = 1;
            }                
        }
    }
    if(pessoa_apagada[y]==*((char*)pBuffer+y+n*tamanho_inicial)){
        for(int x=n;x<n_pessoas;x++){
            for(int g=0;g<10;g++){
                *((char*)pBuffer + x*tamanho_inicial + g*sizeof(char)) = *((char*)(pBuffer + (x+1)*tamanho_inicial + g*sizeof(char)));
            }            
            *((int*)(pBuffer + x*tamanho_inicial+ (sizeof(char)*10))) = *((int*)(pBuffer + (x+1)*tamanho_inicial + (sizeof(char)*10)));
            *((int*)(pBuffer + x*tamanho_inicial + (sizeof(char)*10) + sizeof(int))) = *((int*)(pBuffer + (x+1)*tamanho_inicial + (sizeof(char)*10) + sizeof(int)));
        }
        n_pessoas--;
        tamanho -= tamanho_inicial;
        pBuffer = realloc(pBuffer, tamanho);
        printf("\n\n\t\t\t########  PESSOA APAGADA!!! ########\n\n\n");
    }
    else{
        printf("\n\n\t\t\t########  PESSOA NAO ENCONTRADA!!! ########\n\n\n");
    } 
    
}
void escrita(){
    for(int x=0; x < n_pessoas; x++){
        printf("\t\t%s\n", (char*)(pBuffer + x * tamanho_inicial));
        printf("Idade: %i\n", *((int*)(pBuffer + x * tamanho_inicial + (sizeof(char)*10))));
        printf("Telefone: %i\n", *((int*) (pBuffer + x * tamanho_inicial + (sizeof(char)*10)+sizeof(int))));
        printf("-------------------------------------------\n");
    }
}
