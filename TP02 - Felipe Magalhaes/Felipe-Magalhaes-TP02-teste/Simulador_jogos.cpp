#include "Simulador_jogos.h"

void IniciaCasa(TCasa *casa)
{
    casa -> comodos = new TComodo[NComodos];

    casa -> comodos[0].nome = "Sala";
    casa -> comodos[1].nome = "Cozinha";
    casa -> comodos[2].nome = "Quarto 1";
    casa -> comodos[3].nome = "Quarto 2";
    casa -> comodos[4].nome = "Banheiro 1";
    casa -> comodos[5].nome = "Banheiro 2";

    casa -> comodos[0].portas = 0;
    casa -> comodos[1].portas = 0;
    casa -> comodos[2].portas = 0;
    casa -> comodos[3].portas = 0;
    casa -> comodos[4].portas = 0;
    casa -> comodos[5].portas = 0;

    casa -> comodos[0].janelas = 0;
    casa -> comodos[1].janelas = 0;
    casa -> comodos[2].janelas = 0;
    casa -> comodos[3].janelas = 0;
    casa -> comodos[4].janelas = 0;
    casa -> comodos[5].janelas = 0;

    casa -> comodos[0].luz = 0;
    casa -> comodos[1].luz = 0;
    casa -> comodos[2].luz = 0;
    casa -> comodos[3].luz = 0;
    casa -> comodos[4].luz = 0;
    casa -> comodos[5].luz = 0;
}

void IniciaCPU(TProcessador *CPU)
{
    CPU -> PC = 0;
    CPU -> IR = -1;
    CPU -> MAR = -1;
}

void IniciaMemoriaCache1(MCache *cache)
{

    cache -> linhas = new TBloco[TAM_Cache1];
    cache -> TempoEmCache = new int[TAM_Cache1];
    cache -> EnderecoLinhas = new int[TAM_Cache1];
    cache -> FrequenciaDeUso = new int[TAM_Cache1];
    cache -> Modificou = new int[TAM_Cache1];
    cache -> CacheHit = 0;
    cache -> CacheMiss = 0;

    for(int i = 0; i < TAM_Cache1; i++) {
        IniciaCasa(&(cache -> linhas[i].palavra[0]));
        IniciaCasa(&(cache -> linhas[i].palavra[1]));
        IniciaCasa(&(cache -> linhas[i].palavra[2]));
        IniciaCasa(&(cache -> linhas[i].palavra[3]));
        cache -> TempoEmCache[i] = 0;
        cache -> FrequenciaDeUso[i] = 0;
        cache -> Modificou[i] = 0;
    }

}

void IniciaMemoriaCache2(MCache *cache)
{

    cache -> linhas = new TBloco[TAM_Cache2];
    cache -> TempoEmCache = new int[TAM_Cache2];
    cache -> EnderecoLinhas = new int[TAM_Cache2];
    cache -> FrequenciaDeUso = new int[TAM_Cache2];
    cache -> Modificou = new int[TAM_Cache2];
    cache -> CacheHit = 0;
    cache -> CacheMiss = 0;

    for(int i = 0; i < TAM_Cache2; i++) {
        IniciaCasa(&(cache -> linhas[i].palavra[0]));
        IniciaCasa(&(cache -> linhas[i].palavra[1]));
        IniciaCasa(&(cache -> linhas[i].palavra[2]));
        IniciaCasa(&(cache -> linhas[i].palavra[3]));
        cache -> TempoEmCache[i] = 0;
        cache -> FrequenciaDeUso[i] = 0;
        cache -> Modificou[i] = 0;
    }

}

