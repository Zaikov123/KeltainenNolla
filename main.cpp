#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "gameMenu.h"

void InitText(sf::Text& mtext, float xpos, float ypos, const sf::String str, int size_font = 60,
    sf::Color menu_text_color = sf::Color::White, int bord = 0, sf::Color border_color = sf::Color::Black);

int main() 
{
    //creating window 
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
    if (!font.loadFromFile("MorrisRomanAlternate-Black.ttf")) return 2;

    sf::Text Titul;
    Titul.setFont(font); 

    InitText(Titul, 480, 50, L"Keltainen Nolla", 150, sf::Color(237, 147, 0), 3);

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

    // get volume for options
    int soundVolume = buttonHoverSound.getVolume();
    int musicVolume = backgroundMusic.getVolume();

    //name menu buttons
    sf::String curr_menu[1]{ L"Util" };
    sf::String name_menu[4]{ L"Start",L"Options",L"About game", L"Exit" };
    sf::String name_options_menu[4]{ L"Video",L"Audio",L"controls", L"Back" };
    sf::String name_audio_menu[3]{ L"Sound Volume",L"Music Volume",L"Back" };
    sf::String name_video_menu[3]{ L"Fullscreen / Windowed",L"Resolution",L"Back" };

    //menu object
    game::GameMenu currentmenu(window, 950, 350, name_menu, 4, 100, 120);

    game::GameMenu mainmenu(window, 950, 350, name_menu, 4, 100, 120);
    mainmenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
    mainmenu.AlignMenu(2);

    game::GameMenu optionsmenu(window, 950, 350, name_options_menu, 4, 100, 120);
    optionsmenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
    optionsmenu.AlignMenu(2);

    game::GameMenu audiomenu(window, 950, 350, name_audio_menu, 3, 100, 120);
    audiomenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
    audiomenu.AlignMenu(2);

    game::GameMenu videomenu(window, 950, 350, name_video_menu, 3, 100, 120);
    videomenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
    videomenu.AlignMenu(2);

    // for change fullscreen/windowed
    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0];
    bool isFullscreen = (window.getSize().x == fullscreenMode.width && window.getSize().y == fullscreenMode.height);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::KeyReleased)
            {
                if (currentmenu.getCurrentState() == MainMenu) {
                    if (event.key.code == sf::Keyboard::Up) { mainmenu.MoveUp(); buttonHoverSound.play(); }
                    if (event.key.code == sf::Keyboard::Down) { mainmenu.MoveDown(); buttonHoverSound.play(); }
                    if (event.key.code == sf::Keyboard::Return) {
                        switch (mainmenu.getSelectedMenuNumber()) {
                        case 0: /*GameStart();*/  break; //Start
                        case 1: currentmenu.SetState(OptionsMenu); break; //Options
                        case 2: /*About_Game();*/ break; //About game
                        case 3: window.close(); break; //Exit
                        }
                        buttonClickSound.play();
                    }
                }
                else if (currentmenu.getCurrentState() == OptionsMenu) {
                    if (event.key.code == sf::Keyboard::Up) { optionsmenu.MoveUp(); buttonHoverSound.play(); }
                    if (event.key.code == sf::Keyboard::Down) { optionsmenu.MoveDown(); buttonHoverSound.play(); }
                    if (event.key.code == sf::Keyboard::Return) {
                        switch (optionsmenu.getSelectedMenuNumber()) {
                        case 0: currentmenu.SetState(VideoOptions); break; // Video
                        case 1: currentmenu.SetState(AudioOptions); break; // Audio
                        case 2: /*About_Game();*/ break; // Controls
                        case 3: currentmenu.SetState(MainMenu); break; // Exit
                        }
                        buttonClickSound.play();
                    }
                }
                else if (currentmenu.getCurrentState() == AudioOptions) {
                    if (event.key.code == sf::Keyboard::Up) { audiomenu.MoveUp(); buttonHoverSound.play(); }
                    if (event.key.code == sf::Keyboard::Down) { audiomenu.MoveDown(); buttonHoverSound.play(); }
                    // Sound options
                    if (event.key.code == sf::Keyboard::Left) {
                        switch (audiomenu.getSelectedMenuNumber()) {
                        case 0:
                            soundVolume > 0 ? soundVolume -= 5 : 0;
                            audiomenu.soundVolumeText.setString("Sound Volume: " + std::to_string(soundVolume) + "%");
                            break;
                        case 1:
                            musicVolume > 0 ? musicVolume -= 5 : 0;
                            audiomenu.musicVolumeText.setString("Music Volume: " + std::to_string(musicVolume) + "%");
                            break;
                        }
                        buttonClickSound.play();
                    }

                    if (event.key.code == sf::Keyboard::Right) {
                        switch (audiomenu.getSelectedMenuNumber()) {
                        case 0:
                            soundVolume < 100 ? soundVolume += 5 : 0;
                            audiomenu.soundVolumeText.setString("Sound Volume: " + std::to_string(soundVolume) + "%");
                            break;
                        case 1:
                            musicVolume < 100 ? musicVolume += 5 : 0;
                            audiomenu.musicVolumeText.setString("Music Volume: " + std::to_string(musicVolume) + "%");
                            break;
                        }
                        buttonClickSound.play();
                    }

                    if (event.key.code == sf::Keyboard::Return) {
                        switch (audiomenu.getSelectedMenuNumber()) {
                        case 0: break; // Sound Volume
                        case 1: break; // Music Volume
                        case 2: currentmenu.SetState(OptionsMenu);  break; // exit
                        }
                        buttonClickSound.play();
                    }
                }
                else if (currentmenu.getCurrentState() == VideoOptions) {
                    if (event.key.code == sf::Keyboard::Up) { videomenu.MoveUp(); buttonHoverSound.play(); }
                    if (event.key.code == sf::Keyboard::Down) { videomenu.MoveDown(); buttonHoverSound.play(); }
                    if (event.key.code == sf::Keyboard::Return) {
                        switch (videomenu.getSelectedMenuNumber()) {
                        case 0: window.create(isFullscreen ? sf::VideoMode(800, 600) : sf::VideoMode::getDesktopMode(), "SFML Window", isFullscreen ? sf::Style::Default : sf::Style::Fullscreen); 
                        break; // Full screen / windowed
                        case 1: break; // Resolution
                        case 2: currentmenu.SetState(OptionsMenu); break; // back
                        }
                        buttonClickSound.play();
                    }
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
            if(currentmenu.getCurrentState() == MainMenu){ mainmenu.draw(false); }
            else if (currentmenu.getCurrentState() == OptionsMenu)  { optionsmenu.draw(false);}
            else if (currentmenu.getCurrentState() == AudioOptions) { audiomenu.draw(true);   }        
            else if (currentmenu.getCurrentState() == VideoOptions) { videomenu.draw(false);  }
        }
        
        buttonHoverSound.setVolume(soundVolume);
        buttonClickSound.setVolume(soundVolume);

        backgroundMusic.setVolume(musicVolume);



        window.display();
    }
}

void InitText(sf::Text & mtext, float xpos, float ypos, const sf::String str, int size_font, sf::Color menu_text_color, int bord, sf::Color border_color){
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);

}
