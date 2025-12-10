#include "playscene.h"
#include "chooselevelscene.h"
#include "dataconfig.h"
#include "mycoin.h"
#include "mypushbutton.h"
#include <QDebug>
#include <QFont>
#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QFile>
#include <QUrl>              
#include <QPropertyAnimation>
#include <QSoundEffect>

// helper: 将多种路径样式归一化为 QUrl（优先本地文件，其次 qrc 资源）
static QUrl normalizeResourcePath(const QString &p) {
    if (p.startsWith(QStringLiteral("qrc:/"))) return QUrl(p);
    if (p.startsWith(QStringLiteral(":/"))) {
        // ":/prefix/..." -> "qrc:/prefix/..."
        return QUrl(QStringLiteral("qrc:") + p);
    }
    // 如果传入的是本地文件路径并存在，则返回本地文件 URL
    if (QFile::exists(p)) return QUrl::fromLocalFile(p);
    // 否则作为 qrc 相对路径尝试（保证以 qrc:/ 开头）
    if (p.startsWith(QStringLiteral("/"))) return QUrl(QStringLiteral("qrc:") + p);
    return QUrl(QStringLiteral("qrc:/") + p);
}

PlayScene::PlayScene(int levelNum) {
  QString str = QString("进入第%1关").arg(levelNum);
  this->levelIndex = levelNum;
  // 设置固定大小
  this->setFixedSize(420, 688);
  // 设置图标
  this->setWindowIcon(QPixmap(":/new/prefix1/image/6831b54a86efeuvI.gif"));
  setWindowTitle("关卡");
  // 创建菜单栏
  QMenuBar *bar = menuBar();
  setMenuBar(bar);
  // 创建开始菜单
  QMenu *startMenu = bar->addMenu("开始");
  // 创建退出菜单项
  QAction *quitAction = startMenu->addAction("退出");
  // 点击退出实现退出游戏
  connect(quitAction, &QAction::triggered, [=]() { this->close(); });
  QSoundEffect *bgm3 = new QSoundEffect(this);
  bgm3->setSource(normalizeResourcePath("qrc/new/prefix2/image/【赛马娘】欧耶_爱给网_aigei_com.wav"));
  bgm3->setLoopCount(114514); 
  bgm3->setVolume(0.5f);
  bgm3->play();
  QSoundEffect *bgm4 = new QSoundEffect(this);
  bgm4->setSource(normalizeResourcePath("qrc/new/prefix2/image/曼波哥我求你了不要再针对我了_爱给网_aigei_com.wav"));
  bgm4->setLoopCount(114514); 
  bgm4->setVolume(0.5f);
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
    QTimer::singleShot(500, this, [=]() { emit this->chooseSceneBack(); });
  });
  // 显示当前关卡数
  QLabel *label = new QLabel;
  label->setParent(this);
  QFont font;
  font.setFamily("华文新魏");
  font.setPointSize(20);
  QString str1 = QString("Level:%1").arg(this->levelIndex);
  label->setFont(font);
  label->setText(str1);
  label->setGeometry(30, this->height() - 50, 120, 50);
  // 初始化每个关卡二维数组
  dataConfig config;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
    }
  }
//胜利图片显示
QLabel *winLabel = new QLabel;
QPixmap tmpPix;
tmpPix.load(":/new/prefix1/image/0335EB749F0B3DCA1EBE0CD6B670FD63.gif");
winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
winLabel->setPixmap(tmpPix);
winLabel->setParent(this);
winLabel->move( (this->width() - tmpPix.width())*0.5, - tmpPix.height());
  // 显示背景图案
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // 绘制背景图
      QPixmap pix = QPixmap(":/new/prefix1/image/6342280b_E835615_ddbb3f2d.png");
      QLabel *bgLabel = new QLabel;
      bgLabel->setGeometry(0, 0, pix.width() * 0.05, pix.height() * 0.05);
      bgLabel->setPixmap(pix);
      bgLabel->setParent(this);
      bgLabel->move(15 + i * 96, 140 + j * 96);
      // 创建金币
      QString imgPath;
      if (this->gameArray[i][j] == 1) {
        imgPath = ":/new/prefix1/image/387EE9C9CDE1E5F5E582204F37B7A777.gif";
      } else {
        imgPath = ":/new/prefix1/image/1D6FFFF59DE1D5B8BD23B7C1BCAE6FF3.gif";
      }
      MyCoin *coin = new MyCoin(imgPath);
      coin->setParent(this);
      coin->move(15 + i * 96, 140 + j * 96);
      // 给金币属性赋值
      coin->posX = i;
      coin->posY = j;
      coin->flag = this->gameArray[i][j]; // 1正面0反面
      coinBtn[i][j] = coin;
      // 点击金币
      connect(coin, &MyCoin::clicked, [=]() {
        int x = i;
        int y = j;
        // 立即翻转自身
        coin->changeFlag();
        this->gameArray[x][y] = this->gameArray[x][y] == 0 ? 1 : 0;
        // 延迟翻转周围金币（上、下、左、右）
        QTimer::singleShot(300, this, [=]() {
          // 上
          if (x - 1 >= 0 && coinBtn[x - 1][y]) {
            coinBtn[x - 1][y]->changeFlag();
            this->gameArray[x - 1][y] = this->gameArray[x - 1][y] == 0 ? 1 : 0;
          }
          // 下
          if (x + 1 <= 3 && coinBtn[x + 1][y]) {
            coinBtn[x + 1][y]->changeFlag();
            this->gameArray[x + 1][y] = this->gameArray[x + 1][y] == 0 ? 1 : 0;
          }
          // 左
          if (y - 1 >= 0 && coinBtn[x][y - 1]) {
            coinBtn[x][y - 1]->changeFlag();
            this->gameArray[x][y - 1] = this->gameArray[x][y - 1] == 0 ? 1 : 0;
          }
          // 右
          if (y + 1 <= 3 && coinBtn[x][y + 1]) {
            coinBtn[x][y + 1]->changeFlag();
            this->gameArray[x][y + 1] = this->gameArray[x][y + 1] == 0 ? 1 : 0;
          }

          // 判断是否胜利
          this-> isWin = true;
          for (int i = 0; i < 4 ;i++) {
            for (int j = 0; j < 4; ++j) {
              if (coinBtn[i][j]->flag == false) {
                this->isWin = false;
                break;
              }
            }
          }
          if (this->isWin==true) {
            qDebug() << "游戏通关！啊米诺斯！";
            
            bgm4->play();
            //所有按钮改为true
            for (int i = 0; i <4 ; ++i) {
              for (int j = 0; j <4 ; ++j) {
                coinBtn[i][j]->isWin=true;
              }
            }
            //天降耄耋
            QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
            animation->setDuration(1000);
            animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
            animation->setEndValue(QRect(winLabel->x(),winLabel->y()+190,winLabel->width(),winLabel->height()));
            animation->start();
          }

          });
      });

    }
  ;}
}

void PlayScene::paintEvent(QPaintEvent *) {
  // 创建背景
  QPainter painter(this);
  QPixmap pix;
  pix.load(":/new/prefix1/image/6825fc13369e9GO7.jpg");
  painter.drawPixmap(0, 0, this->width(), this->height(), pix);
  pix.load(":/new/prefix1/image/1D6FFFF59DE1D5B8BD23B7C1BCAE6FF3.gif");
  pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
  painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}