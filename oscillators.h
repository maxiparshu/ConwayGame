#ifndef BLINKER_H
#define BLINKER_H

#include "shape.h"
#include "stillFigure.h"
class Blinker : public Shape
{
    int period;
public:
    Blinker(int i, int j);
};

class Toad : public Shape
{
    int period;
public:
    Toad(int i, int j);
};

class Beacon : public Shape
{
    int period;
public:
    Beacon(int i, int j);
};

class Pulsar : public Shape
{
    int period;
public:
    Pulsar(int i, int j);
};

class Galaxy : public Shape{
    int period;
public:
    Galaxy(int i, int j);
};

#endif // BLINKER_H
