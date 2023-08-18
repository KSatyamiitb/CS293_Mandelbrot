/*
It is area.hpp file to analyse the captured portion on the window screen as a specific area to be considered for the new 
zoomed in window to be displayed in next step.

In each thread started in main.cpp there are two area objects 
        one the captured portion to be zoomed in and 
		another a new window sized area 
		    to be matched one to one with the first captured area and respective complex numbers get detailed color
*/

#ifndef AREA_HPP
#define AREA_HPP

template <typename T>
class area
{
	T X_left, X_right, Y_top, Y_bottom;

public:
	area(T x_left, T x_right, T y_top, T y_bottom)
		: X_left(x_left), X_right(x_right), Y_top(y_top), Y_bottom(y_bottom)
	{
	}

	T size() const
	{
		return (width() * height());
	}

	T width() const
	{
		return (X_right - X_left);
	}

	T height() const
	{
		return (Y_bottom - Y_top);
	}

	T x_left() const
	{
		return X_left;
	}

	void x_left(T X_left)
	{
		X_left = X_left;
	}

	T x_right() const
	{
		return X_right;
	}

	void x_right(T X_right)
	{
		X_right = X_right;
	}

	T y_top() const
	{
		return Y_top;
	}

	void y_top(T Y_top)
	{
		Y_top = Y_top;
	}

	T y_bottom() const
	{
		return Y_bottom;
	}

	void y_bottom(T Y_bottom)
	{
		Y_bottom = Y_bottom;
	}

	void reset(T X_left, T X_right, T Y_top, T Y_bottom)
	{
		X_left = X_left;
		X_right = X_right;
		Y_top = Y_top;
		Y_bottom = Y_bottom;
	}
};

#endif // AREA_HPP