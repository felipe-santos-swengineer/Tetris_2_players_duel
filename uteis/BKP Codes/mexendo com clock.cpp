#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    sf::Time t1 = sf::seconds(0.1);
    float tempo;
    std::cout<<"Muy buenos vídeos, el mejor curso de sfml que he visto! Una pregunta. No hay que liberar con delete en el destructor??﻿"<<std::endl;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

       // std::cout<<clock.getElapsedTime().asSeconds()<<std::endl;
       tempo = clock.getElapsedTime().asSeconds();
        if(tempo>1){
            std::cout<<"teste tempo﻿"<<std::endl;
            clock.restart();
        }
        //

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
