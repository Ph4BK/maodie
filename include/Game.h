#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();
	void setBackgroundColor(const sf::Color& color);
	void getEvent(sf::RenderWindow& window);
	sf::Color getBackgroundColor() const;
	void setGridColor(const sf::Color& color);
	sf::Color getGridColor() const;
	
	static const int Width = 640;
	static const int Height = 480;
	static const sf::Time TimePerFrame;

	static std::shared_ptr<Screen> Screen;
	static std::unique_ptr<Game> Instance;

public:
	sf::Event event_;

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	sf::Color backgroundColor_;
	sf::Color gridColor_;
};
}


#endif