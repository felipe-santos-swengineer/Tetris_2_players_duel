/// arquivo so com as telas do jogo

#include <SFML/Graphics.hpp>
#include <unistd.h> //renomeaçao de arquivos
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <SFML/Audio.hpp>

bool JogoRodando=true; //vai garantir um loop entre todas as telas
int CodTela=5;//cada tela tem um codigo, e retorna um inteiro que é o codigo da proxima tela
int maiorrecorde=1000;

typedef struct p{
	double px;
	double py;
} Coord; //estrutura que vai guardar os valores de x e y de cada quadrado na matriz q vai montar a peça

typedef struct p2{
	int px;
	int py;
} Coord2;//estrutura sera usada para guardar o codigo das peças. coluna e o px e linha é o py


Coord matrizdevalxy[10][20]; //matriz que guardara os pontos x e y corretos de cada quadrado na posicao
Coord matrizdevalxy_2[10][20];

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

sf::RenderWindow janela(sf::VideoMode(1050, 591), "Trabalho Pablo");
//janela.setFramerateLimit(10);
bool primeiroJogo=true;
int TelaMenuPrincipal();
int TelaJogo();
int TelaRanking();
int TelaJog1();
int TelaJog2();
int TelaRecorde();
int TelaVencedor();
int TelaMesmosJogadores();



int TelaMesmosJogadores(){
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
            JogoRodando=false;
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){
                CodTela=5;
                return 0;//vai direto pra tela do jogo
            }
            if(evento.key.code==sf::Keyboard::Escape){
                file=std::fopen("Players.txt", "w");//se for outros jogadores, ele subscreve o arquivo em branco
                std::fclose(file);
                CodTela=3;
                return 0;//vai pra tela de nome do jogador 1
                }

            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.display();
   }

}





int TelaRecorde(){
    char nomeJogador[7], pontos[7];
    FILE *file;
    file=std::fopen("Ranking_1_Lugar.txt", "r");
    std::fscanf(file,"%s%s ", pontos, nomeJogador);
    std::fclose(file);

   sf::Texture textura;
   //textura.loadFromFile("img/Conferir/recorde conferir.png");
   textura.loadFromFile("img/Recorde.png");
   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

   sf::Font fonteArcade;;
   fonteArcade.loadFromFile("Fontes/ARCADECLASSIC.TTF");

    sf::Text textoNome;
    textoNome.setFont(fonteArcade);

    textoNome.setCharacterSize(65);
    textoNome.setFillColor(sf::Color(255,204,0));
    textoNome.setPosition(420,274);
    textoNome.setString(nomeJogador);

    sf::Text textoPontos;
    textoPontos.setFont(fonteArcade);

    textoPontos.setCharacterSize(51);
    textoPontos.setFillColor(sf::Color::Green);
    textoPontos.setPosition(456,335);
    textoPontos.setString(pontos);





   while(janela.isOpen()){
    sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
            JogoRodando=false;
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){
                CodTela=7;
                return 0;//vai para tela do vencedor
                }
            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.draw(textoNome);
    janela.draw(textoPontos);
    janela.display();
   }


}

int TelaMenuPrincipal(){
   sf::Texture textura;
   textura.loadFromFile("img/teladomenu.png");
   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

   while(janela.isOpen()){
    sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
            JogoRodando=false;
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
                if(evento.key.code==sf::Keyboard::R){
                    CodTela=2;
                    return 0;//TelaRanking();
                }
                if(evento.key.code==sf::Keyboard::Enter){
                        if(primeiroJogo){
                            primeiroJogo=false;
                            CodTela=3;
                           return 0;//TelaJog1();
                        } else {
                            CodTela=8;
                            return 0;//TelaMesmosJogadores();

                        }

                }
                if(evento.key.code==sf::Keyboard::Escape){
                    JogoRodando=false;
                    janela.close();
                }

            }
    	}
    janela.clear();
    janela.draw(sprite);
    janela.display();
   }


}

