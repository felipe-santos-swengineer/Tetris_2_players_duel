
//Marco agr s? falta vc colocar a sua logica de parar o tempo? e preciso que me diga onde a //nova pe?a est? sendo criada e colocada na matriz player pra que eu d? uma melhorada na //condi??o de parada, basicamente ? so verificar se as posic??es da nova pe?a estao true na //matriz espelho, ou seja olhar isso no lugar de se referenciar na primeira linha da matriz.
// tamb?m nn podemos esquecer de colocar o condicional de rota??o para que nn gire no meio de //colisoes? vlw por enquanto ? s? isso.

//ok, hj a noite a gente pode discutir isso pelo whats

//https://1drv.ms/u/s!AiPl9U7IzDER2yqJpq_nIPRF1dVy
///******	RECADO **************
/// baixe o arquivo pause.png e coloquem na pasta img. segue link:
/// https://1drv.ms/u/s!AiPl9U7IzDER2H2PrXpuqxy7pl-s
/// ESSE ? O ALGORITMO MAIS ATUALIZADO - 12-10-2018

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
} Coord; //estrutura que vai guardar os valores de x e y de cada quadrado na matriz q vai montar a pe?a

typedef struct p2{
	int px;
	int py;
} Coord2;//estrutura sera usada para guardar o codigo das pe?as. coluna e o px e linha ? o py


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

	sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo");

	sf::Texture texturause; //setando a imagem do menu
	texturause.loadFromFile("img/teladomenu.png");

	int opcaodomenu=0;// variavel que pega o que o usuario deseja fazer


	sf::Music musicadomenu; //carrega a musica do menu
	musicadomenu.openFromFile("Sons/musica_menu.ogg");
	musicadomenu.play();
	musicadomenu.setLoop(true); //deixa a musica em loop, ou seja, toca de novo sempre que acabar