void IniciaMemoriaCache3(MCache *cache)
{

    cache -> linhas = new TBloco[TAM_Cache3];
    cache -> TempoEmCache = new int[TAM_Cache3];
    cache -> EnderecoLinhas = new int[TAM_Cache3];
    cache -> FrequenciaDeUso = new int[TAM_Cache3];
    cache -> Modificou = new int[TAM_Cache3];
    cache -> CacheHit = 0;
    cache -> CacheMiss = 0;

    for(int i = 0; i < TAM_Cache3; i++) {
        IniciaCasa(&(cache -> linhas[i].palavra[0]));
        IniciaCasa(&(cache -> linhas[i].palavra[1]));
        IniciaCasa(&(cache -> linhas[i].palavra[2]));
        IniciaCasa(&(cache -> linhas[i].palavra[3]));
        cache -> TempoEmCache[i] = 0;
        cache -> FrequenciaDeUso[i] = 0;
        cache -> Modificou[i] = 0;
    }

}

void IniciaMemoriaPrincipal(Memoria *mem)
{

    mem -> Blocos = new TBloco[TAM_MEM];

    for(int i = 0; i < TAM_MEM; i++) {
        IniciaCasa(&(mem ->Blocos[i].palavra[0]));
        IniciaCasa(&(mem ->Blocos[i].palavra[1]));
        IniciaCasa(&(mem ->Blocos[i].palavra[2]));
        IniciaCasa(&(mem ->Blocos[i].palavra[3]));

    }

}



            // Funções de apagar a memória




void ApagaCasa(TCasa *casa) 
{
    delete[] casa -> comodos;
}

void ApagaMemoriaCache1(MCache *cache)
{

    delete[] cache -> TempoEmCache;
    delete[] cache -> EnderecoLinhas;
    delete[] cache -> FrequenciaDeUso;
    delete[] cache -> Modificou;

    for(int i = 0; i < TAM_Cache1; i++) {
        ApagaCasa(&(cache -> linhas[i].palavra[0]));
        ApagaCasa(&(cache -> linhas[i].palavra[1]));
        ApagaCasa(&(cache -> linhas[i].palavra[2]));
        ApagaCasa(&(cache -> linhas[i].palavra[3]));
    }
    delete[] cache -> linhas;
}

void ApagaMemoriaCache2(MCache *cache)
{

    delete[] cache -> TempoEmCache;
    delete[] cache -> EnderecoLinhas;
    delete[] cache -> FrequenciaDeUso;
    delete[] cache -> Modificou;

    for(int i = 0; i < TAM_Cache2; i++) {
        ApagaCasa(&(cache -> linhas[i].palavra[0]));
        ApagaCasa(&(cache -> linhas[i].palavra[1]));
        ApagaCasa(&(cache -> linhas[i].palavra[2]));
        ApagaCasa(&(cache -> linhas[i].palavra[3]));
    }
    delete[] cache -> linhas;
}

void ApagaMemoriaCache3(MCache *cache)
{

    delete[] cache -> TempoEmCache;
    delete[] cache -> EnderecoLinhas;
    delete[] cache -> FrequenciaDeUso;
    delete[] cache -> Modificou;

    for(int i = 0; i < TAM_Cache3; i++) {
        ApagaCasa(&(cache -> linhas[i].palavra[0]));
        ApagaCasa(&(cache -> linhas[i].palavra[1]));
        ApagaCasa(&(cache -> linhas[i].palavra[2]));
        ApagaCasa(&(cache -> linhas[i].palavra[3]));
    }
    delete[] cache -> linhas;
}

void ApagaMemoriaPrincipal(Memoria *mem)
{
    delete[] mem -> Blocos;
}




            // Funções de procura



int Procura_cache(MCache *cache, int address, int tamanho)
{
    int flag = 0;							// flag para indicar o cache hit
    for(int i = 0; i < tamanho; i++) {
        if(cache -> EnderecoLinhas[i] == address) {
            flag = 1;
            cache -> CacheHit++;
            cache -> FrequenciaDeUso[i]++;
            cache -> Modificou[i] = 1;
            break;
        }
    }
    AddTempoEmCache(cache, tamanho);
    return flag;
}

bool Procura_RAM(int address)
{
    if(address < TAM_MEM)
	{
		return true;
	}
    else
	{
        return false;
	}
}

