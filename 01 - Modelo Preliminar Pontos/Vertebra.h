#pragma once

#include "Positionable.h"


namespace humanSpine
{

	class Vertebra : public Positionable
	{

	private:

		double m_height, m_width;

	public:

		Vertebra() : m_height(0), m_width(0)
		{
		}

		bool setHeight(double height)
		{
			if (height < 0)
				return false;
			m_height = height;
			return true;
		}

		double getHeight()
		{
			return m_height;
		}

		bool setWidth(double width)
		{
			if (width < 0)
				return false;
			m_width = width;
			return true;
		}

		double getWidth()
		{
			return m_width;
		}

		virtual ~Vertebra()
		{
		}

	};

}
