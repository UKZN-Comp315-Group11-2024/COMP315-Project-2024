/*
  Edited by Avesh Ramavather (created),...

  [Add name above after editing]
*/

// Header file for the Game class
#pragma once

// Include necessary header files
#include "SDL.h"
#include "SDL_image.h"
#include <fstream>
#include <string>
#include <string>
#include "Question.h"

class Game
{
public:
	Game();
	~Game();

	// Initialize the game window
	void initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	// Handle events
	void handleEvents();

	// Update the game state
	void update();

	// Render the game graphics
	void render();

	// Clean up resources before exiting
	void clean();

	vector<Question> readQuestionsFromFile(const string& filename);

	// Check if the game is running
	bool running() 
	{ 
		return isRunning; 
	}

	void setGameState(std::string str);

	std::string getGameState();


	SDL_Window* getWindow();



	// Static event instance for handling events
	static SDL_Event event;

private:

	// Indicating whether the game is running
	bool isRunning;

	// SDL window instance
	SDL_Window* window;

	// SDL renderer instance for rendering graphics
	SDL_Renderer* renderer;

	/*VALUES OF GAMESTATE USED SO FAR:
	login
	leaderboard
	level 1*/
	std::string gameState;

};
