#pragma once
#include <QColor>
#include <Qt>

enum Cells{ // перечисление всех видов клеток
    CONWAYCELL,
    NUKE,
    ENEMY,
    CONSTANT
};

class ConwayCell
{
protected:
    bool statusIsALive; // жива или нет
    QColor color; // цвет клетки
    QChar colorChar; // символ для сохранения в файл
public:
    ConwayCell(bool _status,const Qt::GlobalColor& _color,const QChar& _charColor) : statusIsALive(_status), color(QColor(_color)), colorChar(_charColor){
    } // конструкторк
    ConwayCell() : statusIsALive(false), color(Qt::black), colorChar('*'){}// конструктор по умолчанию

    ConwayCell(const ConwayCell& other);// конструкто копирования

    QColor getColor() const {return this->color;} // геттер для цвета
    QChar getSymbol() const {return this->colorChar;} // геттер для символа
    bool getStatus() const {return this->statusIsALive;} // геттер для состояния

    void setStatus(bool _status){this->statusIsALive = _status;} // сеттер для состояния

    ConwayCell& operator =(const ConwayCell& other)= default;
    bool operator ==(const ConwayCell&);
    bool operator ==(Cells);
};


