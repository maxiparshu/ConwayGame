#pragma once
#include "shape.h"

class Block : public Shape{
public:
    Block(int i,int j);
};
class BeeHive : public Shape{
public:
    BeeHive(int i, int j);
};
class Loaf : public Shape{
public:
    Loaf(int i, int j);
};
class Boat : public Shape{
public:
    Boat(int i, int j);
};
class Tub : public Shape{
public:
    Tub(int i, int j);
};
class Eater : public Shape{
public:
    Eater(int i, int j);
};
