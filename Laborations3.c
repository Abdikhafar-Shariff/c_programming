#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define MAX_AMNE 1000
#define WORDLENGHT 20

struct radioaktiva
{
    char namn[WORDLENGHT+1];
    char enhet[WORDLENGHT+1];
    int masstal;
    double halveringstid;
};
typedef struct radioaktiva Radioaktiva;

void dataHantering(Radioaktiva radioAktiva[], int *pAntalAmne);
Radioaktiva skapaAmne(char namn[], char enhet[], int masstal, double halveringstid);
int hitta_amne (Radioaktiva radioAktva[], int *pAntalAmne, char AmneNamn[],int Masstala);
void regAmne(Radioaktiva radioAktiva[], int *pAntalAmne);
void skrivUtAmne(Radioaktiva radioAktiva[], int *pantalaAmne);
void lasFranFilen(Radioaktiva radioAktiva[], int *pAntalAmne,char filnamn[]);
void sorteraAmne(Radioaktiva radioaktiva[], int *pAntalAmne);
void sokAmne (Radioaktiva radioAktva[],int *pAntalAmne);
int sokMedNamn(Radioaktiva radioAktiva[], int *pAntalAmne);
int hittaAmne_Masstal(Radioaktiva radioAktiva[], int *pAntalAmne);
int hittaAmne_halveringtid(Radioaktiva radioAktiva[], int *pAntalAmne);
void andraHavleringtid(Radioaktiva radioAktiva[], int *pAntalAmne);
void avregistreraAmne(Radioaktiva radioAktiva[], int *pAntalAmne);
void skrivTillFilen(Radioaktiva radioAktivA[], int *pAntalAmne,char filnamn[]);

int main(void)
{
    Radioaktiva radioaktivaAmne[MAX_AMNE];
    int antalAmne=0;
    char filnamnt[WORDLENGHT+1];
    printf("Skriv in filen namn:");
    gets(filnamnt);

    lasFranFilen(radioaktivaAmne,&antalAmne,filnamnt);
    dataHantering(radioaktivaAmne, &antalAmne);
    skrivTillFilen(radioaktivaAmne,&antalAmne,filnamnt);
    
    return 0;
}

//funktion att hantera hela programmet Meny funktion
void dataHantering(Radioaktiva radioAktiva[], int *pAntalAmne)
{
   int val;
    while (val != 7)
    {
        printf("\n(1) Registrera nya radioaktiva amnen\n");
        printf("(2) Alla amnen\n");
        printf("(3) Sortera amnen\n");
        printf("(4) Soka efter amnen\n");
        printf("(5) Andra halveringstid\n");
        printf("(6) Avregistrera amne\n");
        printf("(7) Avsluta\n");

        printf("\nAnge val: ");
        scanf("%d",&val);

        switch (val)
        {
        case 1:regAmne(radioAktiva ,pAntalAmne);
        break;
        case 2:skrivUtAmne(radioAktiva,pAntalAmne);
        break;
        case 3:sorteraAmne(radioAktiva,pAntalAmne);
        break;
        case 4:sokAmne(radioAktiva,pAntalAmne);
        break;
        case 5:andraHavleringtid(radioAktiva,pAntalAmne);
        break;
        case 6:avregistreraAmne(radioAktiva,pAntalAmne);
        break;
        default:
        break;
        }
    }
}

// funktion att retunera värde i structen
Radioaktiva skapaAmne(char namn[], char enhet[], int masstal, double halveringstid)
{
    Radioaktiva r;
    strcpy(r.namn,namn);
    strcpy(r.enhet,enhet);
    r.masstal = masstal;
    r.halveringstid = halveringstid;
    return r;
}

//funktion att hitta amne namn och masstal och titta om de är lika retunera i annars retunera -1
int hitta_amne (Radioaktiva radioAktva[], int *pAntalAmne, char AmneNamn[], int Masstala)
{
    int i;
    for(i =0; i < (*pAntalAmne); i++)
    {
        if(strcmp(radioAktva[i].namn,AmneNamn) ==0 && radioAktva[i].masstal == Masstala)
        {
        
            return i;
        }
    }
    return -1;
}

