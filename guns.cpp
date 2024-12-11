#include "guns.h"


GosperGun::GosperGun(int i, int j) : Shape(36,i-4,j){
    Block temp(i,j);
    Coordinate coordinate[36];
    for (int k = 0; k < 4; k++) {
        coordinate[k] = temp.getCoords()[k];
    }

    int index = 4;
    coordinate[index++] = Coordinate(i, j + 10);
    coordinate[index++] = Coordinate(i + 1, j + 10);
    coordinate[index++] = Coordinate(i + 2, j + 10);
    coordinate[index++] = Coordinate(i - 1, j + 11);
    coordinate[index++] = Coordinate(i + 3, j + 11);
    coordinate[index++] = Coordinate(i - 2, j + 12);
    coordinate[index++] = Coordinate(i - 2 , j + 13);
    coordinate[index++] = Coordinate(i + 4 , j + 12);
    coordinate[index++] = Coordinate(i + 4 , j + 13);
    coordinate[index++] = Coordinate(i + 1 , j + 14);
    coordinate[index++] = Coordinate(i - 1 , j + 15);
    coordinate[index++] = Coordinate(i + 3 , j + 15);
    coordinate[index++] = Coordinate(i,j + 16);
    coordinate[index++] = Coordinate(i + 1,j + 16);
    coordinate[index++] = Coordinate(i + 2,j + 16);
    coordinate[index++] = Coordinate(i + 1,j + 17);
    coordinate[index++] = Coordinate(i,j + 20);
    coordinate[index++] = Coordinate(i,j + 21);
    coordinate[index++] = Coordinate(i - 1,j + 20);
    coordinate[index++] = Coordinate(i - 2,j + 20);
    coordinate[index++] = Coordinate(i - 1,j + 21);
    coordinate[index++] = Coordinate(i - 2,j + 21);
    coordinate[index++] = Coordinate(i + 1,j + 22);
    coordinate[index++] = Coordinate(i - 3,j + 22);
    coordinate[index++] = Coordinate(i + 1,j + 24);
    coordinate[index++] = Coordinate(i + 2,j + 24);
    coordinate[index++] = Coordinate(i - 3,j + 24);
    coordinate[index++] = Coordinate(i - 4,j + 24);

    temp = Block(i - 2,j + 34);
    for (int k = 0; k < 4; k++) {

        coordinate[index + k] = temp.getCoords()[k];

    }


    for (int k = 0; k < this->amount; k++) {

        this->figureCoordinate[k] = coordinate[k];
    }
}
SimkinGun::SimkinGun(int i, int j) : Shape(36,i,j){
    auto temp = Block(i,j);
    int index = 0;
    Coordinate coordinate[36];
    for (int k = 0; k < 4; k++) {
        coordinate[index++] = temp.getCoords()[k];
    }
    temp = Block(i,j + 7);

    for (int k = 0; k < 4; k++) {
        coordinate[index++] = temp.getCoords()[k];
    }
    temp = Block(i + 3, j + 4);
    for (int k = 0; k < 4; k++) {
        coordinate[index++] = temp.getCoords()[k];
    }
    coordinate[index++] = Coordinate(i + 10,j + 21);
    coordinate[index++] = Coordinate(i + 11,j + 21);
    coordinate[index++] = Coordinate(i + 12,j + 21);
    coordinate[index++] = Coordinate(i + 12,j + 22);
    coordinate[index++] = Coordinate(i + 12,j + 23);
    coordinate[index++] = Coordinate(i + 9,j + 22);
    coordinate[index++] = Coordinate(i + 9,j + 23);
    coordinate[index++] = Coordinate(i + 9,j + 25);
    coordinate[index++] = Coordinate(i + 9,j + 26);
    coordinate[index++] = Coordinate(i + 10,j + 27);
    coordinate[index++] = Coordinate(i + 11,j + 28);
    coordinate[index++] = Coordinate(i + 12,j + 27);
    coordinate[index++] = Coordinate(i + 13,j + 26);
    coordinate[index++] = Coordinate(i + 17,j + 21);
    coordinate[index++] = Coordinate(i + 17,j + 20);
    coordinate[index++] = Coordinate(i + 18,j + 20);
    coordinate[index++] = Coordinate(i + 19,j + 21);
    coordinate[index++] = Coordinate(i + 19,j + 22);
    coordinate[index++] = Coordinate(i + 19,j + 23);
    coordinate[index++] = Coordinate(i + 20,j + 23);
    temp =  Block(i + 11,j + 31);
    for (int k = 0; k < 4; k++) {
        coordinate[index++] = temp.getCoords()[k];
    }

    for (int k = 0; k < this->amount; k++) {
        this->figureCoordinate[k] = coordinate[k];
    }
}
