#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct stNo {
	int number;
	struct stNo *esquerda;
	struct stNo *direita;
}tNo;

tNo* cria_no(tNo *raiz, tNo *no, int number){
    no->number = number;
    no->esquerda = NULL;
	no->direita = NULL;
    
    if(!raiz)
        return no;

    if(number < raiz->number)
        raiz->esquerda = no;
    else
        raiz->direita = no;
    
}

tNo* subArvore(tNo *raiz, tNo *no, int number){
	if(!no){
		no = (tNo *) malloc(sizeof(tNo)); 
		if(!no){
			printf("Sem memoria\n"); exit(0);
		}
		
		return cria_no(raiz, no, number);
	}
	if(number < no->number) 
		return subArvore(no, no->esquerda, number);
	else
		return subArvore(no, no->direita, number);
}

void post_dot(FILE *treeGraph, tNo *no){
	if(no == NULL)
		return;
		
	if(no->esquerda != NULL){
		fprintf(treeGraph,"    %d -> %d;\n", no->number, no->esquerda->number);
		post_dot(treeGraph, no->esquerda);
	}
	
	if(no->direita != NULL){
		fprintf(treeGraph, "    %d -> %d;\n", no->number, no->direita->number);
		post_dot(treeGraph, no->direita);
	}
}

void exportTreeDot(tNo *raizTree, const char *my_tree_graph){
	FILE *dot = fopen(my_tree_graph, "w");
	
	if (dot == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    fprintf(dot, "digraph MyTreeB {\n");
    post_dot(dot, raizTree);
    fprintf(dot, "}\n");

    fclose(dot);
    printf("Árvore exportada com sucesso para '%s'.\n", my_tree_graph);
}

void print_arvore(tNo *no, int espaco){
	int i;
	if(!no)
		return;
	print_arvore(no->direita, espaco + 1);
	for(i=0; i<espaco; ++i)
		printf("  ");
	printf("%i\n", no->number);
	print_arvore(no->esquerda, espaco + 1);
}

int main(int argc, char *argv[]) {
	int number;
	int option;
	
	
	tNo *raiz = NULL;
	
	do{	
		printf("\n");	
		printf("[1] Inserir \n");
		printf("[2] Exibir Arvore \n");
		printf("[3] Exportar Arvore \n");
		printf("[0] Sair \n");
		printf("Opção: ");
		scanf("%d", &option);
		
		switch (option){
			case 1: 
				printf("Digite um inteiro: ");
				scanf("%d", &number);
				if(number != 0){
				if(!raiz)
					raiz = subArvore(raiz, raiz, number);
				else
					subArvore(raiz, raiz, number);
				}
				system("cls");
				printf(" *************************** \n Numero inserido com sucesso \n ***************************\n");
				break;
			case 2:
				system("cls");
				printf(" *************************** \n Exibindo arvore \n ***************************\n");
				print_arvore(raiz, 0);
				break;
			case 3:
				system("cls");
			    printf(" *************************** \n Exportando arvore para 'arvore.dot' \n ***************************\n");
			    exportTreeDot(raiz, "myTree.dot");
			    break;
			default:
				system("cls");
				printf(" *************************** \n Escolha uma Opcao Invalida \n ***************************\n");				
		}		
		
	} while(option != 0);
	system("cls");
	
	return 0;
}