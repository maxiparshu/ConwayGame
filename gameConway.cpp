#include "gameConway.h"

GameConway::GameConway(QWidget *parent)
    :QWidget(parent),
    timer(new QTimer(this)),
    fieldSize(50),
    borderColor(Qt::black),
    figureDraw(false),
    newCellIsAdding(false),
    spinAmount(0),
    xOffset(4 * 50),
    yOffset(4 * 50)
{

    timer->setInterval(175);
    mapSize = fieldSize * 20;
    gameMap.resize((mapSize) * (mapSize ));
    prevMap.resize((mapSize) * (mapSize));
    figureTemplateMap.resize((fieldSize + 2) * (fieldSize + 2));
    for(int i = 0; i < (mapSize) * (mapSize); i ++)
    {
        gameMap[i] = new ConwayCell();
        prevMap[i] = new ConwayCell();
    }
    for(int i = 0; i < (fieldSize + 2) * (fieldSize + 2); i ++)
    {
        figureTemplateMap[i] = new ConwayCell();
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));

    this->setMouseTracking(true);
}

GameConway::~GameConway()
{
    gameMap.clear();;
    figureTemplateMap.clear();
}

void GameConway::startGame()
{
    timer->start();
}

void GameConway::stopGame()
{
    timer->stop();
}

void GameConway::clear()//очистка поля
{
    for(int k = 0; k < mapSize; k++) {
        for(int j = 0; j <mapSize; j++) {
            gameMap[k * mapSize + j] = new ConwayCell();
            prevMap[k * mapSize + j] = new ConwayCell();
        }
    }
    coordsWithAliveCell.clear();
    update();
}

int GameConway::interval()
{
    return timer->interval();
}

void GameConway::setInterval(int msec)
{
    timer->setInterval(msec);
}
void GameConway::paintEvent(QPaintEvent *)
{

    QPainter p(this);

    paintGrid(p);
    paintUniverse(p);
}

void GameConway::mousePressEvent(QMouseEvent *e)
{
    int cellWidth = ((width()+ fieldSize) / fieldSize);
    int cellHeight = ((height()+ fieldSize) / fieldSize);
    QPointF coords = e->position();
    int k =floor(coords.y()/cellHeight) + 1;//координата по y
    int j =floor(coords.x()/cellWidth) + 1;// координата по x'
    int position =(k + yOffset)*mapSize   + j + xOffset;

    if(!figureDraw)  // если не ставится фигура
    {
        if(!newCellIsAdding) // и не ставиться другая клетка
        {
            if(gameMap[position]->getColor() == CONWAYCELL) //если базовая клетка
            {
                gameMap[position]->setStatus(!(gameMap[position]->getStatus()));
                if(gameMap[position]->getStatus()) // если статус true  то добавляем координаты в живые клетки
                {
                    coordsWithAliveCell.pushBack(Coordinate((k + yOffset) , j + xOffset));
                }
                else {
                    coordsWithAliveCell.erase(Coordinate((k + yOffset) ,j + xOffset));
                }

            }
            else
            {
                gameMap[position] = new ConwayCell(); // иначе обнуляем
            }

        }
        else
        {

            gameMap[position] = generateCell(_cellTemplate);
            coordsWithAliveCell.pushBack(Coordinate((k + yOffset)  , j + xOffset));
            gameMap[position]->setStatus(true);
            newCellIsAdding = e->buttons() == Qt::RightButton;
            figureDraw = false;

        }
        update();

    }
    else{
        figureDraw = e->buttons() == Qt::RightButton; // фигура изображена
        Shape* _figure = createFigure(this->_template,k + yOffset,j + xOffset); // создать фигуру класса темлейт
        spinAmount = 0; // обнуляем количество оборотов
        addFigure(_figure); // добавляем на карту
        update();
        newCellIsAdding = false;
        falseVector(); // обнуляем карту
    }
}

void GameConway::mouseMoveEvent(QMouseEvent *e)
{
    int cellWidth = ceil((width()+ fieldSize)/ fieldSize);
    int cellHeight = ceil((height()+ fieldSize)/ fieldSize);
    int j = floor(e->x()/cellWidth) + 1;
    int k = floor(e->y()/cellHeight) + 1;
    int position = (k + yOffset)*mapSize  + j + xOffset;
    if(figureDraw)
    {

        Shape* _figure = createFigure(this->_template,k,j );
        falseVector();
        addToMapTemplate(_figure);
    }
    if(!gameMap[position]->getStatus() && e->buttons() == Qt::LeftButton)
    {
        gameMap[position]->setStatus(!(gameMap[position]->getStatus()));
        coordsWithAliveCell.pushBack(Coordinate((k +  yOffset) , j + xOffset));
        }
    update();

}

