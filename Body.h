#include<cmath>
#include<utility>
constexpr float PI = 3.141592;

float deg_rad(const float degrees)
{
	return degrees * PI / 180.0;
}

float rad_deg(const float radians)
{
	return radians * 180.0 / PI;
}

class Body2D
{
public:
	Body2D(){};
	virtual float calculate_Perimeter() = 0;
	virtual float calculate_Area() = 0;
	virtual std::pair<float, float> getCenter() = 0;
	virtual ~Body2D() {};
};

class Body3D : public Body2D
{
public:
	Body3D(){};
	virtual float calculate_Volume() = 0;
	virtual float calculate_SurfaceArea() = 0;
	virtual ~Body3D() {};
};

class Parallelogram : public Body2D
{
public:
	Parallelogram(float length, float width, float alpha) : length{ length }, width{ width }, alpha{ alpha }{};
	float calculate_Perimeter() override { return 2 * (length + width); };
	float calculate_Area() override { return length * width * sin(deg_rad(alpha)); };
	std::pair<float, float> getCenter() override { return std::make_pair(length / 2.0, width / 2.0); };
	~Parallelogram() {};
private:
	float length;
	float width;
	float alpha;
};

class Ellipse : public Body2D
{
public:
	Ellipse(float length, float width) : length{ length }, width{width} {};
	float calculate_Perimeter() override { return 2 * PI * sqrt((pow(length, 2) + pow(width, 2)) / 8); };
	float calculate_Area() override { return PI * length * width / 4; };
	std::pair<float, float> getCenter() override { return std::make_pair(length / 2.0, width / 2.0); };
	~Ellipse() {};
private:
	float length;
	float width;
};

class Ball : public Body3D
{
public:
	Ball(const float radius) : radius{ radius } {};
	float calculate_Volume() override { return 4 * PI * pow(radius, 3) / 3; };
	float calculate_SurfaceArea() override { return 4 * PI * pow(radius, 2); };
	~Ball() {};
private:
	float radius;
};

class Box : public Body3D
{
public:
	Box(const float length, const float width, const float height) : length{ length }, width{ width }, height{ height }{};
	float calculate_Volume() override { return length * width * height; };
	float calculate_SurfaceArea() override { return 2 * (length * width + length * height + width * height); };
	~Box() {};
private:
	float length;
	float width;
	float height;
};