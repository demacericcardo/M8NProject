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

	const Uint8* currentKeyStates = nullptr;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	bool interact = false;

	int mouseXPos = 0;
	int mouseYPos = 0;
	Uint32 mouseState = 0;

	bool mouseLeftClick = false;
	bool mouseRightClick = false;

	std::optional<Vector2D> mousePosClicked;
	void* entityMouseOverlaid = nullptr;
};