#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//função para embaralhar elementos de dentro de um vetor char
void embaralhar(char *vet, int n){
    for (int i = 0; i < n; i++){
		int r = rand() % n;
        char temp = vet[i];
		vet[i] = vet[r];
		vet[r] = temp;
	}
}

//função para embaralhar elementos de dentro de um vetor inteiro
void embaralhar_int(int *vet, int n){
    for (int i = 0; i < n; i++){
		int r = rand() % n;
        int temp = vet[i];
		vet[i] = vet[r];
		vet[r] = temp;
	}
}

//Criando estrutura registro que vai armazenar a chave e o valor char 
typedef struct registro{
    int chave;
    char str[3];
    struct registro *prox;
}Registro;

typedef Registro* Hash; //Hash é um vetor que será alocado dinâmicamente

//Função para inicializar a tabela hash com NULL
void inicializa(Hash *tab, int m){
    for(int i = 0; i < m; i++){
        tab[i] = NULL;
    }
}

//Função hash de divisão
int hash_div(int chave, int m){
    return chave % m;
}

//Função hash de multiplicação
int hash_mux(int chave){
    return (int) chave * 0.09;
}

//Função para alocar na memória o espaço necessário para criar um Registro
Registro *aloca(int chave, char str[]){
    Registro *novo = (Registro *) malloc(sizeof(Registro));
    novo->chave = chave;
    strcpy(novo->str, str);
    novo->prox = NULL;
    return novo;
}

//Função para inserir elementos na tabela hash de divisão
void insere_div(Hash *tab, int m, int chave, char str[]){
    int h = hash_div(chave, m); //h vai receber o resto da divisão
    Registro *p = tab[h];
    Registro *ant = NULL;
    while(p != NULL){
        ant = p;
        p = p->prox;
    }

    Registro *novo = aloca(chave, str);
    
    //caso aponte para o primeiro elemento ele fará apontar para o proximo, pois o anterior de primeiro aponta para nulo 
    if(!ant){
        tab[h] = novo;
    } else {
        ant->prox = novo;
    }
}

//Função para inserir elementos na tabela hash de multiplicação
void insere_mux(Hash *tab, int chave, char str[]){
    int h = hash_mux(chave); //h vai receber o resultado da chave multplicado por 0.09
    Registro *p = tab[h]; // p pega a posição da tabela em que h foi mapeado
    Registro *ant = NULL;
    while(p != NULL){
        ant = p;
        p = p->prox;
    }

    Registro *novo = aloca(chave, str);
    
    //caso aponte para o primeiro elemento ele fará apontar para o proximo, pois o anterior de primeiro aponta para nulo 
    if(!ant){
        tab[h] = novo;
    } else {
        ant->prox = novo;
    }
}

//Função para imprimir elementos da tabela hash
void imprime(Hash *tab, int m){
    int c = 0;
    for(int i = 0; i < m; i++){
        printf("%i: ", i);
        if(tab[i]){
            Registro *p = tab[i];
            printf("\n");
            while(p){
                printf("\t%d\t%s\t%p\n", p->chave, p->str, p->prox);
                p = p->prox;
                if(p != NULL){//conta o número de colisões
                    c++;
                }
            }
        } else {
            printf("NULL\n");
        }
    }
    printf("############################COLISÕES: %d #######################################################\n", c);//imprime o número de colisões
}

//Função para fazer busca de um elemento nas tabelas hash
Registro* busca(Hash *tab, int m, int chave){
    int h = hash_div(chave, m);

    Registro *p = tab[h];
    
    while((p) && (p->chave != chave)){
        p = p->prox;
    }

    return p;
}

int excluir_div(Hash *tab, int m, int chave){
    int h = hash_div(chave,m);
    if(tab[h] == NULL){ //verifica se tem algum valor na posição
        return -1;
    }

    Registro *p = tab[h];
    Registro *ant = NULL;
    int key = -1;

    while((p != NULL) && (p->chave != chave)){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        return key;
    }

    if(ant == NULL){ //se tiver apontando para um elemento na primeira posição
        tab[h] = p->prox;
    } else {
        ant->prox = p->prox;
    }
    key = p->chave;
    
    free(p);

    return key;
}

