#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b)({typeof (a) a = (a); typeof (b) b = b; a > b? a : b;})


typedef struct stNo {
	int number;
	struct stNo *esquerda;
	struct stNo *direita;
	int fb;
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

tNo* rotacaoDireita(tNo *p){
    tNo *q = p->esquerda;
    p->esquerda = q->direita;
    
    q-> direita = p;
    return q;
}

tNo * rotacaoEsquerda(tNo *p){
    tNo *q = p->direita;
    p->direita = q->esquerda;
    
    q->esquerda = p;
    return q;
}

tNo * balancear (tNo *p){
    if(p->fb <= -2){
        if(p->esquerda->fb > 0)
            p->esquerda=rotacaoEsquerda(p->esquerda);
        p=rotacaoDireita(p);
    }
    else{
        if(p->direita->fb < 0)
            p->direita=rotacaoDireita(p->direita);
        p=rotacaoEsquerda(p);
    }
    return p;
}

int atualizaFatBal (tNo **no){
    int he, hd;
    if(*no == NULL)
        return 0;
    he=atualizaFatBal(&(*no)->esquerda);
    hd=atualizaFatBal(&(*no)->direita);
    (*no)->fb=hd-he;
    if(abs((*no)->fb) >= 2){
        *no=balancear(*no);
        he=atualizaFatBal(&(*no)->esquerda);
        hd=atualizaFatBal(&(*no)->direita);
        (*no)->fb=hd-he;
    }
    return max(hd,he)+1;
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

void exportDotPdf(char *my_tree_graph){
	char comando[200];
    sprintf(comando, "dot -Tpdf %s -o pdf_my_tree_graph.pdf", my_tree_graph);    
	system(comando);
}

void exportDotPng(char *my_tree_graph){
	char comando[200];
    sprintf(comando, "dot -Tpng %s -o png_my_tree_graph.png", my_tree_graph);    
	system(comando);
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
		printf("[3] Exportar Arvore para .dot \n");
		printf("[4] Exportar Arvore para .pdf \n");
		printf("[5] Exportar Arvore para .png \n");
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
					atualizaFatBal(&raiz);
				}
				system("cls");
				printf(" *************************** \n Numero Inserido Com Sucesso \n ***************************\n");
				break;
			case 2:
				system("cls");
				printf(" *************************** \n Exibindo Arvore \n ***************************\n");
				print_arvore(raiz, 0);
				break;
			case 3:
				system("cls");
			    printf(" *************************** \n Exportando Arvore Para .dot \n ***************************\n");
			    exportTreeDot(raiz, "myTree.dot");
			    break;
			case 4:
				system("cls");
			    printf(" *************************** \n Exportando Arvore Para .pdf \n ***************************\n");
			    exportTreeDot(raiz, "myTree.dot");
			    exportDotPdf("myTree.dot");
			    break;
			case 5:
				system("cls");
			    printf(" *************************** \n Exportando Arvore Para .png \n ***************************\n");
			    exportTreeDot(raiz, "myTree.dot");
			    exportDotPng("myTree.dot");
			    break;
			default:
				system("cls");
				printf(" *************************** \n Escolha uma Opcao Valida \n ***************************\n");				
		}		
		
	} while(option != 0);
	system("cls");
	
	return 0;
}