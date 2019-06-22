#include "Maquina.h"

int HDHits = 0;
int RAMHits = 0;
int L1Hits = 0;
int L2Hits = 0;

void criarMaquina (TMemoria** RAM, TMemoria** L1, TMemoria** L2, MInstrucao** MemoriaInstrucao)
{
	(*RAM) = new TMemoria[RAM_TAM];
	(*L1) = new TMemoria[L1_TAM];
	(*L2) = new TMemoria[L2_TAM];
	(*MemoriaInstrucao) = new MInstrucao[TAM_INST];
	
	
	for(int i=0 ; i<RAM_TAM ; i++) //Preenchedo RAM
		(*RAM)[i].LFU = -1;
	
	for(int i=0 ; i<L1_TAM ; i++) //Preenchedo L1
		(*L1)[i].LFU = -1;
	
	for(int i=0 ; i<L2_TAM ; i++) //Preenchedo L2
		(*L2)[i].LFU = -1;
}

void preencheMenuInstrucao(MInstrucao** instrucao)
{
	MInstrucao aux[TAM_INST];
	
	srand(time(NULL));
	
	int i=0, j=0, aleatorio=0;
	
	for(i=0;i<TAM_FOR;i++)
	{
		aux[i].OPCode = rand()%NUM_OPCODE;
		aux[i].End1 = rand()%DADOS_TAM;
		aux[i].End2 = rand()%DADOS_TAM;
	}
	
	for(i=0;i<TAM_INST;)
	{
		aleatorio = rand()%100+1;
		if (aleatorio <= PROBAB)
		{
			for (j=0 ; j<TAM_FOR ; j++,i++)
			{
				if (i != TAM_INST-1)
				{
					(*instrucao)[i].OPCode = NUM_OPCODE;
					(*instrucao)[i].End1 = 0;
					(*instrucao)[i].End2 = 0;
					i++;
					break;
				}
				(*instrucao)[i].OPCode = aux[j].OPCode;
				(*instrucao)[i].End1 = aux[j].End1;
				(*instrucao)[i].End2 = aux[j].End2;
			}
		}
		else
		{
			if(i < TAM_INST-1)
			{
				(*instrucao)[i].OPCode = rand()%NUM_OPCODE;
				(*instrucao)[i].End1 = rand()%DADOS_TAM;
				(*instrucao)[i].End2 = rand()%DADOS_TAM;					
				i++;
			}
			else
			{
				(*instrucao)[i].OPCode = NUM_OPCODE;
				(*instrucao)[i].End1 = 0;
				(*instrucao)[i].End2 = 0;
			}
		}
	}
}

