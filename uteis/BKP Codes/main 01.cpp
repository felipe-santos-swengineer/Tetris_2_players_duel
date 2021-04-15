#include <SFML/Graphics.hpp>
#include <iostream>

double x=190, y=108;

int main(){
    sf::RenderWindow janela(sf::VideoMode(1050, 591), "My janela");

    sf::Texture texturabg;
    texturabg.loadFromFile("background.png");

    sf::Texture textura2;
    textura2.loadFromFile("svg1.png");

    while (janela.isOpen()){
        sf::Sprite background;
        background.setTexture(texturabg);
        background.setPosition(sf::Vector2f(0,0));

        sf::Sprite sprite1;
        sprite1.setTexture(textura2);
        sprite1.move(sf::Vector2f(x,y));

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
        janela.draw(sprite1);

        janela.display();
    }

    return 0;
}


