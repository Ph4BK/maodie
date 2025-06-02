#include <SFML/Graphics.hpp>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Diameter = 10.f;

SnakeNode::SnakeNode(sf::Vector2f position)
: position_(position)
{
	shape_.setPosition(position_);
	shape_.setFillColor(sf::Color::Green);
	shape_.setRadius(SnakeNode::Diameter / 2.f);
	shape_.setOutlineColor(sf::Color::White);
	shape_.setOutlineThickness(-1.f);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
}

sf::FloatRect SnakeNode::getHitbox() const
{
	sf::FloatRect outerBounds = shape_.getGlobalBounds();
	
	float hitWidth = outerBounds.width * 0.7f;
	float hitHeight = outerBounds.height * 0.7f;
	
	float offsetX = (outerBounds.width - hitWidth) / 2.f;
	float offsetY = (outerBounds.height - hitHeight) / 2.f;
	
	return sf::FloatRect(
		outerBounds.left + offsetX,
		outerBounds.top + offsetY,
		hitWidth,
		hitHeight
	);
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}