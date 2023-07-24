#include "stdafx.h"
#include "RectGo.h"
#include "Utils.h"

RectGo::RectGo(const std::string& n)
    : GameObject(n)
{
}

RectGo::~RectGo()
{
}

sf::RectangleShape& RectGo::GetRect()
{
    return rect;
}

void RectGo::SetPosition(const sf::Vector2f& p)
{
    position = p;
    rect.setPosition(position);
}

void RectGo::SetPosition(float x, float y)
{
    SetPosition({ x,y });
}

void RectGo::AddOrigin(Origins origin)
{
    Utils::AddOrigin(rect, origin);

    if (this->origin != Origins::CUSTOM)
    {
        Utils::AddOrigin(rect, origin);
    }
}

void RectGo::AddOrigin(float x, float y)
{
    GameObject::AddOrigin(x, y);
    rect.setOrigin(x, y);
}
void RectGo::Draw(sf::RenderWindow& window)
{
    window.draw(rect);
}

void RectGo::Init()
{
}

void RectGo::Reset()
{
}

void RectGo::Update(float dt)
{
}
