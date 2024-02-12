#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"

int flag_read;


int main() {
    int opcao,pedido,verifica_nome;
    char *nome= malloc(100 * sizeof(char));
    char n[30];
    char entrada[30];
    typeLista lista_reservas, lista_pre_reservas;
    lista_reservas = cria();
    lista_pre_reservas = cria();

    flag_read=0;

    do {
        printf("\n====== Menu ======\n"
               "1- Reservar lavagem\n"
               "2- Reservar manutencao\n"
               "3- Cancelar uma reserva\n"
               "4- Cancelar uma pre-reserva\n"
               "5- Listar reservas por ordem de data (as mais antigas primeiro)\n"
               "6- Listar pre-reservas por ordem de data (as mais antigas primeiro)\n"
               "7- Listar reservas de um cliente por ordem de data (as mais recentes primeiro)\n"
               "8- Listar pre-reservas de um cliente por ordem de data (as mais recentes primeiro)\n"
               "9 - Realizar lavagem (Ira ser a realizada a tarefa mais antiga)\n"
               "10- Realizar manutencao (Ira ser a realizada a tarefa mais antiga)\n"
               "11- Guardar informacao\n"
               "12- Carregar informacao\n"
               "13- Sair\n"
               "====================\n"
               "Digite a opcao desejada: ");
        scanf("%s", n);
        fflush(stdin);
        if(so_numeros(n)) {
            opcao = atoi(n);
            switch (opcao) {
                case 1:
                    pedido = receber_pedido(&lista_reservas, &lista_pre_reservas, "lavagem");
                    if (pedido == 1) {
                        printf("\nPedido de reserva de lavagem guardado na lista de reservas.\n");
                    } else if (pedido == 0) {
                        printf("\nO Pedido de reserva de lavagem foi guardado na lista de pre-reservas.\n");
                    } else if(pedido==-2){
                        printf("\nReserva descartada. Dados duplicados.\n");
                    }else {
                        printf("\nReserva descartada.\n");
                    }
                    break;
                case 2:
                    pedido = receber_pedido(&lista_reservas, &lista_pre_reservas, "manutencao");
                    if (pedido == 1) {
                        printf("\nPedido de reserva de manutencao guardado na lista de reservas.\n");
                    } else if (pedido == 0) {
                        printf("\nO Pedido de reserva de manutencao foi guardado na lista de pre-reservas.\n");
                    } else {
                        printf("\nReserva descartada.\n");
                    }
                    break;
                case 3:
                    if (listar(&lista_reservas, 1) == -1) {
                        printf("\nNao existem reservas\n");
                        break;
                    }
                    printf("Digite 'QUIT' caso pretenda voltar para o Menu\n");
                    printf("\nDigite o numero correspondente a reserva que deseja cancelar: ");
                    fflush(stdin);
                    fgets(entrada, 30,stdin);
                    entrada[strcspn(entrada, "\n")] = '\0';
                    if(!strcmp(entrada,"QUIT")){
                        break;
                    }else if (so_numeros(entrada)) {
                        pedido = cancelar_reserva(&lista_reservas, &lista_pre_reservas, atoi(entrada));
                    } else {
                        printf("\nO valor digitado nao e um numero inteiro.\n");
                        break;
                    }
                    if (pedido == -1) {
                        printf("\nA reserva nao foi cancelada com sucesso. Nao existem reservas com o numero que digitou.\n");
                    }
                    break;
                case 4:
                    if (listar(&lista_pre_reservas, 2) == -2) {
                        printf("\nNao existem pre-reservas\n");
                        break;
                    }
                    printf("Digite 'QUIT' caso pretenda voltar para o Menu\n");
                    printf("\nDigite o numero correspondente a pre-reserva que deseja cancelar: ");
                    fflush(stdin);
                    fgets(entrada, 30,stdin);
                    entrada[strcspn(entrada, "\n")] = '\0';
                    if(!strcmp(entrada,"QUIT")){
                        break;
                    }else if (so_numeros(entrada)) {
                        pedido = cancelar_pre_reserva(&lista_pre_reservas, atoi(entrada));
                    } else {
                        printf("\nO valor digitado nao e um numero inteiro.\n");
                        break;
                    }
                    if (pedido == 1) {
                        printf("\nA pre-reserva foi cancelada com sucesso\n");
                    } else {
                        printf("\nA pre-reserva nao foi cancelada com sucesso. Nao existem pre-reservas com o numero que digitou.\n");
                    }
                    break;
                case 5:
                    if (listar(&lista_reservas, 1) == -1) {
                        printf("\nNao existem reservas\n");
                    }
                    break;
                case 6:
                    if (listar(&lista_pre_reservas, 2) == -2) {
                        printf("\nNao existem pre-reservas\n");
                    }
                    break;
                case 7:
                    do {
                        printf("\nDigite o nome do cliente ao qual pretende listar as reservas: ");
                        fgets(nome, 100, stdin);
                        nome[strcspn(nome, "\n")] = '\0';
                        verifica_nome = so_letras(nome);
                        if (verifica_nome == 0) {
                            printf("Nome invalido!\n");
                        }
                    } while (verifica_nome == 0);

                    if(!strcmp(nome,"QUIT")){
                        break;
                    }

                    pedido = listar_cliente(&lista_reservas, 1, nome);
                    if (pedido == 0) {
                        printf("\nNao existe nenhuma reserva do cliente %s.\n", nome);
                    } else if (pedido == -1) {
                        printf("\nNao existem reservas\n");
                    }
                    break;
                case 8:

                    do {
                        printf("\nDigite o nome do cliente ao qual pretende listar as pre-reservas: ");
                        fgets(nome, 100, stdin);
                        nome[strcspn(nome, "\n")] = '\0';
                        verifica_nome = so_letras(nome);
                        if (verifica_nome == 0) {
                            printf("Nome invalido!\n");
                        }
                    } while (verifica_nome == 0);

                    if(!strcmp(nome,"QUIT")){
                        break;
                    }

                    pedido = listar_cliente(&lista_pre_reservas, 2, nome);
                    if (pedido == 0) {
                        printf("\nNao existe nenhuma pre-reserva do cliente %s.\n", nome);
                    } else if (pedido == -2) {
                        printf("\nNao existem pre-reservas\n");
                    }
                    break;
                case 9:
                    pedido = pop_tarefa(&lista_reservas, "lavagem");
                    if (pedido == 1) {
                        printf("\nTarefa realizada com sucesso\n");
                    } else if (pedido == -1) {
                        printf("\nNao existe nenhuma tarefa deste tipo para ser realizada\n");
                    } else {
                        printf("\nNao existem reservas\n");
                    }
                    break;
                case 10:
                    pedido = pop_tarefa(&lista_reservas, "manutencao");
                    if (pedido == 1) {
                        printf("\nTarefa realizada com sucesso\n");
                    } else if (pedido == -1) {
                        printf("\nNao existe nenhuma tarefa deste tipo para ser realizada\n");
                    } else {
                        printf("\nNao existem reservas\n");
                    }
                    break;
                case 11:
                    if (write_file(&lista_reservas, &lista_pre_reservas, "Reservas.txt") == 1) {
                        flag_read = 0;
                        printf("\nInformacoes das listas guardadas no ficheiro com sucesso.\n");
                    }
                    break;
                case 12:

                    if (flag_read==0) {
                        /*
                        destroi(&lista_reservas);
                        destroi(&lista_pre_reservas);*/
                        if (read_file(&lista_reservas, &lista_pre_reservas, "Reservas.txt") == 1) {
                            printf("\nInformacoes do ficheiro guardadas nas listas com sucesso\n");
                            flag_read = 1;
                        }else{
                            printf("\nErro ao ler o ficheiro. Informacoes incorretas.\n");
                        }
                    } else {
                        printf("\nO ficheiro ja foi lido. Apenas podera carregar a informacao do ficheiro quando houver alteracao no mesmo.\n");
                    }

                    break;
                case 13:
                    printf("\nEncerrando o programa...\n");
                    break;
                default:
                    printf("\nOpção invalida!\n");
                    break;
            }
        }else{
            printf("\nOpcao invalida!\n");
        }
    } while (opcao != 13);

    free(nome);
    destroi(&lista_reservas);
    destroi(&lista_pre_reservas);

    return 0;
}

