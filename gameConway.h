#ifndef GAMECONWAY_H
#define GAMECONWAY_H

#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QImage>
#include <qDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QColor>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <qmath.h>
#include <QVector>
#include <QWheelEvent>

#include "myVector.cpp"
#include "conwayCell.h"
#include "nukeCell.h"
#include "constantcell.h"
#include "enemyCell.h"
#include "oscillators.h"
#include "guns.h"
#include "spaceships.h"
class GameConway : public QWidget
{
    Q_OBJECT
public:
    explicit GameConway(QWidget *parent = nullptr);
    ~GameConway();


protected:
    void paintEvent(QPaintEvent *); // изображение видимого поля
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private slots:
    void paintGrid(QPainter &p); // изображает клеточное поле
    void paintUniverse(QPainter &p); // разукрашивает клетки
    void newGeneration(); // новое поколение
public:

    void startGame(); // start
    void stopGame(); // finish

    void clear(); // clear

    int interval(); // интервал между поколениямим
    void setInterval(int); // сеттер для интервала

    void addFigure(Shape* ); // добавить фигуру в текущее поколение
    void addToMapTemplate(Shape*); // для изображения шаблона в видимое поле

    void windowShift(Direction); // сдвиг видмого поля по игровому
    void incWindowScale();
    void decWindowScale();

    QColor getBorderColor(); // цвет клетки
    void setBorderColor(const QColor &); // установить цвет

    void setDrawFigure(); // пользователь изображает фигуру

    QString dump(); // преобразует все игровое поле в строку для сохранения

    int getFieldSize();
    int getMapSize();

    void setMapSize(const int&);
    void setFieldSize(const int&);

    int getXOffset();
    int getYOffset();

    void setXOffset(const int&);
    void setYOffset(const int&);

    void setDump(const QString &data); // устанавливает игровое поле из файла

    void addTemplate(Figure temp); // добавляет шаблон фигуры который хочет поставить пользователь
    void addCellTemplate(Cells temp); //добавляет шаблон клетки
    void changeCell(); // пользователь изображает клетку
    bool getFigureDrawStatus();
    void setFigureDrawStatus(bool _status);

    void setSpinAmount(const int& _amount);
    int getSpinAmount();

private:
    void extendGameMap(); // расширить границы карты если дошли до конца
    void falseVector(); // обнуляет вектор igureTemplateMap

    int xOffset;//сдвиг по оси Х
    int yOffset;//сдвиг по оси Y

    MyVector<Coordinate> coordsWithAliveCell;//чтобы знать какие координаты посещать

    MyVector<ConwayCell*> gameMap; // текущее поколение
    MyVector<ConwayCell*> prevMap; // следующее
    MyVector<ConwayCell*> figureTemplateMap; // для изображения шаблонов фигур

    bool figureDraw; // отрисовка фигур
    Figure _template; // шаблон фигуры
    int spinAmount; // колво оборотов

    bool newCellIsAdding; // для отрисовки других клеток
    Cells _cellTemplate;
    // цвет
    QColor borderColor;
    QTimer* timer;


    int fieldSize;// размер поля
    int mapSize;// развер игрового

    ConwayCell* generateCell(Cells); // создает клетку
    Shape* createFigure(Figure figure, int , int );

    bool isAlive(int , int ); // если клетка == conwayCell
    bool isAliveEnemy(int , int );// если клетка ==EnemyCell
    void nukeExpand(int , int );// если клетка == NukeCell
};

#endif // GAMECONWAY_H
