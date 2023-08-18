/*
it is the main.cpp file Start reading code from the main function and go into respective hpp files for better understanding
*/

#include <iostream>
#include <complex>
#include <vector>
#include <functional>
#include <thread>
#include <stack>
#include <mutex>
#include <SFML/Graphics.hpp>

#include "area.hpp"
#include "generate.hpp"
#include "customisations.hpp"
#include "functions.hpp"
#include "tools.hpp"

using Complex = std::complex<double>;

// function to be used in threads for imagifying the captured fractal element , produced image to be displayed on window
void Imagify_the_Capture(const double a, const double z, const double r, std::vector<bool> &flags, std::mutex &imageLock)
{
	area<int> scr(0, WIN_SIZE, 0, WIN_SIZE);
	//next window to be mapped with the captured fractal element    see area.hpp

	area<double> fract(a, a + r, z - r, z);
	//captured fractal area object    see area.hpp

	auto func = [](Complex z, Complex c) -> Complex
	{ return z * z + c; };
	// MANDELBROT SET EQUATION      CAN BE ALTERED TO GET OTHER SETS TOO

	std::vector<int> colors(scr.size());
	// vector to contain divergence iteration count as pixel color measure

	imageLock.lock();
	fractal(scr, fract, MAX_ITER, colors, func, FNAME, SMOOTH); // code in tools.hpp
	imageLock.unlock();
	flags[1] = true;
}

// function to load the window using a thread and mutex locks associated to it so as to ease queuing of cpatures
void Load_Window(std::stack<std::tuple<double, double, double>> &zoom_coords, std::vector<bool> &flags, std::mutex &imageLock)
{
	// thread generation using function and parameters it requires
	std::thread t(Imagify_the_Capture, std::get<0>(zoom_coords.top()), std::get<1>(zoom_coords.top()), std::get<2>(zoom_coords.top()), std::ref(flags), std::ref(imageLock));
	t.detach();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE, WIN_SIZE), TITLE, sf::Style::Close);
	window.setFramerateLimit(60);

	std::vector<bool> flags(2, false);

	std::stack<std::tuple<double, double, double>> zoom_coords;

	zoom_coords.push({-2, 2, 4});

	std::mutex imageLock;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i capture_start;
	sf::Vector2i capture_end;
	sf::RectangleShape capture;
	sf::Event event;

	// Initialising the variables introduced above  code in functions.hpp
	Initialise(texture, sprite, capture_start, capture_end, capture);

	Load_Window(zoom_coords, flags, imageLock);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::BackSpace: // TO ZOOM OUT
					zoomOut(zoom_coords);	  // code in tools.hpp
					Load_Window(zoom_coords, flags, imageLock);
					break;
				default:
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left: // Start capturing using a rectangle

					StartCapturing(capture_start, flags, window); // code in tools.hpp
					break;
				default:
					break;
				}
				break;
			case sf::Event::MouseButtonReleased:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:								 // Caturing complete when released , captured area will get ZOOMED IN
					EndCapturing(capture_start, capture_end, flags, window); // code in tools.hpp
					zoomIn(capture_start, capture_end, zoom_coords);		 // code in tools.hpp
					Load_Window(zoom_coords, flags, imageLock);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		// Updating the variables after selected event  code in functions.hpp
		Update(window, texture, sprite, capture_start, capture_end, capture, zoom_coords, flags, imageLock);

		window.clear();

		// Displaying the generated image on window
		window.draw(sprite);

		if (flags[0]) // for time until the capturing mouse left click is released
			window.draw(capture);

		window.display();
	}
	return 0;
}