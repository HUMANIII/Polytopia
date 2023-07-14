#include "stdafx.h"
#include "MapTile.h"
#include "Unit.h"
#include "Scene.h"
#include "rapidcsv.h"


MapTile::MapTile()
	:detectPoints(4)
{
	SetPosition({ 0,0 });	
}

MapTile::~MapTile()
{
}

void MapTile::Update(float dt)
{
	SpriteGo::Update(dt);
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		//std::cout << "testClick" << std::endl;
		if (isPointInsideShape())
		{
			//std::cout << "testDetect Op" << std::endl;			
			clickCount += clickCount == 2 ? -1 : 1;
		}
		else
		{
			clickCount = 0;
		}

		switch (clickCount)
		{
		case 0:
			//clickNone = ;
			std::cout << "test0" << std::endl;
			break;
		case 1:
			//clickOnce = ;
			std::cout << "test1" << std::endl;
			break;
		case 2:
			//clickTwice = ;
			std::cout << "test2" << std::endl;
			break;
		}
	}
}

void MapTile::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(clickBound);
}

void MapTile::SetTileInfo(Types type)
{
	this->type = type;
	int index = (int)type;

	rapidcsv::Document doc("Scripts/MapTileInfoList.csv");
	textureId = doc.GetColumn<std::string>(1)[index];
	Reset();

	spriteSize = Utils::GetSprite(sprite);

	float scale = 1000 / spriteSize.x;
	sprite.setScale(sprite.getScale() * scale);
	spriteSize *= scale;
	//sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y- 650);	
	sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - 650);	
	detectSize.x = spriteSize.x;
	detectSize.y = detectSize.x * 3 / 5;

	SetDetectArea(sprite.getOrigin());
}

void MapTile::SetPosition(sf::Vector2f pos)
{
	position = pos;
	sprite.setPosition(position);
	clickBound.setPosition(position);
}

void MapTile::SetDetectArea(sf::Vector2f center)
{
	position = center;

	float x = detectSize.x * 0.5f;
	float y = detectSize.y * 0.5f;
	clickBound.setPointCount(4);
	clickBound.setPoint(0, sf::Vector2f(0, y));
	clickBound.setPoint(1, sf::Vector2f(x, 2 * y));
	clickBound.setPoint(2, sf::Vector2f(2 * x, y));
	clickBound.setPoint(3, sf::Vector2f(x, 0));
	clickBound.setOrigin(x,y);
	clickBound.setFillColor({ 0,0,0,0 });
}


bool MapTile::isPointInsideShape(sf::Vector2f point)
{	
	point = scene->ScreenToWorldPos(point);
	std::size_t pointCount = clickBound.getPointCount();

	if (pointCount < 3) 
	{
		return false;
	}

	for (std::size_t i = 0; i < pointCount; ++i) {
		sf::Vector2f currentPoint = clickBound.getPoint(i);
		sf::Vector2f nextPoint = clickBound.getPoint((i + 1) % pointCount);

		sf::Vector2f edge = currentPoint - nextPoint;
		sf::Vector2f toPoint = point - currentPoint;

		if ((edge.x * toPoint.y) - (edge.y * toPoint.x) < 0)
			return false;
	}
	return true;
} 
