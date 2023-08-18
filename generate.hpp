/*
it is generate.hpp file which takes input the area object along with the color quantifier(value iterations reqd to diverge a 
fractal of particaur complex no.) to feed the color rgb values into the area object to produce a png image using FreeImage 
library named mandelbrot.png further this image will get displayed upon the window
*/

#include <vector>

#ifndef GENERATE_HPP
#define GENERATE_HPP

#include "area.hpp"

void plot(area<int> &scr, std::vector<int> &colors, int iter_max, const char *fname, bool smooth_color);

#endif // GENERATE_HPP