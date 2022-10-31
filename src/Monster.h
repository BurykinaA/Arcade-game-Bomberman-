#pragma once
#include <SFML/Graphics.hpp>
#include "BoxCollider.h"
#include "Map.h"
#include "Player.h"
#include<vector>


//! @authors Бурыкина А.И.
//! @brief класс мобов
class Monster {
public:
	//! @brief деструкор
	~Monster();
	//! @brief конструкор принимающий карту, массив мобов, игрока
	/*! задаем анимацию, направления движения, коллайдер*/
	Monster(Map* map, std::vector<Monster*>* other_monsters, Player* player);
	//! @brief метод, рисующий монстров в окне игры
	void draw(sf::RenderWindow& window);
	//! @brief метод, обновления монстров, dt - разница во времени с предыдущим кадром
	void update(float dt);
	//! @brief устанавливает позицию моба на карте
	void setPosition(sf::Vector2f& position);
	

private:
	float reload_time = 1.0f;
	float timer = reload_time;

	float speed = 60.0f;
	BoxCollider* collider = nullptr;
	Map* map = nullptr;
	Player* player = nullptr;
	std::vector<Monster*>* monsters;
	sf::Vector2f position;
	sf::Vector2i direction;
	float size = 16;

	sf::Sprite anim;
	sf::Texture t;
	int sprite_width = 32;
	int sprite_height = 32;

	int animRow = 0;
	int animFrames = 0;
	float currentFrame = 0;
};