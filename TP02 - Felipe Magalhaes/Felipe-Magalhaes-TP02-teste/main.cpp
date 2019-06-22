#include "Casa_inteligente.h"

int main()
{

    /*
        Opcodes de Instruções:

            0: Liga / Desliga a luz do cômodo;
            1: Abre / Fecha as portas do cômodo;
            2: Abre / Fecha as janelas do cômodo;
            3: Exibe a situação atual do cômodo;
            4: Encerra o programa.


        Código dos Cômodos

            0 = Sala
            1 = Cozinha
            2 = Quarto 1
            3 = Quarto 2
            4 = Banheiro 1
            5 = Banheiro 2
    */

    TProcessador CPU;

    // Iniciam as memórias

    MCache cache1, cache2, cache3;
    Memoria RAM;

    IniciaCPU(&CPU);
    IniciaMemoriaCache1(&cache1);
    IniciaMemoriaCache2(&cache2);
    IniciaMemoriaCache3(&cache3);
    IniciaMemoriaPrincipal(&RAM);

    // Inicia o programa

    CPU.PC=0;
    while(CPU.PC<TAM_MEM) 
	{
        cin>>CPU.MBR;			// MBR recebe o opcode e passa para o IR
        CPU.IR=CPU.MBR;
        cin>>CPU.MBR;			// MBR recebe o address e passa para o MAR
        CPU.MAR=CPU.MBR;
                                // opcode e address estão separados por questões de uso do gerador de instruções

        cin>>CPU.MBR_Palavra;
        CPU.MBR_Palavra=CPU.MBR_Palavra % 4;	// "MBR" recebe o endereço da palavra do bloco encontrado
        cin>>CPU.MBR_Comodo;
        CPU.MBR_Comodo=CPU.MBR_Comodo % NComodos;


        switch(CPU.IR) 
		{
            case 0: // Liga / Desliga a luz do cômodo		|	true - Ligada / false - Desligada
            {
				if (Procura_Memoria(&cache1, &cache2, &cache3, CPU.MAR) == 1)
				{
					Escreve_Memoria(&cache1, &cache2, &cache3, &RAM, CPU.MAR, CPU.MBR_Palavra, CPU.MBR_Comodo, CPU.IR);
				}
                else
				{
					cout<<"Endereco nao se encontra na memoria."<<endl;
				}
                break;
			}    
            case 1: // Abre / Fecha as portas do cômodo		|	true - Abertas / false - Desligadas
			{
				if (Procura_Memoria(&cache1, &cache2, &cache3, CPU.MAR) == 1)
				{
                    Escreve_Memoria(&cache1, &cache2, &cache3, &RAM, CPU.MAR, CPU.MBR_Palavra, CPU.MBR_Comodo, CPU.IR);					
				}
                else
				{
                    cout<<"Endereco nao se encontra na memoria."<<endl;					
				}
                break;
			}
            case 2: // Abre / Fecha as janelas do cômodo	|	true - Abertas / false - Desligadas
            {
				if (Procura_Memoria(&cache1, &cache2, &cache3, CPU.MAR) == 1)
				{
					Escreve_Memoria(&cache1, &cache2, &cache3, &RAM, CPU.MAR, CPU.MBR_Palavra, CPU.MBR_Comodo, CPU.IR);
				}
                else
				{
                    cout<<"Endereco nao se encontra na memoria."<<endl;					
				}
                break;
			}
            case 3: // Exibe a situação atual do cômodo;
            {
				if (Procura_Memoria(&cache1, &cache2, &cache3, CPU.MAR) == 1)
				{
                    Situacao_Comodo(cache1, cache2, cache3, RAM, CPU.MAR, CPU.MBR_Palavra, CPU.MBR_Comodo);					
				}
                else
				{
                    cout<<"Endereco nao se encontra na memoria."<<endl;					
				}
                break;
			}
        }
        CPU.PC++;
    }

	

    cout<<"\n=========================RESULTADOS========================="<<endl<<endl;
    cout<<"Numero de instrucoes: "<<NUM_INS<<endl;
    cout<<"Tamanho Cache 1: "<<TAM_Cache1<<endl;
    cout<<"Tamanho Cache 2: "<<TAM_Cache2<<endl;
    cout<<"Tamanho Cache 3: "<<TAM_Cache3<<endl;
    cout<<"Tamanho da memoria: "<<TAM_MEM<<endl;
    cout<<endl;
    cout<<"Cache 1:"<<endl;
    cout<<"Cache hit: "<<cache1.CacheHit<<endl;
    cout<<"Cache miss: "<<cache1.CacheMiss<<endl;
    cout<<endl;
    cout<<"Cache 2:"<<endl;
    cout<<"Cache hit: "<<cache2.CacheHit<<endl;
    cout<<"Cache miss: "<<cache2.CacheMiss<<endl;
    cout<<endl;
    cout<<"Cache 3:"<<endl;
    cout<<"Cache hit: "<<cache3.CacheHit<<endl;
    cout<<"Cache miss: "<<cache3.CacheMiss<<endl;

	
    // Apagam as memórias e encerra o programa
    ApagaMemoriaCache1(&cache1);
    ApagaMemoriaCache2(&cache2);
    ApagaMemoriaCache3(&cache3);
    ApagaMemoriaPrincipal(&RAM);

    return 0;
}