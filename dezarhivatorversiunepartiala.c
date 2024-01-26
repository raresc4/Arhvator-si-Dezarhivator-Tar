include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

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

long transformare(long size2)
{
  int i=0;
  if(size2%512==0)
    {
      return size2;
    }
  else
    {
      for(;;)
	{
	  if((512*i)>size2)
	    {
	      return 512*i;
	    }
	  else
	    {
	      i++;
	    }
	}
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
  Header buf;
  long cursor=0;
  while(fread(&buf,sizeof(Header),1,fin)>0)
    {
      FILE *fout=fopen(buf.name,"wb");
      if(fout==NULL)
	{
	  perror("eroare");
	  exit(-1);
	}
      cursor=ftell(fin);
      long size2=strtol(buf.size,NULL,8);
      int c=0;
      cursor+=transformare(size2);
      for(;;)
	{
	  if(ftell(fin)==cursor)
	    {
	      break;
	    }
	  c=fgetc(fin);
	  if(ftell(fin)<=(cursor+size2)){
	    printf("%ld\n",ftell(fin));
	  fwrite(&c,sizeof(char),1,fout);
	  }
	}
      if(fclose(fout)!=0)
	{
	  perror("eroare");
	  exit(-1);
	}
    }
  if(fclose(fin)!=0)
    {
      perror("eroare");exit(-1);
    }
  return 0;
}
