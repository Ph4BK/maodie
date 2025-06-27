#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0), sf::Color color = sf::Color::Red);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;
	sf::Color getColor() const;

	static const float Radius;
private:
	sf::CircleShape shape_;
};
}

#endif