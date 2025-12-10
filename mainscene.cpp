#include "mainscene.h"
#include "./ui_mainscene.h"
#include "mypushbutton.h"
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QSoundEffect>
#include <QUrl>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainScene) {
  ui->setupUi(this);
  // 配置场景
  // 设置固定大小
  setFixedSize(420, 688);
  // 设置图标
  setWindowIcon(
      QIcon(":/new/prefix1/image/0F92BCD49C0CEFE2D4EEEDF11396BECE.jpg"));
  // 设置标题
  setWindowTitle("翻耄耋");
  // 退出
  connect(ui->actionquit, &QAction::triggered, [=]() { this->close(); });
  QSoundEffect *bgm = new QSoundEffect(this);
  bgm->setSource(QUrl(QStringLiteral("qrc:/new/prefix2/image/曼波三倍曼波_爱给网_aigei_com.wav")));
  bgm->setLoopCount(QSoundEffect::Infinite);
  bgm->setVolume(0.5f);
  bgm->play();
  // 开始按钮
  MyPushButton *startbtn = new MyPushButton(
      ":/new/prefix1/image/9d3bd59e928d905f3fd37ae0e3dd760c.jpg");

  startbtn->setParent(this);
  startbtn->move(this->width() * 0.5 - startbtn->width() * 0.5,
                 this->height() * 0.7);
  chooseScene = new ChooseLevelScene;
  // 监听选择关卡的返回按钮信号（放在外面，避免每次点击重复连接）
  connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=]() {
   this->setGeometry(chooseScene->geometry());//设置场景位置
    chooseScene->hide(); // 显示关卡场景隐藏
    this->show();
  });

  connect(startbtn, &MyPushButton::clicked, [=]() {
    qDebug() << "点击开始按钮";
    // 弹起特效
    startbtn->zoom1();
    startbtn->zoom2();
    // 进入选择关卡场景
    // 延时进入
    QTimer::singleShot(500, this, [=]() {
     chooseScene->setGeometry(this->geometry());//设置场景位置
      // 自身隐藏
      this->hide();
      // 选择显示关卡场景
      chooseScene->show();
    });
  });
}
void MainScene::paintEvent(QPaintEvent *) {

  QPainter painter(this);
  QPixmap pix;
  pix.load(":/new/prefix1/image/OIP-C.jpg");
  painter.drawPixmap(0, 0, this->width(), this->height(), pix);
  // 画背景图标
  pix.load(":/new/prefix1/image/OIP-C (3).jpg");
  pix = pix.scaled(pix.width() * 0.2, pix.height() * 0.2);
  painter.drawPixmap(0, 0, pix);
}
MainScene::~MainScene() { delete ui; }
