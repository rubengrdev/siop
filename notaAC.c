#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUMEX 20
#define NUMT 5

struct tema{
	int num_tema;
	int exercicis[NUMEX];
};



void init_bundles(struct tema *bb, struct tema *ba){

	int i=0,j=0;
	for(i=0;i<NUMT;i++){
		bb[i].num_tema=i;
		for(j=0;j<NUMEX;j++){
			bb[i].exercicis[j]=j;
		}
	}
	ba->num_tema=NUMT;
	for(j=0;j<NUMEX;j++){
		ba->exercicis[j]=j;
	}
}


int solve(int tema, int ex){
	int i;
	printf("Intentant resoldre l'exercici %d del tema %d...\n",ex,tema);
	printf("Funciona?(1 SI, 0 NO)\n");
	scanf("%d",&i);
	return i;
}


int main(int argc, char *argv[]){

struct tema bundle_basic[NUMT];
struct tema bundle_adv;

int i=0,j=0;
int nota_ac=0;
int correct=0;

init_bundles(bundle_basic, &bundle_adv);

for(i=0;i<NUMT;i++){
	j=0;correct=0;
	while(!correct && j<NUMEX){
		correct=solve(bundle_basic[i].num_tema,bundle_basic[i].exercicis[j]);
		j++;
	}
	if(j==NUMEX) {
		printf("Se t'han acabat els exercics del tema %d, parla amb la professora\n",i);
		exit(-1);
	}

}
nota_ac=7;
j=0;correct=0;

while(!correct && j<NUMEX){
	correct=solve(bundle_adv.num_tema,bundle_adv.exercicis[j]);
	j++;
}

if(j<NUMEX) nota_ac=10;

printf("Felicitats has arribat a final de curs sense perdre el teu temps de vida\n la teva nota de avaluacio continuada es un %d\n",nota_ac);
}

