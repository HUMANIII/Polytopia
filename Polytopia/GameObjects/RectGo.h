#pragma once
#include "GameObject.h"
class RectGo :
    public GameObject
{
protected:
    sf::RectangleShape rect;

public:
	RectGo(const std::string& n = "");
	virtual ~RectGo() override;

	sf::RectangleShape& GetRect();

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void AddOrigin(Origins origin);
	virtual void AddOrigin(float x, float y);

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

