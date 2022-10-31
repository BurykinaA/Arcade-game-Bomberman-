#include "HealthBar.h"
#include <string>

HealthBar::HealthBar()
{
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}

void HealthBar::decreaseHP()
{
	hp--;
}

void HealthBar::draw(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(font);
	text.setPosition(605 - 40 * 3, 30);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(30);
	text.setString(("HP: " + std::to_string(hp)).c_str());
	window.draw(text);
}


int HealthBar::getCurHP()
{
	return hp;
}

void HealthBar::resetHP()
{
	hp = 3;
}

