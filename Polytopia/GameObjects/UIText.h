#pragma once
#include "GameObject.h"
class UIText
	:public GameObject
{
protected:
	sf::Text mainText;
	sf::Text changingText;
	int* textFactor = nullptr;

	sf::Sprite* img = nullptr;
public:
	UIText(std::string key);
	virtual ~UIText() {};

	void SetTextInfo(std::vector<std::string> infos);
	void SetChangingText(int& param);

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual bool SpecificUpdate(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void SwitchTurn() override;

	void Release();
};

