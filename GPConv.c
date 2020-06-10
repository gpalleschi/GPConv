#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>

char *SearchIN(char *,char *,char *);
void EFPM(int,char **);
void Confr(int,char **);

void main(int argv,char **argc)
{
 char version[40] = "10.6 - 20.12.2004 18:25";
 char PAROLA[500];
 char STRINGA_APP[500];
 char STRINGA_INP[500];
 int tot_byte=0;
 int prima = 0;
 int indsalida;
 int i = 0;
 int y = 0;
 int x = 0;
 int u=0;
 int k;
 int ind_salida = 0;
 int ul = 0;
 int cos;
 char rua;
 int della;
 char auxiliar[2];
 int lonchar,j,pos,flag;
 int posicion=0;
 char param[512];
 int edito = 1;
 int flag_hex = 0;
 int posizione_prec = -1; 
 int flag_ascii = 0;
 int flag_optimize = 0;
 int flag_RMNL = 0;
 int flag_EST = 0;
 int numero_byte_dove_sono_arrivato_a_porre_nl = 0;
 int tot_param = 0;
 int max_valore = 0;
 int min_valore = 100000000;
 char salida[512];
 char caso_c[10];
 char caso_d[10];
 char caso_e[9];
 struct tabella_parametri
 {
   char STRINGA[1000];
   int LUNGHEZZA;
 } TAB_PARAM[50];

 struct Tabella_edit
 {
   char tipo;
   int dal;
   int al;
   char valore[2000];
 } TAB_EDIT[50];

 char APPO[500];
 
 char a;
 int c;
 char Appo_lunghezza_record_ascii[100];
 char lunghezza_record_ascii[1000];
 if ( argv == 1 || !memcmp(argc[1],"help",4) )
 {
    printf("\n GPConv by Giovanni Palleschi - 1998-2020 ");
    printf("\n --------------------------------------------------------------- ");
    printf("\n Version : %s",version);
    printf("\n --------------------------------------------------------------- ");
    printf("\n The program executes the following functions :\n");
    printf("\n 1) Insert new line before specified strings ");
    printf("\n    if present the character X accepts any character \n");
    printf("\n    ex. GPConv 00810c 40X10c < file_input > file_output \n");
    printf("\n 2) Insert new line every n byte, specifying this number after the parameter -r\n ");
    printf("\n    ex. GPConv -r128 < file_input > file_output \n");
    printf("\n 3) Specifying the hex parameter executes an ascii conversion ");
    printf("\n    and as an option you can insert the new line character as specified in points 1 and 2\n");
    printf("\n    ex. GPConv hex 00810c < file_input > file_output ");
    printf("\n    ex. GPConv hex < file_input > file_output (in this way it executes only convercion) \n");
    printf("\n 4) Specifying the -RMNL parameter removes the new line ");
    printf("\n    this option has priority over the others \n");
    printf("\n    ex. GPConv -RMNL < file_input > file_output \n");
    printf("\n 5) Specifying the ascii parameter converts the file from ascii to hex");
    printf("\n    this option has priority over the others \n");
    printf("\n    ex. GPConv ascii < file_input > file_output \n");
    printf("\n 6) Specifying the -EST parameter and the following parameters: byte from, byte to, input type ");
    printf("\n    where the input type can be ascii or bcd ");
    printf("\n    ex. GPConv -EST 200 400 bcd < file_input > file_output \n");
    printf("\n 7) Specifying the -ERec parameter extracts all specified records and successive parameters");
    printf("\n    ex. GPConv -ERec 170000 170001 < file1 > file2");
    printf("\n        extracts from file1 all the records between 170000 and 170001.\n");
    printf("\n 8) Specifying the EFPM parameter you enter the EFPM modality specifying help you enter the help");
    printf("\n    ex. GPConv EFPM help \n");
    printf("\n 9) Specifying the Confr parameter you enter the Comparation file mode specifying help you enter the help:");
    printf("\n    es. GPConv Confr help ");
    printf("\n    es. GPConv Confr Structure_File file1 file2\n");
    printf("\n 10) Specifying the -E parameter, enter the edit option where the possible options are : ");
    printf("\n      -In[...] insert byte n in the line what is between the [...] ( _ for spaces)");
    printf("\n    es. GPConv -E -I3[select * from] -I6[;] < file1 > file2");
    printf("\n      -Sd,a[...] makes a substitution from byte d to byte a, with which it is expressed between [...] ");
    printf("\n    es. GPConv -E -S3,5[_] -S10,12[;_] < file1 > file2");
    printf("\n      -Cn[...] expresses a condition if byte n is present the string between [...] ");
    printf("\n                executes all modifications until the next -C is present");
    printf("\n    es. GPConv -E -C4[41811] -S3,5[_] -S10,12[;_] < file1 > file2");
    printf("\n      -EbAs[3,5] makes a conversion from Ebcdic to Ascii ");
    printf("\n                 es. f1f2f3 --> 123  ");
    printf("\n    es. GPConv -E -EsAs[1,6] < file1 > file2\n");
    printf("\n      -EsAs[3,6] makes a conversation from Exadecimal to Ascii");
    printf("\n    es. GPConv -E -AsEs[1,6] < file1 > file2\n");
    printf("\n      -AsEs[3,6] makes a conversation from Ascii to Exadecimal");
    printf("\n    es. GPConv -E -EbAs[1,6] < file1 > file2\n");
    printf("\n      -AsEb[3,7] makes a conversion from Ascii to Ebcdic ");
    printf("\n                 es. 123 --> f1f2f3 ");
    printf("\n    es. GPConv -E -AsEb[1,3] < file1 > file2\n");
    printf("\n    For all these options, the edit order must be rispectate in byte terms from");
    printf("\n In general both input and output are standard input and output.\n");
    return;
 }

 int indx;
 int indte;
 char stringa_num[40];
 char appo_stringa_E[10000];
 char appo_stringa_U[15000];
 char appo_stringa_Conv[10000];
 int DAL_EDIT;
 int AL_EDIT;
 int LUGHEZZA_VALORE_EDIT;
 int LUGHEZZA_RECORD;
 int CONST_VALORE_INS;
 int CONST_VALORE_SOS;

 if ( !memcmp(argc[1],"Confr",5) )
 {
   Confr(argv,argc);
   return;
 }

 if ( !memcmp(argc[1],"EFPM",4) )
 {
   EFPM(argv,argc);
   return;
 }

 if ( !memcmp(argc[1],"-EST",5) )
 {
    int tot_byte=0;
    int numbyte_dal = atoi(argc[2]);
    int numbyte_al = atoi(argc[3]);
    if ( !memcmp(argc[4],"bcd",3) )
    {
      int c;
      while((c = getchar()) != EOF)
      {
           tot_byte ++;
           if ( tot_byte > numbyte_al ) break;
   
           if ( tot_byte >= numbyte_dal 
             && tot_byte <= numbyte_al ) 
           {
             if ( c < 16 ) printf("0");
             printf("%0x",c); 
           }
      }
    }
    else
    {
      if ( !memcmp(argc[4],"ascii",3) )
      {
        char c;
        while((c = getchar()) != EOF)
        {
          tot_byte ++;
          if ( tot_byte > numbyte_al ) break;
  
          if ( tot_byte >= numbyte_dal 
            && tot_byte <= numbyte_al ) 
          {
            printf("%c",c); 
          }
        }
      }
      else
      {
        printf("\nFor option -EST needs to specify the range from to byte and input type (ascii or bcd )");
        printf("\n    es. GPConv -EST 200 400 bcd < file_input > file_output \n");
      }
    }
    return;
 }

 if ( !memcmp(argc[1],"-ERec",5) )
 {
    int tot_rec=1;
    int rec_dal = atoi(argc[2]);
    int rec_al = atoi(argc[3]);
    char c;
    while((c = getchar()) != EOF)
    {
      if ( (tot_rec >= rec_dal && tot_rec <= rec_al) ) printf("%c",c);
      if (c == '\n') tot_rec+=1;  
      if ( tot_rec > rec_al ) break;
    }
    return;
 }

 if ( !memcmp(argc[1],"-E",2) )
 {
   indte = 0;
   for (i=2;i<argv;i++)
   {
     if ( !memcmp(argc[i],"-C",2) )
     {
       TAB_EDIT[indte].tipo = 'F';
       if ( !(TAB_EDIT[indte].dal = atoi(SearchIN(argc[i],"C","["))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Field Wrong -->%s<--\n",argc[i],SearchIN(argc[i],"C","["));
         return;
       }
       memcpy(&TAB_EDIT[indte].valore[0],SearchIN(argc[i],"[","]"),strlen(SearchIN(argc[i],"[","]")));
       indte++;
     }
     if ( !memcmp(argc[i],"-EsAs",5) )
     {
       TAB_EDIT[indte].tipo = 'y';
       if ( !(TAB_EDIT[indte].dal = atoi(SearchIN(argc[i],"[",","))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Field Wrong -->%s<--\n",argc[i],SearchIN(argc[i],"[",","));
         return;
       }
       if ( !(TAB_EDIT[indte].al = atoi(SearchIN(argc[i],",","]"))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Field Wrong -->%s<--\n",argc[i],SearchIN(argc[i],",","]"));
         return;
       }
       if ( TAB_EDIT[indte].al <= TAB_EDIT[indte].dal || TAB_EDIT[indte].dal == TAB_EDIT[indte].al )
       {
         printf("\n What fuck of values are from %d to %d ???? \n\n",TAB_EDIT[indte].dal,TAB_EDIT[indte].al);
         return;
       }
       if ( (( TAB_EDIT[indte].al - TAB_EDIT[indte].dal + 1))%2 )
       {
         printf("\n What fuck are you doing from %d to %d ???? ",TAB_EDIT[indte].dal,TAB_EDIT[indte].al);
         printf("\n You don't understand.");
         printf("\n Every hexadecimal char is composed by two bytes in ascii  ");
         printf("\n you put %d that in my home are odd ",TAB_EDIT[indte].al-TAB_EDIT[indte].dal+1);
         printf("\n please put correct values.\n\n ");
         return;
       }
       memset(TAB_EDIT[indte].valore,0,1);
       indte++;
     }
     if ( !memcmp(argc[i],"-EbAs",5) )
     {
       TAB_EDIT[indte].tipo = 'e';
       if ( !(TAB_EDIT[indte].dal = atoi(SearchIN(argc[i],"[",","))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Wrong Field -->%s<--\n",argc[i],SearchIN(argc[i],"[",","));
         return;
       }
       if ( !(TAB_EDIT[indte].al = atoi(SearchIN(argc[i],",","]"))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Wrong Field -->%s<-- \n",argc[i],SearchIN(argc[i],",","]"));
         return;
       }
       if ( TAB_EDIT[indte].al <= TAB_EDIT[indte].dal || TAB_EDIT[indte].dal == TAB_EDIT[indte].al )
       {
         printf("\n What fuck of values are you put from %d to %d ???? \n\n",TAB_EDIT[indte].dal,TAB_EDIT[indte].al);
         return;
       }
       if ( (( TAB_EDIT[indte].al - TAB_EDIT[indte].dal + 1))%2 )
       {
         printf("\n What fuck are you doing from %d to %d ???? ",TAB_EDIT[indte].dal,TAB_EDIT[indte].al);
         printf("\n You don't understand. ");
         printf("\n Every ebcdic char is composed by two bytes in ascii");
         printf("\n you put %d that in my home are odd ",TAB_EDIT[indte].al-TAB_EDIT[indte].dal+1);
         printf("\n  please put correct values\n\n ");
         return;
       }

       memset(TAB_EDIT[indte].valore,0,1);
       indte++;
     }
     if ( !memcmp(argc[i],"-AsEs",5) )
     {
       TAB_EDIT[indte].tipo = 'x';
       if ( !(TAB_EDIT[indte].dal = atoi(SearchIN(argc[i],"[",","))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Wrong Field -->%s<--\n",argc[i],SearchIN(argc[i],"[",","));
         return;
       }
       if ( !(TAB_EDIT[indte].al = atoi(SearchIN(argc[i],",","]"))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Wrong Field -->%s<--\n",argc[i],SearchIN(argc[i],",","]"));
         return;
       }
       if ( TAB_EDIT[indte].al <= TAB_EDIT[indte].dal || TAB_EDIT[indte].dal == TAB_EDIT[indte].al )
       {
         printf("\n What fuck of values are you put from %d to %d ???? \n\n",TAB_EDIT[indte].dal,TAB_EDIT[indte].al);
         return;
       }
       memset(TAB_EDIT[indte].valore,0,1);
       indte++;
     }
     if ( !memcmp(argc[i],"-AsEb",5) )
     {
       TAB_EDIT[indte].tipo = 'a';
       if ( !(TAB_EDIT[indte].dal = atoi(SearchIN(argc[i],"[",","))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Wrong Field -->%s<--\n",argc[i],SearchIN(argc[i],"[",","));
         return;
       }
       if ( !(TAB_EDIT[indte].al = atoi(SearchIN(argc[i],",","]"))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Wrong Field -->%s<--\n",argc[i],SearchIN(argc[i],",","]"));
         return;
       }
       if ( TAB_EDIT[indte].al <= TAB_EDIT[indte].dal || TAB_EDIT[indte].dal == TAB_EDIT[indte].al )
       {
         printf("\n What fuck of values are you put from %d to %d ???? \n\n",TAB_EDIT[indte].dal,TAB_EDIT[indte].al);
         return;
       }
       memset(TAB_EDIT[indte].valore,0,1);
       indte++;
     }
     if ( !memcmp(argc[i],"-S",2) )
     {
       TAB_EDIT[indte].tipo = 'S';
       if ( !(TAB_EDIT[indte].dal = atoi(SearchIN(argc[i],"S",","))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Wrong Field -->%s<--\n",argc[i],SearchIN(argc[i],"S",","));
         return;
       }
       if ( !(TAB_EDIT[indte].al = atoi(SearchIN(argc[i],",","["))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Wrong Field -->%s<--\n",argc[i],SearchIN(argc[i],",","["));
         return;
       }
       memcpy(&TAB_EDIT[indte].valore[0],SearchIN(argc[i],"[","]"),strlen(SearchIN(argc[i],"[","]")));
       indte++;
     }
     if ( !memcmp(argc[i],"-I",2) )
     {
       TAB_EDIT[indte].tipo = 'I';
       if ( !(TAB_EDIT[indte].dal = atoi(SearchIN(argc[i],"I","["))) )
       {
         printf("\n Error Numeric Convertion : Error in parameter for edit --> %s Wrong Field -->%s<--\n",argc[i],SearchIN(argc[i],"I","["));
         return;
       }
       memcpy(&TAB_EDIT[indte].valore[0],SearchIN(argc[i],"[","]"),strlen(SearchIN(argc[i],"[","]")));
       if ( !TAB_EDIT[indte].valore )
       {
         printf("\n Error : Wrong Parameter for edit --> %s \n",argc[i]);
         return;
       }
       indte++;
     }
     if ( indte > 1 )
     { 
       if ( TAB_EDIT[indte-1].dal < TAB_EDIT[indte-2].dal && TAB_EDIT[indte-1].tipo != 'F' && TAB_EDIT[indte-2].tipo != 'F' )
       {
         printf("\n Error de Edit: edit order not respected.\n");
         return;
       }
     }
   }

   indx = 0; 

   a = getchar();
   if ( a == EOF ) return;
   do
   {
     if ( (a != '\n' ) && indx <= 9999 )
     {
       memcpy(&appo_stringa_E[indx],&a,1);
       indx++;
     }
     else
     {
       if ( indx > 9999 ) 
       { 
         printf("\n Error : record > 9999 in Edit phase \n");
         return;
       }
       appo_stringa_E[indx] = 0;
       memset(appo_stringa_U,0,15000);
       memcpy(appo_stringa_U,appo_stringa_E,strlen(appo_stringa_E)); 
/*
       LUGHEZZA_RECORD = strlen(appo_stringa_E);
*/
       LUGHEZZA_RECORD = indx; 
       CONST_VALORE_INS = 0;
       CONST_VALORE_SOS = 0;
       for(i=0;i<indte;i++)
       { 
/*
printf("\n TAB_EDIT[i].tipo   --> %c \n",TAB_EDIT[i].tipo);
printf("\n TAB_EDIT[i].dal    --> %d \n",TAB_EDIT[i].dal);
printf("\n TAB_EDIT[i].valore -->%s<-- \n",TAB_EDIT[i].valore);
*/
         AL_EDIT = TAB_EDIT[i].al + CONST_VALORE_INS;
         if ( TAB_EDIT[i].al > LUGHEZZA_RECORD ) AL_EDIT = LUGHEZZA_RECORD;
         DAL_EDIT = TAB_EDIT[i].dal + CONST_VALORE_INS;
         LUGHEZZA_VALORE_EDIT = strlen(TAB_EDIT[i].valore); 
         if ( TAB_EDIT[i].tipo == 'F' )
         {
           if ( !memcmp(&appo_stringa_E[DAL_EDIT-1],TAB_EDIT[i].valore,LUGHEZZA_VALORE_EDIT) )
           {
             edito = 1;
           }
           else
           {
             edito = 0;
           }
         }
         if ( edito )
         {
           if ( TAB_EDIT[i].tipo == 'x' )
           {
             if ( TAB_EDIT[i].dal <= LUGHEZZA_RECORD ) 
             {
               memcpy(param,&appo_stringa_E[DAL_EDIT-1],AL_EDIT-DAL_EDIT+1);
               param[AL_EDIT-DAL_EDIT+1] = 0;
               ind_salida = 0;
               for(k=0;k<strlen(param);k++)
               {
                 della = param[k];  
                 if ( della < 16 )
                 {
                   salida[ind_salida] = '0';
                   ind_salida+=1;
                 }
                 sprintf(&salida[ind_salida],"%0x",della);
                 ind_salida+=2;
                 salida[ind_salida] = 0;
               }
             }
             memcpy(appo_stringa_U,&appo_stringa_E[0],DAL_EDIT);
             memcpy(&appo_stringa_U[DAL_EDIT-1],salida,strlen(salida));
             memcpy(&appo_stringa_U[DAL_EDIT-1+strlen(salida)],&appo_stringa_E[AL_EDIT],strlen(appo_stringa_E)+(strlen(salida)/2)-(DAL_EDIT+strlen(salida))+1);
             LUGHEZZA_RECORD += strlen(salida)/2;
             appo_stringa_U[LUGHEZZA_RECORD] = 0;
             memcpy(appo_stringa_E,appo_stringa_U,LUGHEZZA_RECORD);
             appo_stringa_E[LUGHEZZA_RECORD] = 0;
             CONST_VALORE_INS+=strlen(salida)/2;
           }
           if ( TAB_EDIT[i].tipo == 'y' )
           {
             if ( TAB_EDIT[i].dal <= LUGHEZZA_RECORD ) 
             {
               memcpy(param,&appo_stringa_E[DAL_EDIT-1],AL_EDIT-DAL_EDIT+1); 
               param[AL_EDIT-DAL_EDIT+1] = 0;
               u=0;
               ind_salida = 0;
               ul = 0;
               for ( k=0;k<AL_EDIT-DAL_EDIT+1;k+=2) 
               {
                 cos = 16;
                 ul = 0;
                 for (u=k;u<k+2;u++) 
                 {
                   rua = param[u];  
                   switch (rua)
                   {
		     case '0':
		        ul=ul+(0*cos);
		        break;
		     case '1':
		        ul=ul+(1*cos);
			break;
		     case '2':
		     	ul=ul+(2*cos);
			break;
		     case '3':
			ul=ul+(3*cos);
			break;
		     case '4':
			ul=ul+(4*cos);
			break;
		     case '5':
			ul=ul+(5*cos);
			break;
		     case '6':
			ul=ul+(6*cos);
			break;
		     case '7':
			ul=ul+(7*cos);
			break;
		     case '8':
			ul=ul+(8*cos);
			break;
		     case '9':
			ul=ul+(9*cos);
			break;
		     case 'a':
			ul=ul+(10*cos);
			break;
		     case 'b':
			ul=ul+(11*cos);
			break;
		     case 'c':
			ul=ul+(12*cos);
			break;
		     case 'd':
			ul=ul+(13*cos);
			break;
		     case 'e':
			ul=ul+(14*cos);
			break;
		     case 'f':
			ul=ul+(15*cos);
			break;
	           }
                   cos = 1;
                 }
                 sprintf(&salida[ind_salida],"%c",ul);
                 ind_salida+=1;
                 salida[ind_salida] = 0;
               }
               memcpy(appo_stringa_U,&appo_stringa_E[0],DAL_EDIT);
               memcpy(&appo_stringa_U[DAL_EDIT-1],salida,strlen(salida));
               memcpy(&appo_stringa_U[DAL_EDIT-1+strlen(salida)],&appo_stringa_E[AL_EDIT],strlen(appo_stringa_E)-(DAL_EDIT+strlen(salida
)));
               appo_stringa_U[AL_EDIT+strlen(appo_stringa_E)-(DAL_EDIT+strlen(salida))-1] = 0;

/*
               LUGHEZZA_RECORD = AL_EDIT+strlen(appo_stringa_E)-(DAL_EDIT+strlen(salida));
*/
               CONST_VALORE_INS += (strlen(appo_stringa_U) - strlen(appo_stringa_E));
               LUGHEZZA_RECORD = strlen(appo_stringa_U);
               memcpy(appo_stringa_E,appo_stringa_U,LUGHEZZA_RECORD);
               appo_stringa_E[LUGHEZZA_RECORD] = 0;

             }
           }
           if ( TAB_EDIT[i].tipo == 'e' )
           {
             if ( TAB_EDIT[i].dal <= LUGHEZZA_RECORD ) 
             {
               memcpy(param,&appo_stringa_E[DAL_EDIT-1],AL_EDIT-DAL_EDIT+1); 
               param[AL_EDIT-DAL_EDIT+1] = 0;
               strcpy(caso_c,"ABCDEFGHI\0");
               strcpy(caso_d,"JKLMNOPQR\0");
               strcpy(caso_e,"STUVWXYZ\0");
               posicion=0;
               flag=0;
               lonchar=strlen(param);
               for (j=0;j<lonchar;)
               {
                 if ((param[j]== 'c') && (flag!=1))
                 {
                   j++;
                   auxiliar[0]=param[j];
                   auxiliar[1]='\0';
                   pos=atoi(auxiliar);
                   salida[posicion]=caso_c[--pos];
                   salida[++posicion]='\0';
                   flag=1;
                 }
                 if ((param[j]== 'd') && (flag!=1))
                 {
                   j++;
                   auxiliar[0]=param[j];
                   auxiliar[1]='\0';
                   pos=atoi(auxiliar);
                   salida[posicion]=caso_d[--pos];
                   salida[++posicion]='\0';
                   flag=1;
                 }
                 if ((param[j]== 'e') && (flag!=1))
                 {
                   j++;
                   auxiliar[0]=param[j];
                   auxiliar[1]='\0';
                   pos=atoi(auxiliar);
                   pos=pos-2;
                   salida[posicion]=caso_e[pos];
                   salida[++posicion]='\0';
                   flag=1;
                 }
                 if ((param[j]== 'f') && (flag!=1))
                 {
                   j++;
                   salida[posicion]=param[j];
                   salida[++posicion]='\0';
                   flag=1;
                 }
                 if ((param[j]== '4') && (flag!=1))
                 {
                   j++;
                   if ( param[j]=='0' )
                   {
                     salida[posicion]=' ';
                     salida[++posicion]='\0';
                     flag=1;
                   }
                 }
                 if ( flag!=0 )
                 {
                   j++;
                   flag=0;
                 }
                 else
                 {
                   printf("Error en la conversion\n");
                   return;
                 }
	       }

               memcpy(appo_stringa_U,&appo_stringa_E[0],DAL_EDIT);
               memcpy(&appo_stringa_U[DAL_EDIT-1],salida,strlen(salida));
               memcpy(&appo_stringa_U[DAL_EDIT-1+strlen(salida)],&appo_stringa_E[AL_EDIT],strlen(appo_stringa_E)-(DAL_EDIT+strlen(salida)));
               appo_stringa_U[AL_EDIT+strlen(appo_stringa_E)-(DAL_EDIT+strlen(salida))-1] = 0;
               CONST_VALORE_INS += (strlen(appo_stringa_U) - strlen(appo_stringa_E));
               LUGHEZZA_RECORD = strlen(appo_stringa_U);
/*
               LUGHEZZA_RECORD = AL_EDIT+strlen(appo_stringa_E)-(DAL_EDIT+strlen(salida));
*/
               memcpy(appo_stringa_E,appo_stringa_U,LUGHEZZA_RECORD);
               appo_stringa_E[LUGHEZZA_RECORD] = 0;
             }
           }
           if ( TAB_EDIT[i].tipo == 'a' )
           {
             if ( TAB_EDIT[i].dal <= LUGHEZZA_RECORD ) 
             {
               indsalida = 0;
               memcpy(param,&appo_stringa_E[DAL_EDIT-1],AL_EDIT-DAL_EDIT+1);
               param[AL_EDIT-DAL_EDIT+1] = 0;
               lonchar = strlen(param);
	       for (j=0;j<lonchar;j++)
	       {
	         if ( !memcmp(&param[j]," ",1) ) memcpy(&salida[indsalida],"40",2);
                 else
	         if ( !memcmp(&param[j],"#",1) ) memcpy(&salida[indsalida],"7b",2);
                 else
	         if ( !memcmp(&param[j],"A",1) ) memcpy(&salida[indsalida],"c1",2);
                 else
	         if ( !memcmp(&param[j],"B",1) ) memcpy(&salida[indsalida],"c2",2);
                 else
	         if ( !memcmp(&param[j],"C",1) ) memcpy(&salida[indsalida],"c3",2);
                 else
                 if ( !memcmp(&param[j],"D",1) ) memcpy(&salida[indsalida],"c4",2);
                 else
                 if ( !memcmp(&param[j],"E",1) ) memcpy(&salida[indsalida],"c5",2);
                 else
                 if ( !memcmp(&param[j],"F",1) ) memcpy(&salida[indsalida],"c6",2);
                 else
                 if ( !memcmp(&param[j],"G",1) ) memcpy(&salida[indsalida],"c7",2);
                 else
                 if ( !memcmp(&param[j],"H",1) ) memcpy(&salida[indsalida],"c8",2);
                 else
                 if ( !memcmp(&param[j],"I",1) ) memcpy(&salida[indsalida],"c9",2);
                 else
                 if ( !memcmp(&param[j],"J",1) ) memcpy(&salida[indsalida],"d1",2);
                 else
                 if ( !memcmp(&param[j],"K",1) ) memcpy(&salida[indsalida],"d2",2);
                 else
                 if ( !memcmp(&param[j],"L",1) ) memcpy(&salida[indsalida],"d3",2);
                 else
                 if ( !memcmp(&param[j],"M",1) ) memcpy(&salida[indsalida],"d4",2);
                 else
                 if ( !memcmp(&param[j],"N",1) ) memcpy(&salida[indsalida],"d5",2);
                 else
                 if ( !memcmp(&param[j],"O",1) ) memcpy(&salida[indsalida],"d6",2);
                 else
                 if ( !memcmp(&param[j],"P",1) ) memcpy(&salida[indsalida],"d7",2);
                 else
                 if ( !memcmp(&param[j],"Q",1) ) memcpy(&salida[indsalida],"d8",2);
                 else
                 if ( !memcmp(&param[j],"R",1) ) memcpy(&salida[indsalida],"d9",2);
                 else
                 if ( !memcmp(&param[j],"S",1) ) memcpy(&salida[indsalida],"e2",2);
                 else
                 if ( !memcmp(&param[j],"T",1) ) memcpy(&salida[indsalida],"e3",2);
                 else
                 if ( !memcmp(&param[j],"U",1) ) memcpy(&salida[indsalida],"e4",2);
                 else
                 if ( !memcmp(&param[j],"V",1) ) memcpy(&salida[indsalida],"e5",2);
                 else
                 if ( !memcmp(&param[j],"W",1) ) memcpy(&salida[indsalida],"e6",2);
                 else
                 if ( !memcmp(&param[j],"X",1) ) memcpy(&salida[indsalida],"e7",2);
                 else
                 if ( !memcmp(&param[j],"Y",1) ) memcpy(&salida[indsalida],"e8",2);
                 else
                 if ( !memcmp(&param[j],"Z",1) ) memcpy(&salida[indsalida],"e9",2);
                 else
                 if ( !memcmp(&param[j],"0",1) ) memcpy(&salida[indsalida],"f0",2);
                 else
                 if ( !memcmp(&param[j],"1",1) ) memcpy(&salida[indsalida],"f1",2);
                 else
                 if ( !memcmp(&param[j],"2",1) ) memcpy(&salida[indsalida],"f2",2);
                 else
                 if ( !memcmp(&param[j],"3",1) ) memcpy(&salida[indsalida],"f3",2);
                 else
                 if ( !memcmp(&param[j],"4",1) ) memcpy(&salida[indsalida],"f4",2);
                 else
                 if ( !memcmp(&param[j],"5",1) ) memcpy(&salida[indsalida],"f5",2);
                 else
                 if ( !memcmp(&param[j],"6",1) ) memcpy(&salida[indsalida],"f6",2);
                 else
                 if ( !memcmp(&param[j],"7",1) ) memcpy(&salida[indsalida],"f7",2);
                 else
                 if ( !memcmp(&param[j],"8",1) ) memcpy(&salida[indsalida],"f8",2);
                 else
                 if ( !memcmp(&param[j],"f",1) ) memcpy(&salida[indsalida],"ff",2);
                 else
                 if ( !memcmp(&param[j],"9",1) ) memcpy(&salida[indsalida],"f9",2);
                 else
                 {
                   printf("Error en la conversion\n");
                   return;
                 }
                 indsalida+=2;
               }
               memcpy(appo_stringa_U,&appo_stringa_E[0],DAL_EDIT);
               memcpy(&appo_stringa_U[DAL_EDIT-1],salida,strlen(salida));
               memcpy(&appo_stringa_U[DAL_EDIT-1+strlen(salida)],&appo_stringa_E[AL_EDIT],strlen(appo_stringa_E)+(strlen(salida)/2)-(DAL_EDIT+strlen(salida))+1);
               LUGHEZZA_RECORD += strlen(salida)/2;
               appo_stringa_U[LUGHEZZA_RECORD] = 0;
               memcpy(appo_stringa_E,appo_stringa_U,LUGHEZZA_RECORD);
               appo_stringa_E[LUGHEZZA_RECORD] = 0;
               CONST_VALORE_INS+=strlen(salida)/2;
             }
           }
           if ( TAB_EDIT[i].tipo == 'I' )
           {
             if ( TAB_EDIT[i].dal <= LUGHEZZA_RECORD ) 
             {
               memcpy(&appo_stringa_U[DAL_EDIT-1],TAB_EDIT[i].valore,LUGHEZZA_VALORE_EDIT); 
               memcpy(&appo_stringa_U[DAL_EDIT+LUGHEZZA_VALORE_EDIT-1],&appo_stringa_E[DAL_EDIT-1],LUGHEZZA_RECORD-DAL_EDIT+1);
               LUGHEZZA_RECORD += LUGHEZZA_VALORE_EDIT;
               memcpy(appo_stringa_E,appo_stringa_U,LUGHEZZA_RECORD);
               appo_stringa_E[LUGHEZZA_RECORD] = 0;
               CONST_VALORE_INS += LUGHEZZA_VALORE_EDIT;
             }
           }
           if ( TAB_EDIT[i].tipo == 'S' )
           {
             if ( TAB_EDIT[i].dal <= LUGHEZZA_RECORD && TAB_EDIT[i].al >= TAB_EDIT[i].dal ) 
             {
               memcpy(&appo_stringa_U[DAL_EDIT-1],TAB_EDIT[i].valore,LUGHEZZA_VALORE_EDIT); 
               memcpy(&appo_stringa_U[DAL_EDIT+LUGHEZZA_VALORE_EDIT-1],&appo_stringa_E[AL_EDIT],LUGHEZZA_RECORD - AL_EDIT + DAL_EDIT + 1);
               LUGHEZZA_RECORD += LUGHEZZA_VALORE_EDIT;
               memcpy(appo_stringa_E,appo_stringa_U,LUGHEZZA_RECORD);
               appo_stringa_E[LUGHEZZA_RECORD] = 0;
               CONST_VALORE_INS += LUGHEZZA_VALORE_EDIT - (AL_EDIT - DAL_EDIT + 1);

             }
           }
         }
       }
/*
printf("\n LUGHEZZA_RECORD     = %d \n",LUGHEZZA_RECORD);
printf("\n appo_stringa_U     ->%.*s<-\n",LUGHEZZA_RECORD,appo_stringa_U);
*/
       printf("%.*s\n",LUGHEZZA_RECORD,appo_stringa_U);
       indx = 0; 
     }
   }
   while ( (a = getchar()) != EOF );
 }

 for (i=1;i<argv;i++)
 {
   if ( memcmp(argc[i],"hex",strlen(argc[i])) )
   {
     if ( !memcmp(argc[i],"-RMNL",5) )
     {
       flag_RMNL = 1; 
       break;
     }
/*
     if ( !memcmp(argc[i],"-o",2) )
     {
       flag_optimize = 1; 
     }
*/
     if ( !memcmp(argc[i],"ascii",5) )
     {
       flag_ascii = 1; 
       break;
     }
     if ( !memcmp(argc[i],"-r",2) )
     {
       memset(lunghezza_record_ascii,'\0',1000);
       memcpy(Appo_lunghezza_record_ascii,argc[i],strlen(argc[i])); 
       memcpy(lunghezza_record_ascii,&Appo_lunghezza_record_ascii[2],strlen(argc[i])-2);
       if ( !atoi(lunghezza_record_ascii) )
       {
         printf("\n Error in the parameter %s after -r you must specify\n",argc[i]);
         printf(" a number that represents the record length.\n");
         return;
       }
       else   
       {
         memset(&TAB_PARAM[tot_param].STRINGA,'X',atoi(lunghezza_record_ascii));
         TAB_PARAM[tot_param].STRINGA[atoi(lunghezza_record_ascii)] = 0;
         TAB_PARAM[tot_param].LUNGHEZZA = atoi(lunghezza_record_ascii);
         if ( TAB_PARAM[tot_param].LUNGHEZZA > max_valore ) max_valore = TAB_PARAM[tot_param].LUNGHEZZA;
         if ( TAB_PARAM[tot_param].LUNGHEZZA < min_valore ) min_valore = TAB_PARAM[tot_param].LUNGHEZZA;
       }
     }
     else
     {
       memcpy(&TAB_PARAM[tot_param].STRINGA,argc[i],strlen(argc[i]));
       TAB_PARAM[tot_param].STRINGA[strlen(argc[i])] = 0;
       TAB_PARAM[tot_param].LUNGHEZZA = strlen(argc[i]);
       if ( strlen(argc[i]) > max_valore ) max_valore = strlen(argc[i]);
       if ( strlen(argc[i]) < min_valore ) min_valore = strlen(argc[i]);
     }
     tot_param++;
   }
   else flag_hex = 1;
 }
 if ( flag_RMNL == 1 )
 {
   while((a = getchar()) != EOF)
   {
     if ( a != '\n' ) printf("%c",a);
   }
   return; 
 }
 if ( flag_ascii == 1 )
 {
    int flag;
    while((c = getchar()) != EOF)
    {
      flag=0;
      if ( c != '\n' )
      {
         switch (c)
         {
		case '0':
			i=0*16;
			break;
		case '1':
		        i=1*16;
			break;
		case '2':
			i=2*16;
			break;
		case '3':
			i=3*16;
			break;
		case '4':
			i=4*16;
			break;
		case '5':
			i=5*16;
			break;
		case '6':
			i=6*16;
			break;
		case '7':
			i=7*16;
			break;
		case '8':
			i=8*16;
			break;
		case '9':
			i=9*16;
			break;
		case 'a':
			i=10*16;
			break;
		case 'b':
			i=11*16;
			break;
		case 'c':
			i=12*16;
			break;
		case 'd':
			i=13*16;
			break;
		case 'e':
			i=14*16;
			break;
		case 'f':
			i=15*16;
			break;
	}
     }
     else
     {
	flag=1;
     }
     if ( flag != 1 )
     {
	if ((c=getchar()) != EOF)
	{
          switch (c)
	  {
	  		case '0':
       				i=i+0;
				break;
	  		case '1':
				i=i+1;
				break;
			case '2':
				i=i+2;
				break;
	  		case '3':
				i=i+3;
				break;
	  		case '4':
				i=i+4;
				break;
	  		case '5':
				i=i+5;
				break;
	  		case '6':
				i=i+6;
				break;
			case '7':
				i=i+7;
				break;
	  		case '8':
				i=i+8;
				break;
	  		case '9':
				i=i+9;
				break;
	  		case 'a':
				i=i+10;
				break;
	  		case 'b':
				i=i+11;
				break;
	  		case 'c':
				i=i+12;
				break;
	  		case 'd':
				i=i+13;
				break;
	  		case 'e':
				i=i+14;
				break;
	  		case 'f':
				i=i+15;
				break;
	   }
	}
     }
     if ( i > 128 )
	i=i-256;
     if ( flag != 1)
		printf("%c",i);
   }
   return;
 }
 if ( flag_hex == 1 && argv == 2 )
 {
   while((c = getchar()) != EOF)
   {
        if ( c < 16 ) printf("0");
        printf("%0x",c);
   }
   return;
 }
 if ( flag_hex == 0 )
 {
   while((a = getchar()) != EOF)
   {

/* Inizio Modifica per null letti in input 22121999 */
        if ( a == '\0' ) a = ' ';
/* Fine Modifica per null letti in input 22121999 */

        numero_byte_dove_sono_arrivato_a_porre_nl += 1 ;
        if( tot_byte == max_valore )
        {
          for (y=0;y<tot_param;y++)
          {
            for (x=0;x<TAB_PARAM[y].LUNGHEZZA;x++)
            {
              if (  memcmp(&APPO[x],&TAB_PARAM[y].STRINGA[x],1) &&
                    memcmp(&TAB_PARAM[y].STRINGA[x],"X",1) 
                 ) break;
            }
            if ( x == TAB_PARAM[y].LUNGHEZZA )
            { 
              if ( prima == 1 )
              {
                 if ( posizione_prec == -1 && flag_optimize == 1 )
                 {
                   posizione_prec = numero_byte_dove_sono_arrivato_a_porre_nl;
                 }
                 if ( posizione_prec == (numero_byte_dove_sono_arrivato_a_porre_nl - x -1)  && flag_optimize == 1 ) 
                 {
                   numero_byte_dove_sono_arrivato_a_porre_nl = 0;
                   printf("\n");
                 }
                 else
                 {
                   numero_byte_dove_sono_arrivato_a_porre_nl = 0;
                   if ( flag_optimize == 0 )
                   {
                     printf("\n");
                   }
                 }
              }
              printf("%.*s",TAB_PARAM[y].LUNGHEZZA,APPO);
              tot_byte = tot_byte - TAB_PARAM[y].LUNGHEZZA;
              memcpy(STRINGA_APP,&APPO[TAB_PARAM[y].LUNGHEZZA],tot_byte);
              memcpy(&APPO,STRINGA_APP,tot_byte);
              prima = 1;
              break;
            }
          }
          if ( y == tot_param )
          {
            printf("%.*s",1,APPO);
            memcpy(STRINGA_APP,&APPO[1],tot_byte - 1);
            memcpy(&APPO,STRINGA_APP,tot_byte - 1);
            tot_byte -= 1;
          }
        }
        sprintf(&APPO[tot_byte],"%c",a); 
        tot_byte++;
   }
   if( tot_byte == max_valore )
   {
          for (y=0;y<tot_param;y++)
          {
            for (x=0;x<TAB_PARAM[y].LUNGHEZZA;x++)
            {
              if ( memcmp(&APPO[x],&TAB_PARAM[y].STRINGA[x],1) && memcmp(&TAB_PARAM[y].STRINGA[x],"X",1) ) break;
            }
            if ( x == TAB_PARAM[y].LUNGHEZZA )
            { 
              if ( prima == 1 )
              {
                 printf("\n");
              }
              printf("%.*s",TAB_PARAM[y].LUNGHEZZA,APPO);
              break;
            }
          }
          if ( y == tot_param )
          {
            printf("%.*s",tot_byte,APPO);
          }
   }
   else
   printf("%.*s",tot_byte,APPO);
 }
 else
 {
   while((c = getchar()) != EOF)
   {
        numero_byte_dove_sono_arrivato_a_porre_nl += 1 ;
        if( tot_byte >= max_valore )
        {
          while ( tot_byte >= max_valore )
          {
            for (y=0;y<tot_param;y++)
            {
              for (x=0;x<TAB_PARAM[y].LUNGHEZZA;x++)
              {
                if ( memcmp(&APPO[x],&TAB_PARAM[y].STRINGA[x],1) && memcmp(&TAB_PARAM[y].STRINGA[x],"X",1) ) break;
              }
              if ( x == TAB_PARAM[y].LUNGHEZZA )
              { 
                if ( prima == 1 )
                {
                 if ( posizione_prec == -1 && flag_optimize == 1 )
                 {
                   posizione_prec = numero_byte_dove_sono_arrivato_a_porre_nl;
                 }
                 if ( posizione_prec == numero_byte_dove_sono_arrivato_a_porre_nl -x && flag_optimize == 1 ) 
                 {
                   numero_byte_dove_sono_arrivato_a_porre_nl = 0;
                   printf("\n");
                 }
                 else
                 {
                   if ( flag_optimize == 0 )
                   {
                     printf("\n");
                   }
                 }
                }
                else
                {
                  if ( flag_optimize == 1 )
                  {
                    posizione_prec = numero_byte_dove_sono_arrivato_a_porre_nl;
                    numero_byte_dove_sono_arrivato_a_porre_nl = 0;
                  }
                }
                printf("%.*s",TAB_PARAM[y].LUNGHEZZA,APPO);
                tot_byte = tot_byte - TAB_PARAM[y].LUNGHEZZA;
                memcpy(STRINGA_APP,&APPO[TAB_PARAM[y].LUNGHEZZA],tot_byte);
                memcpy(&APPO,STRINGA_APP,tot_byte);
                prima = 1;
                break;
              }
            }
            if ( y == tot_param )
            {
              printf("%.*s",1,APPO);
              memcpy(STRINGA_APP,&APPO[1],tot_byte - 1);
              memcpy(&APPO,STRINGA_APP,tot_byte - 1);
              tot_byte -= 1;
            }
          }
        }
        if ( c < 16 ) 
        {
          sprintf(&APPO[tot_byte],"0");
          sprintf(&APPO[tot_byte + 1],"%0x",c); 
        }
        else sprintf(&APPO[tot_byte],"%0x",c); 
        tot_byte+=2;
/*
        printf("\n APPO -->%.*s<-- \n",tot_byte,APPO);
*/
   }
   if( tot_byte >= max_valore )
   {
      while ( tot_byte >= max_valore )
      {
        for (y=0;y<tot_param;y++)
        {
          for (x=0;x<TAB_PARAM[y].LUNGHEZZA;x++)
          {
             if ( memcmp(&APPO[x],&TAB_PARAM[y].STRINGA[x],1) && memcmp(&TAB_PARAM[y].STRINGA[x],"X",1) ) break;
          }
          if ( x == TAB_PARAM[y].LUNGHEZZA )
          { 
            if ( prima == 1 )
            {
              printf("\n");
            }
            printf("%.*s",TAB_PARAM[y].LUNGHEZZA,APPO);
            tot_byte = tot_byte - TAB_PARAM[y].LUNGHEZZA;
            memcpy(STRINGA_APP,&APPO[TAB_PARAM[y].LUNGHEZZA],tot_byte);
            memcpy(&APPO,STRINGA_APP,tot_byte);
            prima = 1;
            break;
          }
        }
        if ( y == tot_param )
        {
           printf("%.*s",1,APPO);
           memcpy(STRINGA_APP,&APPO[1],tot_byte - 1);
           memcpy(&APPO,STRINGA_APP,tot_byte - 1);
           tot_byte -= 1;
        }
      }
   }
   printf("%.*s\n",tot_byte,APPO);
 }
}

char *SearchIN(char *Stringa,char *Valore_Da,char *Valore_A)
{
  char *valore_ritorno;
  valore_ritorno = (char *)malloc(2000);
  int indsea = 0;
  int g;
  int flag = 0;
  memset(valore_ritorno,0,2000);
  for (g=0;g<strlen(Stringa);g++)
  {
    if ( flag == 1 && !memcmp(&Stringa[g],Valore_A,strlen(Valore_A)) )
    {
      break;
    }
    if ( flag == 1 )
    {
      if ( !memcmp(&Stringa[g],"_",1) )
      {
        memcpy(&valore_ritorno[indsea]," ",1);
      } 
      else
      {
        memcpy(&valore_ritorno[indsea],&Stringa[g],1);
      }
      indsea++; 
    }
    if ( !memcmp(&Stringa[g],Valore_Da,strlen(Valore_Da)) ) flag = 1;
  }
/*
printf("\n VALORE RITORNO SEARCH IN -->%s<-- \n",valore_ritorno);
*/
  return(valore_ritorno);
}
/***********************************************************************************************/

void EFPM(int argv,char **argc)
{
 
 struct struttura 
 { 
		char NOME[15];
		char INIZIO[6];
		char LUNGHEZZA[6];
		char FLAG;
                char VALORE[40];
                char STOP;
 } STRU[2000];

 struct strut_cont
 { 
		char CAMPO[15];
		char VALORE[80];
                unsigned long int CONTATORE;
 } CONT[20000];

 struct strut_tot
 { 
		char CAMPO[15];
		char VALORE[80];
		char NOME_CAMPO[15];
                int  TOTALE;
 } TOT[20000];

 struct strut_tot2
 { 
		char CAMPO[15];
                int  TOTALE;
 } TOT2[2000];

 struct strut_piccolo
 { 
		char VALORE[50];
 } Piccolo[1000];

 struct strut_grande
 { 
		char VALORE[50];
 } Grande[1000];

 int TABELLA_Cont[20000];
 int TABELLA_Inc[2000];
 int TABELLA_TOT[20000];
 int TABELLA_FUN[20000];
 int TABELLA_Grande[1000];
 int TABELLA_Piccolo[1000];
 int Appo_Cont;
 int inizio_inc;
 int indice_inc;
 int Tot_Grande = 0;
 int Tot_Piccolo = 0;
 int Tot_Appo_Cont = 0;
 int Tot_Appo_Inc = 0;
 int Tot_Appo_TOT = 0;
 int Tot_Appo_FUN = 0;
 int ind_cont = 0;
 int u = 0;
 int ll = 0;
 int tot_elem_cont = 0;
 int tot_elem_TOT = 0;
 int TOTALE_RECORD = 0;
 int totale_contate = 0;
 char prec_nome[20];
 memset(prec_nome,'0',15);
 char stringa_appoggio[200];
 char c;
 int indice_appo = 0;
 if ( !memcmp(argc[2],"help",4) || argv == 2 )
 {
     printf("\n The EFPM option (Multilevel Parametric File Extractor) accepts the following parameters : \n"); 
     printf("\n   - Structure File "); 
     printf("\n   - Input File (standard input) in ascii format\n"); 
     printf("\n   In Output are produced these files : "); 
     printf("\n   - Output File (standard output)"); 
     printf("\n   - File LOG_COUNTER (Only with Flag Values : C,+,P,G e I)\n "); 
     printf("\n   The structure File has this format : "); 
     printf("\n     - FIELD NAME   = 15 byte"); 
     printf("\n     - from byte    = 6 byte"); 
     printf("\n     - length       = 6 byte"); 
     printf("\n     - FLAG         = 1 byte"); 
     printf("\n     - VALUE        = n byte\n"); 
     printf("\n es. --->PULSOS         000100000005U00003<---\n");
     printf("\n Values permitted for field FLAG are the following :");
     printf("\nU              ---> EQUAL TO ");
     printf("\nD              ---> DIFFERENT TO ");
     printf("\nC              ---> COUNT THE PRESENCE OF THE CHAIN ​​IN THE RECORDS ");
     printf("\n               ---> ( if we add the parameter Z it will do the extraction without zeros and if we put a ");
     printf("\n                     digit only refers to that number of digits ) " );
     printf("\n>              ---> GREATER THAN VALUE");
     printf("\n<              ---> LESS THAN VALUES");
     printf("\nZ              ---> FIND ALL RECORDS THAT BEGIN WITH THE STRING FOLLOWED BY Z " );
     printf("\nR              ---> FIND THE STRING WITHIN THE FIELD         ");
     printf("\nV              ---> FIND ALL RECORDS THAT DO NOT CONTAIN THE STRING" ) ;
     printf("\nI              ---> MAKE A CAT OF THE FIELDS THAT APPEAR WITH THIS FLAG, (also supports the");
     printf("\n                    Zn format Like FLAG C )"); 
     printf("\nX              ---> DOES NOT PERFORM ANY CONTROL  ");                                  
     printf("\n+              ---> OF ALL THE RECORDS THAT IT EXTRACTS IF THE FIELD IS NUMERICAL, IT ADDS THEM only if "); 
     printf("\n                    some cat or count of the records has been made");  
     printf("\nP              ---> LOOK FOR THE SMALLEST VALUE  ");                                  
     printf("\nF              ---> MATHEMATIC FUNCTION ");                                  
     printf("\n                    Ex L(001,008) long significant digits of the field that starts at byte 1 and is long 8 byte");
     printf("\n                    Ex V(015,009) numerical value of the field that starts at byte 15 and is long 9 byte");
     printf("\n                    Ex string in structure file : ");
     printf("\n                    ");
     printf("\n                    field Name     from  length Function max 40 byte            ");
     printf("\n                    ------------------------------------------------------------");
     printf("\n                    FUNC           000000000040FV(001,004)+V(005,004)<V(009,004)");
     printf("\nS              ---> STRING FUNCTION ");                                  
     printf("\n                    Ex Z(001,008) STRING without 0 from left ");
     printf("\n                    Ex V(015,009) numeric value of field from byte 15 and with length of 9 bytes");
     printf("\n                    Ex String in structure file : ");
     printf("\n                    ");
     printf("\n                    field Name     from  length Function max 40 byte            ");
     printf("\n                    ------------------------------------------------------------");
     printf("\n                    FUNC           000000000040FV(001,004)+V(005,004)<V(009,004)");
     printf("\n Example of running the process : GPConv EFPM Structure_File < FILEINPUT > FILEOUTPUT\n");                                  
     return;
 }
 
 FILE *fs;
 FILE *fc;

 for (u=0;u<20000;u++) TOT[u].TOTALE = 0;
 char NOMBRE_PREC[15];
 fs  = fopen(argc[2],"r");
 if(fs == 0)
 {
  printf("\n %s \n",strerror(errno));
  printf("Error in opening file %s\n",argc[2]);
  return;
 }

 int FLAG,x,y,lun,i,inizioi,lunghezzai,lenappo;
 int PRIMO_ZERO;
 int FLAG_BUONO = 0;
 int IndS = 0;
 int IndS_real = 0;
 char STRINGA[41];
 char APPOS[200];
 char APPO_INC[200];
 char APPO_NUM[3];
 char APPO[1000];
 char APPOl[7];
 char APPOi[7];
 fgets(APPOS,200,fs);
 while ( feof(fs) != 16 ) 
 {
   memcpy(&STRU[IndS],&APPOS,68);  
   if ( !memcmp(&STRU[IndS].FLAG,"C",1) )
   {
      TABELLA_Cont[Tot_Appo_Cont] = IndS;   
      Tot_Appo_Cont += 1;
   }
   if ( !memcmp(&STRU[IndS].FLAG,"F",1) )
   {
      TABELLA_FUN[Tot_Appo_FUN] = IndS;   
      Tot_Appo_FUN += 1;
   }
   if ( !memcmp(&STRU[IndS].FLAG,"+",1) )
   {
      TABELLA_TOT[Tot_Appo_TOT] = IndS;   
      Tot_Appo_TOT += 1;
   }
   if ( !memcmp(&STRU[IndS].FLAG,"I",1) )
   {
      TABELLA_Inc[Tot_Appo_Inc] = IndS;   
      Tot_Appo_Inc += 1;
   }
   if ( !memcmp(&STRU[IndS].FLAG,"P",1) )
   {
      TABELLA_Piccolo[Tot_Piccolo] = IndS;   
      memcpy(&Piccolo[IndS],"XXXXXXXXXX",10);
      Tot_Piccolo += 1;
   }
   if ( !memcmp(&STRU[IndS].FLAG,"G",1) )
   {
      TABELLA_Grande[Tot_Grande] = IndS;   
      memcpy(&Grande[IndS],"XXXXXXXXXX",10);
      Tot_Grande += 1;
   }
   if ( memcmp(&STRU[IndS].FLAG,"X",1) ) 
   { 
     IndS += 1;
   }

   fgets(APPOS,200,fs);
 }
 fclose(fs);



 
 FLAG_BUONO = 0;

 indice_appo = 0;
 memset(APPO,'\0',200);
 while ( (c = getchar()) != EOF )
 {
   memcpy(&APPO[indice_appo],&c,1);
   indice_appo++;
   if ( c == '\n' )
   {
      indice_appo = 0;
      memset(&NOMBRE_PREC,' ',15);
      for ( i=0;i<IndS;++i)
      {
           if ( memcmp(&NOMBRE_PREC,&STRU[i].NOME,15) )
           {
             FLAG_BUONO = 0;
             memcpy(&NOMBRE_PREC,&STRU[i].NOME,15);
           }
	   memcpy(&APPOi,&STRU[i].INIZIO,6);
	   memcpy(&APPOl,&STRU[i].LUNGHEZZA,6);
	   APPOi[6] = 0;
	   APPOl[6] = 0;
	   inizioi = atoi(APPOi); 
	   lunghezzai = atoi(APPOl); 
           
           if ( !memcmp(&STRU[i].FLAG,"R",1) ||
                !memcmp(&STRU[i].FLAG,"V",1) ||
                !memcmp(&STRU[i].FLAG,"Z",1) )
           {
              for (y=0;y<40;++y)
              {
                if ( (STRU[i].VALORE[y] == '\n' && memcmp(&STRU[i].FLAG,"Z",1)) || ((!memcmp(&STRU[i].VALORE[y]," ",1) || STRU[i].VALORE[y] == '\n') && !memcmp(&STRU[i].FLAG,"Z",1)) ) 
                {
                  break;
                }
                memcpy(&STRINGA,&STRU[i].VALORE,y+1);
              }
              if ( y > lunghezzai )
              { 
	             if ( memcmp(&STRU[i].NOME,&STRU[i+1].NOME,15) && !FLAG_BUONO ) break; 
              }
              lenappo = lunghezzai + inizioi;
              lun = y;
              y = inizioi;
              FLAG = 0;
              PRIMO_ZERO = 0;
              while ( 1 )
              {
/*
                printf("\n APPO[y]    -->%.*s<-- \n",lun,&APPO[y]);
                printf("\n STRINGA    -->%.*s<-- \n",lun,STRINGA);
                printf("\n lenappo    -->%d \n",lenappo);
                printf("\n y          -->%d \n",y);
                printf("\n lun        -->%d \n",lun);
                printf("\n ---------------- \n");
*/
                if ( !memcmp(&APPO[y],&STRINGA,lun) && memcmp(&STRU[i].FLAG,"Z",1) ) 
                {
	             break; 
                }
                if ( !memcmp(&APPO[y],&STRINGA,lun) && !memcmp(&STRU[i].FLAG,"Z",1)  
                     && memcmp(&APPO[y],"0",1) && PRIMO_ZERO == 0)  
                {
	             break; 
                }
                if ( !memcmp(&STRU[i].FLAG,"Z",1) && PRIMO_ZERO == 0 && memcmp(&APPO[y],"0",1) )
                {
                  PRIMO_ZERO = 1;
                }
                if ( (lenappo - y) < lun+1 )
                { 
                  FLAG = 1;
	          break; 
                }
                y += 1;
              }
/*
	      printf("\n FLAG ---> %d \n",FLAG);
	      printf("\n .FLAG --->%c<--- \n",STRU[i].FLAG);
	      printf("\n i ---> %d \n", i);
*/
              if ( FLAG == 1 && ( !memcmp(&STRU[i].FLAG,"R",1) || !memcmp(&STRU[i].FLAG,"Z",1) ) ) 
              {
	           if ( memcmp(&STRU[i].NOME,&STRU[i+1].NOME,15) && !FLAG_BUONO ) break; 
              }

              if ( FLAG == 1 && ( memcmp(&STRU[i].FLAG,"R",1) && memcmp(&STRU[i].FLAG,"Z",1) ) ) 
              {
                   FLAG_BUONO = 1;
              }

              if ( FLAG == 0 && !memcmp(&STRU[i].FLAG,"V",1) ) 
              {
	           if ( memcmp(&STRU[i].NOME,&STRU[i+1].NOME,15) && !FLAG_BUONO ) break; 
              }

              if ( FLAG == 0 && memcmp(&STRU[i].FLAG,"V",1) ) 
              {
                   FLAG_BUONO = 1;
              }
           }
           else
           {
/* 
	   printf("\n ========================= \n");
	   printf("\n APPO[inizioi] -->%.*s<-- \n",lunghezzai,&APPO[inizioi]);
	   printf("\n STRU[i].VALO  -->%.*s<-- \n",lunghezzai,STRU[i].VALORE);
	   printf("\n STRU[i].INIZ  -->%.*s<-- \n",6,STRU[i].INIZIO);
	   printf("\n STRU[i].LUNG  -->%.*s<-- \n",6,STRU[i].LUNGHEZZA);
	   printf("\n STRU[i].NOME  -->%.*s<-- \n",15,STRU[i].NOME);
	   printf("\n inizioi          %d \n",inizioi);
	   printf("\n lunghezzai       %d \n",lunghezzai);
	   printf("\n                     \n");
*/  
	      if ( !memcmp(&STRU[i].FLAG,"U",1) && memcmp(&APPO[inizioi],&STRU[i].VALORE,lunghezzai) )
	      {
                   if ( memcmp(&STRU[i].NOME,&STRU[i+1].NOME,15) && !FLAG_BUONO ) break; 
	      }

	      if ( !memcmp(&STRU[i].FLAG,"U",1) && !memcmp(&APPO[inizioi],&STRU[i].VALORE,lunghezzai) )
	      {
                   FLAG_BUONO = 1; 
	      }

	      if ( !memcmp(&STRU[i].FLAG,"D",1) && !memcmp(&APPO[inizioi],&STRU[i].VALORE,lunghezzai) )
	      {
	           if ( memcmp(&STRU[i].NOME,&STRU[i+1].NOME,15) && !FLAG_BUONO ) break; 
	      }

	      if ( !memcmp(&STRU[i].FLAG,"D",1) && memcmp(&APPO[inizioi],&STRU[i].VALORE,lunghezzai) )
	      {
                   FLAG_BUONO = 1; 
              }

	      if ( !memcmp(&STRU[i].FLAG,">",1) && (memcmp(&APPO[inizioi],&STRU[i].VALORE,lunghezzai) <= 0) )
	      {
                   if ( memcmp(&STRU[i].NOME,&STRU[i+1].NOME,15) && !FLAG_BUONO ) break;
	      }

	      if ( !memcmp(&STRU[i].FLAG,">",1) && (memcmp(&APPO[inizioi],&STRU[i].VALORE,lunghezzai) > 0) )
	      {
                   FLAG_BUONO = 1; 
	      }

	      if ( !memcmp(&STRU[i].FLAG,"<",1) && (memcmp(&APPO[inizioi],&STRU[i].VALORE,lunghezzai) >= 0) )
	      {
                   if ( memcmp(&STRU[i].NOME,&STRU[i+1].NOME,15) && !FLAG_BUONO ) break;
	      }

	      if ( !memcmp(&STRU[i].FLAG,"<",1) && (memcmp(&APPO[inizioi],&STRU[i].VALORE,lunghezzai) < 0) )
	      {
                   FLAG_BUONO = 1; 
              }
           }
       }
/*************************************************************************************************/
       if ( Tot_Appo_FUN > 0 )
       {
         int pos_FUN;
         int FUN_OK = 0;
         int fu;
         char *ptr;
         char stringa_fun[200];
         char stringa_fun2[200];
         char DAL_A[4];
         char SEGNO_FUN = 'N';
         DAL_A[3] = 0;
         char L_A[4];
         L_A[3] = 0;
         int DAL_N; 
         int L_N; 
         int almeno = 0; 
         int valore_fun = 0;
         pos_FUN = TABELLA_FUN[1];
         memcpy(prec_nome,&STRU[pos_FUN].NOME,15);
         for (x=0;x<Tot_Appo_FUN;x++)
         {
           pos_FUN = TABELLA_FUN[x]; 
           valore_fun = 0;
           for (fu=0;fu<40;fu++)
           {
/*
             printf("\n &STRU[pos_FUN].VALORE[fu] -->%.*s<-- \n",1,&STRU[pos_FUN].VALORE[fu]);
*/
             if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"+",1) )
             {
               SEGNO_FUN = '+';
             }
             if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"-",1) )
             {
               SEGNO_FUN = '-';
             }
             if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"*",1) )
             {
               SEGNO_FUN = '*';
             }
             if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"/",1) )
             {
               SEGNO_FUN = '/';
             }
             if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"L",1) )
             {
               fu+=2;
               memcpy(DAL_A,&STRU[pos_FUN].VALORE[fu],3);
               fu+=4;
               memcpy(L_A,&STRU[pos_FUN].VALORE[fu],3);
               fu+=3;
               DAL_N = atoi(DAL_A);
               L_N   = atoi(L_A);
               memcpy(stringa_fun,&APPO[DAL_N],L_N);
               ptr = strchr(stringa_fun,' ');
               if ( ptr == NULL )  
               {
                 stringa_fun[L_N] = 0;
               }
               else
               {
                 ptr = 0;
               }
               strcpy(stringa_fun2,stringa_fun);
               if ( SEGNO_FUN == '+' )
               { 
                 valore_fun += strlen(stringa_fun2);
               }
               else
               {
                 if ( SEGNO_FUN == '-' )
                 { 
                   valore_fun -= strlen(stringa_fun2);
                 }
                 else
                 {
                   if ( SEGNO_FUN == '*' )
                   { 
                     valore_fun = valore_fun * strlen(stringa_fun2);
                   }
                   else
                   {
                     if ( SEGNO_FUN == '/' )
                     { 
                       valore_fun = valore_fun / strlen(stringa_fun2);
                     }
                     else
                     {
                       valore_fun = strlen(stringa_fun2);
                     }
                   }
                 }
               }
               SEGNO_FUN = 'N';
/*
               printf("\n DAL_N %d \n",DAL_N);
               printf("\n L_N   %d \n",L_N);
               printf("\n valore_fun   %d \n",valore_fun);
*/
/*
               printf("\n *LARGO********************************* \n");
               printf("\n stringa_fun2 >%s< \n",stringa_fun2);
               printf("\n strlen(stringa_fun2) > %d \n",strlen(stringa_fun2));
               printf("\n segno       >%c< \n",SEGNO_FUN);
               printf("\n DAL_A >%s< \n",DAL_A);
               printf("\n L_A   >%s< \n",L_A);
               printf("\n DAL_N %d \n",DAL_N);
               printf("\n L_N   %d \n",L_N);
               printf("\n valore_fun   %d \n",valore_fun);
               printf("\n *************************************** \n");
*/
             }
             if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"V",1) )
             {
               fu+=2;
               memcpy(DAL_A,&STRU[pos_FUN].VALORE[fu],3);
               fu+=4;
               memcpy(L_A,&STRU[pos_FUN].VALORE[fu],3);
               fu+=3;
               DAL_N = atoi(DAL_A);
               L_N   = atoi(L_A);
               memcpy(stringa_fun,&APPO[DAL_N],L_N);
               stringa_fun[L_N] = 0;
               if ( SEGNO_FUN == '+' )
               { 
                 valore_fun += atoi(stringa_fun);
               }
               else
               {
                 if ( SEGNO_FUN == '-' )
                 { 
                   valore_fun -= atoi(stringa_fun);
                 }
                 else
                 {
                   if ( SEGNO_FUN == '*' )
                   { 
                     valore_fun = valore_fun * atoi(stringa_fun);
                   }
                   else
                   {
                     if ( SEGNO_FUN == '/' )
                     { 
                       valore_fun = valore_fun / atoi(stringa_fun);
                     }
                     else
                     {
                       valore_fun = atoi(stringa_fun);
                     }
                   }
                 }
               }
/*
               printf("\n *VALOR********************************* \n");
               printf("\n stringa_fun >%s< \n",stringa_fun);
               printf("\n atoi(stringa_fun) > %d \n",atoi(stringa_fun));
               printf("\n segno       >%c< \n",SEGNO_FUN);
               printf("\n DAL_A >%s< \n",DAL_A);
               printf("\n L_A   >%s< \n",L_A);
               printf("\n DAL_N %d \n",DAL_N);
               printf("\n L_N   %d \n",L_N);
               printf("\n valore_fun   %d \n",valore_fun);
               printf("\n *************************************** \n");
*/
             }
             if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"{",1) ) 
             {
               fu+=1;
               int t;
               for (t=0;t<40;t++)
               {
                 if ( !memcmp(&STRU[pos_FUN].VALORE[fu+t],"}",1) ) break;
                 memcpy(&stringa_fun[t],&STRU[pos_FUN].VALORE[fu+t],1);
               }
               stringa_fun[t] = 0;
               fu+=t;
               if ( SEGNO_FUN == '+' )
               { 
                 valore_fun += atoi(stringa_fun);
               }
               else
               {
                 if ( SEGNO_FUN == '-' )
                 { 
                   valore_fun -= atoi(stringa_fun);
                 }
                 else
                 {
                   if ( SEGNO_FUN == '*' )
                   { 
                     valore_fun = valore_fun * atoi(stringa_fun);
                   }
                   else
                   {
                     if ( SEGNO_FUN == '/' )
                     { 
                       valore_fun = valore_fun / atoi(stringa_fun);
                     }
                     else
                     {
                       valore_fun = atoi(stringa_fun);
                     }
                   }
                 }
               }
               SEGNO_FUN = 'N';
             }
             if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"U",1) || 
                  !memcmp(&STRU[pos_FUN].VALORE[fu],"D",1) || 
                  !memcmp(&STRU[pos_FUN].VALORE[fu],"<",1) || 
                  !memcmp(&STRU[pos_FUN].VALORE[fu],">",1) )  
             {
               int prec = fu;
               fu+=1;
               if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"{",1) )
               {
                 fu+=1;
                 int t;
                 for (t=0;t<40;t++)
                 {
                   if ( !memcmp(&STRU[pos_FUN].VALORE[fu+t],"}",1) ) break;
                   memcpy(&stringa_fun[t],&STRU[pos_FUN].VALORE[fu+t],1);
                 }
                 stringa_fun[t] = 0;
               }
               else
               {
                 if ( !memcmp(&STRU[pos_FUN].VALORE[fu],"V",1) )
                 {
                   fu+=2;
                   memcpy(DAL_A,&STRU[pos_FUN].VALORE[fu],3);
                   fu+=4;
                   memcpy(L_A,&STRU[pos_FUN].VALORE[fu],3);
                   fu+=3;
                   DAL_N = atoi(DAL_A);
                   L_N   = atoi(L_A);
                   memcpy(stringa_fun,&APPO[DAL_N],L_N);
                   stringa_fun[L_N] = 0;
                 }
               }
/*
               printf("\n U stringa_fun >%s< \n",stringa_fun);
               printf("\n U valore_fun   %d \n",valore_fun);
*/
               if ( !memcmp(&STRU[pos_FUN].VALORE[prec],"U",1) )
               {
                 if ( valore_fun == atoi(stringa_fun) )
                 {
                   FUN_OK = 1;
                 }
                 else
                 {
                   FUN_OK = 0; 
                 }
               }
               if ( !memcmp(&STRU[pos_FUN].VALORE[prec],"<",1) )
               {
                 if ( valore_fun < atoi(stringa_fun) )
                 {
                   FUN_OK = 1;
                 }
                 else
                 {
                   FUN_OK = 0; 
                 }
               }
               if ( !memcmp(&STRU[pos_FUN].VALORE[prec],">",1) )
               {
                 if ( valore_fun > atoi(stringa_fun) )
                 {
                   FUN_OK = 1;
                 }
                 else
                 {
                   FUN_OK = 0; 
                 }
               }
               if ( !memcmp(&STRU[pos_FUN].VALORE[prec],"D",1) )
               {
                 if ( valore_fun != atoi(stringa_fun) )
                 {
                   FUN_OK = 1;
                 }
                 else
                 {
                   FUN_OK = 0; 
                 }
               }
               if ( FUN_OK == 1 ) almeno = 1;
               break;
             }
           }