//funktion att registrera anme.
void regAmne(Radioaktiva radioAktiva[], int *pAntalAmne)
{
    char AmneNamn[WORDLENGHT+1], enheter[WORDLENGHT+1], sluta[WORDLENGHT+1] ="q";
    int AmneMasstal;
    double halveringstider;

    printf("\nRegistrera nya radioaktiva amnen\n");
    
    while (1)
    {
        if((*pAntalAmne) == MAX_AMNE)
        {
            printf("Registret ar full! kan inte lagga mer amnen\n");
            break;
        }
            printf("Ange namn (q for att avsluta): ");
            scanf("%s%*c",AmneNamn);
         if(strcmp(AmneNamn,sluta)== 0)
        {
            break;
        }
            printf("Ange masstal: ");
            scanf("%d%*c",&AmneMasstal);
         if( hitta_amne(radioAktiva,pAntalAmne, AmneNamn,AmneMasstal) >= 0)
        {
            printf("Amnet ar redan registrerat!\n");
        }
        
        else
        {
            printf("Halveringstid (s,min,h,dagar,ar): ");
            scanf("%le%*c %s%*c",&halveringstider,enheter);
             if(strcmp(enheter,"min")==0)
             {
                halveringstider = halveringstider * 60;
             }
             else if(strcmp(enheter,"h")==0)
             {
                halveringstider = halveringstider * 3600;
             }
             else if(strcmp(enheter,"dagar")==0)
             {
                halveringstider = halveringstider * 86400;
                
             }
             else if(strcmp(enheter,"ar")==0)
             {
                halveringstider = halveringstider* (3.154* pow(10,7));
                 
             }
             else
             {
                 halveringstider =halveringstider;
             }
        radioAktiva[*pAntalAmne] = skapaAmne(AmneNamn,enheter,AmneMasstal,halveringstider);
        (*pAntalAmne)++;   
        }
    }
}

//funktion att skriva ut amnen
void skrivUtAmne(Radioaktiva radioAktiva[], int *pantalaAmne)
{
    int i;
    printf("Namn\t\t\t\tMasstal\t\t\t\tHalveringstid(s)\n");
    printf("-----------------------------------------------------------------------------\n");
    for(i=0; i < (*pantalaAmne); i++)
    {
        printf("%s\t\t\t\t%d\t\t\t\t%.4e \n",radioAktiva[i].namn,radioAktiva[i].masstal,radioAktiva[i].halveringstid);
    }
    printf("\n");
}

//funkution att läsa från filen till array av struct
void lasFranFilen(Radioaktiva radioAktiva[], int *pAntalAmne,char filnamn[])
{
    FILE *fp;
    fp=fopen(filnamn,"rb+");

    if((*pAntalAmne) == MAX_AMNE)
    {
        printf("Registret ar full! kan inte lagga mer amnen\n");
    }
    if(fp!=NULL)
    {
        char namn[WORDLENGHT+1],enhet[WORDLENGHT+1];
        int masstal;
        double halveringtid;

        fscanf(fp,"%d",pAntalAmne);
        for(int i =0; i <(*pAntalAmne); i++)
        {
            fscanf(fp,"%s    %d    %le ",namn,&masstal,&halveringtid);
            radioAktiva[i]=skapaAmne(namn,enhet,masstal,halveringtid);
        }
    }
    
    else
    {
        printf("Filen finns int!\n");
        fp=fopen(filnamn,"wb");
    }
    fclose(fp);
}

//funktion att sortera ämnen
void sorteraAmne(Radioaktiva radioaktiva[], int *pAntalAmne)
{
    Radioaktiva temp;
    int i, j, val;
    printf("Vill du sortera efter namn(1), masstal(2) eller halveringstid(3):");
    scanf("%d",&val);

    if(val == 1)
    {
        for(i =0; i <(*pAntalAmne)-1; i++)
        {
            for(j=0; j < (*pAntalAmne)-i-1; j++)
            {
                if(strcmp(radioaktiva[j].namn, radioaktiva[j+1].namn)>0)
                {
                    temp =radioaktiva[j];
                    radioaktiva[j] = radioaktiva[j+1];
                    radioaktiva[j+1] = temp;
                }
            }
        }

    }
    else if(val == 2)
    {
        for(i =0; i <(*pAntalAmne)-1; i++)
        {
            for(j=0; j < (*pAntalAmne)-i-1; j++)
            {
                if(radioaktiva[j].masstal > radioaktiva[j+1].masstal)
                {
                    temp =radioaktiva[j];
                    radioaktiva[j] = radioaktiva[j+1];
                    radioaktiva[j+1] = temp;
                }
            }
        }

    }
    else
    {
        for(i =0; i <(*pAntalAmne)-1; i++)
        {
            for(j=0; j < (*pAntalAmne)-i-1; j++)
            {
                if(radioaktiva[j].halveringstid > radioaktiva[j+1].halveringstid)
                {
                    temp =radioaktiva[j];
                    radioaktiva[j] = radioaktiva[j+1];
                    radioaktiva[j+1] = temp;
                }
            }
        }
    }

}

