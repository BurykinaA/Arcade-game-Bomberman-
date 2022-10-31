#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Monster.h"
#include "Spawner.h"
#include <fstream>


void menu(sf::RenderWindow & window) {
	sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("../images/111.png");
	menuTexture2.loadFromFile("../images/222.png");
	menuTexture3.loadFromFile("../images/333.png");
	aboutTexture.loadFromFile("../images/about.png");
	menuBackground.loadFromFile("../images/boom.jpg");
	sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(60, 30);
	menu2.setPosition(60, 90);
	menu3.setPosition(60, 150);
	menuBg.setPosition(280, 0);

	while (isMenu)
	{
		menu1.setColor(sf::Color::White);
		menu2.setColor(sf::Color::White);
		menu3.setColor(sf::Color::White);
		menuNum = 0;
		window.clear(sf::Color::Black);

		if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Red); menuNum = 1; }
		if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Red); menuNum = 2; }
		if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Red); menuNum = 3; }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}

//const char* path = "save.txt";
//void save()
//{
//	std::ofstream file(path);
//	file << "hello world" << std::endl;
//}

//void load()
//{
//
//}

int main()
{

	sf::RenderWindow window(sf::VideoMode(600, 600), "BomberMan", sf::Style::Close);

	//std::ifstream input_file(path);
	menu(window);
	Map map;
	//if (input_file)
	//	map.load(input_file);
	Player player(&map);
	//if (input_file)
	//	player.load(input_file);
	std::vector<Monster*> monsters;
	Spawner spawner(&monsters, &player);
	//if (input_file)
	//	spawner.load(input_file);
	map.setSpawner(&spawner);
	//input_file.close();

	map.generate();
	//map.setSpawner(&spawner);
	sf::Clock clock;
	clock.restart();
	while (window.isOpen())
	{
		sf::Event event;
		float dt = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				//std::ofstream output_file(path);
				//map.save(output_file);
				//player.save(output_file);
				//spawner.save(output_file);
				window.close();
			}
		}

		if (window.sf::Window::hasFocus()) {
			window.clear(sf::Color::Black);

			player.update(dt);
			map.update(dt);
			for (auto it : monsters)
				it->update(dt);


			map.draw(window);
			player.draw(window);
			for (auto it : monsters)
				it->draw(window);
			window.display();
		}
	}
	

}
