/* 
 * File:   main.c
 * Author: Daniel
 *
 * Created on 8 de Julho de 2013, 11:39
 */

//bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Definições.

#define MAXINS 100 //Numero maximo de Memoria de instruções.
#define MAXINSTRU 4 //Numero maximo de instruções e para gerar um Opcode.
#define MAXHD 10240000 //passar tamnho para KB depois NÂO ESQUECER!!!!
#define MAXMEMO 524288 //'512MB'//1048576'1GB' //16384'16MB' //8192'8MB'//65536'64MB' //Tamanho maximo da memoria RAM em KB's. 512MB, 1GB, 2GB, 4GB, 8GB, variando de acordo com a necessidade. 
#define TAML1 8   //Tamanho da memoria cache L1 em KB's, pode ser de 16KB, 32KB, 64KB e 128KB na atualidade. 
#define TAML2 16  //Tamanho da memoria cache L2 em KB's, pode ser de 256KB, 512KB, 1MB e 2MB na atualidade. 
#define TAML3 124  //Tamanho da memoria cache L3 em KB's, pode não ter ou ser de 2MB, 3MB, 4MB, 6MB, 8MB, 10MB, 12MB na faixa pra uso domestico.
#define LINHAS 4 // É o K na formula, Quantidade de linhas por grupo para associatividade por conjuto, pode ser 2, 4, 8, 16.
#define LINHA 64 //Cada linha tem o tamanho de 64bytes, mas pode ser definir outros valores também sempre 2^n o tamanho.

//definições para gerar um codigo aleotirio com laço de repetição
#define TAMFOR 50 //Tamanho do laço de repetição
#define PROP_FOR 30 // Esse valor indica a probabilidade de ter um laço de repetição na instrução.

//Variaveis Globais.

float Disco[MAXHD];
int cacheL1_miss;
int cacheL2_miss;
int cacheL3_miss;
int cacheL1_hit;
int cacheL2_hit;
int cacheL3_hit;
int V_L1, V_L2, V_L3, J_L1, J_L2, J_L3, I_L1, I_L2, I_L3;
int aux1, aux2, aux3;


//Definições de tipos.

typedef struct Processador{

    int PC;
    int MAR;
    float MBR;
    int IR;

}CPU;

typedef struct Memoria_Instrucao{

   int instrucao;
   int posmen;

}TOpcodes;

typedef struct Sinal{
    
   float sinal;
   
}TSinal;

typedef struct{
    
    float dado;
    int endereco;
    
}Dado;

typedef struct{
    
    Dado Palavra[LINHAS];
    int end_bloco;
    int flag;
       
}Linha;

typedef struct{

    Linha linha;
         
}Conjunto;

//Funções.

void Alocar_Dados(float* Memoria);                    //preenche memoria de dados "RAM" 
void Preencher_Instrucao(TOpcodes* PMemoria);         //preenche memoria de instrução, mas de forma totalmente aleatoria.
void Preencher_Instrucao_Lacos(TOpcodes* PMemoria);   //preenche memoria de instrução, mas com parte aleatoria e parte com laços de repetições.
void MMU(CPU* CPU1 , Conjunto* L1, Conjunto* L2, Conjunto* L3, float Memoria[]);
void Invalida_Cache(Conjunto *cache, int n);          //preenche todas em todas as linhas da cache, no campo endereço de bloco com o valor -1. indca que linha está vazia

//Principal

