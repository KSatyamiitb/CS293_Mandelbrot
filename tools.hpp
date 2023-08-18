/*
it is tools.hpp file which handle the tools which interact directly with the window displayed
*/

#include <complex>

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "area.hpp"
#include "generate.hpp"
#include "customisations.hpp"
#include "functions.hpp"

using Complex = std::complex<double>;


// fractal function which takes in the captured area object as well as new area object to be developed
// it ,using functions get_number_iterations ,fills up the colors vector for the new area object scr pixel's data
// and further uses it to generate the image to be displayed using plot function of grnerate.hpp
void fractal(area<int> &scr, area<double> &fract, int iter_max, std::vector<int> &colors,
             const std::function<Complex(Complex, Complex)> &func, const char *fname, bool smooth_color);


// first scales the captured fract element to the new area object accordingly for getting complex number grid
// then fills up color vector by iterations counts as a quantitative measure
void get_number_iterations(area<int> &scr, area<double> &fract, int iter_max, std::vector<int> &colors,
                           const std::function<Complex(Complex, Complex)> &func);

// scales captured fract to new area complex numbers
Complex scale(area<int> &scr, area<double> &fr, Complex c);

// counts iterations done for the fractal to diverge
int count_itern(Complex c, int iter_max, const std::function<Complex(Complex, Complex)> &func);


// capturing methods to be done via mouse click events
void StartCapturing(sf::Vector2i &capture_start, std::vector<bool> &flags, const sf::RenderWindow &window);

void EndCapturing(sf::Vector2i &capture_start, sf::Vector2i &capture_end, std::vector<bool> &flags, const sf::RenderWindow &window);


// Zoom into the captured fractal element  
void zoomIn(sf::Vector2i &capture_start, sf::Vector2i &capture_end, std::stack<std::tuple<double, double, double>> &zoom_coords);

// Zoom out to previous display
void zoomOut(std::stack<std::tuple<double, double, double>> &zoom_coords);

#endif // TOOLS_HPP