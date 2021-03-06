#include <stdlib.h>
#include <stdio.h>
#include "listaDinEncad.h"

void MenuDeOpcoes(int* opcao){
    
    printf("\n\n *-*-*-*-* MENU PRINCIPAL -*-*-*-*-* \n\n");

    printf(" Escolha uma opcao: \n\n");
    printf(" 1- Cadastrar alunos\n 2- Mostra alunos cadastrados\n 3- Remover aluno");
    printf("\n 4- Buscar por aluno\n 5- Tamanho da lista\n 6- A lista esta vazia?\n 7- Sair\n\n");

    printf(" Opcao: ");
    scanf("%d", opcao);
}

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    
    if(li != NULL){
        *li = NULL;
    }

    return li;
}

void libera_lista(Lista* li){
    
    if(li != NULL){
        T_elem* no;
        
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }

        free(li);
    }
}

int tamanho_lista(Lista* li){
    system("cls");
    
    if(li == NULL){
        return -1;
    }else{
        int cont = 0;
        T_elem* no = *li;   

        while(no != NULL){
            cont++;
            no = no->prox;
        }

        return cont;
    }
}

int lista_vazia(Lista* li){
    system("cls");

    if(li == NULL){
        return -1;
    }else if( (*li) == NULL ){
        return 1;
    }else{
        return 0;
    }
}

int insere_lista_inicio(Lista* li, T_aluno aluno){
    system("cls");

    if(li == NULL){
        return -1;
    }else{
        T_elem* no = (T_elem*) malloc(sizeof(T_elem));

        no->dados = aluno;
        no->prox = (*li);
        *li = no;

        return 1;
    }

}

void cadastar_alunos(Lista* li){
    system("cls");
    T_aluno aluno;
    char opcao;

    do{
        printf("\n Matricula do aluno: ");
        scanf("%i", &aluno.matricula);

        printf("\n Nome do aluno: ");
        scanf("%s", aluno.nome);

        printf("\n Primeira nota do aluno: ");
        scanf("%f", &aluno.nota1);

        printf("\n Segunda nota do aluno: ");
        scanf("%f", &aluno.nota2);

        printf("\n Segunda nota do aluno: ");
        scanf("%f", &aluno.nota3);
        
        //insere_lista_inicio(li, aluno);
        //insere_lista_final(li, aluno);
        insere_lista_ordenada(li, aluno);

        system("cls");
        printf("\n\n Deseja cadastar outro aluno? [s/n]: ");
        scanf(" %c", &opcao);

    }while(opcao != 'n');

}

void mostrar_todos_alunos(Lista* li){
    system("cls");

    if(li == NULL){
        printf("\n Lista nao existe!!\n\n");
    }else if( (*li) == NULL){
        printf("\n Lista vazia!\n\n");
    }else{
        T_elem* no = (*li);

        while(no != NULL){
            printf("\n Matricula: %i\n", no->dados.matricula);
            printf(" Nome: %s\n", no->dados.nome);
            printf(" Primeira nota: %.1f\n", no->dados.nota1);
            printf(" Segunda nota: %.1f\n", no->dados.nota2);
            printf(" Terceira nota: %.1f\n", no->dados.nota3);
            printf("\n -------------------------------------\n");

            no = no->prox;
        }
    }
}

int insere_lista_final(Lista* li, T_aluno aluno){

    if(li == NULL){
        return -1;
    }else{
        T_elem* no = (T_elem*) malloc(sizeof(T_elem));

        no->dados = aluno;
        no->prox = NULL;

        if((*li) == NULL){
            *li = no;
        }else{
            T_elem* aux = *li;
            
            while(aux->prox != NULL){
                aux = aux->prox;
            }

            aux->prox = no;
        }

        return 1;
    }
}

int insere_lista_ordenada(Lista* li, T_aluno aluno){
    
    if(li == NULL){
        return -1;
    }else{
        T_elem* no = (T_elem*) malloc(sizeof(T_elem));

        no->dados = aluno;
        no->prox = NULL;

        if((*li) == NULL){
            *li = no;
            return 1;
        }else{
            T_elem *anterior, *atual = (*li);

            while(atual != NULL && atual->dados.matricula < no->dados.matricula){
                anterior = atual;
                atual = atual->prox;
            }
            
            if(atual == (*li)){
                no->prox = (*li);
                *li = no;
            }else{
                no->prox = anterior->prox;
                anterior->prox = no;
            }
    
            return 1;
        }
    }
}

int remove_lista_inicio(Lista* li){
    system("cls");

    if(li == NULL){
        return -1;
    }else if(*li == NULL){
        return 0;
    }else{
        T_elem* no = *li;
        *li = (*li)->prox;
        free(no);
        return 1;
    }
}

int remove_lista_final(Lista* li){
    system("cls");

    if(li == NULL){
        return -1;
    }else if((*li) == NULL){
        return 0;
    }else{
        T_elem *no_anterior, *no = *li;

        while(no->prox != NULL){
            no_anterior = no;
            no = no->prox;
        }

        if(no == (*li)){
            *li = NULL; 
        }else{
            no_anterior->prox = NULL;
            free(no);
        }

        return  1;
    }
}

int remove_lista(Lista* li, int matricula){
    system("cls");

    if(li == NULL){
        return -1;
    }else if((*li) == NULL){
        return 0;        
    }else{
        T_elem *no_anterior, *no = *li;

        while(no != NULL && no->dados.matricula != matricula){
            no_anterior = no;
            no = no->prox;
        }

        if(no == (*li)){
            *li = no->prox;
        }else if(no == NULL){
            return 0;
        }else{
            no_anterior->prox = no->prox;
            free(no);   
        }
        
        return 1;
    }
}

int busca_lista_posicao(Lista* li, int posicao){
    system("cls");

    if(li == NULL){
        return -1;
    }else if((*li) == NULL || posicao == 0){
        return 0;
    }else{
        T_elem* no = *li;
        int pos = 1;

        while(no != NULL && pos < posicao){
            no = no->prox;
            pos++;
        }

        if(no == NULL){
            return 0;
        }else{
            printf("\n Matricula: %i\n", no->dados.matricula);
            printf(" Nome: %s\n", no->dados.nome);
            printf(" Primeira nota: %.1f\n", no->dados.nota1);
            printf(" Segunda nota: %.1f\n", no->dados.nota2);
            printf(" Terceira nota: %.1f\n", no->dados.nota3);

            return 1;
        }
    }
}


int busca_lista_matricula(Lista* li, int matricula){
    system("cls");

    if(li == NULL){
        return -1;
    }else if((*li) == NULL){
        return 0;
    }else{
        T_elem* no = *li;

        while(no != NULL && no->dados.matricula != matricula){
            no = no->prox;
        }

        if(no == NULL){
            return 0;
        }else{
            printf("\n Matricula: %i\n", no->dados.matricula);
            printf(" Nome: %s\n", no->dados.nome);
            printf(" Primeira nota: %.1f\n", no->dados.nota1);
            printf(" Segunda nota: %.1f\n", no->dados.nota2);
            printf(" Terceira nota: %.1f\n", no->dados.nota3);

            return 1;
        }
    }
}