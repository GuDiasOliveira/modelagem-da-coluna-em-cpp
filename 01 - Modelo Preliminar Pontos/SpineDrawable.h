#pragma once

#include "HumanSpineElementDrawable.h"
#include "Spine.h"
#include "VertebraDrawable.h"
#include "DiskDrawable.h"
#include "HeadDrawable.h"
#include "SacroCoccyxDrawable.h"
#include "Collision.h"

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

		RectangleShape* selectDisk(Vector2f mouseClickPosition, RenderWindow &w)
		{
			RectangleShape* testRects = new RectangleShape[SPINE_COUNT_ALL_DISKS];
			for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
			{
				Disk &disk = element->getDisk(i);
				FloatRect diskBounds;
				Vector2f diskOrigin((float)disk.getWidth() / 2, (float)disk.getHeight() / 2);
				diskBounds.top = (float) (diskOrigin.y - convertVector(disk.position).y + getPosition().y - disk.getHeight() / 2 * 3);
				diskBounds.height = (float) disk.getHeight() * 2;
				diskBounds.left = (float) (-diskOrigin.x + convertVector(disk.position).x + getPosition().x + disk.getWidth() / 2);
				diskBounds.width = disk.getWidth();

				// For DEBUG
				RectangleShape testArea;
				//float width = diskBounds.width, height = diskBounds.height;
				testArea.setSize({ (float) diskBounds.width, (float) diskBounds.height });
				//testArea.setSize({60, 8});
				testArea.setPosition(diskBounds.left, diskBounds.top);
				//testArea.setPosition(0, 0);
				testArea.setOrigin(diskOrigin);
				testArea.setRotation(360 - Utils::to_sfmlAngle(disk.getAngle()));
				testArea.setFillColor(sf::Color::Green);
				testRects[i] = testArea;

				if (Utils::collision(mouseClickPosition, diskBounds, 360 - Utils::to_sfmlAngle(disk.getAngle()), diskOrigin))
				{
					selectedDiskIndex = i;
					cout << "Disk selected " << selectedDiskIndex << endl;
					return nullptr;
				}
			}
			cout << "No disk selected" << endl;
			selectedDiskIndex = -1;
			return testRects;
		}

		void selectDisk(float mouseX, float mouseY, RenderWindow &w)
		{
			selectDisk({ mouseX, mouseY }, w);
		}

		virtual ~SpineDrawable()
		{
		}

	};

}