#include "Monster.h"

Monster::~Monster()
{
}

Monster::Monster(Map* map, std::vector<Monster*>* other_monsters, Player* player) : map(map), monsters(other_monsters), player(player)
{
	int dir = rand() % 4;

	t.loadFromFile("../images/enemy.png");
	anim.setTexture(t);
	anim.setTextureRect(sf::IntRect(1, 0, 16, 16));
	anim.setScale(2, 2);

	switch (dir)
	{
	case 0:
		direction.x = 1;
		animFrames = 4;
		animRow = 4;
		break;
	case 1:
		direction.x = -1;
		animFrames = 4;
		animRow = 4;
		break;
	case 2:
		direction.y = 1;
		animFrames = 2;
		animRow = 1;
		break;
	case 3:
		direction.y = -1;
		animFrames = 2;
		animRow = 8;
		break;
	}
	sf::FloatRect rect;
	rect.height = size + 4;
	rect.width = size + 4;
	rect.top = position.x;
	rect.left = position.y;
	collider = new BoxCollider(rect);
}

void Monster::draw(sf::RenderWindow& window)
{
	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(size, size));
	rect.setPosition(position.x, position.y);
	rect.setFillColor(sf::Color(123, 45, 55));
	//collider->draw(window);
	//window.draw(rect);
	anim.setTextureRect(sf::IntRect(1 + 16 * animRow + 16 * (int)currentFrame, 0, 16, 16));
	anim.setScale(2, 2);
	window.draw(anim);
}

void Monster::update(float dt)
{
	currentFrame += 8 * dt;
	if (currentFrame > animFrames) { currentFrame = 0; }
	position.x += direction.x * dt * speed;
	collider->setPosition(position.x - 3, position.y - 3);


	for (size_t i = 0; i < (size_t)map->getColumnsCount(); i++)
	{
		for (size_t j = 0; j < (size_t)map->getRowsCount(); j++)
		{
			BoxCollider* result = map->getBlockCollider(i, j);
			if (result)
			{
				if (collider->intersects(*result))
				{
					position.x -= direction.x * dt * speed;
					auto dir = rand() % 4;
					switch (dir)
					{
					case 0:
						direction.x = 1;
						direction.y = 0;
						animFrames = 4;
						animRow = 4;

						break;
					case 1:
						direction.x = -1;
						direction.y = 0;
						animFrames = 4;
						animRow = 10;

						break;
					case 2:
						direction.x = 0;
						direction.y = 1;
						animFrames = 2;
						animRow = 1;

						break;
					case 3:
						direction.x = 0;
						direction.y = -1;
						animFrames = 2;
						animRow = 8;

						break;
					}

					break;
				}
			}
		}
	}

	position.y += direction.y * dt * speed;
	collider->setPosition(position.x - 3, position.y - 3);

	for (size_t i = 0; i < (size_t)map->getColumnsCount(); i++)
	{
		for (size_t j = 0; j < (size_t)map->getRowsCount(); j++)
		{
			BoxCollider* result = map->getBlockCollider(i, j);
			if (result)
			{
				if (collider->intersects(*result))
				{
					position.y -= direction.y * dt * speed;
					auto dir = rand() % 4;
					switch (dir)
					{
					case 0:
						direction.x = 1;
						direction.y = 0;
						animFrames = 4;
						animRow = 4;

						break;
					case 1:
						direction.x = -1;
						direction.y = 0;
						animFrames = 4;
						animRow = 10;

						break;
					case 2:
						direction.x = 0;
						direction.y = 1;
						animFrames = 2;
						animRow = 1;

						break;
					case 3:
						direction.x = 0;
						direction.y = -1;
						animFrames = 2;
						animRow = 8;

						break;
					}
					break;
				}
			}
		}
	}

	for (size_t i = 0; i < monsters->size(); i++) {
		Monster* temp = (*monsters)[i];
		if (temp != this) {
			if (collider->intersects(*temp->collider)) {
				direction = -direction;
			}
		}
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
				curr_x =(int) (collider->getPosition().x / cell_size);
				curr_y = (int)(collider->getPosition().y / cell_size);
				if (curr_x == i && curr_y == j)
				{
					for (auto it = monsters->begin(); it != monsters->end(); it++)
					{
						if (*it == this)
						{
							monsters->erase(it);
							player->addKill();
							break;
						}
					}

					delete this;
					return;
				}
				break;
			}

		}
	}

	if (collider->intersects(*player->getCollider())) {
		player->die();
	}
	anim.setPosition(position.x-8, position.y-12);
}

void Monster::setPosition(sf::Vector2f& position)
{
	this->position = position- sf::Vector2f(size/2, size/2);
}