int main(int argc, char** argv) {

//Estruturas.
    
     CPU *CPU1;
     TOpcodes *Instrucao;
     Conjunto *Cache_L1=NULL;
     Conjunto *Cache_L2=NULL;
     Conjunto *Cache_L3=NULL;

//Variaveis locais.
     
    int M,aux;
              
//Ponteiros.
    
    float *Memoria;
    
//Calculos para algumas definições quantas palavras  memoria RAM e conjutos na Cache.

    M=MAXMEMO*1024/LINHA; //LINHA tambem simula o tamanho de cada palavra na da memoria RAM.
    
    //obter o numero de conjuntos em cada cache.    
    V_L1 = (TAML1*1024)/(LINHA*LINHAS);
    V_L2 = (TAML2*1024)/(LINHA*LINHAS);
    V_L3 = (TAML3*1024)/(LINHA*LINHAS);
        
//alocação dinamica
    
    CPU1 = (CPU*)malloc(sizeof(CPU));
    //Aloca memoria RAM como palavras.
    Memoria =( float*)malloc(sizeof(float)*M);
    //Aloca memorias Cache com o numero de conjuntos ja calulados.
    Cache_L1 = (Conjunto*)calloc(V_L1,sizeof(Conjunto));    
    Cache_L2 = (Conjunto*)calloc(V_L2,sizeof(Conjunto));
    Cache_L3 = (Conjunto*)calloc(V_L3,sizeof(Conjunto));
    
    //Criando as linhas do opcode.
    Instrucao = (TOpcodes*)calloc(MAXINS,sizeof(TOpcodes));
    
    //invalidando todos os campos de endereços das linhas das cache.
    Invalida_Cache(Cache_L1, V_L1);
    Invalida_Cache(Cache_L2, V_L2);
    Invalida_Cache(Cache_L3, V_L3);

//inicializando variaveis.
   CPU1->IR = -1;
   CPU1->PC = -1;
   CPU1->MAR = -1;
   CPU1->MBR = -1;
   cacheL1_miss = 0;
   cacheL2_miss = 0; 
   cacheL3_miss = 0;
   cacheL1_hit = 0;
   cacheL2_hit = 0;
   cacheL3_hit = 0;
   
//Preenchendo memória de dados e instrução.

Preencher_Instrucao_Lacos(Instrucao);   
//Preencher_Instrucao(Instrucao);
Alocar_Dados(Memoria);

/* Opcodes das intruções:
* 0: Envia dados se já codificados(Esses dados tem que estar na frequencia 10,700 a 12,500 GHZ ) .
* 1: Busca novo dado no receptor(Pode ser um dado em qualquer frequencia e guarda na memoria).
* 2: Codifica dados e retorna para memoria principal.
* 3: Armazena dados codificados ou não em disco.
* 4: Encerrar.
*/

//Emulando processamento.

   while(CPU1->IR != 4){
       CPU1->PC++;
       CPU1->IR=Instrucao[CPU1->PC].instrucao;
       CPU1->MAR=Instrucao[CPU1->PC].posmen;
       MMU(CPU1, Cache_L1, Cache_L2, Cache_L3, Memoria);
     
   }
//imprimindo resultados
printf("\n L1 miss %d, L2 miss %d, L3 miss %d\n L1_hit %d, L2_hit %d, L3_hit %d \n",cacheL1_miss,cacheL2_miss,cacheL3_miss, cacheL1_hit, cacheL2_hit, cacheL3_hit);

//liberando memorias alocadas dinamicamente.
   free(Instrucao);
   free(CPU1);
   free(Memoria);
   free(Cache_L1);
   free(Cache_L2);
   free(Cache_L3);
   
system("PAUSE");
   return 0;
}

void Preencher_Instrucao(TOpcodes* PMemoria){
   int i;
   int n=MAXINS;
   srand(time(NULL));
   for(i=0; i <=n ; i++){
      if(i < n ){
           PMemoria[i].instrucao=rand()%MAXINSTRU;
           PMemoria[i].posmen=rand()%MAXMEMO*1024/LINHA;
      }
      else{
           PMemoria[i].instrucao=4;
           PMemoria[i].posmen=-1;
      }
   }
}

void Preencher_Instrucao_Lacos(TOpcodes* PMemoria){
   
   TOpcodes * AUX;
   int i, j, sorteio;
   int n=MAXINS;
   srand(time(NULL));
   
   //Gerando um laço de repetição de tamanho igual a TAMFOR.
   AUX =(TOpcodes*)malloc(sizeof(TOpcodes)*TAMFOR); 
   
   for(i=0; i < TAMFOR ; i++){
           AUX[i].instrucao=rand()%MAXINSTRU;
           AUX[i].posmen=rand()%MAXMEMO*1024/LINHA;
           printf("\n valor de endereco: %d",AUX[i].posmen);
   }
      
   for(i=0; i <n ;){
       sorteio = rand()%100+1;
       if(sorteio <= PROP_FOR){
          for(j=0; j <TAMFOR; j++, i++){
              if(i == n-1){
                  PMemoria[i].instrucao = 4;
                  PMemoria[i].posmen=0;
                  i++;
                  break;
              }    
              PMemoria[i].instrucao = AUX[j].instrucao;
              PMemoria[i].posmen = AUX[j].posmen;
          }                       
       }
       else if(i < n-1 ){
              PMemoria[i].instrucao=rand()%MAXINSTRU;              
              PMemoria[i].posmen=rand()%MAXMEMO*1024/LINHA;
              i++;
       } 
             else{
                 PMemoria[i].instrucao=4;
                 PMemoria[i].posmen=-1;
                }
   }
   //printf("\n valor de i %d",i);
   getchar();
   free(AUX);
}

