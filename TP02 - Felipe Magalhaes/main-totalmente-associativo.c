#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
# define TAMINST 50 // Memoria instrucoes
# define TAMDADOS 100 // Memoria Dados
# define L1 4    // cache1
# define L2 8    // cache2
# define TAMBLOCO 4
# define TAMFOR 10
# define PROBAB 100
# define OPCODE 4

//var globais
int CacheHit1;
int CacheHit2;
int CacheMiss1;
int CacheMiss2;
typedef struct
{
     int opcode,End1,End2;   //IR,MAR1,MAR2
	 
}MInstrucao;

typedef struct   //Memoria de RAM
{
   float dados;
   
}MDados;
typedef struct
{
    MDados dado[TAMBLOCO];
	int TAG; //Representa o endereco bloco
	int LFU;  //Contador do numero de substituicao de dados
    
}TCache;

void preencheMInstrucao(MInstrucao* instrucao)
{
    
    MInstrucao *aux;
	srand(time(NULL));
	aux=(MInstrucao*)malloc(TAMFOR*sizeof(MInstrucao));
    int i=0,j=0,aleatorio=0;
    for(i=0;i<TAMFOR;i++)
	{
	     aux[i].opcode = rand ()%OPCODE;
		 aux[i].End1= rand ()%TAMDADOS;
		 aux[i].End2= rand ()%TAMDADOS;
	}
	for(i=0;i < TAMINST; )
	{
			aleatorio=rand()%100+1;
			if(aleatorio <= PROBAB)
	        {
				for(j=0;j<TAMFOR;j++,i++)
				{
					if(i != TAMINST-1)
					{
					        printf("Passou aqui\n\n");
							instrucao[i].opcode = OPCODE;
							instrucao[i].End1 = 0;
							instrucao[i].End2 = 0;
							i++;
							break;
					}
					instrucao[i].opcode = aux[j].opcode;
					instrucao[i].End1 = aux[j].End1;
					instrucao[i].End2 = aux[j].End2;
				}
			}
			else if(i<TAMINST-1)
			    {
							instrucao[i].opcode = rand ()%OPCODE;
							instrucao[i].End1 = rand ()%TAMDADOS;
							instrucao[i].End2 = rand ()%TAMDADOS;
							i++;
							
				}
				else{
							instrucao[i].opcode = OPCODE;
							instrucao[i].End1 = 0;
							instrucao[i].End2 = 0;				
				}
	}
	
	for(j=0;j<TAMINST;j++,i++)
	{
		printf("M Instrucao = %d, %d, %d\n",instrucao[i].opcode,instrucao[i].End1,instrucao[i].End2);
	}
	free (aux);
}

void preencheMDados(MDados* dados)
{
	int i;
	srand(time(NULL));
	for(i=0; i < TAMDADOS ;i++)
	{
		dados[i].dados = rand()% 100;
	}
}

