/// arquivo so com as telas do jogo

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <SFML/Audio.hpp>

sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo");
//janela.setFramerateLimit(10);
bool primeiroJogo=true;
void TelaMenuPrincipal();
void TelaJogo();
void TelaRanking();
void TelaJog1();
void TelaJog2();
void TelaRecorde();
void TelaVencedor();
void TelaMesmosJogadores();

void TelaMesmosJogadores(){
    sf::Texture textura;
   textura.loadFromFile("img/MesmosJogadores.png");
   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);
   FILE *file;


   while(janela.isOpen()){
    sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){
                TelaJogo();
            }
            if(evento.key.code==sf::Keyboard::Escape){
                file=std::fopen("Players.txt", "w");//se for outros jogadores, ele subscreve o arquivo em branco
                std::fclose(file);
                TelaJog1();
                }

            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.display();
   }

}










void TelaRecorde(){
   sf::Texture textura;
   textura.loadFromFile("img/Recorde.png");
   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

   while(janela.isOpen()){
    sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){
                TelaVencedor();
                }


            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.display();
   }


}

void TelaMenuPrincipal(){
   sf::Texture textura;
   textura.loadFromFile("img/teladomenu.png");
   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

   while(janela.isOpen()){
    sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
                if(evento.key.code==sf::Keyboard::R){
                    TelaRanking();
                }
                if(evento.key.code==sf::Keyboard::Enter){
                        if(primeiroJogo){
                            primeiroJogo=false;
                           TelaJog1();
                        } else {
                            TelaMesmosJogadores();

                        }

                }
                if(evento.key.code==sf::Keyboard::Escape){
                    janela.close();
                }

            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.display();
   }


}

