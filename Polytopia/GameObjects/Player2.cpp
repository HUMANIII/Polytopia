#include "Player2.h"
#include "InputMgr.h"
#include "ResourceMgr.h"

Player2::Player2(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
}

void Player2::Init()
{
	/*
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "Animations/Ruby/IdleU.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "Animations/Ruby/MoveU.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "Animations/Ruby/IdleD.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "Animations/Ruby/MoveD.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "Animations/Ruby/IdleH.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "Animations/Ruby/MoveH.csv");
	*/
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Ruby/IdleU.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Ruby/MoveU.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Ruby/IdleD.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Ruby/MoveD.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Ruby/IdleH.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Ruby/MoveH.csv"));

	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);
}

void Player2::Reset()
{
	//SpriteGo::Reset();
	animation.Play("IdleD");
	SetOrigin(origin);
	SetPosition(0, 0);
}

void Player2::Update(float dt)
{
	float horizontal = INPUT_MGR.GetAxis(Axis::Horizontal);
	float vertical = INPUT_MGR.GetAxis(Axis::Vertical);
	SetOrigin(origin);

	//move
	dir = { horizontal,vertical };
	SetPosition(position + dir * dt * speed);
	

	//animation and flip
	if (horizontal != 0 || vertical != 0)
	{
		if (abs(horizontal) > abs(vertical))
		{
			if (animation.GetCurClip() != "MoveH")
				animation.Play("MoveH");
			if (horizontal > 0.f)
			{
				Utils::FlipX(sprite, true);
			}
			else
			{
				Utils::FlipX(sprite, false);
			}
		}
		else
		{
				Utils::FlipX(sprite, false);			
			if (vertical > 0.f)
			{
				if(animation.GetCurClip() != "MoveD")
					animation.Play("MoveD");
			}
			else
			{
				if (animation.GetCurClip() != "MoveU")
					animation.Play("MoveU");
			}
		}
	}
	else
	{
		if(animation.GetCurClip() == "MoveU")
			animation.Play("IdleU");
		if(animation.GetCurClip() == "MoveD")
			animation.Play("IdleD");
		if(animation.GetCurClip() == "MoveH")
			animation.Play("IdleH");
	}

	
	
	//SpriteGo::Update(dt);
	animation.Update(dt);
}
