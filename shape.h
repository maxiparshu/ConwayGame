#pragma once
#include <qmath.h>
enum Figure{
    BLOCK,
    BEEHIVE,
    LOAF,
    BOAT,
    TUB,
    BLINKER,
    TOAD,
    BEACON,
    PULSAR,
    GLIDER,
    LIGHTSHIP,
    MIDDLESHIP,
    HEAVYSHIP,
    GOSPER,
    SIMKIN,
    EATER,
    LIGHTPUFFERTRAIN,
    GALAXY
};
struct Coordinate{


    int I; // координата по Y
    int J; // координата по X
    Coordinate() // задает дефольнтые значения
    {
        I = 0;
        J = 0;
    }
    Coordinate(int i, int j)
    {
        I = i;
        J = j;
    }
    Coordinate& operator =(const Coordinate&);
    bool operator ==(const Coordinate&) const;
    bool operator !=(const Coordinate& ) const;


};
enum Direction{
    RIGHT = 0,
    DOWN,
    LEFT,
    UP
};
class Shape
{
protected:
    Coordinate* figureCoordinate; // координаты фигуры
    int amount; // количество точек
    int sideMaxRectI; //  область фигуры по Y
    int sideMaxRectJ;// область фигуры по X
    int startI; // начальная точка по Y
    int startJ;// начальная точка по X
    int X[4] = {1,0,-1,0}; // направления по Х
    int Y[4] = {0,1,0,-1}; // направления по У
    Coordinate* drawLine(int , int , int , Direction);// создает новую линию
    void findMax(); // задает sideMaxRectI sideMaxRectJ;
    static Coordinate* reflect(int , int , Coordinate* &, int);// отражает координаты
public:

    explicit Shape(const int&, int , int );
    Coordinate* getCoords();

    int getSize() const;
    void setCoords(Coordinate*&);

    void addLine(int& ,int , int , int , Direction); // добавляет к фигуре линию
    void turnOver90Degree();// поворачивает вокруг 90 градусов
};
