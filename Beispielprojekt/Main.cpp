#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


struct Asteorid {
    const int AsteroidBreite = 30;
    const int AsteroidLaenge = 30;
    const int AsteroidPos = 1;
    const Gosu::Color AsteroidFarbe = Gosu::Color::GRAY;
    double AsteroidX;
    double AsteroidY;
    bool hit = false;
   
};

struct Schuss
{
    const int SchussBreite = 5;
    const int SchussHoehe = 3;
    const int SchussPos = 1;
    const Gosu::Color SchussFarbe = Gosu::Color::RED;
    double SchussX;
    double SchussY;
    bool existent = true;
};
Schuss neuerStachel(double x,double y) {
    Schuss st;
    st.SchussX = x;
    st.SchussY = y;
    return st;
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GameWindow : public Gosu::Window
{
    Gosu::Font exitgame = { 30 };
    Gosu::Font auswahl_spaceInvaders = {30};        //Font lässt variablen anzeigen  30 ist die größe
    int spiel_auswahl = 0;
    double maus_x;
    double maus_y;
    Gosu::Image Raumschiff;
    Gosu::Font anzeige_score_Space = { 30 };
    Gosu::Font anzeige_restart_Space = { 30 };
    Gosu::Font anzeige_start_Space = { 30 };
    const double SpaceBeeX = 50;
    bool spielstatus = false;
    bool initial_start;
    bool gestorben;
    double  SpaceBeeY =400;
    int SpaceScore;
    int rotationSpace = 270;
    vector<Asteorid> Asteroiden;
    vector<Schuss> stachel;
    double SpaceSpeed = 3;
    bool SpaceSpielen = false;
    int AstAnzahl = 0;
    double stachelSpeed = 5;
    int ScoreNichtZerstoert;
    double stachelspeed = 4;
    int stachelzahl;
    double SpaceSpeedincrease = 1.08;
    bool Space_Speed_increase = false;
    int Space_Speed_increase_at = 5;
    Gosu::Image SpaceHintergrund;
    Gosu::Image Asteroid;
    Gosu::Image Logo;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

public:

    GameWindow() : Window(1000, 600), Raumschiff("rakete.png"),SpaceHintergrund("weltraum.png"), Asteroid("asteroid2.png"), Logo("logo.png")
    {
        set_caption("Space Invaders");
    }

  ///////////////////////// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void restart_space() {
        Asteroiden.clear(); 
        stachel.clear();
        SpaceBeeY = 400;
        SpaceScore = 0;
        SpaceSpeed = 3;
        gestorben = false;
        SpaceSpielen = true;
        AstAnzahl = 0;
        ScoreNichtZerstoert = 0;
        stachelSpeed = 4;
        stachelzahl = 0;

    }
    void erstelleAsteroid(vector<Asteorid>& AstVect) {
        double y = Gosu::random(0, 800);
        Asteorid ast;
        ast.AsteroidX = 1000;
        ast.AsteroidY = y;
        AstVect.push_back(ast);
    }  
    void AstInRange() {                 
        vector<Asteorid> hilfsvector;
        vector<Schuss> helpStachel;
        bool raus = false;
        bool AstRaus = false;  
        for (int ast = 0; ast < Asteroiden.size(); ast++) {
            if (Asteroiden.at(ast).AsteroidX <= SpaceBeeX + 30 && Asteroiden.at(ast).AsteroidY >= SpaceBeeY - 40 && Asteroiden.at(ast).AsteroidY <= SpaceBeeY + 40) {
                gestorben = true;
                Asteroiden.at(ast).hit = true;
                break;
            }
            else if (Asteroiden.at(ast).AsteroidX <= 0) {
                ScoreNichtZerstoert++;
                Space_Speed_increase = true;
                Asteroiden.at(ast).hit = true;
            }
            else {
                for (int st = 0; st < stachel.size(); st++) {
                    if (stachel.at(st).SchussX >= Asteroiden.at(ast).AsteroidX && stachel.at(st).SchussX <= Asteroiden.at(ast).AsteroidX + Asteroiden.at(ast).AsteroidBreite
                        && stachel.at(st).SchussY <= (Asteroiden.at(ast).AsteroidY+ Asteroiden.at(ast).AsteroidLaenge + stachel.at(st).SchussHoehe)&& (stachel.at(st).SchussY >= (Asteroiden.at(ast).AsteroidY ))) {
                        SpaceScore++;
                        Asteroiden.at(ast).hit = true;
                        stachel.at(st).existent = false;
                    }                      
                    else if (stachel.at(st).SchussX >= 900.0) {
                        stachel.at(st).existent = false;
                    }
                    else {

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
        for (int st = 0; st < stachel.size(); st++) {
            if (stachel.at(st).existent == false) {
            }
            else {
                helpSt.push_back(stachel.at(st));
            }
        }
        stachel.clear();
        for (Schuss st : helpSt) {
            stachel.push_back(st);
        }
    }
    void StachelBewegen() {
        for (Schuss& st : stachel) {
            st.SchussX += stachelspeed;
        }
    }
    void AsteroidenBewegen() {
        for (Asteorid& ast : Asteroiden) {
            ast.AsteroidX = ast.AsteroidX - SpaceSpeed;

            if ((SpaceBeeX <= (ast.AsteroidX + (ast.AsteroidBreite / 2)) && SpaceBeeX >= (ast.AsteroidX - (ast.AsteroidBreite / 2))) &&
                (SpaceBeeY <= (ast.AsteroidY - (ast.AsteroidLaenge / 2)) && SpaceBeeY >= (ast.AsteroidY + (ast.AsteroidLaenge / 2))))
            {
                gestorben = true;
                break;
            }
        }
    }
  
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void draw() override
    {
        if (spiel_auswahl == 0) {
            SpaceHintergrund.draw(0, 0, 0, 1.0, 1.0);
            Logo.draw(40, 0, 1, 1.0, 1.0);
            auswahl_spaceInvaders.draw_text_rel("Spielen", 515, 500, 1, 0.5, 0.5, 1, 1, Gosu::Color::GREEN);                                                     // Menü beim Start des Spiels              
        }
 
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (spiel_auswahl == 1) {
            SpaceHintergrund.draw(0, 0, 0, 1.0, 1.0);
            string score = to_string(SpaceScore);
            string nothit = to_string(ScoreNichtZerstoert);
            anzeige_score_Space.draw_text_rel("Score: " + score, 0, 0, 2, 0, 0, 1, 1, Gosu::Color::GREEN);

            if (SpaceSpielen) {
                Raumschiff.draw_rot(SpaceBeeX, SpaceBeeY, 2, rotationSpace
                    , 0.5, 0.5,
                    0.1, 0.1
                );
                for (int ast = 0; ast < Asteroiden.size(); ast++) {
                    if (Asteroiden.at(ast).hit == false) {
                        graphics().draw_rect(Asteroiden.at(ast).AsteroidX, Asteroiden.at(ast).AsteroidY, Asteroiden.at(ast).AsteroidLaenge, Asteroiden.at(ast).AsteroidBreite, Asteroiden.at(ast).AsteroidFarbe, Asteroiden.at(ast).AsteroidPos);
                        Asteroid.draw((Asteroiden.at(ast).AsteroidX - 10), (Asteroiden.at(ast).AsteroidY-30), Asteroiden.at(ast).AsteroidPos,0.5, 0.5);

                    }
                }
                for (int st = 0; st < stachel.size(); st++) {
                    if (stachel.at(st).existent) {
                        graphics().draw_rect(stachel.at(st).SchussX, stachel.at(st).SchussY, stachel.at(st).SchussBreite, stachel.at(st).SchussHoehe, stachel.at(st).SchussFarbe, stachel.at(st).SchussHoehe);
                    }
                }
            }
            if (gestorben) {//!SpaceSpielen &&               
                anzeige_restart_Space.draw_text_rel("Restart", 500, 300, 2, 0.5, 0.5, 2, 2, Gosu::Color::GREEN);
                exitgame.draw_text_rel("Exit", 950, 20, 2, 0.5, 0.5, 1, 1, Gosu::Color::RED);
            }
        }
       
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Wird 60x pro Sekunde aufgerufen
    void update() override
    {
        maus_x = input().mouse_x();            //Position Maus im Menü
        maus_y = input().mouse_y();

        /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (spiel_auswahl == 0) {
            if (maus_x >= 430 && maus_x <= 600 && maus_y >= 400 && maus_y <= 600 && input().down(Gosu::Button::MS_LEFT)) {     
                spiel_auswahl = 1;                                                                                                // Menüauswahl
                SpaceSpielen = true;
                restart_space();
               
            }
        }
        /// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       
        if (spiel_auswahl == 1) {
            if (!gestorben) {
                if (SpaceScore % Space_Speed_increase_at == 0 && Space_Speed_increase) {
                    SpaceSpeed = SpaceSpeed * SpaceSpeedincrease;
                    Space_Speed_increase = false;
                }
                AstAnzahl--;
                stachelzahl++;
                
                if (input().down(Gosu::Button::KB_UP)) {
                    SpaceBeeY -= (SpaceSpeed + 2);
                }
                else if (input().down(Gosu::Button::KB_DOWN)) {
                    SpaceBeeY += SpaceSpeed + 2;
                }
                if (AstAnzahl <= 1) {
                    AstAnzahl = 30;
                    erstelleAsteroid(Asteroiden);
                    
                       
                }
                if (input().down(Gosu::Button::KB_SPACE)&& stachelzahl>=20) {
                    stachel.push_back(neuerStachel(SpaceBeeX, SpaceBeeY));
                    stachelzahl = 0;
                }
                AstInRange(); 
                StachelBewegen();
                AsteroidenBewegen();
            }
            else if (maus_x >= 410 && maus_x <= 590 && maus_y >= 270 && maus_y <= 330 && !spielstatus && input().down(Gosu::Button::MS_LEFT) && !initial_start) {    // Restart Knopf wurde betätigt
                restart_space();  
                gestorben = false;
                return;
            }
            else if (maus_x >= 900 && maus_x <= 1000 && maus_y >= 0 && maus_y <= 100 && input().down(Gosu::Button::MS_LEFT)) {               //Spiel beenden
                exit(3);
            }
            if (SpaceBeeY > 600 || SpaceBeeY< 0)              // Abfrage, ob man außerhalb den Bildschirms geflogen ist falls ja Game Over
                gestorben = true;
        }
    }
};


int main()
{
    GameWindow GameWindow;
    GameWindow.show();
}

