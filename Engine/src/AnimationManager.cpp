#include "AnimationManager.h"

AnimationManager::AnimationManager(sf::Texture* texture, sf::Vector2u imgCount, float switchTime)
{
	_currentAnimation = nullptr;
	_imageCount = imgCount;
	_switchTime = switchTime;
	_totalTime = 0.0f;
	_currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(_imageCount.x);
	uvRect.height = texture->getSize().y / float(_imageCount.y);
	_finishAnimation = false;
	
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::update(int row, sf::Time deltaTime)
{
	if (_currentAnimation != nullptr) 
	{
		_currentImage.y = _currentAnimation->row;//row
		_totalTime += deltaTime.asSeconds();

		if (!_finishAnimation)
		{
			if (_totalTime >= _currentAnimation->duration)
			{
				if (_currentImage.x == _currentAnimation->startIndex)
				{
					for (auto& pair : _onStart)
					{
						if (pair.first == _currentAnimation->nameAnimation)
						{
							pair.second();
						}
					}
				}
				
				_totalTime -= _currentAnimation->duration;
				_currentImage.x++;
				if (_currentImage.x >= _imageCount.x)
				{
					if (!_currentAnimation->loop)
					{
						_finishAnimation = true;
					}

					if (_currentAnimation->repeat)
					{
						_currentImage.x = 0;
					}
					for (auto& pair : _onComplete)
					{
						if (pair.first == _currentAnimation->nameAnimation)
						{
							pair.second();
						}
					}

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
		
}

void AnimationManager::addOnStart(int nameAnimation, const FuncType& callback)
{
	_onStart.emplace_back(nameAnimation, callback);
}

void AnimationManager::addOnComplete(int nameAnimation, const FuncType& callback)
{
	_onComplete.emplace_back(nameAnimation, callback);
}

void AnimationManager::addAnimation(Animation& animation)
{
	_animations.emplace_back(animation);
}

void AnimationManager::playAnimation(int animationName)
{
	/*if (_currentAnimation != &_animations.at(animationName))
	{*/
		_currentAnimation = &_animations.at(animationName);
		//_totalTime = 0;
		_finishAnimation = false;
	//}
	
}
