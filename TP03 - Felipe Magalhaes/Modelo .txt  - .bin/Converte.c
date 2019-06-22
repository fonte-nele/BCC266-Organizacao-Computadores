#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef struct
{
	char titulo[75];
}TFilmes;

int main()
{
	TFilmes filmes;
	
	FILE *arq, *DiscoRigido;
	if((arq = fopen("Filmes.txt", "r")) == NULL)
	{
		exit(1);
	}
	if((DiscoRigido = fopen("HD.bin", "wb")) == NULL)
	{
		exit(1);
	}
	while(fgets(filmes.titulo,sizeof(filmes.titulo),arq) != NULL)
	{
		printf("%s", filmes.titulo);
		fwrite(&filmes, sizeof(filmes),1,DiscoRigido);
	}
	//sleep(1000);
	printf("\nAqui\n");
	printf("Passou!");
	fclose(arq);
	fclose(DiscoRigido);
	if((DiscoRigido = fopen("HD.bin", "rb")) == NULL)
	{
		exit(1);
	}
	//fread()
	while(fread(&filmes,sizeof(filmes.titulo),1,DiscoRigido) == 1)
	{
		printf("%s", filmes.titulo);
	}
	return 0;
}