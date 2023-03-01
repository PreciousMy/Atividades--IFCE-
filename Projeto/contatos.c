#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#define TAM_LETRAS 100
#define TAM_REG 20
#define TAM_TELE 20
#define TAM_LER_ARQ 300
#define TAM_CONSULTA 100

enum endereco{AV,AL,R,TR,ROD,PR};
enum telefone{CELULAR,COMERCIAL,FIXO,PESSOAL,FAX};
enum redeSocial{INSTAGRAM,FACEBOOK,LINKEDIN,OUTROS};

typedef struct contato{
    char nome[TAM_LETRAS];
    enum endereco eEnde;
    char endereco[TAM_LETRAS];
    int numCasa;
    enum telefone eTele;
    char numTele[TAM_TELE];
    char email[TAM_LETRAS];
    enum redeSocial eSocial;
    char redeSocial[TAM_TELE];
}regContato;

int ler_arquivo(regContato agenda[TAM_REG]);
int adicionar(regContato agenda[TAM_REG], int cont);
int testeEmail(regContato Temail);
char confirmar(char op);
void ordemAlfabetica(regContato agenda[TAM_REG],int cont);
void salvarArquivo(regContato agenda[TAM_REG],int cont);
void maisculo(regContato agenda[TAM_REG],int cont);
char *obterEnde(enum endereco tpEnd);
char *obterTele(enum telefone tpTele);
char *obterSocial(enum redeSocial tpSocial);
void relatorio(regContato agenda[TAM_REG],int cont);
int consulta(regContato agenda[TAM_REG], int cont);
void imprimirConsulta(regContato agenda[TAM_REG], int cont);
int excluir(regContato agenda[TAM_REG], int cont);
void alterar(regContato agenda[TAM_REG],int cont);
void limparTela(void);
void CorMenu(void);

int main(){
    setlocale(LC_ALL,"");
    regContato agenda[TAM_REG];

    int menuP;
    int cont = ler_arquivo(agenda);
    do{
        CorMenu();
        limparTela();
        printf("\n|-------|[AGENDA]|--------|\n\n");
        printf("|Contatos registrados - %i |\n",cont);
        printf("+-------------------------+\n");
        printf("| 1- Adicionar Contato    |\n");
        printf("| 2- Alterar Contato      |\n");
        printf("| 3- Consultar Contato    |\n");
        printf("| 4- Excluir Contato      |\n");
        printf("| 5- Listagem de Contatos |\n");
        printf("| 0- Sair                 |\n");
        printf("+-------------------------+\n");
        scanf("%i",&menuP);

        switch(menuP){
            case 1:
                // * Recebe o novo valor de contatos cadastrados alem de deixar na proxima do vetor registro
                // * para uso posterior no programa em andamento
                cont = adicionar(agenda,cont);
            break;
            case 2:
                alterar(agenda,cont);
            break;
            case 3:
                imprimirConsulta(agenda,cont);
            break;
            case 4:
                // * Recebe o novo valor de contatos cadastrados alem de deixar na proxima do vetor registro
                // * para uso posterior no programa em andamento
                cont = excluir(agenda,cont);
            break;
            case 5:
                relatorio(agenda,cont);
            break;
            default:
                printf("Invalido\n");
            case 0:
            break;
        }
    }while(menuP!=0);

    return 0;
}