void GameConway::paintGrid(QPainter &p)
{

    QColor gridColor = borderColor; // цвет
    gridColor.setAlpha(40); // должно быть ярче
    p.setPen(gridColor);
    int  cellHeight = ceil((height()+ fieldSize)/fieldSize) ; // высота
    int cellWidth = ceil((width() + fieldSize)/fieldSize) ; //ширина
    int k = cellWidth;

    for(int i = 1; i <= fieldSize; i++ )
    {
        p.drawLine(k, 0, k,height() - 1);
        k += cellWidth;

    }
    k = cellHeight;
    for(int i = 1; i <= fieldSize; i++ )
    {
        p.drawLine(0, k, width() -1 , k);
        k += cellHeight;
    }
   QRectF borders(0, 0, width() -1, height() -1); // границы поля
    p.setPen(Qt::black);
    p.drawRect(borders);
}
void checkRange(int &xOffset,int& yOffset,int fieldSize,int mapSize){
    if(xOffset < 0)
        xOffset = 0;
    if(yOffset < 0)
        yOffset = 0;
}
void GameConway::paintUniverse(QPainter &p)
{
    checkRange(xOffset, yOffset, fieldSize, mapSize);
    int cellWidth = ceil((width() + fieldSize)/fieldSize) ; //ширина
    int  cellHeight = ceil((height()+ fieldSize)/fieldSize) ; // высота

    for(int i=1; i <= fieldSize; i++) {
        for(int j=1; j <= fieldSize; j++) {

            if(gameMap[(i+yOffset)*mapSize + xOffset + j]->getStatus() ) { // ecли имеет смысл
                int left = (cellWidth*j-cellWidth); // граница слева
                int top  = (cellHeight*i-cellHeight); // граница сверху
                QRect r(left, top,  cellWidth  , cellHeight);

                p.fillRect(r, QBrush(gameMap[(i+yOffset)*mapSize+  xOffset + j]->getColor())); // заполняет прямоугольник цветом
            }
            if(figureTemplateMap[i*fieldSize + j]->getStatus())
            {

                int left = (cellWidth*j-cellWidth); // граница слева
                int top  = (cellHeight*i-cellHeight); // граница сверху
                QRect r(left, top,  cellWidth  , cellHeight);

                p.fillRect(r, QBrush(Qt::lightGray)); // заполняет прямоугольник цветом
            }

        }
    }

}

void GameConway::addFigure(Shape *figure)
{
    for(int i = 0; i < figure->getSize(); i++){
        gameMap[figure->getCoords()[i].I *mapSize + figure->getCoords()[i].J]->setStatus(true); // добавляем на карту
        //добавляем в живые
        coordsWithAliveCell.pushBack(Coordinate(figure->getCoords()[i].I, figure->getCoords()[i].J));
    }
}

void GameConway::addToMapTemplate(Shape *figure)
{
    for(int i = 0; i < figure->getSize(); i++){
        if(figure->getCoords()[i].J <= fieldSize && figure->getCoords()[i].I > 0 && figure->getCoords()[i].I <= fieldSize && figure->getCoords()[i].J > 0){
            figureTemplateMap[figure->getCoords()[i].I * fieldSize + figure->getCoords()[i].J]->setStatus(true);
        }
    }
}


QColor GameConway::getBorderColor()
{
    return this->borderColor;
}

void GameConway::setBorderColor(const QColor &color)
{

    borderColor = color;
    update();
}

void GameConway::setDrawFigure(){ this->figureDraw = true;}