//******************** DECLARA?AO DE VARIAVEIS ********************************************************
	int quem_ganhou=0;// variavel que dir? quando alguem perdeu...
	int goto_cont=1; //conta quantas vezes o menu foi aberto, para nn recriar variaveis
	int i, j, mov_y=0, mov_x=4; //mov_y e mov_x ? usado para incrementar a pe?a na matriz principal, no eix x e eixo y | MOV_X=4 para come?ar no meio
	int delay=3; // serve para dar um delay de 3 segundos antes da pe?a descer
	int aleatorioPeca; //vai receber um numero aleatorio entre 0 e 9;
	int aleatorioCor; //vai receber um numero aleatorio entre 0 e 5;
	int limitedapeca_y=0; //valor que vai controlar o limite da pe?a em rela?ao a borda inferior. ele ? igual ao maior valor da pe?a no eixo y;
	int limitedapeca_x=0; //valor que vai controlar o limite da pe?a em rela?ao a borda inferior. ele ? igual ao maior valor da pe?a no eixo x;
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
	//****************************************************************************





	//*************** MATRIZ GUARDA O CONJUNTO DE 4 ROTACOES POR PE?A *******************
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



	//****************** PADRAO DE PE?AS ( 9 TIPOS DE PE?AS DIFERENTES )**********************************************************

	int codigoPeca[23][8]={0,0,0,1,0,2,0,3,//guarda 9 codigos diferentes de 8 posicoes
                      	0,0,0,1,1,1,1,2,
                      	0,0,1,0,0,1,1,1,
                      	0,1,0,2,1,0,1,1,
                      	0,0,1,0,1,1,2,1,
                      	0,1,1,1,1,0,2,0,
                      	0,0,1,0,1,1,2,0,
                      	0,0,0,1,0,2,1,2,
                      	1,0,1,1,1,2,0,2,
                      	//termina as pe?as padrao e segue rota?oes
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

	//*********** TRANSFERE AS COORDENADAS DAS PE?AS PRE DEFINIDO PARA A MATRIZ COORDENADAS DASPECAS.PX E PY **************

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
	//setando valores das posicoes x e y de todas as pe?as
	for(i=0;i<10;i++){
    	for(j=0;j<20;j++){
        	matrizdevalxy[i][j].px=(i*20.8)+190.0; //i multiplica pois ? a coluna ; 20.8 px ? o recuo da pe?a no eixo x quando pressionado (largura)
        	matrizdevalxy[i][j].py=(j*20.7)+108.0; //j multiplica pois ? a linha ; 20.7 px ? o recuo da pe?a no eixo y quando pressionado  (altura)
    	}
	}

	//****************************************************************************



 	//sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo 1");

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

	sf::Texture texturadeganhou;
	texturadeganhou.loadFromFile("img/bg_ganhou.png");


	sf::Music musicanojogo;
	musicanojogo.openFromFile("Sons/musica_no_jogo.ogg");

	sf::Texture texturadeperdeu;//pega a sprite do fim de jogo
	texturadeperdeu.loadFromFile("img/bg_perdeu.png");

	sf::Music musicadoperdeumaquina; //pega a musica do fim de jogo
	musicadoperdeumaquina.openFromFile("Sons/musica_perdeu.ogg");

	sf::Music musicadoganhoumaquina;
	musicadoganhoumaquina.openFromFile("Sons/musica_ganhou.ogg");



	int proxCor[2];
	for(i=0;i<2;i++){
    	proxCor[i]=rand()%5;
	}
	aleatorioCor=proxCor[0]; // seta um valor aleatorio para carregar o arquivo de cor diferente a cada pe?a

	sf::Texture texturapeca;
	texturapeca.loadFromFile(cores[aleatorioCor]);


	sf::Texture texturapecaEstatica;

	sf::Texture texturaPause;
	texturaPause.loadFromFile("img/pause.png");


	int aleatorioPecaEmUso;
	int proximapeca[2];
	for(i=0;i<2;i++){
    	proximapeca[i]=rand()%9; //para nao gerar pe?as de codigo 3 e 4 pois tem redundancia com outras pe?as giradas
    	if(proximapeca[i]==4){proximapeca[i]=3;}
    	if(proximapeca[i]==5){proximapeca[i]=1;}

    	printf("aleat 0: %d", proximapeca[i]);
	}

	aleatorioPecaEmUso=proximapeca[0];
	aleatorioPeca=aleatorioPecaEmUso;



	int matrizdecodcoresparamatrizsecund[10][20];// serve para guardar o codigo de cores na posicao
	bool matrizPlayer[10][20]; //matriz da pe?a que desce
	bool matrizPlayerEstatico[10][20]; // matriz que copia a ultima posisao da pe?a

	//****************************** PE?A
	bool matrizproxPeca[4][4];
	Coord matrizvalProxPeca[4][4];


	goto_voltei_menu: // goto serve para voltar ao menu sempre que o jogo acabar
    	if(goto_cont>0){
	while (janela.isOpen()){ //menu

	sf::Sprite background1;
	background1.setTexture(texturause);

	sf::Event evento;

    	while (janela.pollEvent(evento)){ //captura o que o usario pretende fazer, jogar ou sair
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	}
        	else if (evento.type==sf::Event::KeyPressed){

            	if(evento.key.code==sf::Keyboard::Enter){
                    	opcaodomenu=1;

        	}

            	else  if(evento.key.code==sf::Keyboard::Escape){ //usado para testar a parte da colisao do eixo y
                    	opcaodomenu=2;
            	}
    	}}


    	if(opcaodomenu==2){
        	return 0;}
    	else if(opcaodomenu==1){
        	musicadomenu.stop();
        	opcaodomenu=0;

            	break;}

    	janela.draw(background1);
    	janela.display();
    	}
    	}
opcaodomenu=0;
musicadomenu.stop(); // para o loop, pq se n?o ficaria executando as musicas simultaneamente ao msm tempo;

     	// zero todas as variaveis, para que o jogo possa ser reiniciado sem bugs
            	zeramatrizproxpeca(matrizproxPeca);
            	zeramatrizprincipal(matrizPlayer);
            	zeramatrizsecundaria(matrizPlayerEstatico);
            	quem_ganhou=0;
            	mov_y=0; mov_x=4;
            	delay=3;
            	limitedapeca_y=0;
            	limitedapeca_x=0;
            	y=0; x=4;
            	corDaMatridecor=0;
            	pontos=0; cont=0; cont2=0;
            	j2=0; i2=0;
            	girar=0;
            	temposegundos=0; tempominutos=0;
            	contRegresMin=5; contRegresSeg=59;
            	pause=false;colisao_Y=false; colisao_X_Bot_Direita=0; colisao_X_Bot_Esquerda=0;
            	tempoMomentoPausa=0; tempoMomentoDESPausa=0; tempoEntrePausas=0; guardatempo=0;
            	clockCronometro.restart();
            	clockPauseTempo.restart();
            	clock.restart();
            	MovEsqOuDir=0;MovEsqOuDir1=0;contaMovEsqOuDir=0;VerificsColisao=0;
            	corrigidelay=0;

	for (i=0;i<4;i++){
    	for (j=0;j<4;j++){
        	matrizvalProxPeca[i][j].py=(i*20.8)+142.0;
        	matrizvalProxPeca[i][j].px=(j*20.7)+71.0;
    	}
	}

     	musicanojogo.play();
     	musicanojogo.setLoop(true); //toco a musica do jogo (Naruto)



	zeramatrizproxpeca(matrizproxPeca);
	zeramatrizsecundaria(matrizPlayerEstatico);
