#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct kod
{
	kod *next;
	char byt;
};

int Format(FILE *file)
{
	FILE *Format=NULL;
	char formatsign[32], i, c;
	if ((Format = fopen("Format.txt","r")) == NULL)
		return 1; 
	if (fscanf(Format,"%s",formatsign) != 1)
		return 2
	if (fclose(Format) != 0)
	    return 3;
	for (i=0;formatsign[i] != '\0';i++)
    {
	    if ((c = fgetc(file)) != formatsign[i])
	       return 4;
    }
	return 0;	
}

int signature(FILE *file)
{
	kod *p, *first, *Date;
	char c;
	long int indent;
	FILE *Signature=NULL;
	if ((Signature = fopen("Signature.txt","r")) == NULL)
	    return 1;
	if (fscanf(Signature,"%li",&indent) != 1)
	    return 2;
	if (fseek(file,indent,SEEK_SET) != 0)    
        return 3;
	p = (kod*)malloc(sizeof(kod));
	if (p==NULL)
	    return 4;
	p->next = NULL;
	Date = p;
	first = p;
	if (c = fgetc(Signature) == EOF)
	    return 5;
	if (fscanf(Signature,"%c",&p->byt) != 1)
	    return 6;                   
	while ((c = fgetc(Signature)) != EOF)
	{
		p = (kod*)malloc(sizeof(kod));
		if (p==NULL)
		   return 7;
		p->next = NULL;
		Date->next = p;                   
		Date = p;
		Date->byt = c;	
	}
	if (fclose(Signature) != 0)
	    return 8;
	p = first;                         
	while (p != NULL)               
	{
		if ((c = fgetc(file)) == EOF)
		    return 9;
		if (p->byt != c)
            return 10;
		p = p->next;		
	}
	free(p);
	free(first);
	free(Date);
	return 0;
}

int main()
{
	FILE *file=NULL;
	char way[500];
	if (printf("Введите путь к файлу\n") < 0)
	    return 1;
	if (scanf("%[^\n]s",way) != 1)
	    return 2;
	if ((file = fopen(way,"r")) == NULL)
	    {
	    	if (printf("Не удалось открыть файл с таким именем\n") < 0)
			    return 3;
			if (system("pause") != 0)
			    return 4;
	    	return 0;
		}
    if (Format(file) != 0)
    {
    	if(printf("Формат данного файла не соответствует искомому") < 0)
    	    return 5;
    	if (system("pause") != 0)
		    return 6;
    	return 0;
	}
    if (signature(file) != 0)
    {
    	if (printf("Сигнатура данного файла не соответствует искомой\n") < 0)
			return 7;
		if (system("pause") != 0)
			return 8;
		return 0;	    
	}
	if (fclose(file) != 0)
	    return 9;
    if (printf("Сигнатура данного файла соответствует искомой\n%s\n",way) < 0)
	    return 10;
	if (system("pause") != 0)
	    return 11;
	return 0;
} 
