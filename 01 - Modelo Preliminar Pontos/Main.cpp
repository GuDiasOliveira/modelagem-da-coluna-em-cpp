#pragma once

#include <iostream>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Slider.hpp>

#include "SpineDrawable.h"

#define SIDE_PANEL_WIDTH 300

using namespace std;
using namespace sf;
using namespace humanSpineSfDraw;
using namespace tgui;


double random(double min, double max)
{
	static random_device rand;
	double num = rand();
	num -= rand.min();
	num /= rand.max() - rand.min();
	num *= max - min;
	num += min;
	return num;
}


void loadGUI(tgui::Gui &gui)
{
	Label::Ptr lblMaxDeltaHeight = make_shared<Label>();
	lblMaxDeltaHeight.get()->setText("Inclinação máxima do disco");
	lblMaxDeltaHeight.get()->setTextColor(tgui::Color(sf::Color::White));
	lblMaxDeltaHeight.get()->setPosition({ 20, 20 });
	lblMaxDeltaHeight.get()->setSize({ SIDE_PANEL_WIDTH - 20, 20 });
	lblMaxDeltaHeight.get()->setHorizontalAlignment(Label::HorizontalAlignment::Center);

	Slider::Ptr sldMaxDeltaHeight = make_shared<Slider>();
	sldMaxDeltaHeight.get()->setMinimum(0);
	sldMaxDeltaHeight.get()->setMaximum(100);
	sldMaxDeltaHeight.get()->setValue(50);
	sldMaxDeltaHeight.get()->setPosition({ 20,
		lblMaxDeltaHeight.get()->getPosition().y + lblMaxDeltaHeight.get()->getSize().y + 10
	});
	sldMaxDeltaHeight.get()->setSize({ SIDE_PANEL_WIDTH - 20, 20 });

	Label::Ptr lblDeltaHeight = make_shared<Label>();
	lblDeltaHeight.get()->setText("Inclicação do disco");
	lblDeltaHeight.get()->setTextColor(tgui::Color(sf::Color::White));
	lblDeltaHeight.get()->setPosition({ 20,
		sldMaxDeltaHeight.get()->getPosition().y + sldMaxDeltaHeight.get()->getSize().y + 30
	});
	lblDeltaHeight.get()->setSize({ SIDE_PANEL_WIDTH - 20, 20 });
	lblDeltaHeight.get()->setHorizontalAlignment(Label::HorizontalAlignment::Center);

	Slider::Ptr sldDeltaHeight = make_shared<Slider>();
	sldDeltaHeight.get()->setMinimum(0);
	sldDeltaHeight.get()->setMaximum(100);
	sldDeltaHeight.get()->setValue(0);
	sldDeltaHeight.get()->setPosition({ 20,
		lblDeltaHeight.get()->getPosition().y + lblDeltaHeight.get()->getSize().y + 10
	});
	sldDeltaHeight.get()->setSize({ SIDE_PANEL_WIDTH - 20, 20 });

	Label::Ptr lblPrevDisk = make_shared<Label>();
	lblPrevDisk.get()->setAutoSize(true);
	lblPrevDisk.get()->setText("<<");
	lblPrevDisk.get()->setTextColor(tgui::Color(sf::Color::White));
	lblPrevDisk.get()->setPosition({20,
		sldDeltaHeight.get()->getPosition().y + sldDeltaHeight.get()->getSize().y + 10
	});
	lblPrevDisk.get()->setSize({25, 20});

	Label::Ptr lblSelectDisk = make_shared<Label>();
	lblSelectDisk.get()->setText("Selecionar disco");
	lblSelectDisk.get()->setTextColor(tgui::Color(sf::Color::White));
	lblSelectDisk.get()->setPosition({
		lblPrevDisk.get()->getPosition().x + lblPrevDisk.get()->getSize().x + 5,
		lblPrevDisk.get()->getPosition().y
	});
	//lblSelectDisk.get()->setSize({ lblSelectDisk.get()->getSize().x, 20 });
	lblSelectDisk.get()->setAutoSize(true);
	gui.add(lblSelectDisk, "lblSelectDisk");

	Label::Ptr lblNextDisk = make_shared<Label>();
	lblNextDisk.get()->setAutoSize(true);
	lblNextDisk.get()->setText(">>");
	lblNextDisk.get()->setTextColor(tgui::Color(sf::Color::White));
	lblNextDisk.get()->setPosition({
		lblSelectDisk.get()->getPosition().x + lblSelectDisk.get()->getSize().x + 5,
		lblPrevDisk.get()->getPosition().y
	});
	lblNextDisk.get()->setSize({ lblNextDisk.get()->getSize().x, 20});

	gui.add(lblMaxDeltaHeight, "lblMaxDeltaHeight");
	gui.add(sldMaxDeltaHeight, "sldMaxDeltaHeight");
	gui.add(lblDeltaHeight, "lblDeltaHeight");
	gui.add(sldDeltaHeight, "sldDeltaHeight");
	gui.add(lblPrevDisk, "lblPrevDisk");
	gui.add(lblNextDisk, "lblNextDisk");
}


