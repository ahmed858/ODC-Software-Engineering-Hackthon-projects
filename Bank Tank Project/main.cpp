#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include<string>
using namespace sf;
using namespace std;

class Bullet
{
public:
    CircleShape Rsasa;
    Vector2f velocity;
    float speed;

    Bullet()
        :velocity(0.f, 0.f), speed(20.f)
    {
        this->Rsasa.setFillColor(Color::Red);
        this->Rsasa.setRadius(10.f);
    };

};


int main()
{

    srand(time(0));
    RenderWindow window(VideoMode(1280, 960), "Fight");
    window.setFramerateLimit(60);

    ///sound buffers
    // bullet buffer player 1
    SoundBuffer bull_buff1;
    bull_buff1.loadFromFile("sound/shotsound1.wav");
    // bullet buffer player 2
    SoundBuffer bull_buff2;
    bull_buff2.loadFromFile("sound/shotsound1.wav");
    // back suound buffer
    SoundBuffer back_buffer;
    back_buffer.loadFromFile("sound/backsound.wav");
    /// music
    // shot music 1
    Sound shott1;
    shott1.setBuffer(bull_buff1);

    // shot music 2
    Sound shott2;
    shott2.setBuffer(bull_buff2);

    // backSound music 1
    Sound backSound;
    backSound.setBuffer(back_buffer);


    ///textures

    // background texure
    Texture t1;
    t1.loadFromFile("img/back.png");

    // bullet texure player1
    Texture tex_rasasa;
    tex_rasasa.loadFromFile("img/bullet_u.png");

    // bullet texure playr2
    Texture tex_rasasa2;
    tex_rasasa2.loadFromFile("img/bullet_u.png");

    // tank1 texure
    Texture dbaba1;


    // tank1 texure
    Texture dbaba2;


    //effect2 texure
    Texture effectTex2;
    //effect1 texure
    Texture effectTex1;


    //  to change dbaba in settings

    Texture player1SettingTex;
    player1SettingTex.loadFromFile("img/tank/0.png");//defult

    Texture player2SettingTex;
    player2SettingTex.loadFromFile("img/tank/0.png");//defult

    ///sprites
    Sprite background;
    background.setTexture(t1);

    vector<Sprite>effectsprites2;
    Sprite temp;
    vector<Sprite>effectsprites1;




    /// Shapes

    // playr1
    CircleShape circle1(50.f);
    circle1.setPosition(200, 420);
    //player2
    CircleShape circle2(50.f);
    circle2.setPosition(1000, 420);

    // retangle
    RectangleShape player1;
    player1.setTexture(&player1SettingTex);
    player1.setSize(Vector2f(530,560));
    player1.setPosition(0,200);

    RectangleShape player2;
    player2.setTexture(&player2SettingTex);
    player2.setSize(Vector2f(530,560));
    player2.setPosition(630,200);


    //aim 1
    CircleShape aim(3.f);
    aim.setPosition(circle1.getPosition().x + 100, circle1.getPosition().y+50);



    //aim 2
    CircleShape aim2(3.f);
    aim2.setPosition(circle2.getPosition().x, circle2.getPosition().y+50);


    /// varibles
    // playr1 variables
    Vector2f playerCenter;
    Vector2f mousePosWindow;
    Vector2f aimDir;
    Vector2f aimDirNorm;

    // player2 variables
    Vector2f playerCenter2;
    Vector2f mousePosWindow2;
    Vector2f aimDir2;
    Vector2f aimDirNorm2;

    //bullets
    Bullet b1;
    Bullet b2;
    std::vector<Bullet> bullets1;
    std::vector<Bullet> bullets2;

    //logic variable
    bool up = 0, down = 0, left = 0, right = 0;
    bool up2 = 0, down2 = 0, left2 = 0, right2 = 0;
    bool bullet1Colp2 = 0;
    bool bullet2Colp1 = 0;
    bool NEWGAME_hilight_main = 0;
    bool SETTINGS_hilight_main = 0, ABOUTUS_hilight_main = 0;;


    bool BACK_hilight_settings = 0;

    bool BACK_hilight_aboutus = 0;
    //  players Health
    int  player1Health = 100, player2Health = 100;

    /// index tank textures
    int p1_idx=0;
    int p2_idx=0;


    dbaba1.loadFromFile("img/tank"+to_string(p1_idx)+"/tank_u.png");
    dbaba2.loadFromFile("img/tank"+to_string(p2_idx)+"/tank_u.png");
    circle1.setTexture(&dbaba1);
    circle2.setTexture(&dbaba2);

    /// code state
    int state = 1;


    ///Fonts
    Font f;
    f.loadFromFile("Roboto-Bold.ttf");

    ///Text

    // for player 1 health text
    Text text1;
    text1.setFont(f);
    text1.setFillColor(Color::Black);
    text1.setCharacterSize(40);
    text1.setPosition(50, 50);

    Text text2;
    text2.setFont(f);
    text2.setFillColor(Color::Black);
    text2.setCharacterSize(40);
    text2.setPosition(880, 50);

    // text for state 1 main
    Text NEWGAME, SETTINGS, ABOUTUS;
    NEWGAME.setFont(f);
    NEWGAME.setFillColor(Color::Black);
    NEWGAME.setCharacterSize(70);
    NEWGAME.setPosition(440, 300);
    NEWGAME.setString("PLAY");

    SETTINGS.setFont(f);
    SETTINGS.setFillColor(Color::Black);
    SETTINGS.setCharacterSize(70);
    SETTINGS.setPosition(340, 400);
    SETTINGS.setString("SETTINGS");

    ABOUTUS.setFont(f);
    ABOUTUS.setFillColor(Color::Black);
    ABOUTUS.setCharacterSize(70);
    ABOUTUS.setPosition(340, 500);
    ABOUTUS.setString("ABOUT US..");

    /// settings
    Text p1,p2;
    p1.setFont(f);
    p1.setFillColor(Color::Black);
    p1.setCharacterSize(70);
    p1.setPosition(0,100);
    p1.setString("Player 1");

    p2.setFont(f);
    p2.setFillColor(Color::Black);
    p2.setCharacterSize(70);
    p2.setPosition(630,100);
    p2.setString("Player 2");

    Text back;
    back.setFont(f);
    back.setFillColor(Color::Black);
    back.setCharacterSize(70);
    back.setPosition(0,860);
    back.setString("<- Back");

    Text back_aboutus;
    back_aboutus.setFont(f);
    back_aboutus.setFillColor(Color::Black);
    back_aboutus.setCharacterSize(70);
    back_aboutus.setPosition(0,860);
    back_aboutus.setString("<- Back");

    /// text about us in about us
    Text aboutus;

    aboutus.setFont(f);
    aboutus.setFillColor(Color::Black);
    aboutus.setCharacterSize(70);
    aboutus.setPosition(530, 280);
    aboutus.setOrigin(Vector2f(aboutus.getGlobalBounds().width /2,aboutus.getGlobalBounds().height /2));
    aboutus.setString("BANK TANK team:\n\t-Mohamed Ashraf\n\t-Ahmed Abd elazez\n\t-Najat Khalaf\n\t-Rodina Ahmed\n\t-Margo Emad");


    // mohamed ashraf state3
    Text gameOver;
    Text PlayAgain;
    // game over
    gameOver.setFont(f);
    gameOver.setFillColor(Color::Blue);
    gameOver.setPosition(300, 350);
    gameOver.setCharacterSize(80);
    // play again
    PlayAgain.setFont(f);
    PlayAgain.setString("Play Again");
    PlayAgain.setFillColor(Color::Black);
    PlayAgain.setPosition(500, 450);
    PlayAgain.setCharacterSize(50);

    // login game over
    bool retry;


    while (window.isOpen())
    {
        if (state == 1)
        {
            Event event;
            while (window.pollEvent(event))
            {

                if (event.type == Event::Closed)
                {
                    window.close();
                }


            }

            // play text
            NEWGAME_hilight_main = 0;
            if (NEWGAME.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
            {
                NEWGAME_hilight_main = 1;
            }

            if (NEWGAME_hilight_main)
            {
                NEWGAME.setFillColor(Color::Blue);
            }
            if (!NEWGAME_hilight_main)
            {
                backSound.play();
                NEWGAME.setFillColor(Color::Black);
            }
            // settings text
            SETTINGS_hilight_main = 0;
            if (SETTINGS.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
            {
                SETTINGS_hilight_main = 1;
            }

            if (SETTINGS_hilight_main)
            {
                SETTINGS.setFillColor(Color::Blue);
            }
            if (!SETTINGS_hilight_main)
            {

                SETTINGS.setFillColor(Color::Black);
            }
            // about us text;
            ABOUTUS_hilight_main = 0;
            if (ABOUTUS.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
            {
                ABOUTUS_hilight_main = 1;
            }

            if (ABOUTUS_hilight_main)
            {
                ABOUTUS.setFillColor(Color::Blue);
            }
            if (!ABOUTUS_hilight_main)
            {

                ABOUTUS.setFillColor(Color::Black);
            }
            if (NEWGAME_hilight_main && Mouse::isButtonPressed(Mouse::Left))
            {
                state = 2;
            }

            if (SETTINGS_hilight_main && Mouse::isButtonPressed(Mouse::Left))
            {
                state = 4;

            }

            if (ABOUTUS_hilight_main && Mouse::isButtonPressed(Mouse::Left))
            {
                state = 5;
            }

            window.clear();
            window.draw(background);
            window.draw(NEWGAME);
            window.draw(SETTINGS);
            window.draw(ABOUTUS);
            window.display();


        }

        if (state == 2)
        {
            Event event;
            while (window.pollEvent(event))
            {



                if (event.type == Event::Closed)
                {
                    window.close();
                }
                // player1  [circle1] pressing
                if (Keyboard::isKeyPressed(Keyboard::A))
                {
                    left = 1;
                }
                if (Keyboard::isKeyPressed(Keyboard::D))
                {
                    right = 1;

                }
                if (Keyboard::isKeyPressed(Keyboard::W))
                {
                    up = 1;
                }
                if (Keyboard::isKeyPressed(Keyboard::S))
                {
                    down = 1;
                }

                // player2  [circle2] pressing
                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    left2 = 1;

                }
                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    right2 = 1;

                }
                if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    up2 = 1;

                }
                if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    down2 = 1;

                }

                /// any button released
                if (event.type == Event::KeyReleased)
                {
                    // release player1 buttons
                    if (event.key.code == Keyboard::A)
                    {
                        left = 0;

                    }
                    if (event.key.code == Keyboard::D)
                    {
                        right = 0;

                    }
                    if (event.key.code == Keyboard::W)
                    {
                        up = 0;

                    }
                    if (event.key.code == Keyboard::S)
                    {
                        down = 0;

                    }
                    ///release player2 buttons
                    if (event.key.code == Keyboard::Left)
                    {
                        left2 = 0;

                    }
                    if (event.key.code == Keyboard::Right)
                    {
                        right2 = 0;

                    }
                    if (event.key.code == Keyboard::Up)
                    {
                        up2 = 0;

                    }
                    if (event.key.code == Keyboard::Down)
                    {
                        down2 = 0;

                    }
                }

            }
            /// Player 1 aiming
            playerCenter = Vector2f(circle1.getPosition().x + circle1.getRadius(), circle1.getPosition().y + circle1.getRadius());
            aimDir = aim.getPosition() - playerCenter;
            aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
            aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

            /// Player 2 aiming
            playerCenter2 = Vector2f(circle2.getPosition().x + circle2.getRadius(), circle2.getPosition().y + circle2.getRadius());
            aimDir2 = aim2.getPosition() - playerCenter2;
            aimDirNorm2.x = aimDir2.x / sqrt(pow(aimDir2.x, 2) + pow(aimDir2.y, 2));
            aimDirNorm2.y = aimDir2.y / sqrt(pow(aimDir2.x, 2) + pow(aimDir2.y, 2));

            /// player 1 Logic
            if (left)
            {
                if (tex_rasasa.loadFromFile("img/bullet_l.png") == false)
                {
                    cout << "bull\n";
                }
                dbaba1.loadFromFile("img/tank"+to_string(p1_idx)+"/tank_l.png");

                circle1.move(-10.f, 0.f);
                aim.move(-10.f, 0.f);
                aim.setPosition(circle1.getPosition().x, circle1.getPosition().y + 50);

            }
            if (right)
            {
                if (tex_rasasa.loadFromFile("img/bullet_r.png") == false)
                {
                    cout << "bull\n";
                }
                dbaba1.loadFromFile("img/tank"+to_string(p1_idx)+"/tank_r.png");

                circle1.move(10.f, 0.f);
                aim.move(10.f, 0.f);
                aim.setPosition(circle1.getPosition().x + 100, circle1.getPosition().y + 50);

            }
            if (up)
            {
                if (tex_rasasa.loadFromFile("img/bullet_u.png") == false)
                {
                    cout << "bull\n";
                }
                dbaba1.loadFromFile("img/tank"+to_string(p1_idx)+"/tank_u.png");

                circle1.move(0.f, -10.f);
                aim.move(0.f, -10.f);
                aim.setPosition(circle1.getPosition().x + 50, circle1.getPosition().y);

            }
            if (down)
            {
                if (tex_rasasa.loadFromFile("img/bullet_d.png") == false)
                {
                    cout << "bull\n";
                }
                dbaba1.loadFromFile("img/tank"+to_string(p1_idx)+"/tank_d.png");

                circle1.move(0.f, 10.f);
                aim.move(0.f, 10.f);
                aim.setPosition(circle1.getPosition().x + 50, circle1.getPosition().y + 100);
            }

            /// Player 2 Logic
            if (left2)
            {
                if (tex_rasasa2.loadFromFile("img/bullet_l.png") == false)
                {
                    cout << "img/bull\n";
                }

                dbaba2.loadFromFile("img/tank"+to_string(p2_idx)+"/tank_l.png");
                circle2.move(-10.f, 0.f);
                aim2.move(-10.f, 0.f);
                aim2.setPosition(circle2.getPosition().x, circle2.getPosition().y + 50);


            }
            if (right2)
            {
                if (tex_rasasa2.loadFromFile("img/bullet_r.png") == false)
                {
                    cout << "bull\n";
                }
                dbaba2.loadFromFile("img/tank"+to_string(p2_idx)+"/tank_r.png");
                circle2.move(10.f, 0.f);
                aim2.move(10.f, 0.f);
                aim2.setPosition(circle2.getPosition().x + 100, circle2.getPosition().y + 50);

            }
            if (up2)
            {
                if (tex_rasasa2.loadFromFile("img/bullet_u.png") == false)
                {
                    cout << "bull\n";
                }
                dbaba2.loadFromFile("img/tank"+to_string(p2_idx)+"/tank_u.png");
                circle2.move(0.f, -10.f);
                aim2.move(0.f, -10.f);
                aim2.setPosition(circle2.getPosition().x + 50, circle2.getPosition().y);
            }
            if (down2)
            {
                if (tex_rasasa2.loadFromFile("img/bullet_d.png") == false)
                {
                    cout << "bull\n";
                }
                dbaba2.loadFromFile("img/tank"+to_string(p2_idx)+"/tank_d.png");
                circle2.move(0.f, 10.f);
                aim2.move(0.f, 10.f);
                aim2.setPosition(circle2.getPosition().x + 50, circle2.getPosition().y + 100);
            }

            // Collide players
            if (circle1.getGlobalBounds().intersects(circle2.getGlobalBounds()))
            {
                circle2.move(0.f, -10.f);//u
                circle2.move(-10.f, 0.f);//l
            }

            if (circle2.getGlobalBounds().intersects(circle1.getGlobalBounds()))
            {
                circle1.move(0.f, 10.f);//d
                circle1.move(10.f, 0.f);//r
            }
            /// player 1 shooting
            if (Keyboard::isKeyPressed(Keyboard::F))
            {
                shott1.play();

                b1.Rsasa.setPosition(playerCenter);
                b1.Rsasa.setTexture(&tex_rasasa);
                b1.velocity = aimDirNorm * b1.speed;
                bullets1.push_back(Bullet(b1));
            }
            for (size_t i = 0; i < bullets1.size(); i++)
            {
                bullets1[i].Rsasa.move(bullets1[i].velocity);
                if (bullets1[i].Rsasa.getPosition().x< 0 || bullets1[i].Rsasa.getPosition().x> window.getSize().x
                        || bullets1[i].Rsasa.getPosition().y <0 || bullets1[i].Rsasa.getPosition().y > window.getSize().y)
                {
                    bullets1.erase(bullets1.begin() + i);
                }

                // collision bullets`s player 1 with player 2
                // player 1 shoot player 2
                for (int i = 0; i < bullets1.size(); i++)
                {
                    if (circle2.getGlobalBounds().intersects(bullets1[i].Rsasa.getGlobalBounds()))
                    {
                        player2Health--;
                        cout << "player 2: " << endl;
                        cout << "ooOOOH my health: " << player2Health << endl;
                        bullet1Colp2 = 1;
                        bullets1.erase(bullets1.begin() + i);

                        /// should create any animations
                        break;/// if in impossible case
                    }
                }
            }



            /// player 2 shooting
            if (Keyboard::isKeyPressed(Keyboard::K))
            {
                shott2.play();
                b2.Rsasa.setPosition(playerCenter2);
                b2.Rsasa.setTexture(&tex_rasasa2);
                b2.velocity = aimDirNorm2 * b2.speed;
                bullets2.push_back(Bullet(b2));
            }

            for (size_t i = 0; i < bullets2.size(); i++)
            {
                bullets2[i].Rsasa.move(bullets2[i].velocity);

                if (bullets2[i].Rsasa.getPosition().x< 0 || bullets2[i].Rsasa.getPosition().x> window.getSize().x
                        || bullets2[i].Rsasa.getPosition().y <0 || bullets2[i].Rsasa.getPosition().y > window.getSize().y)
                {
                    bullets2.erase(bullets2.begin() + i);
                }
                // collision bullets`s player 2 with player 1
                // player 2 shoot player 1
                for (int i = 0; i < bullets2.size(); i++)
                {
                    if (circle1.getGlobalBounds().intersects(bullets2[i].Rsasa.getGlobalBounds()))
                    {
                        player1Health--;
                        cout << "player 1: " << endl;
                        cout << "ooOOOH my health: " << player1Health << endl;
                        bullet2Colp1 = 1;
                        bullets2.erase(bullets2.begin() + i);
                        /// should create any animations
                        break;/// if in impossible case
                    }
                }
            }

            /// inialize vector all time to erase it
            for (int i = 0; i <= 13; i++)
            {
                effectTex2.loadFromFile("img/effect1/" + to_string(i) + ".png");
                temp.setTexture(effectTex2);
                effectsprites2.push_back(temp);
            }
            effectsprites1=effectsprites2;

            /// collision
            // collision bullets`s player 1 with player 2
            // player 1 shoot player 2
            for (int i = 0; i < bullets1.size(); i++)
            {
                if (circle2.getGlobalBounds().intersects(bullets1[i].Rsasa.getGlobalBounds()))
                {
                    player2Health--;
                    cout << "player 2: " << endl;
                    cout << "ooOOOH my health: " << player2Health << endl;
                    bullet1Colp2 = 1;
                    bullets1.erase(bullets1.begin() + i);
                    /// should create any animations
                    break;/// if in impossible case
                }
            }
            // collision bullets`s player 2 with player 1
            // player 2 shoot player 1
            for (int i = 0; i < bullets2.size(); i++)
            {
                if (circle1.getGlobalBounds().intersects(bullets2[i].Rsasa.getGlobalBounds()))
                {
                    player1Health--;
                    cout << "player 1: " << endl;
                    cout << "ooOOOH my health: " << player1Health << endl;
                    bullet2Colp1 = true;
                    bullets2.erase(bullets2.begin() + i);
                    /// should create any animations
                    break;/// if in impossible case
                }
            }

            /// check the winer
            if (player1Health <= 0)
            {
                gameOver.setString("Player 2 is winner");
                state = 3;
            }
            if (player2Health <= 0)
            {
                gameOver.setString("Player 1 is winner");
                state = 3;

            }
            // draw
            window.clear();
            window.draw(background);
            window.draw(circle1);
            window.draw(circle2);
            //window.draw(aim);
            ///draw effect


            if (bullet1Colp2)
            {

                for (int i = 0; i <= 13; i++)
                {
                    effectsprites2[i].setPosition(circle2.getPosition());
                    window.draw(effectsprites2[i]);
                    //effectsprites.erase(effectsprites.begin()+i);

                }
                bullet1Colp2 = 0;

            }

            if (bullet2Colp1)
            {

                for (int i = 0; i <= 13; i++)
                {
                    effectsprites1[i].setPosition(circle1.getPosition());
                    window.draw(effectsprites1[i]);
                    //effectsprites.erase(effectsprites.begin()+i);

                }
                bullet2Colp1 = 0;

            }
            /// draw text
            text1.setString("Player 1 health: " + to_string(player1Health));
            text2.setString("Player 2 health: " + to_string(player2Health));
            window.draw(text1);
            window.draw(text2);



            /// drawing player 1 bullets
            for (size_t i = 0; i < bullets1.size(); i++)
            {
                window.draw(bullets1[i].Rsasa);
                if (bullets1[i].Rsasa.getPosition().x< 0 || bullets1[i].Rsasa.getPosition().x> window.getSize().x
                        || bullets1[i].Rsasa.getPosition().y <0 || bullets1[i].Rsasa.getPosition().y > window.getSize().y)
                {
                    bullets1.erase(bullets1.begin() + i);
                }
            }

            /// drawing player 2 bullets
            for (size_t i = 0; i < bullets2.size(); i++)
            {
                window.draw(bullets2[i].Rsasa);
                if (bullets2[i].Rsasa.getPosition().x< 0 || bullets2[i].Rsasa.getPosition().x> window.getSize().x
                        || bullets2[i].Rsasa.getPosition().y <0 || bullets2[i].Rsasa.getPosition().y > window.getSize().y)
                {
                    bullets2.erase(bullets2.begin() + i);
                }
            }

            window.display();
        }

        // mohamed ashraf state 3 code
        if (state == 3)
        {

            // we need to reintilize all variables here
            player1Health = 100;
            player2Health = 100;
            bullets1.clear();
            bullets2.clear();
            circle1.setPosition(200, 420);
            circle2.setPosition(1000, 420);

            Event event;
            while (window.pollEvent(event))
            {

                if (event.type == Event::Closed)
                {
                    window.close();
                }
                retry = 0;
                if (PlayAgain.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
                {
                    retry = 1;
                }
                if (retry)
                {
                    PlayAgain.setFillColor(Color::Blue);
                }
                if (!retry)
                {
                    PlayAgain.setFillColor(Color::Black);
                }
                if (retry && Mouse::isButtonPressed(Mouse::Left))
                {
                    state = 2;
                }

            }

            window.clear();
            window.draw(background);
            window.draw(gameOver);
            window.draw(PlayAgain);
            window.display();
        }
        if(state==4)
        {
            //settings

            Event event;
            while (window.pollEvent(event))
            {

                if (event.type == Event::Closed)
                {
                    window.close();
                }
                if(event.type==Event ::KeyPressed)
                {

                    if(event.key.code == Keyboard::Left)
                    {

                        p2_idx = ((p2_idx -1)+3)%3;
                        player1SettingTex.loadFromFile("img/tank/"+to_string(p1_idx)+".png");
                        player1.setTexture(&player1SettingTex);
                        player1.setSize(Vector2f(530,560));

                    }
                    if(event.key.code == Keyboard::Right)
                    {
                        p2_idx++;
                        p2_idx%=3;

                    }
                    if(event.key.code == Keyboard::A)
                    {
                        p1_idx = ((p1_idx -1)+3)%3;

                    }
                    if(event.key.code == Keyboard::D)
                    {
                        p1_idx++;
                        p1_idx%=3;




                    }
                    player1SettingTex.loadFromFile("img/tank/"+to_string(p1_idx)+".png");
                    player1.setTexture(&player1SettingTex);
                    player1.setSize(Vector2f(530,560));

                    player2SettingTex.loadFromFile("img/tank/"+to_string(p2_idx)+".png");
                    player2.setTexture(&player2SettingTex);
                    player2.setSize(Vector2f(530,560));

                }
            }


            BACK_hilight_settings = 0;
            if (back.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
            {
                BACK_hilight_settings = 1;
            }
            if (BACK_hilight_settings)
            {
                back.setFillColor(Color::Blue);
            }
            if (!BACK_hilight_settings)
            {
                back.setFillColor(Color::Black);
            }

            if (BACK_hilight_settings && Mouse::isButtonPressed(Mouse::Left))
            {
                /// here
                dbaba1.loadFromFile("img/tank"+to_string(p1_idx)+"/tank_u.png");
                dbaba2.loadFromFile("img/tank"+to_string(p2_idx)+"/tank_u.png");
                state = 1;
            }


            window.clear();
            window.draw(background);
            window.draw(player1);
            window.draw(player2);
            window.draw(p1);
            window.draw(p2);
            window.draw(back);

            window.display();

        }

        if(state==5)
        {
            Event event;
            while (window.pollEvent(event))
            {

                if (event.type == Event::Closed)
                {
                    window.close();
                }
            }
            BACK_hilight_aboutus = 0;
            if (back_aboutus.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
            {
                BACK_hilight_aboutus = 1;
            }
            if (BACK_hilight_aboutus)
            {
                back_aboutus.setFillColor(Color::Blue);
            }
            if (!BACK_hilight_aboutus)
            {
                back_aboutus.setFillColor(Color::Black);
            }

            if (BACK_hilight_aboutus && Mouse::isButtonPressed(Mouse::Left))
            {

                state = 1;
            }
            window.clear();
            window.draw(background);
            window.draw(aboutus);
            window.draw(back_aboutus);
            window.display();
        }

    }

    return 0;

}
