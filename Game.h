#pragma once
#include<SFML/Graphics.hpp>
#include "TrackVisual.h"
#include "TrackPhysic.h"
#include "Simulation.h"


class Game {
private:
	sf::RenderWindow window;
	TrackVisual trackVisual;
	TrackPhysic trackPhysic;
	Simulation simulation;

public:
	Game();
	void run();
};