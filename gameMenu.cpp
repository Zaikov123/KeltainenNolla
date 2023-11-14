#include "GameMenu.h"
#include <vector>

void game::GameMenu::setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const
{
	text.setFont(font);
	text.setFillColor(menu_text_color);
	text.setString(str);
	text.setCharacterSize(size_font);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
	text.setOutlineColor(border_color);
}

void game::GameMenu::AlignMenu(int posx)
{

	float nullx = 0;

	for (int i = 0; i < max_menu; i++) {

		switch (posx)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = mainMenu[i].getLocalBounds().width;
			break;
		case 2:
			nullx = mainMenu[i].getLocalBounds().width / 2;
			break;
		default:break;
		}

		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}

}

void game::GameMenu::SetState(GameState state)
{
	currentState = state;
}

void game::GameMenu::MoveUp()
{
	mainMenuSelected--;

	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
		mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);
	}
	else
	{
		mainMenu[0].setFillColor(menu_text_color);
		mainMenuSelected = max_menu - 1;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
}

void game::GameMenu::MoveDown()
{
	mainMenuSelected++;

	if (mainMenuSelected < max_menu) {
		mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
	else
	{
		mainMenu[max_menu - 1].setFillColor(menu_text_color);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}

}


game::GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy, sf::String name[], int arraySize, int sizeFont, int step)
	: mywindow(window), menu_X(menux), menu_Y(menuy), size_font(sizeFont), menu_Step(step)
{
	if (!font.loadFromFile("MorrisRomanAlternate-Black.ttf")) exit(32);
	max_menu = arraySize;

	mainMenu = new sf::Text[arraySize];

	for (int i = 0, ypos = menu_Y; i < max_menu; i++, ypos += menu_Step)
		setInitText(mainMenu[i], name[i], menu_X, ypos);
	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(sf::Color::Yellow);
	setInitText(soundVolumeText, L"Sound Volume: 100%", menu_X, menu_Y);
	setInitText(musicVolumeText, L"Music Volume: 100%", menu_X, menu_Y + size_font + 5);
}


void game::GameMenu::draw(bool isDrawVolumeBar)
{
	for (int i = 0; i < max_menu; i++)
		mywindow.draw(mainMenu[i]);
	if (isDrawVolumeBar) {
		mywindow.draw(soundVolumeText); 
		mywindow.draw(musicVolumeText);
	}
}


void game::GameMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
	menu_text_color = menColor;
	chose_text_color = ChoColor;
	border_color = BordColor;

	for (int i = 0; i < max_menu; i++) {
		mainMenu[i].setFillColor(menu_text_color);
		mainMenu[i].setOutlineColor(border_color);
	}

	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}
