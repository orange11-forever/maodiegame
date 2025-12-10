#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include"mycoin.h"
#include <QMainWindow>

class PlayScene : public QMainWindow {
  Q_OBJECT
public:
  PlayScene(int levelNum);
  int levelIndex; // 记录所选关卡
  // 重写PaintEvent事件
  void paintEvent(QPaintEvent *);
  int gameArray[4][4]; // 二维数组维护关卡数据
  MyCoin*coinBtn[4][4];
  bool isWin;
signals:
  void chooseSceneBack();
};

#endif // PLAYSCENE_H
