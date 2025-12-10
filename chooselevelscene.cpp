#include "chooselevelscene.h"
#include "mypushbutton.h"
#include <QDebug>
#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QSoundEffect>
#include <QUrl>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow{parent} {
  // 配置选择关卡场景
  this->setFixedSize(420, 688);
  // 设置图标
  this->setWindowIcon(QPixmap(":/new/prefix1/image/OIP-C (1).jpg"));
  // 设置标题
  this->setWindowTitle("选择关卡");
  // 创建菜单栏
  QMenuBar *bar = menuBar();
  setMenuBar(bar);
  // 创建开始菜单
  QMenu *startMenu = bar->addMenu("开始");
  // 创建退出菜单项
  QAction *quitAction = startMenu->addAction("退出");
  // 点击退出实现退出游戏
  connect(quitAction, &QAction::triggered, [=]() { this->close(); });
  // BGM2
  QSoundEffect *bgm2 = new QSoundEffect(this);
  bgm2->setSource(QUrl(QStringLiteral("qrc:/new/prefix2/image/不再曼波_爱给网_aigei_com.wav")));
  bgm2->setLoopCount(QSoundEffect::Infinite);
  bgm2->setVolume(0.5f);
  bgm2->play();
  // 返回按钮
  MyPushButton *backbtn =
      new MyPushButton(":/new/prefix1/image/20230220174504_18139.gif",
                       ":/new/prefix1/image/OIP-C (3).jpg");
  backbtn->setParent(this);
  backbtn->move((this->width() - backbtn->width()) * 1.1,
                (this->height() - backbtn->height()) * 1.1);
  // 点击返回
  connect(backbtn, &MyPushButton::clicked, [=]() {
    qDebug() << "点击返回按钮";
    // 告诉主场景我返回了 主场景监听chooselevelscene返回按钮
    QTimer::singleShot(500, this, [=]() { emit this->chooseSceneBack(); });
  });
  // 创建选择关卡按钮
  for (int i = 0; i < 20; i++) {

    MyPushButton *menuBtn = new MyPushButton(
        ":/new/prefix1/image/F18CEFAD11A216604644DDC38D027B32.jpg");
    menuBtn->setParent(this);
    menuBtn->move(5 + i % 4 * 100, 25 + i / 4 * 100);
    // 监听每一个按钮点击（捕获当前索引与创建的 PlayScene 指针，避免捕获会变化的外部变量）
    int level = i + 1;
    connect(menuBtn, &MyPushButton::clicked, this, [this, level]() {
      qDebug() << QString("您选择第%1关").arg(level);
      this->hide();
      PlayScene *p = new PlayScene(level);
      this->play = p; // 若 play 为成员，记录当前场景指针
      p->show();
      p->setGeometry( this->geometry());
      connect(p, &PlayScene::chooseSceneBack, this, [this, p]() {
      p->setGeometry(this->geometry());
      // 只捕获 this 与 p，返回时安全删除 p
      this->show();
        p->deleteLater();
        this->play = nullptr;
      });
    });
    QLabel *label = new QLabel;
    label->setParent(this);
    label->setFixedSize(menuBtn->width(), menuBtn->height());
    label->setText(QString::number(i + 1));
    label->move(5 + i % 4 * 100, 25 + i / 4 * 100);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    // 让鼠标进行穿透
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
  };};
void ChooseLevelScene::paintEvent(QPaintEvent *e){
  // 加载背景
  QPainter painter(this);
  QPixmap pix;
  pix.load(":/new/prefix1/image/73417F82CCD03885D9E180A49C9E0D7C.jpg");
  painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}