#pragma once
#include <SFML/Graphics.hpp>
#include "BoxCollider.h"
#include "Map.h"


//! @authors Бурыкина А.И.
//! @brief класс бомб
//! 
class Bomb {
public:
	//! @brief деструктор
	~Bomb();
	//! @brief конструкор, принимает на вход нашу карту
	Bomb(Map* map);
	//! @brief метод, рисующий бомбу в окне, если она активна
	void draw(sf::RenderWindow& window);
	//! @brief метод обновления бомбы (например взрыв), на вход получает разницу во времени с предыдущем кадром
	void update(float dt);
	//! @brief метод, ставящий бомбу на позицию с координатами (x, y)
	/*! также делает нашу бомбу активной
	*/
	void place_bomb(float x, float y);
	//! @brief нужна для массива бомб, чтобы удалять уже взорвавшиеся
	bool isUsed();
	BoxCollider* getCollider();
private:
	bool used = false;
	float x=0;
	float y=0;
	float timer = 0;
	float time_life = 2;

	float size = 10;
	
	bool activated = false;
	sf::RectangleShape* rect;
	sf::Sprite* sprite;
	BoxCollider* collider = nullptr;
	Map* map = nullptr;

	sf::Sprite anim;
	sf::Texture t;
	//! @brief метод поджигает соседние блоки
	void explode();
};