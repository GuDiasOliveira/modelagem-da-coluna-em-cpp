#pragma once

namespace pointsModel
{

	class Point
	{
	public:

		double x, y;

		Point()
		{
			x = y = 0.0;
		}

		Point(double x, double y)
		{
			this->x = x;
			this->y = y;
		}

		Point operator+(Point p)
		{
			return Point(x + p.x, y + p.y);
		}

		Point operator-(Point p)
		{
			return Point(x - p.x, y - p.y);
		}

		Point operator*(double mult)
		{
			return Point(x * mult, y * mult);
		}

		Point operator/(double mult)
		{
			return Point(x / mult, y / mult);
		}

		void operator+=(Point p)
		{
			x += p.x;
			y += p.y;
		}

		void operator-=(Point p)
		{
			x -= p.x;
			y -= p.y;
		}

		void operator*=(double mult)
		{
			x *= mult;
			y *= mult;
		}

		void operator/=(double mult)
		{
			x /= mult;
			y /= mult;
		}

		Point operator-()
		{
			return Point(-x, -y);
		}

		virtual ~Point()
		{
		}
	};

}