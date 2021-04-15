/// CODIGO DA IA

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <SFML/Audio.hpp>

typedef struct p{
	double px;
	double py;
} Coord; //estrutura que vai guardar os valores de x e y de cada quadrado na matriz q vai montar a peça

typedef struct p2{
	int px;
	int py;
} Coord2;//estrutura sera usada para guardar o codigo das peças. coluna e o px e linha é o py


Coord matrizdevalxy[10][20]; //matriz que guardara os pontos x e y corretos de cada quadrado na posicao


void zeramatrizprincipal(bool matriz[10][20]){
	int i,j;
	for(i=0;i<10;i++){
    	for(j=0;j<20;j++){
        	matriz[i][j]=false;
    	}
	}
}

void zeramatrizsecundaria(bool matriz[10][20]){
	int i, j;
	for(i=0;i<10;i++){
    	for(j=0;j<20;j++){
        	matriz[i][j]=false;
    	}
	}
}

void zeramatrizproxpeca(bool matriz[4][4]){
	int i, j;
	for (i=0;i<4;i++){
    	for(j=0;j<4;j++){
        	matriz[i][j]=false;
    	}
	}
}

int decisaoIA(){
    int IA_botao_baixo=rand()%2;
    int IA_botao_cima=rand()%2;
    int IA_botao_esq=rand()%2;
    int IA_botao_dir=rand()%2;
    return 10000 + (IA_botao_esq*1000) + (IA_botao_dir*100) + (IA_botao_cima*10) + (IA_botao_baixo);
}