/*
   printf("\n **********************************\n");
   printf("\n APPO      -->%s<--\n",APPO);
   printf("\n FUN_OK    -->  %d \n",FUN_OK);
   printf("\n prec_nome          -->%.*s<--\n",15,prec_nome);
   printf("\n STRU[pos_FUN].NOME -->%.*s<--\n",15,&STRU[pos_FUN].NOME);
   printf("\n **********************************\n");
*/
           if ( FUN_OK == 0 && memcmp(prec_nome,&STRU[pos_FUN].NOME,15) )
           {
              i -= 1;     
              break;     
           }
           else
           {
              memcpy(prec_nome,&STRU[pos_FUN].NOME,15);
              prec_nome[15] = 0;
           }
         }
         if ( FUN_OK == 0 && almeno == 0 ) i -= 1; 
       }
       memset(prec_nome,'0',15);
/*************************************************************************************************/
       if ( i == IndS )
       { 
         inizio_inc = 0;
         if ( Tot_Appo_Inc > 0 )
         {
           for (x=0;x<Tot_Appo_Inc;x++) 
           { 
             memcpy(&APPOi,&STRU[TABELLA_Inc[x]].INIZIO,6);
             memcpy(&APPOl,&STRU[TABELLA_Inc[x]].LUNGHEZZA,6);
             APPOi[6] = 0;
             APPOl[6] = 0;
             inizioi = atoi(APPOi);
             lunghezzai = atoi(APPOl);
             indice_inc = TABELLA_Inc[x];

             if ( !memcmp(&STRU[indice_inc].VALORE,"Z",1) )
             {
               for (u=0;u<lunghezzai;u++)
               {
                 if ( memcmp(&APPO[inizioi+u],"0",1) ) break;
               }
               inizioi = inizioi + u;
               memcpy(&APPO_NUM,&STRU[indice_inc].VALORE[1],2);
               APPO_NUM[2] = 0;
               lunghezzai = lunghezzai - u;
               if ( atoi(APPO_NUM) )
               {
                   lunghezzai =  atoi(APPO_NUM);
               }
             }
             else
             {
               memcpy(&APPO_NUM,&STRU[indice_inc].VALORE,2);
               APPO_NUM[2] = 0;
               if ( atoi(APPO_NUM) )
               {
                 if ( atoi(APPO_NUM) < lunghezzai ) lunghezzai =  atoi(APPO_NUM);
               }
             }
             memcpy(&APPO_INC[inizio_inc],&APPO[inizioi],lunghezzai);
             inizio_inc += lunghezzai;
             memcpy(&APPO_INC[inizio_inc]," ",1);
             inizio_inc += 1;
           }

           for (ind_cont=0;ind_cont < tot_elem_cont;ind_cont++)
           {
  	     if ( !memcmp(&CONT[ind_cont].VALORE,&APPO_INC,inizio_inc) &&
                  !memcmp(&CONT[ind_cont].CAMPO,"INCOLLATO",9) )
	     {
	        CONT[ind_cont].CONTATORE++;
                break;
	     }
           }
           if ( ind_cont == tot_elem_cont && tot_elem_cont < 20000 )
           {
             tot_elem_cont += 1;
    	     CONT[ind_cont].CONTATORE = 1;
	     memcpy(&CONT[ind_cont].CAMPO,"INCOLLATO",9);
	     memcpy(&CONT[ind_cont].VALORE,&APPO_INC,inizio_inc);
           }
           if ( Tot_Appo_TOT > 0 )
           {
               for (x=0;x<Tot_Appo_TOT;x++) 
               { 
                  Appo_Cont = TABELLA_TOT[x];
                  memcpy(&APPOi,&STRU[Appo_Cont].INIZIO,6);
                  memcpy(&APPOl,&STRU[Appo_Cont].LUNGHEZZA,6);
                  APPOi[6] = 0;
                  APPOl[6] = 0;
                  int inizioi_cont = atoi(APPOi);
                  int lunghezzai_cont = atoi(APPOl);
                  char stringa_appoggio[200];
                  memcpy(stringa_appoggio,&APPO[inizioi_cont],lunghezzai_cont);
                  stringa_appoggio[lunghezzai_cont] = 0;
                  for(ll=0;ll<totale_contate;ll++)
                  {
                    if ( !memcmp(&CONT[ind_cont].VALORE,&TOT[ll].VALORE,inizio_inc) && !memcmp("INCOLLATO",&TOT[ll].CAMPO,9) && !memcmp(&TOT[ll].NOME_CAMPO,&STRU[Appo_Cont].NOME,15) )
                    {
                      TOT[ll].TOTALE += atoi(stringa_appoggio);
                      break;
                    }
                  }
                  if ( ll == totale_contate )
                  {
                    memcpy(&TOT[ll].VALORE,&CONT[ind_cont].VALORE,inizio_inc);
                    memcpy(&TOT[ll].CAMPO,"INCOLLATO      ",15);
                    memcpy(&TOT[ll].NOME_CAMPO,&STRU[Appo_Cont].NOME,15);
                    TOT[ll].TOTALE = atoi(stringa_appoggio);
                    totale_contate++;
                  }
                }
            }
         }
     
         for (x=0;x<Tot_Appo_Cont;x++) 
         { 
            Appo_Cont = TABELLA_Cont[x];
            memcpy(&APPOi,&STRU[Appo_Cont].INIZIO,6);
            memcpy(&APPOl,&STRU[Appo_Cont].LUNGHEZZA,6);
            APPOi[6] = 0;
            APPOl[6] = 0;
            inizioi = atoi(APPOi);
            lunghezzai = atoi(APPOl);

            if ( !memcmp(&STRU[Appo_Cont].VALORE,"Z",1) )
            {
               for (u=0;u<lunghezzai;u++)
               {
                 if ( memcmp(&APPO[inizioi+u],"0",1) ) break;
               }
               inizioi = inizioi + u;
               memcpy(&APPO_NUM,&STRU[Appo_Cont].VALORE[1],2);
               APPO_NUM[2] = 0;
               lunghezzai = lunghezzai - u;
               if ( atoi(APPO_NUM) )
               {
                   lunghezzai =  atoi(APPO_NUM);
               }
            }
            else
            {
               memcpy(&APPO_NUM,&STRU[Appo_Cont].VALORE,2);
               APPO_NUM[2] = 0;
               if ( atoi(APPO_NUM) )
               {
                 if ( atoi(APPO_NUM) < lunghezzai ) lunghezzai =  atoi(APPO_NUM);
               }
            }
    
            for (ind_cont=0;ind_cont < tot_elem_cont;ind_cont++)
            {
/*
             printf("\n CAMPO -->%.*s<-- \n",15,CONT[ind_cont].CAMPO);
             printf("\n NOME  -->%.*s<-- \n",15,STRU[Appo_Cont].NOME);
             printf("\n VALORE-->%.*s<-- \n",lunghezzai,CONT[ind_cont].VALORE);
	     printf("\n APPO[inizioi] -->%.*s<-- \n",lunghezzai,APPO[inizioi]);
             printf("\n tot cont   %d \n",tot_elem_cont); 
*/
  	         if (!memcmp(&CONT[ind_cont].CAMPO,&STRU[Appo_Cont].NOME,15) && !memcmp(&CONT[ind_cont].VALORE,&APPO[inizioi],lunghezzai))
	         {
	            CONT[ind_cont].CONTATORE++;
                    break;
	         }
            }
            if ( ind_cont == tot_elem_cont && tot_elem_cont < 20000 )
            {
  	       tot_elem_cont += 1;
	       CONT[ind_cont].CONTATORE = 1;
	       memcpy(&CONT[ind_cont].CAMPO,&STRU[Appo_Cont].NOME,15);
	       memcpy(&CONT[ind_cont].VALORE,&APPO[inizioi],lunghezzai);
            }
            if ( Tot_Appo_TOT > 0 )
            {
               for (x=0;x<Tot_Appo_TOT;x++) 
               { 
                  Appo_Cont = TABELLA_TOT[x];
                  memcpy(&APPOi,&STRU[Appo_Cont].INIZIO,6);
                  memcpy(&APPOl,&STRU[Appo_Cont].LUNGHEZZA,6);
                  APPOi[6] = 0;
                  APPOl[6] = 0;
                  int inizioi_cont = atoi(APPOi);
                  int lunghezzai_cont = atoi(APPOl);
                  char stringa_appoggio[200];
                  memcpy(stringa_appoggio,&APPO[inizioi_cont],lunghezzai_cont);
                  stringa_appoggio[lunghezzai_cont] = 0;
                  for(ll=0;ll<totale_contate;ll++)
                  {
                    if ( !memcmp(&CONT[ind_cont].VALORE,&TOT[ll].VALORE,lunghezzai) && !memcmp(&CONT[ind_cont].CAMPO,&TOT[ll].CAMPO,15) && !memcmp(&TOT[ll].NOME_CAMPO,&STRU[Appo_Cont].NOME,15) )
                    {
                      TOT[ll].TOTALE += atoi(stringa_appoggio);
                      break;
                    }
                  }
                  if ( ll == totale_contate )
                  {
                    memcpy(&TOT[ll].VALORE,&CONT[ind_cont].VALORE,lunghezzai);
                    memcpy(&TOT[ll].CAMPO,&CONT[ind_cont].CAMPO,15);
                    memcpy(&TOT[ll].NOME_CAMPO,&STRU[Appo_Cont].NOME,15);
                    TOT[ll].TOTALE = atoi(stringa_appoggio);
                    totale_contate++;
                  }
                }
            }
         }
         if ( Tot_Grande > 0 )
         {
            for (x=0;x<Tot_Grande;x++) 
            { 
               Appo_Cont = TABELLA_Grande[x];
               memcpy(&APPOi,&STRU[Appo_Cont].INIZIO,6);
               memcpy(&APPOl,&STRU[Appo_Cont].LUNGHEZZA,6);
               APPOi[6] = 0;
               APPOl[6] = 0;
               inizioi = atoi(APPOi);
               lunghezzai = atoi(APPOl);
               if ( memcmp(&Grande[Appo_Cont].VALORE,&APPO[inizioi],lunghezzai) < 0 ||
                    !memcmp(&Grande[Appo_Cont].VALORE,"XXXXXXXXXX",10) )
               {
                  memcpy(&Grande[Appo_Cont].VALORE,&APPO[inizioi],lunghezzai);
               }
            }
         }
         if ( Tot_Piccolo > 0 )
         {
            for (x=0;x<Tot_Piccolo;x++) 
            { 
               Appo_Cont = TABELLA_Piccolo[x];
               memcpy(&APPOi,&STRU[Appo_Cont].INIZIO,6);
               memcpy(&APPOl,&STRU[Appo_Cont].LUNGHEZZA,6);
               APPOi[6] = 0;
               APPOl[6] = 0;
               inizioi = atoi(APPOi);
               lunghezzai = atoi(APPOl);
               if ( memcmp(&Piccolo[Appo_Cont].VALORE,&APPO[inizioi],lunghezzai) > 0 ||
                    !memcmp(&Piccolo[Appo_Cont].VALORE,"XXXXXXXXXX",10) )
               {
                  memcpy(&Piccolo[Appo_Cont].VALORE,&APPO[inizioi],lunghezzai);
               }
            }
         }
         TOTALE_RECORD += 1;
         printf("%s",APPO);
       }
        memset(APPO,'\0',1000);
   }
 }
 fc = fopen("LOG_COUNTER","w");
 if(fc == 0)
 {
    printf("\n %s \n",strerror(errno));
    printf("Error in opening file Log_Contatore\n");
    return;
 }
 if ( tot_elem_cont > 0 )
 {
   fprintf(fc,"FIELD NAME       VALUE                 TOTAL\n");
   fprintf(fc,"--------------------------------------------\n");
   for (ind_cont=0;ind_cont < tot_elem_cont;ind_cont++)
   {
     fprintf(fc,"%.*s  >%.*s<               %lu \n",15,CONT[ind_cont].CAMPO,70,CONT[ind_cont].VALORE,CONT[ind_cont].CONTATORE);
   }
   if ( tot_elem_cont == 20000 ) fprintf(fc,"MORE THAN 20000 ELEMENTS KEYS - STOP ELABORATION\n "); 
   fprintf(fc,"-----------------------------------------------\n");
   fprintf(fc,"TOTAL RECORD  --> %d\n",TOTALE_RECORD);                                  
   fprintf(fc,"-----------------------------------------------\n");
 }
 if ( Tot_Appo_TOT > 0 )
 {
   int tot_campi_contati = 0;
   for (x=0;x<totale_contate;x++) 
   { 
      fprintf(fc,"CAMPO %.*s  VALORE -->%.*s<--  SOMMA CAMPO %.*s --> TOTALE %d \n",15,TOT[x].CAMPO,70,TOT[x].VALORE,15,TOT[x].NOME_CAMPO,TOT[x].TOTALE); 

      for (y=0;y<tot_campi_contati;y++)
      {
        if ( !memcmp(&TOT2[y].CAMPO,&TOT[x].NOME_CAMPO,15) )
        { 
           TOT2[y].TOTALE += TOT[x].TOTALE;
           break;
        }
      }
      if ( y == tot_campi_contati )
      {
        memcpy(&TOT2[y].CAMPO,&TOT[x].NOME_CAMPO,15);
        TOT2[y].TOTALE = TOT[x].TOTALE;
        tot_campi_contati++;
      }
   }
   fprintf(fc,"--------------------------------------------------------------------------------\n");
   for (x=0;x<tot_campi_contati;x++)
   {
      fprintf(fc," CAMPOS %.*s TOTAL = %d \n",15,TOT2[x].CAMPO,TOT2[x].TOTALE);
   }
   fprintf(fc,"--------------------------------------------------------------------------------\n");
 }
 if ( Tot_Piccolo > 0 )
 {
   fprintf(fc,"VALORES MAS CHICOS \n\n"); 
   for (x=0;x<Tot_Piccolo;x++) 
   { 
      Appo_Cont = TABELLA_Piccolo[x];
      memcpy(&APPOi,&STRU[Appo_Cont].INIZIO,6);
      memcpy(&APPOl,&STRU[Appo_Cont].LUNGHEZZA,6);
      APPOi[6] = 0;
      APPOl[6] = 0;
      inizioi = atoi(APPOi);
      lunghezzai = atoi(APPOl);
      fprintf(fc," %.*s -->%.*s<-- \n",15,STRU[Appo_Cont].NOME,lunghezzai,Piccolo[Appo_Cont].VALORE); 
   }
   fprintf(fc,"------------------------------------------------\n");
 }
 if ( Tot_Grande > 0 )
 {
   fprintf(fc,"VALORES MAS GRANDES \n\n"); 
   for (x=0;x<Tot_Grande;x++) 
   { 
      Appo_Cont = TABELLA_Grande[x];
      memcpy(&APPOi,&STRU[Appo_Cont].INIZIO,6);
      memcpy(&APPOl,&STRU[Appo_Cont].LUNGHEZZA,6);
      APPOi[6] = 0;
      APPOl[6] = 0;
      inizioi = atoi(APPOi);
      lunghezzai = atoi(APPOl);
      fprintf(fc," %.*s -->%.*s<-- \n",15,STRU[Appo_Cont].NOME,lunghezzai,Grande[Appo_Cont].VALORE); 
   }
   fprintf(fc,"------------------------------------------------\n");
 }
 fclose(fc);
}