QString GameConway::dump()
{
    QChar temp;
    QString master = "";
    for(int k = 0; k < mapSize; k++) {
        for(int j = 0; j < mapSize; j++) {
            if(gameMap[k*mapSize + j]->getStatus() == true) {
                temp = gameMap[k * mapSize + j]->getSymbol();
            } else {
                temp = 'o';
            }
            master.append(temp);
        }
        master.append("\n");
    }
    return master;
}
Cells getCellType(QChar symbol){
    if(symbol == '*')
        return CONWAYCELL;
    if(symbol == '0')
        return NUKE;
    if(symbol == '1')
        return CONSTANT;
    return ENEMY;
}
void GameConway::setDump(const QString &data)
{
    int current = 0;
    for(int k = 0; k < mapSize; k++) {
        for(int j = 0; j < mapSize; j++) {
            if(data[current] != 'o')
            {
                gameMap[k * mapSize + j] = generateCell(getCellType(data[current]));
                gameMap[k*mapSize + j]->setStatus(true);
                coordsWithAliveCell.pushBack(Coordinate(k , j));
            }
            current++;
        }
        current++;
    }
    update();
}

void GameConway::addTemplate(Figure temp){this->_template = temp;}

void GameConway::addCellTemplate(Cells temp){this->_cellTemplate = temp;}

void GameConway::changeCell(){this->newCellIsAdding = true;}

bool GameConway::getFigureDrawStatus(){return this->figureDraw;}

void GameConway::setFigureDrawStatus(bool _status){this->figureDraw = _status;}

void GameConway::windowShift(Direction direction)
{
    switch (direction) {
    case RIGHT: // сдвиг по х на плюс один
    {
        if(xOffset  + fieldSize + 1 < mapSize)
            xOffset++;
        else
            extendGameMap();
        break;
    }
    case LEFT:// сдвиг по х на минус один
    {
        if(xOffset  > 0)
            xOffset--;
        else
            extendGameMap();
        break;
    }
    case UP: // сдвиг по y на минус один
    {
        if(yOffset  > 0)
            yOffset--;
        else
            extendGameMap();
        break;
    }
    case DOWN:// сдвиг по y на плюс один
    {
        if(yOffset  + fieldSize + 1 < mapSize)
            yOffset++;
        else
            extendGameMap();
        break;
    }

    }
    update();
}
void initializeVector(MyVector<ConwayCell*> vector, int newSize){
    for(int i =0; i < (newSize + 2)*(newSize + 2); i++)
    vector[i] = new ConwayCell();


}
void GameConway::extendGameMap()
{
    int newSize =mapSize +    2* mapSize;
    MyVector<ConwayCell*> tempVec;
    tempVec.resize(mapSize * mapSize);
    for(int i =0; i < coordsWithAliveCell.size(); i++)
    {
    Coordinate coords = coordsWithAliveCell[i];
        int position = coords.I * mapSize + coords.J;
         if(*gameMap[position] == NUKE)
         {
               tempVec[position] = new ConwayCell();
                auto tmpCell = NukeCell(*((NukeCell*)(gameMap[position])));
                 tempVec[position] = &tmpCell;
          }
          else
          {
              tempVec[position] = new ConwayCell(*gameMap[position] );
          }
    }

    prevMap.resize(newSize * newSize);
    gameMap.resize(newSize * newSize);
    MyVector<Coordinate> tmpCoords = coordsWithAliveCell;
    coordsWithAliveCell.clear();

    for(int i =0; i < newSize * newSize; i++)
    {
        gameMap[i] = new ConwayCell();
        prevMap[i] = new ConwayCell();
    }

    for (int i =0 ;i < tmpCoords.size(); i++ ){
        Coordinate coords = tmpCoords[i];
        int position = coords.I * mapSize + coords.J;
        auto tmpCell = ConwayCell();
        delete gameMap[(coords.I +newSize /2)* newSize + newSize /2 + coords.J] ;
        if(*tempVec[position] == NUKE)
        {

           gameMap[(coords.I +newSize /2)* newSize + newSize /2 + coords.J]  = new NukeCell(*((NukeCell*)(tempVec[position])));
        }
        else
        {
            gameMap[(coords.I +newSize /2)* newSize + newSize /2 + coords.J] = new ConwayCell(*tempVec[position] );
        }
        gameMap[(coords.I +newSize /2)* newSize + newSize /2 + coords.J] ->setStatus(true);
        coordsWithAliveCell.pushBack(Coordinate((coords.I + newSize /2), newSize /2 + coords.J));;
    }
    mapSize = newSize;
    xOffset += mapSize /2;
    yOffset += mapSize /2;
}


