#pragma once
#include "conwayCell.h"


class NukeCell : public ConwayCell
{
    int rangeMax; // максимальный радиус
    int currentRange; // текущий радиус
public:
    NukeCell();
    NukeCell(const NukeCell&);




    void rangeInc();
    int getMaxRange(){return this->rangeMax;}
    int getCurrentRange() {return this->currentRange;}
    void setCurrentRange (const int& _range) {this->currentRange = _range;}
};
