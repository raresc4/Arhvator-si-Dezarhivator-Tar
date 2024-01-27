#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h> 


long int marime(char *nume)
{
    FILE *f=fopen(nume,"rb");
    if(f==NULL)
    {
        perror("eroare");
        exit(-1);
    }
    long int c=0;
    fseek(f,0,SEEK_END);
    c=ftell(f);
    if(fclose(f)!=0)
    {
        perror("eroare");
        exit(-1);
    }
    return c;
}

char *marime2(long int numar) {
    char *rezultat = malloc(12 * sizeof(char));
    if (rezultat == NULL) {
      perror("eroare");
        exit(-1);
    }
    snprintf(rezultat, 12, "%011lo", numar);
    return rezultat;
}

typedef struct
{                              /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[8];               /* 148 */
  char typeflag;                /* 156 */
  char linkname[100];           /* 157 */
  char magic[6];                /* 257 */
  char version[2];              /* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[155];             /* 345 */
  char padding[12];                                /* 500 */
}Header;

unsigned int calcularechecksum(const Header *header) {
    unsigned int sum = 0;
    const unsigned char *ptr = (const unsigned char *)header;
    for (int i = 0; i < 512; ++i) {
        if (i < 148 || i >= 156) {
            sum += (unsigned char)ptr[i];
        }
	else {
            sum += ' ';
        }
    }
    return sum;
}


char *functietimp(long int timp)
{
  char *rezultat=malloc(sizeof(char)*12);
  if(rezultat==NULL)
    {
      perror("eroare");
      exit(-1);
    }
  sprintf(rezultat,"%ld",timp);
  return rezultat;
}

void punerepezero(char *string,int biti)
{
  for(int i=0;i<biti-1;i++)
    {
      string[i]=0x00;
    }
}

char* format(unsigned int num) {
  char* result=malloc((8*sizeof(char)));
		      if(result==NULL)
			{
			  perror("eroare");
			  exit(-1);
			}
    snprintf(result,8, "%06o", num);
    return result;
}

void punerepezero2(char *string,int inceput,int final)
{
  for(int i=inceput;i<final;i++)
    {
      string[i]=0x00;
    }
}

void punerespatiu(char *string,int final)
{
  for(int i=0;i<final;i++)
    {
      string[i]=' ';
    }
}

int main(int argc,char **argv)
{
  FILE *fin=fopen(argv[1],"rb");
  if(fin==NULL)
    {
      perror("eroare");
      exit(-1);
    }
  Header buf1;
  fread(&buf1,sizeof(Header),1,fin);
  printf("%s\n",buf1.size);
  long int timp=time(NULL);
  for(int i=2;i<argc;i++)
    {
      Header buf;
      strcpy(buf.name,argv[i]); 
      for(int j=strlen(argv[i]);j<99;j++)
	{
	  buf.name[j]=0x00;
	}
      buf.name[99]='\0';
      strcpy(buf.mode,"0000644");
      buf.mode[7]='\0';
      strcpy(buf.uid,"0001750");
      buf.uid[7]='\0';
      strcpy(buf.gid,"0001750");
      buf.gid[7]='\0';
      char *aux = marime2(marime(argv[i]));
      strcpy(buf.size,aux);
      buf.size[11]='\0';
      char *aux2=functietimp(timp);
      strcpy(buf.mtime,aux2);
      buf.mtime[11]='\0';
      buf.typeflag='0';
      for(int j=0;j<99;j++)
	{
	  buf.linkname[j]=0x00;
	}
      buf.name[99]='\0';
      strcpy(buf.magic,"ustar");
      buf.version[0]=0x00;
      buf.version[1]=0x00;
      strcpy(buf.uname,getlogin());
      for(int j=strlen(getlogin());j<31;j++)
	{
	  buf.uname[j]=0x00;
	}
      buf.uname[31]='\0';
      strcpy(buf.gname,getlogin());
      for(int j=strlen(getlogin());j<31;j++)
	{
	  buf.gname[j]=0x00;
	}
      buf.gname[31]='\0';
      for(int j=0;j<7;j++)
	{
	  buf.devmajor[j]=0x00;
	}
      buf.devmajor[7]='\0';
      for(int j=0;j<7;j++)
	{
	  buf.devminor[j]=0x00;
	}
      buf.devminor[7]='\0';
      for(int j=0;j<154;j++)
	{
	  buf.prefix[j]=0x00;
	}
      buf.prefix[154]='\0';
      for(int j=0;j<11;j++)
	{
	  buf.padding[j]=0x00;
	}
      buf.padding[11]='\0';
      for(int j=0;j<7;j++)
	{
	  buf.chksum[j]=0x00;
	}
      buf.chksum[7]='\0';
      char *checksum=format(calcularechecksum(&buf));
      strcpy(buf.chksum,checksum);
      printf("%s\n",buf.chksum);
	free(checksum);
      free(aux);
      free(aux2);
    }
  if(fclose(fin)!=0)
    {
      perror("eroare");
      exit(-1);
    }
  return 0;
} 
