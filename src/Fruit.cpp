#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include "Screen.h"
#include "Game.h"

using namespace sfSnake;

const float Fruit::Radius = 10.f;

Fruit::Fruit(sf::Vector2f position, sf::Color color)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(color);
	shape_.setOutlineColor(Screen::getContrastColor(Game::Instance->getBackgroundColor()));
	shape_.setOutlineThickness(-1.f);
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Color Fruit::getColor() const
{
	return shape_.getFillColor();
}