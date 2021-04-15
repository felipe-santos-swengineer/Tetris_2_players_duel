

//https://1drv.ms/u/s!AiPl9U7IzDER2yqJpq_nIPRF1dVy
///******	RECADO **************
/// baixe o arquivo pause.png e coloquem na pasta img. segue link:
/// https://1drv.ms/u/s!AiPl9U7IzDER2H2PrXpuqxy7pl-s
/// ESSE É O ALGORITMO MAIS ATUALIZADO - 18-10-2018

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
}Coord2;

typedef struct p3{
	double px;
	double py;
} CoordIA; //estrutura que vai guardar os valores de x e y de cada quadrado na matriz q vai montar a peça

typedef struct p4{
	int px;
	int py;
}Coord2IA;//estrutura sera usada para guardar o codigo das peças. coluna e o px e linha é o py


Coord matrizdevalxy[10][20]; //matriz que guardara os pontos x e y corretos de cada quadrado na posicao

Coord matrizdevalxyIA[10][20];

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

	FILE *recorde=fopen("record.txt","r");
	FILE *recordista=fopen("nomedalenda.txt","r");

	char nome[5];

	fscanf(recordista,"%s",nome);
	printf("%s",nome);
	int maiorrecorde;
	int verifica_record_quebrado=0;
	fscanf(recorde,"%d",&maiorrecorde);
	//printf("%d",maiorrecorde);




	sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo");

	sf::Texture texturause; //setando a imagem do menu
	texturause.loadFromFile("img/teladomenu.png");

	int opcaodomenu=0;// variavel que pega o que o usuario deseja fazer


	sf::Music musicadomenu; //carrega a musica do menu
	musicadomenu.openFromFile("Sons/musica_menu.ogg");
	musicadomenu.play();
	musicadomenu.setLoop(true); //deixa a musica em loop, ou seja, toca de novo sempre que acabar


