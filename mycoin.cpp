#include "mycoin.h"
#include <QDebug>
#include <QPixmap>

MyCoin::MyCoin(const QString &btnImg) : QPushButton(nullptr) {

  QPixmap pix;
  bool ret = pix.load(btnImg);
  if (!ret) {

    qDebug() << "图片加载失败";
  }
  this->setFixedSize(pix.width() * 0.5, pix.height() * 0.5);
  this->setStyleSheet("QPushButton{border:0px;}");
  this->setIcon(pix);
  this->setIconSize(QSize(pix.width() * 0.5, pix.height() * 0.5));

  timer1 = new QTimer(this);
  timer2 = new QTimer(this);

  // 监听正面翻反面信号
  connect(timer1, &QTimer::timeout, [=]() {
    QPixmap pix;
    QString str =
        QString(":/new/prefix1/image/1D6FFFF59DE1D5B8BD23B7C1BCAE6FF3.gif")
            .arg(this->min++);
    pix.load(str);
    this->setFixedSize(pix.width() * 0.5, pix.height() * 0.5);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width() * 0.5, pix.height() * 0.5));

    // 翻完了重置min
    if (this->min > this->max) {
      this->min = 1;
      isAnimation = false;
      timer1->stop();
    }
  });

  // 监听反面翻正面信号 
  connect(timer2, &QTimer::timeout, [=]() {
    QPixmap pix;
    QString str1 =
        QString(":/new/prefix1/image/387EE9C9CDE1E5F5E582204F37B7A777.gif")
            .arg(this->max--);
    pix.load(str1);
    this->setFixedSize(pix.width() * 0.5, pix.height() * 0.5);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width() * 0.5, pix.height() * 0.5));

    // 翻完了重置max 
    if (this->max < this->min) {
      this->max = 8;
      isAnimation = false;
      timer2->stop();
    }
  });
}

void MyCoin::mousePressEvent(QMouseEvent *e) {
  if (this->isAnimation||this->isWin) {
    return;
  }
  else{
      QPushButton::mousePressEvent(e);}

}

// 改变正反面标志
void MyCoin::changeFlag() {
  // 如果是正面翻成反面
  if (this->flag) {
    timer1->start(30);
    isAnimation = true;
    this->flag = false;
  } else {
    // 反面翻正面
    timer2->start(30);
    isAnimation = true;
    this->flag = true;
  }
}
