#include "Game.h"

Game::Game() 
	: window(sf::VideoMode(sf::Vector2u(1920,1080)), "Neuroevolution in Game Agents", sf::Style::Close),
	  trackVisual("track_texture.png"),
	  trackPhysic("track_mask.png"),
	  simulation("car.png",sf::Vector2f(1650,150))
{
}

void Game::run() {

	window.setFramerateLimit(60);
	simulation.startNewGeneration(10);

	while (window.isOpen()) {

		//Event handling
		while (auto event = window.pollEvent()) {

			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}



		int simulationSpeed = 3;
		for (int i = 0; i < simulationSpeed; ++i) {
			simulation.updateAll(trackPhysic);

			if (simulation.isGenerationDead()) {
				simulation.nextGeneration();
			}
		}

		//Draw
		window.clear();
		trackVisual.draw(window);
		simulation.drawAll(window);
		window.display();
	}
}
