#pragma once

#include "Point.h"
#include "Utils.h"

using namespace pointsModel;


namespace humanSpine
{

	class Positionable
	{

	private:

		double m_angle;

	protected:

		Positionable()
		{
		}

	public:

		Point position;

		bool setAngle(double angle)
		{
			while (angle > 2 * PI)
				angle -= 2 * PI;
			while (angle < 0)
				angle += 2 * PI;
			m_angle = angle;
		}

		double getAngle()
		{
			return m_angle;
		}

		virtual ~Positionable()
		{
		}

	};

}