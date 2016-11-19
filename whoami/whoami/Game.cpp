//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Gelo123321 - 2016. +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Game.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Game* Game::s_pInstance = 0;

bool Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	// store the game width and height
	m_gameWidth = width;
	m_gameHeight = height;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0) // window init success
		{
			cout << "window creation success\n";
			m_pRenderer = shared_ptr<SDL_Renderer>(SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
				[](SDL_Renderer* render) {SDL_DestroyRenderer(render); });

			if (m_pRenderer != 0) // renderer init success
			{
				cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer.get(), 0, 0, 0, 255);
			}
			else
			{
				cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		cout << "SDL init fail\n";
		return false; // SDL init fail
	}


	if (!TheTextureManager::Instance()->load("resources\\img\\animate-alpha.png", "animate", m_pRenderer.get()))
	{
		return false;
	}

	m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
	m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

	TheInputHandler::Instance()->initialiseJoysticks();

	m_bRunning = true; // everything inited successfully, start the main loop

	return true;
}


void Game::handleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			}
			break;
		}
	}
}

void Game::update()
{
	TheInputHandler::Instance()->update();

	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->update();
	}
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer.get());

	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}

	SDL_RenderPresent(m_pRenderer.get());
}

void Game::clean()
{
	cout << "cleaning game\n";

	TheInputHandler::Instance()->clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer.get());
	SDL_Quit();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++