//#################################################### INT MAIN #############################################################################
int main(){
	srand(time(NULL));

	sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo");
    janela.setFramerateLimit(10);

	sf::Texture texturause; //setando a imagem do menu
	texturause.loadFromFile("img/teladomenu.png");

	int opcaodomenu=0;// variavel que pega o que o usuario deseja fazer




//******************** DECLARAÇAO DE VARIAVEIS ********************************************************
	int quem_ganhou=0;// variavel que dirá quando alguem perdeu...
	int goto_cont=1; //conta quantas vezes o menu foi aberto, para nn recriar variaveis
	int i, j, mov_y=0, mov_x=4; //mov_y e mov_x é usado para incrementar a peça na matriz principal, no eix x e eixo y | MOV_X=4 para começar no meio
	int delay=3; // serve para dar um delay de 3 segundos antes da peça descer
	int aleatorioPeca; //vai receber um numero aleatorio entre 0 e 9;
	int aleatorioCor; //vai receber um numero aleatorio entre 0 e 5;
	int limitedapeca_y=0; //valor que vai controlar o limite da peça em relaçao a borda inferior. ele é igual ao maior valor da peça no eixo y;
	int limitedapeca_x=0; //valor que vai controlar o limite da peça em relaçao a borda inferior. ele é igual ao maior valor da peça no eixo x;
	int y=0, x=4; //valores que serao incrementados nos eventos de botoes e limitara as bordas
	//bool colocarnoespelho=false; //para entrar no if de colocar na matrz espelho secundaria
	int corDaMatridecor=0;//serve pra guardar o valor do codigo espelho
	int pontos=0, cont=0,cont2=0;
	int j2=0,i2=0;
	int girar=0;
	int temposegundos=0, tempominutos=0;
	int contRegresMin=5, contRegresSeg=59;
	bool pause=false, colisao_Y=false;
	int colisao_X_Bot_Direita=0, colisao_X_Bot_Esquerda=0;
	float tempoMomentoPausa=0, tempoMomentoDESPausa=0, tempoEntrePausas=0, guardatempo=0;
	Coord2 coordenadasdaspecas [23][4];
	int MovEsqOuDir=0,MovEsqOuDir1=0;
	int contaMovEsqOuDir=0;
	int VerificsColisao=0;
	int corrigidelay=0;
	int corrigirotacao=0,aleatorioPecateste=0;
	int controtacao=0;
	int IA_DECOD_MOVIMENTO[5];
    int COD_MOVIMENTO;
	bool IA_botao_esq=false, IA_botao_dir=false, IA_botao_baixo=false, IA_botao_cima=false;
	//****************************************************************************





	//*************** MATRIZ GUARDA O CONJUNTO DE 4 ROTACOES POR PEÇA *******************
	int matrizRotacao[9][4]={0,9,0,9,
                        	1,10,1,10,
                        	2,2,2,2,
                        	3,11,3,11,
                        	4,12,4,12,
                        	5,13,5,13,
                        	6,14,17,20,
                        	7,15,18,21,
                        	8,22,19,16
                        	};



	//****************** PADRAO DE PEÇAS ( 9 TIPOS DE PEÇAS DIFERENTES )**********************************************************

	int codigoPeca[23][8]={0,0,0,1,0,2,0,3,//guarda 9 codigos diferentes de 8 posicoes
                      	0,0,0,1,1,1,1,2,
                      	0,0,1,0,0,1,1,1,
                      	0,1,0,2,1,0,1,1,
                      	0,0,1,0,1,1,2,1,
                      	0,1,1,1,1,0,2,0,
                      	0,0,1,0,1,1,2,0,
                      	0,0,0,1,0,2,1,2,
                      	1,0,1,1,1,2,0,2,
                      	//termina as peças padrao e segue rotaçoes
                      	0,0,1,0,2,0,3,0,
                      	0,1,1,0,1,1,2,0,
                      	0,0,1,0,1,1,2,1,
                      	0,1,0,2,1,0,1,1,
                      	0,0,0,1,1,1,1,2,
                      	0,1,1,0,1,1,1,2,
                      	0,0,0,1,1,0,2,0,
                      	0,0,1,0,2,0,2,1,
                      	0,1,1,0,1,1,2,1,
                      	0,0,0,1,1,1,2,1,
                      	0,0,0,1,0,2,1,0,
                      	0,0,0,1,0,2,1,1,
                      	0,1,1,1,2,0,2,1,
                      	0,0,0,1,1,1,2,1
                      	};
	//****************************************************************************

	//*********** TRANSFERE AS COORDENADAS DAS PEÇAS PRE DEFINIDO PARA A MATRIZ COORDENADAS DASPECAS.PX E PY **************

	int aux=0;
	for(i=0;i<23;i++){
    	for(j=0;j<4;j++){
            	coordenadasdaspecas[i][j].px=codigoPeca[i][j+aux];
            	coordenadasdaspecas[i][j].py=codigoPeca[i][j+1+aux];
        	aux++;
    	}
	aux=0;
	}

	//****************************************************************************



	//****************** COLOCANDO VALORES NO VETOR DE STRING **********************************************************
	std::string cores[5]; //cada posicao tera uma string com o caminho do arquivo
	cores[0]="img/svg1.png";
	cores[1]="img/svg2.png";
	cores[2]="img/svg3.png";
	cores[3]="img/svg4.png";
	cores[4]="img/svg5.png";

 	//*******************************************************************************************



	//********** PREENCHENDO A MATRZ DE VALORES COM AS POSICOES X E Y CORRETAS, DE ACORDO COM O i E j ****************
	//setando valores das posicoes x e y de todas as peças
	for(i=0;i<10;i++){
    	for(j=0;j<20;j++){
        	matrizdevalxy[i][j].px=(i*20.8)+655.0; //i multiplica pois é a coluna ; 20.8 px é o recuo da peça no eixo x quando pressionado (largura)
        	matrizdevalxy[i][j].py=(j*20.7)+108.0; //j multiplica pois é a linha ; 20.7 px é o recuo da peça no eixo y quando pressionado  (altura)
    	}
	}

	//****************************************************************************



 	//sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo 1");

	sf::Clock clock;
	sf::Clock clockCronometro;
	sf::Clock clockPauseTempo;

	sf::Font fonteArcade;
	fonteArcade.loadFromFile("Fontes/ARCADECLASSIC.TTF");

	sf::Text textoArcade;
	textoArcade.setFont(fonteArcade);


	sf::Texture texturabg;
	texturabg.loadFromFile("img/background.png");

	sf::Texture texturadeganhou;
	texturadeganhou.loadFromFile("img/bg_ganhou.png");

	sf::Texture texturadeperdeu;//pega a sprite do fim de jogo
	texturadeperdeu.loadFromFile("img/bg_perdeu.png");


	int proxCor[2];
	for(i=0;i<2;i++){
    	proxCor[i]=rand()%5;
	}
	aleatorioCor=proxCor[0]; // seta um valor aleatorio para carregar o arquivo de cor diferente a cada peça

	sf::Texture texturapeca;
	texturapeca.loadFromFile(cores[aleatorioCor]);


	sf::Texture texturapecaEstatica;

	sf::Texture texturaPause;
	texturaPause.loadFromFile("img/pause.png");


	int aleatorioPecaEmUso;
	int proximapeca[2];
	for(i=0;i<2;i++){
    	proximapeca[i]=rand()%9; //para nao gerar peças de codigo 3 e 4 pois tem redundancia com outras peças giradas
    	if(proximapeca[i]==4){proximapeca[i]=3;}
    	if(proximapeca[i]==5){proximapeca[i]=1;}

    	printf("aleat 0: %d", proximapeca[i]);
	}

	aleatorioPecaEmUso=proximapeca[0];
	aleatorioPeca=aleatorioPecaEmUso;



	int matrizdecodcoresparamatrizsecund[10][20];// serve para guardar o codigo de cores na posicao
	bool matrizPlayer[10][20]; //matriz da peça que desce
	bool matrizPlayerEstatico[10][20]; // matriz que copia a ultima posisao da peça

	//****************************** PEÇA
	bool matrizproxPeca[4][4];
	Coord matrizvalProxPeca[4][4];




	for (i=0;i<4;i++){
    	for (j=0;j<4;j++){
        	matrizvalProxPeca[i][j].py=(i*20.8)+142.0;
        	matrizvalProxPeca[i][j].px=(j*20.7)+916.0;
    	}
	}



	zeramatrizproxpeca(matrizproxPeca);
	zeramatrizsecundaria(matrizPlayerEstatico);
//############################################### COMEÇO DO LOOP #############################################################################
int cont3=0;
while (janela.isOpen()){
   // printf("guardatempo %f", guardatempo);
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    cont3++;
    if(cont3==20){
    printf("+++++++++++\n");

    COD_MOVIMENTO=decisaoIA();

    for(i=0;i<5;i++){
        IA_DECOD_MOVIMENTO[i]=(COD_MOVIMENTO%10)*(pow (10,i));
        COD_MOVIMENTO=COD_MOVIMENTO/10;
    }

    IA_botao_baixo=IA_DECOD_MOVIMENTO[0];
    IA_botao_cima=IA_DECOD_MOVIMENTO[1];
    IA_botao_esq=IA_DECOD_MOVIMENTO[2];
    IA_botao_dir=IA_DECOD_MOVIMENTO[3];
    cont3=0;
    }

	if(pause==false){

	//printf("tempo: %f", clockCronometro.getElapsedTime().asSeconds());
   temposegundos = (int) clockCronometro.getElapsedTime().asSeconds(); //esta sendo feito o casting de float para inteiro
	if(temposegundos==60){
    	temposegundos=0;
     	tempominutos++;
    	clockCronometro.restart();
	}

	//convertendo inteiro em string para fazer a pontuaçao
	std::stringstream ss;
	ss << pontos <<std::endl;
	std::string stringdepontos = ss.str();

	textoArcade.setString(stringdepontos);
	textoArcade.setLetterSpacing(2);
	textoArcade.setCharacterSize(29);
	textoArcade.setFillColor(sf::Color::White);
	textoArcade.setPosition(sf::Vector2f(915,300));

	}


	sf::Sprite background;
	background.setTexture(texturabg);
	background.setPosition(sf::Vector2f(0,0));

	sf::Sprite spriteMov; //sprite mov se movimenta atravez da matriz principal
	spriteMov.setTexture(texturapeca);

	sf::Sprite spriteEst; //spriteest copia a posicao de spritemov para a matriz secondaria
	spriteEst.setTexture(texturapecaEstatica);

	sf::Sprite spriteproxpeca;
	spriteproxpeca.setTexture(texturapecaEstatica);

	sf::Sprite spritePause;
	spritePause.setTexture(texturaPause);
	spritePause.setPosition(sf::Vector2f(228,275));





	zeramatrizproxpeca(matrizproxPeca);
	zeramatrizprincipal(matrizPlayer); //chama funçao que zera a matriz/ ele começa com false em todas


    	///****************************** EVENTOS DE PRESSIONADO DE BOTOES **********************************************
    	sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyPressed){

    	///evento do pause

    	if(evento.key.code==sf::Keyboard::P){
            	if(!pause){
                	pause=true;
            	} else {
                	pause=false;
            	}

        	}

        	if(!pause){

            	if(evento.key.code==sf::Keyboard::L){ //usado para testar a parte da colisao do eixo y
                	if(!pause){
                	colisao_Y=true;
            	} else {
                	colisao_Y=false;
            	}
            	}
        	}
    	}
    	}
    	if(mov_y>0){
        	if(IA_botao_cima==true){

        	aleatorioPecateste=matrizRotacao[aleatorioPecaEmUso][girar+1];
        	for(j=0;j<4;j++){
        	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPecateste][j].px + mov_x][coordenadasdaspecas[aleatorioPecateste][j].py + mov_y]==true){
        	corrigirotacao++;}
         	if (coordenadasdaspecas[aleatorioPecateste][j].px + mov_x>9){
        	corrigirotacao++;}
         	if (coordenadasdaspecas[aleatorioPecateste][j].py + mov_y==19){
        	corrigirotacao++;}
         	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPecateste][j].px + mov_x][coordenadasdaspecas[aleatorioPecateste][j].py + mov_y+1]==true){
        	corrigirotacao++;}
  	}
        	if(corrigirotacao==0){
            	girar++;
            	controtacao++;
            	}

        	corrigirotacao=0;
        	aleatorioPecateste=0;



            	//aleatorioPeca=0;
            	//mov_y--;
            	//printf("mov_y: %d\n", mov_y);
            	//printf("aleatorio: %d\n", aleatorioPeca);
            	//printf("girar: %d\n", girar);
            	//printf("pecauso y: %d\n\n", aleatorioPecaEmUso);
            	//girar=0;
            	if(girar>3){
                	girar=0;
            	}
                IA_botao_cima=false;

    	}}

    	if(mov_x<=8-limitedapeca_x &&colisao_X_Bot_Direita==false){
        	if (IA_botao_dir==true){
            	for(j=0;j<4;j++){
                	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x+1][coordenadasdaspecas[aleatorioPeca][j].py + mov_y]==true){
                	VerificsColisao++;}
            	}
            	if(VerificsColisao==0){
            	mov_x++;
            	contaMovEsqOuDir++;}
            	VerificsColisao=0;
            	//printf("mov_x: %d\n", mov_x);
            	//printf("limite x: %d\n", limitedapeca_x);
            	IA_botao_dir==false;
        	}
    	}

    	if(mov_x>0 &&colisao_X_Bot_Esquerda==false){
        	if (IA_botao_esq==true){
            	for(j=0;j<4;j++){
                	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x-1][coordenadasdaspecas[aleatorioPeca][j].py + mov_y]==true){
                	VerificsColisao++;}

            	}
            	if(VerificsColisao==0){
            	mov_x--;
            	contaMovEsqOuDir++;}
            	VerificsColisao=0;
            	//printf("mov_x: %d\n", mov_x);
            	//printf("limite x: %d\n", limitedapeca_x);
            	IA_botao_esq==false;
        	}
    	}

    	if(mov_y<=18-limitedapeca_y){
        	if(IA_botao_baixo==true&&colisao_Y==false&&delay==false){
            	for(j=0;j<4;j++){
            	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x][coordenadasdaspecas[aleatorioPeca][j].py + mov_y+1]==true){
            	corrigidelay++;}
            	}
            	if(corrigidelay==0)
            	mov_y++;
            	corrigidelay=0;
            	//printf("mov_y: %d\n", mov_y);
            	//printf("limite y: %d\n", limitedapeca_y);
            	IA_botao_baixo==false;
        	}
    	}





    	//esta parte anula a rotaçao na borda direita. se a soma da largora da peça com o recuo do eixo y for
    	//maior ou igual a 10(largura total do tetris), isso significa que ele pasou da borda. entao volta o giro.



    	aleatorioPeca=matrizRotacao[aleatorioPecaEmUso][girar];
    	//printf("matrizrotacao[%d] [%d]\n",aleatorioPecaEmUso,girar);


    	//****************************************************************************

	//printf("peça uso %d\n", aleatorioPecaEmUso);
	//********************** SETA VALORES TRUE DE ACORDO CO A MATRIZ DAS PEÇAS ************************************
	//coordenadas passadas para matrizplayer de booleanos atravez da matriz coodenadas pecas px e py
	//esse laço for é feito dentro do loop principal, e pode ser incremeentado com valores mov_x e mov_y para os movimentos
	//matriz player é a matriz de booleanos principal, e esta sendo passado como parametro a coordenadas das peças
	//a coluna é gerada no rand() aleatorioPeca, e a posicao de x e y q existe na struct e passada para a matriz principal.

	colisao_X_Bot_Direita=0;
	colisao_X_Bot_Esquerda=0;
	for(j=0;j<4;j++){
    	matrizPlayer[coordenadasdaspecas[aleatorioPeca][j].px + mov_x][coordenadasdaspecas[aleatorioPeca][j].py + mov_y]=true;//mov_y e mov_x usados para mover a peca
    	//a partir daqui vai ser setado o valor do limite da peça de acordo com o valor de y;
    	//para a peça parar no lugar certo independente do tamanho (altura)
    	//limite das peças para variar nas bordas
    	//a variavel  limite da peça recebe o valor da posicao em relacao ao eixo, nao valores booleanos
    	if(j==0){
        	limitedapeca_y=coordenadasdaspecas[aleatorioPeca][0].py;
        	limitedapeca_x=coordenadasdaspecas[aleatorioPeca][0].px;
    	} else {
        	if(limitedapeca_y<=coordenadasdaspecas[aleatorioPeca][j].py){
            	limitedapeca_y=coordenadasdaspecas[aleatorioPeca][j].py;
        	}
        	if(limitedapeca_x<=coordenadasdaspecas[aleatorioPeca][j].px){
            	limitedapeca_x=coordenadasdaspecas[aleatorioPeca][j].px;
        	}
    	}

    	///PARTE DAS COLISOES - EIXO Y
    	//uma peça transparente e gerada uma casa para baixo e entao é comparado se e true. se a proxima casa
    	//antes da peça verdadeira descer fro true, entao ele para a peça.

    	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x][coordenadasdaspecas[aleatorioPeca][j].py + mov_y+1]==true){
        	colisao_Y++;
        	MovEsqOuDir++;
    	}

    	///PARTE DAS COLISOES - EIXO X
    	if(!colisao_Y){
            	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x+1][coordenadasdaspecas[aleatorioPeca][j].py + mov_y]==true){
            	colisao_X_Bot_Direita++;
        	} else {
            	//colisao_X_Bot_Direita=false;
        	}
        	//********************

        	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x-1][coordenadasdaspecas[aleatorioPeca][j].py + mov_y]==true){
        	colisao_X_Bot_Esquerda++;
        	} else {
        	//colisao_X_Bot_Esquerda=false;
        	}
    	}


	}


   	i=19;
     	while(i>0){

            	for(j=0;j<10;j++){//verifica se a linha esta prenchida, na ordem de baixo pra cima;
                	if(matrizPlayerEstatico[j][i])
                	cont++;
            	}

        	if(cont==10){//quando cont=10 significa que está prenchida
        	matrizPlayerEstatico[0][i]=false; //limpo a linha
        	matrizPlayerEstatico[1][i]=false;
        	matrizPlayerEstatico[2][i]=false;
        	matrizPlayerEstatico[3][i]=false;
        	matrizPlayerEstatico[4][i]=false;
        	matrizPlayerEstatico[5][i]=false;
        	matrizPlayerEstatico[6][i]=false;
        	matrizPlayerEstatico[7][i]=false;
        	matrizPlayerEstatico[8][i]=false;
        	matrizPlayerEstatico[9][i]=false;


    	for(i2=i-1;i2>0;i2--){ // esses 2 laços tranferem todas as linhas acima da linha apagada pra baixo;
        	for(j2=0;j2<10;j2++){ //m
        	if(matrizPlayerEstatico[j2][i2]==true&&i2>0){ //impede que na linha zero, ele pegue o lixo de memoria, pois não existe nada acima da linha 0;
            	matrizPlayerEstatico[j2][i2+1]=matrizPlayerEstatico[j2][i2];
            	matrizdecodcoresparamatrizsecund[j2][i2+1]=matrizdecodcoresparamatrizsecund[j2][i2];
            	matrizPlayerEstatico[j2][i2]=false;
    	}}}
    	for(i2=0;i2<20;i2++)
        	for(j2=0;j2<10;j2++)
            	if(matrizPlayerEstatico[j2][i2])
            	cont2++;
    	if(cont2>0){
        	pontos+=10;
        	printf("%d pontos, continue assim...\n",pontos);}}

    	cont=0;
    	cont2=0;
    	i--;}
	cont2=0;








    	janela.clear(sf::Color(255,255,255));
    	janela.draw(background);









    	//************************* IMPRIME OS TRUE DA MATRIZ PRINCIPAL *********************************
    	//laço for verifica toda a matriz em busca de um true para imprimir.
    	//se for true, ele imprime a figura com a matriz de valores na mesma posicao
    	for(i=0;i<10;i++){
        	for(j=0;j<20;j++){
            	if(matrizPlayer[i][j]){
              	spriteMov.setPosition(sf::Vector2f(matrizdevalxy[i][j].px, matrizdevalxy[i][j].py));
              	janela.draw(spriteMov);

            	}
        	}
    	}
    	//****************************************************************************




     	//******* teste de proxima peça **********


    	for(j=0;j<4;j++){
    	matrizproxPeca[coordenadasdaspecas[proximapeca[1] ][j].py][coordenadasdaspecas[proximapeca[1] ][j].px]=true;//mov_y e mov_x usados para mover a peca
    	}


    	for(i=0;i<4;i++){
        	for(j=0;j<4;j++){
            	if(matrizproxPeca[i][j]){
              	spriteproxpeca.setPosition(sf::Vector2f(matrizvalProxPeca[i][j].px, matrizvalProxPeca[i][j].py));
              	texturapecaEstatica.loadFromFile(cores[proxCor[1]]);
              	janela.draw(spriteproxpeca);


            	}
        	}
       	// puts("");
    	}


    	if(contaMovEsqOuDir!=0){
        	for(j=0;j<4;j++){
        	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x][coordenadasdaspecas[aleatorioPeca][j].py + mov_y+1]==true){
        	MovEsqOuDir1++;}
    	}
    	if(MovEsqOuDir1==0){
            	MovEsqOuDir=0;
            	colisao_Y=false;
            	contaMovEsqOuDir=0;
    	}}
    	MovEsqOuDir1=0;

     	if(controtacao!=0){
        	for(j=0;j<4;j++){
        	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x][coordenadasdaspecas[aleatorioPeca][j].py + mov_y+1]==true){
        	MovEsqOuDir1++;}
    	}
    	if(MovEsqOuDir1==0){
            	MovEsqOuDir=0;
            	colisao_Y=false;
            	controtacao=0;
    	}}
    	MovEsqOuDir1=0;
    	//***************************** TIME DO JOGO ***********************************************


    	//parte do clock do jogo;
    	//funçao retoorna o valor em segundos da execuçao, e de acordo com a
    	//comparacao se define a velocidade qque a peça cai,
    	// usando o incremento mov_y
    	if(!pause){ //se o pause for falso, faça

    	if(clock.getElapsedTime().asSeconds()>0.3){
       	if(delay){
        	delay--;
       	}

       	if(delay==0 && mov_y<=18-limitedapeca_y&&colisao_Y==false){ // limite de incrementaçao ate em baixo vairoa com o tamanho da peça (limitepeca)
        	mov_y++;
        	//colisao_X_Bot_Direita=0;
        	//colisao_X_Bot_Esquerda=0;
       	}


        	else if(MovEsqOuDir!=0||contaMovEsqOuDir==0){

            	//copia os valotes de uma matriz para outra
            	if(delay==0){
                    	//fazendo a copia da maatriz no ultyimo estado
                    	//coloquei o if delay>=3 pq ele tava entrando 3 vezes, antes da peça começar a descer
                    	//o delay serve pra fazer a peça esperar um instante antes de descer..
                    	for(i=0;i<10;i++){
                        	for(j=0;j<20;j++){
                            	if(matrizPlayer[i][j]){
                            	matrizdecodcoresparamatrizsecund[i][j] = aleatorioCor;// toda vez que acontecer a copia sera copiado tmb o codigo da cor da peça em questao
                              	matrizPlayerEstatico[i][j]=matrizPlayer[i][j];
                            	}
                        	}
                	}
            	}

            	//assim que a peça atinge a borda, o valor dela é mudada para ir pra cima
            	mov_y=0;
            	mov_x=4;
            	girar=0;
            	colisao_Y=false;
            	MovEsqOuDir=0;
            	//colisao_X_Bot_Direita=0;
            	//colisao_X_Bot_Esquerda=0; //reseta a condiçao de colisao
            	//////////////////////////////////////////////////
            	//#################  PRODUZ OUTRA COR E OUTRO FORMATO #####################
            	if(delay==0){
                	//aleatorioCor=rand()%5; // seta um valor aleatorio para carregar o arquivo de cor diferente a cada peça
                	//aleatorioPecaEmUso=rand()%9;
                	//aleatorioPecaEmUso=0;
                	aleatorioPecaEmUso=proximapeca[1];
                	proximapeca[0]=proximapeca[1];
                	proximapeca[1]=rand()%9;

                	if(proximapeca[1]==4){proximapeca[1]=3;}
                	if(proximapeca[1]==5){proximapeca[1]=1;}

                	//aleatorioPeca=3;
                	aleatorioCor=proxCor[1];
                	proxCor[0]=proxCor[1];
                	proxCor[1]=rand()%5;
                	texturapeca.loadFromFile(cores[aleatorioCor]);

            	}


       	}



        	clock.restart();
    	}
    	}
        	//***************** IMPRIME A MATRIZ SECUNDARIA ESPELHO ********************

        	for(i=0;i<10;i++){
            	for(j=0;j<20;j++){
                	if(matrizPlayerEstatico[i][j]){
                  	spriteEst.setPosition(sf::Vector2f(matrizdevalxy[i][j].px, matrizdevalxy[i][j].py));
                  	corDaMatridecor = matrizdecodcoresparamatrizsecund[i][j];//passa o codigo de cores da posicao para a variavel corDaMatridecor

                  	texturapecaEstatica.loadFromFile(cores[corDaMatridecor]);// carregar a cor correta na posicao atravaez da variavel corDaMatridecor
                  	janela.draw(spriteEst); //desenha a matriz secundaria

                	}
            	}
        	}



    	//****************************************************************************
    	if(pause){
        	janela.draw(spritePause);
    	}

    	janela.draw(textoArcade);
    	janela.display();

	}



//############################################### FIM DO LOOP #############################################################################

	return 0;
}























