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
    const int SchussBreite = 10;
    const int SchussHoehe = 3;
    const int SchussPos = 1;
    const Gosu::Color SchussFarbe = Gosu::Color::RED;
    double SchussX;
    double SchussY;
    bool existent = true;
};
Schuss neuerSchuss(double x,double y) {
    Schuss st;
    st.SchussX = x;
    st.SchussY = y;
    return st;
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GameWindow : public Gosu::Window
{ 
    Gosu::Image SpaceHintergrund;
    Gosu::Image Asteroid;
    Gosu::Image Logo;
    Gosu::Image Raumschiff;
    Gosu::Font exitgame = { 30 };                              
    Gosu::Font auswahl_spaceInvaders = {30};       
    Gosu::Font anzeige_score_Space = { 30 };
    Gosu::Font anzeige_restart_Space = { 30 };
    Gosu::Font anzeige_start_Space = { 30 };
    int spielAuswahl = 0;
    double mausX;
    double mausY;
    const double RaumschiffX = 50;
    double  RaumschiffY =400;
    bool spielstatus = false;
    bool initial_start;
    bool gestorben;
    int SpaceScore;
    int rotationSpace = 270;
    vector<Asteorid> Asteroiden;
    vector<Schuss> schuesse;
    double SpaceSpeed = 3;
    bool SpaceSpielen = false;
    int AsteroidenAnzahl = 0;
    double schussSpeed = 5;
    int ScoreNichtZerstoert;
    double schussspeed = 4;
    int schussZahl;
    double SpaceSpeedincrease = 1.08;
    bool Space_Speed_increase = false;
    int Space_Speed_increase_at = 5;
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

public:
    GameWindow() : Window(1000, 600), Raumschiff("rakete.png"),SpaceHintergrund("weltraum.png"), Asteroid("asteroid2.png"), Logo("logo.png")
    {
        set_caption("Space Invaders");
    }
    void restart_space() {
        Asteroiden.clear(); 
        schuesse.clear();
        RaumschiffY = 400;
        SpaceScore = 0;
        SpaceSpeed = 3;
        gestorben = false;
        SpaceSpielen = true;
        AsteroidenAnzahl = 0;
        ScoreNichtZerstoert = 0;
        schussSpeed = 4;
        schussZahl = 0;

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
        vector<Schuss> hilfSchuss;
        bool raus = false;
        bool AstRaus = false;  
        for (int ast = 0; ast < Asteroiden.size(); ast++) {
            if (Asteroiden.at(ast).AsteroidX <= RaumschiffX + 30 && Asteroiden.at(ast).AsteroidY >= RaumschiffY - 40 && Asteroiden.at(ast).AsteroidY <= RaumschiffY + 40) {
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
                for (int st = 0; st < schuesse.size(); st++) {
                    if (schuesse.at(st).SchussX >= Asteroiden.at(ast).AsteroidX && schuesse.at(st).SchussX <= Asteroiden.at(ast).AsteroidX + Asteroiden.at(ast).AsteroidBreite
                        && schuesse.at(st).SchussY <= (Asteroiden.at(ast).AsteroidY+ Asteroiden.at(ast).AsteroidLaenge + schuesse.at(st).SchussHoehe)&& (schuesse.at(st).SchussY >= (Asteroiden.at(ast).AsteroidY ))) {
                        SpaceScore++;
                        Asteroiden.at(ast).hit = true;
                        schuesse.at(st).existent = false;
                    }                      
                    else if (schuesse.at(st).SchussX >= 900.0) {
                        schuesse.at(st).existent = false;
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
            st.SchussX += schussspeed;
        }
    }
    void AsteroidenBewegen() {
        for (Asteorid& ast : Asteroiden) {
            ast.AsteroidX = ast.AsteroidX - SpaceSpeed;

            if ((RaumschiffX <= (ast.AsteroidX + (ast.AsteroidBreite / 2)) && RaumschiffX >= (ast.AsteroidX - (ast.AsteroidBreite / 2))) &&
                (RaumschiffY <= (ast.AsteroidY - (ast.AsteroidLaenge / 2)) && RaumschiffY >= (ast.AsteroidY + (ast.AsteroidLaenge / 2))))
            {
                gestorben = true;
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
            auswahl_spaceInvaders.draw_text_rel("Spielen", 515, 500, 1, 0.5, 0.5, 1, 1, Gosu::Color::GREEN);                                                     // Menü beim Start des Spiels              
        }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (spielAuswahl == 1) {
            SpaceHintergrund.draw(0, 0, 0, 1.0, 1.0);
            string score = to_string(SpaceScore);
            string nothit = to_string(ScoreNichtZerstoert);
            anzeige_score_Space.draw_text_rel("Score: " + score, 0, 0, 2, 0, 0, 1, 1, Gosu::Color::GREEN);

            if (SpaceSpielen) {
                Raumschiff.draw_rot(RaumschiffX, RaumschiffY, 2, rotationSpace
                    , 0.5, 0.5,
                    0.1, 0.1
                );
                for (int ast = 0; ast < Asteroiden.size(); ast++) {
                    if (Asteroiden.at(ast).hit == false) {
                        graphics().draw_rect(Asteroiden.at(ast).AsteroidX, Asteroiden.at(ast).AsteroidY, Asteroiden.at(ast).AsteroidLaenge, Asteroiden.at(ast).AsteroidBreite, Asteroiden.at(ast).AsteroidFarbe, Asteroiden.at(ast).AsteroidPos);
                        Asteroid.draw((Asteroiden.at(ast).AsteroidX - 10), (Asteroiden.at(ast).AsteroidY-30), Asteroiden.at(ast).AsteroidPos,0.5, 0.5);

                    }
                }
                for (int st = 0; st < schuesse.size(); st++) {
                    if (schuesse.at(st).existent) {
                        graphics().draw_rect(schuesse.at(st).SchussX, schuesse.at(st).SchussY, schuesse.at(st).SchussBreite, schuesse.at(st).SchussHoehe, schuesse.at(st).SchussFarbe, schuesse.at(st).SchussHoehe);
                    }
                }
            }
            if (gestorben) {//!SpaceSpielen &&               
                anzeige_restart_Space.draw_text_rel("Restart", 500, 300, 2, 0.5, 0.5, 2, 2, Gosu::Color::GREEN);
                exitgame.draw_text_rel("Exit", 950, 20, 2, 0.5, 0.5, 1, 1, Gosu::Color::RED);
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
                SpaceSpielen = true;
                restart_space();
               
            }
        }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       
        if (spielAuswahl == 1) {
            if (!gestorben) {
                if (SpaceScore % Space_Speed_increase_at == 0 && Space_Speed_increase) {
                    SpaceSpeed = SpaceSpeed * SpaceSpeedincrease;
                    Space_Speed_increase = false;
                }
                AsteroidenAnzahl--;
                schussZahl++;
                
                if (input().down(Gosu::Button::KB_UP)) {
                    RaumschiffY -= (SpaceSpeed + 2);
                }
                else if (input().down(Gosu::Button::KB_DOWN)) {
                    RaumschiffY += SpaceSpeed + 2;
                }
                if (AsteroidenAnzahl <= 1) {
                    AsteroidenAnzahl = 30;
                    erstelleAsteroid(Asteroiden);
                    
                       
                }
                if (input().down(Gosu::Button::KB_SPACE)&& schussZahl>=20) {
                    schuesse.push_back(neuerSchuss(RaumschiffX, RaumschiffY));
                    schussZahl = 0;
                }
                AstInRange(); 
                SchussBewegen();
                AsteroidenBewegen();
            }
            else if (mausX >= 410 && mausX <= 590 && mausY >= 270 && mausY <= 330 && !spielstatus && input().down(Gosu::Button::MS_LEFT) && !initial_start) {    // Restart Knopf wurde betätigt
                restart_space();  
                gestorben = false;
                return;
            }
            else if (mausX >= 900 && mausX <= 1000 && mausY >= 0 && mausY <= 100 && input().down(Gosu::Button::MS_LEFT)) {               //Spiel beenden
                exit(3);
            }
            if (RaumschiffY > 600 || RaumschiffY< 0)              // Abfrage, ob man außerhalb den Bildschirms geflogen ist falls ja Game Over
                gestorben = true;
        }
    }
};
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    GameWindow GameWindow;
    GameWindow.show();
}

