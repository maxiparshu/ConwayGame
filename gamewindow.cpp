#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::~GameWindow()
{
    delete ui;
}

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , game(new GameConway(this))
    , gameIsPlay(false)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->GameLayout->addWidget(game);
}
\

 void GameWindow::selectMasterColor(){
    QColor color = QColorDialog::getColor(game->getBorderColor(), this, tr("Select color of figures"));
    if(!color.isValid())
        return;
    game->setBorderColor(color);
}
void GameWindow::saveGame()
{
    game->stopGame();
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save current game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game *.life Files (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QString buf = QString::number(game->getMapSize()) + "\n";
    file.write(buf.toUtf8());
    buf.clear();
    buf = QString::number(game->getFieldSize()) + "\n";
    file.write(buf.toUtf8());
    buf.clear();
    buf = QString::number(game->getXOffset()) + "\n";
    file.write(buf.toUtf8());
    buf.clear();
    buf = QString::number(game->getYOffset()) + "\n";
    file.write(buf.toUtf8());
    buf.clear();

    file.write(game->dump().toUtf8());

    buf = QString::number(game->interval())+"\n";
    file.write(buf.toUtf8());
    buf.clear();
    QColor color = game->getBorderColor();
    buf = QString::number(color.red())+" "+
          QString::number(color.green())+" "+
          QString::number(color.blue())+"\n";
    file.write(buf.toUtf8());


    file.close();
}
void GameWindow::loadGame()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open saved game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game Of Life File (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);
    int readenValue;
    in >> readenValue;
    game->setMapSize(readenValue);

    in >> readenValue;
    game->setFieldSize(readenValue);

    in >> readenValue;
    game->setXOffset(readenValue);

    in >> readenValue;
    game->setYOffset(readenValue);

    QString dump="";
    for(int k=0; k < game->getMapSize(); k++) {
        QString temp;
        in >> temp;
        dump.append(temp+"\n");
    }
    game->setDump(dump);

    in >> readenValue;
    game->setInterval(readenValue);

    int r,g,b; // RGB color
    in >> r >> g >> b;
    game->setBorderColor(QColor(r,g,b));
    game->stopGame();
}
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_E)
    {
        if(game->getFigureDrawStatus())
        {
            this->game->setSpinAmount(game->getSpinAmount() + 1);
        }
    }
    if(key == Qt::Key_Space)
    {
        if(!gameIsPlay){
            game->startGame();
        }
        else
        {
            game->stopGame();
        }
        gameIsPlay =  !gameIsPlay;
    }
    if(key == Qt::Key_R)
    {
        game->clear();
        game->stopGame();
    }

    if(key == Qt::Key_C)
    {
        selectMasterColor();

    }
    if(key ==Qt::Key_8 || key == Qt::Key_W)
    {
        game->windowShift(Direction::UP);
    }
    if(key == Qt::Key_2 || key == Qt::Key_S)
    {
        game->windowShift(Direction::DOWN);
    }
    if(key == Qt::Key_6 || key == Qt::Key_D)
    {
        game->windowShift(Direction::RIGHT);
    }
    if(key == Qt::Key_4|| key == Qt::Key_A)
    {

        game->windowShift(Direction::LEFT);
    }
    if(key == Qt::Key_H)
    {
        QMessageBox howToPlay;
        howToPlay.setText("Conway game of life\n"
                          "Press 'Space' to start/stop game\n"
                          "Press 'R' to restart game\n"
                          "WASD to move screen\n"
                          "+ - to change scale of screen\n"
                          "Press 'C' to change color\n");
        howToPlay.exec();
    }
    if(key == Qt::Key_Minus)
    {
        game->incWindowScale();
    }
    if(key == Qt::Key_Plus)
    {
        game->decWindowScale();
    }
}

void GameWindow::on_actionLoad_triggered()
{
    loadGame();
}


void GameWindow::on_actionSave_triggered()
{
    saveGame();
}


void GameWindow::on_actionEnemy_triggered()
{
    game->changeCell();
    game->addCellTemplate(ENEMY);
}


void GameWindow::on_actionConstant_triggered()
{
    game->changeCell();
    game->addCellTemplate(CONSTANT);
}


void GameWindow::on_actionNuke_triggered()
{
    game->changeCell();
    game->addCellTemplate(NUKE);
}


void GameWindow::on_actionBlock_triggered()
{
    game->setDrawFigure();
    game->addTemplate(BLOCK);
}


void GameWindow::on_actionBee_Hive_triggered()
{
    game->setDrawFigure();
    game->addTemplate(BEEHIVE);
}


void GameWindow::on_actionBoat_triggered()
{
    game->setDrawFigure();
    game->addTemplate(BOAT);
}


void GameWindow::on_actionEater_triggered()
{
    game->setDrawFigure();
    game->addTemplate(EATER);
}


void GameWindow::on_actionLoaf_triggered()
{
    game->setDrawFigure();
    game->addTemplate(LOAF);
}


void GameWindow::on_actionTub_triggered()
{
    game->setDrawFigure();
    game->addTemplate(TUB);
}


void GameWindow::on_actionBeacon_triggered()
{
    game->setDrawFigure();
    game->addTemplate(BEACON);
}


void GameWindow::on_actionBlinker_triggered()
{
    game->setDrawFigure();
    game->addTemplate(BLINKER);
}


void GameWindow::on_actionToad_triggered()
{
    game->setDrawFigure();
    game->addTemplate(TOAD);
}


void GameWindow::on_actionPulsar_triggered()
{
    game->setDrawFigure();
    game->addTemplate(PULSAR);
}


void GameWindow::on_actionGlider_triggered()
{
    game->setDrawFigure();
    game->addTemplate(GLIDER);
}


void GameWindow::on_actionLight_triggered()
{
    game->setDrawFigure();
    game->addTemplate(LIGHTSHIP);
}


void GameWindow::on_actionMiddle_triggered()
{
    game->setDrawFigure();
    game->addTemplate(MIDDLESHIP);
}


void GameWindow::on_actionHeavy_triggered()
{
    game->setDrawFigure();
    game->addTemplate(HEAVYSHIP);
}


void GameWindow::on_actionGosper_gun_triggered()
{
    game->setDrawFigure();
    game->addTemplate(GOSPER);
}


void GameWindow::on_actionSimkiin_gun_triggered()
{
    game->setDrawFigure();
    game->addTemplate(SIMKIN);
}


void GameWindow::on_actionLight_train_triggered()
{
    game->setDrawFigure();
    game->addTemplate(LIGHTPUFFERTRAIN);
}


void GameWindow::on_actionGalaxy_triggered()
{
    game->setDrawFigure();
    game->addTemplate(GALAXY);
}

