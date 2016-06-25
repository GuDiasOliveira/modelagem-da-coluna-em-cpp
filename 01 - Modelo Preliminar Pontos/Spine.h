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

#define SPINE_WIDTH 30

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
				m_disks[i].setDeltaHeight(SPINE_WIDTH * tan(m_pointsModel.getAngle(i+1) - m_pointsModel.getAngle(i)) / 2);
				m_pointsModel.setEdge(i, m_disks[i].getHeight() + m_vertebras[i].getHeight());
			}
			m_pointsModel.setEdge(SPINE_COUNT_ALL_DISKS, m_head.getRadius());
		}

		void calculatePositions()
		{
			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				double theta_i = m_pointsModel.getAngle(i);
				m_vertebras[i].position = m_pointsModel.getPoint(i) + Point(theta_i, theta_i) * m_vertebras[i].getHeight / 2;
				m_vertebras[i].setAngle(theta_i - PI / 2);
				m_disks[i].position = m_pointsModel.getPoint(i) + Point(theta_i, theta_i) * (m_vertebras[i].getHeight() + m_disks[i].getHeight() / 2);
				m_disks[i].setAngle(theta_i - PI / 2);
			}
			m_head.position = m_pointsModel.getPoint(SPINE_COUNT_ALL_DISKS);
			m_head.setAngle(m_pointsModel.getAngle(SPINE_COUNT_ALL_DISKS));
		}

		void calculate()
		{
			calculateDeltaHeightsAndEdges();
			calculatePositions();
		}

	public:

		Spine() : m_pointsModel(PointsModel(SPINE_COUNT_ALL_DISKS + 1, PI / 2, 1))
		{
			m_head.setRadius(3.7);
			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				m_disks[i].setWidth(SPINE_WIDTH);
				m_disks[i].setHeight(8); // inital height for tests
				m_vertebras[i].setWidth(SPINE_WIDTH);
				m_vertebras[i].setHeight(16); // inital height for tests
			}
		}

		bool setAngle(unsigned int index, double angle)
		{
			if (index >= m_pointsModel.getNumberOfPoints())
				return false;
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
				if (m_pointsModel.setAngle(i + 1, angles[i]))
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
			if (diskIndex < 1 || diskIndex >= SPINE_COUNT_ALL_DISKS)
				return false;
			return setAngle(diskIndex, angle + PI / 2);
		}

		bool setHeadInclination(double angle)
		{
			if (m_pointsModel.setAngle(SPINE_COUNT_ALL_DISKS, angle))
			{
				calculate();
				return true;
			}
			return false;
		}

		virtual ~Spine()
		{
			delete[] m_disks;
			delete[] m_vertebras;
		}

	};

}

