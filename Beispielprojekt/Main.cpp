#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Asteroid.h"
#include "Schuss.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GameWindow : public Gosu::Window
{ 
    Gosu::Song hintergrundmusik;
    Gosu::Sample restartSound;
    Gosu::Sample explosionSound;
    Gosu::Sample getroffenSound;
    Gosu::Image SpaceHintergrund;
    Gosu::Image Asteroid;
    Gosu::Image Logo;
    Gosu::Image Raumschiff;
    Gosu::Font exitgame = { 30 };   
    Gosu::Font entwickler = { 20 };
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
    bool fullscreen = false;
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public:
    GameWindow() : Window(1000, 600,true), Raumschiff("raumschiff.png"),SpaceHintergrund("weltraum.png"), Asteroid("asteroid.png"), Logo("logo.png"), explosionSound("explosion1.wav"), getroffenSound("gameover1.wav"), restartSound("restart.wav"), hintergrundmusik("song2.wav")
    {
        set_caption("Space Invaders");
    }
    void restart_game()                                             // Setzt die veränderten Variablen zurück auf ihren Ursprungswert 
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
    void loescheObjekte()                                           // löscht die getroffenen Asteroiden und Schüsse
    {
        vector<Asteorid> helpAst;
        for (int ast = 0; ast < Asteroiden.size(); ast++) 
        {
            if (Asteroiden.at(ast).hit == true)                     // wenn der Asteroid getroffen wird er nicht im Hilfsvektor zwischengespeichert
            {                                                           
            }
            else                                                    // Nicht getroffene Asteroiden werden im Hilfsvektor zwischengespeichert
            {
                helpAst.push_back(Asteroiden.at(ast));              
            }
        }
        Asteroiden.clear();                                         // Alle getroffenen Asteroiden werden gelöscht
        for (Asteorid ast : helpAst) 
        {
            Asteroiden.push_back(ast);                              // Nicht getroffene Asteroiden werden von dem Hilfsvektor in den Asteroidenvektor kopiert
        }

        vector<Schuss> helpSt;
        for (int st = 0; st < schuesse.size(); st++) 
        {
            if (schuesse.at(st).existent == false)                  // wenn der Schuss einen Asteroid trifft wird er nicht im Hilfsvektor zwischengespeichert
            {
            }
            else                                                    // wenn der Schuss keinen Asteroiden trifft wird er im Hilfsvektor zwischengespeichert
            {
                helpSt.push_back(schuesse.at(st));                  
            }
        }
        schuesse.clear();                                           // Alle Schüsse die Asteroiden getroffenen haben werden gelöscht
        for (Schuss st : helpSt) 
        {
            schuesse.push_back(st);                                 // Schüsse die keine Asteroiden getroffen haben werden aus dem HIlfsvektor in den Schussvektor kopiert
        }
    }
    void FunktionenObjekte() 
    {                 
        vector<Asteorid> hilfsvector;
        vector<Schuss> hilfSchuss;
        bool raus = false;
        bool AstRaus = false;  
        for (int ast = 0; ast < Asteroiden.size(); ast++) 
        {    
            if (Asteroiden.at(ast).AsteroidY >= RaumschiffY - 30 && Asteroiden.at(ast).AsteroidY <= 560 && Asteroiden.at(ast).AsteroidX - 30 <= RaumschiffX  && Asteroiden.at(ast).AsteroidX + 90 >= RaumschiffX ) // Prüft ob ein Asteroid das Raumschiff trifft
            {
                getroffen = true;
                Asteroiden.at(ast).hit = true;
                getroffenSound.play(3);
                break;
            }
            else if (Asteroiden.at(ast).AsteroidX >= 600)          // Prüft ob der Asteroid aus dem Bildschirm fliegt
            {
                ScoreNichtZerstoert++;
                speedIncrease = true;
                Asteroiden.at(ast).hit = true;
            }
            /*else if (RaumschiffX > 1000 || RaumschiffX < 0)  // Abfrage, ob man außerhalb den Bildschirms geflogen ist falls ja Game Over
            {
                getroffen = true;
                getroffenSound.play();
            }*/
            else {                                                 // Prüft ob ein Schuss einen Asteroiden getroffen hat
                for (int st = 0; st < schuesse.size(); st++) {
                    if (schuesse.at(st).SchussX >= Asteroiden.at(ast).AsteroidX && schuesse.at(st).SchussX <= Asteroiden.at(ast).AsteroidX + Asteroiden.at(ast).AsteroidHoehe
                        && schuesse.at(st).SchussY <= (Asteroiden.at(ast).AsteroidY+ Asteroiden.at(ast).AsteroidBreite + schuesse.at(st).SchussHoehe)&& (schuesse.at(st).SchussY >= (Asteroiden.at(ast).AsteroidY ))) {
                        Score++;
                        Asteroiden.at(ast).hit = true;
                        schuesse.at(st).existent = false;
                        explosionSound.play(3);
                    }                      
                    else if (schuesse.at(st).SchussX <= 0)         // Prüft ob ein Schuss aus dem Bildschirm fliegt
                    {
                        schuesse.at(st).existent = false;
                    }
                }
            }
        }
        loescheObjekte();                                         // löscht getroffene Asteroiden und Schüsse
    }
   
    void SchussBewegen()                                         // Sorgt dafür das die Schüsse sich von unten nach oben bewegen
    {
        for (Schuss& st : schuesse) {
            st.SchussY -= schussSpeed;
        }
    }
    void AsteroidenBewegen()                                    // Sorgt dafür das die Asteroiden sich von oben nach unten bewegen
    {
        for (Asteorid& ast : Asteroiden)
        {
           ast.AsteroidY = ast.AsteroidY + SpaceSpeed; 
           
        }
    }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void draw() override
    {
        if (spielAuswahl == 0) {
            SpaceHintergrund.draw(0, 0, 0, 1.0, 1.0);
            Logo.draw(40, 0, 1, 1.0, 1.0);                                                                          // Menü beim Start des Spiels  
            auswahlSpaceInvaders.draw_text_rel("Spielen", 500, 450, 1, 0.5, 0.5, 1, 1, Gosu::Color::WHITE);
            exitgame.draw_text_rel("Beenden", 500, 500, 1, 0.5, 0.5, 1, 1, Gosu::Color::WHITE);
            entwickler.draw_text_rel("Adrian Belz, Louis Rosewich, Jan Scharschmidt", 200, 590, 1, 0.5, 0.5, 1, 1, Gosu::Color::WHITE);
        }
        if (spielAuswahl == 1) 
        {
            SpaceHintergrund.draw(0, 0, 0, 1.0, 1.0);
            string score = to_string(Score);
            string nothit = to_string(ScoreNichtZerstoert);
            anzeigeScore.draw_text_rel("Score: " + score, 0, 0, 2, 0, 0, 1, 1, Gosu::Color::RED);                // Blendet den Score oben links ein
            
            if (Spielen) {
                Raumschiff.draw_rot(RaumschiffX, RaumschiffY, 2, rotation, 0.5, 0.5,0.1, 0.1);                    // Blendet das Raumschiff ein
                for (int ast = 0; ast < Asteroiden.size(); ast++) {
                    if (Asteroiden.at(ast).hit == false) {
                        graphics().draw_rect(Asteroiden.at(ast).AsteroidX, Asteroiden.at(ast).AsteroidY, Asteroiden.at(ast).AsteroidBreite, Asteroiden.at(ast).AsteroidHoehe, Asteroiden.at(ast).AsteroidFarbe, Asteroiden.at(ast).AsteroidPos);    // Blendet die Asteroiden ein
                        Asteroid.draw((Asteroiden.at(ast).AsteroidX - 10), (Asteroiden.at(ast).AsteroidY-30), Asteroiden.at(ast).AsteroidPos,0.5, 0.5);         
                    }
                }
                for (int st = 0; st < schuesse.size(); st++) {
                    if (schuesse.at(st).existent) {
                        graphics().draw_rect(schuesse.at(st).SchussX, schuesse.at(st).SchussY, schuesse.at(st).SchussBreite, schuesse.at(st).SchussHoehe, schuesse.at(st).SchussFarbe, schuesse.at(st).SchussHoehe);   // Blendet die Schüsse ein
                    }
                }
            }
            if (getroffen) {
                anzeigeRestart.draw_text_rel("Restart", 500, 300, 2, 0.5, 0.5, 2, 2, Gosu::Color::RED);                                                           // Zeigt den Restart-und Exit-Knopf wenn man getroffen wurde
                exitgame.draw_text_rel("Exit", 970, 20, 2, 0.5, 0.5, 1, 1, Gosu::Color::RED);
            }
        }
       
    }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Wird 60x pro Sekunde aufgerufen
    void update() override
    {
        mausX = input().mouse_x();            //Position der Maus
        mausY = input().mouse_y();

        if (spielAuswahl == 0) {
            if (mausX >= 400 && mausX <= 600 && mausY >= 430 && mausY <= 460 && input().down(Gosu::Button::MS_LEFT))   // Abfrage ob Spielen im Menü gedrückt wurde
            {   
                spielAuswahl = 1;                                                                                                
                Spielen = true;
                restart_game();
            }
            else if (mausX >= 400 && mausX <= 600 && mausY >= 480 && mausY <= 510 && input().down(Gosu::Button::MS_LEFT))
            {
                exit(1);
            }
        }

       
        if (spielAuswahl == 1)
        {
            hintergrundmusik.play(true);
            if (!getroffen)                                                                             // Alle 5 Punkte wird die Geschwindigkeit erhöht
            {
                if (Score % speedIncreaseAt == 0 && speedIncrease) {            
                    SpaceSpeed = SpaceSpeed * SpeedIncreaseFaktor;          
                    speedIncrease = false;
                }
                AsteroidenAnzahl--;
                schussZahl++;
                
                if ((input().down(Gosu::Button::KB_LEFT) || input().down(Gosu::Button::KB_A)) && RaumschiffX > 30 ) 
                {
                    RaumschiffX -= (SpaceSpeed + 2);                                                      // Steuerung des Raumschiffs nach links                                                
                }
                else if ((input().down(Gosu::Button::KB_RIGHT) || input().down(Gosu::Button::KB_D)) && RaumschiffX < 970)
                {
                    RaumschiffX += SpaceSpeed + 2;                                                        // Steuerung des Raumschiffs nach rechts                                                  
                }
                if (AsteroidenAnzahl <= 1) {
                    AsteroidenAnzahl = 20;                                                                // verlangsamt das Spawnen der Asteroiden
                    erstelleAsteroid(Asteroiden);    
                }
                if (input().down(Gosu::Button::KB_SPACE)&& schussZahl>=10) {
                    schuesse.push_back(erstelleSchuss(RaumschiffX, RaumschiffY));                         // lässt Schüsse beim betätigen der Leertaste spawnen
                    schussZahl = 0;
                }
                FunktionenObjekte(); 
                SchussBewegen();
                AsteroidenBewegen();
            }
            else if (mausX >= 410 && mausX <= 590 && mausY >= 270 && mausY <= 330 && input().down(Gosu::Button::MS_LEFT)) {       // Restart Knopf wurde betätigt
                restart_game();  
                getroffen = false;
                restartSound.play(3);
                hintergrundmusik.play(true);
                return;
            }
            else if (mausX >= 900 && mausX <= 1000 && mausY >= 0 && mausY <= 100 && input().down(Gosu::Button::MS_LEFT)) {       //Spiel beenden
                exit(1);
            }
            if (getroffen)
            {
                hintergrundmusik.stop();
            }
        }
    }
};
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    GameWindow GameWindow;
    GameWindow.show();
}