int so_letras(char * string){
    for(int i=0;i<(int)strlen(string);i++){
        if(!(((string[i]>=65 && string[i]<=90) || ((string[i]>=97 && string[i]<=122)) || string[i]==' '))){
            return 0;
        }
    }
    return 1;
}

int so_numeros(char *string){
    for(int i=0;i<(int)strlen(string);i++){
        if(!(string[i]>=48 && string[i]<=57)){
            return 0;
        }
    }
    return 1;
}

int compara_data(Data d1, Data d2) {
    // Comparação do ano
    if (d1.ano < d2.ano) return -1;    // Se o ano de d1 for menor que o ano de d2, retorna -1
    else if (d1.ano > d2.ano) return 1;// Se o ano de d1 for maior que o ano de d2, retorna 1
    // Comparação do mês
    if (d1.mes < d2.mes) return -1;    // Se o mês de d1 for menor que o mês de d2, retorna -1
    else if (d1.mes > d2.mes) return 1;// Se o mês de d1 for maior que o mês de d2, retorna 1
    // Comparação do dia
    if (d1.dia < d2.dia) return -1;    // Se o dia de d1 for menor que o dia de d2, retorna -1
    else if (d1.dia > d2.dia) return 1;// Se o dia de d1 for maior que o dia de d2, retorna 1
    // Comparação da hora inicial
    if (d1.hora_ini < d2.hora_ini) return -1;    // Se a hora inicial de d1 for menor que a hora inicial de d2, retorna -1
    else if (d1.hora_ini > d2.hora_ini) return 1;// Se a hora inicial de d1 for maior que a hora inicial de d2, retorna 1
    // Comparação do minuto inicial
    if (d1.min_ini < d2.min_ini) return -1;    // Se o minuto inicial de d1 for menor que o minuto inicial de d2, retorna -1
    else if (d1.min_ini > d2.min_ini) return 1;// Se o minuto inicial de d1 for maior que o minuto inicial de d2, retorna 1
    // Se todas as comparações forem iguais, retorna 0
    return 0;
}

