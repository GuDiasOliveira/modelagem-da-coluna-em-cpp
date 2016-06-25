#pragma once

#include "Positionable.h"


namespace humanSpine
{

	class Head : public Positionable
	{

	private:

		double m_radius;

	public:

		Head() : m_radius(0)
		{
		}

		Head(double radius)
		{
			if (radius < 0)
				radius = 0;
			m_radius = radius;
		}

		bool setRadius(double radius)
		{
			if (radius < 0)
				return false;
			m_radius = radius;
			return true;
		}

		double getRadius()
		{
			return m_radius;
		}

		virtual ~Head()
		{
		}

	};

}