// funktion att söka amnen
void sokAmne (Radioaktiva radioAktva[],int *pAntalAmne)
{
    int val;
    printf("Hur vill du soka?\n");

    while(val != 4)
    {
    printf("\n(1) namn\n");
    printf("(2) masstal\n");
    printf("(3) halveringstid\n");
    printf("(4) huvudmeny\n");
    printf("Ange val: ");
    scanf("%d",&val);

    switch (val)
    {
    case 1:sokMedNamn(radioAktva,pAntalAmne);
    break;
    case 2:hittaAmne_Masstal(radioAktva,pAntalAmne);
    break;
    case 3:hittaAmne_halveringtid(radioAktva,pAntalAmne);
    break;
    default:
    break;
    }
   }
    }

// fukntion att söka amnen genom att ge namn
int sokMedNamn(Radioaktiva radioAktiva[], int *pAntalAmne)
{
    int i,amneIndex,count=0; //count räkna antal amnen  som har hittas
    bool flag =false;
    char amneNamn[WORDLENGHT+1];

    printf("Ange sokstrang: ");
    scanf("%s%*c",amneNamn);

    printf("Namn\t\t\t\tMasstal\t\t\t\tHalveringstid(s)\n");
    printf("-------------------------------------------------------------------------------\n");
    for(i=0; i < (*pAntalAmne); i++)
    {
        if(strstr(radioAktiva[i].namn,amneNamn)!= NULL)
        {
            flag = true;
            amneIndex = i;
           printf("%s\t\t\t\t %d\t\t\t\t %.4e \n",radioAktiva[i].namn,radioAktiva[i].masstal,radioAktiva[i].halveringstid);
             count++;
        }
    }
    if(!flag)
    {
         return -1; // ingen amne har hittas
    }
    
    if(count >1)
    {
       return amneIndex* (-1); //mer än ett amne har hittas
    }
    if(count == 1)
    {
      return amneIndex; //exat ett amne har hittas
    }
}

// fukntion att söka amnen genom att ge masstal
int hittaAmne_Masstal(Radioaktiva radioAktiva[], int *pAntalAmne)
{
    int mass_tal, i,amneIndex,count =0;
    bool flag = false;
    printf("Ange sokstrang: ");
    scanf("%d",&mass_tal);
     
    printf("Namn\t\t\t\tMasstal\t\t\t\tHalveringstid(s)\n");
    printf("-------------------------------------------------------------------------------\n");
    for(i =0; i < (*pAntalAmne); i++)
    {
        if(radioAktiva[i].masstal == mass_tal)
        {
            flag = true;
            amneIndex = i;
            printf("%s\t\t\t\t %d\t\t\t\t %.4e \n",radioAktiva[i].namn,radioAktiva[i].masstal,radioAktiva[i].halveringstid);
            count++;
        }
    }
     if(!flag)
    {
         return -1; // ingen amne har hittas
    }
    
    if(count >1)
    {
       return amneIndex* (-1); //mer än ett amne har hittas
    }
    if(count == 1)
    {
      return amneIndex; //exat ett amne har hittas
    }
}

// fukntion att söka amnen genom halveringtids
int hittaAmne_halveringtid(Radioaktiva radioAktiva[], int *pAntalAmne)
{
    int amneIndex,i,count=0;
    double minstaV,storstaV;
    printf("Ange minsta halveringtid: ");
    scanf("%le",&minstaV);
    printf("Ange storsta halveringtid: ");
    scanf("%le",&storstaV);
     
    printf("Namn\t\t\t\tMasstal\t\t\t\tHalveringstid(s)\n");
    printf("--------------------------------------------------------------------------\n");
    for(i =0; i < (*pAntalAmne); i++)
    {
        if(radioAktiva[i].halveringstid >= minstaV && radioAktiva[i].halveringstid <= storstaV)
        {
            amneIndex =i;
            printf("%s\t\t\t\t %d\t\t\t\t %.4e \n",radioAktiva[i].namn,radioAktiva[i].masstal,radioAktiva[i].halveringstid);
            count++;
        }
    }
     if(count == 1)
    {
        return amneIndex; //ett amne har hittas
    }
    if(count > 1) // flera än ett amne har hittas
    {
        return amneIndex* (-1);
    }
    else
    {
        return -1;  // ingen amne har hittas
    }
}