int Procura_Memoria(MCache *c1, MCache *c2, MCache *c3, int address)
{
    if(Procura_cache(c1, address, TAM_Cache1) == 0)
	{			// Procura na cache 1
        c1 -> CacheMiss++;
    }
    else
        return 1;

    if(Procura_cache(c2, address, TAM_Cache2) == 0)			// Procura na cache 2
        c2 -> CacheMiss++;
    else
        return 1;

    if(Procura_cache(c3, address, TAM_Cache3) == 0)			// Procura na cache 3
        c3 -> CacheMiss++;
    else
        return 1;
    if(Procura_RAM(address) == 0)			// Procura na RAM
        return 0;
    else
        return 1;

}

            // Funções de escrita

void Escreve_Memoria(MCache *c1, MCache *c2, MCache *c3, Memoria *RAM, int address, int palavra, int comodo, int opcode) {
    int flagAddress;
    for(int i = 0; i < TAM_Cache1; i++) {
        if(c1 -> EnderecoLinhas[i] == address) {
            Encontrou_Cache1(c1, address, palavra, comodo, opcode);
            return;
        }
    }
    for(int i = 0; i < TAM_Cache2; i++) {
        if(c2 -> EnderecoLinhas[i] == address) {
            Encontrou_Cache2(c1, c2, i);
            Encontrou_Cache1(c1, address, palavra, comodo, opcode);
            return;
        }
    }

    for(int i = 0; i < TAM_Cache3; i++) {
        if(c3 -> EnderecoLinhas[i] == address) {
            flagAddress = Encontrou_Cache3(c2, c3, i);
            Encontrou_Cache2(c1, c2, flagAddress);
            Encontrou_Cache1(c1, address, palavra, comodo, opcode);
            return;
        }
    }

    flagAddress =  Encontrou_RAM(c3, RAM, address);
    flagAddress = Encontrou_Cache3(c2, c3, flagAddress);
    Encontrou_Cache2(c1, c2, flagAddress);
    Encontrou_Cache1(c1, address, palavra, comodo, opcode);

    return;


}

void Situacao_Comodo(MCache c1, MCache c2, MCache c3, Memoria RAM, int address, int palavra, int comodo) {
    for(int i = 0; i < TAM_Cache1; i++)
        if(c1.EnderecoLinhas[i] == address) {
            cout_Comodo_CacheOuRAM(c1, RAM, 0, address, i, palavra, comodo);
            return;
        }

    for(int i = 0; i < TAM_Cache2; i++)
        if(c2.EnderecoLinhas[i] == address) {
            cout_Comodo_CacheOuRAM(c2, RAM, 0, address, i, palavra, comodo);
            return;
        }

    for(int i = 0; i < TAM_Cache3; i++)
        if(c3.EnderecoLinhas[i] == address) {
            cout_Comodo_CacheOuRAM(c3, RAM, 0, address, i, palavra, comodo);
            return;
        }

    for(int i = 0; i < TAM_MEM; i++)
        if(i == address) {
            cout_Comodo_CacheOuRAM(c2, RAM, 1, address, i, palavra, comodo);
            return;
        }



}

void cout_Comodo_CacheOuRAM(MCache cache, Memoria RAM, int flag, int addressRAM, int addressCache, int palavra, int comodo) {
    if(flag == 0) {
        cout << "Situacao do comodo " << cache.linhas[addressCache].palavra[palavra].comodos[comodo].nome << " da casa " << addressRAM << endl;
        cout << endl;

        cout << "Portas: ";
        if(cache.linhas[addressCache].palavra[palavra].comodos[comodo].portas == 1)
            cout << "Abertas" << endl;
        else
            cout << "Fechadas" << endl;
            cout << "Janelas: ";

        if(cache.linhas[addressCache].palavra[palavra].comodos[comodo].janelas == 1)
            cout << "Abertas" << endl;
        else
            cout << "Fechadas" << endl;
            cout << "Luzes: ";
        if(cache.linhas[addressCache].palavra[palavra].comodos[comodo].luz == 1)
            cout << "Acesas" << endl;
        else
            cout << "Apagadas" << endl;
            cout << endl;
    }
    else {
        cout << "Situacao do comodo " << RAM.Blocos[addressRAM].palavra[palavra].comodos[comodo].nome << " da casa " << addressRAM << endl;
        cout << endl;
        cout << "Portas: ";
        if(RAM.Blocos[addressRAM].palavra[palavra].comodos -> portas == 1)
            cout << "Abertas" << endl;
        else
            cout << "Fechadas" << endl;
            cout << "Janelas: ";

        if(RAM.Blocos[addressRAM].palavra[palavra].comodos -> janelas == 1)
            cout << "Abertas" << endl;
        else
            cout << "Fechadas" << endl;
            cout << "Luzes: ";

        if(RAM.Blocos[addressRAM].palavra[palavra].comodos -> luz == 1)
            cout << "Acesas" << endl;
        else
            cout << "Apagadas" << endl;
            cout << endl;

    }
}


