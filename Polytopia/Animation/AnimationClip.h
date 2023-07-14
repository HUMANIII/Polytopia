#pragma once
#include "stdafx.h"
enum class AnimationLoopType
{
	Single,
	Loop,
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;
	std::function<void()> action;
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopType loopType;
	int fps;

	bool loadFromFile(const std::string& path);
};