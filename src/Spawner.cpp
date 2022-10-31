#include "Spawner.h"
#include <vector>
#include "Map.h"

Spawner::Spawner(std::vector<Monster*>* monsters, Player* player) : monsters(monsters), player(player)
{
}

void Spawner::spawn(Map* map)
{
	int counter = 0;

	std::vector<sf::Vector2i> used_positions;
	while (counter != 5) {
		for (int i = map->getColumnsCount() - 1; i >= 0; i--)
		{
			for (int j = map->getRowsCount() - 1; j >= 0; j--)
			{
				if (map->getBlock(i, j) == Map::BLOCK_TYPE::GROUND && !(i == 1 && j == 1 || i == 3 && j == 3 || i == 2 && j == 1 || i == 1 && j == 2 || i == 2 && j == 3 || i == 3 && j == 2 || i == 3 && j == 1 || i == 1 && j == 3))
				{
					int chance = rand() % 100;

					for (auto p : used_positions)
					{
						if (p.x == i && p.y == j)
							continue;
					}

					if (chance < 10)
					{
						auto monster = new Monster(map, monsters, player);
						auto m = sf::Vector2f((float)(i * map->getCellSize()), (float)(j * map->getCellSize())) + sf::Vector2f((float)(map->getCellSize() / 2), (float)(map->getCellSize() / 2));
						monster->setPosition(m);
						used_positions.push_back(sf::Vector2i(i, j));
						monsters->push_back(monster);

						counter++;
						if (counter >= 5)
							return;
					}
				}
			}
		}
	}
}

void Spawner::restart()
{
	for (auto it = monsters->begin(); it != monsters->end(); it++)
	{
		auto curr = *it;
		delete curr;
	}

	monsters->clear();
}
