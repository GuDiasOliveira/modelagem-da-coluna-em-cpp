#pragma once

#include "HumanSpineElementDrawable.h"
#include "Spine.h"
#include "VertebraDrawable.h"
#include "DiskDrawable.h"
#include "HeadDrawable.h"
#include "SacroCoccyxDrawable.h"

using namespace pointsModel;
using namespace sf;
using namespace std;


namespace humanSpineSfDraw
{

	class SpineDrawable : public HumanSpineElementDrawable<Spine>
	{

	private:

		int selectedDiskIndex = -1;

		Vector2f& convertVector(Point &point) const
		{
			return Vector2f((float)point.x, (float)point.y);
		}

		virtual void draw(RenderTarget &target, RenderStates states) const
		{
			states.transform *= getTransform();

			states.transform.scale(1, -1);

			HeadDrawable headDrw;
			SacroCoccyxDrawable saccDrw;

			saccDrw.element = new Vector2f(SPINE_WIDTH, 10);
			saccDrw.setPosition(0, 0);
			target.draw(saccDrw, states);
			delete saccDrw.element;
			saccDrw.element = NULL;

			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				VertebraDrawable vertDrw;
				vertDrw.element = &element->getVertebra(i);
				vertDrw.setPosition(convertVector(vertDrw.element->position));
				vertDrw.setRotation(Utils::to_sfmlAngle(vertDrw.element->getAngle()));
				target.draw(vertDrw, states);

				DiskDrawable diskDrw;
				diskDrw.element = &element->getDisk(i);
				diskDrw.selected = i == selectedDiskIndex;
				diskDrw.setPosition(convertVector(diskDrw.element->position));
				diskDrw.setRotation(Utils::to_sfmlAngle(diskDrw.element->getAngle()));
				target.draw(diskDrw, states);
			}

			headDrw.element = &element->getHead();
			headDrw.setPosition(convertVector(headDrw.element->position));
			headDrw.setRotation(Utils::to_sfmlAngle(headDrw.element->getAngle()));
			target.draw(headDrw, states);
		}

	public:

		void selectDisk(unsigned int diskIndex)
		{
			selectedDiskIndex = diskIndex;
		}

		void unselectDisk()
		{
			selectedDiskIndex = -1;
		}

		int getSelectedDiskIndex()
		{
			return selectedDiskIndex;
		}

		virtual ~SpineDrawable()
		{
		}

	};

}