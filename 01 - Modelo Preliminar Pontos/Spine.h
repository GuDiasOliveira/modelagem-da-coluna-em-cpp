#pragma once

#include "Disk.h"
#include "Vertebra.h"
#include "Head.h"
#include "PointsModel.h"

#define SPINE_COUNT_VERTEBRA_CERVICAL 7
#define SPINE_COUNT_VERTEBRA_THORACIC 12
#define SPINE_COUNT_VERTEBRA_LUMBAR 5
#define SPINE_COUNT_VERTEBRA_SACRUM 5
#define SPINE_COUNT_VERTEBRA_COCCYX 4

#define SPINE_COUNT_ALL_VERTEBRAS_NON_FUSED  SPINE_COUNT_VERTEBRA_CERVICAL + SPINE_COUNT_VERTEBRA_THORACIC + SPINE_COUNT_VERTEBRA_LUMBAR
#define SPINE_COUNT_ALL_VERTEBRAS_FUSED  SPINE_COUNT_VERTEBRA_SACRUM + SPINE_COUNT_VERTEBRA_COCCYX
#define SPINE_COUNT_ALL_VERTEBRAS  SPINE_COUNT_ALL_VERTEBRAS_NON_FUSED + SPINE_COUNT_ALL_VERTEBRAS_FUSED
#define SPINE_COUNT_ALL_DISKS SPINE_COUNT_ALL_VERTEBRAS_NON_FUSED + 1

#define SPINE_LAST_VERTEBRA_INDEX_CERVICAL  SPINE_COUNT_VERTEBRA_CERVICAL - 1
#define SPINE_LAST_VERTEBRA_INDEX_THORACIC  SPINE_LAST_VERTEBRA_INDEX_CERVICAL + SPINE_COUNT_VERTEBRA_THORACIC
#define SPINE_LAST_VERTEBRA_INDEX_LUMBAR  SPINE_LAST_VERTEBRA_INDEX_THORACIC + SPINE_COUNT_VERTEBRA_LUMBAR
#define SPINE_LAST_VERTEBRA_INDEX_SACRUM  SPINE_LAST_VERTEBRA_INDEX_LUMBAR + SPINE_COUNT_VERTEBRA_SACRUM
#define SPINE_LAST_VERTEBRA_INDEX_COCCYX  SPINE_LAST_VERTEBRA_INDEX_SACRUM + SPINE_COUNT_VERTEBRA_COCCYX

#define SPINE_WIDTH 60

using namespace pointsModel;


namespace humanSpine
{

	class Spine
	{

	private:
		Disk m_disks[SPINE_COUNT_ALL_DISKS];
		Vertebra m_vertebras[SPINE_COUNT_ALL_DISKS];
		Head m_head;
		PointsModel m_pointsModel;

		void calculateDeltaHeightsAndEdges()
		{
			m_pointsModel.setAngle(0, PI / 2);
			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				double theta_iplus1 = i < SPINE_COUNT_ALL_DISKS - 1 ? m_pointsModel.getAngle(i + 1) : (m_head.getAngle() + PI / 2);
				m_disks[i].setDeltaHeight(-SPINE_WIDTH * tan(theta_iplus1 - m_pointsModel.getAngle(i)) / 2);
				m_pointsModel.setEdge(i, m_disks[i].getHeight() + m_vertebras[i].getHeight());
			}
		}

		void calculatePositions()
		{
			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				double theta_i = m_pointsModel.getAngle(i);
				m_vertebras[i].position = m_pointsModel.getPoint(i) + Point(cos(theta_i), sin(theta_i)) * (m_vertebras[i].getHeight() / 2);
				m_vertebras[i].setAngle(theta_i - PI / 2);
				m_disks[i].position = m_pointsModel.getPoint(i) + Point(cos(theta_i), sin(theta_i)) * (m_vertebras[i].getHeight() + m_disks[i].getHeight() / 2);
				m_disks[i].setAngle(theta_i - PI / 2);
			}
			double theta_H = m_head.getAngle();
			m_head.position = m_pointsModel.getPoint(SPINE_COUNT_ALL_DISKS) + Point(-sin(theta_H), cos(theta_H)) * m_head.getRadius();
		}

		void calculate()
		{
			calculateDeltaHeightsAndEdges();
			calculatePositions();
		}

		bool checkSetAngle(unsigned int index, double angle)
		{
			return index == 0 || abs(angle - m_pointsModel.getAngle(index - 1)) <= getMaxDeltaAngle(index - 1);
		}

		bool limitAngle(unsigned int indexToSetAngle, double &angle)
		{
			if (!checkSetAngle(indexToSetAngle, angle))
			{
				double deltaAngle = getMaxDeltaAngle(indexToSetAngle - 1);
				angle = m_pointsModel.getAngle(indexToSetAngle - 1) + deltaAngle;
				return true;
			}
			return false;
		}

	public:

		Spine() : m_pointsModel(PointsModel(SPINE_COUNT_ALL_DISKS + 1, PI / 2, 1))
		{
			m_head.setRadius(SPINE_WIDTH * 0.7); // initial head radius for tests
			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				m_disks[i].setWidth(SPINE_WIDTH);
				m_disks[i].setHeight(4); // inital height for tests
				m_disks[i].setMaxDeltaHeight(3); // initial max delta height for tests
				m_vertebras[i].setWidth(SPINE_WIDTH);
				m_vertebras[i].setHeight(20); // inital height for tests
			}
			calculate();
		}

		void recalculate()
		{
			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				double angle = m_pointsModel.getAngle(i);
				if (limitAngle(i, angle))
					m_pointsModel.setAngle(i, angle);
			}
			calculate();
		}

		double getMaxDeltaAngle(unsigned int initialAngleIndex)
		{
			return atan(2 * m_disks[initialAngleIndex].getMaxDeltaHeight() / SPINE_WIDTH);
		}

		bool setAngle(unsigned int index, double angle)
		{
			if (index >= SPINE_COUNT_ALL_DISKS)
				return false;
			limitAngle(index, angle);
			if (m_pointsModel.setAngle(index, angle))
			{
				calculate();
				return true;
			}
			return false;
		}

		unsigned int setAngles(double *angles)
		{
			unsigned int set = 0;
			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				limitAngle(i, angles[i]);
				if (m_pointsModel.setAngle(i, angles[i]))
					set++;
			}
			calculate();
			return set;
		}

		unsigned int setInclinations(double *angles)
		{
			double _angles[SPINE_COUNT_ALL_DISKS];
			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
				_angles[i] = angles[i] + PI / 2;
			return setAngles(_angles);
		}

		bool setInclination(unsigned int diskIndex, double angle)
		{
			if (diskIndex >= SPINE_COUNT_ALL_DISKS)
				return false;
			return setAngle(diskIndex, angle + PI / 2);
		}

		bool setHeadInclination(double angle)
		{
			if (angle < 0 || angle > 2 * PI)
				return false;
			m_head.setAngle(angle);
			calculate();
			return true;
		}

		Head& getHead()
		{
			return m_head;
		}

		Disk& getDisk(unsigned int index)
		{
			return m_disks[index];
		}

		Vertebra& getVertebra(unsigned int index)
		{
			return m_vertebras[index];
		}

		virtual ~Spine()
		{
			delete[] m_disks;
			delete[] m_vertebras;
		}

	};

}