bool verifica_disponibilidade(Data d1, Data d2) {
    if (d1.ano != d2.ano || d1.mes != d2.mes || d1.dia != d2.dia) { //Verifica se as datas são diferentes
        return true; //nao há conflito
    }
    else if (d1.ano == d2.ano && d1.mes == d2.mes && d1.dia == d2.dia) { //Verifica se as datas são iguais
        // Verifica se o horário inicial d2 é posterior ao horário final de d1 ou verifica se o horário final de d2 é anterior ao horário inicial de d1
        if ((d2.hora_ini > d1.hora_fim || (d2.hora_ini == d1.hora_fim && d2.min_ini >= d1.min_fim)) ||
            (d2.hora_fim < d1.hora_ini || (d2.hora_fim == d1.hora_ini && d2.min_fim <= d1.min_ini))) {
            return true; //nao há conflito
        }
    }
    return false;//há conflito
}

int verifica_data_hora(int dia, int mes, int ano, int hora_ini, int minuto_ini, int hora_fim, int minuto_fim,const char *tipo_tarefa){
    int h_fim, m_fim;
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1) {
        printf("Data invalida.\n");
        return -1;
    }
    if (hora_ini < 8 || hora_ini >= 18 || hora_fim > 18 || minuto_ini < 0 || minuto_ini > 59 || minuto_fim > 59 || minuto_fim < 0 || (hora_fim >= 18 && minuto_fim != 0)) {
        printf("Hora invalida.\n");
        return -1;
    }
    if (!strcmp(tipo_tarefa, "lavagem")) {
        h_fim = hora_ini;
        m_fim= minuto_ini + 30;

        // Verificação se a hora de fim ultrapassa as horas laborais
        if (m_fim >= 60) {
            h_fim += 1;
            m_fim -= 60;
        }
        if (hora_fim != h_fim || minuto_fim!=m_fim) {
            printf("Horas laborais excedidas.\n");
            return -1;
        }

    } else if (!strcmp(tipo_tarefa, "manutencao")) {
        h_fim= hora_ini + 1;
        m_fim= minuto_ini;

        if (hora_fim != h_fim || minuto_fim!=m_fim) {
            printf("Horas laborais excedidas.\n");
            return -1;
        }
    }
    return 1;
}

