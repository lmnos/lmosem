#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char* retn_ifilenm(int gc,char* argv[])
{
	if(gc<1||NULL==argv)
	{
		return NULL;
	}
	for(int i=0;i<gc;i++)
	{
		if(strcmp("-i",argv[i])==0)
		{
			if(i<(gc-1))
			{
				return argv[i+1];
			}
		}
	}
	return NULL;
}

char* retn_ofilenm(int gc,char * argv[])
{
	if(gc<1||NULL==argv)
	{
		return NULL;
	}
	for(int i=0;i<gc;i++)
	{
		if(strcmp("-o",argv[i])==0)
		{
			if(i<(gc-1))
			{
				return argv[i+1];
			}
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if(argc<4)
	{
		printf("pram argc:%d\n", argc);
		exit(1);
	}
	char* ifnm=retn_ifilenm(argc,argv);
	char* ofnm=retn_ofilenm(argc,argv);
	FILE* ifp=fopen(ifnm,"r");
    FILE* ofp=fopen(ofnm,"w+");
    if (NULL==ifp||NULL==ofp)
    {
    	printf("open fail:%s:%s\n", ifnm,ofnm);
    	exit(1);
    }
	char fch=fgetc(ifp); 
	while(fch!=EOF)
    {
    	if('['==fch)
    	{
    		fch='\t';
    	}
        fputc(fch,ofp);
        fch=fgetc(ifp);
    } 
    fclose(ifp); 
    fclose(ofp);    
	return 0;
}