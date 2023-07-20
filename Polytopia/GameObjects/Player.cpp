#include "stdafx.h"
#include "Player.h"
#include "City.h"


//void Player::SummonUnit()
//{
//
//}

void Player::Init()
{
}

void Player::Reset()
{
}

void Player::Update(float dt)
{
	timer += dt;
	if (timer > 2.f)
	{
		std::cout << "playerType : " << (int)type << "  Current Star : " << stars << std::endl;
		timer = 0.f;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
}

bool Player::SpecificUpdate(float dt)
{
	return false;
}

void Player::SwitchTurn()
{	
}
