#pragma once

#include <memory>

#include "Vector2D.hpp"

class Input
{
private:
	Input() {}
public:
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	static Input& getInstance()
	{
		static Input instance;
		return instance;
	}

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	bool interact = false;
	
	bool mouseLeftClick = false;


	std::unique_ptr<Vector2D> mousePosClicked;
};