#pragma once
#include <ctime>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "BoxCollider.h"
#include "LevelBar.h"

#define rows 15
#define columns 15


//! @authors Бурыкина А.И.
//! @brief класс карта
class Map
{
public:
	//! @brief перечисление типов блоков
	enum class BLOCK_TYPE
	{
		GROUND, WALL, BOX, FIRE, NONE
	};
	//! @brief метод, возвращающая текущий уровень 
	int getLevel();
	//! @brief метод генерации карты, генецации мобов
	/*!
	* Генерация блоков типа wall всегда одинакова. Мы создаем окружающий квадрат 15х15 и внутри него расставляем блоки через один.
Выбор типа блока ground или box определяется случайным образом. На блоке, где находится стартовая позиция нашего игрока, и блоке снизу и справа тип блока всегда будет ground.

	*/
	void generate();
	//! @brief метод поджога области 
	/*! поджигает блок с координатами (x, y), тип BOX меняет на GROUND */
	void fireCell(float x, float y, float time);
	//! @brief метод, рисующий карту в окне
	void draw(sf::RenderWindow& window);
	//! @brief метод, обновляющий карту, dt -разница во времени с предыдущим кадром
	void update(float dt);
	//! @brief получаем тип блока на клеточке с индексами (i,j)
	BLOCK_TYPE getBlock(int i, int j);
	//! @brief получаем коллайдер объекта на клеточке с индексами (i,j)
	BoxCollider* getBlockCollider(int i, int j);
	//! @brief получаем количество строк
	int getRowsCount();
	//! @brief получаем количество столбцов
	int getColumnsCount();
	//! @brief получаем размер клетки в пикселях
	int getCellSize();

	//! @brief метод перезапуска
	void restart();
	//! @brief тушит пожар
	void fireOff();

	sf::Vector2f getOriginPosition();
	//! @brief конструктор, инициализирует начальные значения
	Map();
	//void load(std::ifstream& stream);
	void setSpawner(class Spawner* spawner);
private:
	Spawner* spawner = nullptr;
	LevelBar lb;
	float timer = 0.0f;
	BLOCK_TYPE blocks[rows][columns];
	BoxCollider* block_colliders[rows][columns];
	float fire_life_time = 0;
	int cell_size = 32;

	
};

