#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
double x=190, y=108;
double montagemx, montagemy;


typedef struct p{
    double px;
    double py;
} QdrPecPos; //vai guardar os valores de x e y de cada quadrado q vai montar a peça

QdrPecPos matrizdevaloresxy[10][20];

int main(){
    int i, j;

    //setando valores das posicoes x e y de todas as peças
    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            matrizdevaloresxy[i][j].px=(i*20.8)+190.0;
            matrizdevaloresxy[i][j].py=(i*20.7)+108.0;
        }
    }
   // std::printf("px: %lf", );
    std::cout<<"px " <<matrizdevaloresxy[0][0].px<<std::endl;
    std::cout<<"py " <<matrizdevaloresxy[0][0].py<<std::endl;

    bool matrizPlayer[10][20];
    //matriz do jogo começa com valores false em todas as posições;
    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            matrizPlayer[i][j]=false;
        }
    }

    QdrPecPos peca1[4];
    peca1[0].py=matrizdevaloresxy[0][0].py;
    peca1[0].py=matrizdevaloresxy[0][0].px;
    peca1[1].py=matrizdevaloresxy[1][0].py;
    peca1[1].px=matrizdevaloresxy[1][0].px;
    peca1[2].py=matrizdevaloresxy[2][0].py;
    peca1[2].px=matrizdevaloresxy[2][0].px;
    peca1[3].py=matrizdevaloresxy[3][0].py;
    peca1[3].px=matrizdevaloresxy[3][0].px;


    sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo");

    sf::Texture texturabg;
    texturabg.loadFromFile("img/background.png");

    sf::Texture textura2;
    textura2.loadFromFile("img/svg4.png");

    sf::Texture texturaStatica;
    texturaStatica.loadFromFile("img/svg1.png");

    while (janela.isOpen()){
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
            }
            if (evento.key.code==sf::Keyboard::Left){
                x-=20.8;
                std::cout<<x<<std::endl;
            }
            if(evento.key.code==sf::Keyboard::Up){
                y-=20.7;
                std::cout<<y<<std::endl;
            }
            if(evento.key.code==sf::Keyboard::Down){
                y+=20.7;
                std::cout<<y<<std::endl;
            }
        }
        }

        //imprime os membros da matriz que sao true;
        janela.clear(sf::Color(255,255,255));
        janela.draw(background);
        /*
        for(i=0;i<4;i++){
            montagemx = peca1[i].px;
            montagemy = peca1[i].py;
            spriteStatico.setPosition(sf::Vector2f(montagemx,montagemy));
            janela.draw(spriteStatico);
        }*/

        spriteStatico.setPosition(sf::Vector2f(matrizdevaloresxy[1][0].px,matrizdevaloresxy[0][0].py));
        janela.draw(spriteStatico);

        janela.draw(sprite1);
        janela.display();
    }

    return 0;
}


