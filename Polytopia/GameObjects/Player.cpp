#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"

void Player::Init()
{	
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "Animations/Idle.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "Animations/Jump.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "Animations/Move.csv");

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Jump.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Move.csv"));


	animation.SetTarget(&sprite);

	SetOrigin(Origins::BC);
}

void Player::Reset()
{
	animation.Play("Idle");
	SetOrigin(origin);
	SetPosition({ 0, 0 });
	SetFlipX(false);
}

void Player::Update(float dt)
{
	animation.Update(dt);
	float h = INPUT_MGR.GetAxis(Axis::Horizontal);

	// �ø�
	if (h != 0.f)
	{
		bool flip = h < 0.f;
		if (GetFlipX() != flip)
		{
			SetFlipX(flip);
		}
	}

	// ����
	if (isGround && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		velocity.y += JumpForce;
		animation.Play("Jump");
		isGround = false;
	}

	// �̵�
	velocity.x = h * speed;
	velocity.y += gravity * dt;
	position += velocity * dt;

	// �ٴ� �浹 ó��
	if (position.y > 0.f)
	{
		isGround = true;
		position.y = 0.f;
		velocity.y = 0.f;
	}

	SetPosition(position);

	// ���ϸ��̼�
	if (animation.GetCurClip() == "Idle")
	{
		if (isGround && h != 0.f)
		{
			animation.Play("Move");
		}
	}
	else if (animation.GetCurClip() == "Move")
	{
		if (isGround && h == 0.f)
		{
			animation.Play("Idle");
		}
	}
	else if (animation.GetCurClip() == "Jump")
	{
		if (isGround)
		{
			animation.Play((h == 0.f) ? "Idle" : "Move");
		}
	}
}

bool Player::GetFlipX() const
{
	return filpX;
}

void Player::SetFlipX(bool filp)
{
	filpX = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !filpX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}