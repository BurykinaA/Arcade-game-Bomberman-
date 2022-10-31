#pragma once
#include <SFML/Graphics.hpp>

//! @authors Бурыкина А.И.
//! @brief класс коллайдера 
class BoxCollider
{
public:
	//! @brief конструкор, принимающий область (прямоугольник)
	BoxCollider(const sf::FloatRect& rect);
	//! @brief метод, проверяющий пересечения с другими объектами типа BoxCollider
	bool intersects(const BoxCollider& other);
	//! @brief задаем позицию нашему коллайдеру
	void setPosition(float x, float y);
	//! @brief метод рисующий наш коллайдер
	/*! нужен для отладки и проверки корректной работы*/
	void draw(sf::RenderWindow& window);
	//!@brief  возвращет ширину коллайдера
	float getWidth() {
		return rect.width;
	}
	//! @brief возвращает высоту коллайдера
	float getHeight() {
		return rect.height;
	}
	//! @brief возвращает позицию нашего коллайдера
	sf::Vector2f getPosition();
private:
	sf::FloatRect rect;
};