int TelaRanking(){
    sf::Texture textura;
   textura.loadFromFile("img/Ranking.png");

   sf::Sprite sprite;
   sprite.setTexture(textura);
   sprite.setPosition(0,0);

   std::string nomesRecordes[3][4];//guarda os "nomes" que serao mostrados; tem 4 nomes em cada uma das 3 linhas do ranking
   char n1[10], n2[10], n3[10], n4[10];//variaveis provisoria, pois FSCANF nao atribui diretamente na posiçao da matriz a string, tem que ter esse intermediario


   FILE *file1=std::fopen("Ranking_1_Lugar.txt","r");
std::fscanf(file1,"%s%s%s%s\n",n2,n1,n3,n4);
   nomesRecordes[0][0]=n1;
   nomesRecordes[0][1]=n2;
   nomesRecordes[0][2]=n3;
   nomesRecordes[0][3]=n4;
   fclose(file1);

   FILE *file2=std::fopen("Ranking_2_Lugar.txt","r");
std::fscanf(file2,"%s%s%s%s\n",n2,n1,n3,n4);
   nomesRecordes[1][0]=n1;
   nomesRecordes[1][1]=n2;
   nomesRecordes[1][2]=n3;
   nomesRecordes[1][3]=n4;
   fclose(file2);

   FILE *file3=std::fopen("Ranking_3_Lugar.txt","r");
std::fscanf(file3,"%s%s%s%s\n",n2,n1,n3,n4);
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
            JogoRodando=false;
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){
                CodTela=1;
                return 0;//TelaMenuPrincipal();
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
int TelaVencedor(){
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
            JogoRodando=false;
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter){
                    CodTela=1;
                   return 0;//TelaMenuPrincipal();
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





int TelaJog2(){
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

   sf::Text EntreComNome;
   EntreComNome.setFont(fonte);
   EntreComNome.setCharacterSize(26);
   EntreComNome.setFillColor(sf::Color(210,210,210));
   EntreComNome.setPosition(452,322);
   EntreComNome.setString("DIGITE SEU NOME");

    while(janela.isOpen()){
        nomJog1.setString(nomejog);

    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
            JogoRodando=false;
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter&&posAtualCaractere!=0){//pra o enter funcionar, tem que ter pelo menos uma letra
                std::fprintf(file,"%s ", nomejog);
                std::fclose(file);
                CodTela=5;
               return 0;//TelaJogo();
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
    if(!posAtualCaractere){//se posatualcaractere for 0, nao foi digitado nada e a frase aparece
        janela.draw(EntreComNome);
    }
    janela.display();
   }


}




int TelaJog1(){
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

   sf::Text EntreComNome;
   EntreComNome.setFont(fonte);
   EntreComNome.setCharacterSize(26);
   EntreComNome.setFillColor(sf::Color(210,210,210));
   EntreComNome.setPosition(452,322);
   EntreComNome.setString("DIGITE SEU NOME");

    while(janela.isOpen()){
        nomJog1.setString(nomejog);

    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
            JogoRodando=false;
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){
            if(evento.key.code==sf::Keyboard::Enter&&posAtualCaractere!=0){//pra o enter funcionar, tem que ter pelo menos uma letra
                std::fprintf(file,"%s ", nomejog);
                std::fclose(file);
                CodTela=4;
               return 0;//TelaJog2();

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
    if(!posAtualCaractere){//se posatualcaractere for 0, nao foi digitado nada e a frase aparece
        janela.draw(EntreComNome);
    }
    janela.display();
   }


}
///************************************************************** TELA JOGO ***************************************************************
///****************************************************************************************************************************************

///****************************************************************************************************************************************


int TelaJogo(){


   char n1[10], n2[10];
   char jogRecorde[10], pontosRecorde[10];


    FILE *file=std::fopen("Players.txt", "r");
    std::fscanf(file,"%s%s\n", n1, n2);
    std::fclose(file);

    FILE *file2=std::fopen("Ranking_1_Lugar.txt", "r");
    std::fscanf(file,"%s%s\n", jogRecorde, pontosRecorde);
    std::fclose(file2);

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


    //**************************************************** COMEÇO DO JOGO ***********************************


	srand(time(NULL));

	//******************** DECLARAÇAO DE VARIAVEIS ********************************************************
	int i, j, mov_y=0, mov_x=4,mov_x_2=4,mov_y_2=0; //mov_y e mov_x é usado para incrementar a peça na matriz principal, no eix x e eixo y | MOV_X=4 para começar no meio
	int delay=3,delay_2=2; // serve para dar um delay de 3 segundos antes da peça descer
	int aleatorioPeca,aleatorioPeca_2; //vai receber um numero aleatorio entre 0 e 9;
	int aleatorioCor,aleatorioCor_2; //vai receber um numero aleatorio entre 0 e 5;
	int limitedapeca_y=0,limitedapeca_y_2; //valor que vai controlar o limite da peça em relaçao a borda inferior. ele é igual ao maior valor da peça no eixo y;
	int limitedapeca_x=0,limitedapeca_x_2; //valor que vai controlar o limite da peça em relaçao a borda inferior. ele é igual ao maior valor da peça no eixo x;
	int y=0, x=4, y_2=0, x_2=4; //valores que serao incrementados nos eventos de botoes e limitara as bordas
	//bool colocarnoespelho=false; //para entrar no if de colocar na matrz espelho secundaria
	int corDaMatridecor=0,corDaMatridecor_2=0;//serve pra guardar o valor do codigo espelho
	int pontos=0, cont=0,cont2=0, pontos_2=0;
	int j2=0,i2=0;
	int girar=0, girar_2=0;
	int temposegundos=0, tempominutos=0;
	bool colisao_Y=false, colisao_Y_2=false;
	float tempoMomentoPausa=0, tempoMomentoDESPausa=0, tempoEntrePausas=0, guardatempo=0;
	Coord2 coordenadasdaspecas [23][4];
	Coord2 coordenadasdaspecas_2 [23][4];
	int MovEsqOuDir=0,MovEsqOuDir1=0,MovEsqOuDir1_2=0,MovEsqOuDir_2=0;
    int contaMovEsqOuDir=0,contaMovEsqOuDir_2=0;
    int VerificsColisao=0,VerificsColisao_2=0;
    int corrigidelay=0,corrigidelay_2=0;
    int corrigirotacao=0,aleatorioPecateste=0,corrigirotacao_2=0,aleatorioPecateste_2=0;
    int controtacao=0,controtacao_2=0;
    int impededuplatecla=0; int impededuplatecla_2=0;
    bool jogador1perdeu=false, jogador2perdeu=false;

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
                      	0,0,1,0,1,1,1,2,//aqui
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
            	coordenadasdaspecas_2[i][j].px=codigoPeca[i][j+aux];
            	coordenadasdaspecas_2[i][j].py=codigoPeca[i][j+1+aux];
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
        	matrizdevalxy[i][j].px=(i*20.8)+189.0; //i multiplica pois é a coluna ; 20.8 px é o recuo da peça no eixo x quando pressionado (largura)
        	matrizdevalxy[i][j].py=(j*20.7)+108.0;//j multiplica pois é a linha ; 20.7 px é o recuo da peça no eixo y quando pressionado  (altura)
            matrizdevalxy_2[i][j].px=(i*20.8)+654.0;
            matrizdevalxy_2[i][j].py=(j*20.7)+108.0;
    	}
	}

	//****************************************************************************



	sf::Clock clock;
	sf::Clock clockCronometro;
    sf::Clock clock_2;
	sf::Clock clockCronometro_2;


	sf::Font fonteArcade;
	fonteArcade.loadFromFile("Fontes/ARCADECLASSIC.TTF");

	sf::Font fonteMotion;
	fonteMotion.loadFromFile("Fontes/MotionControl-Bold.ttf");

	sf::Text textoArcade;
	textoArcade.setFont(fonteArcade);
	textoArcade.setLetterSpacing(2);
	textoArcade.setCharacterSize(29);
	textoArcade.setFillColor(sf::Color::White);
	textoArcade.setPosition(sf::Vector2f(75,300));

    sf::Text textoArcade2;
    textoArcade2.setFont(fonteArcade);

    sf::Text textoArcade3;
    textoArcade3.setFont(fonteArcade);

    sf::Text textoArcade4;
    textoArcade4.setFont(fonteArcade);

	sf::Text textoMotion;
	textoMotion.setFont(fonteMotion);
	textoMotion.setLetterSpacing(2);
	textoMotion.setCharacterSize(50);
	textoMotion.setFillColor(sf::Color(38,233,238));
	textoMotion.setPosition(sf::Vector2f(510,228));

	sf::Text textoMotion2;
	textoMotion2.setFont(fonteMotion);
	textoMotion2.setLetterSpacing(2);
	textoMotion2.setCharacterSize(50);
	textoMotion2.setFillColor(sf::Color(38,233,238));
	textoMotion2.setPosition(sf::Vector2f(482,228));


	sf::Texture texturabg;
	texturabg.loadFromFile("img/background.png");

    sf::Texture texturaPerdeu;
    texturaPerdeu.loadFromFile("img/VocePerdeu.png");
    sf::Sprite spritePerdeu1;
    spritePerdeu1.setTexture(texturaPerdeu);
    spritePerdeu1.setPosition(sf::Vector2f(189,107));

    sf::Sprite spritePerdeu2;
    spritePerdeu2.setTexture(texturaPerdeu);
    spritePerdeu2.setPosition(sf::Vector2f(655,107));

    /*
	sf::Music p1;
	p1.openFromFile("sound1.ogg");
	p1.play();
*/


	int proxCor[2];
	int proxCor_2[2];
	for(i=0;i<2;i++){
    	proxCor[i]=rand()%5;
    	proxCor_2[i]=rand()%5;
	}
	aleatorioCor=proxCor[0]; // seta um valor aleatorio para carregar o arquivo de cor diferente a cada peça
    aleatorioCor_2=proxCor_2[0];

	sf::Texture texturapeca;
	texturapeca.loadFromFile(cores[aleatorioCor]);


	sf::Texture texturapecaEstatica;

    sf::Texture texturapeca_2;
	texturapeca_2.loadFromFile(cores[aleatorioCor_2]);


	sf::Texture texturapecaEstatica_2;

	int aleatorioPecaEmUso;
	int aleatorioPecaEmUso_2;
	int proximapeca[2];
	int proximapeca_2[2];

	for(i=0;i<2;i++){
	    proximapeca[i]=rand()%9; //para nao gerar peças de codigo 3 e 4 pois tem redundancia com outras peças giradas
        if(proximapeca[i]==4){proximapeca[i]=3;}
        if(proximapeca[i]==5){proximapeca[i]=1;}

    	//printf("aleat 0: %d", proximapeca[i]);
	}

	aleatorioPecaEmUso=proximapeca[0];
	aleatorioPeca=aleatorioPecaEmUso;

    for(i=0;i<2;i++){
	    proximapeca_2[i]=rand()%9; //para nao gerar peças de codigo 3 e 4 pois tem redundancia com outras peças giradas
        if(proximapeca_2[i]==4){proximapeca_2[i]=3;}
        if(proximapeca_2[i]==5){proximapeca_2[i]=1;}

    	//printf("aleat 0: %d", proximapeca_2[i]);
	}

	aleatorioPecaEmUso_2=proximapeca_2[0];
	aleatorioPeca_2=aleatorioPecaEmUso_2;

	int matrizdecodcoresparamatrizsecund[10][20];// serve para guardar o codigo de cores na posicao
	bool matrizPlayer[10][20]; //matriz da peça que desce
	bool matrizPlayerEstatico[10][20]; // matriz que copia a ultima posisao da peça
    int matrizdecodcoresparamatrizsecund_2[10][20];
    bool matrizPlayer_2[10][20];
    bool matrizPlayerEstatico_2[10][20];

	//****************************** PEÇA
	bool matrizproxPeca[4][4];
	Coord matrizvalProxPeca[4][4];
    bool matrizproxPeca_2[4][4];
    Coord matrizvalProxPeca_2[4][4];

	for (i=0;i<4;i++){
    	for (j=0;j<4;j++){
        	matrizvalProxPeca[i][j].py=(i*20.8)+142.0;
        	matrizvalProxPeca[i][j].px=(j*20.7)+71.0;
        	 matrizvalProxPeca_2[i][j].py=(i*20.8)+142.0;
            matrizvalProxPeca_2[i][j].px=(j*20.7)+916.0;
    	}
	}

	zeramatrizproxpeca(matrizproxPeca);
	zeramatrizsecundaria(matrizPlayerEstatico);
    zeramatrizproxpeca(matrizproxPeca_2);
	zeramatrizsecundaria(matrizPlayerEstatico_2);

    int pontuacao1lugar=0;
    FILE *fileRanking=std::fopen("Ranking_1_Lugar.txt","r");
    std::fscanf(fileRanking,"%d ", &pontuacao1lugar);
    std::fclose(fileRanking);


//############################################### COMEÇO DO LOOP #############################################################################

while (janela.isOpen()){



   // printf("Pontos: %d\n\n\n", pontos);
	//convertendo inteiro em string para fazer a pontuaçao
	std::stringstream ss;
	ss << pontos <<std::endl;
	std::string stringdepontos = ss.str();

	textoArcade.setString(stringdepontos);

	std::stringstream ss_2;
    ss_2 << pontos_2 <<std::endl;
    std::string stringdepontos_2 = ss_2.str();

    textoArcade2.setString(stringdepontos_2);
    textoArcade2.setLetterSpacing(2);
    textoArcade2.setCharacterSize(29);
    textoArcade2.setFillColor(sf::Color::White);
    textoArcade2.setPosition(sf::Vector2f(915,300));


    ///============= PARTE DOS RECORDES ===============
/*
    std::stringstream mostrarecorde;
    mostrarecorde << maiorrecorde <<std::endl;
    std::string stringderecord = mostrarecorde.str();
*/
    textoArcade3.setString(jogRecorde);
    textoArcade3.setLetterSpacing(2);
    textoArcade3.setCharacterSize(29);
    textoArcade3.setFillColor(sf::Color::White);
    textoArcade3.setPosition(sf::Vector2f(477,420));

    textoArcade4.setString(pontosRecorde);
    textoArcade4.setLetterSpacing(2);
    textoArcade4.setCharacterSize(29);
    textoArcade4.setFillColor(sf::Color::White);
    textoArcade4.setPosition(sf::Vector2f(482,445));
    ///==============================================

   temposegundos = (int) clockCronometro.getElapsedTime().asSeconds(); //esta sendo feito o casting de float para inteiro
    if(temposegundos==60){
        temposegundos=0;
         tempominutos++;
        clockCronometro.restart();
    }



        //convertendo int dos segundos para string para fazer o cronometro
        std::stringstream ss2;
        if(temposegundos<10){ //condicional para incluir o zero a esquerda qdo o numero for menos que 10
            ss2<< ":0"<< temposegundos <<std::endl;
        } else {
            ss2<< ":"<< temposegundos <<std::endl;
        }

        std::string temposegundoString = ss2.str();
        textoMotion.setString(temposegundoString);

        //convertendo int dos minutos para string para fazer o cronometro
        std::stringstream ss3;
        ss3<< tempominutos <<std::endl;
        std::string tempominutoString = ss3.str();

        textoMotion2.setString(tempominutoString);



	sf::Sprite background;
	background.setTexture(texturabg);
	background.setPosition(sf::Vector2f(0,0));

	sf::Sprite spriteMov; //sprite mov se movimenta atravez da matriz principal
	spriteMov.setTexture(texturapeca);

	sf::Sprite spriteEst; //spriteest copia a posicao de spritemov para a matriz secondaria
	spriteEst.setTexture(texturapecaEstatica);

	sf::Sprite spriteproxpeca;
	spriteproxpeca.setTexture(texturapecaEstatica);

	sf::Sprite spriteMov_2; //sprite mov se movimenta atravez da matriz principal
	spriteMov_2.setTexture(texturapeca_2);

	sf::Sprite spriteEst_2; //spriteest copia a posicao de spritemov para a matriz secondaria
	spriteEst_2.setTexture(texturapecaEstatica_2);

	sf::Sprite spriteproxpeca_2;
	spriteproxpeca_2.setTexture(texturapecaEstatica_2);





	zeramatrizproxpeca(matrizproxPeca);
	zeramatrizprincipal(matrizPlayer); //chama funçao que zera a matriz/ ele começa com false em todas
    zeramatrizproxpeca(matrizproxPeca_2);
    zeramatrizprincipal(matrizPlayer_2);

    	///****************************** EVENTOS DE PRESSIONADO DE BOTOES **********************************************
    	sf::Event evento;
    	while (janela.pollEvent(evento)){
        	if(evento.type==sf::Event::Closed){
            JogoRodando=false;
        	janela.close();
    	} else if (evento.type==sf::Event::KeyReleased){

                if(evento.key.code==sf::Keyboard::R){
                    CodTela=6;
                    return 0;//TelaRecorde();
                }
                if(evento.key.code==sf::Keyboard::G){
                    CodTela=7;
                    return 0;//TelaVencedor();
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

            }
        }
     if(mov_y_2>0){
            if(evento.key.code==sf::Keyboard::Up){

            aleatorioPecateste_2=matrizRotacao[aleatorioPecaEmUso_2][girar_2+1];
            for(j=0;j<4;j++){
            if (matrizPlayerEstatico_2[coordenadasdaspecas_2[aleatorioPecateste_2][j].px + mov_x_2][coordenadasdaspecas_2[aleatorioPecateste_2][j].py + mov_y_2]==true){
            corrigirotacao_2++;}
             if (coordenadasdaspecas_2[aleatorioPecateste_2][j].px + mov_x_2>9){
            corrigirotacao_2++;}
             if (coordenadasdaspecas_2[aleatorioPecateste_2][j].py + mov_y_2==19){
            corrigirotacao_2++;}
             if (matrizPlayerEstatico_2[coordenadasdaspecas_2[aleatorioPecateste_2][j].px + mov_x_2][coordenadasdaspecas_2[aleatorioPecateste_2][j].py + mov_y_2+1]==true){
            corrigirotacao_2++;}
            if (coordenadasdaspecas_2[aleatorioPecaEmUso_2][j].px + mov_x_2>9){ //add
            corrigirotacao_2++;}
            if (coordenadasdaspecas_2[aleatorioPecaEmUso_2][j].py + mov_y_2>19){ //add
            corrigirotacao_2++;}
      }
            if(corrigirotacao_2==0){
                girar_2++;
                impededuplatecla_2++;
                controtacao_2++;
                }

            corrigirotacao_2=0;
            aleatorioPecateste_2=0;


                if(girar_2>3){
                    girar_2=0;
                }


        }}

        if(mov_x_2<=8-limitedapeca_x_2&&impededuplatecla_2==0){
            if (evento.key.code==sf::Keyboard::Right){
                for(j=0;j<4;j++){
                    if (matrizPlayerEstatico_2[coordenadasdaspecas_2[aleatorioPeca_2][j].px + mov_x_2+1][coordenadasdaspecas_2[aleatorioPeca_2][j].py + mov_y_2]==true){
                    VerificsColisao_2++;}
                }
                if(VerificsColisao_2==0){
                mov_x_2++;
                contaMovEsqOuDir_2++;}
                VerificsColisao_2=0;
                //printf("mov_x: %d\n", mov_x);
                //printf("limite x: %d\n", limitedapeca_x);
            }
        }

        if(mov_x_2>0 &&impededuplatecla_2==0){
            if (evento.key.code==sf::Keyboard::Left){
                for(j=0;j<4;j++){
                    if (matrizPlayerEstatico_2[coordenadasdaspecas_2[aleatorioPeca_2][j].px + mov_x_2-1][coordenadasdaspecas_2[aleatorioPeca_2][j].py + mov_y_2]==true){
                    VerificsColisao_2++;}

                }
                if(VerificsColisao_2==0){
                mov_x_2--;
                contaMovEsqOuDir_2++;}
                VerificsColisao_2=0;
                //printf("mov_x: %d\n", mov_x);
                //printf("limite x: %d\n", limitedapeca_x);
            }
        }

        if(mov_y_2<=18-limitedapeca_y_2){
            if(evento.key.code==sf::Keyboard::Down&&delay_2==false){
                for(j=0;j<4;j++){
                if (matrizPlayerEstatico_2[coordenadasdaspecas_2[aleatorioPeca_2][j].px + mov_x_2][coordenadasdaspecas_2[aleatorioPeca_2][j].py + mov_y_2+1]==true){
                corrigidelay_2++;}
                }
                if(corrigidelay_2==0)
                mov_y_2++;
                corrigidelay_2=0;
                //printf("mov_y: %d\n", mov_y);
                //printf("limite y: %d\n", limitedapeca_y);
            }
        }
    }
}

        //aleatorioPecaIA=matrizRotacao[aleatorioPecaEmUsoIA][girarIA];
        aleatorioPeca=matrizRotacao[aleatorioPecaEmUso][girar];
        //printf("matrizrotacao[%d] [%d]\n",aleatorioPecaEmUso,girar);
        aleatorioPeca_2=matrizRotacao[aleatorioPecaEmUso_2][girar_2];
        impededuplatecla=0;
        impededuplatecla_2=0;
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

        matrizPlayer_2[coordenadasdaspecas_2[aleatorioPeca_2][j].px + mov_x_2][coordenadasdaspecas_2[aleatorioPeca_2][j].py + mov_y_2]=true;//mov_y e mov_x usados para mover a peca
        //a partir daqui vai ser setado o valor do limite da peça de acordo com o valor de y;
        //para a peça parar no lugar certo independente do tamanho (altura)
        //limite das peças para variar nas bordas
        //a variavel  limite da peça recebe o valor da posicao em relacao ao eixo, nao valores booleanos
        if(j==0){
            limitedapeca_y_2=coordenadasdaspecas_2[aleatorioPeca_2][0].py;
            limitedapeca_x_2=coordenadasdaspecas_2[aleatorioPeca_2][0].px;
        } else {
            if(limitedapeca_y_2<=coordenadasdaspecas_2[aleatorioPeca_2][j].py){
                limitedapeca_y_2=coordenadasdaspecas_2[aleatorioPeca_2][j].py;
            }
            if(limitedapeca_x_2<=coordenadasdaspecas_2[aleatorioPeca_2][j].px){
                limitedapeca_x_2=coordenadasdaspecas_2[aleatorioPeca_2][j].px;
            }
        }

        ///PARTE DAS COLISOES - EIXO Y
        //uma peça transparente e gerada uma casa para baixo e entao é comparado se e true. se a proxima casa
        //antes da peça verdadeira descer fro true, entao ele para a peça.

        if (matrizPlayerEstatico_2[coordenadasdaspecas_2[aleatorioPeca_2][j].px + mov_x_2][coordenadasdaspecas_2[aleatorioPeca_2][j].py + mov_y_2+1]==true){
            colisao_Y_2++;
            MovEsqOuDir_2++;
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
              	spriteMov.setPosition(sf::Vector2f(matrizdevalxy[i][j].px, matrizdevalxy[i][j].py));
              	janela.draw(spriteMov);

            	}
            	if(matrizPlayer_2[i][j]){
              	spriteMov_2.setPosition(sf::Vector2f(matrizdevalxy_2[i][j].px, matrizdevalxy_2[i][j].py));
              	janela.draw(spriteMov_2);

            	}
        	}
    	}
    	//****************************************************************************




     	//************** PROXIMA PEÇA **********************


    	for(j=0;j<4;j++){
    	matrizproxPeca[coordenadasdaspecas[proximapeca[1] ][j].py][coordenadasdaspecas[proximapeca[1] ][j].px]=true;//mov_y e mov_x usados para mover a peca
    	matrizproxPeca_2[coordenadasdaspecas_2[proximapeca_2[1] ][j].py][coordenadasdaspecas_2[proximapeca_2[1] ][j].px]=true;
    	}


    	for(i=0;i<4;i++){
        	for(j=0;j<4;j++){
            	if(matrizproxPeca[i][j]){
              	spriteproxpeca.setPosition(sf::Vector2f(matrizvalProxPeca[i][j].px, matrizvalProxPeca[i][j].py));
              	texturapecaEstatica.loadFromFile(cores[proxCor[1]]);
              	if(!jogador1perdeu){
                   janela.draw(spriteproxpeca);
              	}



            	}
            	if(matrizproxPeca_2[i][j]){
              	spriteproxpeca_2.setPosition(sf::Vector2f(matrizvalProxPeca_2[i][j].px, matrizvalProxPeca_2[i][j].py));
              	texturapecaEstatica_2.loadFromFile(cores[proxCor_2[1]]);
              	if(!jogador2perdeu){
                    janela.draw(spriteproxpeca_2);
              	}
            	}
        	}
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

        if(contaMovEsqOuDir_2!=0){
            for(j=0;j<4;j++){
            if (matrizPlayerEstatico_2[coordenadasdaspecas_2[aleatorioPeca_2][j].px + mov_x_2][coordenadasdaspecas_2[aleatorioPeca_2][j].py + mov_y_2+1]==true){
            MovEsqOuDir1_2++;}
        }
        if(MovEsqOuDir1_2==0){
                MovEsqOuDir_2=0;
                colisao_Y_2=false;
                contaMovEsqOuDir_2=0;
        }}
        MovEsqOuDir1_2=0;

         if(controtacao_2!=0){
            for(j=0;j<4;j++){
            if (matrizPlayerEstatico_2[coordenadasdaspecas_2[aleatorioPeca_2][j].px + mov_x_2][coordenadasdaspecas_2[aleatorioPeca_2][j].py + mov_y_2+1]==true){
            MovEsqOuDir1_2++;}
        }
        if(MovEsqOuDir1_2==0){
                MovEsqOuDir_2=0;
                colisao_Y_2=false;
                controtacao_2=0;
        }}
        MovEsqOuDir1_2=0;

        i=19;
    while(i>0){
        for(j=0;j<10;j++){//verifica se a linha esta prenchida, na ordem de baixo pra cima;
            if(matrizPlayerEstatico_2[j][i])
                cont++;
        }

        	if(cont==10){//quando cont=10 significa que está prenchida
        	matrizPlayerEstatico_2[0][i]=false; //limpo a linha
        	matrizPlayerEstatico_2[1][i]=false;
        	matrizPlayerEstatico_2[2][i]=false;
        	matrizPlayerEstatico_2[3][i]=false;
        	matrizPlayerEstatico_2[4][i]=false;
        	matrizPlayerEstatico_2[5][i]=false;
        	matrizPlayerEstatico_2[6][i]=false;
        	matrizPlayerEstatico_2[7][i]=false;
        	matrizPlayerEstatico_2[8][i]=false;
        	matrizPlayerEstatico_2[9][i]=false;


    	for(i2=i-1;i2>0;i2--){ // esses 2 laços tranferem todas as linhas acima da linha apagada pra baixo;
        	for(j2=0;j2<10;j2++){ //m
                if(matrizPlayerEstatico_2[j2][i2]==true&&i2>0){ //impede que na linha zero, ele pegue o lixo de memoria, pois não existe nada acima da linha 0;
                    matrizPlayerEstatico_2[j2][i2+1]=matrizPlayerEstatico_2[j2][i2];
                    matrizdecodcoresparamatrizsecund_2[j2][i2+1]=matrizdecodcoresparamatrizsecund_2[j2][i2];
                    matrizPlayerEstatico_2[j2][i2]=false;
                }
            }
    	}
    	for(i2=0;i2<20;i2++)
        	for(j2=0;j2<10;j2++)
            	if(matrizPlayerEstatico_2[j2][i2])
            	cont2++;
    	if(cont2>0){
        	pontos_2+=10;
        	printf("%d pontos, continue assim...\n",pontos);}}

    	cont=0;
    	cont2=0;
    	i--;
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
                }
            }
    	}
    	for(i2=0;i2<20;i2++)
        	for(j2=0;j2<10;j2++)
            	if(matrizPlayerEstatico[j2][i2])
            	cont2++;
    	if(cont2>0){
        	pontos+=10;
        	printf("%d pontos, continue assim...\n",pontos);}}

    	cont=0;
    	cont2=0;
    	i--;
    }

    	//***************************** TIME DO JOGO ***********************************************


    	//parte do clock do jogo;
    	//funçao retoorna o valor em segundos da execuçao, e de acordo com a
    	//comparacao se define a velocidade qque a peça cai,
    	// usando o incremento mov_y

        //printf("pontos: %d  nomjog :%s  min: %d  seg: %d\n", pontos, nomJog2,tempominutos, temposegundos);

    	if(clock_2.getElapsedTime().asSeconds()>0.3){
       	if(delay_2){
        	delay_2--;
       	}

       	if(delay_2==0 && mov_y_2<=18-limitedapeca_y_2&&colisao_Y_2==false){ // limite de incrementaçao ate em baixo vairoa com o tamanho da peça (limitepeca)
        	mov_y_2++;
       	}
       	else if(MovEsqOuDir_2!=0||contaMovEsqOuDir_2==0){

            	//copia os valotes de uma matriz para outra
            	if(delay_2==0){
                    	//fazendo a copia da maatriz no ultyimo estado
                    	//coloquei o if delay>=3 pq ele tava entrando 3 vezes, antes da peça começar a descer
                    	//o delay serve pra fazer a peça esperar um instante antes de descer..
                    	for(i=0;i<10;i++){
                        	for(j=0;j<20;j++){
                            	if(matrizPlayer_2[i][j]){
                            	matrizdecodcoresparamatrizsecund_2[i][j] = aleatorioCor_2;// toda vez que acontecer a copia sera copiado tmb o codigo da cor da peça em questao
                              	matrizPlayerEstatico_2[i][j]=matrizPlayer_2[i][j];
                            	}
                        	}
                	}
            	}

            	//assim que a peça atinge a borda, o valor dela é mudada para ir pra cima
            	mov_y_2=0;
            	mov_x_2=4;
            	girar_2=0;
            	colisao_Y_2=false;
                MovEsqOuDir_2=0;


            	//#################  PRODUZ OUTRA COR E OUTRO FORMATO #####################
            	if(delay_2==0&&jogador2perdeu==false){//se jogador 2 perdeu, nao sera mais feito peças aleatorias

                	aleatorioPecaEmUso_2=proximapeca_2[1];
                	proximapeca_2[0]=proximapeca_2[1];
                	proximapeca_2[1]=rand()%9;

                	if(proximapeca_2[1]==4){proximapeca_2[1]=3;}
                    if(proximapeca_2[1]==5){proximapeca_2[1]=1;}

                	aleatorioCor_2=proxCor_2[1];
                	proxCor_2[0]=proxCor_2[1];
                	proxCor_2[1]=rand()%5;
                	texturapeca_2.loadFromFile(cores[aleatorioCor_2]);

            	}

       	}

        colisao_Y_2=false; //reseta a condiçao de colisao

        	clock_2.restart();//reset do clock de 0.3 segundos
    	}

    	if(clock.getElapsedTime().asSeconds()>0.3){
       	if(delay){
        	delay--;
       	}

       	if(delay==0 && mov_y<=18-limitedapeca_y&&colisao_Y==false){ // limite de incrementaçao ate em baixo vairoa com o tamanho da peça (limitepeca)
        	mov_y++;
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


            	//#################  PRODUZ OUTRA COR E OUTRO FORMATO #####################
            	if(delay==0&&jogador1perdeu==false){//se jogador 1 perdeu, nao sera mais feito peças aleatorias


                	aleatorioPecaEmUso=proximapeca[1];
                	proximapeca[0]=proximapeca[1];
                	proximapeca[1]=rand()%9;

                	if(proximapeca[1]==4){proximapeca[1]=3;}
                    if(proximapeca[1]==5){proximapeca[1]=1;}

                	aleatorioCor=proxCor[1];
                	proxCor[0]=proxCor[1];
                	proxCor[1]=rand()%5;
                	texturapeca.loadFromFile(cores[aleatorioCor]);

            	}


       	}

        colisao_Y=false; //reseta a condiçao de colisao

        	clock.restart();//reset do clock de 0.3 segundos
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
                	if(matrizPlayerEstatico_2[i][j]){
                  	spriteEst_2.setPosition(sf::Vector2f(matrizdevalxy_2[i][j].px, matrizdevalxy_2[i][j].py));
                  	corDaMatridecor_2 = matrizdecodcoresparamatrizsecund_2[i][j];//passa o codigo de cores da posicao para a variavel corDaMatridecor

                  	texturapecaEstatica_2.loadFromFile(cores[corDaMatridecor_2]);// carregar a cor correta na posicao atravaez da variavel corDaMatridecor
                  	janela.draw(spriteEst_2); //desenha a matriz secundaria

                	}
            	}
        	}
        //****************** TESTE DE COLISAO NO TETO ********************************

        for(i=0;i<10;i++){
            if(matrizPlayerEstatico[i][0]==true){
                janela.draw(spritePerdeu1);
                jogador1perdeu=true;
            }
            if(matrizPlayerEstatico_2[i][0]==true){
                janela.draw(spritePerdeu2);
                jogador2perdeu=true;
            }
            if(jogador1perdeu==true&&jogador2perdeu==true){//vai ser setados os recordes, se houver
                if(pontos>pontuacao1lugar){
                    std::rename("Ranking_1_Lugar.txt", "Ranking_2_Lugar.txt");
                    std::rename("Ranking_2_Lugar.txt", "Ranking_3_Lugar.txt");
                    FILE *fileAlteraRanking=std::fopen("Ranking_1_Lugar.txt", "w");
                    std::fprintf(fileAlteraRanking,"%d %s %d %d\n", pontos, n1,tempominutos, temposegundos);
                    std::fclose(fileAlteraRanking);
                    CodTela=6;//tela recorde
                    return 0;
                } else if(pontos_2>pontuacao1lugar){
                    std::rename("Ranking_1_Lugar.txt", "Ranking_2_Lugar.txt");
                    std::rename("Ranking_2_Lugar.txt", "Ranking_3_Lugar.txt");
                    FILE *fileAlteraRanking=std::fopen("Ranking_1_Lugar.txt", "w");
                    std::fprintf(fileAlteraRanking,"%d %s %d %d\n", pontos_2, n2,tempominutos, temposegundos);
                    std::fclose(fileAlteraRanking);
                    CodTela=6;//tela recorde
                    return 0;
                } else {
                    FILE *fileAlteraVencedor=std::fopen("VencedorPartidaAtual.txt", "w");
                    if(pontos>pontos_2){
                        std::fprintf(fileAlteraVencedor,"%s %s", pontos, n1);
                    } else if(pontos>pontos){
                        std::fprintf(fileAlteraVencedor,"%s %s", pontos_2, n2);
                    }
                    std::fclose(fileAlteraVencedor);
                    CodTela=7;
                    return 0;// TelaVencedor();
                }


            }
        }


    	//****************************************************************************

    	janela.draw(textoArcade);
    	janela.draw(textoArcade2);
    	janela.draw(textoArcade3);
    	janela.draw(textoArcade4);
    	janela.draw(textoMotion);
        janela.draw(textoMotion2);


        janela.draw(nomJog1);
        janela.draw(nomJog2);
        janela.display();
	}
//############################################### FIM DO LOOP #############################################################################




}

int main(){
    //essa parte serve pra deixar os players em branco, pois a cada nova execuçao, tem que começar sem jogadores no arquivo
    FILE *file;
    file=std::fopen("Players.txt", "w");
    std::fclose(file);
    //**************

    while(JogoRodando){
        if(CodTela==1){
            TelaMenuPrincipal();
        } else if(CodTela==2){
            TelaRanking();
        } else if(CodTela==3){
            TelaJog1();
        } else if(CodTela==4){
            TelaJog2();
        } else if(CodTela==5){
            TelaJogo();
        } else if(CodTela==6){
            TelaRecorde();
        } else if(CodTela==7){
            TelaVencedor();
        } else if(CodTela==8){
            TelaMesmosJogadores();
        }
    }
    return 0;
}




