int MMU (TMemoria* RAM, TMemoria* L1, TMemoria* L2, int MAR)
{
	int pos_L1, pos_L2, pos_RAM, i, j;
	TMemoria auxiliar;
	
	for (i=0 ; i<L1_TAM ; i++)
	{
		if (L1[i].End == MAR)
		{ //busca o dado na Cache1
			L1Hits++; //incrementando L1Hits
			L1[i].LFU++; //incrementando LFU
			return i; //retorna onde e em qual posicao foi achado o dado
		}
	}
	
	for (i=0 ; i<L2_TAM ; i++)
	{
		if (L2[i].End == MAR)
		{ //busca o dado na Cache2
			L2Hits++; //incrementando L2Hits
			L2[i].LFU++;
			
			pos_L1 = 0; //aplicando politica de substituicao
			for (j=0 ; j<L1_TAM ; j++)
			{ //procurando o menos usado
				if (L1[pos_L1].LFU > L1[j].LFU)
					pos_L1 = j;
			}
			auxiliar = L1[pos_L1];
			L1[pos_L1] = L2[i];
			L2[i] = auxiliar;
			return pos_L1;
		}
	}
	
	for (i=0 ; i<RAM_TAM ; i++)
	{ //bucando dado na Memoria
		if(RAM[i].End == MAR)
		{
			RAMHits++;
			RAM[i].LFU++;
			
			pos_L1 = 0;
			for(j=0 ; j<L1_TAM ; j++)
			{
				if(L1[pos_L1].LFU > L1[j].LFU)
					pos_L1 = j;
			}
			
			pos_L2 = 0;
			for(j=0 ; j<L2_TAM ; j++)
			{
				if(L2[pos_L2].LFU > L2[j].LFU)
					pos_L2 = j;
			}
			
			if(L1[pos_L1].LFU!=-1 && L2[pos_L2].LFU==-1)
			{
				auxiliar = L1[pos_L1];
				L1[pos_L1] = RAM[i];
				L2[pos_L2] = auxiliar;
				return pos_L1;
			}
			
			if(L1[pos_L1].LFU == -1)
			{
				L1[pos_L1] = RAM[i];
				return pos_L1;
			}
			
			auxiliar = RAM[i];
			RAM[i] = L2[pos_L2];
			L2[pos_L2] = L1[pos_L1];
			L1[pos_L1] = auxiliar;
			return pos_L1;
		}
	}
	
	HDHits++;
	
	fstream HD;
	
	HD.open("HD.bin", ios_base::binary | ios::in | ios::out);
	HD.seekg(sizeof(TMemoria)*MAR, ios::beg);
	HD.read((char*)&auxiliar, sizeof(TMemoria));
	
	pos_RAM = 0;
	for(i=0 ; i<RAM_TAM ; i++)
	{
		if(RAM[pos_RAM].LFU > RAM[i].LFU)
			pos_RAM = i;
	}
	pos_L1 = 0;
	for(i=0 ; i<L1_TAM ; i++)
	{
		if(L1[pos_L1].LFU > L1[i].LFU)
			pos_L1 = i;
	}
	pos_L2 = 0;
	for(i=0 ; i<L2_TAM ; i++)
	{
		if(L2[pos_L2].LFU > L2[i].LFU)
			pos_L2 = i;
	}
	
	if(L1[pos_L1].LFU!=-1 && L2[pos_L2].LFU!=-1 && RAM[pos_RAM].LFU==-1)
	{ //Cache 1 e 2 cheias e RAM livre
		RAM[pos_RAM] = L2[pos_L2];
		L2[pos_L2] = L1[pos_L1];
		L1[pos_L1] = auxiliar;
		return pos_L1;
	}
	
	if(L1[pos_L1].LFU!=-1 && L2[pos_L2].LFU==-1)
	{ //Cache 1 cheia e Cache 2 livre
		L2[pos_L2] = L1[pos_L1];
		L1[pos_L1] = auxiliar;
		return pos_L1;
	}
	
	if(L1[pos_L1].LFU == -1)
	{ //Cache 1 livre
		L1[pos_L1] = auxiliar;
		return pos_L1;
	}
	
	HD.seekp((MAR-1) * (sizeof(TMemoria)));
	HD.write((char*)&auxiliar, sizeof(TMemoria));
	
	RAM[pos_RAM] = L2[pos_RAM];
	L2[pos_L2] = L1[pos_L1];
	L1[pos_L1] = auxiliar;
	
	HD.close();
	
	return pos_L1;
}

void AtualizaHD (TMemoria* RAM, TMemoria* L1, TMemoria* L2){
	
	fstream HD;
	TMemoria auxiliar;
	
	HD.open("HD.bin", ios_base::binary | ios::in | ios::out);
	
	for(int i=0 ; i<RAM_TAM ; i++){
		auxiliar = RAM[i];
		HD.seekp(auxiliar.End * (sizeof(TMemoria)));
		HD.write((char*)&auxiliar, sizeof(TMemoria));
	}
	
	for(int i=0 ; i<L2_TAM ; i++){
		auxiliar = L2[i];
		HD.seekp(auxiliar.End * (sizeof(TMemoria)));
		HD.write((char*)&auxiliar, sizeof(TMemoria));
	}
	
	for(int i=0 ; i<L1_TAM ; i++){
		auxiliar = L1[i];
		HD.seekp(auxiliar.End * (sizeof(TMemoria)));
		HD.write((char*)&auxiliar, sizeof(TMemoria));
	}
	
	HD.close();
}

string resultado(string p1 , string p2, int num)
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

void deletarMaquina (TMemoria** RAM, TMemoria** L1, TMemoria** L2, MInstrucao** MemoriaInstrucao)
{
	delete [] (*RAM);
	delete [] (*L2);
	delete [] (*MemoriaInstrucao);
	delete [] (*L1);
}