void TelaRanking(){
    sf::Texture textura;
   textura.loadFromFile("img/Ranking.png");

   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

   std::string nomesRecordes[3][4];//guarda os "nomes" que serao mostrados; tem 4 nomes em cada uma das 3 linhas do ranking
   char n1[10], n2[10], n3[10], n4[10];//variaveis provisoria, pois FSCANF nao atribui diretamente na posiçao da matriz a string, tem que ter esse intermediario


   FILE *file1=std::fopen("Ranking_1_Lugar.txt","r");
std::fscanf(file1,"%s%s%s%s\n",n1,n2,n3,n4);
   nomesRecordes[0][0]=n1;
   nomesRecordes[0][1]=n2;
   nomesRecordes[0][2]=n3;
   nomesRecordes[0][3]=n4;
   fclose(file1);

   FILE *file2=std::fopen("Ranking_2_Lugar.txt","r");
std::fscanf(file2,"%s%s%s%s\n",n1,n2,n3,n4);
   nomesRecordes[1][0]=n1;
   nomesRecordes[1][1]=n2;
   nomesRecordes[1][2]=n3;
   nomesRecordes[1][3]=n4;
   fclose(file2);

   FILE *file3=std::fopen("Ranking_3_Lugar.txt","r");
std::fscanf(file3,"%s%s%s%s\n",n1,n2,n3,n4);
   nomesRecordes[2][0]=n1;
   nomesRecordes[2][1]=n2;
   nomesRecordes[2][2]=n3;
   nomesRecordes[2][3]=n4;
   fclose(file3);


   sf::Font fonte;
   fonte.loadFromFile("Fontes/ARCADECLASSIC.TTF");
   sf::Text nome1;
   nome1.setFont(fonte);
   nome1.setString(nomesRecordes[0][0]);
   nome1.setCharacterSize(43);
   nome1.setFillColor(sf::Color::Green);
   nome1.setPosition(278,228);

   sf::Text nome2;
   nome2.setFont(fonte);
   nome2.setString(nomesRecordes[0][1]);
   nome2.setCharacterSize(43);
   nome2.setFillColor(sf::Color::Green);
   nome2.setPosition(460,228);

   sf::Text nome3;
   nome3.setFont(fonte);
   nome3.setString(nomesRecordes[0][2]);
   nome3.setCharacterSize(43);
   nome3.setFillColor(sf::Color::Green);
   nome3.setPosition(630,228);

   sf::Text nome4;
   nome4.setFont(fonte);
   nome4.setString(nomesRecordes[0][3]);
   nome4.setCharacterSize(43);
   nome4.setFillColor(sf::Color::Green);
   nome4.setPosition(709,228);
//***************************************** 01
   sf::Text nome5;
   nome5.setFont(fonte);
   nome5.setString(nomesRecordes[1][0]);
   nome5.setCharacterSize(43);
   nome5.setFillColor(sf::Color::Green);
   nome5.setPosition(278,292);

   sf::Text nome6;
   nome6.setFont(fonte);
   nome6.setString(nomesRecordes[1][1]);
   nome6.setCharacterSize(43);
   nome6.setFillColor(sf::Color::Green);
   nome6.setPosition(460,292);

   sf::Text nome7;
   nome7.setFont(fonte);
   nome7.setString(nomesRecordes[1][2]);
   nome7.setCharacterSize(43);
   nome7.setFillColor(sf::Color::Green);
   nome7.setPosition(630,292);

   sf::Text nome8;
   nome8.setFont(fonte);
   nome8.setString(nomesRecordes[1][3]);
   nome8.setCharacterSize(43);
   nome8.setFillColor(sf::Color::Green);
   nome8.setPosition(709,292);
   //***************************************** 02

   sf::Text nome9;
   nome9.setFont(fonte);
   nome9.setString(nomesRecordes[2][0]);
   nome9.setCharacterSize(43);
   nome9.setFillColor(sf::Color::Green);
   nome9.setPosition(278,356);

   sf::Text nome10;
   nome10.setFont(fonte);
   nome10.setString(nomesRecordes[2][1]);
   nome10.setCharacterSize(43);
   nome10.setFillColor(sf::Color::Green);
   nome10.setPosition(460,356);

   sf::Text nome11;
   nome11.setFont(fonte);
   nome11.setString(nomesRecordes[2][2]);
   nome11.setCharacterSize(43);
   nome11.setFillColor(sf::Color::Green);
   nome11.setPosition(630,356);

   sf::Text nome12;
   nome12.setFont(fonte);
   nome12.setString(nomesRecordes[2][3]);
   nome12.setCharacterSize(43);
   nome12.setFillColor(sf::Color::Green);
   nome12.setPosition(709,356);

   while(janela.isOpen()){
    sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){

                TelaMenuPrincipal();
                }

            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.draw(nome1); janela.draw(nome2); janela.draw(nome3); janela.draw(nome4); janela.draw(nome5); janela.draw(nome6);
    janela.draw(nome7); janela.draw(nome8); janela.draw(nome9); janela.draw(nome10); janela.draw(nome11); janela.draw(nome12);
    janela.display();
   }

}








//***************************************************************************************************************
void TelaVencedor(){
     sf::Texture textura;
   //textura.loadFromFile("img/Conferir/vencedor conferir.png");
   textura.loadFromFile("img/Vencedor.png");
   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

    sf::Font fonte;
   fonte.loadFromFile("Fontes/ARCADECLASSIC.TTF");

   char n1[10], n2[10];

   FILE *file1=std::fopen("VencedorPartidaAtual.txt", "r");
   std::fscanf(file1,"%s%s\n", n1, n2);

   sf::Text nome1;
   nome1.setFont(fonte);
   nome1.setString(n1);
   nome1.setCharacterSize(56);
   nome1.setFillColor(sf::Color::Blue);
   nome1.setPosition(449.f,174.f);
   //nome1.setOrigin(sf::Vector2f(25.f,25.f));

   sf::Text nome2;
   nome2.setFont(fonte);
   nome2.setString(n2);
   nome2.setCharacterSize(47);
   nome2.setFillColor(sf::Color::Black);
   nome2.setPosition(465,225);

   while(janela.isOpen()){
    sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){
                   TelaMenuPrincipal();
                }

            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.draw(nome1);
    janela.draw(nome2);
    janela.display();
   }

}