// Inicializar registro
int ler_arquivo(regContato agenda[TAM_REG]){
    char aux[TAM_LER_ARQ ];
    char *pt;
    int cont=0;
    setlocale(LC_ALL,"");

    FILE *arquivo = NULL;
    // Teste se ja h? um arquivo
    arquivo=fopen("lista.txt","r");
    if(arquivo==NULL){
        return cont;
    }

    // Leitura das linhas do arquivo
    while(!feof(arquivo)){
        fgets(aux,TAM_LER_ARQ ,arquivo);

        pt=strtok(aux,";");
        // * i Serve para avan?ar nos campos pos ; individualmente e atribuir cada um
        // * em seu determinado lugar no registro de acordo com a ordem armazenada
        int i=0;
        while(pt!=NULL){
            switch(i){
                case 0:
                    strcpy(agenda[cont].nome,pt);
                break;
                case 1:
                    agenda[cont].eEnde = atoi(pt);
                break;
                case 2:
                    strcpy(agenda[cont].endereco,pt);
                break;
                case 3:
                    agenda[cont].numCasa = atoi(pt);
                break;
                case 4:
                    agenda[cont].eTele = atoi(pt);
                break;
                case 5:
                    strcpy(agenda[cont].numTele,pt);
                break;
                case 6:
                    strcpy(agenda[cont].email,pt);
                break;
                case 7:
                    agenda[cont].eSocial = atoi(pt);
                break;
                case 8:
                    strcpy(agenda[cont].redeSocial,pt);
                break;
            }
            pt = strtok(NULL,";\n");
            i++;
        }
        // * cont Sera a quantidade de contatos lidos, e sera deixado na proxima posi??o
        // * no vetor do registro
        cont++;
    }
    fclose(arquivo);
    return cont-1;
}

// Adicionar
int adicionar(regContato agenda[TAM_REG], int cont){
    setlocale(LC_ALL,"");
    regContato regAux;
    char saida;

    limparTela();
    printf("|> Adicionar Contato <|\n\n");
    do{
        limparTela();
        printf("|> Adicionar Contato <|\n\n");
        // * Compara a quantidade de contatos armazenados com o tamanho do registro
        // * para saber o limite
        if(cont<TAM_REG){
            // Nome
            fflush(stdin);
            printf("| Nome |\n");
            scanf("%[^\n]s",&regAux.nome);

            // Endereço
            printf("Tipo de endereço\n");
            do{
                printf("1-Avenida | 2-Alameda | 3-Rua | 4-Travessa | 5-Rodovia | 6-Praça\n");
                scanf("%i",&regAux.eEnde);
                if(regAux.eEnde<1 || regAux.eEnde>6){
                    printf("Entrada invalida, Escolha uma das opções abaixo...\n");
                }
            }while(regAux.eEnde<1 || regAux.eEnde>6);
            fflush(stdin);
            printf("| Endereço |\n");
            scanf("%[^\n]s",&regAux.endereco);

            // Numero da casa
            printf("| Numero de casa -Apenas Numeros- |\n");
            scanf("%i",&regAux.numCasa);

            // Telefone
            printf("Tipo de telefone\n");
            do{
                printf("1-Celular | 2-Comercial | 3-Fixo | 4-Pessoal | 5-Fax\n");
                scanf("%i",&regAux.eTele);
                if(regAux.eTele<1 || regAux.eTele>5){
                    printf("Entrada invalida, Escolha uma das opções abaixo...\n");
                }
            }while(regAux.eTele<1 || regAux.eTele>5);
            fflush(stdin);
            printf("| Numero telefonico |\n");
            scanf("%[0123456789]s",&regAux.numTele);

            // Email
            int valido;
            printf("| Email |\n");
            // Chama uma função para fazer a validação do email, se der certo retorna 0
            do{
                fflush(stdin);
                scanf("%[^\n]s",&regAux.email);
                valido = testeEmail(regAux);
            }while(valido!=0);

            // Rede Social
            printf("Tipo de rede social\n");
            do{
                printf("1-Instagran | 2-Facebook | 3-LinkedIn | 4-Outros\n");
                scanf("%i",&regAux.eSocial);
                if(regAux.eSocial<1 || regAux.eSocial>4){
                    printf("Entrada invalida, escolha uma das opções abaixo...\n");
                }
            }while(regAux.eSocial<1 || regAux.eSocial>4);
            fflush(stdin);
            printf("| Rede Social |\n");
            scanf("%[^\n]s",&regAux.redeSocial);

            // Area de Confirmação
            printf("Confirma novo contato (S/N)\n");
            char op = confirmar(op);

            // Adicionando
            if(op=='s'){
                printf("Adicionado\n");
                agenda[cont]=regAux;
                cont++;
            }
            // Não adicionando
            if(op=='n'){
                printf("Removendo entrada...\n");
            }
        }
        else{
            printf("Limite maximo atingido\n");
        }

        // Adicionar outro contato?
        printf("Deseja adicionar outro contato (S/N)?\n");
        saida = confirmar(saida);
    }while(saida!='n');

    // Ordenação alfabetica, formatação e Salvamento no arquivo
    maisculo(agenda,cont);
    if(cont != 1 && cont >0){
        ordemAlfabetica(agenda,cont);
    }
    salvarArquivo(agenda,cont);

    return cont;
}

