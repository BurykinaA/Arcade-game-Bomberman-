#pragma once
#include "Monster.h"
#include <vector>


//! @authors Бурыкина А.И.
//! @brief класс спавнер мобов
class Spawner {
public:
	//! @brief конструкор принимающий массив монстров, игрока
	Spawner(std::vector<Monster*>* monsters, Player* player);
	//! @brief метод генерирующий случайным образом пять мобов на карте
	/*! с определенным шансом на блоке типа ground создается монстр.*/
	void spawn(class Map* map);
	//! @brief метод, очищающий массив монстров
	void restart();
private:
	
	Monster* monster = nullptr;
	Player* player = nullptr;
	std::vector<Monster*>* monsters;
};