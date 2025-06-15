#include "Screen.h"
#include <cmath>

sf::Color Screen::getContrastColor(const sf::Color& backgroundColor)
{
	float r = backgroundColor.r / 255.0f;
	float g = backgroundColor.g / 255.0f;
	float b = backgroundColor.b / 255.0f;
	
	r = (r <= 0.03928f) ? r / 12.92f : pow((r + 0.055f) / 1.055f, 2.4f);
	g = (g <= 0.03928f) ? g / 12.92f : pow((g + 0.055f) / 1.055f, 2.4f);
	b = (b <= 0.03928f) ? b / 12.92f : pow((b + 0.055f) / 1.055f, 2.4f);
	
	float luminance = 0.2126f * r + 0.7152f * g + 0.0722f * b;
	
	return (luminance > 0.5f) ? sf::Color::Black : sf::Color::White;
}