void Encontrou_Cache1(MCache *c1, int address, int palavra, int comodo, int opcode) {
    switch(opcode) {
        case 0:
            for(int i = 0; i < TAM_Cache1; i++) {
                if(c1 -> EnderecoLinhas[i] == address) {
                    if(c1 -> linhas[i].palavra[palavra].comodos[comodo].luz == 0)
                     {
                        c1 -> linhas[i].palavra[palavra].comodos[comodo].luz = 1;

                    }else
                        c1 -> linhas[i].palavra[palavra].comodos[comodo].luz = 0;

                }
            }
            break;
        case 1:
            for(int i = 0; i < TAM_Cache1; i++) {
                if(c1 -> EnderecoLinhas[i] == address) {
                    if(c1 -> linhas[i].palavra[palavra].comodos[comodo].portas == 0)
                        c1 -> linhas[i].palavra[palavra].comodos[comodo].portas = 1;
                    else
                        c1 -> linhas[i].palavra[palavra].comodos[comodo].portas = 0;

                }
            }
            break;
        case 2:
            for(int i = 0; i < TAM_Cache1; i++) {
                if(c1 -> EnderecoLinhas[i] == address) {
                    if(c1 -> linhas[i].palavra[palavra].comodos[comodo].janelas == 0)
                        c1 -> linhas[i].palavra[palavra].comodos[comodo].janelas = 1;
                    else
                        c1 -> linhas[i].palavra[palavra].comodos[comodo].janelas = 0;

                }
            }
            break;
    }
}

void Encontrou_Cache2(MCache *c1, MCache *c2, int posCache2) {
    int menosfreq1 = 0;
    TBloco aux;
    int auxEnd, auxTempo, auxFreq, auxMod;

    // Acha o menos frequente em c2

    for(int i = 0; i < TAM_Cache1; i++) {
        if (c1 -> FrequenciaDeUso[menosfreq1] > c1 -> FrequenciaDeUso[i])
            menosfreq1 = i;
    // Se forem iguais compara seu tempo em cache
        else if (c1 -> FrequenciaDeUso[menosfreq1] == c1 -> FrequenciaDeUso[i])
            if(c1 -> TempoEmCache[menosfreq1] > c1 -> TempoEmCache[i])
                menosfreq1 = i;
    }


    // Faz a troca com o menor em c1

    aux = c1 -> linhas[menosfreq1];
    auxEnd = c1 -> EnderecoLinhas[menosfreq1];
    auxTempo = c1 -> TempoEmCache[menosfreq1];
    auxFreq = c1 -> FrequenciaDeUso[menosfreq1];
    auxMod = c1 -> Modificou[menosfreq1];

    c1 -> linhas[menosfreq1] = c2 -> linhas[posCache2];
    c1 -> EnderecoLinhas[menosfreq1] = c2 -> EnderecoLinhas[posCache2];
    c1 -> TempoEmCache[menosfreq1] = c2 -> TempoEmCache[posCache2];
    c1 -> FrequenciaDeUso[menosfreq1] = c2 -> FrequenciaDeUso[posCache2];
    c1 -> Modificou[menosfreq1] = c2 -> Modificou[posCache2];

    c2 -> linhas[posCache2] = aux;
    c2 -> EnderecoLinhas[posCache2] = auxEnd;
    c2 -> TempoEmCache[posCache2] = auxTempo;
    c2 -> FrequenciaDeUso[posCache2] = auxFreq;
    c2 -> Modificou[posCache2] = auxMod;



}


