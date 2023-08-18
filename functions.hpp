/*
it is functions.hpp file which covers sevral member variables related functions (initialising them accessing them etc)
generated in the main.cpp
*/

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "customisations.hpp"

void Initialise(sf::Texture &texture, sf::Sprite &sprite,
                const sf::Vector2i &capture_start, const sf::Vector2i &capture_end, sf::RectangleShape &capture);
// iniatialises the varaibles sprite ,texture ,capturing clicks and the capture rectangle defined in main.cpp

void InitSprite(sf::Texture &texture, sf::Sprite &sprite);

void InitRectangle(const sf::Vector2i &capture_start, const sf::Vector2i &capture_end, sf::RectangleShape &capture);

void Update(const sf::RenderWindow &window,
            sf::Texture &texture, sf::Sprite &sprite,
            const sf::Vector2i &capture_start, const sf::Vector2i &capture_end, sf::RectangleShape &capture,
            const std::stack<std::tuple<double, double, double>> &zoom_coords,
            std::vector<bool> &flags, std::mutex &imageLock);
// updates the varaibles sprite ,texture ,capturing clicks and the capture rectangle defined in main.cpp after every event
// input taken from mouse or keyboard on the window

void UpdateSprite(sf::Texture &texture, sf::Sprite &sprite, std::vector<bool> &flags, std::mutex &imageLock);

void UpdateRectangle(const sf::RenderWindow &window, const sf::Vector2i &capture_start, sf::RectangleShape &capture);

#endif // FUNCTIONS_HPP