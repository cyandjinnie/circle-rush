#pragma once

class GameObject {
public:
    virtual void act(float dt) = 0;
    virtual ~GameObject() = default;
};