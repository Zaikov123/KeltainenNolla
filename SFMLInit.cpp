#include "SFMLInit.h"
#include "gameMenu.h"  

float SFMLInitializer::width = sf::VideoMode::getDesktopMode().width;
float SFMLInitializer::height = sf::VideoMode::getDesktopMode().height;

bool SFMLInitializer::initializeRenderWindow(sf::RenderWindow& window, sf::Texture& texture) {

    sf::RectangleShape background(sf::Vector2f(width, height));
    sf::Texture texture_window;

    if (!texture.loadFromFile("resources/images/mainMenu.jpg")) {
        return false;
    }
    background.setTexture(&texture);
    sf::Image icon;
    if (icon.loadFromFile("resources/images/shroom.jpg")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    else {
        return false;
    }
    return true;
}

bool SFMLInitializer::initializeBackgroundMusic(sf::Music& backgroundMusic) {
    if (!backgroundMusic.openFromFile("resources/sounds/backgroundmusic.wav")) {
        return false;
    }
    backgroundMusic.setVolume(0);
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
    return true;
}

bool SFMLInitializer::initializeButtonHoverSound(sf::Sound& buttonHoverSound) {
    sf::SoundBuffer buttonHoverBuffer;
    if (!buttonHoverBuffer.loadFromFile("resources/sounds/buttonHover.wav")) {
        return false;
    }

    buttonHoverSound.setBuffer(buttonHoverBuffer);
    return true;
}

bool SFMLInitializer::initializeButtonClickSound(sf::Sound& buttonClickSound) {
    sf::SoundBuffer buttonClickBuffer;
    if (!buttonClickBuffer.loadFromFile("resources/sounds/buttonClick.wav")) {
        return false;
    }

    buttonClickSound.setBuffer(buttonClickBuffer);
    return true;
}

bool SFMLInitializer::initializeFont(sf::Font& font) {
    if (!font.loadFromFile("GhastlyPanicCyr.otf")) {
        return false;
    }
    return true;
}

bool SFMLInitializer::initializeSplashTexture(sf::Texture& splashTexture) {
    if (!splashTexture.loadFromFile("resources/images/splash.jpg")) {
        return false;
    }
    return true;
}
