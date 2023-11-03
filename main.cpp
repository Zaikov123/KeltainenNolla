#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gameMenu.h"
void InitText(sf::Text& mtext, float xpos, float ypos, const sf::String str, int size_font = 60,
    sf::Color menu_text_color = sf::Color::White, int bord = 0, sf::Color border_color = sf::Color::Black);
//void GameStart();
//void Options();
//void About_Game();
int main() {
    //creating window with your resolution
    sf::RenderWindow window;
    window.create(sf::VideoMode::getDesktopMode(), L"Keltain Nolla", sf::Style::Fullscreen);

    //get your resolution
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    //background
    sf::RectangleShape background(sf::Vector2f(width, height));
    sf::Texture texture_window;
    
    if (!texture_window.loadFromFile("resources/images/mainMenu.jpg")) {
        return 1;
    }
    background.setTexture(&texture_window);

    //font for screen name
    sf::Font font;
    if (!font.loadFromFile("GhastlyPanicCyr.otf")) return 2;

    sf::Text Titul;
    Titul.setFont(font);

    //name menu buttons
    sf::String name_menu[4]{ L"Start",L"Options",L"About game", L"Exit"};

    //menu object
    game::GameMenu mymenu(window, 950, 350, name_menu, 100, 120);

    //set color for menu text
    mymenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
    mymenu.AlignMenu(2);

    InitText(Titul, 480 , 50, L"Keltainen Nolla", 150, sf::Color(237, 147, 0), 3);

    //splash
    sf::RectangleShape splash(sf::Vector2f(width, height));

    sf::Texture splashTexture;
    if (!splashTexture.loadFromFile("resources/images/splash.jpg")) {
        return 3;
    }
    splash.setTexture(&splashTexture);

    //icon for all except .exe file
    sf::Image icon;
    if (icon.loadFromFile("resources/images/shroom.jpg")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    else {
        return 1;
    }

    //sounds for buttons
    sf::SoundBuffer buttonHoverBuffer;
    if (!buttonHoverBuffer.loadFromFile("resources/sounds/buttonHover.wav")) {
        return 4;
    }

    sf::Sound buttonHoverSound;
    buttonHoverSound.setBuffer(buttonHoverBuffer);

    sf::SoundBuffer buttonClickBuffer;
    if (!buttonClickBuffer.loadFromFile("resources/sounds/buttonClick.wav")) {
        return 5;
    }

    sf::Sound buttonClickSound;
    buttonClickSound.setBuffer(buttonClickBuffer); 

    //background music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("resources/sounds/backgroundmusic.wav")) {
        return 6;
    }
    backgroundMusic.setVolume(0);
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    bool showSplash = true;

    sf::Clock clock;
    float splashDisplayTime = 5.0f;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up) { mymenu.MoveUp(); buttonHoverSound.play();}
                if (event.key.code == sf::Keyboard::Down) { mymenu.MoveDown(); buttonHoverSound.play();}
                if (event.key.code == sf::Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0: /*GameStart();*/  break;
                    case 1: /*Options();  */  break;
                    case 2: /*About_Game();*/ break;
                    case 3: window.close();   break;
                    }
                    buttonClickSound.play();
                }
            }
        }
        window.clear();
        if (showSplash) {
            window.draw(splash);

            if (clock.getElapsedTime().asSeconds() >= splashDisplayTime) {
                showSplash = false;
                clock.restart();
            }
        }
        else {
            
            window.draw(background);
            window.draw(Titul);
            mymenu.draw();
        }

        window.display();
    }




    return 0;
}

void InitText(sf::Text & mtext, float xpos, float ypos, const sf::String str, int size_font, sf::Color menu_text_color, int bord, sf::Color border_color){
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);

}
/* На очень потом реализовать отклик на кнопки
void GameStart()
{
    sf::RenderWindow Play(sf::VideoMode::getDesktopMode(), L"Level 1", sf::Style::Fullscreen);


    sf::RectangleShape background_play(sf::Vector2f(1920, 1080));

    sf::Texture texture_play;
    if (!texture_play.loadFromFile("image/menu4.jpg")) exit(1);
    background_play.setTexture(&texture_play);

    while (Play.isOpen())
    {
        sf::Event event_play;
        while (Play.pollEvent(event_play))
        {
            if (event_play.type == sf::Event::KeyPressed)
            {
                if (event_play.key.code == sf::Keyboard::Escape) { Play.close(); }
            }
        }
        Play.clear();
        Play.draw(background_play);
        Play.display();
    }
}

void Options()
{
    sf::RenderWindow Options(sf::VideoMode::getDesktopMode(), L"Options", sf::Style::Fullscreen);

    sf::RectangleShape background_opt(sf::Vector2f(1920, 1080));
    sf::Texture texture_opt;
    if (!texture_opt.loadFromFile("image/menu1.jpg")) exit(2);

    background_opt.setTexture(&texture_opt);
    while (Options.isOpen())
    {
        sf::Event event_opt;
        while (Options.pollEvent(event_opt))
        {
            if (event_opt.type == sf::Event::Closed) Options.close();
            if (event_opt.type == sf::Event::KeyPressed)
            {
                if (event_opt.key.code == sf::Keyboard::Escape) Options.close();
            }
        }
        Options.clear();
        Options.draw(background_opt);
        Options.display();
    }

}

void About_Game(){

}

*/