int excluir_mux(Hash *tab, int chave){
    int h = hash_mux(chave);
    if(tab[h] == NULL){ //verifica se tem algum valor na posição
        return -1;
    }

    Registro *p = tab[h];
    Registro *ant = NULL;
    int key = -1;

    while((p != NULL) && (p->chave != chave)){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        return key;
    }

    if(ant == NULL){ //se tiver apontando para um elemento na primeira posição
        tab[h] = p->prox;
    } else {
        ant->prox = p->prox;
    }
    key = p->chave;
    
    free(p);

    return key;
}

//Função para liberar o espaço da tabela hash
void libera(Hash *tab, int m){
    int i;
    for(i = 0; i < m; i++){
        if(tab[i]){
            Registro *p = tab[i];
            Registro *q;
            while(p){
                q = p;
                p = p->prox;
                free(q);
            }
        }
    }
}

//Função para gerar o char de tamanho 3
char *gera_char(){
    char vet[26] = {"abcdefghijklmnopqrstuvwxyz"};
    char *c;
    c = (char *) malloc(sizeof(char));
    
    int n;
    for(int i = 0; i < 3; i++){
        embaralhar(vet, 26);
        n = rand() % 26;
        c[i] = vet[n];
    }
    
    return c;
}

//Função para preencher o vetor com os registros do tipo 1, pares
void preenche_vet_tipo1(int *vet, int tam){
    int vet_tipo1[512];
    int x = 0;
    for(int i = 0; i < 1024; i++){
        if((i % 2) == 0){    
            vet_tipo1[x] = i;
            x++;
        }
    }

    embaralhar_int(vet_tipo1, 512);

    for(int i = 0; i < tam; i++){
        vet[i] = vet_tipo1[i];
    }
}

//Função para preencher o vetor com os registros do tipo 2, sem restrição
void preenche_vet_tipo2(int *vet, int tam){
    int vet_tipo2[1024];
    for(int i = 0; i < 1024; i++){
        vet_tipo2[i] = i;
    }

    embaralhar_int(vet_tipo2, 1024);

    for(int i = 0; i < tam; i++){
        vet[i] = vet_tipo2[i];
    }
}

//Função para inserir os registros na tabela hash de divisão
void insere_tab_div(Hash *tab, int qtd_reg, int *vet, int tipo){
    if(tipo == 1){
        inicializa(tab, 100);
        for(int i = 0; i < qtd_reg; i++){
            insere_div(tab, 100, vet[i], gera_char());
        }
    } else if(tipo == 2){
        inicializa(tab, 100);
        for(int i = 0; i < qtd_reg; i++){
            insere_div(tab, 100, vet[i], gera_char());
        }
    } else {
        printf("Tipo invalido!\n");
        exit(1);
    }
}

//Função para inserir os registros na tabela hash de multiplicação
void insere_tab_mux(Hash *tab, int qtd_reg, int *vet, int tipo){
    if(tipo == 1){
        inicializa(tab, 100);
        for(int i = 0; i < qtd_reg; i++){
            insere_mux(tab, vet[i], gera_char());
        }

    } else if(tipo == 2){
        inicializa(tab, 100);
        for(int i = 0; i < qtd_reg; i++){
                insere_mux(tab, vet[i], gera_char());
        }
    } else {
        printf("Tipo invalido!\n");
        exit(1);
    }
}

