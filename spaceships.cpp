#include "spaceships.h"


Glider::Glider(int i, int j) : Shape(5,i,j){
    Coordinate coordinate[5];
    coordinate[0] = Coordinate(i + 0, j + 0);
    coordinate[1] = Coordinate(i + 1, j + 1);
    coordinate[2] = Coordinate(i + 2, j + 0);
    coordinate[3] = Coordinate(i + 2, j + 1);
    coordinate[4] = Coordinate(i + 1, j + 2);

    for (int k = 0; k < 5; k++) {
        this->figureCoordinate[k] = coordinate[k];
    }
}

LargeSpaceship::LargeSpaceship(int i, int j) : Shape(13,i,j-2)
{
    int index = 0;

    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i,j + 1);
    this->figureCoordinate[index++] = Coordinate(i + 1,j - 2);
    this->figureCoordinate[index++] = Coordinate(i + 1,j + 3);
    this->figureCoordinate[index++] = Coordinate(i + 3,j - 2);
    i += 4;
    j--;
    addLine(index,6,j,i,RIGHT);
    j += 5;
    i--;
    addLine(index,3,j,i, UP);
}

MiddleSpaceship::MiddleSpaceship(int i, int j) : Shape(11,i,j-2)
{
    int index = 0;
    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i+1,j-2);
    this->figureCoordinate[index++] = Coordinate(i+1,j+2);
    this->figureCoordinate[index++] = Coordinate(i+3,j-2);
    i += 2;
    j += 3;
    addLine(index,3,j,i,DOWN);
    i += 2;
    j -= 1;
    addLine(index,5,j,i,LEFT);
}

LightSpaceship::LightSpaceship(int i, int j) : Shape(9,i,j)
{
    int index = 0;
    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i+2,j);
    this->figureCoordinate[index++] = Coordinate(i,j+3);
    j += 4;
    i++;
    addLine(index,3,j,i,DOWN);
    i += Y[DOWN] * 2;
    j--;
    addLine(index,4,j,i,LEFT);

}

LightPufferTrain::LightPufferTrain(int i, int j) : Shape(22, i,j)
{
    int index =0;
    this->figureCoordinate[index++] = Coordinate(i+2,j);
    this->figureCoordinate[index++] = Coordinate(i,j+3);
    this->figureCoordinate[index++] = Coordinate(i+ 1,j+4);
    this->figureCoordinate[index++] = Coordinate(i+ 2,j+4);
    addLine(index,4,j+1,i+3,RIGHT);

    this->figureCoordinate[index++] = Coordinate(i+7,j);
    this->figureCoordinate[index++] = Coordinate(i+8,j + 1);
    this->figureCoordinate[index++] = Coordinate(i+8,j + 2);
    this->figureCoordinate[index++] = Coordinate(i+9,j + 2);
    this->figureCoordinate[index++] = Coordinate(i+10,j + 2);
    this->figureCoordinate[index++] = Coordinate(i+11,j + 1);

    this->figureCoordinate[index++] = Coordinate(i+16,j);
    this->figureCoordinate[index++] = Coordinate(i + 14,j+3);
    this->figureCoordinate[index++] = Coordinate(i+ 15,j+4);
    this->figureCoordinate[index++] = Coordinate(i+ 16,j+4);

    addLine(index,4,j+1,i+17,RIGHT);
}
