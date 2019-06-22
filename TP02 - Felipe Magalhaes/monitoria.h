//ESTRUTRA TP 2
int main
{
	Ler o arquivo programa.txt;
	while (IR) != OP de saida)
	{
		MBR1 = MI[PC].OP;
		if (MBR1 == 0)
		{
			MBR2[0] = MI[PC].ENDBLOCO
			MBR2[1] = MI[PC].ENDPALAVRA
		}
		if (MBR1 == 1)
		{
			.
			.
			.
		}
		IR=MBR1;
	}
	switch(IR)
	{
		case 0:
			T=MMU();
			OPCODE(L1, TAML1, T, MAR[1]);
		case 1:
			T=MMU();
			Tx=MMU();
			OPCODE(L1,TAM,T,Tx,MAR[1], MAR[3])
	}
}

//ESTRUTURA MMU

MMU(L1, tamL1, L2, tamL2, MD, tamMD, MAR[0])
{
	for (i=0; i<tamL1; i++)
	{
		if(L1[i].ENDBLOCO == ENDBLOCO)// se encontrou
		{
			cachehit1++;
			tempo += 5;
			return;
		}
		cachemiss1++;
		tempo += 5;
	}
	
	for (j=0; j<tamL2; j++)
	{
		if (L2[j].ENDBLOCO == ENDBLOCO)
		{
			cachehit2++;
			tempo += 10;
			for (i=0; i<tamL1; i++)
			{
				if(L1[i].ENDBLOCO == -1)// se encontrou
				{
					L1[i]=L2[j];
					L2[j].ENDBLOCO = -1;
					//Esvaziar outros campos
					return;
				}
				else if (L1[i].acessos < menosUsado)
				{
					menosUsado = L1[i].acessos;
				}
				if (i== tamL1-1 && L1[i].ENDBLOCO != -1)
				{
					for (k=0; k<tamL1; k++)
					{
						if (L1[k].acessos == menosUsado)
						{
							/*aux = L1[menosUsado];
							L1[menosUsado] = L2[j];
							L2[j] = aux;*/
							//TROCO
							return;
						}
					}
				}
			}
		}
		cachemiss2++;
		tempo += 10;
	}
	
	for (y=0; y< tamMD, y++)
	{
		if (i == ENDBLOCO)
		{
			tempo += 20;
			for (j=0; j<tamL2; j++)
			{
				if (L2[j] == -1)
				{
					for (k=0; k<4; k++)
					{
						L2[j].PALAVRA[k] = MD[y].PALAVRA[k];
						L2[1].ENDBLOCO = y;
						for (i=0; i<tamL1; i++)
						{
							if (L1[i] == -1)
							{
								//coloca o dado
								return;
							}
							else if (L1[i].acessos < menosUsado)
							{
								menosUsado = L1[i].acessos;
							}
							if (i== tamL1-1 && L1[i].ENDBLOCO != -1)
							{
								for (k=0; k<tamL1; k++)
								{
									if (L1[k].acessos == menosUsado)
									{
										/*aux = L1[menosUsado];
										L1[menosUsado] = L2[j];
										L2[j] = aux;*/
										//TROCO
										return;
									}
								}
							}
						}
					}
				}
			}
		}	
	}	
}