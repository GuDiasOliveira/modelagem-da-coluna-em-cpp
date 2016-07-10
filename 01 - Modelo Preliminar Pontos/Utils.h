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

	template <typename T> std::string& to_string(T& x);
	float to_sfmlAngle(double angle);
	void delimitAngle(double &radAngle);
	void delimitAnglef(float &radAngle);
	float distance(sf::Vector2f p1, Vector2f p2);
	Vector2f rotatePoint(Vector2f initialPoint, float angle, Vector2f origin);
	float sign(Vector2f p1, Vector2f p2, Vector2f p3);
	bool pointInTriangle(Vector2f point, Vector2f v1, Vector2f v2, Vector2f v3);


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
		int revs = floor(radAngle / 2 * PI);
		radAngle -= 2 * PI * revs;
	}

	void delimitAnglef(float &radAngle)
	{
		int revs = floor(radAngle / 2 * PI);
		radAngle -= 2 * PI * revs;
	}

	float distance(sf::Vector2f p1, Vector2f p2)
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

	/*bool collision(sf::Vector2f point, sf::FloatRect area)
	{
		float x1 = area.left;
		float y1 = area.top;
		float x2 = x1 + area.width;
		float y2 = y1 + area.height;
		float x = point.x;
		float y = point.y;
		return x >= x1 && x <= x2 && y >= y1 && y <= y2;
	}*/

	//bool collision(sf::Vector2f point, sf::FloatRect area, float rotation, sf::Vector2f localAreaOrigin)
	//{
	//	Vector2f globalAreaOrigin = localAreaOrigin + Vector2f(area.left, area.top); // convert to global
	//	Vector2f point2 = rotatePoint(point, -rotation, globalAreaOrigin);
	//	return area.contains(point2);
	//	//return collision(point2, area);
	//}

	float sign(Vector2f p1, Vector2f p2, Vector2f p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	bool pointInTriangle(Vector2f point, Vector2f v1, Vector2f v2, Vector2f v3)
	{
		bool b1, b2, b3;

		b1 = sign(point, v1, v2) < 0.0f;
		b2 = sign(point, v2, v3) < 0.0f;
		b3 = sign(point, v3, v1) < 0.0f;

		return ((b1 == b2) && (b2 == b3));
	}

	


	class Collision
	{
	private:

		Vector2f m_rectanglePoints[4];
		float m_rotation;

		float scalarProduct(Vector2f v1, Vector2f v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

	public:

		Collision()
		{
		}

		void setRectangle(FloatRect rectangle, float rotation, Vector2f localAreaOrigin)
		{
			Utils::delimitAnglef(rotation);

			m_rectanglePoints[0] = { rectangle.left, rectangle.top };
			m_rectanglePoints[1] = { rectangle.left + rectangle.width, rectangle.top };
			m_rectanglePoints[2] = { rectangle.left + rectangle.width, rectangle.top + rectangle.height };
			m_rectanglePoints[3] = { rectangle.left, rectangle.top + rectangle.height };

			Vector2f globalAreaOrigin = localAreaOrigin + Vector2f(rectangle.left, rectangle.top);
			for (int i = 0; i < 4; i++)
				m_rectanglePoints[i] = Utils::rotatePoint(m_rectanglePoints[i], rotation, globalAreaOrigin);
		}

		bool collision(Vector2f point)
		{
			Vector2f ap = point - m_rectanglePoints[0];
			Vector2f ab = m_rectanglePoints[1] - m_rectanglePoints[0];
			Vector2f ad = m_rectanglePoints[3] - m_rectanglePoints[0];

			float ap_ab = scalarProduct(ap, ab);
			float ab_ab = scalarProduct(ab, ab);
			float ap_ad = scalarProduct(ap, ad);
			float ad_ad = scalarProduct(ad, ad);

			return ab_ab > ap_ab && ap_ab > 0 && ad_ad > ap_ad && ap_ad > 0;
		}

		virtual ~Collision()
		{
		}
	};


	bool collision(sf::Vector2f point, sf::FloatRect area, float rotation, sf::Vector2f localAreaOrigin)
	{
		/*Vector2f areaPoints[4] =
		{
		{area.left, area.top},
		{area.left + area.width, area.top},
		{area.left + area.width, area.top + area.height},
		{area.left, area.top + area.height}
		};

		sf::Vector2f globalAreaOrigin = localAreaOrigin + Vector2f(area.left, area.top);
		for (int i = 0; i < 4; i++)
		areaPoints[i] = rotatePoint(areaPoints[i], rotation, globalAreaOrigin);*/
		Collision coll;
		coll.setRectangle(area, rotation, localAreaOrigin);
		return coll.collision(point);
	}
}