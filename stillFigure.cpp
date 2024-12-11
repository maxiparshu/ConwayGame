#include "stillfigure.h"


Block::Block(int i, int j) : Shape(4,i,j)
{
    Coordinate coordinate[4];
    coordinate[0] = Coordinate(i, j);
    coordinate[1] = Coordinate(i + 1, j);
    coordinate[2] = Coordinate(i, j + 1);
    coordinate[3] = Coordinate(i + 1, j + 1);

    for (int k = 0; k < 4; k++) {
        this->figureCoordinate[k] = coordinate[k];
    }
}

Boat::Boat(int i, int j) : Shape(5,i,j)
{
    int index = 0;
    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i+1,j);
    this->figureCoordinate[index++] = Coordinate(i,j+1);
    this->figureCoordinate[index++] = Coordinate(i+1,j+2);
    this->figureCoordinate[index] = Coordinate(i+2,j+1);

}

BeeHive::BeeHive(int i, int j) : Shape(6,i-1,j)
{
    int index = 0;
    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i-1,j+1);
    this->figureCoordinate[index++] = Coordinate(i+1,j+1);
    this->figureCoordinate[index++] = Coordinate(i-1,j+2);
    this->figureCoordinate[index++] = Coordinate(i+1,j+2);
    this->figureCoordinate[index] = Coordinate(i,j+3);
}

Loaf::Loaf(int i, int j) : Shape(7,i -1,j)
{
    int index = 0;
    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i-1,j+1);
    this->figureCoordinate[index++] = Coordinate(i+1,j+1);
    this->figureCoordinate[index++] = Coordinate(i-1,j+2);
    this->figureCoordinate[index++] = Coordinate(i+2,j+2);
    this->figureCoordinate[index++] = Coordinate(i,j+3);
    this->figureCoordinate[index] = Coordinate(i+1,j+3);

}

Tub::Tub(int i, int j) : Shape(4,i,j)
{
    int index = 0;
    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i+1,j+1);
    this->figureCoordinate[index++] = Coordinate(i,j+2);
    this->figureCoordinate[index] = Coordinate(i-1,j+1);

}

Eater::Eater(int i, int j) : Shape(7,i,j)
{
    int index = 0;
    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i + 1,j);
    this->figureCoordinate[index++] = Coordinate(i,j + 1);
    this->figureCoordinate[index++] = Coordinate(i + 1,j + 2);
    this->figureCoordinate[index++] = Coordinate(i + 2,j + 2);
    this->figureCoordinate[index++] = Coordinate(i + 3,j + 2);
    this->figureCoordinate[index++] = Coordinate(i + 3,j + 3);
}
