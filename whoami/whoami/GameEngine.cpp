//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Gelo123321 - 2016. +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "GameEngine.h"
#include "GameState.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GameEngine::GameEngine()
{
	
}

GameEngine::~GameEngine()
{

}

bool GameEngine::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
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

	//// add some sound effects - TODO move to better place
	//TheSoundManager::Instance()->load("assets/DST-Away.ogg", "music1", SOUND_MUSIC);
	//TheSoundManager::Instance()->load("assets/jump.wav", "jump", SOUND_SFX);
	////TheSoundManager::Instance()->load("phaser.wav", "shoot", SOUND_SFX);

	//TheSoundManager::Instance()->playMusic("music1", -1);


	//TheInputHandler::Instance()->initialiseJoysticks();

	//// register the types for the game
	//TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	//TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	//TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
	//TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
	//TheGameObjectFactory::Instance()->registerType("Snail", new SnailCreator());

	//// start the menu state
	//m_pGameStateMachine = new GameStateMachine();
	//m_pGameStateMachine->changeState(new MainMenuState());

	m_bRunning = true; // everything inited successfully, start the main loop

	return true;
}

void GameEngine::changeState(GameState * state)
{
	// Cleanup the current state.
	if (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	// Store and init the new state.
	states.push_back(state);
	states.back()->init(this);
}

void GameEngine::pushState(GameState * state)
{
	// Pause current state.
	if (!states.empty()) {
		states.back()->pause();
	}

	// Store and init the new state.
	states.push_back(state);
	states.back()->init(this);
}

void GameEngine::popState()
{
	// Cleanup the current state.
	if (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	// Resume previous state.
	if (!states.empty()) {
		states.back()->resume();
	}
}

void GameEngine::handleEvents()
{
	// Let the state handle events.
	states.back()->handleEvents(this);
}

void GameEngine::update()
{
	// Let the state update the game.
	states.back()->update(this);
}

void GameEngine::draw()
{
	// Let the state draw the screen.
	states.back()->draw(this);
}

void GameEngine::render()
{
	SDL_RenderClear(m_pRenderer.get());
	SDL_RenderPresent(m_pRenderer.get());
}

void GameEngine::clean()
{
	cout << "cleaning game\n";

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer.get());
	SDL_Quit();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++