int lerDataHora(int *dia, int *mes, int *ano, int *hora_ini, int *minuto_ini, int *hora_fim, int *minuto_fim, const char *tipo_tarefa) {
    char input[20];
    bool flag;
    // Verificação da data
    do{
        flag=1;
        printf("Insira a data no formato (dia/mes/ano): ");
        scanf("%19s", input);

        if (strcmp(input, "QUIT") == 0) {
            return -1;
        }

        // Leitura da data
        if (sscanf(input, "%d/%d/%d", dia, mes, ano) != 3) {
            fflush(stdin);
            printf("Formato de data invalido.\n");
            flag=0;
        }
        fflush(stdin);
        if (*dia < 1 || *dia > 31 || *mes < 1 || *mes > 12 || *ano < 1) {
            printf("Data invalida.\n");
            flag=0;
        }
    }while(flag==0);

    // Verificação do horário
    do{
        flag=1;
        printf("Insira a hora no formato (hora:minuto): ");
        scanf("%19s", input);

        if (strcmp(input, "QUIT") == 0) {
            return -1;
        }

        // Leitura da hora
        if (sscanf(input, "%d:%d", hora_ini, minuto_ini) != 2) {
            fflush(stdin);
            printf("Formato de hora invalido.\n");
            flag=0;
        }
        fflush(stdin);

        // Verificação da hora
        if (*hora_ini < 8 || *hora_ini >= 18 || *minuto_ini < 0 || *minuto_ini > 59) {
            printf("Hora invalida.\n");
            flag=0;
        }

        if (!strcmp(tipo_tarefa, "lavagem")) {
            // Atualizar hora de fim para meia hora após a hora de início
            *hora_fim = *hora_ini;
            *minuto_fim = *minuto_ini + 30;

            // Verificação se a hora de fim ultrapassa as horas laborais
            if (*minuto_fim >= 60) {
                *hora_fim += 1;
                *minuto_fim -= 60;
            }
            if ((*hora_fim >= 18 && *minuto_fim != 0)) {
                printf("Horas laborais excedidas.\n");
                flag=0;
            }
        } else if (!strcmp(tipo_tarefa, "manutencao")) {
            // Atualizar hora de fim para uma hora após a hora de início
            *hora_fim = *hora_ini + 1;
            *minuto_fim = *minuto_ini;

            // Verificação se a hora de fim ultrapassa as horas laborais
            if ((*hora_fim >= 18 && *minuto_fim != 0)) {
                printf("Horas laborais excedidas.\n");
                flag=0;
            }
        }
    }while(flag==0);

    return 1;
}

typeLista cria() {
    //declara uma instância da struct typeLista para e inicializa os seus campos a null
    typeLista lista;
    lista.inicio = NULL;
    lista.fim = NULL;
    return lista;
}

int vazia(typeLista *lista) {
    return (lista->inicio == NULL); //verifica se a lista está vazia através do ponteiro para o inicio
}


void destroi(typeLista *lista) {
    //liberta a memória alocada para cada nó da lista
    noLista* atual = lista->inicio;
    while (atual != NULL) {
        noLista* temp_ptr = atual;
        atual = atual->prox;
        free(temp_ptr);
    }
    lista->inicio = NULL;
    lista->fim = NULL;
}

