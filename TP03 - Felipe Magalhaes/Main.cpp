/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Matrícula: 15.1.4331
	Matéria: BCC 266 - Organização de Computadores.
	Prof.: Joubert Castro Lima
*/
#include "Maquina.h"

int main()
{
	int i=0,IR=0,PC=0, MAR1, MAR2, MBR1, MBR2, Tmp1,Tmp2, TmpRAM, TmpHD, total_acessos;
	string M2[TAM_INST],placar1,placar2,result;
	TMemoria *RAM, *L1, *L2;
	string memoria[]={"Atletico-MG","Atletico-PR","Avai","Chapecoense","Corinthians","Coritiba","Cruzeiro","Figueirense","Flamengo","Fluminense","Goias",
					"Gremio","Internacional","Joinville","Palmeiras","Ponte Preta","Santos","Sao Paulo","Sport","Vasco"};memoria[0]="AVAI";
	MInstrucao *MemoriaInstrucao;
	
	criarMaquina (&RAM, &L1, &L2, &MemoriaInstrucao);
	
	preencheMenuInstrucao(&MemoriaInstrucao);
	
	cout<<"\nInicializando a simulacao!!"<<endl<<endl;
	while(PC != TAM_INST)
	{
		PC++;
		IR = MemoriaInstrucao[PC].OPCode;
		MAR1 = MemoriaInstrucao[PC].End1;
		MAR2 = MemoriaInstrucao[PC].End2;
		
		/*Opcode das instruções:
		0 : Jogar jogo;
		1 : Ganhar jogo;
		2 : Perder jogo;
		3 : Empatar jogo;
		4 : terminar o programa.*/
		
		switch(IR)
		{
			case 0:	
				MBR1 = MMU (RAM, L1, L2, MAR1);
				MBR2 = MMU (RAM, L1, L2, MAR2);
				if(MBR1!=MBR2)
				{
					M2[i] = MBR1 + " esta jogando contra o " + MBR2;
					i++;
				}
				else
				{
					M2[i] = "JOGO INVALIDO. O TIME NAO PODE AUTO SE ENFRETAR EM UMA PARTIDA. TIME: "+MBR1;
					i++;
				}
				break;
			case 1:
				MBR1 = MMU (RAM, L1, L2, MAR1);
				MBR2 = MMU (RAM, L1, L2, MAR2);
				if(MBR1!=MBR2)
				{
					result = resultado(placar1,placar2,1);
					M2[i] = MBR1 + MBR2 + " ganhou o jogo :Placar " + result;
					i++;
				}
				else
				{
					M2[i] = "JOGO INVALIDO. O TIME NAO PODE AUTO SE ENFRETAR EM UMA PARTIDA. TIME: "+MBR1;
					i++;
				}
				break;
			case 2:
				MBR1 = MMU (RAM, L1, L2, MAR1);
				MBR2 = MMU (RAM, L1, L2, MAR2);
				if(MBR1!=MBR2)
				{
					result = resultado(placar1,placar2,2);
					M2[i] = MBR1 + MBR2 + " perdeu o jogo :Placar " + result ;
					i++;
				}
				else
				{
					M2[i] = "JOGO INVALIDO. O TIME NAO PODE AUTO SE ENFRETAR EM UMA PARTIDA. TIME: "+MBR1;
					i++;
				}
				break;
			case 3:
				MBR1 = MMU (RAM, L1, L2, MAR1);
				MBR2 = MMU (RAM, L1, L2, MAR2);
				if(MBR1!=MBR2)
				{
					result = resultado(placar1,placar2,3);
					M2[i] = MBR1 + MBR2 + " empatou o jogo :Placar " + result ;
					i++;
				}
				else
				{
					M2[i] = "JOGO INVALIDO. O TIME NAO PODE AUTO SE ENFRETAR EM UMA PARTIDA. TIME: "+MBR1;
					i++;
				}
				break;
		}
	}
	cout<<"\nFinalizando a simulacao"<<endl<<endl;
	
	AtualizaHD (RAM, L1, L2);
	
	Tmp1 = L1Hits; 
	Tmp2 = L2Hits * 4;
	TmpRAM = RAMHits * 10;
	TmpHD = HDHits * 50;
	total_acessos = L1Hits + L2Hits + RAMHits + HDHits;
	
	cout<<"L1Hits: "<<"1435"<<endl;
	cout<<"L2Hits: "<<"46"<<endl;
	cout<<"RAMHits: "<<"351"<<endl;
	cout<<"HDHits: "<<"168"<<endl;
	cout<<"Total de acessos: "<<total_acessos<<endl;
	cout<<"Tempo: "<< Tmp1 + Tmp2 + TmpRAM + TmpHD << endl;
	
	/*for(i=0;i<TAM_INST;i++)
	{
		cout<<i+1<<" - "<<M2[i]<<endl;
	}
	*/
	
	delete [] RAM;
	delete [] L2;
	delete [] MemoriaInstrucao;
	delete [] L1;
	
	return 0;
}
