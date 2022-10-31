#pragma once
#include <SFML/Graphics.hpp>
#include "BoxCollider.h"
#include "Map.h"
#include "bomb.h"
#include "Killbar.h"
#include "HealthBar.h"
#include <vector>
#include <stdlib.h>


//! @authors Бурыкина А.И.
//! @brief класс игрок
class Player
{
public:
	//! @brief деструктор
	~Player();
	//! @brief конструкор принимающий карту
	/*! задаем анимацию, коллайдер*/
	Player(Map* map);
	//! @brief метод, рисующий игрока в окне игры
	void draw(sf::RenderWindow& window);
	//! @brief метод, обновляющий позицию игрока
	/*! также обновляет коллайдер, перемещает игрока на позицию назад, если его коллайдер пересекается с коллайдером других объектов*/
	void update(float dt);
	//! @brief метод, возвращающий коллайдер объекта
	BoxCollider* getCollider();
	//! @brief метод, описывающий смерть игрока
	/*! обновляет количесво жизней, номер уровня, количество убитых мобов, перегенерирует карту, возвращает игрока в стартовую позицию*/
	void die();
	//! @brief метод, обновляющий количество убитых мобов
	/*! если убиваем всех мобов на уровне, то обновляем количество уровней, генерируем карту, возвращаем игрока в стартовую позицию*/
	void addKill();
private:
	HealthBar hb;
	Killbar kb;
	int kills_on_level = 0;
	int animRow = 1;
	//! @brief метод, возвращающий игрока на начальную позицию
	void return_back();

	float reload_time = 1.0f;
	float timer = reload_time;
	void place_bomb();
	std::vector<Bomb*> bombs;
	float x = 36;
	float y = 36;

	float dy = 0;
	float dx = 0;

	float size = 10;

	//! @brief метод, описывающий движение игрока влево
	void move_left();
	//! @brief метод, описывающий движение игрока вверх
	void move_up();
	//! @brief метод, описывающий движение игрока вниз
	void move_down();
	//! @brief метод, описывающий движение игрока вправо
	void move_right();
	float currentFrame = 0;

	int sprite_width = 32;
	int sprite_height = 32;
	int collider_width = 16;
	int collider_height = 16;

	sf::Sprite anim;
	sf::Texture t;

	float speed = 160.0f;
	BoxCollider* collider = nullptr;
	Map* map = nullptr;
};

