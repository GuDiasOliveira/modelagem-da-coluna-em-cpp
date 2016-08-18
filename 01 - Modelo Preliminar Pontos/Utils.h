#pragma once

#include <iostream>
#include <sstream>
#include <SFML\Graphics.hpp>

#ifndef PI
#define PI 3.14159265359
#endif

namespace Utils
{
	using namespace sf;

	template <typename T> std::string& to_string(T& x)
	{
		std::ostringstream s;
		s << x;
		return s.str();
	}

	float to_sfmlAngle(double angle)
	{
		return (float)angle * 180 / PI;
	}

	void delimitAngle(double &radAngle)
	{
		radAngle = fmod(radAngle, 2 * PI);
	}

	void delimitAnglef(float &radAngle)
	{
		radAngle = (float) fmod(radAngle, 2 * PI);
	}

	float distance(sf::Vector2f p1, sf::Vector2f p2)
	{
		float deltaX = abs(p1.x - p2.x);
		float deltaY = abs(p1.y - p2.y);
		return sqrt(deltaX * deltaX + deltaY * deltaY);
	}

	Vector2f rotatePoint(Vector2f initialPoint, float angle, Vector2f origin)
	{
		angle *= PI / 180; // to radians
		delimitAnglef(angle);

		Vector2f relativeInitialPoint = initialPoint - origin;
		Vector2f relativeFinalPoint;
		relativeFinalPoint.x = relativeInitialPoint.x * cos(angle) - relativeInitialPoint.y * sin(angle);
		relativeFinalPoint.y = relativeInitialPoint.x * sin(angle) + relativeInitialPoint.y * cos(angle);
		Vector2f finalPoint = origin + relativeFinalPoint;
		return finalPoint;
	}

	float sign(Vector2f p1, Vector2f p2, Vector2f p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}
}