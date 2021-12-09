#include <SFML/OpenGL.hpp>
#include "TextureManager.h"
#include <iostream>

int main() {
    RenderWindow window(VideoMode( 500, 896), "UserView");   // screen size is 2/3 resolution of iphone 6 screen

    bool findFriend = false;
    bool welcome = true;
    bool eventView = false;
    bool newFriends = false;
    int nextEvent = 1;
    TextureManager textures;
    textures.LoadTexture("Nightly logo");
    textures.LoadTexture("findFriends");
    textures.LoadTexture("doBase");
    textures.LoadTexture("dog park");
    textures.LoadTexture("Minecraft");
    textures.LoadTexture("poolParty");
    textures.LoadTexture("starGazing");
    textures.LoadTexture("study session");
    textures.LoadTexture("crescentMoon");
    textures.LoadTexture("boring");
    textures.LoadTexture("makeFriends");
    Font font;
    font.loadFromFile("srcImg/OpenSans-Regular.ttf");


    while (window.isOpen()) {      // currently infinite window

        window.clear();
        TextureManager textures;
        Event event;
        Event event2;

        while (window.pollEvent(event)){

            if (event.type == Event::Closed){
                window.close();
            }

            if (welcome) {

                Sprite sprite;
                sprite.setTexture(textures.GetTexture("NightlyWelcome"));
                sprite.setPosition(0.0f, 0.0f);
                window.draw(sprite);

                if (Mouse::isButtonPressed(Mouse::Left)){
                    findFriend = true;
                    welcome = false;
                }

                window.display();
            }
            else if (findFriend){

                window.clear();
                Sprite doBase;
                doBase.setTexture(textures.GetTexture("doBase"));
                doBase.setPosition(0.0f, 0.0f);
                window.draw(doBase);

                Sprite events1;
                Sprite events2;
                Sprite events3;

                events1.setTexture(textures.GetTexture("crescentMoon"));
                events2.setTexture(textures.GetTexture("crescentMoon"));
                events3.setTexture(textures.GetTexture("crescentMoon"));

                for (int i = 1; i < 4; i++) {
                    Text text;
                    text.setFont(font);
                    text.setCharacterSize(30);
                    text.setOutlineColor(Color::White);
                    text.setFillColor(Color::White);
                    text.setPosition(20.0f, 150.0f + (i*150)*1.0f);
                    string temp;
                    string eventName;
                    string friendsThere;

                    // set nextEvent based on ranking from graph algorithm

                    switch (nextEvent + 2) {                  // sets event name based on a 1 through 5 identification system
                        case 1:
                            eventName = "Pool Party";
                            break;
                        case 2:
                            eventName = "Stargazing";
                            break;
                        case 3:
                            eventName = "Dog Park Gathering";
                            break;
                        case 4:
                            eventName = "Study Session";
                            break;
                        case 5:
                            eventName = "Minecraft Meeting";
                            break;
                    }
                    temp = (char) (i + 48);
                    friendsThere = (char) (/*numoffrinds + */48);
                    text.setString(temp + ". " + eventName + "    F: " + friendsThere);
                    window.draw(text);
                }

                events1.setPosition(420.0f, 300.0f);
                window.draw(events1);
                events2.setPosition(420.0f, 450.0f);
                window.draw(events2);
                events3.setPosition(420.0f, 600.0f);
                window.draw(events3);

                window.display();

                if (Mouse::isButtonPressed(Mouse::Left)){
                    if (Mouse::getPosition(window).x > events1.getPosition().x && Mouse::getPosition(window).x < events1.getPosition().x + 80.0f && Mouse::getPosition(window).y > events1.getPosition().y && Mouse::getPosition(window).y < events1.getPosition().y + 50.0f) {
                        eventView = true;
                        findFriend = false;

                        // set nextEvent according to clicked sprite
                    }
                    else if (Mouse::getPosition(window).x > events1.getPosition().x && Mouse::getPosition(window).x < events1.getPosition().x + 80.0f && Mouse::getPosition(window).y > events2.getPosition().y && Mouse::getPosition(window).y < events2.getPosition().y + 50.0f) {
                        eventView = true;
                        findFriend = false;

                        // set nextEvent according to clicked sprite
                    }
                    else if (Mouse::getPosition(window).x > events1.getPosition().x && Mouse::getPosition(window).x < events1.getPosition().x + 80.0f && Mouse::getPosition(window).y > events3.getPosition().y && Mouse::getPosition(window).y < events3.getPosition().y + 50.0f) {
                        eventView = true;
                        findFriend = false;
                        // nextEvent = third ranked
                        // set nextEvent according to clicked sprite
                    }
                }

            }
            else if (eventView) {

                Sprite eventPicture;
                Sprite boring;
                Sprite makeFriends;

                switch (nextEvent + 4) {                  // sets event name based on a 1 through 5 identification system
                    case 1:
                        eventPicture.setTexture(textures.GetTexture("poolParty"));
                        break;
                    case 2:
                        eventPicture.setTexture(textures.GetTexture("starGazing"));
                        break;
                    case 3:
                        eventPicture.setTexture(textures.GetTexture("dog park"));
                        break;
                    case 4:
                        eventPicture.setTexture(textures.GetTexture("study session"));
                        break;
                    case 5:
                        eventPicture.setTexture(textures.GetTexture("Minecraft"));
                        break;
                }

                boring.setTexture(textures.GetTexture("boring"));
                boring.setPosition(50.0f, 600.0f);
                window.draw(boring);

                makeFriends.setTexture(textures.GetTexture("makeFriends"));
                makeFriends.setPosition(300.0f, 600.0f);
                window.draw(makeFriends);

                eventPicture.setPosition(60.0f, 100.0f);
                window.draw(eventPicture);
                window.display();

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (Mouse::getPosition(window).x > boring.getPosition().x &&
                        Mouse::getPosition(window).x < boring.getPosition().x + 100.0f &&
                        Mouse::getPosition(window).y > boring.getPosition().y &&
                        Mouse::getPosition(window).y < boring.getPosition().y + 100.0f) {
                        eventView = false;
                        findFriend = true;

                        // set nextEvent according to clicked sprite
                    }
                    else if (Mouse::getPosition(window).x > makeFriends.getPosition().x &&
                             Mouse::getPosition(window).x < makeFriends.getPosition().x + 100.0f &&
                             Mouse::getPosition(window).y > makeFriends.getPosition().y &&
                             Mouse::getPosition(window).y < makeFriends.getPosition().y + 100.0f) {

                        eventView = false;
                        newFriends = true;

                    }
                }

                /*if (Mouse::isButtonPressed(Mouse::Left)){
                    findFriend = true;
                    welcome = false;
                }*/
            }
            else if (newFriends) {
                window.clear();
                int userId = 0;

                Sprite boring;
                boring.setTexture(textures.GetTexture("boring"));
                boring.setPosition(25.0f, 750.0f);
                window.draw(boring);

                Text text;
                text.setFont(font);
                text.setCharacterSize(90);
                text.setOutlineColor(Color::White);
                text.setFillColor(Color::White);

                text.setString("Hooray!");
                text.setPosition( 50.0f, 50.0f);
                window.draw(text);

                text.setCharacterSize(50);
                text.setString("New Friends:");
                text.setPosition( 50.0f, 200.0f);
                window.draw(text);

                // int to string to display user id
                string user = to_string(userId);

                for (int i = 1; i < 4; i++) {                    // 4 needs to be set to number of friends made

                    text.setCharacterSize(30);              // display friends just made
                    text.setPosition(20.0f, 300.0f + (i*50)*1.0f);
                    string temp;
                    string eventName;
                    string friendsThere;


                    temp = (char) (i + 48);
                    friendsThere = (char) (/*numoffrinds + */48);
                    text.setString(temp + ". " + user);
                    window.draw(text);
                }

                window.display();

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (Mouse::getPosition(window).x > boring.getPosition().x &&
                        Mouse::getPosition(window).x < boring.getPosition().x + 100.0f &&
                        Mouse::getPosition(window).y > boring.getPosition().y &&
                        Mouse::getPosition(window).y < boring.getPosition().y + 100.0f) {
                        newFriends = false;
                        findFriend = true;

                    }
                }
            }
        }
    }

    return 0;
}
