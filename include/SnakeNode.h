#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), bool isHead = false);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setDirection(float x, float y);
	void triggerHeadChange();

	void move(float xOffset, float yOffset);
	void update();

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getHitbox() const;

	static const float Diameter;

private:
	void setTextureAndScale(const sf::Texture& texture);
	
	sf::Vector2f position_;
	sf::Sprite sprite_;
	static sf::Texture headTexture_;
	static sf::Texture headTexture2_;
	static sf::Texture bodyTexture_;
	static bool headTextureLoaded_;
	static bool headTexture2Loaded_;
	bool isHead_;
	int headChangeCounter_;
	bool usingAlternateHead_;
};
}

#endif