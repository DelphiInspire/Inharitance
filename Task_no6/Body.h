#include<cmath>
#include<vector>
#include"exceptions_list.h"

enum class pointPositions { bottomLeftVertice, topLeftVertice, bottomRightVertice, topRightVertice};

class coordinates_2D
{
public:
    coordinates_2D(float x, float y): x{x}, y{y}{};
    coordinates_2D(std::initializer_list<float> input_coordinates);

    friend coordinates_2D operator-(const coordinates_2D& firstMember, const coordinates_2D& secondMember)
    {
        return coordinates_2D{firstMember.x - secondMember.x, firstMember.y - secondMember.y};
    }

    friend coordinates_2D operator+(const coordinates_2D& firstMember, const coordinates_2D& secondMember)
    {
        return coordinates_2D{firstMember.x + secondMember.x, firstMember.y + secondMember.y};
    }

    coordinates_2D operator/(const float divider) const
    {
        return coordinates_2D{x / divider, y / divider};
    }

    float get_X() const {return x;};
    float get_Y() const {return y;};
private:
    float x;
    float y;
    std::initializer_list<float>::iterator input_arg_it;
    const int num_input_params{2};
    std::string error_msg_log{" "};
};


class coordinates_3D
{
public:
    coordinates_3D(float x, float y, float z): x{x}, y{y}, z{z}{};
    coordinates_3D(std::initializer_list<float> input_coordinates);

    friend coordinates_3D operator-(const coordinates_3D& firstMember, const coordinates_3D& secondMember)
    {
        return coordinates_3D{firstMember.x - secondMember.x, firstMember.y - secondMember.y, firstMember.z - secondMember.z};
    }

    friend coordinates_3D operator+(const coordinates_3D& firstMember, const coordinates_3D& secondMember)
    {
        return coordinates_3D{firstMember.x + secondMember.x, firstMember.y + secondMember.y, firstMember.z - secondMember.z};
    }

    coordinates_3D operator/(const float divider) const
    {
        return coordinates_3D{x / divider, y / divider, z / divider};
    }

    float get_X() const {return x;};
    float get_Y() const {return y;};
    float get_Z() const {return z;};
private:
    float x;
    float y;
    float z;
    std::initializer_list<float>::iterator input_arg_it;
    const int num_input_params{3};
    std::string error_msg_log{""};
};

class Body2D
{
public:
    Body2D(){};
 	virtual float calculate_Perimeter() = 0;
 	virtual float calculate_Area() = 0;
    virtual coordinates_2D get_center() const = 0;
	virtual ~Body2D() {};
};

class Body3D
{
public:
	Body3D(){};
 	virtual float calculate_Volume() = 0;
 	virtual float calculate_SurfaceArea() = 0;
    virtual coordinates_3D get_center() const = 0;
	virtual ~Body3D() {};
};

class Parallelogram : public Body2D
{
public:
	Parallelogram(coordinates_2D&& bottomLeftPos,  coordinates_2D&& topLeftPos,
				  coordinates_2D&& bottomRightPos, coordinates_2D&& topRightPos);
	float calculate_Perimeter() override;
	float calculate_Area() override;
	coordinates_2D get_center() const override;
    const std::vector<const coordinates_2D>* getVerteces() const {return &verteces;};
	~Parallelogram() {};
private:
    std::vector<const coordinates_2D> verteces;
    const int num_parallel_sides{2};
    enum class vertecesID{bottomLeftVertece = 0, topLeftVertece, bottomRightVertece, topRightVertece};
};

class Ellipse : public Body2D
{
public:
	Ellipse(coordinates_2D&& init_draw_point, float length, float width) : origin{init_draw_point}, length{ length }, width{width} {};
	float calculate_Perimeter() override;
	float calculate_Area() override;
	coordinates_2D get_center() const override;
	~Ellipse() {};
private:
    coordinates_2D origin;
	float length;
	float width;
};

class Ball : public Body3D
{
public:
    Ball(const coordinates_3D&& init_draw_point, const float radius_vectorLength) : origin{init_draw_point},radius_vector{ radius_vectorLength } {};
	float calculate_Volume() override;
	float calculate_SurfaceArea() override;
	coordinates_3D get_center() const override;
	~Ball() {};
private:
    coordinates_3D origin;
	float radius_vector;
};

class Box : public Body3D
{
public:
	Box(coordinates_3D& front_bottomLeftVertex, coordinates_3D& front_topLeftVertex,
        coordinates_3D& front_bottomRightVertex,coordinates_3D& front_topRightVertex,
        coordinates_3D& back_bottomLeftVertex,  coordinates_3D& back_topLeftVertex,
        coordinates_3D& back_bottomRightVertex, coordinates_3D& back_topRightVertex);

	float calculate_Volume() override;
	float calculate_SurfaceArea() override;
    const std::vector<const coordinates_3D>* getVerteces() const {return &verteces;};
    coordinates_3D get_center() const override;
	~Box() {};
private:
	std::vector<const coordinates_3D> verteces;
    enum class vertecesID {front_bottomLeftVertex = 0, front_topLeftVertex, front_bottomRightVertex, front_topRightVertex,
                            back_bottomLeftVertex, back_topLeftVertex, back_bottomRightVertex, back_topRightVertex};
	float length;
	float width;
	float height;
private:
    static float getEdgeLength(coordinates_3D& firstVertex, coordinates_3D& secondVertex);
};
