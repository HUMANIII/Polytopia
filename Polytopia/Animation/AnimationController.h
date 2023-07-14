#pragma once
#include "AnimationClip.h"

class AnimationController
{
protected:
	std::unordered_map<std::string, AnimationClip> clips;
	std::queue<std::string> queue;

	float speed = 1.f;
	bool isPlaying = false;

	AnimationClip* currentClip = nullptr;
	int currentFrame = -1;
	int totalFrame = 0;
	float clipDuration = 0.f;
	float accumTime = 0.f;

	sf::Sprite* target = nullptr;

public:
	void AddClip(const AnimationClip& newClip);
	void SetTarget(sf::Sprite* sprite) { target = sprite; }
	sf::Sprite* GetTarget() { return target; }
	bool IsPlaying() { return isPlaying; }
	void SetSpeed(float speed) { this->speed = speed; }
	float GetSpeed() { return speed; }
	const std::string GetCurClip() { return currentClip == nullptr ? "" : currentClip->id; }

	void Update(float dt);

	void Play(const std::string& clipId, bool clearQueue = true);
	void PlayQueue(const std::string& clipId);

	void Stop();

	void SetFrame(const AnimationFrame& frame);
};