#include "Body.h"

coordinates_2D::coordinates_2D(std::initializer_list<float> input_coordinates): input_arg_it{input_coordinates.begin()}
{
    try {
        if (input_coordinates.size() != num_input_params)
        {
            throw arg_verification();
        }
        else
        {
            x = *input_arg_it;
            y = *++input_arg_it;
        }
    }
    catch(std::exception& ex)
    {
        error_msg_log = ex.what();
    }
}

coordinates_3D::coordinates_3D(std::initializer_list<float> input_coordinates): input_arg_it{input_coordinates.begin()}
{
    try{
        if (input_coordinates.size() != num_input_params)
        {
            throw arg_verification();
        }
        else
        {
            x = *input_arg_it;
            y = *++input_arg_it;
            z = *++input_arg_it;
        }
    }
    catch(std::exception& ex)
    {
        error_msg_log = ex.what();
    }
}

Parallelogram::Parallelogram(coordinates_2D &&bottomLeftPos, coordinates_2D &&topLeftPos,
                             coordinates_2D &&bottomRightPos,coordinates_2D &&topRightPos)
{
    verteces.push_back(bottomLeftPos);
    verteces.push_back(topLeftPos);
    verteces.push_back(bottomRightPos);
    verteces.push_back(topRightPos);
};

float Parallelogram::calculate_Perimeter()
{
	coordinates_2D LRsideDifference{ verteces.at((size_t) vertecesID::topLeftVertece) - verteces.at((size_t)vertecesID::bottomLeftVertece) };
	coordinates_2D BTsideDifference{ verteces.at((size_t)vertecesID::topLeftVertece) - verteces.at((size_t)vertecesID::topRightVertece) };
	float LRsideLength =  sqrtf(powf(LRsideDifference.get_X(), 2) + powf(LRsideDifference.get_Y(), 2));
	float BTsideLength = sqrtf(powf(BTsideDifference.get_X(), 2) + powf(BTsideDifference.get_Y(), 2));
	return num_parallel_sides * (LRsideLength + BTsideLength);
}

float Parallelogram::calculate_Area()
{
	float height = verteces.at((size_t)vertecesID::topLeftVertece).get_Y() - verteces.at((size_t)vertecesID::bottomLeftVertece).get_Y();
	coordinates_2D bottomSideDifference = verteces.at((size_t)vertecesID::bottomLeftVertece) - verteces.at((size_t)vertecesID::bottomRightVertece) ;
	float bottomSideLength = sqrtf(powf(bottomSideDifference.get_X(), 2) + powf(bottomSideDifference.get_Y(), 2));
	return bottomSideLength * height;
}

coordinates_2D Parallelogram::get_center() const
{
	return coordinates_2D((verteces.at((size_t) vertecesID::bottomLeftVertece) + verteces.at((size_t)vertecesID::topRightVertece)) / 2.0);
}

float Ellipse::calculate_Perimeter()
{
    return 2.0 * M_PI * sqrtf((powf(length, 2.0) + powf(width, 2.0)) / 8.0); ;
}

float Ellipse::calculate_Area()
{
    return M_PI * length * width / 4.0;
};

coordinates_2D Ellipse::get_center() const
{
    return origin;
};

float Ball::calculate_Volume()
{
     return 4.0 * M_PI * powf(radius_vector, 3.0) / 3.0;
}

float Ball::calculate_SurfaceArea()
{
    return 4.0 * M_PI * powf(radius_vector, 2.0);
}

coordinates_3D Ball::get_center() const
{
    return origin;
}

Box::Box(coordinates_3D &front_bottomLeftVertex, coordinates_3D &front_topLeftVertex,
         coordinates_3D &front_bottomRightVertex,coordinates_3D &front_topRightVertex,
         coordinates_3D &back_bottomLeftVertex, coordinates_3D &back_topLeftVertex,
         coordinates_3D &back_bottomRightVertex, coordinates_3D &back_topRightVertex)
{
    verteces.push_back(front_bottomLeftVertex);
    verteces.push_back(front_topLeftVertex);
    verteces.push_back(front_bottomRightVertex);
    verteces.push_back(front_topRightVertex);
    verteces.push_back(back_bottomLeftVertex);
    verteces.push_back(back_topLeftVertex);
    verteces.push_back(back_bottomRightVertex);
    verteces.push_back(back_topRightVertex);
    length = getEdgeLength(front_bottomLeftVertex, front_bottomRightVertex);
    width = getEdgeLength(front_bottomLeftVertex, back_bottomLeftVertex);
    height = getEdgeLength(front_bottomLeftVertex, front_topLeftVertex);
};

float Box::calculate_Volume()
{
    return length * width * height;
};

float Box::calculate_SurfaceArea()
{
    return 2.0 * (length * width + length * height + width * height);
};

coordinates_3D Box::get_center() const
{
    return coordinates_3D{static_cast<float>(length / 2.0), static_cast<float>(width / 2.0), static_cast<float>(height / 2.0)};
};

float Box::getEdgeLength(coordinates_3D& firstVertex, coordinates_3D& secondVertex)
{
	return sqrtf(powf((firstVertex.get_X() - secondVertex.get_X()), 2) +
				powf((firstVertex.get_Y() - secondVertex.get_Y()), 2) +
				powf((firstVertex.get_Z() - secondVertex.get_Z()), 2));
}
