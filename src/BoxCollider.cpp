#include "BoxCollider.h"

BoxCollider::BoxCollider(const sf::FloatRect& rect) : rect(rect)
{
}

bool BoxCollider::intersects(const BoxCollider& other)
{
    return rect.intersects(other.rect);
}

void BoxCollider::setPosition(float x, float y)
{
    rect.left = x;
    rect.top = y;
}

void BoxCollider::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(this->rect.width, this->rect.height));
    rect.setPosition(this->rect.left , this->rect.top);
    rect.setFillColor(sf::Color::Red);
    window.draw(rect);
}

sf::Vector2f BoxCollider::getPosition()
{
    return sf::Vector2f(rect.left, rect.top);
}
