#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.hpp"

namespace game {

	

	class GameMenu
	{
		GameState currentState;
		float menu_X;                                    
		float menu_Y;				                      
		int menu_Step;                                    
		int max_menu;                                     
		int size_font;                                    
		int mainMenuSelected;                             
		sf::Font font;                                   
		sf::Text* mainMenu;                  

		sf::Color menu_text_color = sf::Color::White;     
		sf::Color chose_text_color = sf::Color::Yellow;   
		sf::Color border_color = sf::Color::Black;        

		

		void setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const;

		sf::RenderWindow& mywindow;                   
	public:
		sf::Text soundVolumeText;
		sf::Text musicVolumeText;

		GameMenu(sf::RenderWindow& window, float menux, float menuy, sf::String name[], int arraySize, int sizeFont = 60, int step = 80);
		~GameMenu() {
			delete[] mainMenu;
		}
		void draw(bool isDrawVolumeBar);                                    

		void MoveUp();                                  

		void MoveDown();                               

		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor);

		void AlignMenu(int posx);      

		int getSelectedMenuNumber() const    
		{
			return mainMenuSelected;
		}

		void SetState(GameState state);

		GameState getCurrentState() const {
			return currentState;
		}
	};

}