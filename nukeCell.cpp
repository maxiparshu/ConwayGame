#include "nukeCell.h"

NukeCell::NukeCell() : ConwayCell(false,Qt::yellow, '0'){
    rangeMax = 10;
    currentRange = 0;

}

NukeCell::NukeCell(const NukeCell &other) {
    this->color = other.color;
    this->statusIsALive = other.statusIsALive;
    this->colorChar = other.colorChar;
    this->rangeMax = other.rangeMax;
    this->currentRange = other.currentRange;
}


void NukeCell::rangeInc()
{
    currentRange++;
}
