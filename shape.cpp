#include "shape.h"



Coordinate &Coordinate::operator =(const Coordinate &other)
{
    this->I = other.I;
    this->J = other.J;
    return *this;
}

bool Coordinate::operator ==(const Coordinate &other) const{
    return this->I == other.I && this->J == other.J;
}

bool Coordinate::operator !=(const Coordinate &other) const{
    return !(*this == other);
}

void Shape::findMax()
{
    for (int i = 0; i < this->amount; i++) {
        if (abs(this->figureCoordinate[i].I) + 1 - startI > this->sideMaxRectI)
            sideMaxRectI = this->figureCoordinate[i].I + 1 -startI;
        if (abs(this->figureCoordinate[i].J) + 1 - startJ > this->sideMaxRectJ)
            sideMaxRectJ = this->figureCoordinate[i].J + 1 - startJ;
    }
}

Coordinate *Shape::reflect(int Yline, int Xline, Coordinate *&coords, int size)
{
    auto* list = new Coordinate[size];
    for (int i = 0; i <size; i++) {
        if(Yline > 0)
            list[i].I = 2 * Yline - coords[i].I;
        else
            list[i].I = coords[i].I;
        if(Xline > 0)
            list[i].J = 2 * Xline - coords[i].J;
        else
            list[i].J = coords[i].J;
    }
    return list;
}

Shape::Shape(const int &_amount, int startI, int startJ) :  sideMaxRectI(0), sideMaxRectJ(0), startI(startI), startJ(startJ)
{
        figureCoordinate = new Coordinate[_amount];
        amount = _amount;
}

Coordinate *Shape::getCoords()
{
        return this->figureCoordinate;
}

int Shape::getSize() const
{
        return this->amount;
}

void Shape::setCoords(Coordinate *& coords)
{
        for(int i =0 ;  i < amount; i++ )
        {
            figureCoordinate[i] = coords[i];
        }
}

Coordinate *Shape::drawLine(int length, int startX, int startY, Direction directions)
{
        auto* temp = new Coordinate[length];
        for (int i = 0; i < length; i++) {
        temp[i] = Coordinate(startY + this->Y[directions] * i, startX + this->X[directions] * i);
        }
        return temp;
}

void Shape::addLine(int &begin, int length, int startX, int startY, Direction direc)
{
        Coordinate* temp = drawLine(length,startX,startY,direc);
        for (int i = 0; i < length; i++) {
        this->figureCoordinate[begin + i] = temp[i];
        }
        begin += length;
}

void Shape::turnOver90Degree()
{
        this->findMax();
        bool** inData = new bool*[sideMaxRectI];
        bool** outData = new bool*[sideMaxRectJ];

        for (int i = 0; i < sideMaxRectI; i++) {
        inData[i] = new bool[sideMaxRectJ]{false};
        }
        for (int i = 0; i < sideMaxRectJ; i++) {
        outData[i] = new bool[sideMaxRectI]{false};
        }
        for (int i = 0; i < amount; i++) {
        inData[this->figureCoordinate[i].I - startI][this->figureCoordinate[i].J - startJ] = true;
        }

        for (int i = 0; i < sideMaxRectI; i++) {
        for (int j = 0; j < sideMaxRectJ; j++) {
            outData[j][sideMaxRectI - i - 1] = inData[i][j];
        }
        }

        int index =0;
        for (int i = 0; i < sideMaxRectJ; i++) {
        for (int j = 0; j < sideMaxRectI; j++) {
            if (outData[i][j])
            {
                this->figureCoordinate[index++] = Coordinate(i + startI,j + startJ);
            }
        }
        }

        delete []inData;
        delete [] outData;
}
