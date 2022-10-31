#pragma once
#pragma once
#include <SFML/Graphics.hpp>

//! @authors Бурыкина А.И.
//! @brief класс панель уровней

class LevelBar
{
public:
	//! @brief конструктор
	/*! выбирает нужный шрифт*/
	LevelBar();
	//! @brief метод, выводящий информацию о номере уровня в игровое окно
	void draw(sf::RenderWindow& window);
	//! @brief метод, сбрасывающий количество уровней
	/*! вызывается после смерти персонажа*/
	void resetLevel();
	//! @brief метод, увеличивающий номер уровня
	void addLevel();
	//! @brief метод, возвращающий номер уровня
	int getLevel();

private:
	//! @brief начальный номер уровня
	int level = 0;
	sf::Font font;

};

