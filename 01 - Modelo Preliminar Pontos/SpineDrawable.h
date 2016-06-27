#pragma once

#include "HumanSpineElementDrawable.h"
#include "Spine.h"
#include "VertebraDrawable.h"
#include "DiskDrawable.h"
#include "HeadDrawable.h"
#include "SacroCoccyxDrawable.h"

using namespace pointsModel;


namespace humanSpineSfDraw
{

	class SpineDrawable : public HumanSpineElementDrawable<Spine>
	{

	private:

		Vector2f& convertVector(Point &point) const
		{
			return Vector2f(point.x, point.y);
		}

		virtual void draw(RenderTarget &target, RenderStates states) const
		{
			//Vector2f position = getPosition();
			//Vector2f point = Vector2f(0, 0);
			states.transform *= getTransform();

			VertebraDrawable vertDrw;
			DiskDrawable diskDrw;
			HeadDrawable headDrw;
			SacroCoccyxDrawable saccDrw;

			saccDrw.element = new Vector2f(SPINE_WIDTH, 10);
			saccDrw.setPosition(0, 0);
			target.draw(saccDrw, states);
			delete saccDrw.element;
			saccDrw.element = NULL;

			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				vertDrw.element = &element->getVertebra(i);
				vertDrw.setPosition(convertVector(vertDrw.element->position));
				vertDrw.setRotation(to_sfmlAngle(vertDrw.element->getAngle()));
				target.draw(vertDrw, states);

				diskDrw.element = &element->getDisk(i);
				diskDrw.setPosition(convertVector(diskDrw.element->position));
				diskDrw.setRotation(to_sfmlAngle(diskDrw.element->getAngle()));
				target.draw(diskDrw, states);
			}

			headDrw.element = &element->getHead();
			headDrw.setPosition(convertVector(headDrw.element->position));
			headDrw.setRotation(to_sfmlAngle(headDrw.element->getAngle()));
			target.draw(headDrw, states);
		}

	};

}