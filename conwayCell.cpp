#include "conwayCell.h"


ConwayCell::ConwayCell(const ConwayCell &other) {
    this->color = other.color;
    this->statusIsALive = other.statusIsALive;
    this->colorChar = other.colorChar;
}

bool ConwayCell::operator ==(const ConwayCell &other){
    return this->statusIsALive == other.statusIsALive && this->color == other.color;
}

bool ConwayCell::operator ==(Cells cellName){
    switch(cellName)
    {
    case CONWAYCELL:
        return color == Qt::black;
    case NUKE:
        return color == Qt::yellow;
    case ENEMY:
        return color == Qt::red;
    case CONSTANT:
        return color == Qt::green;
    }
}
