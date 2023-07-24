#pragma once
#include "GameObject.h"
class TextGo : public GameObject
{
public:
	sf::Text text;
	std::string resourceId;


	TextGo(const std::string n = "", const std::string rId = "");
	virtual ~TextGo() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void AddOrigin(Origins origin);
	virtual void AddOrigin(float x, float y);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

