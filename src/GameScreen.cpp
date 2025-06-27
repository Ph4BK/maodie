#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "MenuScreen.h"
#include "HighScoreManager.h"
#include "NameInputScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	sf::Event event = Game::Instance->event_;
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
	{
		Game::Screen = std::make_shared<MenuScreen>();
		return;
	}
	
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf()) {
		size_t score = snake_.getSize();
		if (HighScoreManager::getInstance().isHighScore(score)) {
			Game::Screen = std::make_shared<NameInputScreen>(score);
		} else {
			Game::Screen = std::make_shared<GameOverScreen>(score);
		}
	}
}

void GameScreen::render(sf::RenderWindow& window)
{
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - 2 * Fruit::Radius);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - 2 * Fruit::Radius);
	int x = 0, y = 0;
	bool regenerate = false;
	do {
		x = xDistribution(engine);
		y = yDistribution(engine);
		sf::FloatRect fruitBounds(x, y, 2 * Fruit::Radius, 2 * Fruit::Radius);
		regenerate = false;
		for (const auto& node : snake_.getNodes()) {
			if (node.getHitbox().intersects(fruitBounds)) {
				regenerate = true;
				break;
			}
		}
	} while (regenerate);

	sf::Color color;
	switch (rand() % 8)
	{
		case 0:
			color = sf::Color::Black;
			break;
		case 1:
			color = sf::Color(139, 69, 19); // Brown
			break;
		case 2: case 3:
			color = sf::Color::Red;
			break;
		case 4: case 5:
			color = sf::Color::Blue;
			break;
		case 6: case 7:
			color = sf::Color::Green;
			break;
	}
	fruit_.push_back(Fruit(sf::Vector2f(x, y), color));
}
