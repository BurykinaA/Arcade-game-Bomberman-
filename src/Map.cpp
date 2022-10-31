#include "Map.h"
#include "LevelBar.h"
#include "Spawner.h"

int Map::getLevel()
{
	return lb.getLevel();
}

void Map::generate()
{
	lb.addLevel();
	srand((unsigned int)time(NULL));

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (block_colliders[i][j] != nullptr)
				delete block_colliders[i][j];

			block_colliders[i][j] = nullptr;
		}
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			sf::FloatRect rect;
			rect.height = (float)cell_size;
			rect.width = (float)cell_size;
			rect.left = (float)(i * cell_size);
			rect.top = (float)(j * cell_size);
			if (i == 0 || j == 0 || i == rows - 1 || j == columns - 1) {
				blocks[i][j] = BLOCK_TYPE::WALL;
				block_colliders[i][j] = new BoxCollider(rect);
				continue;
			}

			if (i % 2 == 0 && j % 2 == 0) {
				blocks[i][j] = BLOCK_TYPE::WALL;
				block_colliders[i][j] = new BoxCollider(rect);
				continue;
			}
			if ((i == 1 && (j == 1 || j == 2)) || (j == 1 && i == 2)) {
				blocks[i][j] = BLOCK_TYPE::GROUND;

				continue;
			}

			if (rand() % 2 == 0)
			{
				blocks[i][j] = BLOCK_TYPE::GROUND;
			}
			else
			{
				blocks[i][j] = BLOCK_TYPE::BOX;
				block_colliders[i][j] = new BoxCollider(rect);
			}
		}
	}

	spawner->spawn(this);
}

void Map::fireCell(float x, float y, float time)
{
	int w = cell_size;
	int i = (int)(x / w);
	int j = (int)(y / w);
	auto current_block = blocks[i][j];
	fire_life_time = time;
	if (current_block == Map::BLOCK_TYPE::BOX || current_block == Map::BLOCK_TYPE::GROUND)
	{
		auto c = block_colliders[i][j];
		if (c != nullptr)
			delete c;
		block_colliders[i][j] = nullptr;

		blocks[i][j] = Map::BLOCK_TYPE::FIRE;

		timer = 0;
	}

}

void Map::draw(sf::RenderWindow& window)
{
	sf::Texture t1;
	t1.loadFromFile("../images/tileset.png");
	sf::Sprite anim1;
	anim1.setTexture(t1);
	sf::Texture t2;
	sf::Sprite anim2;
	t2.loadFromFile("../images/fire.png");
	anim2.setTexture(t2);
	anim2.setTextureRect(sf::IntRect(32, 32, 16, 16));
	anim2.setScale(2, 2);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {

			BLOCK_TYPE current_block = blocks[i][j];
			sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f((float)cell_size, (float)cell_size));
			rect.setPosition((float)(i * cell_size), (float)(j * cell_size));
			switch (current_block)
			{
			case Map::BLOCK_TYPE::GROUND:
				anim1.setTextureRect(sf::IntRect(32, 0, 32, 32));
				anim1.setPosition((float)(i * cell_size), (float)(j * cell_size));
				window.draw(anim1);
				rect.setFillColor(sf::Color::White);
				break;
			case Map::BLOCK_TYPE::WALL:
				anim1.setTextureRect(sf::IntRect(64, 0, 32, 32));
				anim1.setPosition((float)(i * cell_size), (float)(j * cell_size));
				window.draw(anim1);
				rect.setFillColor(sf::Color::Black);
				break;
			case Map::BLOCK_TYPE::BOX:
				anim1.setTextureRect(sf::IntRect(64, 32, 32, 32));
				anim1.setPosition((float)(i * cell_size), (float)(j * cell_size));
				window.draw(anim1);
				rect.setFillColor(sf::Color::Yellow);
				break;
			case Map::BLOCK_TYPE::FIRE:
				anim2.setPosition((float)(i * cell_size), (float)(j * cell_size));
				anim1.setTextureRect(sf::IntRect(32, 0, 32, 32));
				anim1.setPosition((float)(i * cell_size), (float)(j * cell_size));
				window.draw(anim1);
				window.draw(anim2);
				rect.setFillColor(sf::Color::Red);
				break;

			default:
				break;
			}
			//window.draw(rect);
		}
	}
	lb.draw(window);
}

void Map::update(float dt)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			auto block = blocks[i][j];
			if (block == Map::BLOCK_TYPE::FIRE)
			{
				if (timer >= fire_life_time)
				{
					blocks[i][j] = Map::BLOCK_TYPE::GROUND;
				}
			}
		}
	}

	timer += dt;
}

Map::BLOCK_TYPE Map::getBlock(int i, int j)
{
	return blocks[i][j];
}

BoxCollider* Map::getBlockCollider(int i, int j)
{
	if (i < 0 || j < 0 || i > rows - 1 || j > columns - 1)
		return nullptr;
	return block_colliders[i][j];
}

int Map::getRowsCount()
{
	return rows;
}

int Map::getColumnsCount()
{
	return columns;
}

int Map::getCellSize()
{
	return cell_size;
}

void Map::restart()
{
	
	lb.resetLevel();
	spawner->restart();
	generate();
}

void Map::fireOff()
{
	timer = 2;
}

sf::Vector2f Map::getOriginPosition()
{
	return sf::Vector2f(36, 36);
}

void Map::setSpawner(Spawner* spawner)
{
	this->spawner = spawner;
}

Map::Map()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			block_colliders[i][j] = nullptr;
			blocks[i][j] = BLOCK_TYPE::NONE;
		}
	}
}




