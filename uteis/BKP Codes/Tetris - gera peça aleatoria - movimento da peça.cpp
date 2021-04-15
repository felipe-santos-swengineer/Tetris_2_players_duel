#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double x=190, y=108;

typedef struct p{
    double px;
    double py;
} Coord; //vai guardar os valores de x e y de cada quadrado q vai montar a peça

typedef struct p2{
    int px;
    int py;
} Coord2;
Coord matrizdevalxy[10][20];



int main(){
    srand(time(NULL));
    int aleatorio;
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


    int i, j, aux=0, aux2=0; //aux e aux2 é usado para incrementar a peça na matriz principal, no eix x e eixo y
    int comeco=0;

    sf::Clock clock;

    //setando valores das posicoes x e y de todas as peças
    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            matrizdevalxy[i][j].px=(i*20.8)+190.0; //i multiplica pois é a coluna ; 20.8 px é o recuo da peça no eixo x quando pressionado (largura)
            matrizdevalxy[i][j].py=(j*20.7)+108.0; //j multiplica pois é a linha ; 20.7 px é o recuo da peça no eixo y quando pressionado  (altura)
        }
    }



    sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo");

    sf::Texture texturabg;
    texturabg.loadFromFile("img/background.png");

    sf::Texture textura2;
    textura2.loadFromFile("img/svg4.png");

    sf::Texture texturaStatica;
    texturaStatica.loadFromFile("img/svg1.png");

    aleatorio=rand()%9;

    while (janela.isOpen()){

    bool matrizPlayer[10][20];
    //matriz do jogo começa com valores false em todas as posições;
    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            matrizPlayer[i][j]=false;
        }
    }


        for(j=0;j<4;j++){ //coordenadas passadas para matrizplayer de booleanos atravez da matriz coodenadas pecas px e py
                matrizPlayer[coordenadasdaspecas[aleatorio][j].px+aux2][coordenadasdaspecas[aleatorio][j].py+aux]=true;//aux e aux2 usados para mover a peca
            }

        sf::Sprite background;
        background.setTexture(texturabg);
        background.setPosition(sf::Vector2f(0,0));

        sf::Sprite sprite1;
        sprite1.setTexture(textura2);
        sprite1.move(sf::Vector2f(x,y));

        sf::Sprite spriteStatico;
        spriteStatico.setTexture(texturaStatica);


        sf::Event evento;
        while (janela.pollEvent(evento)){
            if(evento.type==sf::Event::Closed){
            janela.close();
        } else if (evento.type==sf::Event::KeyPressed){

            if (evento.key.code==sf::Keyboard::Right){
                x+=20.8;
                std::cout<<x<<std::endl;
                aux2++;
            }
            if (evento.key.code==sf::Keyboard::Left){
                x-=20.8;
                std::cout<<x<<std::endl;
                aux2--;
            }
            if(evento.key.code==sf::Keyboard::Up){
                y-=20.7;
                std::cout<<y<<std::endl;
                aux--;
            }
            if(evento.key.code==sf::Keyboard::Down){
                y+=20.7;
                std::cout<<y<<std::endl;
                aux++;

            }
        }
        }


        janela.clear(sf::Color(255,255,255));
        janela.draw(background);

        //laço for verifica toda a matriz em busca de um true para imprimir. se for true, ele imprime a figura com a matriz de valores
        for(i=0;i<10;i++){
            for(j=0;j<20;j++){
                if(matrizPlayer[i][j]){
                  spriteStatico.setPosition(sf::Vector2f(matrizdevalxy[i][j].px, matrizdevalxy[i][j].py));
                    janela.draw(spriteStatico);

                }
            }
        }



        if(clock.getElapsedTime().asSeconds()>0.4){
           comeco++;
           if(comeco>=3&&aux<=17){
            aux++;
           }
            clock.restart();
        }

        //janela.draw(sprite1);
        janela.display();
    }

    return 0;
}


