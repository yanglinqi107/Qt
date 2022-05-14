#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <chooselevelscene.h>

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    //重写paintEvent事件 或背景图
    void paintEvent(QPaintEvent *);

private:
    Ui::MainScene *ui;
    ChooseLevelScene *chooseLevelScene = NULL;
};

#endif // MAINSCENE_H
