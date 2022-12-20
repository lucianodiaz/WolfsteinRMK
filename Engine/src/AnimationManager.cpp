#include "AnimationManager.h"
#include <iostream>

AnimationManager::AnimationManager(sf::Texture* texture, sf::Vector2u imgCount)
{
	_currentAnimation = nullptr;
	_imageCount = imgCount;
	_totalTime = 0.0f;
	//_currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(_imageCount.x);
	uvRect.height = texture->getSize().y / float(_imageCount.y);
	_finishAnimation = false;
	
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::update(sf::Time deltaTime)
{
	if (_currentAnimation != nullptr) 
	{
		_currentImage.y = _currentAnimation->row;//row
		_totalTime += deltaTime.asSeconds();
		//_currentImage.x = _currentAnimation->startIndex;
		/*_imageCount.x = _currentAnimation->cantFrame;*/

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

				if (_currentImage.x+1 >= _currentAnimation->cantFrame)
				{
					if (!_currentAnimation->loop)
					{
						_finishAnimation = true;
					}

					if (_currentAnimation->repeat)
					{
						_currentImage.x = _currentAnimation->startIndex;
					}
					else
					{
						_currentImage.x = _currentAnimation->cantFrame-1;
						_finishAnimation = true;
						_totalTime = 0;
					}
					for (auto& pair : _onComplete)
					{
						if (pair.first == _currentAnimation->nameAnimation)
						{
							pair.second();
						}
					}

				}
				else
				{
					_currentImage.x++;
				}
			}
			uvRect.left = _currentImage.x * uvRect.width;
			uvRect.top = _currentImage.y * uvRect.height;
			//_totalTime = 0;
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