int main(){
    
    srand(time(NULL));
    int m = 100; //tamanho da tabela hash
    Hash *tab[m]; //criando tab que é do tipo hash que corresponde a um vetor que será alocado dinâmicamente
    
    //declarando vetores tamanho 20 do tipo 1
    int vetor1_tipo1_tam20[20], vetor2_tipo1_tam20[20], vetor3_tipo1_tam20[20], vetor4_tipo1_tam20[20], vetor5_tipo1_tam20[20];
    //declarando vetores tamanho 20 do tipo 2
    int vetor1_tipo2_tam20[20], vetor2_tipo2_tam20[20], vetor3_tipo2_tam20[20], vetor4_tipo2_tam20[20], vetor5_tipo2_tam20[20];

    //declarando vetores tamanho 50 do tipo 1
    int vetor1_tipo1_tam50[50], vetor2_tipo1_tam50[50], vetor3_tipo1_tam50[50], vetor4_tipo1_tam50[50], vetor5_tipo1_tam50[50];
    //declarando vetores tamanho 50 do tipo 2
    int vetor1_tipo2_tam50[50], vetor2_tipo2_tam50[50], vetor3_tipo2_tam50[50], vetor4_tipo2_tam50[50], vetor5_tipo2_tam50[50];

    //declarando vetores tamanho 80 do tipo 1
    int vetor1_tipo1_tam80[80], vetor2_tipo1_tam80[80], vetor3_tipo1_tam80[80], vetor4_tipo1_tam80[80], vetor5_tipo1_tam80[80];
    //declarando vetores tamanho 80 do tipo 2
    int vetor1_tipo2_tam80[80], vetor2_tipo2_tam80[80], vetor3_tipo2_tam80[80], vetor4_tipo2_tam80[80], vetor5_tipo2_tam80[80];

    //preenchendo os vetores com os valores correspondentes
    preenche_vet_tipo1(vetor1_tipo1_tam20, 20);
    preenche_vet_tipo1(vetor2_tipo1_tam20, 20);
    preenche_vet_tipo1(vetor3_tipo1_tam20, 20);
    preenche_vet_tipo1(vetor4_tipo1_tam20, 20);
    preenche_vet_tipo1(vetor5_tipo1_tam20, 20);

    preenche_vet_tipo2(vetor1_tipo2_tam20, 20);
    preenche_vet_tipo2(vetor2_tipo2_tam20, 20);
    preenche_vet_tipo2(vetor3_tipo2_tam20, 20);
    preenche_vet_tipo2(vetor4_tipo2_tam20, 20);
    preenche_vet_tipo2(vetor5_tipo2_tam20, 20);

    preenche_vet_tipo1(vetor1_tipo1_tam50, 50);
    preenche_vet_tipo1(vetor2_tipo1_tam50, 50);
    preenche_vet_tipo1(vetor3_tipo1_tam50, 50);
    preenche_vet_tipo1(vetor4_tipo1_tam50, 50);
    preenche_vet_tipo1(vetor5_tipo1_tam50, 50);

    preenche_vet_tipo2(vetor1_tipo2_tam50, 50);
    preenche_vet_tipo2(vetor2_tipo2_tam50, 50);
    preenche_vet_tipo2(vetor3_tipo2_tam50, 50);
    preenche_vet_tipo2(vetor4_tipo2_tam50, 50);
    preenche_vet_tipo2(vetor5_tipo2_tam50, 50);

    preenche_vet_tipo1(vetor1_tipo1_tam80, 80);
    preenche_vet_tipo1(vetor2_tipo1_tam80, 80);
    preenche_vet_tipo1(vetor3_tipo1_tam80, 80);
    preenche_vet_tipo1(vetor4_tipo1_tam80, 80);
    preenche_vet_tipo1(vetor5_tipo1_tam80, 80);

    preenche_vet_tipo2(vetor1_tipo2_tam80, 80);
    preenche_vet_tipo2(vetor2_tipo2_tam80, 80);
    preenche_vet_tipo2(vetor3_tipo2_tam80, 80);
    preenche_vet_tipo2(vetor4_tipo2_tam80, 80);
    preenche_vet_tipo2(vetor5_tipo2_tam80, 80);

    //inserindo 20 registros de tipo 1 nas hashs de multiplicação 
    printf("\n20 REGISTROS DO TIPO 1 COM HASHS DE MULTIPLICACAO\n\n");
    insere_tab_mux(tab, 20, vetor1_tipo1_tam20, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 20, vetor2_tipo1_tam20, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 20, vetor3_tipo1_tam20, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 20, vetor4_tipo1_tam20, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 20, vetor5_tipo1_tam20, 1);
    imprime(tab, m);

    //inserindo 20 registros de tipo 1 nas hashs de divisão 
    printf("\n20 REGISTROS DO TIPO 1 COM HASHS DE DIVISAO\n\n");
    insere_tab_div(tab, 20, vetor1_tipo1_tam20, 1);
    imprime(tab, m);
    insere_tab_div(tab, 20, vetor2_tipo1_tam20, 1);
    imprime(tab, m);
    insere_tab_div(tab, 20, vetor3_tipo1_tam20, 1);
    imprime(tab, m);
    insere_tab_div(tab, 20, vetor4_tipo1_tam20, 1);
    imprime(tab, m);
    insere_tab_div(tab, 20, vetor5_tipo1_tam20, 1);
    imprime(tab, m);

    //inserindo 50 registros de tipo 1 nas hashs de multiplicação 
    printf("\n50 REGISTROS DO TIPO 1 COM HASHS DE MULTIPLICACAO\n\n");
    insere_tab_mux(tab, 50, vetor1_tipo1_tam50, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 50, vetor2_tipo1_tam50, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 50, vetor3_tipo1_tam50, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 50, vetor4_tipo1_tam50, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 50, vetor5_tipo1_tam50, 1);
    imprime(tab, m);

    //inserindo 50 registros de tipo 1 nas hashs de divisão
    printf("\n50 REGISTROS DO TIPO 1 COM HASHS DE DIVISAO\n\n");
    insere_tab_div(tab, 50, vetor1_tipo1_tam50, 1);
    imprime(tab, m);
    insere_tab_div(tab, 50, vetor2_tipo1_tam50, 1);
    imprime(tab, m);
    insere_tab_div(tab, 50, vetor3_tipo1_tam50, 1);
    imprime(tab, m);
    insere_tab_div(tab, 50, vetor4_tipo1_tam50, 1);
    imprime(tab, m);
    insere_tab_div(tab, 50, vetor5_tipo1_tam50, 1);
    imprime(tab, m);

    //inserindo 80 registros de tipo 1 nas hashs de multiplicação 
    printf("\n80 REGISTROS DO TIPO 1 COM HASHS DE MULTIPLICACAO\n\n");
    insere_tab_mux(tab, 80, vetor1_tipo1_tam80, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 80, vetor2_tipo1_tam80, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 80, vetor3_tipo1_tam80, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 80, vetor4_tipo1_tam80, 1);
    imprime(tab, m);
    insere_tab_mux(tab, 80, vetor5_tipo1_tam80, 1);
    imprime(tab, m);

    //inserindo 80 registros de tipo 1 nas hashs de divisão 
    printf("\n80 REGISTROS DO TIPO 1 COM HASHS DE DIVISAO\n\n");
    insere_tab_div(tab, 80, vetor1_tipo1_tam80, 1);
    imprime(tab, m);
    insere_tab_div(tab, 80, vetor2_tipo1_tam80, 1);
    imprime(tab, m);
    insere_tab_div(tab, 80, vetor3_tipo1_tam80, 1);
    imprime(tab, m);
    insere_tab_div(tab, 80, vetor4_tipo1_tam80, 1);
    imprime(tab, m);
    insere_tab_div(tab, 80, vetor5_tipo1_tam80, 1);
    imprime(tab, m);
    
    //inserindo 20 registros de tipo 2 nas hashs de multiplicação 
    printf("\n20 REGISTROS DO TIPO 2 COM HASHS DE MULTIPLICACAO\n\n");
    insere_tab_mux(tab, 20, vetor1_tipo2_tam20, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 20, vetor2_tipo2_tam20, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 20, vetor3_tipo2_tam20, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 20, vetor4_tipo2_tam20, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 20, vetor5_tipo2_tam20, 2);
    imprime(tab, m);

    //inserindo 20 registros de tipo 2 nas hashs de divisão 
    printf("\n20 REGISTROS DO TIPO 2 COM HASHS DE DIVISAO\n\n");
    insere_tab_div(tab, 20, vetor1_tipo2_tam20, 2);
    imprime(tab, m);
    insere_tab_div(tab, 20, vetor2_tipo2_tam20, 2);
    imprime(tab, m);
    insere_tab_div(tab, 20, vetor3_tipo2_tam20, 2);
    imprime(tab, m);
    insere_tab_div(tab, 20, vetor4_tipo2_tam20, 2);
    imprime(tab, m);
    insere_tab_div(tab, 20, vetor5_tipo2_tam20, 2);
    imprime(tab, m);

    //inserindo 50 registros de tipo 2 nas hashs de multiplicação
    printf("\n50 REGISTROS DO TIPO 2 COM HASHS DE MULTIPLICACAO\n\n");
    insere_tab_mux(tab, 50, vetor1_tipo2_tam50, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 50, vetor2_tipo2_tam50, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 50, vetor3_tipo2_tam50, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 50, vetor4_tipo2_tam50, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 50, vetor5_tipo2_tam50, 2);
    imprime(tab, m);

    //inserindo 50 registros de tipo 2 nas hashs de divisão 
    printf("\n50 REGISTROS DO TIPO 2 COM HASHS DE DIVISAO\n\n");
    insere_tab_div(tab, 50, vetor1_tipo2_tam50, 2);
    imprime(tab, m);
    insere_tab_div(tab, 50, vetor2_tipo2_tam50, 2);
    imprime(tab, m);
    insere_tab_div(tab, 50, vetor3_tipo2_tam50, 2);
    imprime(tab, m);
    insere_tab_div(tab, 50, vetor4_tipo2_tam50, 2);
    imprime(tab, m);
    insere_tab_div(tab, 50, vetor5_tipo2_tam50, 2);
    imprime(tab, m);

    //inserindo 80 registros de tipo 2 nas hashs de multiplicação 
    printf("\n80 REGISTROS DO TIPO 2 COM HASHS DE MULTIPLICACAO\n\n");
    insere_tab_mux(tab, 80, vetor1_tipo2_tam80, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 80, vetor2_tipo2_tam80, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 80, vetor3_tipo2_tam80, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 80, vetor4_tipo2_tam80, 2);
    imprime(tab, m);
    insere_tab_mux(tab, 80, vetor5_tipo2_tam80, 2);
    imprime(tab, m);

    //inserindo 80 registros de tipo  nas hashs de divisão
    printf("\n80 REGISTROS DO TIPO 2 COM HASHS DE DIVISAO\n\n"); 
    insere_tab_div(tab, 80, vetor1_tipo2_tam80, 2);
    imprime(tab, m);
    insere_tab_div(tab, 80, vetor2_tipo2_tam80, 2);
    imprime(tab, m);
    insere_tab_div(tab, 80, vetor3_tipo2_tam80, 2);
    imprime(tab, m);
    insere_tab_div(tab, 80, vetor4_tipo2_tam80, 2);
    imprime(tab, m);
    insere_tab_div(tab, 80, vetor5_tipo2_tam80, 2);
    imprime(tab, m);

/*
    //Buscando elemento na tabela hash
    Registro *reg = busca(tab, m, vetor5_tipo2_tam80[10]);
    printf("%d\t%s\t\n", reg->chave, reg->str);
*/

/*
    //Excluindo na hash de divisão
    int ex = excluir_div(tab, m, vetor5_tipo2_tam80[10]);
    printf("Chave: %d foi excluida.\n", ex);
    imprime(tab, m);
*/

/*
    //Excluindo na hash de multplicação
    int ex = excluir_mux(tab, vetor5_tipo2_tam80[10]);
    printf("Chave: %d foi excluida.\n", ex);
    imprime(tab, m);
*/

    libera(tab, m);

    return 0;
}