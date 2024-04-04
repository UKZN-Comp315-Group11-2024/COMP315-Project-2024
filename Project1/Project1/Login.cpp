/*
 
  Edited by Avesh Ramavather (created),...

  [Add name above after editing]

*/

// Include necessary header files
#include "Login.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "RenderText.h"

#include <iostream>
#include <string>
#include <fstream>

// Rendering text
RenderText* usernameText;
RenderText* userInputText;

// User input
std::string userInput = "";

// Event
SDL_Event event;

// Constructor
Login::Login(){

}

// / Method used to create the login screen
void Login::createLoginScreen(const char* textureSheet, SDL_Renderer* renderer)
{
	// Store renderer for the login screen
	this->renderer = renderer;

	// Load login screen texture
	objTexture = TextureManager::LoadTexture(textureSheet, renderer);

	srcRect.h = 720;
	srcRect.w = 1280;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = 0;
	destRect.y = 0;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;

	// Set login screen as active
	checkActive = true;

	// Create RenderText object for username display
	usernameText = new RenderText(100, 300, 110, renderer, "Username:  ", {0 ,0 ,0});
	userInputText = new RenderText(600, 300, 110, renderer, userInput.c_str(), {0, 0, 0});

	SDL_StartTextInput();
}

// Method used to update th login screen
void Login::update()
{
	// Get the state of the keyboard
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	// Ensures that the user can enter at most 10 characters for their name
	if (userInput.length() < 10) 
	{
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_TEXTINPUT:
				// Checking if a character is being inputted
				if (event.text.text[0] != '\0') {
					userInput += event.text.text;
					userInputText->updateText(this->renderer, userInput);
				}
				break;
			}
		}
	}
	
	// If the user presses backspace, it clears their entire entry
	if (currentKeyStates[SDL_SCANCODE_BACKSPACE] != 0)
	{
		userInput.clear();
		userInputText->updateText(this->renderer, userInput);
	}

	// Press enter to continue to game if the username enetered is of the appropriate length
	if (currentKeyStates[SDL_SCANCODE_RETURN] != 0
		&& userInput.length() >= 3
		&& userInput.length() <= 10)
	{
		// Used to open/create a text file in overwrite mode, use "std::ios::app" in the last parameter to append a text file
		std::ofstream file("textfiles/LoginInfo.txt", std::ios::trunc);

		// Adds username to a user login info textfile found at "textfiles/LoginInfo.txt"
		file << userInput;

		file.close();

		// Sets the login screen to false;
		Login::checkActive = false;
	}

	
}

// Method to render the login screen
void Login::render()
{
	// Render the login screen texture
	SDL_RenderCopy(this->renderer, objTexture, &srcRect, &destRect);

	// Render the login screen text
	usernameText->RenderTextOnScreen(this->renderer);

	userInputText->RenderTextOnScreen(this->renderer);
}

// Method to check if login screen is active
bool Login::isActive()
{
	return checkActive;
}

// Destructor
Login::~Login()
{
	delete usernameText;
	delete userInputText;
}