int verifica_duplos(typeLista* lista, Reserva elemento_inserir){
    //verifica se já existe um nó com as mesmas informaçoes
    noLista* temp;
    temp=lista->inicio;
    while(temp!=NULL){
        if(!compara_data(temp->reserva.data,elemento_inserir.data) && !strcmp(temp->reserva.cliente.nome,elemento_inserir.cliente.nome) && temp->reserva.cliente.numero==elemento_inserir.cliente.numero && !strcmp(temp->reserva.tipo,elemento_inserir.tipo)){
            return 1;
        }
        temp=temp->prox;
    }
    return 0;
}
void insere(typeLista* lista, Reserva elemento_inserir) {
    noLista *newNo = (noLista *) malloc(sizeof(noLista)); // aloca memória para o novo nó
    if (newNo == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    newNo->reserva = elemento_inserir; // guarda a reserva passada por parametro no novo nó
    newNo->ant = NULL;
    newNo->prox = NULL;

    if (vazia(lista)) { // se estiver vazia os dois ponteiros da listas igualam-se ao novo nó
        lista->inicio = newNo;
        lista->fim = newNo;

    } else { // caso contrario percorre a lista e encontra o sitio onde pertence (a lista é ordenada por datas de forma ascendente (antiga para a mais recente))
        noLista *atual = lista->inicio;
        while (atual != NULL) {
            if (compara_data(elemento_inserir.data, atual->reserva.data) <
                0) { // a data da reserva do nó a inserir é mais antiga que a atual da lista, logo é atrás da atual que tem que se inserir o nó
                newNo->prox = atual;
                newNo->ant = atual->ant;
                if (atual->ant != NULL) {
                    atual->ant->prox = newNo;
                } else {
                    lista->inicio = newNo;
                }
                atual->ant = newNo;
                break;
            }
            if (atual->prox == NULL) {
                atual->prox = newNo;
                newNo->ant = atual;
                lista->fim = newNo;
                break;
            }
            atual = atual->prox;
        }
    }
}

int reservar(typeLista* lista_reservas, typeLista* lista_pre_reservas,Reserva *elemento_reservar){
    bool flag=1;
    noLista *aux=lista_reservas->inicio;
    while(aux!=NULL){ // percorre a lista de reservas e verifica se há disponibilidade para inserir a nova reserva
        if(verifica_disponibilidade(aux->reserva.data,elemento_reservar->data)==false){
            flag=0;
            break;
        }
        aux=aux->prox;
    }
    if(!verifica_duplos(lista_reservas,*elemento_reservar)) {
        if (flag) { // se houver disponibilidade insere na lista de reservas
            insere(lista_reservas, *elemento_reservar);
            free(elemento_reservar);
            return 1;
        } else if(!verifica_duplos(lista_pre_reservas,*elemento_reservar)) { // se não houver é inserida na lista de pré-reservas caso o utilizador queira
            char opcao;
            printf("Hora indisponivel. Deseja inscrever-se na lista de espera? (y/n): ");
            scanf("%c", &opcao);
            fflush(stdin);
            while (opcao != 'y' && opcao != 'n') {
                printf("Resposta invalida. Introduza y ou n: ");
                fflush(stdin);
                scanf("%c", &opcao);
            }
            if (opcao == 'y') {
                insere(lista_pre_reservas, *elemento_reservar);
                free(elemento_reservar);
                return 0;
            } else {
                free(elemento_reservar);
                return -1; //reserva descartada
            }
        }else{
            return -2;
        }
    }else{
        return -2;
    }
}

int pop_tarefa(typeLista* lista_reservas, const char *tipo_tarefa) {
    if (lista_reservas == NULL || lista_reservas->inicio == NULL) { //Verifica se a lista está vazia
        return 0;
    }
    noLista* atual = lista_reservas->inicio;
    while (atual != NULL) { //percorre a lista de reservas
        if (strcmp(atual->reserva.tipo, tipo_tarefa) == 0) {
            // Encontrou uma reserva do tipo desejado
            if (atual == lista_reservas->inicio && atual == lista_reservas->fim) {
                // A lista possui apenas um elemento
                lista_reservas->inicio = NULL;
                lista_reservas->fim = NULL;
            } else if (atual == lista_reservas->inicio) {
                // A reserva está no início da lista
                lista_reservas->inicio = atual->prox;
                atual->prox->ant = NULL;
            } else if (atual == lista_reservas->fim) {
                // A reserva está no fim da lista
                lista_reservas->fim = atual->ant;
                atual->ant->prox = NULL;
            } else {
                // A reserva está no meio da lista
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
            }
            free(atual); // Libera a memória do nó removido
            return 1; // Retorna 1 para indicar sucesso
        }
        atual = atual->prox;
    }
    return -1; // Retorna -1 se não encontrou uma reserva do tipo desejado
}

int read_file(typeLista* lista_reservas, typeLista* lista_pre_reservas, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r"); //abre o ficheiro como leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return -1;
    }
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {  //lê linha a linha do ficheiro
        if (linha[0] == 'r') { //se o primeiro caracter for um "r" significa que é uma reserva
            Reserva reserva;
            //lê a reserva e coloca os dados numa instância da struct Reserva
            if(sscanf(linha, "r#%[^#]#%d#%d#%d#%d#%d#%d#%d#%d#%[^#]",
                      reserva.cliente.nome, &reserva.cliente.numero,
                      &reserva.data.dia, &reserva.data.mes, &reserva.data.ano,
                      &reserva.data.hora_ini, &reserva.data.min_ini,&reserva.data.hora_fim, &reserva.data.min_fim,
                      reserva.tipo)!=10){
                return -1;
            }else{
                reserva.tipo[strcspn( reserva.tipo, "\n")] = '\0';
                if(so_letras(reserva.cliente.nome)==0 || (strcmp(reserva.tipo,"lavagem")!=0 && strcmp(reserva.tipo,"manutencao")!=0)){
                    return -1;
                }
                if(verifica_data_hora(reserva.data.dia,reserva.data.mes,reserva.data.ano,reserva.data.hora_ini,
                                      reserva.data.min_ini,reserva.data.hora_fim,reserva.data.min_fim,reserva.tipo)==-1){
                    return -1;
                }
            }
            if(!verifica_duplos(lista_reservas,reserva)) {
                insere(lista_reservas, reserva); //insere na lista de reservas
            }
        } else if (linha[0] == 'p'){ //se o primeiro caracter for um "p" significa que é uma pre-reserva
            Reserva pre_reserva;
            //lê a pre-reserva e coloca os dados numa instância da struct Reserva
            if(sscanf(linha, "p#%[^#]#%d#%d#%d#%d#%d#%d#%d#%d#%[^#]",
                      pre_reserva.cliente.nome, &pre_reserva.cliente.numero,
                      &pre_reserva.data.dia, &pre_reserva.data.mes, &pre_reserva.data.ano,
                      &pre_reserva.data.hora_ini, &pre_reserva.data.min_ini,&pre_reserva.data.hora_fim, &pre_reserva.data.min_fim,
                      pre_reserva.tipo)!=10){
                return -1;
            }else{
                pre_reserva.tipo[strcspn( pre_reserva.tipo, "\n")] = '\0';
                if(so_letras(pre_reserva.cliente.nome)==0 || (strcmp(pre_reserva.tipo,"lavagem")!=0 && strcmp(pre_reserva.tipo,"manutencao")!=0)){
                    return -1;
                }
                if(verifica_data_hora(pre_reserva.data.dia,pre_reserva.data.mes,pre_reserva.data.ano,pre_reserva.data.hora_ini,
                                      pre_reserva.data.min_ini,pre_reserva.data.hora_fim,pre_reserva.data.min_fim,pre_reserva.tipo)==-1){
                    return -1;
                }
            }
            if(!verifica_duplos(lista_pre_reservas,pre_reserva)) {
                insere(lista_pre_reservas, pre_reserva); //insere na lista de pre-reservas
            }
        }else{
            return -1;
        }
    }
    fclose(arquivo);//fecha o ficheiro
    return 1;
}

