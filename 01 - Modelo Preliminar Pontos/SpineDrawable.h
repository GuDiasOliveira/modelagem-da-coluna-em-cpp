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
			Vector2f point = position;

			VertebraDrawable vertDrw;
			DiskDrawable diskDrw;
			HeadDrawable headDrw;
			SacroCoccyxDrawable saccDrw;

			saccDrw.element = new Vector2f(SPINE_WIDTH, 10);
			saccDrw.position = point;
			target.draw(saccDrw, states);
			delete saccDrw.element;
			saccDrw.element = NULL;

			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				vertDrw.element = &element->getVertebra(i);
				vertDrw.position = position + convertVector(vertDrw.element->position);
				target.draw(vertDrw, states);

				diskDrw.element = &element->getDisk(i);
				diskDrw.position = position + convertVector(diskDrw.element->position);
				target.draw(diskDrw, states);
			}

			headDrw.element = &element->getHead();
			headDrw.position = position + convertVector(headDrw.element->position);
			target.draw(headDrw, states);
		}

	};

}