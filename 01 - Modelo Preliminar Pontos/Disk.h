#pragma once

#include "Positionable.h"
#include<cmath>

using namespace pointsModel;


namespace humanSpine
{

	class Disk : public Positionable
	{

	private:

		double m_height, m_deltaHeight, m_width;

	public:

		Disk() : m_height(0), m_deltaHeight(0), m_width(0)
		{
		}

		bool setHeight(double height)
		{
			if (height < 0)
				return false;
			m_height = height;
			if (m_deltaHeight > m_height)
				m_deltaHeight = m_height;
			else if (-m_deltaHeight > m_height)
				m_deltaHeight = -m_height;
			return true;
		}

		double getHeight()
		{
			return m_height;
		}

		bool setDeltaHeight(double deltaHeight)
		{
			if (abs(deltaHeight) > m_height)
				return false;
			m_deltaHeight = deltaHeight;
			return true;
		}

		double getDeltaHeight()
		{
			return m_deltaHeight;
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

		virtual ~Disk()
		{
		}

	};

}