int write_file(typeLista* lista_reservas, typeLista* lista_pre_reservas, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w"); //abre o ficheiro como escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return -1;
    }
    //percorre a lista de reservas
    noLista* atual = lista_reservas->inicio;
    while (atual != NULL) {
        //escreve cada reserva existente da lista reservas no ficheiro com o formato utilizado no "fprintf"
        Reserva reserva = atual->reserva;
        fprintf(arquivo, "r#%s#%d#%d#%d#%d#%d#%d#%d#%d#%s\n",
                reserva.cliente.nome, reserva.cliente.numero,
                reserva.data.dia, reserva.data.mes, reserva.data.ano,
                reserva.data.hora_ini, reserva.data.min_ini,reserva.data.hora_fim, reserva.data.min_fim,
                reserva.tipo);
        atual = atual->prox;
    }
    //percorre a lista de pre-reservas
    atual = lista_pre_reservas->inicio;
    while (atual != NULL) {
        //escreve cada pre-reserva existente da lista pre-reservas no ficheiro com o formato utilizado no "fprintf"
        Reserva pre_reserva = atual->reserva;
        fprintf(arquivo, "p#%s#%d#%d#%d#%d#%d#%d#%d#%d#%s\n",
                pre_reserva.cliente.nome, pre_reserva.cliente.numero,
                pre_reserva.data.dia, pre_reserva.data.mes, pre_reserva.data.ano,
                pre_reserva.data.hora_ini, pre_reserva.data.min_ini,pre_reserva.data.hora_fim, pre_reserva.data.min_fim,
                pre_reserva.tipo);
        atual = atual->prox;
    }
    fclose(arquivo);//fecha o ficheiro
    return 1;
}

int listar(typeLista* lista, const int tipo_lista) {
    int contador=1;
    noLista* aux = lista->inicio;
    if (tipo_lista == 1) {
        if(vazia(lista)){
            return -1;
        }else {
            printf("\nLista de Reservas:\n");
            while (aux != NULL) {
                printf("\t%d.\n",contador);
                printf("\tCliente: %s\n", aux->reserva.cliente.nome);
                printf("\tNumero: %d\n", aux->reserva.cliente.numero);
                printf("\tData: %d/%d/%d\n", aux->reserva.data.dia, aux->reserva.data.mes, aux->reserva.data.ano);
                printf("\tHora inicio: %02d:%02d\n",aux->reserva.data.hora_ini, aux->reserva.data.min_ini);
                printf("\tHora fim: %02d:%02d\n",aux->reserva.data.hora_fim, aux->reserva.data.min_fim);
                printf("\tTipo: %s\n", aux->reserva.tipo);
                printf("\n");
                aux = aux->prox;
                contador++;
            }
        }
    } else if (tipo_lista == 2) {
        if(vazia(lista)){
            return -2;
        }else {
            printf("\nLista de Pre-Reservas:\n");
            while (aux != NULL) {
                printf("\t%d.\n",contador);
                printf("\tCliente: %s\n", aux->reserva.cliente.nome);
                printf("\tNumero: %d\n", aux->reserva.cliente.numero);
                printf("\tData: %d/%d/%d\n", aux->reserva.data.dia, aux->reserva.data.mes, aux->reserva.data.ano);
                printf("\tHora inicio: %02d:%02d\n",aux->reserva.data.hora_ini, aux->reserva.data.min_ini);
                printf("\tHora fim: %02d:%02d\n",aux->reserva.data.hora_fim, aux->reserva.data.min_fim);
                printf("\tTipo: %s\n", aux->reserva.tipo);
                printf("\n");
                aux = aux->prox;
                contador++;
            }
        }
    }
    return 1;
}

