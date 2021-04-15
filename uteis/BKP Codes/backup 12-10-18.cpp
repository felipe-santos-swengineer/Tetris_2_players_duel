


///*********************    RECADO    ************************
/// baixe o arquivo pause.png e coloquem na pasta img. segue link:
/// https://1drv.ms/u/s!AiPl9U7IzDER2H2PrXpuqxy7pl-s
/// ESSE É O ALGORITMO MAIS ATUALIZADO - 10-10-2018

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
//#################################################### INT MAIN #############################################################################
int main(){

	srand(time(NULL));

	//******************** DECLARAÇAO DE VARIAVEIS ********************************************************
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
	int contRegresMin=2, contRegresSeg=59;
	bool pause=false, colisao_Y=false, colisao_X_Bot_Direita=false, colisao_X_Bot_Esquerda=false;
	float tempoMomentoPausa=0, tempoMomentoDESPausa=0, tempoEntrePausas=0, guardatempo=0;
	Coord2 coordenadasdaspecas [23][4];

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
        	matrizdevalxy[i][j].px=(i*20.8)+190.0; //i multiplica pois é a coluna ; 20.8 px é o recuo da peça no eixo x quando pressionado (largura)
        	matrizdevalxy[i][j].py=(j*20.7)+108.0; //j multiplica pois é a linha ; 20.7 px é o recuo da peça no eixo y quando pressionado  (altura)
    	}
	}

	//****************************************************************************



	sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo");

	sf::Clock clock;
	sf::Clock clockCronometro;
	sf::Clock clockPauseTempo;

	sf::Font fonteArcade;
	fonteArcade.loadFromFile("Fontes/ARCADECLASSIC.TTF");

	sf::Font fonteMotion;
	fonteMotion.loadFromFile("Fontes/MotionControl-Bold.ttf");

	sf::Text textoArcade;
	textoArcade.setFont(fonteArcade);

	sf::Text textoMotion;
	textoMotion.setFont(fonteMotion);

	sf::Text textoMotion2;
	textoMotion2.setFont(fonteMotion);


	sf::Texture texturabg;
	texturabg.loadFromFile("img/background.png");

    /*
	sf::Music p1;
	p1.openFromFile("sound1.ogg");
	p1.play();
*/


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
        	matrizvalProxPeca[i][j].px=(j*20.7)+71.0;
    	}
	}





	zeramatrizproxpeca(matrizproxPeca);
	zeramatrizsecundaria(matrizPlayerEstatico);
//############################################### COMEÇO DO LOOP #############################################################################

while (janela.isOpen()){
   // printf("guardatempo %f", guardatempo);




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
	textoArcade.setPosition(sf::Vector2f(75,300));


    if(contRegresMin - tempominutos>=0){ //condicional para impedir cronometro com numeros negativos
	//convertendo int dos segundos para string para fazer o cronometro
	std::stringstream ss2;
	if(temposegundos<50){ //condicional para incluir o zero a esquerda qdo o numero for menos que 10
        ss2<< ":"<< contRegresSeg - temposegundos <<std::endl;
	} else {
        ss2<< ":0"<< contRegresSeg - temposegundos <<std::endl;
	}

	std::string temposegundoString = ss2.str();

	textoMotion.setString(temposegundoString);
    textoMotion.setLetterSpacing(2);
	textoMotion.setCharacterSize(50);
	textoMotion.setFillColor(sf::Color(38,233,238));
	textoMotion.setPosition(sf::Vector2f(510,228));

	//convertendo int dos minutos para string para fazer o cronometro
	std::stringstream ss3;
	ss3<< contRegresMin - tempominutos <<std::endl;
	std::string tempominutoString = ss3.str();

	textoMotion2.setString(tempominutoString);
    textoMotion2.setLetterSpacing(2);
	textoMotion2.setCharacterSize(50);
	textoMotion2.setFillColor(sf::Color(38,233,238));
	textoMotion2.setPosition(sf::Vector2f(482,228));
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

    	if(mov_y>0){
        	if(evento.key.code==sf::Keyboard::Up){


            	//aleatorioPeca=0;
            	//mov_y--;
            	//printf("mov_y: %d\n", mov_y);
            	//printf("aleatorio: %d\n", aleatorioPeca);
            	printf("girar: %d\n", girar);
            	//printf("pecauso y: %d\n\n", aleatorioPecaEmUso);
            	girar++;
            	//girar=0;
            	if(girar>3){
                	girar=0;
            	};


        	}
    	}

    	if(mov_x<=8-limitedapeca_x &&colisao_X_Bot_Direita==false){
        	if (evento.key.code==sf::Keyboard::Right){
            	mov_x++;
            	//printf("mov_x: %d\n", mov_x);
            	//printf("limite x: %d\n", limitedapeca_x);
        	}
    	}

    	if(mov_x>0){
        	if (evento.key.code==sf::Keyboard::Left &&colisao_X_Bot_Esquerda==false){
            	mov_x--;
            	//printf("mov_x: %d\n", mov_x);
            	//printf("limite x: %d\n", limitedapeca_x);
        	}
    	}

    	if(mov_y<=18-limitedapeca_y){
        	if(evento.key.code==sf::Keyboard::Down){
            	mov_y++;
            	printf("mov_y: %d\n", mov_y);
            	//printf("limite y: %d\n", limitedapeca_y);
        	}
    	}
    	}
    	}
    	}

        //esta parte anula a rotaçao na borda direita. se a soma da largora da peça com o recuo do eixo y for
        //maior ou igual a 10(largura total do tetris), isso significa que ele pasou da borda. entao volta o giro.
    	if(mov_x+limitedapeca_x>=10){
            girar--;
        }
    	aleatorioPeca=matrizRotacao[aleatorioPecaEmUso][girar];
    	//****************************************************************************

	//printf("peça uso %d\n", aleatorioPecaEmUso);
	//********************** SETA VALORES TRUE DE ACORDO CO A MATRIZ DAS PEÇAS ************************************
	//coordenadas passadas para matrizplayer de booleanos atravez da matriz coodenadas pecas px e py
	//esse laço for é feito dentro do loop principal, e pode ser incremeentado com valores mov_x e mov_y para os movimentos
	//matriz player é a matriz de booleanos principal, e esta sendo passado como parametro a coordenadas das peças
	//a coluna é gerada no rand() aleatorioPeca, e a posicao de x e y q existe na struct e passada para a matriz principal.

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
            colisao_Y=true;
    	}

        ///PARTE DAS COLISOES - EIXO X

        if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x+1][coordenadasdaspecas[aleatorioPeca][j].py + mov_y]==true/*||
            matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x+1][coordenadasdaspecas[aleatorioPeca][j].py + mov_y+1]==true*/){
            colisao_X_Bot_Direita=true;
    	} else {
            colisao_X_Bot_Direita=false;
    	}
    	//********************

    	//if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x-2][coordenadasdaspecas[aleatorioPeca][j].py + mov_y]==true/*||
       //     matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x-1][coordenadasdaspecas[aleatorioPeca][j].py + mov_y+1]==true*/){
       //     colisao_X_Bot_Esquerda=true;
    	//} else {
       //     colisao_X_Bot_Esquerda=false;
    	//}

	}


    	//******************* PARTE DO FELIPE ***************************
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

	//****************************************************************************









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
       	} else {

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

        colisao_Y=false; //reseta a condiçao de colisao

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
    	janela.draw(textoMotion);
        janela.draw(textoMotion2);

    	janela.display();
	}
//############################################### FIM DO LOOP #############################################################################

	return 0;
}

