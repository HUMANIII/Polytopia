#include "stdafx.h"
#include "SpriteGo.h"
#include "Utils.h"
#include "ResourceMgr.h"

SpriteGo::SpriteGo(const std::string& textureId, const std::string& n)
	: GameObject(n), textureId(textureId)
{
}

SpriteGo::~SpriteGo()
{
}

void SpriteGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	sprite.setPosition(p);
}

void SpriteGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
}

void SpriteGo::AddOrigin(Origins origin)
{
	GameObject::AddOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::AddOrigin(sprite, origin);
	}
}

void SpriteGo::AddOrigin(float x, float y)
{
	GameObject::AddOrigin(x, y);
	sprite.setOrigin(x, y);
}

void SpriteGo::Init()
{

}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture(textureId);
	if (tex != nullptr)
	{
		sprite.setTexture(*tex);
	}
	AddOrigin(origin);
}

void SpriteGo::Update(float dt)
{
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool SpriteGo::SpecificUpdate(float dt)
{
	return false;
}