void GameConway::incWindowScale()
{
    if(fieldSize + 10 <= mapSize / 4)
    {

        int cellWidth = (width() / fieldSize);
        int cellHeight = (height() / fieldSize);
        fieldSize += 10;
        QPoint coords = QCursor::pos();

        int i =floor(coords.y()/cellHeight);//координата по y
        int j =floor(coords.x()/cellWidth) ;// координата по x
        xOffset = xOffset + j  - fieldSize/2;
        yOffset = yOffset + i  - fieldSize/2;
        figureTemplateMap.clear();

        figureTemplateMap.resize((fieldSize + 2)*(fieldSize + 2));
        initializeVector(figureTemplateMap, fieldSize);


        update();
    }
}


void GameConway::decWindowScale()
    {

        if(fieldSize  > 10)
        {
            QPoint coords = QCursor::pos();
            int cellWidth = ceil((width() + fieldSize) / fieldSize);
            int cellHeight =  ceil((height() + fieldSize) / fieldSize);
            int j =floor((coords.x()/cellWidth) );//координата по y
            int i =floor((coords.y()/cellHeight) );// координата по x'
            fieldSize -= 10;

            xOffset = xOffset +  j - fieldSize/2;
            yOffset =yOffset + i -fieldSize/2;
            if(fieldSize > 50)
            {
                figureTemplateMap.clear();
                figureTemplateMap.resize((fieldSize + 2)*(fieldSize + 2));
                initializeVector(figureTemplateMap, fieldSize);
            }
            update();
        }
    }

void GameConway::falseVector()
{
        for(int i = 0; i < fieldSize + 2; i++)
        {
            for(int j = 0; j < fieldSize + 2 ; j++)
             {
                 figureTemplateMap[i * fieldSize + j]->setStatus(false);
             }
        }
}

void GameConway::setSpinAmount(const int &_amount)
{
    this->spinAmount = _amount;
}
int GameConway::getSpinAmount(){return spinAmount;}


int GameConway::getFieldSize()
{
    return fieldSize;
}

int GameConway::getMapSize()
{
    return mapSize;
}

void GameConway::setMapSize(const int &value)
{
    mapSize = value;
    gameMap.resize((mapSize) * (mapSize ));
    prevMap.resize((mapSize) * (mapSize));

    for(int i = 0; i < (mapSize) * (mapSize); i ++)
    {
        gameMap[i] = new ConwayCell();
        prevMap[i] = new ConwayCell();
    }
}

void GameConway::setFieldSize(const int &value)
{
    fieldSize =  value;
    figureTemplateMap.resize((fieldSize + 2) * (fieldSize + 2));
    for(int i = 0; i < (fieldSize + 2) * (fieldSize + 2); i ++)
    {
        figureTemplateMap[i] = new ConwayCell();
    }
}

int GameConway::getXOffset()
{
    return xOffset;
}

int GameConway::getYOffset()
{
    return yOffset;
}

void GameConway::setXOffset(const int &value)
{
    xOffset = value;
}

void GameConway::setYOffset(const int &value)
{
    yOffset = value;
}

ConwayCell *GameConway::generateCell(Cells _cellTemplate)
{
    switch(_cellTemplate)
    {
    case CONWAYCELL:
        return new ConwayCell();
    case NUKE:
        return new NukeCell();
    case ENEMY:
        return new EnemyCell();
    case CONSTANT:
        return new ConstantCell();
    }
}

Shape *GameConway::createFigure(Figure figure, int i, int j)
{
    Shape* temp;
    switch(figure)
    {
    case BLOCK:
    {

        temp = new Block(i,j);
        break;
    }
    case BEEHIVE:
    {
        temp = new BeeHive(i,j);
        break;
    }
    case LOAF:
    {
        temp = new Loaf(i,j);
        break;
    }
    case BOAT:
    {
        temp = new Boat(i,j);
        break;
    }
    case TUB:
    {
        temp = new Tub(i,j);
        break;
    }
    case BLINKER:
    {
        temp = new Blinker(i,j);
        break;
    }
    case TOAD:
    {
        temp = new Toad(i,j);
        break;
    }
    case BEACON:
    {
        temp = new Beacon(i,j);
        break;
    }
    case PULSAR:
    {
        temp = new Pulsar(i,j);
        break;
    }
    case LIGHTSHIP:
    {
        temp = new LightSpaceship(i,j);
        break;
    }
    case MIDDLESHIP:
    {
        temp = new MiddleSpaceship(i,j);
        break;
    }
    case HEAVYSHIP:
    {
        temp = new LargeSpaceship(i,j);
        break;
    }
    case GOSPER:
    {
        temp = new GosperGun(i,j);
        break;
    }
    case SIMKIN:
    {
        temp = new SimkinGun(i,j);
        break;
    }
    case GLIDER:
    {

        temp = new Glider(i,j);
        break;
    }
    case LIGHTPUFFERTRAIN:
    {
        temp = new LightPufferTrain(i,j);
        break;
    }
    case EATER:{
        temp = new Eater(i,j);
        break;
    }
    case GALAXY:{
    temp = new Galaxy(i,j);
    break;
        }
    }
    for(int i = 0; i < spinAmount; i++)
        temp->turnOver90Degree();
    return temp;
}

