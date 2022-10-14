#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Asteroid.h"
#include "Schuss.h"
using namespace std;




// Deklaration der Variablen
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GameWindow : public Gosu::Window
{ 
    Gosu::Image SpaceHintergrund;
    Gosu::Image Asteroid;
    Gosu::Image Logo;
    Gosu::Image Raumschiff;
    Gosu::Font exitgame = { 30 };                              
    Gosu::Font auswahlSpaceInvaders = {30};       
    Gosu::Font anzeigeScore = { 30 };
    Gosu::Font anzeigeScoreNichtZerstoert = { 30 };
    Gosu::Font anzeigeRestart = { 30 };
    Gosu::Font anzeigeStart = { 30 };
    vector<Asteorid> Asteroiden;
    vector<Schuss> schuesse; 
    int spielAuswahl = 0;   
    double mausX;
    double mausY;
    const double RaumschiffY = 550;                                                     
    double  RaumschiffX = 500;
    int rotation = 0;
    double SpeedIncreaseFaktor = 1.08;
    bool speedIncrease = false;
    int speedIncreaseAt = 5;
    int Score;
    int ScoreNichtZerstoert;
    double SpaceSpeed = 3;
    bool getroffen;
    bool Spielen = false;
    int AsteroidenAnzahl = 0;
    double schussSpeed = 7;
    int schussZahl;
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

public:
    GameWindow() : Window(1000, 600), Raumschiff("raumschiff1.png"),SpaceHintergrund("weltraum.png"), Asteroid("asteroid2.png"), Logo("logo.png")
    {
        set_caption("Space Invaders");
    }
    void restart_space() 
    {
        Asteroiden.clear();
        schuesse.clear();
        RaumschiffX = 500;
        Score = 0;
        SpaceSpeed = 3;
        getroffen = false;
        Spielen = true;
        AsteroidenAnzahl = 0;
        ScoreNichtZerstoert = 0;
        schussSpeed = 7;
        schussZahl = 0;
    }
    void AstInRange() {                 
        vector<Asteorid> hilfsvector;
        vector<Schuss> hilfSchuss;
        bool raus = false;
        bool AstRaus = false;  
        for (int ast = 0; ast < Asteroiden.size(); ast++) {    
            if (Asteroiden.at(ast).AsteroidY >= RaumschiffY - 30 && Asteroiden.at(ast).AsteroidY <= 560 && Asteroiden.at(ast).AsteroidX - 30 <= RaumschiffX  && Asteroiden.at(ast).AsteroidX + 90 >= RaumschiffX ) {
                getroffen = true;
                Asteroiden.at(ast).hit = true;
                break;
            }
            else if (Asteroiden.at(ast).AsteroidX >= 600) {
                ScoreNichtZerstoert++;
                speedIncrease = true;
                Asteroiden.at(ast).hit = true;
            }
            else {
                for (int st = 0; st < schuesse.size(); st++) {
                    if (schuesse.at(st).SchussX >= Asteroiden.at(ast).AsteroidX && schuesse.at(st).SchussX <= Asteroiden.at(ast).AsteroidX + Asteroiden.at(ast).AsteroidHoehe
                        && schuesse.at(st).SchussY <= (Asteroiden.at(ast).AsteroidY+ Asteroiden.at(ast).AsteroidBreite + schuesse.at(st).SchussHoehe)&& (schuesse.at(st).SchussY >= (Asteroiden.at(ast).AsteroidY ))) {
                        Score++;
                        Asteroiden.at(ast).hit = true;
                        schuesse.at(st).existent = false;
                    }                      
                    else if (schuesse.at(st).SchussX <= 0) {
                        schuesse.at(st).existent = false;
                    }
                }
            }
        }
        loescheObjekte();
    }
    void loescheObjekte() {
        vector<Asteorid> helpAst;
        for (int ast = 0; ast < Asteroiden.size(); ast++) {
            if (Asteroiden.at(ast).hit == true) {
            }
            else {
                helpAst.push_back(Asteroiden.at(ast));
            }
        }
        Asteroiden.clear();
        for (Asteorid ast : helpAst) {
            Asteroiden.push_back(ast);
        }

        vector<Schuss> helpSt;
        for (int st = 0; st < schuesse.size(); st++) {
            if (schuesse.at(st).existent == false) {
            }
            else {
                helpSt.push_back(schuesse.at(st));
            }
        }
        schuesse.clear();
        for (Schuss st : helpSt) {
            schuesse.push_back(st);
        }
    }
    void SchussBewegen() {
        for (Schuss& st : schuesse) {
            st.SchussY -= schussSpeed;
        }
    }
    void AsteroidenBewegen() {
        for (Asteorid& ast : Asteroiden)
        {
           ast.AsteroidY = ast.AsteroidY + SpaceSpeed; 
           if ((RaumschiffX <= (ast.AsteroidX + (ast.AsteroidHoehe / 2)) && RaumschiffX >= (ast.AsteroidX - (ast.AsteroidHoehe / 2))) &&
              (RaumschiffY <= (ast.AsteroidY - (ast.AsteroidBreite / 2)) && RaumschiffY >= (ast.AsteroidY + (ast.AsteroidBreite / 2))))
            {
                getroffen = true;
                break;
            }
            
        }
    }
  
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void draw() override
    {
        if (spielAuswahl == 0) {
            SpaceHintergrund.draw(0, 0, 0, 1.0, 1.0);
            Logo.draw(40, 0, 1, 1.0, 1.0);
            auswahlSpaceInvaders.draw_text_rel("Spielen", 515, 500, 1, 0.5, 0.5, 1, 1, Gosu::Color::GREEN);                                                     // Menü beim Start des Spiels              
        }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (spielAuswahl == 1) {
            SpaceHintergrund.draw(0, 0, 0, 1.0, 1.0);
            string score = to_string(Score);
            string nothit = to_string(ScoreNichtZerstoert);
            anzeigeScore.draw_text_rel("Score: " + score, 0, 0, 2, 0, 0, 1, 1, Gosu::Color::GREEN);
            

            if (Spielen) {
                Raumschiff.draw_rot(RaumschiffX, RaumschiffY, 2, rotation, 0.5, 0.5,0.1, 0.1);
                for (int ast = 0; ast < Asteroiden.size(); ast++) {
                    if (Asteroiden.at(ast).hit == false) {
                        graphics().draw_rect(Asteroiden.at(ast).AsteroidX, Asteroiden.at(ast).AsteroidY, Asteroiden.at(ast).AsteroidBreite, Asteroiden.at(ast).AsteroidHoehe, Asteroiden.at(ast).AsteroidFarbe, Asteroiden.at(ast).AsteroidPos);
                        Asteroid.draw((Asteroiden.at(ast).AsteroidX - 10), (Asteroiden.at(ast).AsteroidY-30), Asteroiden.at(ast).AsteroidPos,0.5, 0.5);

                    }
                }
                for (int st = 0; st < schuesse.size(); st++) {
                    if (schuesse.at(st).existent) {
                        graphics().draw_rect(schuesse.at(st).SchussX, schuesse.at(st).SchussY, schuesse.at(st).SchussBreite, schuesse.at(st).SchussHoehe, schuesse.at(st).SchussFarbe, schuesse.at(st).SchussHoehe);
                    }
                }
            }
            if (getroffen) {
                graphics().draw_quad(400, 270, Gosu::Color::RED, 400, 330, Gosu::Color::RED, 600, 330, Gosu::Color::RED, 600, 270, Gosu::Color::RED, 1);
                anzeigeRestart.draw_text_rel("Restart", 500, 300, 2, 0.5, 0.5, 2, 2, Gosu::Color::WHITE);
                exitgame.draw_text_rel("Exit", 970, 20, 2, 0.5, 0.5, 1, 1, Gosu::Color::RED);
            
            }
        }
       
    }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // 
    // Wird 60x pro Sekunde aufgerufen
    void update() override
    {
        mausX = input().mouse_x();            //Position der Maus im Menü
        mausY = input().mouse_y();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (spielAuswahl == 0) {
            if (mausX >= 430 && mausX <= 600 && mausY >= 400 && mausY <= 600 && input().down(Gosu::Button::MS_LEFT)) {     
                spielAuswahl = 1;                                                                                                // Menüauswahl
                Spielen = true;
                restart_space();
               
            }
        }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       
        if (spielAuswahl == 1) {
            if (!getroffen) {
                if (Score % speedIncreaseAt == 0 && speedIncrease) {
                    SpaceSpeed = SpaceSpeed * SpeedIncreaseFaktor;
                    speedIncrease = false;
                }
                AsteroidenAnzahl--;
                schussZahl++;
                
                if (input().down(Gosu::Button::KB_LEFT) || input().down(Gosu::Button::KB_A)) 
                {
                    RaumschiffX -= (SpaceSpeed + 2);
                }
                else if (input().down(Gosu::Button::KB_RIGHT) || input().down(Gosu::Button::KB_D)) 
                {
                    RaumschiffX += SpaceSpeed + 2;
                }
                
                if (AsteroidenAnzahl <= 1) {
                    AsteroidenAnzahl = 30;
                    erstelleAsteroid(Asteroiden);
                    
                       
                }
                if (input().down(Gosu::Button::KB_SPACE)&& schussZahl>=10) {
                    schuesse.push_back(erstelleSchuss(RaumschiffX, RaumschiffY));
                    schussZahl = 0;
                }
                AstInRange(); 
                SchussBewegen();
                AsteroidenBewegen();
            }
            else if (mausX >= 410 && mausX <= 590 && mausY >= 270 && mausY <= 330 && input().down(Gosu::Button::MS_LEFT)) {    // Restart Knopf wurde betätigt
                restart_space();  
                getroffen = false;
                return;
            }
            else if (mausX >= 900 && mausX <= 1000 && mausY >= 0 && mausY <= 100 && input().down(Gosu::Button::MS_LEFT)) {               //Spiel beenden
                exit(3);
            }
            if (RaumschiffX > 1000 || RaumschiffX< 0)              // Abfrage, ob man außerhalb den Bildschirms geflogen ist falls ja Game Over
            getroffen = true;
        }
    }
};
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    GameWindow GameWindow;
    GameWindow.show();
}

