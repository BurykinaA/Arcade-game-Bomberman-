#include "Killbar.h"
#include <string>
using namespace std;
Killbar::Killbar()
{
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}

void Killbar::draw(sf::RenderWindow& window)
{
    sf::Text text;
    text.setFont(font);
    text.setPosition(605 - 40 *3, 60);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(30);
    text.setString(("Kills: " + to_string(kills)).c_str());
    window.draw(text);
}


void Killbar::resetKills()
{
    kills = 0;
}

void Killbar::addKill()
{
    kills++;
}

int Killbar::getKills()
{
    return kills;
}

