#ifndef SIMULADOR_JOGOS_H
#define SIMULADOR_JOGOS_H
#include<iostream>
#include<cstdlib>
#include<string>
#define NComodos 6
#define TAM_Cache1 1
#define TAM_Cache2 10
#define TAM_Cache3 500
#define TAM_MEM 100000
#define NUM_INS 10000000
using namespace std;


// Estrutura da casa

typedef struct {
    string nome;
    int portas;
    int janelas;
    int luz;

}TComodo;

typedef struct {
    TComodo *comodos;
}TCasa;

// Estrutura da Memória

typedef struct {
    int PC;
    int IR; // Registrador com o OPcode
    int MAR; // Registrador com o Endereço
    int MBR;
    int MBR_Palavra; // Feito para fins didáticos
    int MBR_Comodo; // Feito para fins didáticos
}TProcessador;


typedef struct {
    TCasa palavra[4];
}TBloco;

typedef struct {
    TBloco *linhas;
    int *EnderecoLinhas;
    int *TempoEmCache;
    int *FrequenciaDeUso;
    int *Modificou; 		// Bit para informar se o dado inserido foi modificado ou não
    int CacheHit, CacheMiss;
}MCache;

typedef struct {
    TBloco *Blocos;
}Memoria;

    // Funções de iniciar a memória

void IniciaCasa(TCasa*);
void IniciaCPU(TProcessador *CPU);
void IniciaMemoriaCache1(MCache*);
void IniciaMemoriaCache2(MCache*);
void IniciaMemoriaCache3(MCache*);
void IniciaMemoriaPrincipal(Memoria*);

    // Funções de apagar a memória

void ApagaCasa(TCasa*);
void ApagaMemoriaCache1(MCache*);
void ApagaMemoriaCache2(MCache*);
void ApagaMemoriaCache3(MCache*);
void ApagaMemoriaPrincipal(Memoria*);

    // Funções de procura

int Procura_Cache(MCache*, int, int);
bool Procura_RAM(int);
int Procura_Memoria(MCache*, MCache*, MCache*, int);

    // Funções de escrita

void Escreve_Memoria(MCache*, MCache*, MCache*, Memoria*, int, int, int, int);
void Situacao_Comodo(MCache, MCache, MCache, Memoria, int, int, int);
void cout_Comodo_CacheOuRAM(MCache, Memoria, int, int, int, int, int);
void Encontrou_Cache1(MCache*, int, int, int, int);
void Encontrou_Cache2(MCache*, MCache*, int);
int Encontrou_Cache3(MCache*, MCache*, int);
int Encontrou_RAM(MCache*, Memoria*, int);

    // Funções extras

void AddTempoEmCache(MCache*, int);

#endif