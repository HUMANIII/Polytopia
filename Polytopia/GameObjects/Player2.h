#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player2 :
    public SpriteGo
{
protected:
	AnimationController animation;

	sf::Vector2f dir = {0.f, 0.f};

	float speed = 200;
public:
	Player2(const std::string& textureId = "", const std::string& n = "");
	virtual ~Player2() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
};

