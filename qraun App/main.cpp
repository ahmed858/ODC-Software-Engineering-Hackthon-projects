#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std ;
using namespace sf ;
int main()
{
    int cnt=0;
    string dir = "0.jpg";

    RenderWindow app (VideoMode(476,710),"Qraun ");

    Texture texture;
    Sprite img;

    if(!texture.loadFromFile(dir))
    {
        cout<<"Some error\n";
    }

    img.setTexture(texture);



    while(app.isOpen())
    {

        Event ev;

        while(app.pollEvent(ev))
        {

            if(ev.type == Event::Closed)
            {
                app.close();
            }

            if(ev.type == Event::KeyPressed)
            {
                if(ev.key.code == Keyboard::Right)
                {
                    cnt++;
                    cnt%=10;
                    dir = to_string(cnt) ;
                    cout<<cnt<<endl;

                }
                if(ev.key.code == Keyboard::Left)
                {
                    cnt--;
                    cnt = (cnt+10)%10;
                    dir = to_string(cnt) ;
                    cout<<cnt<<endl;

                }
                dir+= ".jpg";

            }
            if(!texture.loadFromFile(dir))
            {
                cout<<"Some error\n";
            }

            img.setTexture(texture);
        }
        app.draw(img);
        app.display();
    }

    return 507;
}
