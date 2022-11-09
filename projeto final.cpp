#include <iostream>
#include <string.h>
#include <Windows.h>
#include <locale>

struct reg
{
	char nome[20];
	char universo[20];
	char np[20];//nivel de poder
	char cpf[11];
	char status;
};
int tamanho(FILE *);
void cadastrar(FILE *);
void consultar(FILE *);
void geraarqtxt(FILE *);
void excluir(FILE *);

int main()
{
	
	int op;
	FILE *arq;
	if ((arq = fopen("dados1.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("dados1.dat", "wb+")) == NULL)
		{
			printf("Falha ao abrir o arquivo!\n");
			system("pause");
		}
	}
	do
	{
		system("CLS");
		printf("Escolha a operacao que deseja fazer:\n");
		printf("1. cadastrar\n");
		printf("2. excluir\n");
		printf("3. consultar\n");
		printf("4. gerar arquivo\n");
		printf("5. sair\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)	
		{
		case 1://cadastrar novo contato
			cadastrar(arq);
			break;
		case 2:
		     excluir(arq);
			
			break;
		case 3: 
			consultar(arq); 
			break;

		case 4: 
		      geraarqtxt(arq);
		    break;
		case 5: fclose(arq);
		}
	}while(op!=5);


	
}
void cadastrar(FILE *arq)
{
	reg ficha;
	char confirma;
	ficha.status= ' ';
	fflush(stdin);

	printf("Cadastrando novo registro:\n");
	printf("\nNumero do registro:%d\n", tamanho(arq) + 1);
	printf("Nome:");
	//getchar();
	gets(ficha.nome);
	printf("universo:");
	gets(ficha.universo);
	printf("nivel de poder:");
	gets(ficha.np);
	printf("Cpf:");
	gets(ficha.cpf);
	printf("\nConfirma <s/n>:");
	fflush(stdin);
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\ngravando...\n\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&ficha, sizeof(reg), 1, arq);

	}
	system("pause");
}	

void consultar(FILE *arq)
{
	reg ficha;
	int nr;
	printf("\nConsulta pelo codigo\n");
	printf("\nInforme o Codigo...:");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&ficha, sizeof(reg), 1, arq);
		if (ficha.status == ' ')
		{
			printf("\nNome:%s", ficha.nome);
			printf("\nuniverso:%s", ficha.universo);
			printf("\nnivel de poder:%s\n\n", ficha.np);
			printf("\ncpf:%s\n\n", ficha.cpf);
		}

		else
			printf("\nRegistro excluido! \n");

	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}
void geraarqtxt(FILE *arq)
{
	char nomearq[20];
	printf("Nome do arquivo texto:");
	scanf("%s", nomearq);
	strcat(nomearq, ".txt");
	FILE *arqtxt = fopen(nomearq, "w");
	if (!arqtxt)
	{
		printf("Nao foi possivel criar esse arquivo!\n");
		system("pause");
		//return;
	}
	fprintf(arqtxt, "Nome                universo    nivel de poder   cpf                 Status\n");
	fprintf(arqtxt, "================================================================\n");
	int nr;
	reg ficha;
	for (nr = 0; nr<tamanho(arq); nr++)
	{
		fseek(arq, nr * sizeof(reg), SEEK_SET);
		fread(&ficha, sizeof(reg), 1, arq);
		fprintf(arqtxt, "%-20s%-12s%-25s-%-12s %c\n", ficha.nome, ficha.universo, ficha.np, ficha.cpf, ficha.status);
	}
	fprintf(arqtxt, "================================================================\n");
	fclose(arqtxt);
}

void excluir(FILE *arq)
{
	reg ficha;
	char confirma;
	int nr;

	printf("\nInforme o codigo do registro para excluir\n");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&ficha, sizeof(reg), 1, arq);
		if (ficha.status == ' ')
		{
			printf("\nNome:%s", ficha.nome);
			printf("\nuniverso:%s", ficha.universo);
			printf("\nnivel de poder:%s\n", ficha.np);
			printf("\ncpf:%s\n", ficha.cpf);
			printf("\nConfirma a exclusao: <s/n>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nexcluindo...\n\n");
				fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
				ficha.status = '*';
				fwrite(&ficha, sizeof(reg), 1, arq);
			}
		}
	else
		printf("Registro inexistente! \n");
	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}	

int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}
