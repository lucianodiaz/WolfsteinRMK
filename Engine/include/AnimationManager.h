#pragma once
#include <SFML/Graphics.hpp>

class AnimationManager
{
public:
	AnimationManager(sf::Texture* texture, sf::Vector2u imgCount, float switchTime);
	~AnimationManager();

	void update(int row, sf::Time deltaTime);

public:
	void playAnimation();

	sf::IntRect uvRect;


private:
	sf::Vector2u _imageCount;
	sf::Vector2u _currentImage;

	float _totalTime;
	float _switchTime;
	bool _finishAnimation;
};

