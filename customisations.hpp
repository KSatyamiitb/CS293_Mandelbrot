/*
It is customisations.hpp file from where we can alter several important features of the mandelbrot plot to be produced
*/

#ifndef CUSTOMISATIONS_HPP
#define CUSTOMISATIONS_HPP

#define TITLE "MANDELBROT SET ZOOM" // title of the window

#define MAX_ITER 300
// max iterations done per complex number c to confirm whether fractal_c(z) diverges or not
// depending upon its value we can get an idea of pixel color representing the complex number

#define WIN_SIZE 700
// the dimension of squared size window where all displays will be done

#define FNAME "mandelbrot.png"
// the image file in which the fractals are generated and further displayed on window

#define SMOOTH true
// boolean to be used while color generation for each complex no.
// setting it false alters rgb pixel generation method

#endif // CUSTOMISATIONS_HPP