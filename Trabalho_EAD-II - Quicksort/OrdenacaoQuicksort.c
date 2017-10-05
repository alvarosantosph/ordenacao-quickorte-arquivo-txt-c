/**
 * ORDENACAO QUICKSORT A PARTIR DE ARQUIVO TXT
 *
 * UNIPE - CENTRO UNIVERSITÁRIO DE JOÃO PESSOA
 * CURSO: CIÊNCIA DA COMPUTAÇÃO - 4° PERÍODO - 2017.2
 * MATÉRIA: ESTRUTURA DE DADOS II
 * PROFESSOR: EWERTON M. SALVADOR
 * ALUNO: ALVARO PHILIPE ANDRADE DOS SANTOS
 * MATRÍCULA: 1610015475
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

// Tipo base dos elementos da lista 
typedef struct elemento {
	int matricula;
	char nome[100];
	int idade;
}t_elemento;

// Estrutura lista
typedef struct lista {
	t_elemento vetor[MAX];
	int n;
}t_lista;

/**
 * Protótipos de Funções
 */

// Cria uma nova lista.
void criarLista(t_lista *lista);

// Obtem o tamanho atual da lista, nao o tamanho maximo.
int getTamanho(t_lista * lista);

// Listar do inicio ao fim
void listarInicioaoFim(t_lista * lista);

// Verifica se a lista esta cheia ou nao.
int isCheia(t_lista * lista);

// Inserir no final.
int inserirFinal(t_lista * lista, t_elemento dado);

// Algoritimo de ordenacao quicksort
void quickSort(t_lista *lista, int inicio, int fim);

int main() {
	
  t_lista mLista;
  t_elemento dado;	
  
  criarLista(&mLista); // Cria e inicializa lista
  
  FILE *arq;
  char matriculaTemp[11];
  char nomeTemp[100];
  char idadeTemp[4];
  char Linha[100];
  
  char temp;
  int i, ii;
  int matriculaConvertida;
  int idadeConvertida;
  
  arq = fopen("alunos.txt", "r");

  if (!arq) {
    printf("Impossivel abrir arquivo.\n");
    getch();
    exit(1);
  } else {
  	
  	  printf("----------------------------------------------\n");
	  printf("Ordenacao QuickSort a partir de arquivo txt\n");
	  printf("----------------------------------------------\n");

	  i = 0;
	  ii = 0;
	  
	  while (fgets(Linha, 100, arq)) {
	  	  	
	  	for (i = 0; i < strlen(Linha); i++) {
	  		if (Linha[i] != ',') {
	  			temp = Linha[i];
	  			matriculaTemp[ii] = temp;
	  			ii++;
	  		} else  {		
	  			matriculaTemp[ii] = '\0';
				ii = 0;
	  			break;
	  		}  	
	  	} 
	  	
	  	matriculaConvertida = atoi(matriculaTemp);
	  	
	  	dado.matricula = matriculaConvertida;
	  	
	  	for (i = i + 1; i < strlen(Linha); i++) {	
	  		if (Linha[i] != ',') {
	  			temp = Linha[i];
	  			nomeTemp[ii] = temp;
	  			ii++;
	  		} else  {		
	  			nomeTemp[ii] = '\0';
				ii = 0;
	  			break;
	  		}  	
	  	} 
	  	
	  	strcpy(dado.nome, nomeTemp);
	  	
	  	for (i = i + 1; i < strlen(Linha); i++) {	
	  		if (Linha[i] != '\n') {
	  			temp = Linha[i];
	  			idadeTemp[ii] = temp;
	  			ii++;
	  		} else  {		
	  			idadeTemp[ii] = '\0';
				ii = 0;
	  			break;
	  		}  	
	  	} 
	  	
	  	idadeConvertida = atoi(idadeTemp);
	  	
	  	dado.idade = idadeConvertida;
	  	
	  	inserirFinal(&mLista, dado); // Insere os dados obtidos do arquivo na estrutura
	  	  	
	  }
	  		  
	  int tamanhoLista = getTamanho(&mLista);
	  		  
	  quickSort(&mLista, 0, tamanhoLista-1);
	  
	  listarInicioaoFim(&mLista); // Lista os dados ordenados
  
  }
  
  fclose(arq);
  
  return 0;
}

/**
 * Funções
 */

/**
 * Cria uma nova lista, inicializa o n.
 *
 *@param lista ponteiro para lista
 */
void criarLista(t_lista * lista) {
	lista->n = 0;
}

/**
 * Obtem o tamanho atual da lista, nao o tamanho maximo.
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 *
 * @return o quantidade de elementos que estao na lista
 */
int getTamanho(t_lista * lista) {
    return lista->n;
}

/**
 * Listar do inÃ­cio ao fim.
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 */
 void listarInicioaoFim(t_lista * lista) {
 	int i;
 	t_elemento dado;
 	for (i = 0; i < lista->n; i++) {
 		dado = lista->vetor[i];
 		printf("Matricula: %d\n", dado.matricula);
 		printf("Nome: %s\n", dado.nome);
 		printf("Idade: %d\n\n", dado.idade);
 	}
}

/**
 * Verifica se a lista esta cheia ou nao.
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 *
 * @return Verdadeiro (1) se a lista estiver cheia, ou falso (0) caso contrario
 */
int isCheia(t_lista * lista) {
    return (lista->n == MAX-1);
}

/**
 * Inserir no final.
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 *
 * @param dado variavel do tipo t_elemento
 *
 * @return Verdadeiro (1) se conseguir inserir, ou falso (0) caso contrario
 */
int inserirFinal(t_lista * lista, t_elemento dado) {
	if (isCheia(lista)) {
    	return 0;
    } else {
 		lista->vetor[lista->n] = dado;
 		lista->n = lista->n + 1;
 		return 1;
 	}
 }
 
 /**
 * Algoritimo de ordenacao quicksort - complexidade: O(n log n)
 * 
 * @param vetor ponteiro para a lista
 *
 * @param inicio inicio da lista
 *
 * @param fim final da lista 
 */ 
void quickSort(t_lista *lista, int inicio, int fim)
{
   int i, j;
   t_elemento meio, aux;
 
   i = inicio;
   j = fim;
   meio = lista->vetor[(inicio + fim) / 2];
   
 
   do
   {
      while(lista->vetor[i].matricula < meio.matricula)
         i++;
      while(lista->vetor[j].matricula > meio.matricula)
         j--;
      if(i <= j)
      {
         aux = lista->vetor[i];
         lista->vetor[i] = lista->vetor[j];
         lista->vetor[j] = aux;
         i++;
         j--;
      }
   }while(i <= j);
 
   if(inicio < j)
      quickSort(lista, inicio, j);
   if(i < fim)
      quickSort(lista, i, fim);
}
