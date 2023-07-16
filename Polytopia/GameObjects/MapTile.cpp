#include "stdafx.h"
#include "MapTile.h"
#include "Unit.h"
#include "Scene.h"
#include "rapidcsv.h"
#include "ResourceMgr.h"


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
		/*sf::Vector2f pos = scene->ScreenToWorldPos(INPUT_MGR.GetMousePos());
		std::cout << pos.x << " , " << pos.y << std::endl;*/
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
	window.draw(envSprite);
	window.draw(resSprite);

}


void MapTile::SetTileInfo(Base base, Environment env, Resource res)
{
	this->base = base;
	this->env = env;
	this->res = res;
}

void MapTile::SetDraw()
{
	rapidcsv::Document doc("Scripts/MapTileInfoList copy.csv");
	int baseindex = (int)base;
	int envindex = (int)env;
	int resindex = (int)res;

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (doc.GetCell<std::string>(0, i) == "base" 
			&& doc.GetCell<int>(1, i) == baseindex)
		{
			std::string path = doc.GetCell<std::string>(2, i);
			RESOURCE_MGR.Load(ResourceTypes::Texture, path);
			sprite.setTexture(*RESOURCE_MGR.GetTexture(path));

			spriteSize = Utils::GetSprite(sprite);
			float scale = 256 / spriteSize.x;
			sprite.setScale(sprite.getScale() * scale);
			spriteSize *= scale;
			//sprite.setOrigin(spriteSize.x, spriteSize.y - 168);
			sprite.setOrigin(spriteSize.x, spriteSize.y - 168);
			detectSize.x = spriteSize.x;
	        detectSize.y = detectSize.x * 154 / 256;
			SetDetectArea(sprite.getOrigin());
		}
		if (envindex != -1 && doc.GetCell<std::string>(0, i) == "env" && doc.GetCell<int>(1, i) == envindex)
		{
			std::string path = doc.GetCell<std::string>(2, i);
			RESOURCE_MGR.Load(ResourceTypes::Texture, path);
			envSprite.setTexture(*RESOURCE_MGR.GetTexture(path));

			spriteSize = Utils::GetSprite(envSprite);
			float scale = 256 / spriteSize.x;
			envSprite.setScale(sprite.getScale() * scale);
			spriteSize *= scale;
			//envSprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - 77);
			envSprite.setOrigin(0,spriteSize.y - 128);
		}
		if (resindex != -1 && doc.GetCell<std::string>(0, i) == "res" && doc.GetCell<int>(1, i) == resindex)
		{
			std::string path = doc.GetCell<std::string>(2, i);
			RESOURCE_MGR.Load(ResourceTypes::Texture, path);
			resSprite.setTexture(*RESOURCE_MGR.GetTexture(path));

			spriteSize = Utils::GetSprite(resSprite);
			float scale = 128 / spriteSize.x;
			resSprite.setScale(sprite.getScale() * scale);
			spriteSize *= scale;
			//resSprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
			resSprite.setOrigin((spriteSize.x - Utils::GetSprite(sprite).x) * 0.5f, (spriteSize.y - 128)* 0.5f);
		}
	}
}

//void MapTile::SetTileInfo(Types type)
//{
//	this->type = type;
//	int index = (int)type;
//	rapidcsv::Document doc("Scripts/MapTileInfoList.csv");	
//	textureId = doc.GetColumn<std::string>(1)[index];
//	/*std::vector<std::string> infos = Utils::GetInfos<int>(doc, index);
//	textureId = infos[0];*/
//	Reset();
//
//	spriteSize = Utils::GetSprite(sprite);
//
//	float scale = 256 / spriteSize.x;
//	sprite.setScale(sprite.getScale() * scale);
//	spriteSize *= scale;
//	//sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y- 650);	
// 77  154 245 245 - 77 168
//	sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - 650);	
//	detectSize.x = spriteSize.x;
//	detectSize.y = detectSize.x * 3 / 5;
//
//	SetDetectArea(sprite.getOrigin());
//}

void MapTile::SetPosition(sf::Vector2f pos)
{
	position = pos;
	sprite.setPosition(position);
	clickBound.setPosition(position);
	envSprite.setPosition(position);
	resSprite.setPosition(position);
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
