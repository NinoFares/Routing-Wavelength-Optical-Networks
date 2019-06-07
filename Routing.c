#include<stdio.h>

#define INFINITY 9999
#define MAX 6
 
int dijkstra(int G[MAX][MAX],int n,int startnode,int dist);
void greedyColor(int G[MAX][MAX],int n);
void chooseRate(int dist);
 
int main()
{
	int i,j,n=6,u,dist;
	//G est la matrice distance entre les different noeuds

	
	int G[MAX][MAX] = {
		{0,500,600,0,0,0},
		{500,0,300,400,0,0},
		{600,300,0,500,400,0},
		{0,400,500,0,300,400},
		{0,0,400,300,0,600},
		{0,0,0,400,600,0}};
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%d ",G[i][j]);
		printf("\n");		
	}

	printf("\nEntrez le noeud initial : ");
	scanf("%d",&u);
	printf("\nEntrez le noeud déstination : ");
	scanf("%d",&dist);
	u=u-1;
	dist = dijkstra(G,n,u,dist);
	printf("\n");
	printf("\n");
	greedyColor(G,n);
	printf("\n");
	chooseRate(dist);
	printf("\n");
	return 0;
}

void chooseRate(int dist){

	int i,j,k,taille,rate;
	int nbrP=0,nP[3],nbr,min=1;

	float prix;

	int debit[3][3] = {{0,130,0},{60,0,200},{0,130,0}};
	int capacite[3][3] = {{0,140,0},{60,0,200},{0,130,0}};

	int R[3][3] = 	{{10,1750,1},
			{40,1800,2.5},
			{100,900,3.5}};
	

	for(i=0;i<3;i++){
		//Single Rate
		printf("\n\nAvec Rate %d ...\n",i);

		if(dist <= R[i][1]){
			nbrP++;
			nbr = 130 / R[i][0];
			prix = (nbr+1) * R[i][2];
			printf("\nPrix avec R%d est %.2f\n",(i+1),prix);
		}
		else
			printf("Impossible d'utiliser rate %d, Distance de couvrage inferieur a la distance du chemin.\n",(i+1));
	
	}

	for(i=0;i<3;i++){		
		//Multiple rate
		printf("\n\nMultiple rate ... \n");
		float minCost = 100000000;
		for(i=0;i<3;i++){
			nP[i] = 130/R[i][0];
		}
		
		if(nbrP==2){
			for(i=0;i<nP[0];i++){
				for(j=0;j<nP[1];j++){
					rate = (i*R[0][0])+(j*R[1][0]);
					prix = (i*R[0][2])+(j*R[1][2]);
					if(prix<minCost && rate>=taille)
						minCost = prix;
				}
			}
		}
		else if(nbrP==3){
			for(i=0;i<nP[0];i++){
				for(j=0;j<nP[1];j++){
					for(k=0;k<nP[2];k++){
						rate = (i*R[0][0])+(j*R[1][0])+(k*R[2][0]);
						prix = (i*R[0][2])+(j*R[1][2])+(k*R[2][2]);
						if(prix<minCost && rate>=taille)
							minCost = prix;
					}
				}
			}
		}		
		
		printf("Le prix avec le multiple rate %d\n",minCost);

		printf("\n\nDebit : \n");
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				printf("%d ",debit[i][j]);

		printf("\nCapacite : \n");
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				printf("%d ",capacite[i][j]);

	}
}

void greedyColor(int G[MAX][MAX],int n){

	int i,j,tmp;
	char chaine[5] = {'R','B','V','N','W'};
	char Vchaine[n]; //vecteur des couleurs

	//Labeling
	for(i=0;i<n;i++){
		Vchaine[i] = '0'; //Initialiser le vecteur aux couleur 0
	}

	//Initialisation de la premiere couleur
	Vchaine[0] = chaine[0]; //Donner couleur au premier noeuds


	for(i=1;i<n;i++){
		tmp = 0;
		for(j=0;j<i;j++){
			if(G[i][j] > 0){
				if(Vchaine[j] == chaine[tmp]){
					tmp++;
				}
			}
		}
		Vchaine[i] = chaine[tmp];
	}

	//Affichage des couleurs 
	for(i=0;i<n;i++)
		printf("Couleur du noeud %d : %c\n",(i+1),Vchaine[i]);	
}
 
int dijkstra(int G[MAX][MAX],int n,int startnode,int dist)
{
 
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	
	//pred[] Sauvgarde le prédecesseur de chaque noeud
	//Count donne le nombre de noeud visité
	

	//Creation de la matrice cost
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];
	
	//initilisation des vecteurs pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<n-1)
	{
		mindistance=INFINITY;
		
		//Verification du noeud avec la plus petite distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			
			//Vérifier si il ya un meilleure chemin			
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
 
	//Affichage du chemin le plus court et des distance entre les noeuds
	for(i=0;i<n;i++)
		if(i!=startnode)
		{
			if(dist == (i+1))
				dist = distance[i];
			printf("\nDistance entre v1 et v%d = %d",(i+1),distance[i]);
			printf("\nChemin le plus court = %d",(i+1));
			
			j=i;
			do
			{
				j=pred[j];
				printf("<-%d",(j+1));
			}while(j!=startnode);
	}
	printf("\n\nDistance entre noeud initial et final : %d\n",dist);

	return dist;
}
