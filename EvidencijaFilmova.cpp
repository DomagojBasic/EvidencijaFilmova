#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>


#define MAX 20



typedef struct{         
	char naslov[20+1];		
	char zanr[20+1];
	int godina;
	float ocijena;
}Podatci;   

typedef struct{
 int zadnji; 
Podatci elementi[MAX];
} Lista;

void ubaci (Podatci x, int pozicija_ubacivanja, Lista *pokLista)
{
  int pozicija;
  if (pokLista->zadnji >= MAX-1)
    printf("Lista je puna!");
  else if ((pozicija_ubacivanja>pokLista->zadnji+1) || (pozicija_ubacivanja<0) )
    printf("Pozicija ne postoji!");
  else {
            for (pozicija=pokLista->zadnji; pozicija >= pozicija_ubacivanja; pozicija--)
                 pokLista->elementi[pozicija+1]= pokLista->elementi[pozicija];
            pokLista->zadnji++;
            pokLista->elementi[pozicija_ubacivanja] = x;
           }
}

void ispis(Lista *pokLista){
  int pozicija;
  printf("\nR.BR\tNaslov filma\t\tZanr filma\tgodina\tocijena");
  for (pozicija=0; pozicija <= pokLista->zadnji; pozicija++){

    printf("\n%d.\t %s\t\t\t %s\t\t%d\t\t%.1f",pozicija+1, pokLista->elementi[pozicija].naslov,
									pokLista->elementi[pozicija].zanr,
									pokLista->elementi[pozicija].godina,
									pokLista->elementi[pozicija].ocijena);
    if (pozicija < pokLista->zadnji);

  }
}




void obrisi (int pozicija_brisanja, Lista *pokLista) {
  int pozicija;
  if ( (pozicija_brisanja>pokLista->zadnji ) || (pozicija_brisanja<0) )
    printf("Pozicija ne postoji!");
  else {
    pokLista->zadnji--;    
    for (pozicija=pozicija_brisanja; pozicija<=pokLista->zadnji; pozicija++)
       pokLista->elementi[pozicija] = pokLista->elementi[pozicija+1];
  
  }
}




void ispis_pretrage_naziva(Lista *pokLista)
{
	
	char naslov[50];
    int brojacPrazna=1;
    printf("\n");
    printf("Unesite Naslov filma ");
    scanf(" %s",&naslov);
    
    for(int pozicija=0; pozicija<=pokLista->zadnji; pozicija++)
     
{
        if (strcmp (naslov, pokLista->elementi[pozicija].naslov)==0)
        
        
        {
          brojacPrazna++;	
        	printf("\nR.Br.\tNaslov\t\tZanr\tGodina\tOcijena\n");
        	printf("\n%.d \t %st\t %s\t%d\t%.1f\n",pozicija+1,pokLista->elementi[pozicija].naslov,
									pokLista->elementi[pozicija].zanr,
									pokLista->elementi[pozicija].godina,
									pokLista->elementi[pozicija].ocijena);
        	
          	
		}
		
        else if (brojacPrazna==0)
        {
            printf("Nema trazenog unosa!");
        }                                       
}
}





void spremiDatoteku(Lista *pokLista)
{
	FILE *datoteka;
	datoteka = fopen("Evidencija_Filmova", "wb");
	if( datoteka == NULL ) 
	{
    printf("Problem u otvaranju datoteke!");
   	}
	else
	{
    	fwrite(pokLista , sizeof(*pokLista),1, datoteka);
   	}
   fclose( datoteka );
   printf("!!!Spremljena evidencija filma!");
}


void procitajDatoteku(Lista *pokLista) {
	FILE *datoteka;
	datoteka = fopen("Evidencija_Filmova", "rb");
	if( datoteka == NULL ) 
	{
    printf("Problem u otvaranju datoteke!");
  	}
  	else
	{
    fread(pokLista,sizeof(*pokLista),1,datoteka);
  	}
  fclose(datoteka );
  printf("!!!Ucitana evidencija filma!");
}




main(){
	Podatci PodatciFilma;
	Lista ListaFilma;
	
	ListaFilma.zadnji=-1;
	int odabir;
	
	
	do
	{
		printf("--------------------------------------------------------------------------------\n");
		printf("\n1. UNOS PODATAKA\n2. ISPIS PODATAKA\n3. OBRISI PODATKE\n4. PRETRAZI PODATKE\n5. SPREMI PODATKE\n6. UCITAJ PODATKE\n7. IZMJENI PODATKE\n8. IZLAZ\n\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("Odaberite\n");
		scanf("%d",&odabir);
		
		if(odabir==1)
		{
		int kolicina;
			printf("Koliko filmova zelite unijeti: ");
			scanf("%d",&kolicina);
				for(int i=1;i<=kolicina;i++)
				{
		printf("Unesi naslov %d. filma:\n",i);
		scanf(" %s",&PodatciFilma.naslov);
		
		
		do{
		
		printf("Unesi godinu %d. filma\n",i);
		scanf("%d",&PodatciFilma.godina);
			
			if(PodatciFilma.godina<0){
			printf("godina je manja od 0\n");
									}
		}
	while(PodatciFilma.godina<0);
	
		printf("Unesi zanr %d. filma\n",i);
		scanf(" %s",&PodatciFilma.zanr);
		
		do{
		
		
		printf("Unesi ocijenu %d. filma na IMDB-u\n",i);
		scanf("%f",&PodatciFilma.ocijena);
		
			if(PodatciFilma.ocijena<0){
			printf("Ocijena ne moze biti manja od 0\n");
									}
		}
		while(PodatciFilma.ocijena<0);
		
		
		ubaci(PodatciFilma,ListaFilma.zadnji+1,&ListaFilma);
		
		}
		
			
		}
		else if(odabir==2)
		{
				ispis(&ListaFilma);
		}
		else if(odabir==3)
		{
			int RedBrisanja;
				ispis(&ListaFilma);
				printf("\nKoji red zeite obrisati?");
				scanf("%d",&RedBrisanja);
			obrisi(RedBrisanja-1,&ListaFilma);
		}
		else if(odabir==4)
		{
			ispis_pretrage_naziva(&ListaFilma);
			
		}
		else if(odabir==5){
			spremiDatoteku(&ListaFilma);
			
	
		}
		else if(odabir==6){
			procitajDatoteku(&ListaFilma);
		}
		else if(odabir==7){
			{
			
			
	
			ispis(&ListaFilma);
			int broj;
				printf("\nUnesite redni broj filma kojeg zelite izmjeniti: ");
			scanf("%d", &broj);
			
			if(broj>0 && broj<ListaFilma.zadnji){
		
			
			obrisi(broj - 1, &ListaFilma);

		printf("Unesi naslov  filma:\n");
		scanf(" %s",&PodatciFilma.naslov);
		
		printf("Unesi godinu  filma\n");
		scanf("%d",&PodatciFilma.godina);
		
		printf("Unesi zanr  filma\n");
		scanf(" %s",&PodatciFilma.zanr);
		
		printf("Unesi ocijenu  filma na IMDB-u\n");
		scanf("%f",&PodatciFilma.ocijena);
		
		
			ubaci(PodatciFilma, ListaFilma.zadnji + broj, &ListaFilma);
		}
		else{
			printf("red ne postoji!");
		}
			
		}


	}
}
	
	while(odabir!=8);
}
