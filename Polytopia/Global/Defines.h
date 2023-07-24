#pragma once

#define _USE_MATH_DEFINES

enum class Languages
{
	KOR,
	ENG,
	JP,
	Count,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AnimationClip,
};

enum class SceneId
{
	None = -1,
	Title,
	Dev1,
	Count,
};

#include "AnimationClip.h"