//funktion att ändra på halverinngstid
void andraHavleringtid(Radioaktiva radioAktiva[], int *pAntalAmne)
{
    int val, i, j;
    double ny_halveringstid;
    printf("Andra halveringstid\n");
   
    for(i =0; i < (*pAntalAmne); i++)
    {
        printf("Vill du soka pa namn(1), masstal(2) eller halveringstid(3):");
        scanf("%d",&val);
      if(val == 1)
      {
          j=sokMedNamn(radioAktiva,pAntalAmne);
    
        if( j <= -1)
        {
            printf("Du fick inte exakt ett resultat.\n");
        }
        else
        {
            printf("Ange ny halveringstid: ");
            scanf("%le",&ny_halveringstid);
            radioAktiva[j].halveringstid = ny_halveringstid;
            break;
        }
      }
       if(val == 2)
      {
        j=hittaAmne_Masstal(radioAktiva,pAntalAmne);
        if( j <= -1)
        {
            printf("Du fick inte exakt ett resultat.\n");
        }
        else
        {
            printf("Ange ny halveringstid: ");
            scanf("%le",&ny_halveringstid);
            radioAktiva[j].halveringstid = ny_halveringstid;
            break;
        }
      }
       if(val == 3)
      {
        j=hittaAmne_halveringtid(radioAktiva,pAntalAmne);
    
        if( j <= -1)
        {
            printf("Du fick inte exakt ett resultat.\n");
        }
        else
        {
            printf("Ange ny halveringstid: ");
            scanf("%le",&ny_halveringstid);
            radioAktiva[j].halveringstid = ny_halveringstid;
            break;
        }
      }

    }
}
//funktion att avregistrera ämne
void avregistreraAmne(Radioaktiva radioAktiva[], int *pAntalAmne)
{
    int val,pos, i;
    printf("Avregistrera\n");
   
    while(1)
    {
        printf("Vill du soka pa namn(1), masstal(2) eller halveringstid(3):");
        scanf("%d",&val);
      if(val == 1)
      {
          pos=sokMedNamn(radioAktiva,pAntalAmne);
    
        if( pos <= -1)
        {
            printf("Du fick inte exakt ett resultat.\n");
        }
        else
        {
            break;
        }
      }
       if(val == 2)
      {
        pos=hittaAmne_Masstal(radioAktiva,pAntalAmne);
        if( pos <= -1)
        {
            printf("Du fick inte exakt ett resultat.\n");
        }
        else
        {
            break;
        }
      }
       if(val == 3)
      {
        pos=hittaAmne_halveringtid(radioAktiva,pAntalAmne);
    
        if( pos <= -1)
        {
            printf("Du fick inte exakt ett resultat.\n");
        }
        else
        {
            break;
        }
      }
     
    }
    printf("%s-%d avregistreras\n",radioAktiva[pos].namn,radioAktiva[pos].masstal);
    for(i =pos; i <= (*pAntalAmne)-1; i++)
    {
      radioAktiva[i]= radioAktiva[i+1];
    }
    (*pAntalAmne)--;
    

    
    
}

//funktion att skriva ut till filen
void skrivTillFilen(Radioaktiva radioAktivA[], int *pAntalAmne, char filnamn[])
{
     FILE *fp;
     int i;
    fp=fopen(filnamn,"w");

    if((*pAntalAmne) == MAX_AMNE)
    {
        printf("Registret ar full! kan inte lagga mer amnen\n");
    }
    if(fp!=NULL)
    {
        char namn[WORDLENGHT+1];
        int masstal;
        double halveringtid;

        fprintf(fp,"%d\n",*pAntalAmne);

        for(i =0; i <(*pAntalAmne); i++ )
        {
          fprintf(fp,"%s\t\t\t\t%d\t\t\t\t%.4e \n",radioAktivA[i].namn,radioAktivA[i].masstal,radioAktivA[i].halveringstid);  
        }
        fprintf(fp,"\n");
    }
}