void TelaJog2(){
    sf::Texture textura;
   textura.loadFromFile("img/Jog2Nome.png");
   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

    int i;
    char nomejog[7]="      ";
    int posAtualCaractere=0;
    FILE *file=std::fopen("Players.txt", "a");

    sf::Event evento;
    sf::Font fonte;
    fonte.loadFromFile("fontes/MotionControl-Bold.ttf");
    sf::Text nomJog1;

   nomJog1.setFont(fonte);
   nomJog1.setCharacterSize(30);
   nomJog1.setFillColor(sf::Color(39,84,92));
   nomJog1.setPosition(486,319);

    while(janela.isOpen()){
        nomJog1.setString(nomejog);

    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){
                std::fprintf(file,"%s ", nomejog);
                std::fclose(file);
               TelaJogo();
            }
            //***************************************
            if(posAtualCaractere){//o bakspace so funciona qdo a posicao for true, ou seja, 1 ou mais;
                if(evento.key.code==sf::Keyboard::Backspace){
                        nomejog[posAtualCaractere-1]=' ';//-1 por causa do \0, senao deleta ele
                        posAtualCaractere--;
                }
            }

                if (posAtualCaractere!=6){
                    if(evento.key.code==sf::Keyboard::A){
                        nomejog[posAtualCaractere]='A';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::B){
                        nomejog[posAtualCaractere]='B';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::C){
                        nomejog[posAtualCaractere]='C';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::D){
                        nomejog[posAtualCaractere]='D';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::E){
                        nomejog[posAtualCaractere]='E';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::F){
                        nomejog[posAtualCaractere]='F';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::G){
                        nomejog[posAtualCaractere]='G';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::H){
                        nomejog[posAtualCaractere]='H';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::I){
                        nomejog[posAtualCaractere]='I';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::J){
                        nomejog[posAtualCaractere]='J';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::K){
                        nomejog[posAtualCaractere]='K';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::L){
                        nomejog[posAtualCaractere]='L';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::M){
                        nomejog[posAtualCaractere]='M';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::N){
                        nomejog[posAtualCaractere]='N';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::O){
                        nomejog[posAtualCaractere]='O';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::P){
                       nomejog[posAtualCaractere]='P';
                       posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::Q){
                        nomejog[posAtualCaractere]='Q';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::R){
                        nomejog[posAtualCaractere]='R';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::S){
                        nomejog[posAtualCaractere]='S';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::T){
                        nomejog[posAtualCaractere]='T';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::U){
                        nomejog[posAtualCaractere]='U';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::V){
                        nomejog[posAtualCaractere]='V';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::W){
                        nomejog[posAtualCaractere]='W';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::X){
                        nomejog[posAtualCaractere]='X';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::Y){
                        nomejog[posAtualCaractere]='Y';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::Z){
                        nomejog[posAtualCaractere]='Z';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::Hyphen){
                        nomejog[posAtualCaractere]='-';
                        posAtualCaractere++;
                    }
                }
            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.draw(nomJog1);
    janela.display();
   }


}