//******************** DECLARAÇAO DE VARIAVEIS ********************************************************
	int quem_ganhou=0;// variavel que dirá quando alguem perdeu...
	int i, j, mov_y=0,mov_yIA=0, mov_x=4,mov_xIA=4; //mov_y e mov_x é usado para incrementar a peça na matriz principal, no eix x e eixo y | MOV_X=4 para começar no meio
	int delay=3,delayIA=3; // serve para dar um delay de 3 segundos antes da peça descer
	int aleatorioPeca,aleatorioPecaIA; //vai receber um numero aleatorio entre 0 e 9;
	int aleatorioCor,aleatorioCorIA; //vai receber um numero aleatorio entre 0 e 5;
	int limitedapeca_y=0,limitedapeca_yIA=0; //valor que vai controlar o limite da peça em relaçao a borda inferior. ele é igual ao maior valor da peça no eixo y;
	int limitedapeca_x=0,limitedapeca_xIA=0; //valor que vai controlar o limite da peça em relaçao a borda inferior. ele é igual ao maior valor da peça no eixo x;
	int y=0,yIA=0, x=4,xIA=4; //valores que serao incrementados nos eventos de botoes e limitara as bordas
	//bool colocarnoespelho=false; //para entrar no if de colocar na matrz espelho secundaria
	int corDaMatridecor=0,corDaMatridecorIA=0;//serve pra guardar o valor do codigo espelho
	int pontos=0,pontosIA=0, cont=0,cont2=0;
	int j2=0,i2=0;
	int girar=0,girarIA=0;
	int temposegundos=0, tempominutos=0;
	int contRegresMin=5, contRegresSeg=59;
	bool pause=false, colisao_Y=false,colisao_YIA=false;
	int colisao_X_Bot_Direita=0,colisao_X_Bot_DireitaIA=0, colisao_X_Bot_Esquerda=0,colisao_X_Bot_EsquerdaIA=0;
	float tempoMomentoPausa=0, tempoMomentoDESPausa=0, tempoEntrePausas=0, guardatempo=0;
	Coord2 coordenadasdaspecas [23][4];
 	Coord2IA coordenadasdaspecasIA [23][4];
	int MovEsqOuDir=0,MovEsqOuDir1=0,MovEsqOuDir1IA=0,MovEsqOuDirIA=0;
	int contaMovEsqOuDir=0,contaMovEsqOuDirIA=0;
	int VerificsColisao=0,VerificsColisaoIA=0;
	int corrigidelay=0,corrigidelayIA=0;
	int corrigirotacao=0,aleatorioPecateste=0,corrigirotacaoIA=0,aleatorioPecatesteIA=0;
	int controtacao=0,controtacaoIA=0;
	int contaletra=0;
	int impededuplatecla=0; int impededuplateclaIA=0;
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
            	coordenadasdaspecasIA[i][j].px=codigoPeca[i][j+aux];
            	coordenadasdaspecas[i][j].py=codigoPeca[i][j+1+aux];
            	coordenadasdaspecasIA[i][j].py=codigoPeca[i][j+1+aux];
        	aux++;
    	}
	aux=0;
	}

	//*****************************/***********************************************



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
        	matrizdevalxy[i][j].py=(j*20.7)+108.0;
        	matrizdevalxyIA[i][j].px=(i*20.8)+655.0; //i multiplica pois é a coluna ; 20.8 px é o recuo da peça no eixo x quando pressionado (largura)
        	matrizdevalxyIA[i][j].py=(j*20.7)+108.0; //j multiplica pois é a linha ; 20.7 px é o recuo da peça no eixo y quando pressionado  (altura)
    	//j multiplica pois é a linha ; 20.7 px é o recuo da peça no eixo y quando pressionado  (altura)
    	}
	}

	//****************************************************************************




	sf::Clock clock;
	sf::Clock clockIA;
	sf::Clock clockCronometro;
	sf::Clock clockPauseTempo;
	sf::Clock clockCronometroIA;
	sf::Clock clockPauseTempoIA;

	sf::Font fonteArcade;
	fonteArcade.loadFromFile("Fontes/ARCADECLASSIC.TTF");

	sf::Font fonteMotion;
	fonteMotion.loadFromFile("Fontes/MotionControl-Bold.ttf");

	sf::Text textoArcade;
	textoArcade.setFont(fonteArcade);

	sf::Text textoArcade2;
	textoArcade2.setFont(fonteArcade);

	sf::Text textoArcade3;
	textoArcade3.setFont(fonteArcade);

	sf::Text textoArcade4;
	textoArcade4.setFont(fonteArcade);

	sf::Text textoArcade5;
	textoArcade5.setFont(fonteArcade);

	sf::Text textoMotion;
	textoMotion.setFont(fonteMotion);

	sf::Text textoMotion2;
	textoMotion2.setFont(fonteMotion);


	sf::Texture texturabg;
	texturabg.loadFromFile("img/background.png");

	sf::Texture texturadeganhou;
	texturadeganhou.loadFromFile("img/bg_ganhou.png");

	sf::Texture texturadequebrourecorde;
	texturadequebrourecorde.loadFromFile("img/telaquebrourec.png");


	sf::Music musicanojogo;
	musicanojogo.openFromFile("Sons/musica_no_jogo.ogg");

	sf::Music musicaquebrourec;
	musicaquebrourec.openFromFile("Sons/musica_quebrou_rec.ogg");

	sf::Texture texturadeperdeu;//pega a sprite do fim de jogo
	texturadeperdeu.loadFromFile("img/bg_perdeu.png");

	sf::Music musicadoperdeumaquina; //pega a musica do fim de jogo
	musicadoperdeumaquina.openFromFile("Sons/musica_perdeu.ogg");

	sf::Music musicadoganhoumaquina;
	musicadoganhoumaquina.openFromFile("Sons/musica_ganhou.ogg");



	int proxCor[2];
	int proxCorIA[2];
	for(i=0;i<2;i++){
    	proxCor[i]=rand()%5;
    	proxCorIA[i]=rand()%5;
	}
	aleatorioCor=proxCor[0];// seta um valor aleatorio para carregar o arquivo de cor diferente a cada peça
	aleatorioCorIA=proxCorIA[0];

	sf::Texture texturapecaIA;
	texturapecaIA.loadFromFile(cores[aleatorioCorIA]);

	sf::Texture texturapeca;
	texturapeca.loadFromFile(cores[aleatorioCor]);


	sf::Texture texturapecaEstatica;
	sf::Texture texturapecaEstaticaIA;



	int aleatorioPecaEmUso;
	int aleatorioPecaEmUsoIA;
	int proximapeca[2];
	int proximapecaIA[2];
	for(i=0;i<2;i++){
    	proximapeca[i]=rand()%9; //para nao gerar peças de codigo 3 e 4 pois tem redundancia com outras peças giradas
    	proximapecaIA[i]=rand()%9;
    	if(proximapeca[i]==4){proximapeca[i]=3;}
    	if(proximapeca[i]==5){proximapeca[i]=1;}
    	if(proximapecaIA[i]==4){proximapecaIA[i]=3;}
    	if(proximapecaIA[i]==5){proximapecaIA[i]=1;}
    	//printf("aleat 0: %d", proximapeca[i]);
	}

	aleatorioPecaEmUso=proximapeca[0];
	aleatorioPecaEmUsoIA=proximapecaIA[0];
	aleatorioPeca=aleatorioPecaEmUso;
	aleatorioPecaIA=aleatorioPecaEmUsoIA;


	int matrizdecodcoresparamatrizsecund[10][20];// serve para guardar o codigo de cores na posicao
	bool matrizPlayer[10][20]; //matriz da peça que desce
	bool matrizPlayerEstatico[10][20]; // matriz que copia a ultima posisao da peça
	int matrizdecodcoresparamatrizsecundIA[10][20];// serve para guardar o codigo de cores na posicao
	bool matrizPlayerIA[10][20]; //matriz da peça que desce
	bool matrizPlayerEstaticoIA[10][20]; // matriz que copia a ultima posisao da peça
	//****************************** PEÇA
	bool matrizproxPeca[4][4];
	Coord matrizvalProxPeca[4][4];
	bool matrizproxPecaIA[4][4];
	CoordIA matrizvalProxPecaIA[4][4];


	goto_voltei_menu: // goto serve para voltar ao menu sempre que o jogo acabar
	while (janela.isOpen()){ //menu

	sf::Sprite background1;
	background1.setTexture(texturause);

	sf::Event evento;

    	while (janela.pollEvent(evento)){ //captura o que o usario pretende fazer, jogar ou sair
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	}
        	else if (evento.type==sf::Event::KeyReleased){

            	if(evento.key.code==sf::Keyboard::Enter){
                    	opcaodomenu=1;

        	}

            	else  if(evento.key.code==sf::Keyboard::Escape){ //usado para testar a parte da colisao do eixo y
                    	fclose(recorde);
                    	fclose(recordista);
                    	opcaodomenu=2;
            	}
    	}}


    	if(opcaodomenu==2){
        	fclose(recorde);
        	fclose(recordista);
        	return 0;}
    	else if(opcaodomenu==1){
        	musicadomenu.stop();
        	opcaodomenu=0;

            	break;}

    	janela.draw(background1);
    	janela.display();
    	}

