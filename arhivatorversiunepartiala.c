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
    snprintf(rezultat, 12, "%011ld", numar);
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
  long int timp=time(NULL);
  for(int i=1;i<argc;i++)
    {
      Header buf;
      strcpy(buf.name,argv[i]);
      punerepezero2(buf.name,strlen(argv[i]),99);
      strcpy(buf.mode,"0000644");
      strcpy(buf.uid,"0001750");
      strcpy(buf.gid,"0001750");
      char *aux = marime2(marime(argv[i]));
      strcpy(buf.size,aux);
      char *aux2=functietimp(timp);
      strcpy(buf.mtime,aux2);
      buf.typeflag='0';
      punerepezero(buf.linkname,100);
      strcpy(buf.magic,"ustar");
      buf.version[0]=0x00;
      buf.version[1]=0x00;
      strcpy(buf.uname,getlogin());
      punerepezero2(buf.uname,strlen(getlogin()),31);
      strcpy(buf.gname,getlogin());
      punerepezero2(buf.gname,strlen(getlogin()),31);
      punerepezero(buf.devmajor,8);
      punerepezero(buf.devminor,8);
      punerepezero(buf.prefix,155);
      punerepezero(buf.padding,12);
      punerespatiu(buf.chksum,8);
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
