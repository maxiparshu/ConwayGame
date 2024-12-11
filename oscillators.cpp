#include "oscillators.h"


Pulsar::Pulsar(int i, int j) : Shape(48,i,j) {
    int index = 0;
    period = 3;
    int Ystart = i;
    int Xstart = j;
    Xstart += 2;
    addLine(index,3,Xstart, Ystart,RIGHT);
    Ystart += this->Y[RIGHT] * 3 + 2;
    Xstart += this->X[RIGHT] * 3;
    addLine(index,3,Xstart, Ystart,DOWN);
    Ystart += this->Y[DOWN] * 3;
    Xstart += this->X[DOWN] * 3 - 1;
    addLine(index,3,Xstart, Ystart,LEFT);
    Ystart += this->Y[LEFT] * 3;
    Ystart--;
    Xstart += this->X[LEFT] * 3 - 1;
    addLine(index,3,Xstart, Ystart, UP);
    auto* temp = reflect(0,j + 6, this->figureCoordinate,12);
    for (int k = 0; k < 12; k++) {
        this->figureCoordinate[index++] = temp[k];
    }
    temp = reflect(i + 6,0, this->figureCoordinate,24);
    for (int k = 0; k < 24; k++) {
        this->figureCoordinate[index++] = temp[k];
    }

}
Blinker::Blinker(int i, int j): Shape(3,i,j - 1){
    int index = 0;
    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i+1,j);
    this->figureCoordinate[index] = Coordinate(i+2,j);
    period = 2;
}

Toad::Toad(int i, int j): Shape(6,i,j){
    period = 2;
    int index = 0;
    this->figureCoordinate[index++] = Coordinate(i,j);
    this->figureCoordinate[index++] = Coordinate(i,j+1);
    this->figureCoordinate[index++] = Coordinate(i,j+2);
    this->figureCoordinate[index++] = Coordinate(i-1,j+1);
    this->figureCoordinate[index++] = Coordinate(i-1,j+2);
    this->figureCoordinate[index] = Coordinate(i-1,j+3);

}

Beacon::Beacon(int i, int j): Shape(8,i,j){
    period = 2;
    int index = 0;
    auto temp = Block(i,j);
    for (int k = 0; k < 4; k++) {
        this->figureCoordinate[index++] = temp.getCoords()[k];
    }
    temp = Block(i + 2,j + 2);
    for (int k = 0; k < 4; k++) {
        this->figureCoordinate[index++] = temp.getCoords()[k];
    }


}

Galaxy::Galaxy(int i, int j): Shape(48,i,j){
    int index = 0;
    period = 6;
    addLine(index,6,j, i, RIGHT);
    addLine(index,6,j,i+ 1, RIGHT);
    addLine(index,6,j,i + 3, DOWN);
    addLine(index,6,j + 1,i + 3, DOWN);
    addLine(index,6,j+ 3,i+7, RIGHT);
    addLine(index,6,j+ 3,i+8, RIGHT);
    addLine(index,6,j + 7,i, DOWN);
    addLine(index,6,j+ 8,i, DOWN);

}