void GameConway::newGeneration()
{
    int notChanged=0;

    for(int i =0; i < coordsWithAliveCell.size(); i++){  // добавить новые клетки на предыдущую карту
        Coordinate coords = coordsWithAliveCell[i];
        delete prevMap[coords.I * mapSize + coords.J];
        int position = coords.I * mapSize + coords.J;
        if(*gameMap[position] == NUKE)
        {
            prevMap[position] = new ConwayCell();
            auto tmpCell = NukeCell(*((NukeCell*)(gameMap[position])));
            prevMap[position] = &tmpCell;
        }
        else
        {
            prevMap[position] = new ConwayCell(*gameMap[position] );
        }
    }
    auto coordsWithAliveCellTemp = coordsWithAliveCell;
    for(int i =0; i < coordsWithAliveCellTemp.size(); i++){

        Coordinate coords = coordsWithAliveCellTemp[i];
        coordsWithAliveCell.erase(coords);
        int position = coords.I * mapSize+ coords.J;
        \
            if(*prevMap[position] == CONWAYCELL && *gameMap[position] == CONWAYCELL)
        {
            for(int x = (coords.I != 0) ? -1 : 0;x <=  (coords.I < mapSize) ? 1 : 0; x++)
            {
                for(int y = (coords.J != 0) ? -1 : 0; y <= (coords.J < mapSize) ? 1 : 0; y++)
                {
                    if(isAlive(coords.I + x,coords.J + y)) //если живая
                    {
                        gameMap[position + x* mapSize + y]->setStatus(true);
                        if(!coordsWithAliveCell.contains(Coordinate(coords.I + x, coords.J + y)))
                            coordsWithAliveCell.pushBack(Coordinate(coords.I + x, coords.J + y));
                    }
                    else
                    {
                        if(!(*gameMap[position + x* mapSize + y] == CONSTANT) && !(*gameMap[position + x* mapSize + y]  == NUKE))
                        {
                            gameMap[position + x* mapSize +y] = new ConwayCell();
                        }
                    }

                }
            }

        }
        else if(*prevMap[position] == ENEMY){ // cell == enemy
            for(int x = (coords.I != 0) ? -1 : 0;x <=  (coords.I< mapSize) ? 1 : 0; x++)
            {
                for(int y = (coords.J != 0) ? -1 : 0; y <= (coords.J < mapSize) ? 1 : 0; y++)
                {
                    if(isAliveEnemy(coords.I + x,coords.J + y)  && (*prevMap[position] == CONWAYCELL || *prevMap[position] ==ENEMY)  ) //если живая
                    {
                        delete gameMap[position + x* mapSize + y];
                        gameMap[position + x* mapSize + y] = new EnemyCell();
                        gameMap[position + x* mapSize + y]->setStatus(true);
                        if(!coordsWithAliveCell.contains(Coordinate(coords.I + x, coords.J + y)))
                            coordsWithAliveCell.pushBack(Coordinate(coords.I + x, coords.J + y));
                    }
                    else
                    {
                        if(!(*prevMap[position + x* mapSize + y] == CONSTANT))
                        {

                            gameMap[position + x* mapSize +y] = new ConwayCell();
                        }
                    }

                }
            }
        }
        else  if(*prevMap[position] == NUKE)
        {
            nukeExpand(coords.I,coords.J);
        }
        else if(*prevMap[position] == CONSTANT){
            gameMap[position] = new ConstantCell();
            coordsWithAliveCell.pushBack(Coordinate(coords.I, coords.J));
        }
        if((*gameMap[position]).getStatus() ==  (*prevMap[position]).getStatus() &&(*gameMap[position]).getSymbol() == (*gameMap[position]).getSymbol() )
            notChanged++;
    }
    for(int i =0; i < coordsWithAliveCellTemp.size(); i++){  // обнулить карту предыдущую
        Coordinate coords = coordsWithAliveCellTemp[i];
        prevMap[coords.I * mapSize + coords.J] = new ConwayCell();
    }

    if(coordsWithAliveCell.size()== coordsWithAliveCellTemp.size() && notChanged == coordsWithAliveCellTemp.size()) {
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
        stopGame();
        return;
    }

    update();
}

