#include "AnimationManager.h"

AnimationManager::AnimationManager(sf::Texture* texture, sf::Vector2u imgCount, float switchTime)
{
	_imageCount = imgCount;
	_switchTime = switchTime;
	_totalTime = 0.0f;
	_currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(_imageCount.x);
	uvRect.height = texture->getSize().y / float(_imageCount.y);

	_finishAnimation = true;
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::update(int row, sf::Time deltaTime)
{
	_currentImage.y = row;
	_totalTime += deltaTime.asSeconds();

	if (!_finishAnimation)
	{
		if (_totalTime >= _switchTime)
		{
			_totalTime -= _switchTime;
			_currentImage.x++;

			if (_currentImage.x >= _imageCount.x)
			{
				_finishAnimation = true;
				_currentImage.x = 0;
			}
		}
		uvRect.left = _currentImage.x * uvRect.width;
		uvRect.top = _currentImage.y * uvRect.height;
	}
	else
	{
		_totalTime = 0;
	}
	
}

void AnimationManager::playAnimation()
{
	_finishAnimation = false;
}
