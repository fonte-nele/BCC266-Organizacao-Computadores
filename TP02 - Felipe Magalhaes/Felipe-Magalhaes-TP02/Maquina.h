#ifndef MAQUINA_H
#define MAQUINA_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;
#define TAM_INST 1000 //Memoria intrucoes
#define DADOS_TAM 100 // Memoria Dados
#define RAM_TAM 50 // Tamanho RAM
#define L1_TAM 8 // Tamanho Cache 1
#define L2_TAM 16 // Tamanho Cache 2
#define NUM_OPCODE 3
#define TAM_FOR 10
#define PROBAB 70

typedef struct{
	int OPCode; //IR
	int End1; //MAR1
	int End2; //MAR2
}MInstrucao;

typedef struct{
	int quantidade;
	int End;
	int LFU; // em Cache
}TMemoria;

extern int RAMHits;
extern int L1Hits;
extern int L2Hits;

void preencheMenuInstrucao(MInstrucao**);

void criarMaquina (TMemoria**, TMemoria**, TMemoria**, MInstrucao**);
void deletarMaquina (TMemoria**, TMemoria**, TMemoria**, MInstrucao**);

int MMU (TMemoria*, TMemoria*, TMemoria*, int);

string resultado(string,string,int);

#endif