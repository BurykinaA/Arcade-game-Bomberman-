#include "Player.h"

Player::~Player()
{
}

Player::Player(Map* map) : map(map)
{
	sf::FloatRect rect;
	rect.height = size + 8;
	rect.width = size + 8;
	rect.top = y;
	rect.left = x;
	collider = new BoxCollider(rect);
	t.loadFromFile("../images/player.png");
	anim.setTexture(t);
	anim.setTextureRect(sf::IntRect(sprite_width, sprite_height, sprite_width, sprite_height));
	return_back();
}

void Player::draw(sf::RenderWindow& window)
{
	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(size, size));
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color::Blue);
	//collider->draw(window);
	for (auto it = bombs.begin(); it != bombs.end(); it++)
	{
		(*it)->draw(window);
	}
	//window.draw(rect);
	window.draw(anim);
	kb.draw(window);
	hb.draw(window);
}

void Player::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move_right();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move_left();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move_up();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move_down();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		place_bomb();
	}
	int player_map_position_x = (int)(x / map->getCellSize());
	int player_map_position_y =(int)( y / map->getCellSize());


	x += dx * dt;
	collider->setPosition(x - 4, y - 4);

	for (int i = 0; i < map->getRowsCount(); i++) {
		for (int j = 0; j < map->getColumnsCount(); j++) {
			auto block_collider = map->getBlockCollider(i, j);
			if (block_collider)
			{
				if (collider->intersects(*block_collider))
				{
					x -= dx * dt;
				}
			}
		}
	}

	y += dy * dt;
	collider->setPosition(x - 4, y - 4);

	for (int i = 0; i < map->getRowsCount(); i++) {
		for (int j = 0; j < map->getColumnsCount(); j++) {
			auto block_collider = map->getBlockCollider(i, j);
			if (block_collider)
			{
				if (collider->intersects(*block_collider))
				{
					y -= dy * dt;
				}
			}
		}
	}


	collider->setPosition(x - 4, y - 4);
	anim.setPosition(x-10, y-12);

	dx = 0;
	dy = 0;
	if (bombs.size())
	{
		auto it = bombs.begin();

		if ((*it)->isUsed())
		{
			delete* it;
			bombs.erase(it);
		}
	}

	for (auto it = bombs.begin(); it != bombs.end(); it++)
	{
		(*it)->update(dt);
	}

	int curr_x;
	int curr_y;
	for (int i = 0; i < map->getColumnsCount(); i++) {
		for (int j = 0; j < map->getRowsCount(); j++) {
			auto x = map->getBlock(i, j);
			switch (x)
			{
			case Map::BLOCK_TYPE::FIRE:
				auto cell_size = map->getCellSize();
				curr_x = (int)(collider->getPosition().x / cell_size);
				curr_y = (int)(collider->getPosition().y / cell_size);
				if (curr_x == i && curr_y == j)
				{
					die();
				}
				break;
			}

		}
	}

	timer += dt;

}

BoxCollider* Player::getCollider()
{
	return collider;
}

void Player::die()
{
	if (hb.getCurHP() <= 1)
	{
		hb.resetHP();
		kb.resetKills();
		map->restart();
		return_back();
	}
	else
	{
		hb.decreaseHP();
		return_back();
	}
}

void Player::addKill()
{
	kb.addKill();
	kills_on_level++;
	if (kills_on_level)
		if (kills_on_level % 5 == 0)
		{
			map->generate();
			return_back();
		}
}

void Player::place_bomb()
{
	if (timer >= reload_time)
	{
		auto bomb = new Bomb(map);
		bombs.push_back(bomb);
		bomb->place_bomb(x, y);
		timer = 0.0f;
	}


}

void Player::return_back()
{
	x = 36;
	y = 36;
	map->fireOff();
}

void Player::move_left()
{
	dx = -speed;
	animRow = 3;
	anim.setTextureRect(sf::IntRect((int)currentFrame * 32, animRow * 32, sprite_width, sprite_height));
}

void Player::move_up()
{
	dy = -speed;
	animRow = 2;
	anim.setTextureRect(sf::IntRect((int)currentFrame * 32, animRow * 32, sprite_width, sprite_height));
}

void Player::move_down()
{
	dy = speed;
	animRow = 0;
	anim.setTextureRect(sf::IntRect((int)currentFrame * 32, animRow * 32, sprite_width, sprite_height));
}

void Player::move_right()
{
	dx = speed;
	animRow = 1;
	anim.setTextureRect(sf::IntRect((int)currentFrame * 32, animRow * 32, sprite_width, sprite_height));
}
