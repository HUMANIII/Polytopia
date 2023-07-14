#pragma once
#include "Singleton.h"

enum class Axis
{
	Horizontal,
	Vertical,
	Wheel,
};

struct AxisInfo
{
	Axis axis;
	std::list<int> positivies;
	std::list<int> negatives;

	float sensi = 3.f;
	float value = 0.f;
};


class InputMgr : public Singleton<InputMgr>
{
	friend Singleton<InputMgr>;

protected:
	InputMgr();
	virtual ~InputMgr() override = default;

	std::list<int> downList;
	std::list<int> upList;
	std::list<int> ingList;

	sf::Vector2f mousePos;
	sf::Vector2f prevMousePos;
	float mouseWheelAxis;

	std::map<Axis, AxisInfo> axisInfoMap;	
public:
	void Update(float dt);
	void UpdateEvent(const sf::Event& ev);

	// Keyboard
	bool GetKeyDown(sf::Keyboard::Key key);
	bool GetKey(sf::Keyboard::Key key);
	bool GetKeyUp(sf::Keyboard::Key key);

	// Mouse
	const sf::Vector2f& GetMousePos();
	bool GetMouseButtonDown(sf::Mouse::Button button);
	bool GetMouseButton(sf::Mouse::Button button);
	bool GetMouseButtonUp(sf::Mouse::Button button);

	void SwipeMap(sf::View& world, sf::Mouse::Button button, bool followTheMouse = true);
	void ZoomMap(sf::View& world, bool reverse = false);

	// Axis
	float GetAxis(Axis axis);
	float GetAxisRaw(Axis axis);
};

#define INPUT_MGR (InputMgr::Instance())