float MMU_cache(TCache *cache1,TCache *cache2,MDados *dados,int MAR){
     int i=0,j=0,EndBloco,palavra,pos_cache1,pos_cache2;
	 EndBloco=MAR/TAMBLOCO; //End Bloco calculando end bloco
     palavra=MAR%TAMBLOCO;
     int m3=0,m4=0,m5=0;	 
     TCache aux;
     TCache aux2;	 
     for(i=0;i<L1;i++){           //buscando dado da cache 1
             if(EndBloco == cache1[i].TAG){
                  CacheHit1++;                 //incrementando cache hit 
				  cache1[i].LFU++;            //incrementando lfu
                  return cache1[i].dado[palavra].dados; //retornando o dado
             }
	}
	for(i=0;i<L2;i++)          //procurando cache 2
	{
            if(EndBloco == cache2[i].TAG){       
                  CacheHit2++;
				  cache2[i].LFU++;
				  for(j=0;j<L1;j++)     //procurando espaÃ§o livre na cache 1
				  {
					if(cache1[j].TAG == -1)
					{
						cache1[j] = cache2[i];
						return cache1[j].dado[palavra].dados;
					}
				  }
				  pos_cache1=0;  //aplicando a politica de substituicao
				  for(j=1;j<L1;j++)//procurando o menos usado e substituindo
				  {
					if(cache1[pos_cache1].LFU < cache1[j].LFU)
					{
						pos_cache1=j;
					}
				  }
				  aux = cache1[pos_cache1];
				  cache1[pos_cache1]=cache2[i];
				  for(j=0;j<L2;j++) //procurando espaÃ§o vazio na cache 2 para levar dado da cache 1
				  {
				    if(cache2[j].TAG == -1) //olhando se esta vazio
					{
					   
						cache2[i]=aux;
						return cache1[pos_cache1].dado[palavra].dados;
					}
				  }
				  pos_cache2=0; //aplicando a politica de substituicao
				  for(j=0;j<L2;j++)
				  {
					if(cache2[pos_cache2].LFU < cache2[j].LFU)
					{
						pos_cache2=j;
					}
				  }
				  if(cache2[pos_cache2].LFU < aux.LFU)
				  {
					cache2[pos_cache2]=aux;
					return cache1[pos_cache1].dado[palavra].dados;
				  }
             }
	}
	for(i=0;i<TAMBLOCO;i++)  //busca do bloco na memoria de dados
	{
		aux.dado[i].dados = dados[EndBloco*TAMBLOCO+i].dados;
		for(j=0;j<L2;j++)
		{
			if(cache2[j].TAG == -1)
			{
				cache2[j] = aux;
				cache2[j].TAG = EndBloco;
				break;
			}	
		}
		m3=cache2[0].LFU;
		if(m3 != 0)
		{
			for(j=0;j<L2;j++)
			{
				if(cache2[j].LFU <= m3)
				{
					pos_cache2 = j;
				}
			}
			for(j=0;j<TAMBLOCO;j++)
			{
				cache2[pos_cache2].dado[j].dados = dados[EndBloco*TAMBLOCO+j].dados;
				cache2[pos_cache2].TAG = EndBloco;
			}
		}
		m4=cache2[pos_cache2].LFU;
		for(j=0;j<L1;j++)
		{
			if(cache1[j].LFU <= m4)
			{
				pos_cache1 = j;
			}
		}
		 aux2 = cache1[pos_cache1];
		 cache1[pos_cache1] = cache2[pos_cache2];
		 for(j=0;j<L2;j++)
		 {
			if(cache2[j].TAG == -1)
			{
				cache2[j] = aux2;
				break;
			}
		 }
		 m5=cache2[0].LFU;
		 for(j=0;j<L2;j++)
		 {
			if(cache2[j].LFU <= m5)
			{
				pos_cache2 = j;
			}
		 }
		 cache2[pos_cache2] = aux2;
		
	}
	 return cache1[pos_cache1].dado[palavra].dados;
}
int soma(int valor,int valor2)
{
   
      return valor=valor+valor2;
       
}
int sub(int valor,int valor2)
{
      
       return valor=valor-valor2;
}
int mult(int valor,int valor2)
{
      
       return valor=valor*valor2;
}
float divisao(float valor,float valor2)
{
      
      if(valor2 > 0){
         return valor=valor/valor2;
                  
      } else{
          return 0;
        }
  exit(0);       
}         
int main()
{
   int IR=0,pc=0;
   float MQ,MBR1=0,MBR2=0;
   int MAR1, MAR2;
   TCache *cache1;
   TCache *cache2;
   
   cache1=(TCache*)malloc(L1*sizeof(TCache)); //alocando memoria cache1
   cache2=(TCache*)malloc(L2*sizeof(TCache)); //alocando memoria cache2
   
   MInstrucao *MemoriaInstrucao;
   MDados *MemoriaDados;
   
   MemoriaInstrucao=(MInstrucao*)malloc(TAMINST*sizeof(MInstrucao));
   preencheMInstrucao(MemoriaInstrucao);
   
   MemoriaDados=(MDados*)malloc(TAMDADOS*sizeof(MDados));
   preencheMDados(MemoriaDados);
 
 
	     while(IR != 4)
		 {
		 pc++;
         IR = MemoriaInstrucao[pc].opcode;
		 MAR1 = MemoriaInstrucao[pc].End1; 
		 MAR2 = MemoriaInstrucao[pc].End2;
         MBR1 = MMU_cache(cache1,cache2,MemoriaDados,MAR1);
		 printf("MBR1 = %.2f\n",MBR1);
         MBR2 = MMU_cache(cache1,cache2,MemoriaDados,MAR2);
		  printf("MBR2 = %.2f\n",MBR2);
		 
            switch(IR)
            {
                case 0: 
                    MQ=soma(MBR1,MBR2);
					printf("\nSoma = %.2f\n",MQ);
                    break;
                  
                case 1:  
                   MQ=sub(MBR1,MBR2);
                    printf("\nSub = %.2f\n",MQ);
                    break;  

                case 2:  
                    MQ=mult(MBR1,MBR2);
					printf("\nMult = %.2f\n",MQ);
                    break;

                case 3:  
                    MQ=divisao(MBR1,MBR2);
                    printf("\nDivisao = %.2f\n",MQ);					
                    break;
            }
       
        }
		printf("FIM PROGRAMA");
        free(MemoriaInstrucao);
        free(MemoriaDados);
        return 0;
}
