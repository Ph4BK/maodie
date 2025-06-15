#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Screen.h"

namespace sfSnake
{
class SettingsScreen : public Screen
{
public:
	SettingsScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Font font_;
	sf::Text titleText_;
	sf::Text instructionText_;
    sf::Text backgroundText_;
	sf::Text gridText_;
	
	std::vector<sf::Text> colorOptions_;
	std::vector<sf::Color> colors_;
	std::vector<std::string> colorNames_;
	
	std::vector<sf::Text> gridOptions_;
	std::vector<sf::Color> gridColors_;
	std::vector<std::string> gridColorNames_;
	
	int selectedColorIndex_;
	int selectedGridIndex_;
	int currentSelection_; // 0 for background, 1 for grid
	void updateColorSelection();
	void updateGridSelection();
	void updateCurrentSelection();
};
}

#endif 