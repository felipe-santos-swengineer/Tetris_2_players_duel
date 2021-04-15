 #include<unistd.h> 
 #include<stdio.h>
 int main(){ 
 	int x, y=2;
 	char nome[20];
 	
	FILE *file=fopen("Ranking_1_Lugar.txt", "r");
	while(y){
		fgets(nome,sizeof(nome), file);
		y--;	
	}
	
	fclose(file);
	
	printf("valor: %s", nome);
	 
  
    }