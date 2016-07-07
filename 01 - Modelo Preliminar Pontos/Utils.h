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

	Vector2f rotatePoint(Vector2f initialPoint, float fromAngle, float toAngle, float radius)
	{
		if (radius < 0)
			radius = 0;
		fromAngle *= PI / 180; // to radians
		toAngle *= PI / 180; // to radians

		Vector2f finalPoint = initialPoint - Vector2f(cos(fromAngle), sin(fromAngle)) * radius;
		finalPoint += Vector2f(cos(toAngle), sin(toAngle)) * radius;
		return finalPoint;
	}

	float distance(sf::Vector2f p1, Vector2f p2)
	{
		float deltaX = abs(p1.x - p2.x);
		float deltaY = abs(p1.y - p2.y);
		return sqrt(deltaX * deltaX + deltaY * deltaY);
	}

	bool collision(sf::Vector2f point, sf::FloatRect area, float rotation, sf::Vector2f areaOrigin)
	{
		areaOrigin += {area.left, area.top}; // convert to global
		point = rotatePoint(point, rotation, 0, distance(point, areaOrigin));
		return area.contains(point);
	}


}