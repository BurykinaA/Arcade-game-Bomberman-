#include "bomb.h"
#include <iostream>


Bomb::~Bomb()
{
	delete collider;
	delete rect;
}

Bomb::Bomb(Map* map) : map(map)
{
	t.loadFromFile("../images/bomb.png");
	anim.setTexture(t);
	anim.setTextureRect(sf::IntRect(0, 0, 32, 32));
	rect = new sf::RectangleShape(sf::Vector2f(size, size));
	sf::FloatRect collider_rect;
	collider_rect.height = size + 5;
	collider_rect.width = size + 5;
	collider_rect.top = y;
	collider_rect.left = x;
	collider = new BoxCollider(collider_rect);
}

void Bomb::draw(sf::RenderWindow& window)
{
	if (!activated)
		return;
	rect->setPosition(x+11, y+11);
	rect->setFillColor(sf::Color::Cyan);
	//collider->draw(window);
	collider->setPosition(x, y);
	//window.draw(*rect);
	anim.setScale(0.5, 0.5);
	anim.setPosition(this->x - 8, this->y - 8);
	window.draw(anim);
}

void Bomb::update(float dt)
{
	if (activated)
	{
		timer += dt;
		if (timer >= time_life )
			explode();
	}
}

void Bomb::place_bomb(float x, float y)
{
	this->x = x;
	this->y = y;
	activated = true;
	
	rect->setPosition(x, y);
	collider->setPosition(x, y);

}

bool Bomb::isUsed()
{
	return used;
}

BoxCollider* Bomb::getCollider()
{
	return collider;
}

void Bomb::explode()
{
	int w = map->getCellSize();
	map->fireCell(x, y, 1);
	map->fireCell(x+w, y, 1);
	map->fireCell(x-w, y, 1);
	map->fireCell(x, y+w, 1);
	map->fireCell(x, y-w, 1);
	timer = 0;
	activated = false;
	used = true;
}
