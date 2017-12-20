/*  -> Simple Console/CommandLine Assembler Application Using C11.
 *  -> Project Type -- Self/Educational.
 *  -> Institute -- University Institute Of Technology, Burdwan University.
 *  -> Owner/Code file Designer :
 *             @ Name - Palash Sarkar.
 *             @ Department - Computer Science And Engineering.
 *             @ Roll.Number - 2014_1038.
 *             @ Email - palashsarkar0007@gmail.com.
 *  -> Copyright Norms - Every piece of code given below 
 *                       has been written by 'Palash Sarkar (Tj07)'©,
 *                       and he holds the rights to the file. Not meant to be
 *                       copied or tampered without prior permission
 *                       from the author. 
 * -> --Note-- - Some comments were added here and there throughout the source code
 *               to verify the flow control and correctness of the program. Please
 *               ignore them.
 * -> About .out file - It has been named assemb2p.out and it was compiled using Xcode's cLang compiler
 *                      for C99 standard on a MacOS X (Sierra 10.12.6) machine. Please recompile if necessary
 *                      according to your OS.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct snode
{
   char sym[10];
   int offset;
   struct snode *next;
}SYMTAB;

typedef struct pnode
{
   char ins[5];
   int size;
}POT;

SYMTAB *s=NULL, *r=NULL;
POT p={"dd",4};

//void write();
void open();                         
void search(char *s);
void insert(char *pt, int l);
void writeto_symfile();

int main()
{
  //write();
  open();
  //printf("%s %d \n",s->next->sym,s->next->offset);
  //printf("%s %d \n",r->sym,r->offset);
  writeto_symfile();
  return (0);
}

//Uncomment this module/subroutine once for filling in the assembler program and the machine-opcode table and then recomment it!!

/*void write()
{
   FILE *rt;
   char chh;
   //char s[20];
   //int i=0;
   printf("Writing Assembler Program - \n");
   rt=fopen("AP.txt","w");
   if(rt==NULL)
   {
      printf("Cannot Open File \n");
      exit(1);
   }
   while((chh=getchar())!=EOF)
      fputc(chh,rt);
   fclose(rt);
   printf("Writing Machine Op-Code Table - \n");
   rt=fopen("MOTAB.txt","w");
   if(rt==NULL)
   {
      printf("Cannot Open File \n");
      exit(1);
   }
   while((chh=getchar())!=EOF)
      fputc(chh,rt);
   fclose(rt);
}*/

void open()
{
   FILE *fp;
   char ch;
   //char *p;
   char s[20];
   int i=0;
   //printf("In func op \n");
   fp=fopen("AP.txt","r");
   if(fp==NULL)
   {
      printf("Cannot Open File \n");
      exit(1);
   }
   while(1)
   {
      ch=fgetc(fp);
      //printf("%c \n",ch);
      if(ch==EOF)
         break;
      if(ch=='\n')
      {
         s[i]='\0';
         //puts(s);
         //p=parse(s);
         search(s);   
         i=0;
      }
      else
      {
         s[i]=ch;
         i++;
      }
   }
   fclose(fp);
   return;
}

