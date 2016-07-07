#pragma once

#include <iostream>
#include <random>
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

	gui.add(lblMaxDeltaHeight, "lblMaxDeltaHeight");
	gui.add(sldMaxDeltaHeight, "sldMaxDeltaHeight");
	gui.add(lblDeltaHeight, "lblDeltaHeight");
	gui.add(sldDeltaHeight, "sldDeltaHeight");
}


int main(int argc, char** argv)
{
	RenderWindow window({ 1280, 720 }, "Visualização em 2D da Coluna Vertebral", Style::Default);
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
		//double deltaAngle = deltaAngleMax;
		angles[i] = angles[i - 1] - deltaAngle;
		//angles[i] = 2.5 * SPINE_WIDTH * sin(2*PI/10 * i);
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
		double angles[SPINE_COUNT_ALL_DISKS + 1];
		angles[0] = PI / 2;
		for (int i = 1; i < SPINE_COUNT_ALL_DISKS + 1; i++)
		{
			double deltaAngle = (value - 50) / 50.0 * spine.getMaxDeltaAngle(i - 1);
			angles[i] = angles[i - 1] + deltaAngle;
			while (angles[i] > 2 * PI)
				angles[i] -= 2 * PI;
			while (angles[i] < 0)
				angles[i] += 2 * PI;
		}
		spine.setAngles(angles);
		spine.setHeadInclination(angles[SPINE_COUNT_ALL_DISKS] - PI / 2);
	};
	gui.get<Slider>("sldDeltaHeight").get()->connect("ValueChanged", deltaHeightChangeCallback);

	gui.get<Slider>("sldMaxDeltaHeight").get()->connect("ValueChanged", [&](int value)
	{
		for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
		{
			Disk& disk = spine.getDisk(i);
			double maxDeltaHeight = value / 100.0 * disk.getHeight();
			disk.setMaxDeltaHeight(maxDeltaHeight);
		}
		spine.recalculate();
		deltaHeightChangeCallback(gui.get<Slider>("sldDeltaHeight").get()->getValue());
	});

	window.setVisible(true);
	while (window.isOpen())
	{
		Event evt;
		RectangleShape* testRects = nullptr;
		while (window.pollEvent(evt))
		{
			if (evt.type == Event::Closed)
			{
				window.close();
			}
			
			gui.handleEvent(evt);
		}

		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			Vector2f mousePosition = Vector2f(Mouse::getPosition(window));
			testRects = spineDrw.selectDisk(mousePosition, window);
		}

		window.clear();
		window.draw(spineDrw);
		gui.draw();
		if (testRects != nullptr)
		{
			//testRects[0].setPosition(0, 0);
			//testRects[0].setSize({ 100, 100 });
			//for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
				//window.draw(testRects[i]);
		}
		window.display();

		if (testRects != nullptr)
			delete[] testRects;
	}

	return EXIT_SUCCESS;
}