void TelaJog1(){
    sf::Texture textura;
   textura.loadFromFile("img/Jog1Nome.png");
   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

    int i;
    char nomejog[7]="      ";
    int posAtualCaractere=0;
    FILE *file=std::fopen("Players.txt", "a");

    sf::Event evento;
    sf::Font fonte;
    fonte.loadFromFile("fontes/MotionControl-Bold.ttf");
    sf::Text nomJog1;

   nomJog1.setFont(fonte);
   nomJog1.setCharacterSize(30);
   nomJog1.setFillColor(sf::Color(39,84,92));
   nomJog1.setPosition(486,319);

    while(janela.isOpen()){
        nomJog1.setString(nomejog);

    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){
                std::fprintf(file,"%s ", nomejog);
                std::fclose(file);
               TelaJog2();
            }
            //***************************************

            if(posAtualCaractere){//o bakspace so funciona qdo a posicao for true, ou seja, 1 ou mais;
                if(evento.key.code==sf::Keyboard::Backspace){
                        nomejog[posAtualCaractere-1]=' ';//-1 por causa do \0, senao deleta ele
                        posAtualCaractere--;
                }
            }

                if (posAtualCaractere!=6){
                    if(evento.key.code==sf::Keyboard::A){
                        nomejog[posAtualCaractere]='A';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::B){
                        nomejog[posAtualCaractere]='B';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::C){
                        nomejog[posAtualCaractere]='C';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::D){
                        nomejog[posAtualCaractere]='D';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::E){
                        nomejog[posAtualCaractere]='E';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::F){
                        nomejog[posAtualCaractere]='F';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::G){
                        nomejog[posAtualCaractere]='G';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::H){
                        nomejog[posAtualCaractere]='H';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::I){
                        nomejog[posAtualCaractere]='I';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::J){
                        nomejog[posAtualCaractere]='J';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::K){
                        nomejog[posAtualCaractere]='K';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::L){
                        nomejog[posAtualCaractere]='L';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::M){
                        nomejog[posAtualCaractere]='M';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::N){
                        nomejog[posAtualCaractere]='N';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::O){
                        nomejog[posAtualCaractere]='O';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::P){
                       nomejog[posAtualCaractere]='P';
                       posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::Q){
                        nomejog[posAtualCaractere]='Q';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::R){
                        nomejog[posAtualCaractere]='R';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::S){
                        nomejog[posAtualCaractere]='S';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::T){
                        nomejog[posAtualCaractere]='T';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::U){
                        nomejog[posAtualCaractere]='U';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::V){
                        nomejog[posAtualCaractere]='V';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::W){
                        nomejog[posAtualCaractere]='W';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::X){
                        nomejog[posAtualCaractere]='X';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::Y){
                        nomejog[posAtualCaractere]='Y';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::Z){
                        nomejog[posAtualCaractere]='Z';
                        posAtualCaractere++;
                    }
                    if(evento.key.code==sf::Keyboard::Hyphen){
                        nomejog[posAtualCaractere]='-';
                        posAtualCaractere++;
                    }
                }
            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.draw(nomJog1);
    janela.display();
   }


}


void TelaJogo(){
   sf::Texture textura;
   textura.loadFromFile("img/background.png");
   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

   char n1[10], n2[10];


    FILE *file=std::fopen("Players.txt", "r");
    std::fscanf(file,"%s%s\n", n1, n2);
    std::fclose(file);

    sf::Font fonte;
    fonte.loadFromFile("fontes/ARCADECLASSIC.TTF");
    sf::Text nomJog1;
    sf::Text nomJog2;

   nomJog1.setFont(fonte);
   nomJog1.setString(n1);
   nomJog1.setCharacterSize(29);
   nomJog1.setFillColor(sf::Color::White);
   nomJog1.setPosition(244,68);

   nomJog2.setFont(fonte);
   nomJog2.setString(n2);
   nomJog2.setCharacterSize(29);
   nomJog2.setFillColor(sf::Color::White);
   nomJog2.setPosition(709,68);

   while(janela.isOpen()){
    sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::R){
                    TelaRecorde();
            }
            if(evento.key.code==sf::Keyboard::G){
                    TelaVencedor();
            }

            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.draw(nomJog1);
    janela.draw(nomJog2);
    janela.display();
   }


}

int main(){
    //essa parte serve pra deixar os players em branco, pois a cada nova execuçao, tem que começar sem jogadores no arquivo
    FILE *file;
    file=std::fopen("Players.txt", "w");
    std::fclose(file);
    //**************
    //TelaMenuPrincipal();
    //TelaRanking();
    //TelaVencedor();
    //TelaJog1();
    TelaJogo();

    return 0;
}




















