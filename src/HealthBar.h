#pragma once

//! @authors Бурыкина А.И.
//! @brief класс панель жизней

#include <SFML/Graphics.hpp>
class HealthBar
{
public:
	//!@brief конструктор
	/*! выбирает нужный шрифт*/
	HealthBar();
	//! @brief метод, уменьшающий количество HP героя
	void decreaseHP();
	//! @brief метод, выводящий информацию о HP в игровое окно
	void draw(sf::RenderWindow& window);
	//! @brief метод, возвращающий количество жизний в текущий момент
	int getCurHP();
	//! @brief метод, сбрасывающий количество жизней
	/*! вызывается после смерти персонажа*/
	void resetHP();

private:
	//! @brief начальное количество жизней
	int hp = 3;
	sf::Font font;
};

