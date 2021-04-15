#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef struct p{
    double px;
    double py;
} Coord; //vai guardar os valores de x e y de cada quadrado q vai montar a peça

typedef struct p2{
    int px;
    int py;
} Coord2;
Coord matrizdevalxy[10][20];


//############################################### COMEÇO DO LOOP #############################################################################
int main(){
    srand(time(NULL));
    int aleatorio;

    //****************** PADRAO DE PEÇAS ( 9 TIPOS DE PEÇAS DIFERENTES )**********************************************************
    //matriz em que cada coluna representa uma peça e as 4 linhas estao ponto x e ponto y da peça.
    Coord2 coordenadasdaspecas [9][4];
    //01 barra
    coordenadasdaspecas[0][0].px=0;
    coordenadasdaspecas[0][0].py=0;
    coordenadasdaspecas[0][1].px=0;
    coordenadasdaspecas[0][1].py=1;
    coordenadasdaspecas[0][2].px=0;
    coordenadasdaspecas[0][2].py=2;
    coordenadasdaspecas[0][3].px=0;
    coordenadasdaspecas[0][3].py=3;
    //02 N invertido
    coordenadasdaspecas[1][0].px=0;
    coordenadasdaspecas[1][0].py=0;
    coordenadasdaspecas[1][1].px=0;
    coordenadasdaspecas[1][1].py=1;
    coordenadasdaspecas[1][2].px=1;
    coordenadasdaspecas[1][2].py=1;
    coordenadasdaspecas[1][3].px=1;
    coordenadasdaspecas[1][3].py=2;
    //03 quadrado
    coordenadasdaspecas[2][0].px=0;
    coordenadasdaspecas[2][0].py=0;
    coordenadasdaspecas[2][1].px=1;
    coordenadasdaspecas[2][1].py=0;
    coordenadasdaspecas[2][2].px=0;
    coordenadasdaspecas[2][2].py=1;
    coordenadasdaspecas[2][3].px=1;
    coordenadasdaspecas[2][3].py=1;
    //04 N comum
    coordenadasdaspecas[3][0].px=0;
    coordenadasdaspecas[3][0].py=1;
    coordenadasdaspecas[3][1].px=0;
    coordenadasdaspecas[3][1].py=2;
    coordenadasdaspecas[3][2].px=1;
    coordenadasdaspecas[3][2].py=0;
    coordenadasdaspecas[3][3].px=1;
    coordenadasdaspecas[3][3].py=1;
    //05 Z comum
    coordenadasdaspecas[4][0].px=0;
    coordenadasdaspecas[4][0].py=0;
    coordenadasdaspecas[4][1].px=1;
    coordenadasdaspecas[4][1].py=0;
    coordenadasdaspecas[4][2].px=1;
    coordenadasdaspecas[4][2].py=1;
    coordenadasdaspecas[4][3].px=2;
    coordenadasdaspecas[4][3].py=1;
    //06 S
    coordenadasdaspecas[5][0].px=0;
    coordenadasdaspecas[5][0].py=1;
    coordenadasdaspecas[5][1].px=1;
    coordenadasdaspecas[5][1].py=1;
    coordenadasdaspecas[5][2].px=1;
    coordenadasdaspecas[5][2].py=0;
    coordenadasdaspecas[5][3].px=2;
    coordenadasdaspecas[5][3].py=0;
    //07 T
    coordenadasdaspecas[6][0].px=0;
    coordenadasdaspecas[6][0].py=0;
    coordenadasdaspecas[6][1].px=1;
    coordenadasdaspecas[6][1].py=0;
    coordenadasdaspecas[6][2].px=1;
    coordenadasdaspecas[6][2].py=1;
    coordenadasdaspecas[6][3].px=2;
    coordenadasdaspecas[6][3].py=0;
    //08 L comum
    coordenadasdaspecas[7][0].px=0;
    coordenadasdaspecas[7][0].py=0;
    coordenadasdaspecas[7][1].px=0;
    coordenadasdaspecas[7][1].py=1;
    coordenadasdaspecas[7][2].px=0;
    coordenadasdaspecas[7][2].py=2;
    coordenadasdaspecas[7][3].px=1;
    coordenadasdaspecas[7][3].py=2;
    //09 L invertido
    coordenadasdaspecas[8][0].px=1;
    coordenadasdaspecas[8][0].py=0;
    coordenadasdaspecas[8][1].px=1;
    coordenadasdaspecas[8][1].py=1;
    coordenadasdaspecas[8][2].px=1;
    coordenadasdaspecas[8][2].py=2;
    coordenadasdaspecas[8][3].px=0;
    coordenadasdaspecas[8][3].py=2;

    //****************************************************************************




    //******************** DECLARAÇAO DE VARIAVEIS ********************************************************
    int i, j, mov_y=0, mov_x=0; //mov_y e mov_x é usado para incrementar a peça na matriz principal, no eix x e eixo y
    int delay=0; // serve para dar um delay de 3 segundos antes da peça descer

    //****************************************************************************




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

    sf::Texture texturaStatica;
    texturaStatica.loadFromFile("img/svg2.png");

    aleatorio=rand()%9;

//############################################### COMEÇO DO LOOP #############################################################################
while (janela.isOpen()){

    bool matrizPlayer[10][20];

    //******************** SETA FALSE EM TODAS AS POSICOES DA MATRIZ PRINCIPAL *****************************
    //matriz do jogo começa com valores false em todas as posições;
    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            matrizPlayer[i][j]=false;
        }
    }

    //****************************************************************************




    //********************** SETA VALORES TRUE DE ACORDO CO A MATRIZ DAS PEÇAS ************************************
    //coordenadas passadas para matrizplayer de booleanos atravez da matriz coodenadas pecas px e py
    //esse laço for é feito dentro do loop principal, e pode ser incremeentado com valores mov_x e mov_y para os movimentos
    //matriz player é a matriz de booleanos principal, e esta sendo passado como parametro a coordenadas das peças
    //a coluna é gerada no rand() aleatorio, e a posicao de x e y q existe na struct e passada para a matriz principal.

    for(j=0;j<4;j++){
        matrizPlayer[coordenadasdaspecas[aleatorio][j].px+mov_x][coordenadasdaspecas[aleatorio][j].py+mov_y]=true;//mov_y e mov_x usados para mover a peca
    }

    //****************************************************************************




    sf::Sprite background;
    background.setTexture(texturabg);
    background.setPosition(sf::Vector2f(0,0));

    sf::Sprite spriteStatico;
    spriteStatico.setTexture(texturaStatica);




        //****************************** EVENTOS DE PRESSIONADO DE BOTOES **********************************************
        sf::Event evento;
        while (janela.pollEvent(evento)){
            if(evento.type==sf::Event::Closed){
            janela.close();
        } else if (evento.type==sf::Event::KeyPressed){

            if (evento.key.code==sf::Keyboard::Right){
                mov_x++;
            }
            if (evento.key.code==sf::Keyboard::Left){
                mov_x--;
            }
            if(evento.key.code==sf::Keyboard::Up){
                mov_y--;
            }
            if(evento.key.code==sf::Keyboard::Down){
                mov_y++;

            }
        }
        }
        //****************************************************************************




        janela.clear(sf::Color(255,255,255));
        janela.draw(background);




        //************************* IMPRIME OS TRUE DA MATRIZ PRINCIPAL *********************************
        //laço for verifica toda a matriz em busca de um true para imprimir.
        //se for true, ele imprime a figura com a matriz de valores na mesma posicao
        for(i=0;i<10;i++){
            for(j=0;j<20;j++){
                if(matrizPlayer[i][j]){
                  spriteStatico.setPosition(sf::Vector2f(matrizdevalxy[i][j].px, matrizdevalxy[i][j].py));
                    janela.draw(spriteStatico);

                }
            }
        }
        //****************************************************************************





        //***************************** TIME DO JOGO ***********************************************

        if(clock.getElapsedTime().asSeconds()>0.4){
           delay++;
           if(delay>=3&&mov_y<=17){
            mov_y++;
           }
            clock.restart();
        }
        //parte do clock do jogo;
        //funçao retoorna o valor em segundos da execuçao, e de acordo com a
        //comparacao se define a velocidade qque a peça cai,
        // usando o incremento mov_y

        //****************************************************************************

        janela.display();
    }
//############################################### FIM DO LOOP #############################################################################

    return 0;
}