void Confr(int argv,char **argc)
{
 
 char APPOS[200];
 FILE *fs;
 FILE *f1;
 FILE *f2;
 FILE *fd;
 FILE *fp1;
 FILE *fp2;

 struct struttura 
 { 
		char NOME[15];
		char INIZIO[6];
		char LUNGHEZZA[6];
		char FLAG;
		char FLAG_TIPO;
		char INIZIO2[6];
		char LUNGHEZZA2[6];
                char VALORE[50];
                char STOP;
 } STRU[2000];

 int TABELLA_Key[4000];
 int Tot_Key = 0;
 int i       = 0;
 int z;
 int t=0;
 int ind     = 0;
 int IndS    = 0;
 char APPO_f1[1000];
 char APPO_f2[1000];
 char APPOl[7];
 char APPOi[7];
 char STRINGA_UNO[500];
 char STRINGA_DUE[500];
 int inizioi;
 int lunghezzai;
 int lunghezza;
 int inizioi2;
 int lunghezzai2;
 int TROVATO;
 int PRIMA_VES;
 int Tot_f1 = 0;
 int Tot_f2 = 0;
 int Rec_f2[1000000];

/************************************************************************************************************/

 for (i=0;i<1000000;i++) 
 {
   Rec_f2[i] = 0; 
 }
 if ( !memcmp(argc[2],"help",4) || argv == 2 )
 {
     printf("\n The program COMPARE ( Compare Two ascii files ) : this modality has the following parameters : \n"); 
     printf("\n   - Structure File "); 
     printf("\n   - File 1 "); 
     printf("\n   - File 2 "); 
     printf("\n   In Output generate these files : "); 
     printf("\n   - File of Difference (same record but differents fields)"); 
     printf("\n   - File MORE_FILE1 (RECORD presents on file1 but not on file2)\n "); 
     printf("\n   - File MORE_FILE2 (RECORD presents on file2 but not on file1)\n "); 
     printf("\n   Structure File has this format : "); 
     printf("\n     - FIELD NAME = 15 byte"); 
     printf("\n     - from byte  = 6 byte start field on file1"); 
     printf("\n     - length     = 6 byte length field on file1"); 
     printf("\n     - FLAG       = 1 byte"); 
     printf("\n     - FLAG_TYPE  = 1 byte Type Field Numeric or Alphanumeric"); 
     printf("\n     - from byte  = 6 byte start field on file2"); 
     printf("\n     - length     = 6 byte length field on file2"); 
     printf("\n es. --->PULSOS         000100000005CN000100000005<---\n");
     printf("\n FLAG VALUES PERMITTED :");
     printf("\nK              --->  KEY ");
     printf("\nC              --->  COMPARE");
     printf("\nP              --->  COMPARE removing spaces");
     printf("\nX              --->  DOES NOT MAKE ANY COMPARISON");                                  
     printf("\n Example of process launch : GPConv Confr STRUCTURE_FILE FILE1 FILE2\n");                                  
     return;
 }
 
 fs  = fopen(argc[2],"r");
 if(fs == 0)
 {
  printf("\n %s \n",strerror(errno));
  printf("Error in opening structure file %s\n",argc[2]);
  return;
 }

 f1  = fopen(argc[3],"r");
 if(f1 == 0)
 {
  printf("\n %s \n",strerror(errno));
  printf("Error in opening file 1 : %s\n",argc[3]);
  return;
 }

 fd  = fopen("./DIFFERENCES","w");
 if(fd == 0)
 {
  printf("\n %s \n",strerror(errno));
  printf("Error in opening file DIFFERENZE \n");
  return;
 }

 fp1  = fopen("./MORE_FILE1","w");
 if(fp1 == 0)
 {
  printf("\n %s \n",strerror(errno));
  printf("Error in opening file PIU_FILE1 \n");
  return;
 }

 fp2  = fopen("./MORE_FILE2","w");
 if(fp2 == 0)
 {
  printf("\n %s \n",strerror(errno));
  printf("Error in opening file PIU_FILE2 \n");
  return;
 }

 fgets(APPOS,200,fs);
 while ( feof(fs) != 16 ) 
 {
   memcpy(&STRU[IndS],&APPOS,92);  
   if ( !memcmp(&STRU[IndS].FLAG,"K",1) )
   {
      TABELLA_Key[Tot_Key] = IndS;   
      Tot_Key += 1;
   }
   if ( memcmp(&STRU[IndS].FLAG,"X",1) ) 
   { 
     IndS += 1;
   }
   fgets(APPOS,200,fs);
 }
 fclose(fs);

/*
  for (i=0;i<IndS;i++)
  {
    printf("\n NOME       -->%.*s<-- ",15,STRU[i].NOME);
    printf("\n INIZIO     -->%.*s<-- ",6,STRU[i].INIZIO);
    printf("\n LUNGHEZZA  -->%.*s<-- ",6,STRU[i].LUNGHEZZA);
    printf("\n FLAG       -->%.*s<-- ",1,STRU[i].FLAG);
    printf("\n FLAG_TIPO  -->%.*s<-- ",1,STRU[i].FLAG_TIPO);
    printf("\n INIZIO2    -->%.*s<-- ",6,STRU[i].INIZIO2);
    printf("\n LUNGHEZZA2 -->%.*s<-- ",6,STRU[i].LUNGHEZZA2);
  }
  for (i=0;i<Tot_Key;i++)
  {
    printf("\n KEY      -->%d<-- ",TABELLA_Key[i]);
  }
*/

 memset(APPO_f1,'\0',1000);
 fgets(APPO_f1,1000,f1);
 while ( feof(f1) != 16 )
 {
   Tot_f1 += 1;
   TROVATO = 0;
   f2  = fopen(argc[4],"r");
   if(f2 == 0)
   {
    printf("\n %s \n",strerror(errno));
    printf("Error in opening file 2 : %s\n",argc[4]);
    return;
   }
   Tot_f2 = 0;
   fgets(APPO_f2,600,f2);
   while ( feof(f2) != 16 )
   {
     Tot_f2 += 1;
     if ( Rec_f2[Tot_f2] == 0 )
     { 
       for ( i=0;i<Tot_Key;i++)
       { 
         ind = TABELLA_Key[i];
         memcpy(&APPOi,&STRU[ind].INIZIO,6);
         memcpy(&APPOl,&STRU[ind].LUNGHEZZA,6);
         APPOi[6] = 0;
         APPOl[6] = 0;
         inizioi = atoi(APPOi); 
         lunghezzai = atoi(APPOl); 
         memcpy(&APPOi,&STRU[ind].INIZIO2,6);
         memcpy(&APPOl,&STRU[ind].LUNGHEZZA2,6);
         APPOi[6] = 0;
         APPOl[6] = 0;
         inizioi2 = atoi(APPOi); 
         lunghezzai2 = atoi(APPOl); 

         if ( lunghezzai > lunghezzai2 )
         {
           lunghezza = lunghezzai2;
         }
         else
         {
           lunghezza = lunghezzai;
         }
         if ( lunghezza > strlen(APPO_f1) )
         {
           lunghezza = strlen(APPO_f1) - 1;
         }
         if ( lunghezza > strlen(APPO_f2) )
         {
           lunghezza = strlen(APPO_f2) - 1;
         }

if ( !memcmp(argc[5],"key",3) )
{
       printf("\n ************************************************************* \n");
       printf("\n Field Name -->%.*s<-- \n",15,(char *)&STRU[ind].NOME);
       printf("\n Tot_f1  -->%d<-- \n",Tot_f1);
       printf("\n APPO_f1 -->%s<-- \n",APPO_f1);
       printf("\n APPO_f1[inizioi] -->%.*s<-- \n",lunghezzai,&APPO_f1[inizioi]);
       printf("\n APPO_f2[inizioi2] -->%.*s<-- \n",lunghezzai2,&APPO_f2[inizioi2]);
       printf("\n ************************************************************* \n");
}

         if ( !memcmp(&STRU[ind].FLAG_TIPO,"N",1) )
         {
           memcpy(STRINGA_UNO,&APPO_f1[inizioi],lunghezzai);
           STRINGA_UNO[lunghezzai] = '\0';
           memcpy(STRINGA_DUE,&APPO_f2[inizioi2],lunghezzai2);
           STRINGA_DUE[lunghezzai2] = '\0';

           if ( atol(STRINGA_DUE) != atol(STRINGA_UNO) ) break; 
         }
         else
         {
           if ( !memcmp(&STRU[ind].FLAG_TIPO,"A",1) )
           {
             if ( memcmp(&APPO_f1[inizioi],&APPO_f2[inizioi2],lunghezza) ) break;
if ( !memcmp(argc[5],"test",4) )
{
       printf("\n DONE ***************************************************************************\n");
}
           }
           if ( !memcmp(&STRU[ind].FLAG_TIPO,"<",1) )
           {
if ( !memcmp(argc[5],"test",4) )
{
       printf("\n *********************************************************************************\n");
       printf("\n Function Search Key < \n");
       printf("\n lunghezzai2   ---->%d<----\n",lunghezzai2);
       printf("\n lunghezzai    ---->%d<----\n",lunghezzai );
       printf("\n *********************************************************************************\n");
}
             if ( lunghezzai2 > lunghezzai ) break;
             for(z=0;z<lunghezzai;z++)
             {
               if ( (inizioi + z + lunghezzai2) > inizioi + lunghezzai )
               {
                 z = lunghezzai;
                 break; 
               }
               else
               {
if ( !memcmp(argc[5],"test",4) )
{
       printf("\n *********************************************************************************\n");
       printf("\n Function Search Key < \n");
       printf("\n APPO_f1[inizioi+z]   ---->%.*s<----\n",lunghezzai2,&APPO_f1[inizioi+z]);
       printf("\n APPO_f2[inizioi2]    ---->%.*s<----\n",lunghezzai,&APPO_f2[inizioi2]);
       printf("\n *********************************************************************************\n");
}
                 if ( !memcmp(&APPO_f1[inizioi+z],&APPO_f2[inizioi2],lunghezzai2) ) break;
               }
             }
             if ( z == lunghezzai ) break; 
           }
           if ( !memcmp(&STRU[ind].FLAG_TIPO,"P",1) )
           {
             t=0;
             for (z=0;z<lunghezzai;z++)
             { 
               if ( memcmp(&APPO_f1[inizioi+z]," ",1) )
               { 
                 memcpy(&STRINGA_UNO[t],&APPO_f1[inizioi+z],1); 
                 t++;
               }
             }
             lunghezzai = t;
             t=0;
             for (z=0;z<lunghezzai2;z++)
             { 
               if ( memcmp(&APPO_f2[inizioi2+z]," ",1) )
               { 
                 memcpy(&STRINGA_DUE[t],&APPO_f2[inizioi2+z],1); 
                 t++;
               }
             }
             lunghezzai2 = t;

             if ( lunghezzai > lunghezzai2 )
             {
               lunghezza = lunghezzai2;
             }
             else
             {
               lunghezza = lunghezzai;
             }
             if ( lunghezza > strlen(APPO_f1) )
             {
               lunghezza = strlen(APPO_f1) - 1;
             }
             if ( lunghezza > strlen(APPO_f2) )
             {
               lunghezza = strlen(APPO_f2) - 1;
             }

if ( !memcmp(argc[5],"test",4) )
{
       printf("\n *********************************************************************************\n");
       printf("\n Function Search Key < \n");
       printf("\n STRINGA_UNO     ---->%.*s<----\n",lunghezza,&STRINGA_UNO[0]);
       printf("\n STRINGA_DUE     ---->%.*s<----\n",lunghezza,&STRINGA_DUE[0]);
       printf("\n *********************************************************************************\n");
}

             if ( memcmp(&STRINGA_UNO[0],&STRINGA_DUE[0],lunghezza) ) break;

if ( !memcmp(argc[5],"test",4) )
{
       printf("\n FATTO ***************************************************************************\n");
}

           }
         }
       }
       if ( i == Tot_Key )
       {
         TROVATO = 1;
         PRIMA_VES = 0;
         Rec_f2[Tot_f2] = 1;
         for (i=0;i<IndS;i++)
         {
            memcpy(&APPOi,&STRU[i].INIZIO,6);
            memcpy(&APPOl,&STRU[i].LUNGHEZZA,6);
            APPOi[6] = 0;
            APPOl[6] = 0;
            inizioi = atoi(APPOi); 
            lunghezzai = atoi(APPOl); 
            memcpy(&APPOi,&STRU[i].INIZIO2,6);
            memcpy(&APPOl,&STRU[i].LUNGHEZZA2,6);
            APPOi[6] = 0;
            APPOl[6] = 0;
            inizioi2 = atoi(APPOi); 
            lunghezzai2 = atoi(APPOl); 
            if ( lunghezzai > lunghezzai2 )
            {
              lunghezza = lunghezzai2;
            }
            else
            {
              lunghezza = lunghezzai;
            }

            if ( !memcmp(&STRU[i].FLAG_TIPO,"N",1) )
            {
              memcpy(STRINGA_UNO,&APPO_f1[inizioi],lunghezzai);
              STRINGA_UNO[lunghezzai] = '\0';
              memcpy(STRINGA_DUE,&APPO_f2[inizioi2],lunghezzai2);
              STRINGA_DUE[lunghezzai2] = '\0';
              if ( atol(STRINGA_DUE) != atol(STRINGA_UNO) ) 
              {
                if ( PRIMA_VES == 0 )
                {
                  fprintf(fd,"*************************************************************************\n");
                  fprintf(fd,"REC f1 n. %d -->%.*s<--\n",Tot_f1,(int)strlen(APPO_f1),APPO_f1);
                  fprintf(fd,"REC f2 n. %d -->%.*s<--\n",Tot_f2,(int)strlen(APPO_f2),APPO_f2);
                  PRIMA_VES = 1;
                }
                fprintf(fd,"-------------------------------------------------------------------------\n");
                fprintf(fd,"Field >%.*s< \n",15,STRU[i].NOME);
                fprintf(fd,"      Val1 -->%.*s<-- \n",lunghezzai,&APPO_f1[inizioi]);
                fprintf(fd,"      Val2 -->%.*s<-- \n",lunghezzai2,&APPO_f2[inizioi2]);
                fprintf(fd,"-------------------------------------------------------------------------\n");
              }
            }
            else
            {
              if ( !memcmp(&STRU[i].FLAG_TIPO,"V",1) )
              {
                if ( memcmp(&APPO_f1[inizioi],&STRU[i].VALORE,lunghezza) )
                {
                  if ( PRIMA_VES == 0 )
                  {
                    fprintf(fd,"*************************************************************************\n");
                    fprintf(fd,"REC f1 n. %d -->%.*s<--\n",Tot_f1,(int)strlen(APPO_f1),APPO_f1);
                    fprintf(fd,"REC f2 n. %d -->%.*s<--\n",Tot_f2,(int)strlen(APPO_f2),APPO_f2);
                    PRIMA_VES = 1;
                  }
                  fprintf(fd,"-------------------------------------------------------------------------\n");
                  fprintf(fd,"Field >%.*s< \n",15,STRU[i].NOME);
                  fprintf(fd,"      Val1 -->%.*s<-- \n",lunghezzai,&APPO_f1[inizioi]);
                  fprintf(fd,"      Val2 -->%.*s<-- \n",lunghezzai2,&APPO_f2[inizioi2]);
                  fprintf(fd,"    Value -->%.*s<-- \n",lunghezza,(char *)&STRU[i].VALORE);
                  fprintf(fd,"-------------------------------------------------------------------------\n");
                }
              }
              if ( !memcmp(&STRU[i].FLAG_TIPO,"A",1) )
              {
                if ( memcmp(&APPO_f1[inizioi],&APPO_f2[inizioi2],lunghezza) )
                {
                  if ( PRIMA_VES == 0 )
                  {
                    fprintf(fd,"*************************************************************************\n");
                    fprintf(fd,"REC f1 n. %d -->%.*s<--\n",Tot_f1,(int)strlen(APPO_f1),APPO_f1);
                    fprintf(fd,"REC f2 n. %d -->%.*s<--\n",Tot_f2,(int)strlen(APPO_f2),APPO_f2);
                    PRIMA_VES = 1;
                  }
                  fprintf(fd,"-------------------------------------------------------------------------\n");
                  fprintf(fd,"Field >%.*s< \n",15,STRU[i].NOME);
                  fprintf(fd,"      Val1 -->%.*s<-- \n",lunghezzai,&APPO_f1[inizioi]);
                  fprintf(fd,"      Val2 -->%.*s<-- \n",lunghezzai2,&APPO_f2[inizioi2]);
                  fprintf(fd,"-------------------------------------------------------------------------\n");
                }
              }
              else
              {
                if ( !memcmp(&STRU[i].FLAG_TIPO,"P",1) )
                {
                  t=0;
                  for (z=0;z<lunghezzai;z++)
                  { 
                    if ( memcmp(&APPO_f1[inizioi+z]," ",1) )
                    { 
                      memcpy(&STRINGA_UNO[t],&APPO_f1[inizioi+z],1); 
                      t++;
                    }
                  }
                  lunghezzai = t;
                  t=0;
                  for (z=0;z<lunghezzai2;z++)
                  { 
                    if ( memcmp(&APPO_f2[inizioi2+z]," ",1) )
                    { 
                      memcpy(&STRINGA_DUE[t],&APPO_f2[inizioi2+z],1); 
                      t++;
                    }
                  }
                  lunghezzai2 = t;
                  if ( lunghezzai > lunghezzai2 )
                  {
                    lunghezza = lunghezzai2;
                  }
                  else
                  {
                    lunghezza = lunghezzai;
                  }
                  if ( memcmp(&STRINGA_UNO[0],&STRINGA_DUE[0],lunghezza) )
                  {
                    if ( PRIMA_VES == 0 )
                    {
                      fprintf(fd,"*************************************************************************\n");
                      fprintf(fd,"*REC f1 n. %d -->%.*s<--\n",Tot_f1,(int)strlen(APPO_f1),APPO_f1);
                      fprintf(fd,"*REC f2 n. %d -->%.*s<--\n",Tot_f2,(int)strlen(APPO_f2),APPO_f2);
                      PRIMA_VES = 1;
                    }
                    fprintf(fd,"-------------------------------------------------------------------------\n");
                    fprintf(fd,"Field >%.*s< \n",15,STRU[i].NOME);
                    fprintf(fd,"      Val1 -->%.*s<-- \n",lunghezzai,&APPO_f1[inizioi]);
                    fprintf(fd,"      Val2 -->%.*s<-- \n",lunghezzai2,&APPO_f2[inizioi2]);
                    fprintf(fd,"-------------------------------------------------------------------------\n");
                  }
                }
              }
            }
         }
         if ( i == IndS )
         {
           break;
         }
       }
     }
     fgets(APPO_f2,1000,f2);
   }
   fclose(f2);
   if ( TROVATO == 0 )
   {
     fprintf(fp1,"%d -->%.*s<--\n",Tot_f1,(int)strlen(APPO_f1) - 1,APPO_f1);
   }
   memset(APPO_f1,'\0',1000);
   fgets(APPO_f1,1000,f1);
 }
 fclose(f1);
 fclose(fd);
 fclose(fp1);
 
 f2  = fopen(argc[4],"r");
 if(f2 == 0)
 {
  printf("\n %s \n",strerror(errno));
  printf("Error in opening file 2 : %s\n",argc[4]);
  return;
 }
 Tot_f2 = 0;
 fgets(APPO_f2,1000,f2);
 while ( feof(f2) != 16 )
 {
   Tot_f2 += 1;
   if ( Rec_f2[Tot_f2] == 0 ) fprintf(fp2,"%d -->%.*s<--\n",Tot_f2,(int)strlen(APPO_f2) - 1,APPO_f2);
   fgets(APPO_f2,1000,f2);
 } 
 fclose(fp2);
}
