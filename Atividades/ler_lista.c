#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100
#define TAM_STRUCT 50

typedef struct dados{
    char nome[TAM];
    int dia,mes,ano;
}dado;

int main(void){
    dado pessoas[TAM_STRUCT];
    int i=0,f=0;
    char aux1[TAM],aux2[TAM];
    FILE *arq=NULL;
    
    arq=fopen("lista.txt","r");
    fscanf(arq,"%s %s",aux1,aux2);
    while(!feof(arq)){
        fscanf(arq,"%s %d / %d / %d",pessoas[i].nome,&pessoas[i].dia,&pessoas[i].mes,&pessoas[i].ano),i++;
    }
    while(f<i) printf("%s %d / %d / %d\n",pessoas[f].nome,pessoas[f].dia,pessoas[f].mes,pessoas[f].ano),f++;
    
    velha(pessoas,i-1);

    fclose(arq);
    return 0;
}

int velha(dado pessoa[TAM_STRUCT],int cont){
    char velho[TAM],novo[TAM];

    for(int i=0;i<cont;i++){
        for(int f=1;f<=cont;f++){
            if(pessoa[i].ano>pessoa[f].ano)
            {
                strcpy(velho,pessoa[i].nome);
            }
            else if(pessoa[i].ano==pessoa[f].ano)
            {
                if(pessoa[i].mes>pessoa[f].mes)
                {
                    strcpy(velho,pessoa[i].nome);
                }
                else if(pessoa[i].mes==pessoa[f].mes)
                {
                    if(pessoa[i].dia>pessoa[f].dia)
                    {
                        strcpy(velho,pessoa[i].nome);
                    }
                }
            }
            else strcpy(novo,pessoa[f].nome);
        }
    }
    printf("Velho: %s\nNovo: %s\n",velho,novo);
}
