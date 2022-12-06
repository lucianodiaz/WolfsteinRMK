#pragma once
#include <SFML/Graphics.hpp>
#include <Animation.h>
#include <map>


class AnimationManager
{
public:
	using FuncType = std::function<void()>;

	AnimationManager(sf::Texture* texture, sf::Vector2u imgCount, float switchTime);
	~AnimationManager();

	void update(int row, sf::Time deltaTime);

public:
	void addOnStart(int nameAnimation, const FuncType& callback);
	void addOnComplete(int nameAnimation, const FuncType& callback);
	void addAnimation(Animation& animation);
	void playAnimation(int animationName);

	sf::IntRect uvRect;


private:

	//We recive a name (index),cant frames and start frame for each animation

	Animation* _currentAnimation;
	std::vector<Animation> _animations;
	std::vector<std::pair<int, FuncType>> _onStart;
	std::vector<std::pair<int, FuncType>> _onComplete;
	sf::Vector2u _imageCount;
	sf::Vector2u _currentImage;

	float _totalTime;
	float _switchTime;
	bool _finishAnimation;
};