int main(int argc, char** argv)
{
	RenderWindow window({ 1000, 670 }, "Visualização em 2D da Coluna Vertebral", Style::Default);
	View view = window.getDefaultView();
	tgui::Gui gui(window);

	try
	{
		loadGUI(gui);
	}
	catch (const tgui::Exception &e)
	{
		cerr << "Erro ao carregar a interface gráfica: " << e.what() << endl;
	}

	Spine spine;
	double angles[SPINE_COUNT_ALL_DISKS + 1];
	angles[0] = PI / 2;
	for (int i = 1; i < SPINE_COUNT_ALL_DISKS + 1; i++)
	{
		double deltaAngleMax = spine.getMaxDeltaAngle(i - 1);
		double deltaAngle = random(-deltaAngleMax, deltaAngleMax);
		angles[i] = angles[i - 1] - deltaAngle;
		while (angles[i] > 2 * PI)
			angles[i] -= 2 * PI;
		while (angles[i] < 0)
			angles[i] += 2 * PI;
	}
	spine.setAngles(angles);
	spine.setHeadInclination(angles[SPINE_COUNT_ALL_DISKS] - PI / 2);

	SpineDrawable spineDrw;
	spineDrw.element = &spine;
	spineDrw.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y - 10));

	auto deltaHeightChangeCallback = [&](int value)
	{	
		int selectedDiskIndex = spineDrw.getSelectedDiskIndex();

		if (selectedDiskIndex < 0)
			return;

		double deltaAngle = (value - 50) / 50.0 * spine.getMaxDeltaAngle(selectedDiskIndex);
		double angle = spine.getAngle(selectedDiskIndex) + deltaAngle;
		Utils::delimitAngle(angle);
		spine.setAngle(selectedDiskIndex + 1, angle);
		for (int i = selectedDiskIndex + 2; i < SPINE_COUNT_ALL_DISKS; i++)
			spine.setAngle(i, spine.getAngle(i) + deltaAngle);
		spine.setHeadInclination(spine.getInclination(SPINE_COUNT_ALL_DISKS - 1));
		cout << "Delta Height GET value = " << value << endl;
	};
	gui.get<Slider>("sldDeltaHeight").get()->connect("ValueChanged", deltaHeightChangeCallback);

	gui.get<Slider>("sldMaxDeltaHeight").get()->connect("ValueChanged", [&](int value)
	{
		int selectedDiskIndex = spineDrw.getSelectedDiskIndex();
		
		if (selectedDiskIndex < 0)
			return;

		Disk& disk = spine.getDisk(selectedDiskIndex);
		double maxDeltaHeight = value / 100.0 * disk.getHeight();
		disk.setMaxDeltaHeight(maxDeltaHeight);
		spine.recalculate();
		deltaHeightChangeCallback(gui.get<Slider>("sldDeltaHeight").get()->getValue());
		cout << "Max Delta Height GET value = " << value << endl;
	});

	int selectedDiskIndex = 1;
	gui.get<Label>("lblPrevDisk").get()->connect("clicked", [&]()
	{
		if (selectedDiskIndex > 1)
			selectedDiskIndex--;
		spineDrw.selectDisk(selectedDiskIndex);
	});
	gui.get<Label>("lblSelectDisk").get()->connect("clicked", [&]()
	{
		if (spineDrw.getSelectedDiskIndex() == -1)
			spineDrw.selectDisk(selectedDiskIndex);
		else
			spineDrw.unselectDisk();
	});
	gui.get<Label>("lblNextDisk").get()->connect("clicked", [&]()
	{
		if (selectedDiskIndex < SPINE_COUNT_ALL_DISKS - 1)
			selectedDiskIndex++;
		spineDrw.selectDisk(selectedDiskIndex);

		Disk& selectedDisk = spine.getDisk(selectedDiskIndex);
		gui.get<Slider>("sldMaxDeltaHeight").get()->setValue(selectedDisk.getMaxDeltaHeight() / selectedDisk.getHeight() * 100.0);
		cout << "Max Delta Height SET value = " << gui.get<Slider>("sldMaxDeltaHeight").get()->getValue() << endl;
		double deltaAngle = spine.getAngle(selectedDiskIndex) - spine.getAngle(selectedDiskIndex - 1);
		gui.get<Slider>("sldDeltaHeight").get()->setValue(deltaAngle / spine.getMaxDeltaAngle(selectedDiskIndex - 1) * 50.0 + 50.0);
		cout << "Delta Height SET value = " << gui.get<Slider>("sldDeltaHeight").get()->getValue() << endl;
	});

	Vector2i prevMousePos = Mouse::getPosition(window);
	Clock clkMouseMove;

	window.setVisible(true);
	while (window.isOpen())
	{
		if (clkMouseMove.getElapsedTime().asSeconds() > 1 / 30.0f)
		{
			Vector2i mousePos = Mouse::getPosition(window);
			Vector2i mouseMove = mousePos - prevMousePos;

			if (Mouse::isButtonPressed(Mouse::Button::Left) && mousePos.x > SIDE_PANEL_WIDTH)
			{
				view.move(-mouseMove.x, -mouseMove.y);
			}

			prevMousePos = mousePos;

			clkMouseMove.restart();
		}

		Event evt;
		//RectangleShape* testRects = nullptr;
		while (window.pollEvent(evt))
		{
			if (evt.type == Event::Closed)
			{
				window.close();
			}
			else if (evt.type == Event::MouseWheelScrolled)
			{
				view.zoom(1.0f - evt.mouseWheelScroll.delta * 0.1f);
			}
			
			gui.handleEvent(evt);
		}

		

		/*if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			Vector2f mousePosition = Vector2f(Mouse::getPosition(window));
			spineDrw.selectDisk(mousePosition);
		}*/

		//// For tests DEBUG
		//Vector2f* testShapePoints = new Vector2f[4]
		//{
		//	{20, 20},
		//	{100, 20},
		//	{100, 100},
		//	{20, 100}
		//};
		//int sldValue = gui.get<Slider>("sldDeltaHeight").get()->getValue();
		//float angle = sldValue / 100.1f * 360;
		//ConvexShape testShape;
		//Vector2f testOrigin = testShapePoints[0];
		//testShape.setPointCount(4);
		//FloatRect testBounds = testShape.getGlobalBounds();
		//for (int i = 0; i < 4; i++)
		//{
		//	Vector2f point = testShapePoints[i];
		//	point = Utils::rotatePoint(point, angle, testOrigin);
		//	testShape.setPoint(i, point);
		//}
		//if (Utils::collision(Vector2f(Mouse::getPosition()), testBounds, angle, {0, 0}))
		//{
		//	testShape.setFillColor(sf::Color::White);
		//}
		//else
		//{
		//	testShape.setFillColor(sf::Color::Yellow);
		//}

		window.clear();
		window.draw(spineDrw);
		gui.draw();
		//if (testRects != nullptr)
		//{
		//	//testRects[0].setPosition(0, 0);
		//	//testRects[0].setSize({ 100, 100 });
		//	for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
		//		window.draw(testRects[i]);
		//}
		//else
		//{
		//	Vector2f mousePosition = Vector2f(Mouse::getPosition(window));
		//	CircleShape c;
		//	c.setFillColor(sf::Color::Blue);
		//	c.setRadius(1);
		//	c.setPosition(mousePosition);
		//	window.draw(c);
		//}
		//window.draw(testShape);

		

		window.setView(view);

		window.display();

		/*if (testRects != nullptr)
			delete[] testRects;*/
	}

	return EXIT_SUCCESS;
}