bool GameConway::isAlive(int k, int j)
{
    int power = 0;
    for(int y = -1 ; y <= 1; y++)
    {
        for(int x = -1;  x <=  1 ; x++)
        {
            if(!(x == 0 && y == 0))
            {
                if(prevMap[(k + y)* mapSize + (j +x)]->getStatus() == true && *prevMap[(k + y)* mapSize + (j +x)] ==CONWAYCELL)
                {
                    power++;
                }
            }
        }
    }
    if ((prevMap[k* mapSize + j]->getStatus()  && (power == 2)) || (power == 3))
        return true;
    return false;
}

bool GameConway::isAliveEnemy(int k, int j)
{
    int powerEnemy = 0;
    int powerConway = 0;
    for(int y =(k != 0) ? -1 : 0 ; y  <= (k != mapSize - 1) ? 1 : 0; y ++)
    {
        for(int x = (j != 0) ? -1: 0; x <=  (j != mapSize -1) ? 1 : 0; x++)
        {
            if(!(x == 0 && y  == 0))
            {
                if(prevMap[(k + y )* mapSize + (j +x)]->getStatus() == true && (*prevMap[(k + y )* mapSize + (j +x)] == ENEMY))
                {
                    powerEnemy++;
                }
                if(*prevMap[(k + y )* mapSize + (j +x)] == CONWAYCELL && prevMap[(k + y )* mapSize + (j +x)]->getStatus())
                {
                    powerConway++;
                }
            }
        }
    }
    if(((prevMap[k* mapSize + j]->getStatus() && (powerEnemy == 2)) || (powerEnemy == 3))  || (*prevMap[k* mapSize + j] == CONWAYCELL  && ((powerConway == 2) || (powerConway == 1))))
    {
        return true;
    }
    return false;
}

void GameConway::nukeExpand(int startI, int startJ)
{
    int tempRange = (NukeCell(*((NukeCell*)(gameMap[startI * mapSize + startJ])))).getCurrentRange();
    tempRange++;
    int maxRange =  (NukeCell(*((NukeCell*)(gameMap[startI * mapSize + startJ])))).getMaxRange();

    if(tempRange  > maxRange){
        int sizeOfMaxNuke = tempRange * 2 - 1;
        for(int k = 0; k < sizeOfMaxNuke ; k++)
            for(int j = 0; j < sizeOfMaxNuke; j++)
            {
                int position = (startI +  k)* mapSize + startJ + j;
                gameMap[position] = new ConwayCell();
                prevMap[position] = new ConwayCell();
                if(coordsWithAliveCell.contains(Coordinate(startI +  k,startJ + j)))
                    coordsWithAliveCell.erase(Coordinate(startI +  k,startJ + j));
            }
        return;
    }
    for(int k = (startI != 0) ? -1 : 0; k <=  (startI < mapSize) ? 1 : 0; k++)
    {
        for(int j = (startJ != 0) ? -1 : 0; j <=  (startJ < mapSize)? 1 : 0; j++)
        {
            int position = (startI  + k) * mapSize + startJ  + j;
            if ( (!(*gameMap[position] == NUKE && !gameMap[position]->getStatus()) && !(*prevMap[position] == NUKE))) {
                gameMap[position] =new NukeCell();
                gameMap[position]->setStatus(true);

                ((NukeCell*)(gameMap[position]))->setCurrentRange(tempRange);
                if(!coordsWithAliveCell.contains(Coordinate((startI  + k)  , startJ  + j)))
                    coordsWithAliveCell.pushBack(Coordinate((startI  + k)  , startJ  + j));
            } else {
                gameMap[position]->setStatus(false);
            }
        }
    }
}
