#include "gameScenes/SceneMainMenu.h"
#include <Configuration.h>

SceneMainMenu::SceneMainMenu(SceneStateMachine& ssm, Window& window) :
	_sceneStateMachine(ssm), _window(window), _switchToState(0), _mainMenu(window.getRenderWindow())
{
}

void SceneMainMenu::onCreate()
{
	
}

void SceneMainMenu::onDestroy()
{
}

void SceneMainMenu::onActivate()
{
	sf::Texture& texture = Configuration::textures.get(Configuration::Textures::MenuImage);
	_menuSprite.setTexture(texture);
	sf::FloatRect spriteSize = _menuSprite.getLocalBounds();
	_menuSprite.setOrigin(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
	_menuSprite.setScale(0.4, 0.4);
	_menuSprite.setPosition(_window.getWindowCentrePos().x, _window.getWindowCentrePos().y);
	initGUI();

	Configuration::musics.get(Configuration::Music::MainMenu).setLoop(true);
	Configuration::musics.get(Configuration::Music::MainMenu).play();
}

void SceneMainMenu::onDeactivate()
{
	Configuration::musics.get(Configuration::Music::MainMenu).stop();
}

void SceneMainMenu::setSwitchToScene(unsigned int id)
{
	_switchToState = id;
}

void SceneMainMenu::processInput()
{
	sf::Event evt;
	while (_window.pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			_window.close();
		else if (evt.type == sf::Event::KeyPressed)
		{
			if (evt.key.code == sf::Keyboard::Escape)
			{
				_window.close();
			}
		}
		else
		{
			switch (_status)
			{
			default:
				_mainMenu.processEvent(evt);
				break;
			}
		}
	}

	switch (_status)
	{
	default:
		_mainMenu.processEvents();
		break;
	}
}

void SceneMainMenu::update(sf::Time deltaTime)
{
}

void SceneMainMenu::draw(Window& window)
{
	window.draw(_menuSprite);
	switch (_status)
	{
	case StatusMainMenu:
		window.draw(_mainMenu);
		break;

	default:
		window.draw(_mainMenu);
		break;
	}
}

void SceneMainMenu::initGUI()
{
	//New game button text
	
	
	VLayout* layout = new VLayout();
	
	layout->setSpace(2);
	TextButton* newGame = new TextButton("New Game");
	newGame->hideShape();
	newGame->setTextColor(sf::Color(176, 176, 176, 255));
	newGame->onClick = [this](const sf::Event&, Button& button) {
		_sceneStateMachine.switchTo(_switchToState);
		_status = Status::StatusGame;
	};
	layout->add(newGame);

	//Load game button text
	TextButton* Loadgame = new TextButton("Load game");
	Loadgame->setTextColor(sf::Color(176, 176, 176, 255));
	Loadgame->hideShape();

	Loadgame->onClick = [this](const sf::Event&, Button& button) {
		
	};
	layout->add(Loadgame);

	//Controls button text
	TextButton* ControlsButton = new TextButton("Controls");
	ControlsButton->setTextColor(sf::Color(176, 176, 176, 255));
	ControlsButton->hideShape();
	ControlsButton->onClick = [this](const sf::Event&, Button& button) {

	};
	layout->add(ControlsButton);

	//Exit button text
	TextButton* exit = new TextButton("Exit");
	exit->setTextColor(sf::Color(176, 176, 176, 255));
	exit->hideShape();
	exit->onClick = [this](const sf::Event&, Button& button) {
		_window.close();
	};
	layout->add(exit);

	_mainMenu.setLayout(layout);

	_mainMenu.bind(Configuration::GuiInputs::Escape, [this](const sf::Event& evt) {
		_window.close();
		});
}
