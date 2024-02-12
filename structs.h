#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int dia,mes,ano,hora_ini,min_ini,hora_fim,min_fim;
} Data;

typedef struct {
    int numero;
    char nome [50];
} Cliente;

typedef struct{
    Cliente cliente;
    Data data;
    char tipo[20];
}Reserva;

typedef struct noLista {
    Reserva reserva;
    struct noLista * ant;
    struct noLista * prox;
} noLista;

typedef struct{
    noLista *inicio;
    noLista *fim;
}typeLista;


int so_letras(char * string);

int so_numeros(char *string);

int compara_data(Data d1, Data d2);

bool verifica_disponibilidade(Data d1, Data d2);

int verifica_data_hora(int dia, int mes, int ano, int hora_ini, int minuto_ini, int hora_fim, int minuto_fim,const char *tipo_tarefa);

int lerDataHora(int *dia, int *mes, int *ano, int *hora_ini, int *minuto_ini, int *hora_fim, int *minuto_fim, const char *tipo_tarefa);

typeLista cria();

int vazia(typeLista *lista);

void destroi(typeLista *lista);

int verifica_duplos(typeLista* lista, Reserva elemento_inserir);

void insere(typeLista* lista, Reserva elemento_inserir);

int reservar(typeLista* lista_reservas, typeLista* lista_pre_reservas,Reserva *elemento_reservar);

int pop_tarefa(typeLista* lista_reservas, const char *tipo_tarefa);

int read_file(typeLista* lista_reservas, typeLista* lista_pre_reservas, const char* nome_arquivo);

int write_file(typeLista* lista_reservas, typeLista* lista_pre_reservas, const char* nome_arquivo);

int listar(typeLista* lista, const int tipo_lista);

int receber_pedido(typeLista* lista_reservas, typeLista* lista_pre_reservas,const char *tipo_tarefa);

int listar_cliente(typeLista* lista, const int tipo_lista,const char *nome_cliente);

int cancelar_pre_reserva(typeLista* lista_pre_reservas, int indice_elemento_eliminar);

void encaixa_pre_reserva(typeLista* lista_reservas,typeLista* lista_pre_reservas);

int cancelar_reserva(typeLista* lista_reservas,typeLista* lista_pre_reservas, int indice_elemento_eliminar);

#endif