//############################################### COME?O DO LOOP #############################################################################

while (janela.isOpen()){
   // printf("guardatempo %f", guardatempo);


	if(pause==false){

	//printf("tempo: %f", clockCronometro.getElapsedTime().asSeconds());
   temposegundos = (int) clockCronometro.getElapsedTime().asSeconds(); //esta sendo feito o casting de float para inteiro
	if(temposegundos==60){
    	temposegundos=0;
     	tempominutos++;
    	clockCronometro.restart();
	}

	//convertendo inteiro em string para fazer a pontua?ao
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
	textoMotion2.setPosition(sf::Vector2f(482,228));}
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
	zeramatrizprincipal(matrizPlayer); //chama fun?ao que zera a matriz/ ele come?a com false em todas


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
        	}
    	}

    	if(mov_x>0 &&colisao_X_Bot_Esquerda==false){
        	if (evento.key.code==sf::Keyboard::Left){
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
        	}
    	}

    	if(mov_y<=18-limitedapeca_y){
        	if(evento.key.code==sf::Keyboard::Down&&colisao_Y==false&&delay==false){
            	for(j=0;j<4;j++){
            	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x][coordenadasdaspecas[aleatorioPeca][j].py + mov_y+1]==true){
            	corrigidelay++;}
            	}
            	if(corrigidelay==0)
            	mov_y++;
            	corrigidelay=0;
            	printf("mov_y: %d\n", mov_y);
            	//printf("limite y: %d\n", limitedapeca_y);
        	}
    	}
    	}
    	}
    	}


    	//esta parte anula a rota?ao na borda direita. se a soma da largora da pe?a com o recuo do eixo y for
    	//maior ou igual a 10(largura total do tetris), isso significa que ele pasou da borda. entao volta o giro.
    	if(mov_x+limitedapeca_x>=10){
        	girar--;
    	}
    	aleatorioPeca=matrizRotacao[aleatorioPecaEmUso][girar];
    	//****************************************************************************

	//printf("pe?a uso %d\n", aleatorioPecaEmUso);
	//********************** SETA VALORES TRUE DE ACORDO CO A MATRIZ DAS PE?AS ************************************
	//coordenadas passadas para matrizplayer de booleanos atravez da matriz coodenadas pecas px e py
	//esse la?o for ? feito dentro do loop principal, e pode ser incremeentado com valores mov_x e mov_y para os movimentos
	//matriz player ? a matriz de booleanos principal, e esta sendo passado como parametro a coordenadas das pe?as
	//a coluna ? gerada no rand() aleatorioPeca, e a posicao de x e y q existe na struct e passada para a matriz principal.

	colisao_X_Bot_Direita=0;
	colisao_X_Bot_Esquerda=0;
	for(j=0;j<4;j++){
    	matrizPlayer[coordenadasdaspecas[aleatorioPeca][j].px + mov_x][coordenadasdaspecas[aleatorioPeca][j].py + mov_y]=true;//mov_y e mov_x usados para mover a peca
    	//a partir daqui vai ser setado o valor do limite da pe?a de acordo com o valor de y;
    	//para a pe?a parar no lugar certo independente do tamanho (altura)
    	//limite das pe?as para variar nas bordas
    	//a variavel  limite da pe?a recebe o valor da posicao em relacao ao eixo, nao valores booleanos
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
    	//uma pe?a transparente e gerada uma casa para baixo e entao ? comparado se e true. se a proxima casa
    	//antes da pe?a verdadeira descer fro true, entao ele para a pe?a.

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

        	if(cont==10){//quando cont=10 significa que est? prenchida
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


    	for(i2=i-1;i2>0;i2--){ // esses 2 la?os tranferem todas as linhas acima da linha apagada pra baixo;
        	for(j2=0;j2<10;j2++){ //m
        	if(matrizPlayerEstatico[j2][i2]==true&&i2>0){ //impede que na linha zero, ele pegue o lixo de memoria, pois n?o existe nada acima da linha 0;
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



	for(i=0;i<10;i++){ // verifico se o jogador perdeu
        	if(matrizPlayerEstatico[i][cont2])
            	cont++;
            	}
    	if(cont!=0){
       	quem_ganhou=1;//essa variavel vai servir para abrir a sprite de dorrota
       	cont=0;
       	goto fimdojogo; // goto serve para ir direto para a execu?ao da sprite de dorrota;
    	}







    	janela.clear(sf::Color(255,255,255));
    	janela.draw(background);









    	//************************* IMPRIME OS TRUE DA MATRIZ PRINCIPAL *********************************
    	//la?o for verifica toda a matriz em busca de um true para imprimir.
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




     	//******* teste de proxima pe?a **********


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

    	//***************************** TIME DO JOGO ***********************************************


    	//parte do clock do jogo;
    	//fun?ao retoorna o valor em segundos da execu?ao, e de acordo com a
    	//comparacao se define a velocidade qque a pe?a cai,
    	// usando o incremento mov_y
    	if(!pause){ //se o pause for falso, fa?a

    	if(clock.getElapsedTime().asSeconds()>0.3){
       	if(delay){
        	delay--;
       	}

       	if(delay==0 && mov_y<=18-limitedapeca_y&&colisao_Y==false){ // limite de incrementa?ao ate em baixo vairoa com o tamanho da pe?a (limitepeca)
        	mov_y++;
        	//colisao_X_Bot_Direita=0;
        	//colisao_X_Bot_Esquerda=0;
       	}


        	else if(MovEsqOuDir!=0||contaMovEsqOuDir==0){

            	//copia os valotes de uma matriz para outra
            	if(delay==0){
                    	//fazendo a copia da maatriz no ultyimo estado
                    	//coloquei o if delay>=3 pq ele tava entrando 3 vezes, antes da pe?a come?ar a descer
                    	//o delay serve pra fazer a pe?a esperar um instante antes de descer..
                    	for(i=0;i<10;i++){
                        	for(j=0;j<20;j++){
                            	if(matrizPlayer[i][j]){
                            	matrizdecodcoresparamatrizsecund[i][j] = aleatorioCor;// toda vez que acontecer a copia sera copiado tmb o codigo da cor da pe?a em questao
                              	matrizPlayerEstatico[i][j]=matrizPlayer[i][j];
                            	}
                        	}
                	}
            	}

            	//assim que a pe?a atinge a borda, o valor dela ? mudada para ir pra cima
            	mov_y=0;
            	mov_x=4;
            	girar=0;
            	colisao_Y=false;
            	MovEsqOuDir=0;
            	//colisao_X_Bot_Direita=0;
            	//colisao_X_Bot_Esquerda=0; //reseta a condi?ao de colisao
            	//////////////////////////////////////////////////
            	//#################  PRODUZ OUTRA COR E OUTRO FORMATO #####################
            	if(delay==0){
                	//aleatorioCor=rand()%5; // seta um valor aleatorio para carregar o arquivo de cor diferente a cada pe?a
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
    	janela.draw(textoMotion);
    	janela.draw(textoMotion2);

    	janela.display();
	}
fimdojogo: //p2 ? o ponto que o goto vem
musicanojogo.stop(); //paro o loop musical da musica do jogo

quem_ganhou=2; //variavel que mostra quem ganhou, 1 = jogador ganhou, 2 = maquina ganhou
if(quem_ganhou==1){ //entro nos comandos de execu??o da sprite deorrta


	musicadoganhoumaquina.play();
	musicadoganhoumaquina.setLoop(true);
	cont=0;
	while (janela.isOpen()){ //menu

	sf::Sprite background2; // seta a textura do fim de jogo
	background2.setTexture(texturadeganhou);
 	sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	}
            	else if (evento.type==sf::Event::KeyPressed){

                	if(evento.key.code==sf::Keyboard::Enter){
                        	musicadoganhoumaquina.stop(); // paro o loop musical do fim de jogo
                        	goto_cont++;
                        	musicadomenu.play(); // colocando a musica do menu pra tocar de novo
                        	musicadomenu.setLoop(true);
                        	goto goto_voltei_menu; // volta ao menu caso digite esc

                	}

            	}
    	}
    	janela.draw(background2);
    	janela.display();

	}



}
else if(quem_ganhou==2){ //entro nos comandos de execu??o da sprite deorrta


	musicadoperdeumaquina.play();
	musicadoperdeumaquina.setLoop(true);
	cont=0;
	while (janela.isOpen()){ //menu

	sf::Sprite background2; // seta a textura do fim de jogo
	background2.setTexture(texturadeperdeu);
 	sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	}
        	else if (evento.type==sf::Event::KeyPressed){

            	if(evento.key.code==sf::Keyboard::Enter){
                    	musicadoperdeumaquina.stop(); // paro o loop musical do fim de jogo
                    	goto_cont++;
                    	musicadomenu.play(); // colocando a musica do menu pra tocar de novo
                    	musicadomenu.setLoop(true);
                    	goto goto_voltei_menu; // volta ao menu caso digite esc

        	}

    	}}
    	janela.draw(background2);
    	janela.display();

	}



}
//############################################### FIM DO LOOP #############################################################################

	return 0;
}























