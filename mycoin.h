#ifndef MYCOIN_H
#define MYCOIN_H

#include <QMouseEvent>
#include <QObject>
#include <QPushButton>
#include <QTimer>


class MyCoin : public QPushButton {
  Q_OBJECT
public:
  // explicit MyCoin(QWidget *parent = nullptr);
  // 参数代表图片路径
  MyCoin(const QString &btnImg);
  virtual ~MyCoin() = default;

  // 金币属性
  int posX;  // x坐标位置
  int posY;  // y坐标位置
  bool flag; // 标志正反面

  // 改变标志的方法
  void changeFlag();

  QTimer *timer1; // 正面翻反面
  QTimer *timer2; // 反面翻正面
  int min = 1;
  int max = 8;
  bool isAnimation = false;


  // 正确的函数名：mousePressEvent (大写P)
void mousePressEvent(QMouseEvent *e) override;
bool isWin=false;
signals:
};

#endif // MYCOIN_H
