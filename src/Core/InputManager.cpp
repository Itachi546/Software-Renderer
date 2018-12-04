#include "InputManager.h"
#include <iostream>

std::map<int64_t, bool> InputManager::sKeys;


void InputManager::KeyDown(int64_t key)
{
	sKeys[key] = true;
}

void InputManager::KeyUp(int64_t key)
{
	sKeys[key] = false;
}

bool InputManager::IsKeyPressed(int key)
{
	auto it = sKeys.find(key);
	if (it != sKeys.end())
		return sKeys[key];
	else
		return false;
}

bool InputManager::IsKeyReleased(int key)
{
	auto it = sKeys.find(key);
	if (it != sKeys.end())
		return sKeys[key];
	else
		return false;
}
