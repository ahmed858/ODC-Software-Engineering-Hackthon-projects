#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include<time.h>
using namespace std;
using namespace sf;
struct point
{
    int x, y;
};

int main()
{
    srand(time(0));

    /// Create the main window
    sf::RenderWindow app(sf::VideoMode(400, 533), "Doodle Game window");
    app.setFramerateLimit(120);
    auto image = sf::Image{};
    if (!image.loadFromFile("data/doodle.png"))
    {
        // Error handling...
    }
    app.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    ///data
    Sprite s_background,s_doodle,s_doodle1,s_plattform;
    Texture  t_background,t_doodle,t_platform,t_doodle1;

    if(!t_background.loadFromFile("data/background.png"))
    {
        cout<<"read background failed\n";
    }
    if(!t_doodle.loadFromFile("data/doodle.png"))
    {
        cout<<"read doodle failed\n";
    }
    if(!t_platform.loadFromFile("data/platform.png"))
    {
        cout<<"read platform failed\n";
    }
    s_background.setTexture(t_background);
    s_doodle.setTexture(t_doodle);
    s_plattform.setTexture(t_platform);

    if(!t_doodle1.loadFromFile("data/doodle1.png"))
    {
        cout<<"read doodle failed\n";
    }


    //load Font
    Font poor;
    if(poor.loadFromFile("data/Roboto-LightItalic.ttf")==false)
    {
        cout<<"Loading Failed"<<endl;
    }
    else
    {
        cout<<"Loading Success"<<endl;
    }

    //text object
    Text s;
    s.setFont(poor);

    s.setColor(Color(0,0,0));
    s.setCharacterSize(25);


    int score=0;
    string str="score 0";
    s.setString(str);



    point plat[11];

    for(int i=0; i<10; i++)
    {
        plat[i].x=rand()%400;
        plat[i].y=rand()%533;
    }

    int x=100,y=100,h=200;
    float dx=0,dy=0;







/// my habd

    int state=1;
    bool flag=0;

    Text over;
    over.setFont(poor);

    over.setColor(Color(0,0,0));
    over.setCharacterSize(55);

    over.setStyle(Text::Bold);
    over.setString("GAME OVER");
    over.setPosition(55,150);

    Text tt;
    tt.setFont(poor);

    tt.setColor(Color(0,0,0));
    tt.setCharacterSize(20);

    tt.setStyle(Text::Bold);
    tt.setString("Enter space to Play again..");
    tt.setPosition(55,300);

    /// Start the game loop
    while (app.isOpen())
    {
        /// Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            /// Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();


        }
        /// Clear screen
        app.clear();

        if(state==1)
        {
            cout<<"state1\n";
            s_doodle.setPosition(180,250);

            s.setString("Press Enter to Start....");
            s.setPosition(100,200);

            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                state=2;
            }
            app.draw(s_background);
            app.draw(s_doodle);
            app.draw(s);

        }
        if(state==2)
        {
            cout<<"state2\n";

            if(Keyboard::isKeyPressed(Keyboard::Left))
            {
                 s_doodle.setTexture(t_doodle);
                x-=3;
                x=(x+400)%400;

            }
            if(Keyboard::isKeyPressed(Keyboard::Right))
            {
                 s_doodle.setTexture(t_doodle1);
                x+=3;
                x%=400;
            }
            /// Draw the sprite
            dy+=.2;
            y+=dy;
            if(y>500)
            {
                dy=-10;
                cout<<"Hayy game over\n";
                state=3;
            }


            if(y<h)
            {

                for(int i=0; i<10; i++)
                {
                    y=h;
                    plat[i].y-=dy;
                    if(plat[i].y>533)
                    {
                        plat[i].y=0,plat[i].x=rand()%400;

                    }
                }
            }
            for(int i=0; i<10; i++)
            {
                if((plat[i].x<x+50) && (x+20<plat[i].x+68)
                        &&(plat[i].y<y+70) &&(y+70<plat[i].y+14) &&(dy>0))
                {
                    dy=-10;
                    //cout<<"score \n";
                }

            }
            if(dy<0)
            {
                score++;
            }
            else score--;


            s_doodle.setPosition(x,y);


            app.draw(s_background);
            app.draw(s_doodle);
            score=max(0,score);
            str = "Score: "+to_string(score);
            s.setPosition(0,0);
            s.setString(str);
            app.draw(s);
            for(int i=0; i<10; i++)
            {
                s_plattform.setPosition(plat[i].x,plat[i].y);
                app.draw(s_plattform);
            }

        }
        if(state==3)
        {
            for(int i=0; i<10; i++)
            {
                plat[i].x=rand()%400;
                plat[i].y=rand()%533;
            }
            x=100,y=100,h=200;
            dy=0;
            app.draw(s_background);
            s.setPosition(130,250);
            if(Keyboard::isKeyPressed(Keyboard::Space))
            {
                state=1;
            }

            app.draw(s);
            app.draw(tt);
            app.draw(over);

        }

        /// Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