void Alocar_Dados(float Memoria[]){
   int i=0;
   srand(time(NULL));
   for(i=0; i<=(MAXMEMO*1024/LINHA); i++){
       Memoria[i] = rand()%3100 /100.0;
       //printf("%d %f\n",i, Memoria[i]);
   }
} 

void Invalida_Cache(Conjunto *cache, int n){
   
   int i;

   for(i=0; i<n; i++){
       cache->linha.end_bloco = -1;
       cache->linha.flag = 0;
   }
}

void MMU(CPU* CPU , Conjunto* L1, Conjunto* L2, Conjunto* L3, float Memoria[]){
   
     srand(time(NULL));
    //estruturas
     TSinal Saida;
     TSinal Entrada;
     Linha aux;
     
    //variaveis locais    
    int i, endereco, dado, auxrand;
    int I_aux, hit_aux1=0, hit_aux2=0, hit_aux3=0;
    
    //variaveis recebem o que procurar na cache
    endereco = CPU->MAR;
    //dado = CPU->MBR;
    
    
    //Calculos para saber qual é palavra, o bloco e linha da cache1
    aux1 = endereco%LINHA;
    J_L1 = endereco /LINHA; 
    I_L1 = J_L1 % V_L1;
    
    //Calculos para saber qual é palavra, o bloco e linha da cache2
    aux2 = endereco%LINHA;
    J_L2 = endereco /LINHA;
    I_L2 = J_L2 % V_L2;
    
    //Calculos para saber qual é palavra, o bloco e linha da cache1
    aux3 = endereco%LINHA;
    J_L3 = endereco /LINHA;
    I_L3 = J_L3 % V_L3;
        
    
    //Verificando se dado esta ou não na cache.
    
    //verifica na cache1.
    if(L1[I_L1].linha.end_bloco == J_L1){  
            cacheL1_hit++;
            hit_aux1=1;
            L1[I_L1].linha.flag++;
            dado = L1[I_L1].linha.Palavra[aux1].dado;
        }
        //verifica na cache2.
        else if(L2[I_L2].linha.end_bloco == J_L2){
             cacheL1_miss++;
             cacheL2_hit++;
             hit_aux2=1;
             L2[I_L2].linha.flag++;
             dado = L2[I_L2].linha.Palavra[aux2].dado;
             I_aux = L2[I_L2].linha.end_bloco %V_L1;
                    if(L1[I_aux].linha.end_bloco == -1){ //verifica se a linha ta vazia
                          L1[I_aux].linha = L3[I_L3].linha;
                    }   
                       else { //se existe algum bloco na linha if(L1[I_L1].linha.end_bloco != -1) 
                              aux = L1[I_L1].linha;      
                              L1[I_L1].linha.end_bloco = J_L1;
                              L1[I_L1].linha = L3[I_L3].linha;
                              dado = L1[I_L1].linha.Palavra[aux1].dado;
                              //como atualizar as outras caches.
                              I_aux = aux.end_bloco %V_L2 ;
                              //printf("\n %d, bloco da ram %d ", I_aux, aux.end_bloco);
                              if(L2[I_aux].linha.end_bloco == -1)
                                    L2[I_aux].linha = aux;                             
                              else if(L2[I_aux].linha.end_bloco != -1){
                                      if(L2[I_aux].linha.flag > aux.flag){
                                          I_aux = aux.end_bloco %V_L3;
                                          if(L3[I_aux].linha.end_bloco == -1)
                                              L3[I_aux].linha = aux;
                                          else if(L3[I_aux].linha.end_bloco != -1)
                                                  if(L3[I_aux].linha.flag < aux.flag)
                                                     L3[I_aux].linha = aux;
                                      }
                                      I_aux = aux.end_bloco %V_L2;
                                      if(L2[I_aux].linha.flag < aux.flag){
                                          Linha troca;
                                          troca = L2[I_aux].linha;
                                          L2[I_aux].linha = aux;
                                          aux = troca;
                                          I_aux = aux.end_bloco %V_L3;
                                          if(L3[I_aux].linha.end_bloco == -1)
                                              L3[I_aux].linha = aux;
                                          else if(L3[I_aux].linha.end_bloco != -1)
                                                 if(L3[I_aux].linha.flag < aux.flag)
                                                     L3[I_aux].linha = aux;
                                     }
                                  
                             }
                       }  
                  }
            //verifica na cache3.
            else if(L3[I_L3].linha.end_bloco == J_L3){
                    cacheL1_miss++;
                    cacheL2_miss++;
                    cacheL3_hit++;
                    hit_aux3=1;
                    L3[I_L3].linha.flag++;
                    dado = L3[I_L3].linha.Palavra[aux3].dado;
                    I_aux = L3[I_L3].linha.end_bloco %V_L1;
                    if(L1[I_aux].linha.end_bloco == -1){ //verifica se a linha ta vazia
                          L1[I_aux].linha = L3[I_L3].linha;
                    }   
                       else { //se existe algum bloco na linha if(L1[I_L1].linha.end_bloco != -1) 
                              aux = L1[I_L1].linha;      
                              L1[I_L1].linha.end_bloco = J_L1;
                              for(i=0; i<LINHAS; i++)
                              L1[I_L1].linha.Palavra[i].dado= Memoria[(J_L1*4)+i];
                              dado = L1[I_L1].linha.Palavra[aux1].dado;
                              //como atualizar as outras caches.
                              I_aux = aux.end_bloco %V_L2 ;
                              //printf("\n %d, bloco da ram %d ", I_aux, aux.end_bloco);
                              if(L2[I_aux].linha.end_bloco == -1)
                                    L2[I_aux].linha = aux;                             
                              else if(L2[I_aux].linha.end_bloco != -1){
                                      if(L2[I_aux].linha.flag > aux.flag){
                                          I_aux = aux.end_bloco %V_L3;
                                          if(L3[I_aux].linha.end_bloco == -1)
                                              L3[I_aux].linha = aux;
                                          else if(L3[I_aux].linha.end_bloco != -1)
                                                  if(L3[I_aux].linha.flag < aux.flag)
                                                     L3[I_aux].linha = aux;
                                      }    
                                      I_aux = aux.end_bloco %V_L2;
                                      if(L2[I_aux].linha.flag < aux.flag){
                                          Linha troca;
                                          troca = L2[I_aux].linha;
                                          L2[I_aux].linha = aux;
                                          aux = troca;
                                          I_aux = aux.end_bloco %V_L3;
                                          if(L3[I_aux].linha.end_bloco == -1)
                                              L3[I_aux].linha = aux;
                                          else if(L3[I_aux].linha.end_bloco != -1)
                                                 if(L3[I_aux].linha.flag < aux.flag)
                                                     L3[I_aux].linha = aux;
                                     }
                                  
                             }
                       }  
                  }
                  //caso não encontrou all cache miss.
                  else{
                       cacheL1_miss++;
                       cacheL2_miss++;
                       cacheL3_miss++;
                  //Colocar dado da memoria RAM na Cache
                 
                       if(L1[I_L1].linha.end_bloco == -1){ //verifica se a linha ta vazia
                          L1[I_L1].linha.end_bloco = J_L1; //linha recebe o endereco do bloco
                          for(i=0; i<LINHAS; i++)
                          L1[I_L1].linha.Palavra[i].dado= Memoria[(J_L1*4)+i]; //cada posição da linha recebe uma palavra do bloco
                          dado = L1[I_L1].linha.Palavra[aux1].dado;  //o MBR recebe a palavra do bloco da RAM.
                          L1[I_L1].linha.flag++;
                     }   
                       else { //se existe algum bloco na linha if(L1[I_L1].linha.end_bloco != -1) 
                              aux = L1[I_L1].linha;      
                              L1[I_L1].linha.end_bloco = J_L1;
                              for(i=0; i<LINHAS; i++)
                              L1[I_L1].linha.Palavra[i].dado= Memoria[(J_L1*4)+i];
                              dado = L1[I_L1].linha.Palavra[aux1].dado;
                              L1[I_L1].linha.flag++;
                              //como atualizar as outras caches.
                              I_aux = aux.end_bloco %V_L2;
                              //printf("\n %d, bloco da ram %d ", I_aux, aux.end_bloco);
                              if(L2[I_aux].linha.end_bloco == -1)
                                    L2[I_aux].linha = aux;                             
                              else if(L2[I_aux].linha.end_bloco != -1){
                                      if(L2[I_aux].linha.flag > aux.flag){
                                          I_aux = aux.end_bloco %V_L3;
                                          if(L3[I_aux].linha.end_bloco == -1)
                                              L3[I_aux].linha = aux;
                                          else if(L3[I_aux].linha.end_bloco != -1)
                                                  if(L3[I_aux].linha.flag < aux.flag)
                                                     L3[I_aux].linha = aux;
                                      } 
                                      I_aux = aux.end_bloco %V_L2;
                                      if(L2[I_aux].linha.flag < aux.flag){
                                             Linha troca;
                                             troca = L2[I_aux].linha;
                                             L2[I_aux].linha = aux;
                                             aux = troca;
                                             I_aux = aux.end_bloco %V_L3;
                                             if(L3[I_aux].linha.end_bloco == -1)
                                                 L3[I_aux].linha = aux;
                                             else if(L3[I_aux].linha.end_bloco != -1)
                                                    if(L3[I_aux].linha.flag < aux.flag)
                                                       L3[I_aux].linha = aux;
                                     }
                                  
                             }  
                       }
              }
    CPU->MBR= dado;
  //simulação do processamento.          
    switch (CPU->IR)
       {
           case 0: if(CPU->MBR >= 10.700 && CPU->MBR <= 12.500){
                   Saida.sinal = CPU->MBR;
                   printf("\n %d %.5f", CPU->IR, Saida.sinal);}
                   break;
           case 1: Entrada.sinal = rand()%3100 /100.0;
                   CPU->MBR = Entrada.sinal;
                   Memoria[CPU->MAR]=CPU->MBR;
                   if (hit_aux2 == 1)
                   L1[I_L1].linha.Palavra[aux2].dado =CPU->MBR ;
                   else if (hit_aux3 == 1)
                            L1[I_L1].linha.Palavra[aux3].dado=CPU->MBR;
                        else
                            L1[I_L1].linha.Palavra[aux1].dado=CPU->MBR;
                   printf("\n %d %.5f", CPU->IR, Memoria[CPU->MAR]);
                   break;
           case 2: if(CPU->MBR <= 10.699 || CPU->MBR >= 12.501){
                   CPU->MBR= (rand() %1000) +11000.0 ;
                   Memoria[CPU->MAR]= CPU->MBR;
                   if (hit_aux2 == 1)
                   L1[I_L1].linha.Palavra[aux2].dado =CPU->MBR ;
                   else if (hit_aux3 == 1)
                            L1[I_L1].linha.Palavra[aux3].dado=CPU->MBR;
                        else
                            L1[I_L1].linha.Palavra[aux1].dado=CPU->MBR;
                   printf("\n %d %.5f", CPU->IR, Memoria[CPU->MAR]);}
                   break;
           case 3: auxrand=rand()%MAXHD;
                   Disco[auxrand]= CPU->MBR;
                   printf("\n %d %.5f", CPU->IR, CPU->MBR);
                   break;
       }

//free(aux);
}
/*
 int Tfila_vazia (tfila *fila)
 * return fila->inicio == fila->fim;
 int i, j=0;
 void tfila_push(tfila *fila. int x)
 * if((fila->fim) +1) % fila->tamMax == fila->inicio)
 * fila->tamMax =*2;
 * int *vaux = (int*)malloc(sizeof(int)*fila->tamMax * 2)
 * for(i = fila->incio; i!= fila->fim; i = (i+1) % fila->tamMax)
 *  vaux[j]= fila->[i];
 *   j++;
 * 
 * fila->V[fila->fim] =x;
 * fila->tam++;
 * fila->fim = (fila->fim+1)%fila->tamMax;
 * if(fila->fim + 1 < fila->tamMax)
 *   fila->fim++;
 * else
 *   
 

 */

 /*if(aux.TAG != -1){
			for (int j=0; j<l; j++)
			{
				if ( Cache3[linha2].Linha[j].TAG == aux.TAG )
				{
					Cache3[linha2].Linha[j] = aux ;
				}
				if ( Cache3[linha2].Linha[j].acesso < aux.acesso )
				{
					aux2 = Cache3[linha2].Linha[j];
					Cache3[linha2].Linha[j] = aux ;
					aux2 = aux ;
				}
			}
                        }
						 */