int Encontrou_Cache3(MCache *c2, MCache *c3, int posCache3) {
    int menosfreq2 = 0;
    TBloco aux;
    int auxEnd, auxTempo, auxFreq, auxMod;

    // Acha os meno frequente em c2

    for(int i = 0; i < TAM_Cache2; i++) {
        if (c2 -> FrequenciaDeUso[menosfreq2] > c2 -> FrequenciaDeUso[i])
            menosfreq2 = i;
    // Se forem iguais compara seu tempo em cache
        else if (c2 -> FrequenciaDeUso[menosfreq2] == c2 -> FrequenciaDeUso[i])
            if(c2 -> TempoEmCache[menosfreq2] > c2 -> TempoEmCache[i])
                menosfreq2 = i;
    }


    // Faz a troca com o menor em c2

        aux = c2 -> linhas[menosfreq2];
        auxEnd = c2 -> EnderecoLinhas[menosfreq2];
        auxTempo = c2 -> TempoEmCache[menosfreq2];
        auxFreq = c2 -> FrequenciaDeUso[menosfreq2];
        auxMod = c2 -> Modificou[menosfreq2];

        c2 -> linhas[menosfreq2] = c3 -> linhas[posCache3];
        c2 -> EnderecoLinhas[menosfreq2] = c3 -> EnderecoLinhas[posCache3];
        c2 -> TempoEmCache[menosfreq2] = c3 -> TempoEmCache[posCache3];
        c2 -> FrequenciaDeUso[menosfreq2] = c3 -> FrequenciaDeUso[posCache3];
        c2 -> Modificou[menosfreq2] = c3 -> Modificou[posCache3];

        c3 -> linhas[posCache3] = aux;
        c3 -> EnderecoLinhas[posCache3] = auxEnd;
        c3-> TempoEmCache[posCache3] = auxTempo;
        c3 -> FrequenciaDeUso[posCache3] = auxFreq;
        c3 -> Modificou[posCache3] = auxMod;

        return menosfreq2;	// retorna qual posição está na cache 2

}

int Encontrou_RAM(MCache *c3, Memoria *RAM, int address) {

    int menosfreq3 = 0;
    TBloco aux;
    int auxEnd;

    // Acha os meno frequente em c3

    for(int i = 0; i < TAM_Cache3; i++) {
        if (c3 -> FrequenciaDeUso[menosfreq3] > c3 -> FrequenciaDeUso[i])
            menosfreq3 = i;
    // Se forem iguais compara seu tempo em cache
        else if (c3 -> FrequenciaDeUso[menosfreq3] == c3 -> FrequenciaDeUso[i])
            if(c3 -> TempoEmCache[menosfreq3] > c3 -> TempoEmCache[i])
                menosfreq3 = i;
    }

    // Faz a troca com o menor em c2



    // Faz o Write-back

    if(c3 -> Modificou[menosfreq3] == 0) {
        c3 -> linhas[menosfreq3] = RAM -> Blocos[address];
        c3 -> EnderecoLinhas[menosfreq3] = address;
        c3 -> TempoEmCache[menosfreq3] = 1;
        c3 -> FrequenciaDeUso[menosfreq3] = 0;
        c3 -> Modificou[menosfreq3] = 0;

    }
    else {

        aux = c3 -> linhas[menosfreq3];
        auxEnd = c3 -> EnderecoLinhas[menosfreq3];

        c3 -> linhas[menosfreq3] = RAM -> Blocos[address];
        c3 -> EnderecoLinhas[menosfreq3] = address;
        c3 -> TempoEmCache[menosfreq3] = 1;
        c3 -> FrequenciaDeUso[menosfreq3] = 0;
        c3 -> Modificou[menosfreq3] = 0;

        RAM -> Blocos[auxEnd] = aux;

        }

   return menosfreq3;
}
            // Funções extras

void AddTempoEmCache(MCache *cache, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
	{
		cache -> TempoEmCache[i]++;
	}
}