// Teste email
int testeEmail(regContato Temail){
     // Encontrar @
    int aux = -1;
    // Pegando tamanho do email digitado
    int tam = strlen(Temail.email);

    for(int i = 0; i<tam; i++){
        if(Temail.email[i]=='@'){
                aux = i;
        }
    }
    // Se o achar o @
    if(aux !=-1){
        // Se o @ não tiver na primeira posição ou na ultima
        if(aux !=0 && aux != tam-1){
            return 0;
        }
        else{
            printf("Email invalido! Digite novamente\n");
            return -1;
        }
    }
    // N?o achou o @
    else{
        printf("Email invalido! Digite novamente\n");
        return aux;
    }
}

// Confirmação
char confirmar(char op){
    do{
        fflush(stdin);
        op = tolower(getchar());
        if(op!='s' && op!='n'){
            printf("Entrada invalida\n");
        }
    }while(op!= 's' && op!='n');
    return op;
}

// Ordenação em ordem alfabetica
void ordemAlfabetica(regContato agenda[TAM_REG],int cont){
    setlocale(LC_ALL,"");
    regContato auxReg;

    for(int i=0;i<cont-1;i++){
        for(int j=i+1;j<cont;j++){
            if(strcmp(agenda[i].nome,agenda[j].nome)>0){
                auxReg = agenda[i];
                agenda[i] = agenda[j];
                agenda[j] = auxReg;
            }
        }
    }
}

// Salvamento (Possivel autosave)
void salvarArquivo(regContato agenda[TAM_REG],int cont){
    setlocale(LC_ALL,"");
    FILE *arquivo = NULL;

    arquivo = fopen("lista.txt","w");
    if(arquivo==NULL){
        printf("Erro ao acessar arquivo\n");
        exit(0);
    }
    for(int i=0;i<cont;i++){
        fprintf(arquivo,"%s;%i;%s;%i;%i;%s;%s;%i;%s\n",agenda[i].nome,agenda[i].eEnde,agenda[i].endereco, agenda[i].numCasa,agenda[i].eTele,agenda[i].numTele,
                                                       agenda[i].email,agenda[i].eSocial,agenda[i].redeSocial);
    }
    fclose(arquivo);
}

// Maiusculo
void maisculo(regContato agenda[TAM_REG],int cont){
    setlocale(LC_ALL,"");
    // * Testa se a primeira letra do nome esta entre as letras minusculas na tabela ASCII
    // * e a transforma em maiscula.
    for(int i=0;i<cont;i++){
        if(agenda[i].nome[0]>=97 && agenda[i].nome[0]<=122){
            agenda[i].nome[0]-=32;
        }
    }

}

