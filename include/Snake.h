#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;

	unsigned getSize() const;
	const std::vector<SnakeNode>& getNodes() const;

private:
	void move();
	void grow(int length);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();
	void getDirection(std::pair<float, float> temp_dir);

	bool hitSelf_;

	std::pair<float, float> direction_;
	std::pair<float, float> residualDirection_;
	bool sharpTurn_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;
	int overlap_;

	static const int InitialSize;
};
}

#endif