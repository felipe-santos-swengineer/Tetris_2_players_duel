#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


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
//############################################### INT MAIN #############################################################################
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
    int pontos=0, cont=0;
    int j2=0,i2=0;
    int girar=1;
    Coord2 coordenadasdaspecas [23][4];

    //****************************************************************************



    //*************** MATRIZ GUARDA O CONJUNTO DE 4 ROTACOES POR PEÇA *******************
    int matrizRotacao[9][4]={9,0,9,0,
                            10,1,10,1,
                            2,2,2,2,
                            11,3,11,3,
                            12,4,12,4,
                            13,5,13,5,
                            14,17,20,6,
                            15,18,21,7,
                            22,19,16,8
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

    sf::Texture texturabg;
    texturabg.loadFromFile("img/background.png");

    sf::Texture textura2;
    textura2.loadFromFile("img/svg4.png");

    aleatorioCor=rand()%5; // seta um valor aleatorio para carregar o arquivo de cor diferente a cada peça
    sf::Texture texturapeca;
    texturapeca.loadFromFile(cores[aleatorioCor]);


    sf::Texture texturapecaEstatica;

    int aleatorioPecaEmUso;
    aleatorioPecaEmUso=rand()%9;
    aleatorioPeca=aleatorioPecaEmUso;


    //int aleatorioPecaEmUso=7;

    int matrizdecodcoresparamatrizsecund[10][20];// serve para guardar o codigo de cores na posicao
    bool matrizPlayer[10][20];
    bool matrizPlayerEstatico[10][20];
    zeramatrizsecundaria(matrizPlayerEstatico);
//############################################### COMEÇO DO LOOP #############################################################################

while (janela.isOpen()){

    sf::Sprite background;
    background.setTexture(texturabg);
    background.setPosition(sf::Vector2f(0,0));

    sf::Sprite spriteMov; //sprite mov se movimenta atravez da matriz principal
    spriteMov.setTexture(texturapeca);

    sf::Sprite spriteEst; //spriteest copia a posicao de spritemov para a matriz secondaria
    spriteEst.setTexture(texturapecaEstatica);




    zeramatrizprincipal(matrizPlayer); //chama funçao que zera a matriz/ ele começa com false em todas


        //****************************** EVENTOS DE PRESSIONADO DE BOTOES **********************************************
        sf::Event evento;
        while (janela.pollEvent(evento)){
            if(evento.type==sf::Event::Closed){
            janela.close();
        } else if (evento.type==sf::Event::KeyPressed){

        if(mov_y>0){
            if(evento.key.code==sf::Keyboard::Up){


                //aleatorioPeca=0;
                //mov_y--;
                //printf("mov_y: %d\n", mov_y);
                //printf("aleatorio: %d\n", aleatorioPeca);
                printf("girar: %d\n", girar);
                //printf("pecauso y: %d\n\n", aleatorioPecaEmUso);
                girar++;
                if(girar>3){
                    girar=0;
                };

            }
        }

        if(mov_x<=8-limitedapeca_x){
            if (evento.key.code==sf::Keyboard::Right){
                mov_x++;
                //printf("mov_x: %d\n", mov_x);
                //printf("limite x: %d\n", limitedapeca_x);
            }
        }

        if(mov_x>0){
            if (evento.key.code==sf::Keyboard::Left){
                mov_x--;
                //printf("mov_x: %d\n", mov_x);
                //printf("limite x: %d\n", limitedapeca_x);
            }
        }

        if(mov_y<=18-limitedapeca_y){
            if(evento.key.code==sf::Keyboard::Down){
                mov_y++;
                //printf("mov_y: %d\n", mov_y);
                //printf("limite y: %d\n", limitedapeca_y);
            }
        }
        }
        }
        aleatorioPeca=matrizRotacao[aleatorioPecaEmUso][girar];
        //****************************************************************************


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


    }
        //******************* PARTE DO FELIPE ***************************
        i=19;
         while(i>0){

                for(j=0;j<10;j++){//verifica se a linha esta prenchida, na ordem de baixo pra cima;
                    if(matrizPlayerEstatico[j][i])
                    cont++;
                }

            if(cont==10){//quando cont=10 significa que está prenchida
                pontos+=10; // o jogador ganha pontuação
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
                printf("%d pontos\n",pontos);

                for(i2=i-1;i2>0;i2--){ // esses 2 laços tranferem todas as linhas acima da linha apagada pra baixo;
                    for(j2=0;j2<10;j2++){ //m
                        if(matrizPlayerEstatico[j2][i2]==true&&i2>0){ //impede que na linha zero, ele pegue o lixo de memoria, pois não existe nada acima da linha 0;
                        matrizPlayerEstatico[j2][i2+1]=matrizPlayerEstatico[j2][i2];
                        matrizdecodcoresparamatrizsecund[j2][i2+1]=matrizdecodcoresparamatrizsecund[j2][i2];
                        matrizPlayerEstatico[j2][i2]=false;
                        }
                    }
                }

            }
            else cont=0;

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




        //***************************** TIME DO JOGO ***********************************************


        //parte do clock do jogo;
        //funçao retoorna o valor em segundos da execuçao, e de acordo com a
        //comparacao se define a velocidade qque a peça cai,
        // usando o incremento mov_y

        if(clock.getElapsedTime().asSeconds()>0.4){
           if(delay){
            delay--;
           }

           if(delay==0 && mov_y<=18-limitedapeca_y){ // limite de incrementaçao ate em baixo vairoa com o tamanho da peça (limitepeca)
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

                //////////////////////////////////////////////////
                //#################  PRODUZ OUTRA COR E OUTRO FORMATO #####################
                if(delay==0){
                    aleatorioCor=rand()%5; // seta um valor aleatorio para carregar o arquivo de cor diferente a cada peça
                    aleatorioPecaEmUso=rand()%9;
                    //aleatorioPecaEmUso=0;
                    aleatorioPeca=aleatorioPecaEmUso;
                    //aleatorioPeca=3;
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



        //****************************************************************************


        janela.display();
    }
//############################################### FIM DO LOOP #############################################################################

    return 0;
}