// Pegando enumerado de endereço
char *obterEnde(enum endereco tpEnd){
    char *nomeEnde[] = {"Av.", "Al.", "R.", "Tr.", "Rod.", "Pr."};

    return (nomeEnde[tpEnd-1]);
}
// Pegando enumerado de telefone
char *obterTele(enum telefone tpTele){
    char *nomeTele[] = {"Celular:","Comercial:","Fixo:","Pessoal:","Fax:"};

    return (nomeTele[tpTele-1]);
}
// Pegando enumerado de rede social
char *obterSocial(enum redeSocial tpSocial){
    char *nomeSocial[] = {"Instagram>","Facebook>","LinkedIn>","Outros>"};

    return (nomeSocial[tpSocial-1]);
}

// Listagem
void relatorio(regContato agenda[TAM_REG],int cont){
    setlocale(LC_ALL,"");
    limparTela();
    printf("|> Relatorio de Contatos <|\n\n");
    // Mostragem em padronizada dos dados registrados, pela função printf.
    if(cont!=0){
        printf("+-----------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("| %-20.20s | %-24.24s | %-6s | %-20.20s | %-20.20s | %-30.30s |\n","Nome","Endereço","Casa","Telefone","Email","Rede Social");
        printf("+-----------------------------------------------------------------------------------------------------------------------------------------+\n");
        for(int i=0;i<cont;i++){
            printf("| %-20.20s | %-4s%-20.20s | %-6i | %-10s%-10.10s | %-20.20s | %-10s%-20.20s |\n",agenda[i].nome, obterEnde(agenda[i].eEnde), agenda[i].endereco, agenda[i].numCasa,
                                                                                                     obterTele(agenda[i].eTele), agenda[i].numTele, agenda[i].email,
                                                                                                     obterSocial(agenda[i].eSocial), agenda[i].redeSocial);
            printf("+-----------------------------------------------------------------------------------------------------------------------------------------+\n");
            if(i%5==4){                                           // * Testa se o resto da 4, que como começa com 0, o total de resto ate 4 ira ser 5
                printf("Pressione <ENTER> para continuar.\n");    // * e apos cinco rodadas precisara pressionar enter para continuar.
                fflush(stdin);
                getchar();
            }
        }
    }
    else{
        printf("Nada registrado...\n");
    }
    printf("Pressione <ENTER> para prosseguir para o menu.\n");
    fflush(stdin);
    getchar();
    limparTela();
}

// Consulta pelo nome
int consulta(regContato agenda[TAM_REG], int cont){
    setlocale(LC_ALL,"");
    char nome[TAM_CONSULTA];

    printf("| Insira um Nome |\n");
    fflush(stdin);
    scanf("%[^\n]s",&nome);
    if(nome[0]>=97 && nome[0]<=122){
        nome[0]-=32;
    }

    for(int i=0;i<cont;i++){
        // Achou o nome e retorna a posição.
        if(strncmp(nome,agenda[i].nome,8)==0){
            return i;
        }
        // Não achou o nome.
        else if(i==cont-1 && strncmp(nome,agenda[i].nome,8)!=0){
            return -1;
        }
    }
}

// Impressao da consulta
void imprimirConsulta(regContato agenda[TAM_REG], int cont){
    setlocale(LC_ALL,"");
    char saida;

    do{
        limparTela();
        printf("|> Consultar Contato <|\n\n");
        // Testa se ja tem contatos registrados antes de continuar.
        if(cont!=0){
            // Recebe a posição da função de procura.
            int i = consulta(agenda,cont);
                // Se o retorno da procura for diferente de -1, no caso se achar o nome.
                if(i!=-1){
                    printf("+----------------------------+\n");
                    printf("| %s |\n",agenda[i].nome);
                    printf("Endereço: %s%s\n",obterEnde(agenda[i].eEnde),agenda[i].endereco);
                    printf("Casa: %i\n",agenda[i].numCasa);
                    printf("Telefone> %s %s\n",obterTele(agenda[i].eTele),agenda[i].numTele);
                    printf("Email: %s\n",agenda[i].email);
                    printf("Rede social> %s %s\n",obterSocial(agenda[i].eSocial),agenda[i].redeSocial);
                    printf("+----------------------------+\n");
                }
                // Retorno -1, não achou o nome.
                else{
                    printf("Nome não encontrado...\n");
                }
        }
        // Sem contatos registrados.
        else{
            printf("Nada registrado...\n");
        }
        printf("Pressione <ENTER> para prosseguir.\n");
        fflush(stdin);
        getchar();
        // Teste de saida(Deseja continuar).
        printf("Deseja procurar outro nome(S/N)\n");
        saida = confirmar(saida);
    }while(saida=='s');
}

// Excluir contato
int excluir(regContato agenda[TAM_REG], int cont){
    setlocale(LC_ALL,"");
    char saida,op;

    do{
        limparTela();
        printf("|> Excluir Contato <|\n\n");
        // Checa se ja tem contatos existentes.
        if(cont!=0){
            int i = consulta(agenda,cont);
            // Checa se achou o nome, se achou vai ser diferente de -1.
            if(i!=-1){
                // Recebe o tipo de confirmação do usuario.
                printf("| %s |\n",agenda[i].nome);
                printf("Deseja excluir esse contato(S/N)\n");
                op = confirmar(op);
                // Recebe a confirmação do usario.
                if(op=='s'){
                    printf("Excluindo...\n");
                    for(int f=i;f<cont;f++){
                            agenda[f] = agenda[f+1];
                    }
                    cont --;
                }
                // Recebe o cancelamento do usuario.
                else if(op=='n'){
                    printf("Cancelando operação...\n");
                }
            }
            // Retorno do i sera -1, ou seja não encontrou.
            else{
                printf("Nome não encontrado...\n");
            }
        }
        else{
            printf("Nada registrado...\n");
        }
        printf("Pressione <ENTER> para prosseguir.\n");
        fflush(stdin);
        getchar();
        // Teste de saida(Deseja continuar).
        printf("Deseja excluir outro contato(S/N)\n");
        saida = confirmar(saida);
    }while(saida=='s');

    if(cont != 1 && cont >0){
        ordemAlfabetica(agenda,cont);
    }
    salvarArquivo(agenda,cont);

    return cont;
}

// Alterar
void alterar(regContato agenda[TAM_REG],int cont){
    setlocale(LC_ALL,"");
    regContato regAlt;
    // Saida = saida, op = opções de confirmações, escolha = escolha de campos, valido = validação do email.
    char saida,op;
    int escolha,valido;

    do{
        limparTela();
        printf("|> Alterar Contato <|\n\n");
        // Checa se ja tem contatos existentes.
        if(cont!=0){
            int i = consulta(agenda,cont);
            // Checa se achou o nome, se achou vai ser diferente de -1.
            if(i!=-1){
                // Recebe o tipo de confirmação do usuario
                printf("| %s |\n",agenda[i].nome);
                printf("Usar este contato(S/N)\n");
                op = confirmar(op);
                // Recebe a confirmação do usario para usar esse nome.
                if(op=='s'){
                    // Registro de alteração sem vetor recebe os dados da posição para alteração posterior
                    regAlt = agenda[i];

                    printf("+--------<Escolha o campo>---------+\n");
                    printf("+----------------------------------+\n");
                    printf("| 1- Nome        || 2- Endereço    |\n");
                    printf("| 3- Numero casa || 4- Telefone    |\n");
                    printf("| 5- Email       || 6- Rede social |\n");
                    printf("+----------------------------------+\n");
                    scanf("%i",&escolha);
                    // * Nos cases dos switch sempre mostrara primeiro o dado antigo, e logo depois pedira
                    // * para inserir o dado novo.
                    switch(escolha){
                        case 1:
                            printf("| %s |\n\n",agenda[i].nome);
                            printf("Novo: ");
                            fflush(stdin);
                            scanf("%[^\n]s",&regAlt.nome);
                        break;
                        case 2:
                            printf("| %s %s |\n\n",obterEnde(agenda[i].eEnde), agenda[i].endereco);
                            printf("Novo Tipo\n");
                            do{
                                printf("1-Avenida | 2-Alameda | 3-Rua | 4-Travessa | 5-Rodovia | 6-Praça\n");
                                scanf("%i",&regAlt.eEnde);
                                if(regAlt.eEnde<1 || regAlt.eEnde>6){
                                    printf("Entrada invalida, escolha uma das opções abaixo...\n");
                                }
                            }while(regAlt.eEnde<1 || regAlt.eEnde>6);
                            printf("Endereço: ");
                            fflush(stdin);
                            scanf("%[^\n]s",&regAlt.endereco);
                        break;
                        case 3:
                            printf("| %i |\n\n",agenda[i].numCasa);
                            printf("Novo: ");
                            scanf("%i",&regAlt.numCasa);
                        break;
                        case 4:
                            printf("| %s %s |\n\n",obterTele(agenda[i].eTele), agenda[i].numTele);
                            printf("Novo Tipo\n");
                            do{
                                printf("1-Celular | 2-Comercial | 3-Fixo | 4-Pessoal | 5-Fax\n");
                                scanf("%i",&regAlt.eTele);
                                if(regAlt.eTele<1 || regAlt.eTele>5){
                                    printf("Entrada invalida, escolha uma das opções abaixo...\n");
                                }
                            }while(regAlt.eTele<1 || regAlt.eTele>5);
                            printf("Numero: ");
                            fflush(stdin);
                            scanf("%[0123456789]s",&regAlt.numTele);
                        break;
                        case 5:
                            printf("| %s |\n\n",agenda[i].email);
                            printf("Novo: ");
                            // Chama uma função para fazer a validação do email, se der certo retorna 0
                            do{
                                fflush(stdin);
                                scanf("%[^\n]s",&regAlt.email);
                                valido = testeEmail(regAlt);
                            }while(valido!=0);
                        break;
                        case 6:
                            printf("| %s %s |\n\n",obterSocial(agenda[i].eSocial), agenda[i].redeSocial);
                            printf("Novo Tipo\n");
                            do{
                                printf("1-Instagran | 2-Facebook | 3-LinkedIn | 4-Outros\n");
                                scanf("%i",&regAlt.eSocial);
                                if(regAlt.eSocial<1 || regAlt.eSocial>4){
                                    printf("Entrada invalida, escolha uma das opções abaixo...\n");
                                }
                            }while(regAlt.eSocial<1 || regAlt.eSocial>4);
                            printf("Rede social: ");
                            fflush(stdin);
                            scanf("%[^\n]s",&regAlt.redeSocial);
                        break;
                        default:
                            printf("Invalido...\n");
                        break;
                    }
                    // Confirmar altera??o.
                    printf("Confirmar alteração(S/N)\n");
                    op = confirmar(op);
                    if(op=='s'){
                        agenda[i] = regAlt;
                    }
                    else if(op=='n'){
                        printf("Cancelando operação...\n");
                    }

                }
                // Recebe o cancelamento do usuario de não usar aquele nome.
                else if(op=='n'){
                    printf("Cancelando operação...\n");
                }
            }
            // Retorno do i sera -1, ou seja não encontrou.
            else{
                printf("Nome não encontrado...\n");
            }

        }
        else{
            printf("Nada registrado...\n");
        }
        // Teste de saida(Deseja continuar).
        printf("Deseja alterar outro contato(S/N)\n");
        saida = confirmar(saida);
    }while(saida=='s');

    if(cont != 1 && cont >0){
        ordemAlfabetica(agenda,cont);
    }
    salvarArquivo(agenda,cont);
}

void limparTela(void){
#ifdef __linux__
    system ( "clear" );
#elif _WIN32
    system ( "cls" );
#endif
}
void CorMenu(void){
#ifdef __linux__
    system ( "70" );
#elif _WIN32
    system ( "color 70" );
#endif
}
