#include "GameScenes/SceneSplashScreen.h"
#include "Configuration.h"

SceneSplashScreen::SceneSplashScreen(SceneStateMachine& ssm, Window& window) :
	_sceneStateMachine(ssm),_window(window),_switchToState(0),_currentSeconds(0),
	_showForSeconds(15.0f)
{
}

void SceneSplashScreen::onCreate()
{
	sf::Texture& texture = Configuration::textures.get(Configuration::Textures::TittleScreenImage);
	_splashSprite.setTexture(texture);
	sf::FloatRect spriteSize = _splashSprite.getLocalBounds();
	_splashSprite.setOrigin(spriteSize.width *0.5f, spriteSize.height * 0.5f);
	_splashSprite.setScale(0.6, 0.6);
	_splashSprite.setPosition(_window.getWindowCentrePos().x, _window.getWindowCentrePos().y);
	
	Configuration::musics.get(Configuration::Music::TittleScreen).setLoop(true);
	Configuration::musics.get(Configuration::Music::TittleScreen).play();

}

void SceneSplashScreen::onDestroy()
{
}

void SceneSplashScreen::processInput()
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
				_skip = true;
			}
		}
		/*else if (evt.type == sf::Event::MouseButtonPressed)
		{
			if (evt.key.code == sf::Mouse::Left)
			{
				_skip = true;
			}
		}*/
	}
}

void SceneSplashScreen::onActivate()
{
	_currentSeconds = 0.f;
}

void SceneSplashScreen::onDeactivate()
{
	Configuration::musics.get(Configuration::Music::TittleScreen).stop();
}

void SceneSplashScreen::setSwitchToScene(unsigned int id)
{
	_switchToState= id ;
}

void SceneSplashScreen::update(sf::Time deltaTime)
{
	_currentSeconds += deltaTime.asSeconds();

	if (_currentSeconds >= _showForSeconds || _skip)
	{
		_sceneStateMachine.switchTo(_switchToState);
	}
}

void SceneSplashScreen::draw(Window& window)
{
	window.draw(_splashSprite);
}
