#pragma once

#include "GameObject.h"
#include "Drawable.h"
#include "Canvas.h"

#include <vector>
#include <unordered_map>

Canvas* canvas = nullptr;

std::vector<GameObject*> game_objects;
std::vector<Drawable*> drawables;