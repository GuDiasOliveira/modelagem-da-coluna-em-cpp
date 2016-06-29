#pragma once

#include "Positionable.h"
#include<cmath>

using namespace pointsModel;


namespace humanSpine
{

	class Disk : public Positionable
	{

	private:

		double m_height, m_deltaHeight, m_width, *m_maxDeltaHeight = NULL;

	public:

		Disk() : m_height(0), m_deltaHeight(0), m_width(0)
		{
		}

		bool setHeight(double height)
		{
			if (height < 0)
				return false;
			m_height = height;
			if (m_maxDeltaHeight != NULL && *m_maxDeltaHeight > m_height)
			{
				*m_maxDeltaHeight = m_height;
			}
			double maxDeltaHeight = getMaxDeltaHeight();
			if (m_deltaHeight > maxDeltaHeight)
				m_deltaHeight = maxDeltaHeight;
			else if (-m_deltaHeight > maxDeltaHeight)
				m_deltaHeight = -maxDeltaHeight;
			return true;
		}

		double getHeight()
		{
			return m_height;
		}

		bool setDeltaHeight(double deltaHeight)
		{
			if (abs(deltaHeight) > getMaxDeltaHeight())
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

		double getLeftHeight()
		{
			return m_height + m_deltaHeight;
		}

		double getRightHeight()
		{
			return m_height - m_deltaHeight;
		}

		bool setMaxDeltaHeight(double maxDeltaHeight)
		{
			if (maxDeltaHeight > m_height || maxDeltaHeight < 0)
				return false;
			if (m_maxDeltaHeight == NULL)
				m_maxDeltaHeight = new double;
			*m_maxDeltaHeight = maxDeltaHeight;
			return true;
		}

		void unsetMaxDeltaHeight()
		{
			if (m_maxDeltaHeight == NULL)
				return;
			delete m_maxDeltaHeight;
			m_maxDeltaHeight = NULL;
		}

		double getMaxDeltaHeight()
		{
			return m_maxDeltaHeight == NULL ? m_height : *m_maxDeltaHeight;
		}

		virtual ~Disk()
		{
			if (m_maxDeltaHeight != NULL)
				delete m_maxDeltaHeight;
		}

	};

}