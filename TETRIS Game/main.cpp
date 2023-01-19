#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;
const int ROWS=20;
const int COLS=10;

int field[ROWS][COLS];

struct Point
{
    int x,y;
} a[4],b[4];

int figures[7][4]=
{
    1,3,5,7, /// I
    2,4,5,7, /// Z
    3,5,4,7, /// S
    3,5,4,7, /// T
    2,3,5,7, /// L
    3,5,7,6, /// J
    2,3,4,5, ///O
};

bool check()
{
    for(int i=0; i<4; i++)
        if(a[i].x<0 ||a[i].x>=ROWS || a[i].y>=COLS)return 0;
        else if(field[a[i].y][a[i].x])return 0;

    return 1;
}

int main()
{
    srand(time(0));
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(320, 480), "TETRIS Game");

    // Load a sprite to display
    Texture t1,t2;
    t1.loadFromFile("data/background.png");
    t2.loadFromFile("data/tiles.png");
    Sprite sback(t1),stiles(t2);
    stiles.setTextureRect(IntRect(0,0,18,18));

    int dx=0;
    bool Rotate =0;
    int colorNum=1;

    float timer=0,delay=0.3;

    Clock clock;

    // Start     the game loop
    while (app.isOpen())
    {
        float time =clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;


        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {

                if(event.key.code==Keyboard::Space)Rotate=true;
                else if(event.key.code==Keyboard::Left)dx=-1;
                else if(event.key.code==Keyboard::Right)dx=1;
            }


        }
        if(Keyboard::isKeyPressed(Keyboard::Down))delay=0.05;

        ////////MOVE///////////
        for(int i=0; i<4; i++ )
        {
            b[i]=a[i];
            a[i].x+=dx;
        }
        if(!check())
            for(int i=0; i<4; i++)
                a[i]=b[i];

        ////////Rotate//////
        if(Rotate)
        {
            Point p = a[1];
            for(int i=0; i<4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if(!check())
                for(int i=0; i<4; i++)
                    a[i]=b[i];
        }

        ////////Tick///////////
        if(timer>delay)
        {
            for(int i=0; i<4; i++)
            {
                b[i]=a[i];
                a[i].y+=1;
            }
            if(!check())
            {
                for(int i=0; i<4; i++)
                {
                    field[b[i].y][b[i].x]=colorNum;
                }
                colorNum=1+rand()%7;
                int shapeNum = rand()%7;
                for(int i=0; i<4; i++)
                {
                    a[i].x=figures[shapeNum][i]%2;
                    a[i].y=figures[shapeNum][i]/2;
                }

            }
            timer=0;
        }

//////////chaeck lines////////
        int k=ROWS-1;
        for(int i=k; i>0; i--)
        {
            int count= 0;
            for(int j=0; j<COLS; j++)
            {
                if(field[i][j])count++;
                field[k][j]=field[i][j];
            }
            if(count<COLS)k--;

        }

        dx=0;
        Rotate=false;
        delay=.3;


        // Clear screen
        app.clear(Color::White);
        app.draw(sback);
        // Draw the sprites
        for(int i=0; i<ROWS; i++)
        {
            for(int j=0; j<COLS; j++)
            {
                if(field[i][j]==0)continue;
                stiles.setTextureRect(IntRect(field[i][j]*18,0,18,18));
                stiles.setPosition(j*18,i*18);
                app.draw(stiles);
            }
        }
        for(int i=0; i<4; i++)
        {
            stiles.setTextureRect(IntRect(colorNum*18,0,18,18));
            stiles.setPosition(a[i].x*18,a[i].y*18);
            app.draw(stiles);
        }

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
