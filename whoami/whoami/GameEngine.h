//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Gelo123321 - 2016. +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <SDL.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;
class GameState;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class GameEngine
{
public:
	static GameEngine* Instance() 
	{
		if (s_pInstance == 0) {
			s_pInstance = new GameEngine();
			return s_pInstance;
		}

		return s_pInstance;
	}

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();

	void handleEvents();
	void update();
	void draw();

	void render();
	void clean();

	bool running() { return m_bRunning; }
	void quit() { m_bRunning = false; }

	shared_ptr<SDL_Renderer> getRenderer() const { return m_pRenderer; }
	SDL_Window* getWindow() const { return m_pWindow; }

	int getGameWidth() const { return m_gameWidth; }
	int getGameHeight() const { return m_gameHeight; }

private:
	static GameEngine* s_pInstance;
	SDL_Window* m_pWindow;
	shared_ptr<SDL_Renderer> m_pRenderer;

	int m_gameWidth;
	int m_gameHeight;

	// The stack of states.
	vector<GameState*> states;
	bool m_bRunning;
	bool m_fullscreen;

	GameEngine();
	~GameEngine();

	GameEngine(const GameEngine&) = delete;
	GameEngine& operator=(const GameEngine&) = delete;
};

typedef GameEngine Game;

#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++