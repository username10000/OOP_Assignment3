#ifndef GAME_H
#define GAME_H

// Dependencies
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <Functions.h>
#include <memory>
#include <cmath>
#include <Formula.h>
#include <AstroObject.h>
#include <Sun.h>
#include <Planet.h>
#include <Moon.h>
#include <SolarSystem.h>
#include <Ship.h>
#include <VelocityVector.h>
#include <DistanceToObject.h>
#include <Thrust.h>
#include <Fuel.h>
#include <AstroMap.h>
#include <Human.h>
#include <Message.h>
#include <InfoPanel.h>
#include <SpeedLine.h>
#include <Shop.h>

// Game
class Game {
	private:
		sf::RenderWindow window;
		sf::VideoMode screen;
		sf::ContextSettings settings;
		sf::Font font;
		sf::RectangleShape background;
		sf::RenderTexture bRenderTexture;
		sf::Texture bTexture;
		int keys[512] = { 0 };
		int stop;
		int noPlanets;
		int noMoons;
		float fps;
		std::vector<std::unique_ptr<AstroObject>> astro;
		std::vector<std::unique_ptr<Ship>> ships;
		std::vector<std::unique_ptr<SpeedLine>> speedLines;
		std::unordered_map<std::string, bool> menu;
		int stars[200][3];
		//std::vector<std::unique_ptr<sf::CircleShape>> stars;
		std::unique_ptr<VelocityVector> velocityVector;
		std::unique_ptr<DistanceToObject> distanceObject;
		std::unique_ptr<Thrust> thrust;
		std::unique_ptr<Fuel> fuel;
		std::unique_ptr<AstroMap> astroMap;
		std::unique_ptr<Human> human;
		std::unique_ptr<Message> message;
		std::unique_ptr<InfoPanel> infoPanel;
		std::unique_ptr<Shop> shop;
		SolarSystem solarSystem;
		sf::Vector2<double> view;
		float ppm;
		int frames;
		sf::Clock clock;
		sf::Clock frameTime;
		sf::Clock stateTime;
		sf::Clock lastSpeedLine;
		sf::Text frameRate;
		sf::Text distance;
		sf::Text idText;
		sf::Text moneyText;
		float dt;
		float accumulator;
		int targetAstro;
		int noSpeedLines;
		int money;
		bool onPlanet;
		bool jump;
		bool gameOver;
		bool panel;
		sf::Texture humanTexture;
		sf::Texture commonTexture;
		sf::Texture shipTexture;
		std::vector<std::unique_ptr<Human>> locals;
		int closestPlanet;
		//AstroMap astroMap(0);
	public:
		Game();
		~Game();
		void events();
		int getStop();
		//double dist(double x1, double y1, double x2, double y2);
		//float semiMajorAxis(int i);
		//float eccentricityVector(int i);
		//float apoapsis(int i);
		void keyPressed();
		void collisions();
		void nearObjects();
		void fastForwardObject(int i, int loops);
		double getRelativeVelocity();
		double getRelativeVelocity(int index);
		//int randomInt(int start, int stop);
		//float randomFloat(float start, float stop);
		//double map(double v, double lmin, double lmax, double rmin, double rmax);
		void disableMenus();
		void update();
		void render();
};


#endif