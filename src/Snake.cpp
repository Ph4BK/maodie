#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(0.f, -1.f), residualDirection_(0.f, 0.f), sharpTurn_(false), hitSelf_(false), overlap_(0)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Diameter / 2,
			Game::Height / 2 - (SnakeNode::Diameter / 2) + (SnakeNode::Diameter * i)),
			i == 0));
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	sf::Event event = Game::Instance->event_;
	if ((event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) ||
		sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

		float mouse_x = mouseWorldPos.x;
		float mouse_y = mouseWorldPos.y;
		float head_x = nodes_[0].getPosition().x;
		float head_y = nodes_[0].getPosition().y;

		float dist = sqrt((mouse_x - head_x) * (mouse_x - head_x) +
						  (mouse_y - head_y) * (mouse_y - head_y));
		if (dist == 0) return;
		std::pair<float, float> temp_dir = std::make_pair((mouse_x - head_x) / dist, 
														  (mouse_y - head_y) / dist);
		getDirection(temp_dir);
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up){
		getDirection(std::make_pair(0.f, -1.f));
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down){
		getDirection(std::make_pair(0.f, 1.f));
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left){
		getDirection(std::make_pair(-1.f, 0.f));
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right){
		getDirection(std::make_pair(1.f, 0.f));
	}
	else if (sharpTurn_){
		direction_ = residualDirection_;
		sharpTurn_ = false;
		residualDirection_ = std::make_pair(0.f, 0.f);
	}
}

void Snake::getDirection(std::pair<float, float> temp_dir){
	float out_prod = direction_.first * temp_dir.second - direction_.second * temp_dir.first;
	if (out_prod == 0){
		sharpTurn_ = false;
		residualDirection_ = std::make_pair(0.f, 0.f);
		return;
	}
	float in_prod = direction_.first * temp_dir.first + direction_.second * temp_dir.second;
	if (in_prod >= 0){
		direction_ = temp_dir;
		sharpTurn_ = false;
		residualDirection_ = std::make_pair(0.f, 0.f);
	} else {
		direction_ = out_prod > 0 ?
		std::make_pair(-direction_.second, direction_.first) :
		std::make_pair(direction_.second, -direction_.first);
		sharpTurn_ = true;
		residualDirection_ = temp_dir;
	}
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
	
	for (auto& node : nodes_)
		node.update();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto& it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getHitbox()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		if (toRemove->getColor() == sf::Color::Red) grow(3);
		else if (toRemove->getColor() == sf::Color::Blue) grow(2);
		else if (toRemove->getColor() == sf::Color::Green) grow(1);
		nodes_[0].triggerHeadChange();
		fruits.erase(toRemove);
	}
}

void Snake::grow(int length)
{
	overlap_ += length;
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

const std::vector<SnakeNode>& Snake::getNodes() const
{
	return nodes_;
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 2; i < nodes_.size(); ++i)
	{
		if (headNode.getHitbox().intersects(nodes_[i].getHitbox()) && !hitSelf_)
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	decltype(nodes_.size()) orig_len = nodes_.size();

	if (overlap_){
		nodes_.push_back(SnakeNode(sf::Vector2f(
			nodes_[orig_len - 1].getPosition().x, nodes_[orig_len - 1].getPosition().y)));
		overlap_--;
	}

	for (decltype(nodes_.size()) i = orig_len - 1; i > 0; --i)
	{
		sf::Vector2f prevPos = nodes_[i - 1].getPosition();
		sf::Vector2f currentPos = nodes_[i].getPosition();
		float dx = prevPos.x - currentPos.x;
		float dy = prevPos.y - currentPos.y;
		nodes_[i].setDirection(dx, dy);
		nodes_[i].setPosition(prevPos);
	}

	nodes_[0].setDirection(direction_.first, direction_.second);
	nodes_[0].move(direction_.first * SnakeNode::Diameter, direction_.second * SnakeNode::Diameter);
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto& node : nodes_)
		node.render(window);
}
