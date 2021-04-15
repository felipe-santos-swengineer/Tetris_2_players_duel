#include <SFML/Graphics.hpp>
#include <iostream>



double x=190, y=108;
double montagemx, montagemy;


typedef struct p{
    double px;
    double py;
} Coord; //vai guardar os valores de x e y de cada quadrado q vai montar a pe�a

Coord matrizdevalxy[10][20];

int main(){
    int i, j;

    //setando valores das posicoes x e y de todas as pe�as
    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            matrizdevalxy[i][j].px=(i*20.8)+190.0; //i multiplica pois � a coluna ; 20.8 px � o recuo da pe�a no eixo x quando pressionado (largura)
            matrizdevalxy[i][j].py=(j*20.7)+108.0; //j multiplica pois � a linha ; 20.7 px � o recuo da pe�a no eixo y quando pressionado  (altura)
        }
    }

    bool matrizPlayer[10][20];
    //matriz do jogo come�a com valores false em todas as posi��es;
    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            matrizPlayer[i][j]=false;
        }
    }

    matrizPlayer[0][1]=true;
    matrizPlayer[1][0]=true;
    matrizPlayer[1][1]=true;
    matrizPlayer[2][1]=true;

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


        janela.clear(sf::Color(255,255,255));
        janela.draw(background);

        //la�o for verifica toda a matriz em busca de um true para imprimir. se for true, ele imprime a figura com a matriz de valores
        for(i=0;i<10;i++){
            for(j=0;j<20;j++){
                if(matrizPlayer[i][j]){
                  spriteStatico.setPosition(sf::Vector2f(matrizdevalxy[i][j].px, matrizdevalxy[i][j].py));
                    janela.draw(spriteStatico);

                }
            }
        }



        janela.draw(sprite1);
        janela.display();
    }

    return 0;
}


