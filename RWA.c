#include<stdio.h>

#define INFINITY 9999
#define MAX 3

int calcule_indice(int s,int r){
	return (r+((s-1)*3));
}

void main(){

	int i,j,z,compt=0,tmp;
	int LightP[9][9] = {0};

	int Com[3][3] = {
		{0,1,1},
		{1,0,1},
		{1,1,0}
		};

	int Chemin[3][3] = {
		{1,1,2},
		{2,2,2},
		{2,3,3}
	};

	int Lamda[3][3] = {
		{0,1,0},
		{1,0,1},
		{0,1,0}
	};
	//Generation de la matrice M2
	int M[9][9] = {0};

	printf("Matrice de communication\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
			printf("%d ",Com[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("Matrice de chemin\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
			printf("%d ",Chemin[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("Matrice de Lamda\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
			printf("%d ",Lamda[i][j]);
		printf("\n");
	}
	printf("\n");

	//Parcour 
	printf("Calcule des indices\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(Com[i][j]==1){
				if(Chemin[i][j] != (i+1) && Chemin[i][j] != (j+1)){
					tmp = calcule_indice((i+1),Chemin[i][j]);
					printf("Indice : %d ",tmp);
					M[compt][tmp-1] = 1;
					
					tmp = calcule_indice(Chemin[i][j],(j+1));
					printf("Indice : %d \n",tmp);
					M[compt][tmp-1] = 1;		
				}
				else{
					tmp = calcule_indice((i+1),(j+1));
					printf("Indice : %d \n",tmp);
					M[compt][tmp-1] = 1;				
				}
			}				
			else
				printf("Indice : 0 \n");	
			compt++;		
		}
	}
	printf("\n");

	printf("Affichage matrice transition\n");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++)
			printf("%d ",M[i][j]);
		printf("\n");
	}
	printf("\n");
	
	printf("Creation de matrice LightPath ...\n");

	//Parcour et vérification :
	for (i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(M[i][j] == 1){
				for(z=i+1;z<9;z++){
					if(M[z][j] == 1){
						LightP[i][z] = 1;
						LightP[z][i] = 1;			
					}

				}
			}
		}
	}

	printf("Matrice de Light Path\n");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++)
			printf("%d ",LightP[i][j]);
		printf("\n");
	}
	printf("\n");

}
