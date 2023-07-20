#include "stdafx.h"
#include "MapTile.h"
#include "Unit.h"
#include "SceneTitle.h"
#include "rapidcsv.h"
#include "ResourceMgr.h"
#include "City.h"

SceneTitle* MapTile::scene = nullptr;

MapTile::MapTile()
	:SpriteGo("","tile")
{
	SetPosition({ 0,0 });
	sortLayer = 3;
	origin = Origins::CUSTOM;
}

MapTile::~MapTile()
{
}

void MapTile::Update(float dt)
{
	SpriteGo::Update(dt);
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{				
		rapidcsv::Document doc("Scripts/MapTileInfoList.csv");
		

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
			if (scene->GetSelectTileOpt() == this || scene->GetSelectTileOpt() == this->cityBelonged || scene->GetSelectTileOpt() == this->onTileUnit)
			{
				clickFuctionOpt = [this]() {return nullptr; };
				sf::Texture empty;
				UI.setTexture(empty,true);
			}
			//std::cout << "test0" << std::endl;
			break;
		case 1:
			if (onTileUnit != nullptr)
			{
				clickFuctionOpt = [this]() { return onTileUnit; };
				if (onTileUnit->GetPlayerType() != Player::PlayerType::Player)
					return;
				int move = onTileUnit->GetMoveRange();
				int atk = onTileUnit->GetAtkRange();
				std::list<GameObject*> tiles;
				scene->FindGos(tiles,"tile");
				for (auto tile : tiles)
				{
					MapTile* mt = dynamic_cast<MapTile*>(tile);
					int param = 0;

					for (int i = 0; i < doc.GetRowCount(); i++)
					{
						if (mt->CheckRange(this, move))
						{
							param = 0;
						}
						if (mt->CheckRange(this, atk) &&
							mt->GetOnTileUnit() != nullptr)
						{
							if (mt->GetOnTileUnit()->GetPlayerType() != Player::PlayerType::Enemy)
								continue;
							param = 1;
						}

						if (param != 0 && param != 1)
						{
							sf::Texture empty;
							mt->GetUI()->setTexture(empty, true);
						}
						else if (doc.GetCell<std::string>(0, i) == "ui"
							&& doc.GetCell<int>(1, i) == param)
						{
							std::string path = doc.GetCell<std::string>(2, i);

							mt->GetUI()->setTexture(*RESOURCE_MGR.GetTexture(path), true);
							sf::Vector2f spriteSize = Utils::GetSprite(*mt->GetUI());
							mt->GetUI()->setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
							mt->GetUI()->setPosition(mt->GetPosition());
						}
					}
					/*
					if (mt->CheckRange(this, move))
					{						
						for (int i = 0; i < doc.GetRowCount(); i++)
						{
							if (doc.GetCell<std::string>(0, i) == "ui"
								&& doc.GetCell<int>(1, i) == 0)
							{
								std::string path = doc.GetCell<std::string>(2, i);

								mt->GetUI()->setTexture(*RESOURCE_MGR.GetTexture(path), true);
								sf::Vector2f spriteSize = Utils::GetSprite(*mt->GetUI());
								mt->GetUI()->setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
								mt->GetUI()->setPosition(mt->GetPosition());
							}
						}
					}
					if (mt->CheckRange(this, atk) && 
						mt->GetOnTileUnit() != nullptr)
					{						
						for (int i = 0; i < doc.GetRowCount(); i++)
						{
							if (mt->GetOnTileUnit()->GetPlayerType() != Player::PlayerType::Enemy)
								continue;
							if (doc.GetCell<std::string>(0, i) == "ui"
								&& doc.GetCell<int>(1, i) == 1)
							{
								std::string path = doc.GetCell<std::string>(2, i);

								mt->GetUI()->setTexture(*RESOURCE_MGR.GetTexture(path),true);
								sf::Vector2f spriteSize = Utils::GetSprite(*mt->GetUI());
								mt->GetUI()->setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
								mt->GetUI()->setPosition(mt->GetPosition());
							}
						}
					}
					*/
				}								
			}
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
	window.draw(UI);
	window.draw(clickBound);
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
	rapidcsv::Document doc("Scripts/MapTileInfoList.csv");
	
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

		if (envindex == -1)
		{
			sf::Texture empty;
			envSprite.setTexture(empty,true);
		}
		else if (envindex != -1 && doc.GetCell<std::string>(0, i) == "env" && doc.GetCell<int>(1, i) == envindex)
		{
			std::string path = doc.GetCell<std::string>(2, i);
			envSprite.setTexture(*RESOURCE_MGR.GetTexture(path));

			sf::Vector2f spriteSize = Utils::GetSprite(envSprite);
			envSprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - spriteSize.x * 0.25f);
		}

		if (resindex == -1)
		{
			sf::Texture empty;
			resSprite.setTexture(empty, true);
		}
		else if (resindex != -1 && doc.GetCell<std::string>(0, i) == "res" && doc.GetCell<int>(1, i) == resindex)
		{
			std::string path = doc.GetCell<std::string>(2, i);
			resSprite.setTexture(*RESOURCE_MGR.GetTexture(path));

			sf::Vector2f spriteSize = Utils::GetSprite(resSprite);
			resSprite.setOrigin(spriteSize * 0.5f);
		}
	}	
}

void MapTile::SetPosition(sf::Vector2f pos)
{
	tilePos = pos;

	position = { tilePos.x * detectSize.x * 0.5f , tilePos.y * detectSize.y * 0.5f };
	sprite.setPosition(position);
	envSprite.setPosition(position);
	resSprite.setPosition(position);
	UI.setPosition(position);

	sortOrder = (int)position.y;

	float x = detectSize.x * 0.5f;
	float y = detectSize.y * 0.5f;
	clickBound.setPointCount(4);
	clickBound.setPoint(0, sf::Vector2f(-x, 0) + position);
	clickBound.setPoint(1, sf::Vector2f(0, y) + position);
	clickBound.setPoint(2, sf::Vector2f(x, 0) + position);
	clickBound.setPoint(3, sf::Vector2f(0, -y) + position);
	clickBound.setFillColor({ 0,0,0,0 });
}


void MapTile::SetUnit(Unit* unit, MapTile* tile)
{
	if (unit == nullptr)
	{
		std::cout << "�ڿ��� �����Ͽ� ������ ���� �� �� �����ϴ�." << std::endl;
		return;
	}
	tile->onTileUnit = unit;
	scene->AddGo(unit);
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

void MapTile::SetPosition(float x, float y)
{
	SetPosition({ x,y });
}

bool MapTile::CheckRange(MapTile* otherTile, int range)
{
	sf::Vector2f findPos = otherTile->tilePos - tilePos;
	if (abs(findPos.x) <= range * 2)
		if (abs(findPos.x) == abs(findPos.x) && abs(findPos.x) == range * 2)
			return false;
		if (abs(findPos.y) <= range * 2)
			return true;			
	return false;
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
