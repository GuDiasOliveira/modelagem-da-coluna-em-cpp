#pragma once

#include <stdexcept>

#include "Point.h"
#include "Utils.h"


namespace pointsModel
{

	class PointsModel
	{

	private:

		const unsigned int m_numberOfPoints;
		double *m_edges, *m_angles, *m_maxAngles, *m_minAngles;
		Point *m_points;

		void calculatePoints()
		{
			m_points[0] = Point(0, 0);
			for (int i = 0; i < m_numberOfPoints - 1; i++)
			{
				m_points[i+1] = m_points[i] + Point(cos(m_angles[i]), sin(m_angles[i])) * m_edges[i];
			}
		}

	public:

		PointsModel() : m_numberOfPoints(0)
		{
		}

		PointsModel(const PointsModel &obj) : m_numberOfPoints(obj.m_numberOfPoints)
		{
			m_edges = new double[m_numberOfPoints - 1];
			m_angles = new double[m_numberOfPoints - 1];
			m_maxAngles = new double[m_numberOfPoints - 1];
			m_minAngles = new double[m_numberOfPoints - 1];
			m_points = new Point[m_numberOfPoints];

			for (int i = 0; i < m_numberOfPoints - 1; i++)
			{
				m_edges[i] = obj.m_edges[i];
				m_angles[i] = obj.m_angles[i];
				m_maxAngles[i] = obj.m_maxAngles[i];
				m_minAngles[i] = obj.m_minAngles[i];
				m_points[i] = obj.m_points[i];
			}
			m_points[m_numberOfPoints - 1] = obj.m_points[m_numberOfPoints - 1];
		}
		
		PointsModel(const unsigned int numberOfPoints, double initialAngle, double initialEdge) : m_numberOfPoints(numberOfPoints)
		{
			if (initialEdge <= 0)
				throw std::invalid_argument("Points model edge must be positive not including 0");
			if (initialAngle < 0 || initialAngle > 2 * PI)
				throw std::invalid_argument("Points model angle must be between 0 and 2*PI");

			m_edges = new double[m_numberOfPoints - 1];
			m_angles = new double[m_numberOfPoints - 1];
			m_maxAngles = new double[m_numberOfPoints - 1];
			m_minAngles = new double[m_numberOfPoints - 1];
			m_points = new Point[m_numberOfPoints];

			for (int i = 0; i < m_numberOfPoints - 1; i++)
			{
				m_edges[i] = initialEdge;
				m_angles[i] = initialAngle;
				m_maxAngles[i] = 2 * PI;
				m_minAngles[i] = 0;
			}

			calculatePoints();
		}

		unsigned int getNumberOfPoints()
		{
			return m_numberOfPoints;
		}

		bool setEdge(unsigned int index, double edge)
		{
			if (index >= m_numberOfPoints - 1)
				return false;
			if (edge <= 0)
				return false;
			m_edges[index] = edge;
			calculatePoints();
			return true;
		}

		double getEdge(unsigned int index)
		{
			return m_edges[index];
		}

		bool setAngle(unsigned int index, double angle)
		{
			if (index >= m_numberOfPoints - 1)
				return false;
			if (angle > m_maxAngles[index] || angle < m_minAngles[index])
				return false;
			m_angles[index] = angle;
			calculatePoints();
			return true;
		}

		double getAngle(unsigned int index)
		{
			return m_angles[index];
		}

		bool setMaxAngle(unsigned int index, double maxAngle)
		{
			if (index >= m_numberOfPoints - 1)
				return false;
			if (maxAngle > 2 * PI || maxAngle < m_minAngles[index])
				return false;
			m_maxAngles[index] = maxAngle;
			if (m_angles[index] > maxAngle)
			{
				m_angles[index] = maxAngle;
				calculatePoints();
			}
			return true;
		}

		double getMaxAngle(unsigned int index)
		{
			return m_maxAngles[index];
		}

		bool setMinAngle(unsigned int index, double minAngle)
		{
			if (index >= m_numberOfPoints - 1)
				return false;
			if (minAngle < 0 || minAngle > m_maxAngles[index])
				return false;
			m_minAngles[index] = minAngle;
			if (m_angles[index] < minAngle)
			{
				m_angles[index] = minAngle;
				calculatePoints();
			}
			return true;
		}

		double getMinAngle(unsigned int index)
		{
			return m_minAngles[index];
		}

		Point getPoint(unsigned int index)
		{
			return m_points[index];
		}

		virtual ~PointsModel()
		{
			delete[] m_edges;
			delete[] m_angles;
			delete[] m_maxAngles;
			delete[] m_minAngles;
			delete[] m_points;
		}

	};

}