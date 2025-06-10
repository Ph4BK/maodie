#include <SFML/Graphics.hpp>
#include <cmath>

#define M_PI 3.14159265358979323846

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Diameter = 20.f;
sf::Texture SnakeNode::headTexture_;
sf::Texture SnakeNode::headTexture2_;
sf::Texture SnakeNode::bodyTexture_;
bool SnakeNode::headTextureLoaded_ = false;
bool SnakeNode::headTexture2Loaded_ = false;

SnakeNode::SnakeNode(sf::Vector2f position, bool isHead)
: position_(position), isHead_(isHead), headChangeCounter_(0), usingAlternateHead_(false)
{
	if (isHead_) {
		if (headTexture_.getSize().x == 0) {
			if (headTexture_.loadFromFile("Images/head.png")) {
				headTextureLoaded_ = true;
			} else {
				headTextureLoaded_ = false;
				// Default texture for head.png
				sf::Image image;
				image.create(static_cast<unsigned int>(Diameter), static_cast<unsigned int>(Diameter), sf::Color::Green);
				headTexture_.loadFromImage(image);
			}
		}
		if (headTexture2_.getSize().x == 0) {
			if (headTexture2_.loadFromFile("Images/head2.png")) {
				headTexture2Loaded_ = true;
			} else {
				headTexture2Loaded_ = false;
			}
		}
		
		// If head.png failed but head2.png succeeded, use head2.png as default head texture
		if (!headTextureLoaded_ && headTexture2Loaded_) {
			headTexture_ = headTexture2_;
		}
	}
	else if (!isHead_ && bodyTexture_.getSize().x == 0) {
		if (!bodyTexture_.loadFromFile("Images/body.png")) {
			// Default texture for body.png
			sf::Image image;
			image.create(static_cast<unsigned int>(Diameter), static_cast<unsigned int>(Diameter), sf::Color::Green);
			bodyTexture_.loadFromImage(image);
		}
	}
	
	setTextureAndScale(isHead_ ? headTexture_ : bodyTexture_);
	sprite_.setPosition(position_);
}

void SnakeNode::setTextureAndScale(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
	
	// Calculate scale to stretch the image to fill the square
	sf::Vector2u textureSize = texture.getSize();
	float scaleX = Diameter / textureSize.x;
	float scaleY = Diameter / textureSize.y;
	sprite_.setScale(scaleX, scaleY);
	
	sprite_.setOrigin(textureSize.x / 2.f, textureSize.y / 2.f);
}

void SnakeNode::setDirection(float x, float y)
{
	float angle = std::atan2(y, x) * 180.f / M_PI + 90.f;
	sprite_.setRotation(angle);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	sprite_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	sprite_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	sprite_.setPosition(position_);
}

sf::FloatRect SnakeNode::getHitbox() const
{
	sf::FloatRect outerBounds = sprite_.getGlobalBounds();
	
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
	window.draw(sprite_);
}

void SnakeNode::triggerHeadChange()
{
	if (isHead_ && headTexture2Loaded_) {
		headChangeCounter_ = 5;
		usingAlternateHead_ = true;
		setTextureAndScale(headTexture2_);
	}
}

void SnakeNode::update()
{
	if (isHead_ && usingAlternateHead_) {
		headChangeCounter_--;
		if (headChangeCounter_ <= 0) {
			usingAlternateHead_ = false;
			setTextureAndScale(headTexture_);
		}
	}
}