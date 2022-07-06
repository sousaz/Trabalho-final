#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

typedef struct{
    char nome[50], genero[15];
    int idade;
}Dados;

int pegaInfo(){
    int tamanho;
    printf("Qual o tamanho da matriz? \n");
    scanf("%i", &tamanho);
    return tamanho;
}

char **alocaMatriz(char **dna, int tam){
    int i;
    dna = calloc(tam, sizeof(char*));
    for(i=0; i<tam; i++){
        dna[i] = calloc(tam, sizeof(char));
    }
    return dna;
}

char **carrega(char **dna, int tam){
    int i, j;
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
			printf("Digite o dna a ser comparado (a,g,t,c): \n");
			scanf(" %c", &*(*(dna + i) + j));
            if(tolower((*(*(dna + i) + j))) != 'a' && tolower((*(*(dna + i) + j))) != 'g' && tolower((*(*(dna + i) + j))) != 't' && tolower((*(*(dna + i) + j))) != 'c'){
                printf("Letra invalida!!\n");
                exit(0);
            }
        }
    }
}

void mostra(char **dna, int tam){
	int i, j;
	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			printf("%c\t", *(*(dna + i) + j));
		}
		printf("\n");
	}
}

int linha(char **dna, int tam){
    int i, j, igual;
    for(i = 0; i < tam; i++){
        igual = 1;
        for(j = 0; j < tam - 1; j++){
            if(*(*(dna + i) + j) == *(*(dna + i) + j + 1)){
                igual++;
            }
            else{
                igual = 1;
            }
            if(igual == 4){
                return 1;
            }
        }
    }
    return 0;
}

int coluna(char **dna, int tam){
    int i, j, igual;
    for(j = 0;j < tam; j++){
        igual = 1;
        for(i = 0; i < tam - 1; i++){
            if(*(*(dna + i) + j) == *(*(dna + i + 1) + j)){
                igual++;
            }
            else{
                igual = 1;
            }
            if(igual == 4){
                return 1;
            }
        }
    }
    return 0;
}

int principal(char **dna, int tam){
    int i, igual;
    igual = 1;
    for(i = 0; i < tam - 1; i++){
        if(*(*(dna + i) + i) == *(*(dna + i + 1) + i + 1)){
            igual++;
        }
        else{
            igual = 1;
        }
        if(igual == 4){
            return 1;
        }
    }
    return 0;
}

int principais(char **dna, int tam){
    int i, j, z, igual;
    // acima da diagonal principal
    igual = 1;
    for(z = 0; z < tam; z++){
        i = 0;
        for(j = 1 + z; j < tam; j++){
            if(*(*(dna + i) + j) == *(*(dna + i + 1) + j + 1)){
                igual++;
            }
            else{
                igual = 1;
            }
            if(igual == 4){
                return 1;
            }
            i++;
        }
    }

    // abaixo da diagonal principal
    igual = 1;
    for(z = 0; z <  tam; z++){
        j = 0;
        for(i = 1 + z; i < tam - 1; i++){
            if(*(*(dna + i) + j) == *(*(dna + i + 1) + j + 1)){
                igual++;
            }
            else{
                igual = 1;
            }
            if(igual == 4){
                return 1;
            }
            j++;
        }
    }
    return 0;
}

int secundaria(char **dna, int tam){
    int i, j ,k, igual;
    // olha a secundaria principal e acima dela
    igual = 1;
    for(k = 1; k < tam; k++){
        j = tam - k;
        for(i = 0; i < tam - k; i++){
            if(*(*(dna + i) + j) == *(*(dna + i + 1) + j - 1)){
                igual++;
            }
            else{
                igual = 1;
            }
            if(igual == 4){
                return 1;
            }
            j--;
        }
    }

    // olha abaixo da diagonal secundaria
    igual = 1;
    for( k = 0; k < tam; k++){
        j = tam - k;
        for(i = 1; i <  tam - 1; i++){
            if(*(*(dna + i) + j) == *(*(dna + i + 1) + j - 1)){
                igual++;
            }
            else{
                igual = 1;
            }
            if(igual == 4){
                return 1;
            }
        }
    }
    return 0;
}

int isSimian(char **dna, int tam){
    if(linha(dna, tam) == 1){
        return 1;
    }
    if(coluna(dna, tam) == 1){
        return 1;
    }
    if(principal(dna, tam) == 1){
        return 1;
    }
    if(principais(dna, tam) == 1){
        return 1;
    }
    if(secundaria(dna, tam) == 1){
        return 1;
    }
}

int menu(){
    int opcao;
    printf("O que deseja fazer?\n(1)- Iniciar analise\n(2)- Sair\n");
    scanf("%i", &opcao);
    return opcao;
}

Dados carregaCadastro(Dados cadastro){
    printf("Qual o nome do dono(a) do DNA? \n");
    scanf(" %[^\n]", &cadastro.nome);
    printf("Qual a idade do mesmo? \n");
    scanf("%i", &cadastro.idade);
    printf("\n");
    return cadastro;
}

Dados mostraCadastroSimian(Dados cadastro){
    strcpy(cadastro.genero, "Simian");
    printf("Nome: %s\n", cadastro.nome);
    printf("\tIdade: %i\n", cadastro.idade);
    printf("\tGenero: %s\n", cadastro.genero);
    printf("\n");	
}

Dados mostraCadastroHuman(Dados cadastro){
	strcpy(cadastro.genero, "Human");
    printf("Nome: %s\n", cadastro.nome);
    printf("\tIdade: %i\n", cadastro.idade);
    printf("\tGenero: %s\n", cadastro.genero);
    printf("\n");
}

void liberaMemoria(char **dna, int tam){
	int i;
	for( i = 0; i <  tam; i++){
		free(*(dna + i));
	}
	free(dna);
}

int main(){
    char **dna;
    int tamanho, resultado, opcao, i;
    Dados cadastro;
    do{
        opcao = menu();
        switch (opcao){
        case 1:
            cadastro = carregaCadastro(cadastro);
            tamanho = pegaInfo();
            dna = alocaMatriz(dna, tamanho);
            carrega(dna, tamanho);
            mostra(dna, tamanho);
            resultado = isSimian(dna, tamanho);
            if(resultado == 1){
				mostraCadastroSimian(cadastro);
            }
            else{
				mostraCadastroHuman(cadastro);
            }
            liberaMemoria(dna, tamanho);
            break;
        case 2:
        printf("Saindo...");
            exit(0);
            break;
        default:
            printf("Opcao invalida!!\n");
            sleep(1);
            printf("\n");
        }
    }while(opcao != 2);







}