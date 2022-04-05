#include "Body.h"

int main()
{
	Parallelogram par(coordinates_2D(1.0, 9.0), coordinates_2D(-3.0, 6.0), coordinates_2D(3.0, 9.0), coordinates_2D(-1.0, 6.0));
    const std::vector<const coordinates_2D>* a{ par.getVerteces() };
	return 0;
}