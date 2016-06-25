#pragma once

#include "HumanSpineElementDrawable.h"
#include "Disk.h"


namespace humanSpineSfDraw
{

	class DiskDrawable : public HumanSpineElementDrawable<Disk>
	{

	private:

		virtual void draw(RenderTarget &target, RenderStates states) const
		{
			Vector2f point = position;
			ConvexShape leftTriangle;
			leftTriangle.setPointCount(3);
			leftTriangle.setPoint(0, point);
			point += Vector2f(-element.getWidth / 2, element.getHeight / 2);
			leftTriangle.setPoint(1, point);
			point.y -= element.getLeftHeight;
			leftTriangle.setPoint(2, point);
			leftTriangle.setRotation(element.getAngle);

			point = position;
			ConvexShape rightTriangle;
			rightTriangle.setPointCount(3);
			rightTriangle.setPoint(0, point);
			point += Vector2f(element.getWidth / 2, element.getHeight / 2);
			rightTriangle.setPoint(1, point);
			point.y -= element.getRightHeight;
			rightTriangle.setPoint(2, point);
			rightTriangle.setRotation(element.getAngle);

			leftTriangle.setFillColor(Color::Red);
			rightTriangle.setFillColor(Color::Red);
			leftTriangle.setOutlineThickness(3.5f);
			rightTriangle.setOutlineThickness(3.5f);
			leftTriangle.setOutlineColor(Color::Magenta);
			rightTriangle.setOutlineColor(Color::Magenta);

			target.draw(leftTriangle, states);
			target.draw(rightTriangle, states);
		}

	};

}