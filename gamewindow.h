#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextStream>
#include <QFileDialog>
#include <QColorDialog>

#include <gameConway.h>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
public slots:
    void selectMasterColor();
    void saveGame();
    void loadGame();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_actionEnemy_triggered();

    void on_actionConstant_triggered();

    void on_actionNuke_triggered();

    void on_actionBlock_triggered();

    void on_actionBee_Hive_triggered();

    void on_actionBoat_triggered();

    void on_actionEater_triggered();

    void on_actionLoaf_triggered();

    void on_actionTub_triggered();

    void on_actionBeacon_triggered();

    void on_actionBlinker_triggered();

    void on_actionToad_triggered();

    void on_actionPulsar_triggered();

    void on_actionGlider_triggered();

    void on_actionLight_triggered();

    void on_actionMiddle_triggered();

    void on_actionHeavy_triggered();

    void on_actionGosper_gun_triggered();

    void on_actionSimkiin_gun_triggered();

    void on_actionLight_train_triggered();

    void on_actionGalaxy_triggered();

private:
    bool gameIsPlay;
    GameConway* game;
    Ui::GameWindow *ui;
};

