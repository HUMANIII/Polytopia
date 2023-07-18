#include "stdafx.h"
#include "MapTile.h"
#include "Unit.h"
#include "SceneTitle.h"
#include "rapidcsv.h"
#include "ResourceMgr.h"
#include "City.h"


MapTile::MapTile()
{
	SetPosition({ 0,0 });
	sortLayer = 3;
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
		if (isPointInsideShape(clickBound))
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
			if (scene->GetSelectTile() == this || scene->GetSelectTile() == this->cityBelonged || scene->GetSelectTile() == this->onTileUnit)
				clickFuctionOpt = []() { return nullptr; };
			//std::cout << "test0" << std::endl;
			break;
		case 1:
			if (onTileUnit != nullptr)
				clickFuctionOpt = [this]() { return onTileUnit; };
			else
			{
				if (cityBelonged != nullptr)
					clickFuctionOpt = [this]() { return cityBelonged; };
				else
					clickFuctionOpt = [this]() { return this; };
			}
			//std::cout << "test1" << std::endl;
			break;
		case 2:
			if (clickFuctionOpt() == onTileUnit)
				clickFuctionOpt = [this]() { return cityBelonged; };
			else
				clickFuctionOpt = [this]() { return this; };
			//std::cout << "test2" << std::endl;
			break;
		}
	}
}

bool MapTile::SpecificUpdate(float dt)
{
	return false;
}

void MapTile::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(envSprite);
	window.draw(resSprite);
	//window.draw(clickBound);
}


void MapTile::SetTileInfo(Base base, Environment env, Resource res)
{
	sortLayer = 1;

	this->base = base;
	this->env = env;
	this->res = res;
}

void MapTile::SetDraw()
{
	rapidcsv::Document doc("Scripts/MapTileInfoList copy.csv");
	
	if (isHidden)
	{
		for (int i = 0; i < doc.GetRowCount(); i++)
		{
			if (doc.GetCell<std::string>(0, i) == "base"
				&& doc.GetCell<int>(1, i) == 99)
			{
				std::string path = doc.GetCell<std::string>(2, i);

				sprite.setTexture(*RESOURCE_MGR.GetTexture(path));								
				sf::Vector2f spriteSize = Utils::GetSprite(sprite);
				sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - 168);
				detectSize.x = spriteSize.x;
				detectSize.y = detectSize.x * 154 / 256;
				return;
			}
		}
	}

	int baseindex = (int)base;
	int envindex = (int)env;
	int resindex = (int)res;


	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (doc.GetCell<std::string>(0, i) == "base" 
			&& doc.GetCell<int>(1, i) == baseindex)
		{
			std::string path = doc.GetCell<std::string>(2, i);
			
			sprite.setScale(1, 1);
			sprite.setTexture(*RESOURCE_MGR.GetTexture(path));
			sf::Vector2f spriteSize = Utils::GetSprite(sprite);
			sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - 168);
			detectSize.x = spriteSize.x;
	        detectSize.y = detectSize.x * 154 / 256;
		}

		if (envindex != -1 && doc.GetCell<std::string>(0, i) == "env" && doc.GetCell<int>(1, i) == envindex)
		{
			std::string path = doc.GetCell<std::string>(2, i);
			envSprite.setTexture(*RESOURCE_MGR.GetTexture(path));

			sf::Vector2f spriteSize = Utils::GetSprite(envSprite);
			envSprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - spriteSize.x * 0.25f);
		}
		if (resindex != -1 && doc.GetCell<std::string>(0, i) == "res" && doc.GetCell<int>(1, i) == resindex)
		{
			std::string path = doc.GetCell<std::string>(2, i);
			resSprite.setTexture(*RESOURCE_MGR.GetTexture(path));

			sf::Vector2f spriteSize = Utils::GetSprite(resSprite);
			resSprite.setOrigin(spriteSize * 0.5f);
		}
	}	
}
/*
void MapTile::SetTileInfo(Types type)
{
	this->type = type;
	int index = (int)type;
	rapidcsv::Document doc("Scripts/MapTileInfoList.csv");	
	textureId = doc.GetColumn<std::string>(1)[index];

	std::vector<std::string> infos = Utils::GetInfos<int>(doc, index);
	textureId = infos[0];

	Reset();

	spriteSize = Utils::GetSprite(sprite);

	float scale = 256 / spriteSize.x;
	sprite.setScale(sprite.getScale() * scale);
	spriteSize *= scale;
	//sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y- 650);	
 //77  154 245 245 - 77 168
	sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - 650);	
	detectSize.x = spriteSize.x;
	detectSize.y = detectSize.x * 3 / 5;

	SetDetectArea(sprite.getOrigin());
}*/

void MapTile::SetPosition(sf::Vector2f pos)
{
	position = pos;
	sprite.setPosition(position);
	envSprite.setPosition(position);
	resSprite.setPosition(position);

	sortOrder = (int)position.y;

	float x = detectSize.x * 0.5f;
	float y = detectSize.y * 0.5f;
	clickBound.setPointCount(4);
	clickBound.setPoint(0, sf::Vector2f(-x, 0) + position);
	clickBound.setPoint(1, sf::Vector2f(0, y) + position);
	clickBound.setPoint(2, sf::Vector2f(x, 0) + position);
	clickBound.setPoint(3, sf::Vector2f(0, -y) + position);
}


void MapTile::SetUnit(Unit* unit, MapTile* tile)
{
	tile->onTileUnit = unit;
	unit->SetPosition(position);
}

void MapTile::SetCity(City* city, MapTile* tile)
{
	tile->cityBelonged = city;
	city->SetPosition(tile->position);
}

void MapTile::Move(MapTile* tile)
{
	SetUnit(onTileUnit, tile);
	this->onTileUnit = nullptr;
}

bool MapTile::isPointInsideShape(const sf::Shape& shape, sf::Vector2f point)
{	
	point = scene->ScreenToWorldPos(point);
	std::size_t pointCount = shape.getPointCount();

	if (pointCount < 3) 
	{
		return false;
	}

	for (std::size_t i = 0; i < pointCount; ++i) {
		sf::Vector2f currentPoint = shape.getPoint(i);
		sf::Vector2f nextPoint = shape.getPoint((i + 1) % pointCount);

		sf::Vector2f edge = currentPoint - nextPoint;
		sf::Vector2f toPoint = point - currentPoint;

		if ((edge.x * toPoint.y) - (edge.y * toPoint.x) < 0)
			return false;
	}
	return true;
} 
