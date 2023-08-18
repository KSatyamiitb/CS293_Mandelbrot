#include <iostream>
#include <complex>
#include <functional>
#include <stack>
#include <mutex>
#include <SFML/Graphics.hpp>

#include "area.hpp"
#include "generate.hpp"
#include "customisations.hpp"
#include "functions.hpp"
#include "tools.hpp"

using Complex = std::complex<double>;

void fractal(area<int> &scr, area<double> &fract, int iter_max, std::vector<int> &colors,
             const std::function<Complex(Complex, Complex)> &func, const char *fname, bool smooth_color)
{
    get_number_iterations(scr, fract, iter_max, colors, func);
    plot(scr, colors, iter_max, fname, smooth_color); // code in generate.hpp
}

void get_number_iterations(area<int> &scr, area<double> &fract, int iter_max, std::vector<int> &colors,
                           const std::function<Complex(Complex, Complex)> &func)
{

    int k = 0, i, j;
    Complex c;
    for (i = scr.y_top(); i < scr.y_bottom(); ++i)
    {
        for (j = scr.x_left(); j < scr.x_right(); ++j)
        {
            c = {(double)j, (double)i};
            c = scale(scr, fract, c);
            colors[k] = count_itern(c, iter_max, func);
            ++k;
        }
    }
}

Complex scale(area<int> &scr, area<double> &fr, Complex c)
{
    Complex temp(c.real() / (double)scr.width() * fr.width() + fr.x_left(), c.imag() / (double)scr.height() * fr.height() + fr.y_top());
    return temp;
}

int count_itern(Complex c, int iter_max, const std::function<Complex(Complex, Complex)> &func)
{
    Complex z(0);
    double z_r_sq = 0;
    double z_i_sq = 0;

    int iter = 0;
    while (z_r_sq + z_i_sq <= 4.0 && iter < iter_max) // counting iterations to diverge fractal eqn
    {
        z.imag((z.real() + z.imag()) * (z.real() + z.imag()) - z_r_sq - z_i_sq);
        z.imag(z.imag() + c.imag());
        z.real(z_r_sq - z_i_sq + c.real());
        z_r_sq = z.real() * z.real();
        z_i_sq = z.imag() * z.imag();
        iter++;
    }
    return iter;
}

void StartCapturing(sf::Vector2i &capture_start, std::vector<bool> &flags, const sf::RenderWindow &window)
{
    capture_start = sf::Mouse::getPosition(window);
    flags[0] = true;
}

void EndCapturing(sf::Vector2i &capture_start, sf::Vector2i &capture_end, std::vector<bool> &flags, const sf::RenderWindow &window)
{
    capture_end = sf::Mouse::getPosition(window);
    flags[0] = false;
}

void zoomIn(sf::Vector2i &capture_start, sf::Vector2i &capture_end, std::stack<std::tuple<double, double, double>> &zoom_coords)
{
    try
    {
        if (capture_start.x < 0 || capture_start.x >= WIN_SIZE ||
            capture_start.y < 0 || capture_start.y >= WIN_SIZE)
            throw "Position of beginning of capture is outside window!";
        if (capture_end.x < 0 || capture_end.x >= WIN_SIZE ||
            capture_end.y < 0 || capture_end.y >= WIN_SIZE)
            throw "Position of end of capture is outside window!";

        double x0 = std::get<0>(zoom_coords.top());
        double y0 = std::get<1>(zoom_coords.top());
        double r = std::get<2>(zoom_coords.top());

        double new_x0 = x0 + r * capture_start.x / WIN_SIZE; // scaling x0 wrt the captured element
        double new_y0 = y0 - r * capture_start.y / WIN_SIZE; // scaling y0 wrt the captured element

        double tmp = x0 + r * capture_end.x / WIN_SIZE;
        r = tmp - new_x0; // scaling r wrt the captured element

        zoom_coords.push({new_x0, new_y0, r});
    }
    catch (const std::string &e)
    {
        std::cerr << e << std::endl;
    }
}

void zoomOut(std::stack<std::tuple<double, double, double>> &zoom_coords)
{
    if (zoom_coords.size() > 1)
        zoom_coords.pop(); // next zoom_coords in stack represent previous display
}
