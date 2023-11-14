#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SFMLInitializer {
public:
    static float width;
    static float height;
    static bool initializeRenderWindow(sf::RenderWindow& window, sf::Texture& texture_window);
    static bool initializeBackgroundMusic(sf::Music& backgroundMusic);
    static bool initializeButtonHoverSound(sf::Sound& buttonHoverSound);
    static bool initializeButtonClickSound(sf::Sound& buttonClickSound);
    static bool initializeFont(sf::Font& font);
    static bool initializeSplashTexture(sf::Texture& splashTexture);
};