int receber_pedido(typeLista* lista_reservas, typeLista* lista_pre_reservas,const char *tipo_tarefa){
    int verificacao_pedido;
    char entrada[100];
    Reserva *reserva= (Reserva*)malloc(sizeof(Reserva)); //aloca memória para uma nova reserva
    if (reserva == NULL) {
        printf("Erro ao alocar memória.\n");
        return -1;
    }
    printf("Digite 'QUIT' caso pretenda voltar para o Menu\n");
    //lê todos os dados necessários da consola para o preenchimento dos campos da reserva
    printf("Nome do cliente: ");
    fgets(reserva->cliente.nome, sizeof(reserva->cliente.nome), stdin);
    reserva->cliente.nome[strcspn(reserva->cliente.nome, "\n")] = '\0';
    if(!strcmp(reserva->cliente.nome,"QUIT")){
        return -1;
    }

    while(!so_letras(reserva->cliente.nome) || !strlen(reserva->cliente.nome)){
        printf("O nome nao pode conter caracteres especiais.\n");
        fflush(stdin);
        printf("Nome do cliente: ");
        fgets(reserva->cliente.nome, sizeof(reserva->cliente.nome), stdin);
        reserva->cliente.nome[strcspn(reserva->cliente.nome, "\n")] = '\0';
        if(!strcmp(reserva->cliente.nome,"QUIT")){
            return -1;
        }
    }
    printf("Numero do cliente: ");
    fflush(stdin);
    fgets(entrada, 30, stdin);
    entrada[strcspn(entrada, "\n")] = '\0';
    if(!strcmp(entrada,"QUIT")){
        return -1;
    }
    while(!so_numeros(entrada) || !strlen(entrada)){
        printf("O nome nao pode conter caracteres especiais.\n");
        fflush(stdin);
        printf("Numero do cliente: ");
        fgets(entrada, 30, stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
        if(!strcmp(entrada,"QUIT")){
            return -1;
        }
    }
    reserva->cliente.numero=atoi(entrada);
    fflush(stdin);
    int verifica_hora;
    strcpy(reserva->tipo,tipo_tarefa);
    verifica_hora=lerDataHora(&reserva->data.dia,&reserva->data.mes,&reserva->data.ano,&reserva->data.hora_ini,
                              &reserva->data.min_ini,&reserva->data.hora_fim,&reserva->data.min_fim,tipo_tarefa);
    if(verifica_hora==-1){
        return -1;
    }
    verificacao_pedido=reservar(lista_reservas,lista_pre_reservas,reserva);

    return verificacao_pedido;

}

int listar_cliente(typeLista* lista, const int tipo_lista,const char *nome_cliente){
    int contador=0;
    noLista* aux = lista->fim;
    if (tipo_lista == 1) {
        if(vazia(lista)){
            return -1;
        }else {
            while (aux != NULL) {
                if(!strcmp(aux->reserva.cliente.nome,nome_cliente)){
                    contador++;
                    if(contador==1){
                        printf("\nLista de Reservas do cliente %s:\n",nome_cliente);
                    }
                    printf("\tData: %d/%d/%d\n", aux->reserva.data.dia, aux->reserva.data.mes, aux->reserva.data.ano);
                    printf("\tHora inicio: %02d:%02d\n",aux->reserva.data.hora_ini, aux->reserva.data.min_ini);
                    printf("\tHora fim: %02d:%02d\n",aux->reserva.data.hora_fim, aux->reserva.data.min_fim);
                    printf("\tTipo: %s\n", aux->reserva.tipo);
                    printf("\n");
                }
                aux = aux->ant;
            }
        }
    } else if (tipo_lista == 2) {
        if(vazia(lista)){
            return -2;
        }else {
            while (aux != NULL) {
                if(!strcmp(aux->reserva.cliente.nome,nome_cliente)){
                    contador++;
                    if(contador==1){
                        printf("\nLista de Pre-Reservas do cliente %s:\n",nome_cliente);
                    }
                    printf("\tData: %d/%d/%d\n", aux->reserva.data.dia, aux->reserva.data.mes, aux->reserva.data.ano);
                    printf("\tHora inicio: %02d:%02d\n",aux->reserva.data.hora_ini, aux->reserva.data.min_ini);
                    printf("\tHora fim: %02d:%02d\n",aux->reserva.data.hora_fim, aux->reserva.data.min_fim);
                    printf("\tTipo: %s\n", aux->reserva.tipo);
                    printf("\n");
                }
                aux = aux->ant;
            }
        }
    }
    return contador;
}

int cancelar_pre_reserva(typeLista* lista_pre_reservas, int indice_elemento_eliminar){
    int contador=1;
    if (lista_pre_reservas == NULL || lista_pre_reservas->inicio == NULL) {
        // Verifica se a lista está vazia
        return 0; // Retorna 0 para indicar falha
    }
    noLista* atual = lista_pre_reservas->inicio;
    while (atual != NULL) {
        if (contador==indice_elemento_eliminar) {
            // Encontrou uma reserva do tipo desejado
            if (atual == lista_pre_reservas->inicio && atual == lista_pre_reservas->fim) {
                // A lista possui apenas um elemento
                lista_pre_reservas->inicio = NULL;
                lista_pre_reservas->fim = NULL;
            } else if (atual == lista_pre_reservas->inicio) {
                // A reserva está no início da lista
                lista_pre_reservas->inicio = atual->prox;
                atual->prox->ant = NULL;
            } else if (atual == lista_pre_reservas->fim) {
                // A reserva está no fim da lista
                lista_pre_reservas->fim = atual->ant;
                atual->ant->prox = NULL;
            } else {
                // A reserva está no meio da lista
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
            }

            free(atual); // Libera a memória do nó removido
            return 1; // Retorna 1 para indicar sucesso
        }
        contador++;
        atual = atual->prox;
    }
    return -1;
}

void encaixa_pre_reserva(typeLista* lista_reservas,typeLista* lista_pre_reservas) {
    int contador_pre_reservas=1;
    bool flag;
    noLista *aux_p = lista_pre_reservas->inicio;
    noLista *aux_r;
    while (aux_p != NULL) {// percorre a lista de pre-reservas
        flag = 1;
        aux_r = lista_reservas->inicio;
        while (aux_r != NULL) { // percorre a lista de reservas
            //se a pre-reserva criou conflito com alguma reserva a flag fica a 0 significando que não é possível inseri-la na lista de reservas
            if (verifica_disponibilidade(aux_r->reserva.data, aux_p->reserva.data) == false) {
                flag = 0;
                break;
            }
            aux_r = aux_r->prox;
        }
        if (flag) {// caso a flag tenha permanecido a 1, quer dizer que não foram encontrados conflitos e a pré-reserva vai ser inserida na lista de reservas
            insere(lista_reservas, aux_p->reserva);
            printf("\nA seguinte pre-reserva e compativel com a data da reserva cancelada.\n\tCliente: %s\n\tNumero: %d\n\tData: %d/%d/%d\n\tHora inicio: %d:%d\n\tHora fim: %d:%d\n\tTipo: %s\nEsta foi adicionada a lista de reservas\n",
                   aux_p->reserva.cliente.nome, aux_p->reserva.cliente.numero, aux_p->reserva.data.dia,
                   aux_p->reserva.data.mes, aux_p->reserva.data.ano, aux_p->reserva.data.hora_ini,
                   aux_p->reserva.data.min_ini, aux_p->reserva.data.hora_fim, aux_p->reserva.data.min_fim,
                   aux_p->reserva.tipo);
            cancelar_pre_reserva(lista_pre_reservas, contador_pre_reservas);
        }
        aux_p = aux_p->prox;
        contador_pre_reservas++;
    }
}

int cancelar_reserva(typeLista* lista_reservas,typeLista* lista_pre_reservas, int indice_elemento_eliminar){
    int contador=1;

    noLista* atual = lista_reservas->inicio;
    while (atual != NULL) {
        if (contador==indice_elemento_eliminar) {
            // Encontrou uma reserva do tipo desejado
            if (atual == lista_reservas->inicio && atual == lista_reservas->fim) {
                // A lista possui apenas um elemento
                lista_reservas->inicio = NULL;
                lista_reservas->fim = NULL;
            } else if (atual == lista_reservas->inicio) {
                // A reserva está no início da lista
                lista_reservas->inicio = atual->prox;
                atual->prox->ant = NULL;
            } else if (atual == lista_reservas->fim) {
                // A reserva está no fim da lista
                lista_reservas->fim = atual->ant;
                atual->ant->prox = NULL;
            } else {
                // A reserva está no meio da lista
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
            }
            free(atual); // Libera a memória do nó removido
            printf("\nA reserva foi cancelada com sucesso\n");
            encaixa_pre_reserva(lista_reservas,lista_pre_reservas);
            return 1; // Retorna 1 para indicar sucesso
        }
        contador++;
        atual = atual->prox;
    }
    return -1;
}


