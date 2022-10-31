#pragma once

#include <SFML/Graphics.hpp>
//! @authors Бурыкина А.И.
//! @brief класс количество убийств
class Killbar
{
public:
	//! @brief конструктор
	/*! выбирает нужный шрифт*/
	Killbar();
	//! @brief метод, выводящий информацию о количестве убитых мобов в игровое окно
	void draw(sf::RenderWindow& window);
	//! @brief метод, сбрасывающий количество убийств
	/*! вызывается после смерти персонажа, количество убийств становится равное нулю*/
	void resetKills();
	//! @brief метод, увеличивающий количество убийств
	void addKill();
	//! @brief метод, возвращающий количество убитых мобов в текущий момент
	int getKills();

private:
	//! @brief начальное количество убитых мобов
	int kills = 0;
	sf::Font font;

};