void search(char *k)
{
   FILE *ft;
   char *a, ht;
   char ph[20], st[5], tx[20], q[20], p1[10], p2[10], off[5];
   int t=0, c=0;
   static int lc=0;
   //printf("HA AHA!! \n");
   a=k;
   while(*a!='\0')
   {
      ph[t]=*a;
      a++;
      t++;  
   }
   ph[t]=*a;
   //puts(ph);
   t=0;
   while(1)
   {
     //printf("!!\n");
     if(ph[t]==' ')
     {
        st[0]=ph[t+1];
        st[1]=ph[t+2];
        st[2]='\0';
        //puts(st);
        if(strcmp(st,p.ins)==0)
        {
            ph[t]='\0';
            //puts(ph);
            insert(ph,lc);
            lc=lc+p.size;
            //printf("%d\n",lc);
            return;
        }
        else
        {
           //printf("YUP!\n");
           break;
        }
     }
     t++;
   }
   ft=fopen("MOTAB.txt","r");
   if(ft==NULL)
   {
      printf("Cannot Open File \n");
      exit(1);
   }
   t=0;
   while(1)
   {
      ht=fgetc(ft);
      //printf("%c",ht);
      if(ht==EOF)
        break;
      if(ht=='\n')
      {
         tx[t]='\0';
         //puts(tx);
         t=0;
         while(tx[t]!='-')
         {
            t++;
         }
         off[0]=tx[t+1];
         off[1]='\0';
         tx[t]='\0';
         //puts(tx);
         //puts(off);
         if(strcmp(ph,tx)==0)
         {
            lc=lc+atoi(off);
            fclose(ft);
            return;        
         }
         else
         {
               t=0;
               while((ph[t]!=',')&&(tx[t]!=','))
               {
                    p1[t]=ph[t];
                    p2[t]=tx[t];
                    t++; 
               }
               p1[t]='\0';
               p2[t]='\0';
               //puts(p1);
               //puts(p2);
               if(strcmp(p1,p2)==0)
               {  
                    t=t+1;
                    while(ph[t]!='\0')
                    {
                        q[c]=ph[t];
                        c++;
                        t++;
                    }
                    q[c]='\0';               
                    insert(q,lc);
                    lc=lc+atoi(off);
                    fclose(ft);
                    return;
               }
               else
               {    
                    t=0; 
                    continue;
               }      
         }
               
      }
      else
      {
         tx[t]=ht;
         t++;
      }              
   }
   fclose(ft);
   return;
}

void insert(char *pt, int l)
{
     SYMTAB *temp, *aux;
     int h=0, count;
     char k[20];
     //printf("In 1 \n");
     while(*pt!='\0')
     {
         k[h]=*pt;
         pt++;
         h++;
     }
     //printf("%c",*pt);
     k[h]='\0';
     //puts(k);
     h=0;
     if((s==NULL)&&(r==NULL))
     {
         temp=(SYMTAB *)malloc(sizeof(SYMTAB));
         while(k[h]!='\0')
         {
             temp->sym[h]=k[h];
             h++;
         }
         temp->sym[h]='\0';
         temp->offset=l;
         temp->next=NULL;
         s=temp;
         r=temp;
     }
     else
     {
        aux=s;
        while(aux!=NULL)
        {
            if(strcmp(k,aux->sym)==0)
            {
                count=1;
                break;
            }
            else
            {
                count=0;
                aux=aux->next;
                continue;
            }
        }
        if(count==1)
        { 
             return;
        }
        else
        {
            temp=(SYMTAB *)malloc(sizeof(SYMTAB));
            //printf("%d\n",temp);
            while(k[h]!='\0')
            {
                temp->sym[h]=k[h];
                h++;
            }
            temp->sym[h]='\0';
            //printf("%d\n",l);
            ///puts(temp->sym);
            temp->offset=l;
            temp->next=NULL;
            r->next=temp;
            r=r->next;
        }
     }
     return;
}

void writeto_symfile()
{
    FILE *fr;
    SYMTAB *btw;
    char cch, wr[10];
    int kt;
    //printf("In 2 \n");
    fr=fopen("Symtab.txt","w");
    btw=s;
    while(btw!=NULL)
    {
        kt=0;
        //puts(btw->sym);
        while(btw->sym[kt]!='\0')
        {
            fputc(btw->sym[kt],fr);
            kt++;
        }
        cch=' ';
        fputc(cch,fr);
        //itoa(btw->offset,wr,10); --don't use for C11/C99, as it is not a standard lib function, use 'snprintf' instead.
        snprintf(wr,10,"%d",btw->offset);
        kt=0;
        while(wr[kt]!='\0')
        {
             fputc(wr[kt],fr);
             kt++;
        }
        cch='\n';
        fputc(cch,fr);
        btw=btw->next;
        //printf("%d\n",btw);
    }
    //fputc('T',fr);
    fclose(fr);
    return;
}                      
