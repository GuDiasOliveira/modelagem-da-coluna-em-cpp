#pragma once

#include "HumanSpineElementDrawable.h"


namespace humanSpineSfDraw
{

	class SacroCoccyxDrawable : public HumanSpineElementDrawable<Vector2f>
	{

	private:

		virtual void draw(RenderTarget &target, RenderStates states) const
		{
			ConvexShape shape;
			shape.setPointCount(3);
			Vector2f point = point;
			point.y += element.y;
			shape.setPoint(0, point);
			point.y -= element.y;
			point.x -= element.x / 2;
			shape.setPoint(1, point);
			point.x += element.x;
			shape.setPoint(2, point);
			
			target.draw(shape, states);
		}

	};

}