opcaodomenu=0;
musicadomenu.stop(); // para o loop, pq se não ficaria executando as musicas simultaneamente ao msm tempo;

     	// zero todas as variaveis, para que o jogo possa ser reiniciado sem bugs
            	zeramatrizproxpeca(matrizproxPeca);
            	zeramatrizprincipal(matrizPlayer);
            	zeramatrizsecundaria(matrizPlayerEstatico);
             	zeramatrizproxpeca(matrizproxPecaIA);
            	zeramatrizprincipal(matrizPlayerIA);
            	zeramatrizsecundaria(matrizPlayerEstaticoIA);

    	quem_ganhou=0;// variavel que dirá quando alguem perdeu...
    	mov_y=0;mov_yIA=0; mov_x=4;mov_xIA=4; //mov_y e mov_x é usado para incrementar a peça na matriz principal, no eix x e eixo y | MOV_X=4 para começar no meio
    	delay=3;delayIA=3; // serve para dar um delay de 3 segundos antes da peça descer
    	aleatorioPeca;aleatorioPecaIA; //vai receber um numero aleatorio entre 0 e 9;
    	aleatorioCor;aleatorioCorIA; //vai receber um numero aleatorio entre 0 e 5;
    	limitedapeca_y=0;limitedapeca_yIA=0; //valor que vai controlar o limite da peça em relaçao a borda inferior. ele é igual ao maior valor da peça no eixo y;
    	limitedapeca_x=0;limitedapeca_xIA=0;
    	y=0;yIA=0; x=4;xIA=4;
    	corDaMatridecor=0;corDaMatridecorIA=0;
    	pontos=0;pontosIA=0; cont=0;cont2=0;
    	j2=0;i2=0;
    	girar=0;girarIA=0;
    	temposegundos=0;tempominutos=0;
    	contRegresMin=5; contRegresSeg=59;
    	pause=false; colisao_Y=false;colisao_YIA=false;
    	colisao_X_Bot_Direita=0;colisao_X_Bot_DireitaIA=0; colisao_X_Bot_Esquerda=0;colisao_X_Bot_EsquerdaIA=0;
    	tempoMomentoPausa=0; tempoMomentoDESPausa=0; tempoEntrePausas=0; guardatempo=0;
    	MovEsqOuDir=0; MovEsqOuDir1=0; MovEsqOuDir1IA=0; MovEsqOuDirIA=0;
    	contaMovEsqOuDir=0; contaMovEsqOuDirIA=0;
    	VerificsColisao=0; VerificsColisaoIA=0;
    	corrigidelay=0; corrigidelayIA=0;
    	corrigirotacao=0; aleatorioPecateste=0; corrigirotacaoIA=0; aleatorioPecatesteIA=0;
    	controtacao=0; controtacaoIA=0;
    	clockCronometro.restart();
    	clockCronometroIA.restart();
    	clock.restart();
    	clockIA.restart();
    	clockPauseTempo.restart();
    	clockPauseTempoIA.restart();
    	verifica_record_quebrado=0;contaletra=0;
    	impededuplatecla=0;impededuplateclaIA=0;

    	if(maiorrecorde==0){
            	nome[0]=32;nome[1]=32;nome[2]=32;nome[3]=32;nome[4]=32;
    	}

	for (i=0;i<4;i++){
    	for (j=0;j<4;j++){
        	matrizvalProxPeca[i][j].py=(i*20.8)+142.0;
        	matrizvalProxPeca[i][j].px=(j*20.7)+71.0;
         	matrizvalProxPecaIA[i][j].py=(i*20.8)+142.0;
        	matrizvalProxPecaIA[i][j].px=(j*20.7)+916.0;
    	}
	}

     	musicanojogo.play();
     	musicanojogo.setLoop(true); //toco a musica do jogo (Naruto)



	zeramatrizproxpeca(matrizproxPeca);
	zeramatrizsecundaria(matrizPlayerEstatico);

	zeramatrizproxpeca(matrizproxPecaIA);
	zeramatrizsecundaria(matrizPlayerEstaticoIA);
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

	std::stringstream ssIA;
	ssIA << pontosIA <<std::endl;
	std::string stringdepontosIA = ssIA.str();

	textoArcade2.setString(stringdepontosIA);
	textoArcade2.setLetterSpacing(2);
	textoArcade2.setCharacterSize(29);
	textoArcade2.setFillColor(sf::Color::White);
	textoArcade2.setPosition(sf::Vector2f(915,300));



	std::stringstream mostrarecorde;
	mostrarecorde << maiorrecorde <<std::endl;
	std::string stringderecord = mostrarecorde.str();

	textoArcade3.setString(stringderecord);
	textoArcade3.setLetterSpacing(2);
	textoArcade3.setCharacterSize(29);
	textoArcade3.setFillColor(sf::Color::White);
	textoArcade3.setPosition(sf::Vector2f(482,420));

	std::string nomerecorde=nome;

	textoArcade5.setString(nomerecorde);
	textoArcade5.setLetterSpacing(2);
	textoArcade5.setCharacterSize(29);
	textoArcade5.setFillColor(sf::Color::White);
	textoArcade5.setPosition(sf::Vector2f(482,445));

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



	sf::Sprite background;
	background.setTexture(texturabg);
	background.setPosition(sf::Vector2f(0,0));

	sf::Sprite spriteMov; //sprite mov se movimenta atravez da matriz principal
	spriteMov.setTexture(texturapeca);

	sf::Sprite spriteEst; //spriteest copia a posicao de spritemov para a matriz secondaria
	spriteEst.setTexture(texturapecaEstatica);

	sf::Sprite spriteproxpeca;
	spriteproxpeca.setTexture(texturapecaEstatica);

	sf::Sprite spriteMovIA; //sprite mov se movimenta atravez da matriz principal
	spriteMovIA.setTexture(texturapecaIA);

	sf::Sprite spriteEstIA; //spriteest copia a posicao de spritemov para a matriz secondaria
	spriteEstIA.setTexture(texturapecaEstaticaIA);

	sf::Sprite spriteproxpecaIA;
	spriteproxpecaIA.setTexture(texturapecaEstaticaIA);







	zeramatrizproxpeca(matrizproxPeca);
	zeramatrizprincipal(matrizPlayer); //chama funçao que zera a matriz/ ele começa com false em todas
 	zeramatrizproxpeca(matrizproxPecaIA);
	zeramatrizprincipal(matrizPlayerIA); //chama funçao que zera a matriz/ ele começa com false em todas


    	///****************************** EVENTOS DE PRESSIONADO DE BOTOES **********************************************
    	sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){



            	if(evento.key.code==sf::Keyboard::L){ //usado para testar a parte da colisao do eixo y
                	if(!pause){
                	colisao_Y=true;
            	} else {
                	colisao_Y=false;
            	}
            	}

    	if(mov_y>0){
        	if(evento.key.code==sf::Keyboard::W){

        	aleatorioPecateste=matrizRotacao[aleatorioPecaEmUso][girar+1];
        	for(j=0;j<4;j++){
        	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPecateste][j].px + mov_x][coordenadasdaspecas[aleatorioPecateste][j].py + mov_y]==true){
        	corrigirotacao++;}
         	if (coordenadasdaspecas[aleatorioPecateste][j].px + mov_x>9){
        	corrigirotacao++;}
        	if (coordenadasdaspecas[aleatorioPecaEmUso][j].px + mov_x>9){ //add
        	corrigirotacao++;}
        	if (coordenadasdaspecas[aleatorioPecaEmUso][j].py + mov_y>19){ //add
        	corrigirotacao++;}
         	if (coordenadasdaspecas[aleatorioPecateste][j].py + mov_y==19){
        	corrigirotacao++;}
         	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPecateste][j].px + mov_x][coordenadasdaspecas[aleatorioPecateste][j].py + mov_y+1]==true){
        	corrigirotacao++;}

  	}
        	if(corrigirotacao==0){
            	girar++;
            	impededuplatecla++;
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


    	}}

    	if(mov_x<=8-limitedapeca_x &&impededuplatecla==0){
        	if (evento.key.code==sf::Keyboard::D){
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

    	if(mov_x>0 &&impededuplatecla==0){
        	if (evento.key.code==sf::Keyboard::A){
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
        	if(evento.key.code==sf::Keyboard::S&&delay==false){
            	for(j=0;j<4;j++){
            	if (matrizPlayerEstatico[coordenadasdaspecas[aleatorioPeca][j].px + mov_x][coordenadasdaspecas[aleatorioPeca][j].py + mov_y+1]==true){
            	corrigidelay++;}
            	}
            	if(corrigidelay==0)
            	mov_y++;
            	corrigidelay=0;
            	//printf("mov_y: %d\n", mov_y);
            	//printf("limite y: %d\n", limitedapeca_y);
        	}
    	}
    	if(mov_yIA>0){
        	if(evento.key.code==sf::Keyboard::Up){

        	aleatorioPecatesteIA=matrizRotacao[aleatorioPecaEmUsoIA][girarIA+1];
        	for(j=0;j<4;j++){
        	if (matrizPlayerEstaticoIA[coordenadasdaspecasIA[aleatorioPecatesteIA][j].px + mov_xIA][coordenadasdaspecasIA[aleatorioPecatesteIA][j].py + mov_yIA]==true){
        	corrigirotacaoIA++;}
         	if (coordenadasdaspecasIA[aleatorioPecatesteIA][j].px + mov_xIA>9){
        	corrigirotacaoIA++;}
         	if (coordenadasdaspecasIA[aleatorioPecatesteIA][j].py + mov_yIA==19){
        	corrigirotacaoIA++;}
         	if (matrizPlayerEstaticoIA[coordenadasdaspecasIA[aleatorioPecatesteIA][j].px + mov_xIA][coordenadasdaspecasIA[aleatorioPecatesteIA][j].py + mov_yIA+1]==true){
        	corrigirotacaoIA++;}
        	if (coordenadasdaspecasIA[aleatorioPecaEmUsoIA][j].px + mov_xIA>9){ //add
        	corrigirotacaoIA++;}
        	if (coordenadasdaspecasIA[aleatorioPecaEmUso][j].py + mov_yIA>19){ //add
        	corrigirotacaoIA++;}
  	}
        	if(corrigirotacaoIA==0){
            	girarIA++;
            	impededuplateclaIA++;
            	controtacaoIA++;
            	}

        	corrigirotacaoIA=0;
        	aleatorioPecatesteIA=0;


            	if(girarIA>3){
                	girarIA=0;
            	}


    	}}

    	if(mov_xIA<=8-limitedapeca_xIA&&impededuplateclaIA==0){
        	if (evento.key.code==sf::Keyboard::Right){
            	for(j=0;j<4;j++){
                	if (matrizPlayerEstaticoIA[coordenadasdaspecasIA[aleatorioPecaIA][j].px + mov_xIA+1][coordenadasdaspecasIA[aleatorioPecaIA][j].py + mov_yIA]==true){
                	VerificsColisaoIA++;}
            	}
            	if(VerificsColisaoIA==0){
            	mov_xIA++;
            	contaMovEsqOuDirIA++;}
            	VerificsColisaoIA=0;
            	//printf("mov_x: %d\n", mov_x);
            	//printf("limite x: %d\n", limitedapeca_x);
        	}
    	}

    	if(mov_xIA>0 &&impededuplateclaIA==0){
        	if (evento.key.code==sf::Keyboard::Left){
            	for(j=0;j<4;j++){
                	if (matrizPlayerEstaticoIA[coordenadasdaspecasIA[aleatorioPecaIA][j].px + mov_xIA-1][coordenadasdaspecasIA[aleatorioPecaIA][j].py + mov_yIA]==true){
                	VerificsColisaoIA++;}

            	}
            	if(VerificsColisaoIA==0){
            	mov_xIA--;
            	contaMovEsqOuDirIA++;}
            	VerificsColisaoIA=0;
            	//printf("mov_x: %d\n", mov_x);
            	//printf("limite x: %d\n", limitedapeca_x);
        	}
    	}

    	if(mov_yIA<=18-limitedapeca_yIA){
        	if(evento.key.code==sf::Keyboard::Down&&delayIA==false){
            	for(j=0;j<4;j++){
            	if (matrizPlayerEstaticoIA[coordenadasdaspecasIA[aleatorioPecaIA][j].px + mov_xIA][coordenadasdaspecasIA[aleatorioPecaIA][j].py + mov_yIA+1]==true){
            	corrigidelayIA++;}
            	}
            	if(corrigidelayIA==0)
            	mov_yIA++;
            	corrigidelayIA=0;
            	//printf("mov_y: %d\n", mov_y);
            	//printf("limite y: %d\n", limitedapeca_y);
        	}
    	}
    	}
    	}


    	//esta parte anula a rotaçao na borda direita. se a soma da largora da peça com o recuo do eixo y for
    	//maior ou igual a 10(largura total do tetris), isso significa que ele pasou da borda. entao volta o giro.


    	aleatorioPecaIA=matrizRotacao[aleatorioPecaEmUsoIA][girarIA];
    	aleatorioPeca=matrizRotacao[aleatorioPecaEmUso][girar];
    	//printf("matrizrotacao[%d] [%d]\n",aleatorioPecaEmUso,girar);
    	impededuplatecla=0;
    	impededuplateclaIA=0;


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
        	colisao_Y++;
        	MovEsqOuDir++;
    	}

    	matrizPlayerIA[coordenadasdaspecasIA[aleatorioPecaIA][j].px + mov_xIA][coordenadasdaspecasIA[aleatorioPecaIA][j].py + mov_yIA]=true;//mov_y e mov_x usados para mover a peca
    	//a partir daqui vai ser setado o valor do limite da peça de acordo com o valor de y;
    	//para a peça parar no lugar certo independente do tamanho (altura)
    	//limite das peças para variar nas bordas
    	//a variavel  limite da peça recebe o valor da posicao em relacao ao eixo, nao valores booleanos
    	if(j==0){
        	limitedapeca_yIA=coordenadasdaspecasIA[aleatorioPecaIA][0].py;
        	limitedapeca_xIA=coordenadasdaspecasIA[aleatorioPecaIA][0].px;
    	} else {
        	if(limitedapeca_yIA<=coordenadasdaspecasIA[aleatorioPecaIA][j].py){
            	limitedapeca_yIA=coordenadasdaspecasIA[aleatorioPecaIA][j].py;
        	}
        	if(limitedapeca_xIA<=coordenadasdaspecasIA[aleatorioPecaIA][j].px){
            	limitedapeca_xIA=coordenadasdaspecasIA[aleatorioPecaIA][j].px;
        	}
    	}

    	///PARTE DAS COLISOES - EIXO Y
    	//uma peça transparente e gerada uma casa para baixo e entao é comparado se e true. se a proxima casa
    	//antes da peça verdadeira descer fro true, entao ele para a peça.

    	if (matrizPlayerEstaticoIA[coordenadasdaspecasIA[aleatorioPecaIA][j].px + mov_xIA][coordenadasdaspecasIA[aleatorioPecaIA][j].py + mov_yIA+1]==true){
        	colisao_YIA++;
        	MovEsqOuDirIA++;
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
        	//printf("%d pontos, continue assim...\n",pontos);}}
     	}}
    	cont=0;
    	cont2=0;
    	i--;}
	cont2=0;
	cont=0;

 i=19;
     	while(i>0){

            	for(j=0;j<10;j++){//verifica se a linha esta prenchida, na ordem de baixo pra cima;
                	if(matrizPlayerEstaticoIA[j][i])
                	cont++;
            	}

        	if(cont==10){//quando cont=10 significa que está prenchida
        	matrizPlayerEstaticoIA[0][i]=false; //limpo a linha
        	matrizPlayerEstaticoIA[1][i]=false;
        	matrizPlayerEstaticoIA[2][i]=false;
        	matrizPlayerEstaticoIA[3][i]=false;
        	matrizPlayerEstaticoIA[4][i]=false;
        	matrizPlayerEstaticoIA[5][i]=false;
        	matrizPlayerEstaticoIA[6][i]=false;
        	matrizPlayerEstaticoIA[7][i]=false;
        	matrizPlayerEstaticoIA[8][i]=false;
        	matrizPlayerEstaticoIA[9][i]=false;


    	for(i2=i-1;i2>0;i2--){ // esses 2 laços tranferem todas as linhas acima da linha apagada pra baixo;
        	for(j2=0;j2<10;j2++){ //m
        	if(matrizPlayerEstaticoIA[j2][i2]==true&&i2>0){ //impede que na linha zero, ele pegue o lixo de memoria, pois não existe nada acima da linha 0;
            	matrizPlayerEstaticoIA[j2][i2+1]=matrizPlayerEstaticoIA[j2][i2];
            	matrizdecodcoresparamatrizsecundIA[j2][i2+1]=matrizdecodcoresparamatrizsecundIA[j2][i2];
            	matrizPlayerEstaticoIA[j2][i2]=false;
    	}}}
    	for(i2=0;i2<20;i2++)
        	for(j2=0;j2<10;j2++)
            	if(matrizPlayerEstaticoIA[j2][i2])
            	cont2++;
    	if(cont2>0){
        	pontosIA+=10;
        	//printf("%d pontos, continue assim...\n",pontos);}}
     	}}
    	cont=0;
    	cont2=0;
    	i--;}
	cont2=0;
	cont=0;

   	if(maiorrecorde<pontos){
        	maiorrecorde=pontos;
        	verifica_record_quebrado=1;

    	}
     	if(maiorrecorde<pontosIA){
        	maiorrecorde=pontosIA;
        	verifica_record_quebrado=2;

    	}


	for(i=0;i<10;i++){ // verifico se o jogador perdeu
        	if(matrizPlayerEstatico[i][cont2])
            	cont++;
            	}
    	if(cont!=0){
       	quem_ganhou=2;//essa variavel vai servir para abrir a sprite de dorrota
       	cont=0;
       	goto fimdojogo; // goto serve para ir direto para a execuçao da sprite de dorrota;
    	}
	for(i=0;i<10;i++){ // verifico se o jogador perdeu
        	if(matrizPlayerEstaticoIA[i][cont2])
            	cont++;
            	}
    	if(cont!=0){
       	quem_ganhou=1;//essa variavel vai servir para abrir a sprite de dorrota
       	cont=0;
       	goto fimdojogo; // goto serve para ir direto para a execuçao da sprite de dorrota;
    	}






    	janela.clear(sf::Color(255,255,255));
    	janela.draw(background);









    	//************************* IMPRIME OS TRUE DA MATRIZ PRINCIPAL *********************************
    	//laço for verifica toda a matriz em busca de um true para imprimir.
    	//se for true, ele imprime a figura com a matriz de valores na mesma posicao
    	for(i=0;i<10;i++){
        	for(j=0;j<20;j++){
            	if(matrizPlayer[i][j]){
              	spriteMov.setPosition(sf::Vector2f(matrizdevalxy[i][j].px, matrizdevalxy[i][j].py));
              	janela.draw(spriteMov);}
              	if(matrizPlayerIA[i][j]){
              	spriteMovIA.setPosition(sf::Vector2f(matrizdevalxyIA[i][j].px, matrizdevalxyIA[i][j].py));
              	janela.draw(spriteMovIA);}


        	}
    	}



    	//****************************************************************************




     	//******* teste de proxima peça **********


    	for(j=0;j<4;j++){
    	matrizproxPeca[coordenadasdaspecas[proximapeca[1] ][j].py][coordenadasdaspecas[proximapeca[1] ][j].px]=true;//mov_y e mov_x usados para mover a peca
    	matrizproxPecaIA[coordenadasdaspecasIA[proximapecaIA[1] ][j].py][coordenadasdaspecasIA[proximapecaIA[1] ][j].px]=true;
    	}



    	for(i=0;i<4;i++){
        	for(j=0;j<4;j++){
            	if(matrizproxPeca[i][j]){
              	spriteproxpeca.setPosition(sf::Vector2f(matrizvalProxPeca[i][j].px, matrizvalProxPeca[i][j].py));
              	texturapecaEstatica.loadFromFile(cores[proxCor[1]]);
              	janela.draw(spriteproxpeca);


            	}
            	if(matrizproxPecaIA[i][j]){
              	spriteproxpecaIA.setPosition(sf::Vector2f(matrizvalProxPecaIA[i][j].px, matrizvalProxPecaIA[i][j].py));
              	texturapecaEstaticaIA.loadFromFile(cores[proxCorIA[1]]);
              	janela.draw(spriteproxpecaIA);}
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

    	if(contaMovEsqOuDirIA!=0){
        	for(j=0;j<4;j++){
        	if (matrizPlayerEstaticoIA[coordenadasdaspecasIA[aleatorioPecaIA][j].px + mov_xIA][coordenadasdaspecasIA[aleatorioPecaIA][j].py + mov_yIA+1]==true){
        	MovEsqOuDir1IA++;}
    	}
    	if(MovEsqOuDir1IA==0){
            	MovEsqOuDirIA=0;
            	colisao_YIA=false;
            	contaMovEsqOuDirIA=0;
    	}}
    	MovEsqOuDir1IA=0;

     	if(controtacaoIA!=0){
        	for(j=0;j<4;j++){
        	if (matrizPlayerEstaticoIA[coordenadasdaspecasIA[aleatorioPecaIA][j].px + mov_xIA][coordenadasdaspecasIA[aleatorioPecaIA][j].py + mov_yIA+1]==true){
        	MovEsqOuDir1IA++;}
    	}
    	if(MovEsqOuDir1IA==0){
            	MovEsqOuDirIA=0;
            	colisao_YIA=false;
            	controtacaoIA=0;
    	}}
    	MovEsqOuDir1IA=0;
    	//***************************** TIME DO JOGO ***********************************************


    	//parte do clock do jogo;
    	//funçao retoorna o valor em segundos da execuçao, e de acordo com a
    	//comparacao se define a velocidade qque a peça cai,
    	// usando o incremento mov_y


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



    	if(clockIA.getElapsedTime().asSeconds()>0.3){
       	if(delayIA){
        	delayIA--;
       	}

       	if(delayIA==0 && mov_yIA<=18-limitedapeca_yIA&&colisao_YIA==false){ // limite de incrementaçao ate em baixo vairoa com o tamanho da peça (limitepeca)
        	mov_yIA++;
        	//colisao_X_Bot_Direita=0;
        	//colisao_X_Bot_Esquerda=0;
       	}


        	else if(MovEsqOuDirIA!=0||contaMovEsqOuDirIA==0){

            	//copia os valotes de uma matriz para outra
            	if(delayIA==0){
                    	//fazendo a copia da maatriz no ultyimo estado
                    	//coloquei o if delay>=3 pq ele tava entrando 3 vezes, antes da peça começar a descer
                    	//o delay serve pra fazer a peça esperar um instante antes de descer..
                    	for(i=0;i<10;i++){
                        	for(j=0;j<20;j++){
                            	if(matrizPlayerIA[i][j]){
                            	matrizdecodcoresparamatrizsecundIA[i][j] = aleatorioCorIA;// toda vez que acontecer a copia sera copiado tmb o codigo da cor da peça em questao
                              	matrizPlayerEstaticoIA[i][j]=matrizPlayerIA[i][j];
                            	}
                        	}
                	}
            	}

            	//assim que a peça atinge a borda, o valor dela é mudada para ir pra cima
            	mov_yIA=0;
            	mov_xIA=4;
            	girarIA=0;
            	colisao_YIA=false;
            	MovEsqOuDirIA=0;
            	//colisao_X_Bot_Direita=0;
            	//colisao_X_Bot_Esquerda=0; //reseta a condiçao de colisao
            	//////////////////////////////////////////////////
            	//#################  PRODUZ OUTRA COR E OUTRO FORMATO #####################
            	if(delayIA==0){
                	//aleatorioCor=rand()%5; // seta um valor aleatorio para carregar o arquivo de cor diferente a cada peça
                	//aleatorioPecaEmUso=rand()%9;
                	//aleatorioPecaEmUso=0;
                	aleatorioPecaEmUsoIA=proximapecaIA[1];
                	proximapecaIA[0]=proximapecaIA[1];
                	proximapecaIA[1]=rand()%9;

                	if(proximapecaIA[1]==4){proximapecaIA[1]=3;}
                	if(proximapecaIA[1]==5){proximapecaIA[1]=1;}

                	//aleatorioPeca=3;
                	aleatorioCorIA=proxCorIA[1];
                	proxCorIA[0]=proxCorIA[1];
                	proxCorIA[1]=rand()%5;
                	texturapecaIA.loadFromFile(cores[aleatorioCorIA]);

            	}


       	}
            	clockIA.restart();
    	}
        	//***************** IMPRIME A MATRIZ SECUNDARIA ESPELHO ********************

        	for(i=0;i<10;i++){
            	for(j=0;j<20;j++){
                	if(matrizPlayerEstaticoIA[i][j]){
                  	spriteEstIA.setPosition(sf::Vector2f(matrizdevalxyIA[i][j].px, matrizdevalxyIA[i][j].py));
                  	corDaMatridecorIA = matrizdecodcoresparamatrizsecundIA[i][j];//passa o codigo de cores da posicao para a variavel corDaMatridecor

                  	texturapecaEstaticaIA.loadFromFile(cores[corDaMatridecorIA]);// carregar a cor correta na posicao atravaez da variavel corDaMatridecor
                  	janela.draw(spriteEstIA); //desenha a matriz secundaria

                	}
            	}
        	}


    	//****************************************************************************


    	janela.draw(textoArcade);
    	janela.draw(textoArcade2);
    	janela.draw(textoArcade3);
    	if(verifica_record_quebrado==0){
    	janela.draw(textoArcade5);}
    	else {  nome[0]=32;nome[1]=32;nome[2]=32;nome[3]=32;nome[4]=32;
            	janela.draw(textoArcade5);}
    	janela.draw(textoMotion);
    	janela.draw(textoMotion2);

    	janela.display();

	}
fimdojogo:
//printf("%d pontos %d pontosIA",pontos,pontosIA);
musicanojogo.stop(); //paro o loop musical da musica do jogo
	//printf("%d",verifica_record_quebrado);
	//verifica_record_quebrado=1;
    	contaletra=0;
    	if(verifica_record_quebrado!=0){
        	verifica_record_quebrado=0;
        	nome[0]=32;nome[1]=32;nome[2]=32;nome[3]=32;nome[4]=32;
        	musicaquebrourec.play();
        	musicaquebrourec.setLoop(true);

	while (janela.isOpen()){

	sf::Sprite telarecorde;
	telarecorde.setTexture(texturadequebrourecorde);
	sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	}
            	else if (evento.type==sf::Event::KeyReleased){

                	if(evento.key.code==sf::Keyboard::Enter&&contaletra==5){
                        	musicaquebrourec.stop();
                        	contaletra=0;
                        	recordista=fopen("nomedalenda.txt","w");
                        	fprintf(recordista,"%s",nome);
                        	recorde=fopen("record.txt","w");
                        	fprintf(recorde,"%d",maiorrecorde);


                        	goto diga_quem_venceu; // paro o loop musical do fim de jogo


                	}


           	if(evento.key.code==sf::Keyboard::BackSpace&&contaletra>0){
                        	nome[contaletra-1]=' ';
                        	contaletra--;

        	}
            	if(evento.key.code==sf::Keyboard::W&&contaletra<5){
                    	nome[contaletra]='W';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::Q&&contaletra<5){
                    	nome[contaletra]='Q';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::E&&contaletra<5){
                    	nome[contaletra]='E';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::R&&contaletra<5){
                    	nome[contaletra]='R';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::T&&contaletra<5){
                    	nome[contaletra]='T';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::Y&&contaletra<5){
                    	nome[contaletra]='Y';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::U&&contaletra<5){
                    	nome[contaletra]='U';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::I&&contaletra<5){
                    	nome[contaletra]='I';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::O&&contaletra<5){
                    	nome[contaletra]='O';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::P&&contaletra<5){
                    	nome[contaletra]='P';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::A&&contaletra<5){
                    	nome[contaletra]='A';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::S&&contaletra<5){
                    	nome[contaletra]='S';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::D&&contaletra<5){
                    	nome[contaletra]='D';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::F&&contaletra<5){
                    	nome[contaletra]='F';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::G&&contaletra<5){
                    	nome[contaletra]='G';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::H&&contaletra<5){
                    	nome[contaletra]='H';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::J&&contaletra<5){
                    	nome[contaletra]='J';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::K&&contaletra<5){
                    	nome[contaletra]='K';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::L&&contaletra<5){
                    	nome[contaletra]='L';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::Z&&contaletra<5){
                    	nome[contaletra]='Z';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::X&&contaletra<5){
                    	nome[contaletra]='X';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::C&&contaletra<5){
                    	nome[contaletra]='C';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::V&&contaletra<5){
                    	nome[contaletra]='V';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::B&&contaletra<5){
                    	nome[contaletra]='B';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::N&&contaletra<5){
                    	nome[contaletra]='N';
                    	contaletra++;

        	}if(evento.key.code==sf::Keyboard::M&&contaletra<5){
                    	nome[contaletra]='M';
                    	contaletra++;

        	}

    	}
    	}



    	janela.draw(telarecorde);
    	std::string printanome = nome;
    	textoArcade4.setString(printanome);
    	textoArcade4.setLetterSpacing(2);
    	textoArcade4.setCharacterSize(29);
    	textoArcade4.setFillColor(sf::Color::White);
    	textoArcade4.setPosition(sf::Vector2f(488,330));
    	janela.draw(textoArcade4);
    	janela.display();

	}



}
diga_quem_venceu:
//printf("\n%s",nome);

if(quem_ganhou==1){ //entro nos comandos de execução da sprite deorrta


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
            	else if (evento.type==sf::Event::KeyReleased){

                	if(evento.key.code==sf::Keyboard::Enter){
                        	musicadoganhoumaquina.stop(); // paro o loop musical do fim de jogo
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
else if(quem_ganhou==2){ //entro nos comandos de execução da sprite deorrta


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
        	else if (evento.type==sf::Event::KeyReleased){

            	if(evento.key.code==sf::Keyboard::Enter){
                    	musicadoperdeumaquina.stop(); // paro o loop musical do fim de jogo
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
	fclose(recorde);
	fclose(recordista);
	return 0;
}























