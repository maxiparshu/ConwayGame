#pragma once
#include "shape.h"
#include "stillfigure.h"
class Glider : public Shape
{
public:
    Glider(int i, int j);
};

class LightSpaceship : public Shape{
public:
    LightSpaceship(int i, int j);
};
class MiddleSpaceship : public Shape{
public:
    MiddleSpaceship(int i, int j);
};
class LargeSpaceship : public  Shape{
public:
    explicit LargeSpaceship(int i, int j );
};

class LightPufferTrain : public Shape
{
public:
    LightPufferTrain(int i, int j);
};
