/*  
 *  Máquina de simulação de jogos do campeonato Brasileiro 2015.
 *
 *	Created by Felipe Fontenele 03/11/2015
 *
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#define TAM 100 //Tamanho máximo da memoria.
using namespace std;

typedef struct
{
	int opcode;
	int End1;
	int End2;
}MInstrucao;

string resultado (string p1 , string p2, int num)
{
	srand((unsigned)time(NULL));
	p1 = rand()%7 + 48;
	p2 = rand()%7 + 48;
	if(num == 1)
	{
		if(p1 >= p2)
		{
			if(p1==p2)
				p1 += '1';
			return p1 + " X " + p2 ;
		}
		else
		{
			return p2 + " X " + p1 ;
		}
	}
	else
		if(num == 2)
		{
			if(p1>=p2)
			{
				if(p1==p2)
					p2 += '1';
				return p2 + " X " + p1 ;
			}
			else
			{
				return p1 + " X " + p2 ;
			}
		}
		else
		{
			return p1 + " X " + p1;
		}
}
void preencheMInstrucao(MInstrucao* instrucao)
{
    
    MInstrucao *aux;
	srand((unsigned)time(NULL));
	aux = new MInstrucao;
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
					        cout<<"Passou aqui\n\n";
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
		cout<<"M Instrucao : "<<instrucao[i].opcode<<instrucao[i].End1<<instrucao[i].End2;
	}
	delete aux;
}

int main()
{
	int PC=0, IR = -1, MAR = -1, MAR2 = -1, i=0,J=0;
	int memoria_opcodes[]={-1,2,1,3,0,1,3,2,3,1,0,2,1,3,1,2,3,0,3,2,1,4};
	int memoria_adress[]={-1,11,16,6,0,19,18,9,17,4,14,7,2,15,3,13,1,12,5,8,11};
	int memoria_adress2[]={-1,10,15,5,19,18,17,8,16,3,13,6,2,14,2,12,0,11,4,7,10};
	string memoria[]={"Atletico-MG","Atletico-PR","Avai","Chapecoense","Corinthians","Coritiba","Cruzeiro","Figueirense","Flamengo","Fluminense","Goias",
					"Gremio","Internacional","Joinville","Palmeiras","Ponte Preta","Santos","Sao Paulo","Sport","Vasco"};
	string M2[TAM],MBR, MBR2;
	string placar1,placar2,result;
	
	
	/*Opcode das instruções:
	-1 : inicializa simulação !!!
	0 : Jogar jogo;
	1 : Ganhar jogo;
	2 : Perder jogo;
	3 : Empatar jogo;
	4 : terminar o programa.*/
	
	while (IR!=4)
	{
		IR = memoria_opcodes[PC];
		MAR = memoria_adress[PC];
		MAR2 = memoria_adress2[J];
		MBR = memoria[MAR];
		MBR2 = memoria[MAR2];
		
		switch (IR)
		{
			case -1:
			{
				cout<<"\nINICIALIZANDO A SIMULACAO !!!"<<endl<<endl;
				break;
			}
			case 0:
			{
				if(MBR!=MBR2)
				{
					M2[i] = MBR + " esta jogando contra o " + MBR2;
					i++;
				}
				else
				{
					M2[i] = "JOGO INVALIDO. O TIME " + MBR +" NAO PODE AUTO SE ENFRETAR EM UMA PARTIDA.";
					i++;
				}
				break;
			}
			case 1:
			{
				if(MBR!=MBR2)
				{
					result = resultado(placar1,placar2,1);
					M2[i] = MBR + " ganhou o jogo contra o " + MBR2 + " :Placar " + result;
					i++;
				}
				else
				{
					M2[i] = "JOGO INVALIDO. O TIME " + MBR + " NAO PODE AUTO SE ENFRETAR EM UMA PARTIDA.";
					i++;
				}
				break;
			}
			case 2:
			{
				if(MBR!=MBR2)
				{
					result = resultado(placar1,placar2,2);
					M2[i] = MBR + " perdeu o jogo contra o " + MBR2 + " :Placar " + result ;
					i++;
				}
				else
				{
					M2[i] = "JOGO INVALIDO. O TIME " + MBR + " NAO PODE AUTO SE ENFRETAR EM UMA PARTIDA.";
					i++;
				}
				break;
			}
			case 3:
			{
				if(MBR!=MBR2)
				{
					result = resultado(placar1,placar2,3);
					M2[i] = MBR + " empatou o jogo contra o " + MBR2 + " :Placar " + result ;
					i++;
				}
				else
				{
					M2[i] = "JOGO INVALIDO. O TIME " + MBR + " NAO PODE AUTO SE ENFRETAR EM UMA PARTIDA.";
					i++;
				}
				break;
			}
		}	
		PC++;
		J++;
	}
	for(i=0;i<20;i++)
	{
		cout<<i+1<<" - "<<M2[i]<<endl;
	}
	if(IR==4)
	{
		cout<<"\nFINALIZANDO A SIMULACAO...\n";
	}
	return 0;
}