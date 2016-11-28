#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

typedef struct
{
	char *nome;
	struct stat uidPerTam;//User ID, permissoes, tamanho
	struct tm *data;// data e hora
	int ordem;
}CABECALHO;//item de cabecalho

void arqVazio(FILE *a,char *v[])
{

	char t;
	t = getc(a);
	if(t == EOF) { perror("Erro:arquivo inexistente"); fclose(a); if(remove(v[2]) != 0) perror("Erro ao remover arquivo"); exit(1); }
																	//Primeiro if:arquivo inexistente Segundo if:Deleta arquivo se ja nao havia algum
	return;
}
bool arqvazio(FILE *a)
{ 
	char t;
	t = getc(a);
	if(t == EOF) return true;
	return false;
}
void guardaValor(FILE *a,CABECALHO *b,int tam)//armazena as informaçoes do cabecalho
{
	rewind(a);
	int i;
	for(i = 0;i < tam;i++)
	{
		fprintf(a," %s ",b[i].nome);//nome do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1); }

		fprintf(a,"%d ",b[i].uidPerTam.st_uid);//User ID do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}

		fprintf(a,"%d ",b[i].uidPerTam.st_mode);//permissoes do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}

		fprintf(a,"%ld ",b[i].uidPerTam.st_size);//tamanho do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}

		fprintf(a,"%ld ",b[i].uidPerTam.st_mtime);//data do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}
		
		fprintf(a,"%d\n", b[i].ordem);//ordem do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}

	}
	fprintf(a,"\n");//fim do arquivo -------- indicado por dois \n seguidos
	if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}
	return;
}

int recebeValor(FILE *a,CABECALHO *b)//recupera as informacoes do cabecalho
{
	int tam;
	for(tam = 0;true;tam++)
	{
		b = realloc(b,sizeof(CABECALHO)*(tam+1));
		if(b==NULL){ perror("Erro ao alocar memoria"); exit(1);}
		char t;//verifica final do item do cabecalho
		int i = 0;//indice da string b[tam].nome
		do
		{
			i++;
			b[tam].nome = (char*) realloc (b[tam].nome, sizeof(char)*i);
			if(b[tam].nome==NULL){ perror("Erro ao alocar memoria"); exit(1);}
			b[tam].nome[i-1] = t;
		}while((t = getc(a)) != ' ');
		i++;
		b[tam].nome = (char*) realloc (b[tam].nome, sizeof(char)*i);
		if(b[tam].nome==NULL){ perror("Erro ao alocar memoria"); exit(1);}
		b[tam].nome[i-1] = '\0';//nome do arquivo

		fscanf(a,"%d", &b[tam].uidPerTam.st_uid);//User ID do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}

		fscanf(a,"%d", &b[tam].uidPerTam.st_mode);//permissoes do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}

		fscanf(a,"%ld", &b[tam].uidPerTam.st_size);//tamanho do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}
		
		fscanf(a,"%ld", &b[tam].uidPerTam.st_mtime);//data do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}
		b[tam].data = localtime(&b[tam].uidPerTam.st_mtime);

		fscanf(a,"%d", &b[tam].ordem);//ordem do arquivo
		if(ferror(a)){ perror("Erro ao escrever em arquivo"); exit(1);}

		if((t = getc(a)) == '\n') break;
	}
	return tam;
}

inline int fimCabecalho(FILE *f)//retorna o fim do cabecalho, que esta localizado antes dos membros
{
	rewind(f);
	char c;
	do
	{
		c = getc(f);
		if(c == '\n')
		{
			c = getc(f);
			if(c == '\n') break;
		}
	}while(true);
	return ftell(f);
}

inline void gotoMembro(FILE *f,int ordem,CABECALHO *ca)//vai para o inicio do membro de ordem n
{
	fseek(f, fimCabecalho(f), SEEK_SET);
	int pos;
	for(pos = 0;pos < ordem-1;pos++) fseek(f,ca[pos].uidPerTam.st_size,SEEK_CUR);
	return;
}

