#pragma once
#include <functional>



struct Animation
{
	//Name Index this is a enum but this recive a int (enum it's just mantein clean animation name)
	int nameAnimation{};
	//Where is in the image height
	int row{};
	//how many frames does it have
	int cantFrame{};
	//in wich frames does it start
	int startIndex{};
	//duration of animation
	float duration{};
	//is a loop?
	bool loop{};
	//when finish animation we start in index 0 or we stay in last animation
	bool repeat{ true };
};