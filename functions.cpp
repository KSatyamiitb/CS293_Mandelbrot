#include <iostream>
#include <stack>
#include <mutex>
#include <SFML/Graphics.hpp>

#include "customisations.hpp"
#include "functions.hpp"

void Initialise(sf::Texture &texture, sf::Sprite &sprite,
                const sf::Vector2i &capture_start, const sf::Vector2i &capture_end, sf::RectangleShape &capture)
{
    InitSprite(texture, sprite);
    InitRectangle(capture_start, capture_end, capture);
}

void InitSprite(sf::Texture &texture, sf::Sprite &sprite)
{
    texture.loadFromFile(FNAME);  // loading texture from File FNAME
    sprite.setTexture(texture);   // making sprite out of texture to display it on window
}

void InitRectangle(const sf::Vector2i &capture_start, const sf::Vector2i &capture_end, sf::RectangleShape &capture)
{
    // capturing rectangle properties
    capture.setSize(sf::Vector2f(0, 0));
    capture.setFillColor(sf::Color::Transparent);
    capture.setOutlineColor(sf::Color::White);
    capture.setOutlineThickness(1);
    capture.setPosition(sf::Vector2f(capture_start.x, capture_start.y));
}

void UpdateSprite(sf::Texture &texture, sf::Sprite &sprite, std::vector<bool> &flags, std::mutex &imageLock)
{
    if (imageLock.try_lock())
    {
        if (flags[1])
        {
            texture.loadFromFile(FNAME);
            sprite.setTexture(texture);
            flags[1] = false;
        }
        imageLock.unlock();
    }
}

void UpdateRectangle(const sf::RenderWindow &window, const sf::Vector2i &capture_start, sf::RectangleShape &capture)
{
    capture.setSize(sf::Vector2f(std::abs(sf::Mouse::getPosition(window).x - capture_start.x), std::abs(sf::Mouse::getPosition(window).y - capture_start.y)));
    capture.setPosition(sf::Vector2f(std::min(capture_start.x, sf::Mouse::getPosition(window).x), std::min(capture_start.y, sf::Mouse::getPosition(window).y)));
}

void Update(const sf::RenderWindow &window,
            sf::Texture &texture, sf::Sprite &sprite,
            const sf::Vector2i &capture_start, const sf::Vector2i &capture_end, sf::RectangleShape &capture,
            const std::stack<std::tuple<double, double, double>> &zoom_coords,
            std::vector<bool> &flags, std::mutex &imageLock)
{
    UpdateSprite(texture, sprite, flags, imageLock);
    UpdateRectangle(window, capture_start, capture);
}

#include "functions.hpp"