void incluir(int c, char *v[], FILE *f, CABECALHO *ca, int tam)//inclui um membro ao arquivo, e cria o arquivo caso ele nao exista
{
    int i,j,k;
    char **tempV;
    int tempI = 3;
    tempV = malloc(tempI);

    tempV[0] = malloc(strlen(v[0]));//copiando as 3 primeiras strings de argv
    strcpy(v[0],tempV[0]);
    tempV[1] = malloc(strlen(v[1]));
    strcpy(v[1],tempV[1]);
    tempV[2] = malloc(strlen(v[2]));
    strcpy(v[2],tempV[2]);

    for(i = 3;i < c;i++)
    {
        for(j = 0;j < tam;j++)
        {
            if(!strcmp(v[i],ca[j].nome))
            {
                tempI++;
                tempV = realloc(tempV,tempI);
                tempV[tempI-1] = malloc(strlen(v[i]));
                strcpy(v[i],tempV[tempI-1]);
            }
        }
    }
    remover(c,tempV,f,ca,tam);
    for(i = 0;i < tempI;i++) free(tempV[i]);
    free(tempV);
    int tot = tam;
    for(i = 3;i < c;i++)
    {
        tam++;
        ca = realloc(ca,sizeof(CABECALHO)*tam);
        ca[tam-1].nome = v[i];
        stat(v[i],&ca[tam-1].uidPerTam);
        ca[tam-1].data = localtime(&ca[tam-1].uidPerTam.st_mtime);
        ca[tam-1].ordem = tam;
    }
    
    
    
    FILE *T = fopen("temp.hu3","wb");
    guardaValor(T,ca,tam);
    for(i = 0;i < tot;i++)//coloca os dados no fim dos archive
    {
        long int tamarc = ca[i].uidPerTam.st_size, resultado;//tamanho do arquivo em bytes
        gotoMembro(f,ca[i].ordem,ca);
        while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
        {
            void *buffer = (void*) malloc (1024);
            resultado = fread(buffer,1,1024,f);
            if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
            fwrite(buffer,1,1024,T);
            tamarc -= 1024;
            free(buffer);
        }
        void *buffer = (void*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
        resultado = fread(buffer,1,tamarc,f);
        if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
        fwrite(buffer,1,tamarc,T);
        free(buffer);
    }
    for(i = tot;i < tam;i++)//coloca os dados no fim dos archive
    {
    	FILE *tempFile = fopen(ca[i].nome,"rb");
        long int tamarc = ca[i].uidPerTam.st_size, resultado;//tamanho do arquivo em bytes
        gotoMembro(f,ca[i].ordem,ca);
        while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
        {
            void *buffer = (void*) malloc (1024);
            resultado = fread(buffer,1,1024,f);
            if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
            fwrite(buffer,1,1024,T);
            tamarc -= 1024;
            free(buffer);
        }
        void *buffer = (void*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
        resultado = fread(buffer,1,tamarc,f);
        if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
        fwrite(buffer,1,tamarc,T);
        free(buffer);
        fclose(tempFile);
    }
    fclose(f);
    fclose(T);
    remove(v[2]);
    rename("temp.hu3",v[2]);
    
    return;
}

void app(int c, char *v[], FILE *f, CABECALHO *ca, int tam)//variacao de incluir, onde se o membro ja existir e for mais recente
															//ele eh substituido
{
    int i,j,k;
    char **tempV;
    int tempI = 3;
    tempV = malloc(tempI);

    tempV[0] = malloc(strlen(v[0]));//copiando as 3 primeiras strings de argv
    strcpy(v[0],tempV[0]);
    tempV[1] = malloc(strlen(v[1]));
    strcpy(v[1],tempV[1]);
    tempV[2] = malloc(strlen(v[2]));
    strcpy(v[2],tempV[2]);

    CABECALHO *tempCa;
    CABECALHO *caAnt = malloc(sizeof(CABECALHO)*tam);
    *caAnt = *ca;
    int tamAnt = tam;
    
    int tempTam;
    for(i = 3;i < c;i++)
    {
        tempTam++;
        tempCa = realloc(tempCa,sizeof(CABECALHO)*tempTam);
        tempCa[tempTam-1].nome = malloc(strlen(v[i]));
        strcpy(v[i],tempCa[tempTam-1].nome);
        stat(v[i],&tempCa[tempTam-1].uidPerTam);
        tempCa[tempTam-1].data = localtime(&ca[tam-1].uidPerTam.st_mtime);
    }


    for(i = 0;i < tempTam;i++)
    {
        for(j = 0;j < tam;j++)
        {
            if(!strcmp(tempCa[i].nome,ca[j].nome) && tempCa[i].uidPerTam.st_mtime > ca[j].uidPerTam.st_mtime)
            {
                tempI++;
                tempV = realloc(tempV,tempI);
                tempV[tempI-1] = malloc(strlen(v[i]));
                strcpy(v[i],tempV[tempI-1]);
            }
        }
    }


    remover(c,tempV,f,ca,tam);
    free(tempV);
    
    for(i = 0;i < tempTam;i++)//tira aqueles que tem nome igual, porem nao possuem data de modificao mais recente 
    						  //mantem a ordem da linha de comando
    {
        for(j = 0;j < tam;j++)
        {
        	if(!strcmp(tempCa[i].nome,caAnt[j].nome) && tempCa[i].uidPerTam.st_mtime <= caAnt[j].uidPerTam.st_mtime)
            {
                tempTam--;
                for(k = i;k < tempTam;k++) tempCa[k] = tempCa[k+1];
                tempCa = realloc(tempCa,sizeof(CABECALHO)*tempTam);
            }
        }
    }
    
    int tot = tam;
    for(i = 0;i < tempTam;i++)
    {
        tam++;
        ca = realloc(ca,sizeof(CABECALHO)*tam);
        ca[tam-1].nome = malloc(strlen(tempCa[i].nome));
        strcpy(ca[tam-1].nome,tempCa[i].nome);
        ca[tam-1].uidPerTam = tempCa[i].uidPerTam;
        ca[tam-1].data = localtime(&ca[tam-1].uidPerTam.st_mtime);
        ca[tam-1].ordem = tam;
    }
    
    
    
    
    FILE *T = fopen("temp.hu3","wb");
    guardaValor(T,ca,tam);
    for(i = 0;i < tot;i++)//coloca os dados no fim dos archive
    {
        long int tamarc = ca[i].uidPerTam.st_size,resultado;//tamanho do arquivo em bytes
        gotoMembro(f,ca[i].ordem,ca);
        while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
        {
            char *buffer = (char*) malloc (1024);
            resultado = fread(buffer,1,1024,f);
            if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
            fwrite(buffer,1,1024,T);
            tamarc -= 1024;
            free(buffer);
        }
        char *buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
        resultado = fread(buffer,1,tamarc,f);
        if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
        fwrite(buffer,1,tamarc,T);
        free(buffer);
    }
    for(i = tot;i < tam;i++)//coloca os dados no fim dos archive
    {
    	FILE *tempFile = fopen(ca[i].nome,"rb");
        long int tamarc = ca[i].uidPerTam.st_size,resultado;//tamanho do arquivo em bytes
        while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
        {
            char *buffer = (char*) malloc (1024);
            resultado = fread(buffer,1,1024,tempFile);
            if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
            fwrite(buffer,1,1024,T);
            tamarc -= 1024;
            free(buffer);
        }
        char *buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
        resultado = fread(buffer,1,tamarc,tempFile);
        if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
        fwrite(buffer,1,tamarc,T);
        free(buffer);
        fclose(tempFile);
    }
    fclose(f);
    fclose(T);
    remove(v[2]);
    rename("temp.hu3",v[2]);
    
    return;
}

void move(int c,char *v[], FILE *f, CABECALHO *ca, int tam)//move um membro do arquivo para apos outro membro
{
	arqVazio(f,v);
	long int tamarc,resultado;
	char *buffer;
    FILE *tempFile = fopen("temp.hu3", "wb");
    int i,j,ordemTarg,ordemMem;
    bool existe = false;
    for(j = 0;j < tam;j++) if(!strcmp(v[3],ca[j].nome)) { ordemTarg = ca[j].ordem; existe = true; break; }
    if(!existe) { perror("Erro:membro alvo nao existe no arquivo"); exit(1); }
    existe = false;
    for(j = 0;j < tam;j++) if(!strcmp(v[4],ca[j].nome) && ca[j].ordem != ordemTarg) { ordemMem = ca[j].ordem; existe = true; break; }
    if(!existe) { perror("Erro:um membro nao existe no arquivo"); exit(1); }
    if(ordemTarg == ordemMem) { return; }
    CABECALHO *tempCa = malloc(sizeof(CABECALHO)*tam);
    for(i = 0;i < tam;i++) tempCa[i] = ca[i];
    for(i = 0;i < tam;i++)
    	if(i == ordemTarg-1)
    	{
    		for(i = ordemMem-1;i > ordemTarg-1;i--) tempCa[i] = ca[i-1];
    		tempCa[ordemTarg] = ca[ordemMem-1];
    		break;
    	}
    	else if(i == ordemMem-1)
    	{
    		for(i = ordemMem-1;i < ordemTarg-1;i++) tempCa[i] = ca[i+1];
    		ordemTarg--;
    		tempCa[ordemTarg] = ca[ordemMem-1];
    		break;
    	}
    for(i = 0;i < tam;i++) tempCa[i].ordem = i+1;
	rewind(tempFile);
	guardaValor(tempFile,tempCa,tam);
    for(i = 0;i < tam;i++)
    {
        if(i != ordemTarg-1 && i != ordemMem-1)
        {	
        	gotoMembro(f,ca[i].ordem,ca);
        	tamarc = ca[i].uidPerTam.st_size;//tamanho do arquivo em bytes
		    while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
		    {
		        buffer = (char*) malloc (1024);
		        resultado = fread(buffer,1,1024,f);
		        if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
		        fwrite(buffer,1,1024,tempFile);
		        tamarc -= 1024;
		        free(buffer);
		    }
		    buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
		    resultado = fread(buffer,1,tamarc,f);
		    if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
		    fwrite(buffer,1,tamarc,tempFile);
		    free(buffer);
        }
        else if(i == ordemTarg-1)
        {	
			gotoMembro(f,ca[i].ordem,ca);
			tamarc = ca[i].uidPerTam.st_size;//tamanho do arquivo em bytes
			while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
			{
				buffer = (char*) malloc (1024);
				resultado = fread(buffer,1,1024,f);
				if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
				fwrite(buffer,1,1024,tempFile);
				tamarc -= 1024;
				free(buffer);
			}
			buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
			resultado = fread(buffer,1,tamarc,f);
			if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
			fwrite(buffer,1,tamarc,tempFile);
			free(buffer);
			
			i = ordemMem-1;
			gotoMembro(f,ca[i].ordem,ca);
			tamarc = ca[i].uidPerTam.st_size;//tamanho do arquivo em bytes
			while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
			{
				buffer = (char*) malloc (1024);
				resultado = fread(buffer,1,1024,f);
				if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
				fwrite(buffer,1,1024,tempFile);
				tamarc -= 1024;
				free(buffer);
			}
			buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
			resultado = fread(buffer,1,tamarc,f);
			if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
			fwrite(buffer,1,tamarc,tempFile);
			free(buffer);
			
			for(i = ordemTarg;i < tam;i++)
			{
				if(i == ordemMem-1) continue;
				gotoMembro(f,ca[i].ordem,ca);
				tamarc = ca[i].uidPerTam.st_size;//tamanho do arquivo em bytes
				while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
				{
					buffer = (char*) malloc (1024);
					resultado = fread(buffer,1,1024,f);
					if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
					fwrite(buffer,1,1024,tempFile);
					tamarc -= 1024;
					free(buffer);
				}
				buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
				resultado = fread(buffer,1,tamarc,f);
				if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
				fwrite(buffer,1,tamarc,tempFile);
				free(buffer);
			}
			break;
        }
        else//i == ordemMem-1
        {
        	for(i = ordemMem;i < ordemTarg;i++)
			{
				gotoMembro(f,ca[i].ordem,ca);
				tamarc = ca[i].uidPerTam.st_size;//tamanho do arquivo em bytes
				while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
				{
					buffer = (char*) malloc (1024);
					resultado = fread(buffer,1,1024,f);
					if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
					fwrite(buffer,1,1024,tempFile);
					tamarc -= 1024;
					free(buffer);
				}
				buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
				resultado = fread(buffer,1,tamarc,f);
				if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
				fwrite(buffer,1,tamarc,tempFile);
				free(buffer);
			}
			
			i = ordemMem-1;
			gotoMembro(f,ca[i].ordem,ca);
			tamarc = ca[i].uidPerTam.st_size;//tamanho do arquivo em bytes
			while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
			{
				buffer = (char*) malloc (1024);
				resultado = fread(buffer,1,1024,f);
				if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
				fwrite(buffer,1,1024,tempFile);
				tamarc -= 1024;
				free(buffer);
			}
			buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
			resultado = fread(buffer,1,tamarc,f);
			if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
			fwrite(buffer,1,tamarc,tempFile);
			free(buffer);
			
			for(i = ordemTarg;i < tam;i++)
			{
				gotoMembro(f,ca[i].ordem,ca);
				tamarc = ca[i].uidPerTam.st_size;//tamanho do arquivo em bytes
				while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
				{
					buffer = (char*) malloc (1024);
					resultado = fread(buffer,1,1024,f);
					if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
					fwrite(buffer,1,1024,tempFile);
					tamarc -= 1024;
					free(buffer);
				}
				buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
				resultado = fread(buffer,1,tamarc,f);
				if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
				fwrite(buffer,1,tamarc,tempFile);
				free(buffer);
			}
			break;
        }
    }
    fclose(f);
    fclose(tempFile);
    remove(v[2]);
    rename("temp.hu3",v[2]);
    return;
}

void extract(int c, char *v[], FILE *f, CABECALHO *ca, int tam)//extrai membros do arquivo
{
    arqVazio(f,v);
    long int resultado;
	int i;
	if(c == 3)
	{
		for(i = 0;i < tam;i++)
		{
            FILE *fileTemp = fopen(v[i],"wb");
            long int tamarc = ca[i].uidPerTam.st_size;
            gotoMembro(f,ca[i].ordem,ca);
            while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
            {
                char *buffer = (char*) malloc (1024);
                resultado = fread(buffer,1,1024,f);
                if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
                fwrite(buffer,1,1024,fileTemp);
                tamarc -= 1024;
                free(buffer);
            }
            char *buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
            resultado = fread(buffer,1,tamarc,f);
            if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
            fwrite(buffer,1,tamarc,fileTemp);
            free(buffer);
            fclose(fileTemp);
        }
	}
	else
	{
		int j,c;
		for(i = 3;i < c;i++)
		{
			for(j = 0,c = 0;j < tam;j++)
			{
				if(!strcmp(v[i],ca[j].nome))//caso seja igual o arquivo será extraido
				{
					FILE *fileTemp = fopen(v[i],"wb");
					long int tamarc = ca[j].uidPerTam.st_size;
					gotoMembro(f,ca[j].ordem,ca);
					while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
					{
						char *buffer = (char*) malloc (1024);
						resultado = fread(buffer,1,1024,f);
						if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
						fwrite(buffer,1,1024,fileTemp);
						tamarc -= 1024;
						free(buffer);
					}
					char *buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
                    resultado = fread(buffer,1,tamarc,f);
                    if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
                    fwrite(buffer,1,tamarc,fileTemp);
                    free(buffer);
                    fclose(fileTemp);
					c++;
					break;
				}
			}
			if(c == 0){ perror("Membro não existente"); }
		}
	}
	return;
}

void remover(int c, char *v[], FILE *f, CABECALHO *ca, int tam)//remove membros do arquivo
{
    while(true)
    {
    	long int resultado;
        arqVazio(f,v);
        int i,j,k;
        FILE *tempFile = fopen("temp.hu3", "wb");
        CABECALHO tempCa;
        bool buscando = true;
        for(i = 3;i < c && buscando;i++)
            for(j = 0;j < tam;j++)
                if(!strcmp(v[i],ca[j].nome))
                {
                    tempCa = ca[j];
                    tam--;
                    for(k = j;k < tam;k++) { ca[k] = ca[k+1]; ca[k].ordem--; }
                    ca = realloc(ca,sizeof(CABECALHO)*tam);
                    buscando = false;
                    break;
                }
        if(buscando) return;
        guardaValor(tempFile,ca,tam);
        for(i = 0;i < tam;i++)
        {
            if(i == j) { fseek(f,tempCa.uidPerTam.st_size,SEEK_CUR); continue; }
            long int tamarc = ca[i].uidPerTam.st_size;
            gotoMembro(f,ca[i].ordem,ca);
            while(tamarc > 1024)//passa 1Mb de cada vez para o arquivo
            {
                char *buffer = (char*) malloc (1024);
                resultado = fread(buffer,1,1024,f);
                if(resultado != 1024) { perror("Erro de leitura"); exit(1);}
                fwrite(buffer,1,1024,tempFile);
                tamarc -= 1024;
                free(buffer);
            }
            char *buffer = (char*) malloc (tamarc);//a partir daqui passa o restante, que é menor que 1024B
            resultado = fread(buffer,1,tamarc,f);
            if(resultado != tamarc) { perror("Erro de leitura"); exit(1);}
            fwrite(buffer,1,tamarc,tempFile);
            free(buffer);
        }
        fclose(f);
        fclose(tempFile);
        remove(v[2]);
        rename("temp.hu3",v[2]);
    }
	return;
}

void chow(CABECALHO *b, int tam)//da um show de caracteristicas dos membros do arquivo
{
	int i;
	for(i = 0;i < tam;i++)
	{
		printf("Nome:%s ",b[i].nome);//nome do arquivo

		printf("User ID:%d ",b[i].uidPerTam.st_uid);//User ID do arquivo

		printf("Permissoes:");//permissoes do arquivo
		printf( (b[i].uidPerTam.st_mode & S_IRUSR) ? "r" : "-");//permissoes do arquivo
		printf( (b[i].uidPerTam.st_mode & S_IWUSR) ? "w" : "-");
		printf( (b[i].uidPerTam.st_mode & S_IXUSR) ? "x" : "-");
		printf( (b[i].uidPerTam.st_mode & S_IRGRP) ? "r" : "-");
		printf( (b[i].uidPerTam.st_mode & S_IWGRP) ? "w" : "-");
		printf( (b[i].uidPerTam.st_mode & S_IXGRP) ? "x" : "-");
		printf( (b[i].uidPerTam.st_mode & S_IROTH) ? "r" : "-");
		printf( (b[i].uidPerTam.st_mode & S_IWOTH) ? "w" : "-");
		printf( (b[i].uidPerTam.st_mode & S_IXOTH) ? "x" : "-");//permissoes do arquivo

		printf(" Tamanho:%ld ",b[i].uidPerTam.st_size);//tamanho do arquivo

		printf("Data:%d/",b[i].data->tm_mday);//data do arquivo
		printf("%d/",b[i].data->tm_mon);
		printf("%d ",b[i].data->tm_year);
		printf("Hora:%d:",b[i].data->tm_hour);
		printf("%d:",b[i].data->tm_min);
		printf("%d ",b[i].data->tm_sec);//data do arquivo

		printf("Ordem:%d\n", b[i].ordem);//ordem do arquivo
	}
	return;
}

int main(int argc, char *argv[])
{
	if(argc == 1) { perror("Erro:falta argumento opção e o arquivo"); exit(1); }// Erros
	else if(argc == 2) { perror("Erro:arquivo não especificado"); exit(1); }
	else if(strcmp(argv[2],"-x") && argc == 3) { perror("Erro:nenhum membro foi especificado"); exit(1); }
	FILE *file = fopen(argv[2],"rb");
	CABECALHO *cabecalho;
	int tam;
	if(!strcmp(argv[2],"-i")) // Chamada de função
	{
		if(!arqvazio(file)) tam = recebeValor(file,cabecalho);
		incluir(argc,argv,file,cabecalho,tam);
	}
	else if(!strcmp(argv[2],"-a"))
	{
		if(!arqvazio(file)) tam = recebeValor(file,cabecalho);
		app(argc,argv,file,cabecalho,tam);
	}
	else if(!strcmp(argv[2],"-m"))
	{
		tam = recebeValor(file,cabecalho);
		move(argc,argv,file,cabecalho,tam);
	}
	else if(!strcmp(argv[2],"-x"))
	{
		tam = recebeValor(file,cabecalho);
		extract(argc,argv,file,cabecalho,tam);
	}
	else if(!strcmp(argv[2],"-r"))
	{
		tam = recebeValor(file,cabecalho);
		remover(argc,argv,file,cabecalho,tam);
	}
	else if(!strcmp(argv[2],"-c"))
	{
		arqVazio(file,argv);
		tam = recebeValor(file,cabecalho);
		chow(cabecalho,tam);
	}
	return 0;
}
