#include "dataconfig.h"
#include <QDebug>
#include<QVector>
#include <cstdlib>
#include <ctime>

dataConfig::dataConfig(QObject *parent) : QObject(parent) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int arry1[4][4] = {{1, 1, 1, 1}, {1, 1, 0, 1}, {1, 0, 0, 0}, {1, 1, 0, 1}};
    QVector<QVector<int>> v;
    for (int i = 0; i < 4; i++) {

        QVector<int> v1;
        for (int j = 0; j < 4; j++) {
            v1.push_back(arry1[i][j]);
        }
        v.push_back(v1);
    }
    mData.insert(1, v);

    //第二关

    int array2[4][4] = { {0, 1, 0, 1},
                         {1, 0, 0, 0},
                         {1, 0, 0, 0},
                         {0, 1, 0, 1}} ;

    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array2[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(2,v);


    int array3[4][4] = {  {1, 0, 1, 1},
                          {1, 1, 0, 0},
                          {0, 0, 1, 1},
                          {1, 1, 0, 1}} ;
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array3[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(3,v);


    int array4[4][4] = {   {0, 1, 1, 1},
                           {1, 1, 0, 1},
                           {1, 0, 1, 1},
                           {1, 1, 1, 0}} ;
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array4[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(4,v);


    int array5[4][4] = {  {1, 0, 0, 1},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0},
                          {1, 0, 0, 1}} ;
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array5[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(5,v);


    int array6[4][4] = {   {1, 0, 0, 1},
                           {0, 1, 1, 0},
                           {0, 1, 1, 0},
                           {1, 0, 0, 1}} ;
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array6[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(6,v);


    int array7[4][4] = {   {0, 1, 1, 0},
                           {0, 0, 0, 0},
                           {0, 0, 0, 0},
                           {0, 1, 1, 0}} ;
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array7[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(7,v);

    int array8[4][4] = {      {0, 1, 1, 0},
                              {1, 1, 1, 1},
                              {1, 1, 1, 1},
                              {0, 1, 1, 0}} ;
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array8[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(8,v);


    int array9[4][4] = {      {0, 0, 0, 0},
                              {0, 0, 0, 0},
                              {0, 0, 0, 0},
                              {0, 0, 0, 0} };
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array9[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(9,v);
    //===============10随机关==================//
    v.clear();

    int num=0;
    int sum=0;
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            num = std::rand() % 2;
            v1.push_back(num);
            if(num==1){
                sum++;
            }
        }
        v.push_back(v1);
    }

    //还需要设置成偶数个，奇数个不行，可以利用vector的性质来做
    // 需要保证 1 的个数为偶数：如果为奇数，则翻转第一个元素（安全索引）
    if ((sum & 1) != 0) {
        v[0][0] = 1 - v[0][0];
    }
    mData.insert(10,v);
    int array11[4][4] = {  {0, 0, 0, 0, },
                           {0, 1, 0, 1, },
                           {0, 0, 1, 0, },
                           {0, 1, 0, 1, },
                     };
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array11[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(11,v);

    int array12[4][4] = {  {0, 0, 0, 1, },
                           {1, 0, 1, 1, },
                           {1, 0, 1, 1, },
                           {1, 0, 1, 1, },
                           };
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array12[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(12,v);


    int array13[4][4] = {  {1, 1, 1, 0, },
                           {0, 1, 0, 0, },
                           {0, 1, 1, 1, },
                           {0, 1, 0, 0, },
                           };
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array13[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(13,v);

    int array14[4][4] = {  {1, 1, 1, 1, },
                           {1, 0, 0, 0, },
                           {1, 0, 0, 0, },
                           {1, 0, 1, 1, },
                           };
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array14[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(14,v);


    //===============15随机关==================//
    v.clear();

    int num1=0;
    int sum1=0;
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            num1 = std::rand() % 2;
            v1.push_back(num1);
            if(num1==1){
                sum1++;
            }
        }
        v.push_back(v1);
    }

    // 需要保证 1 的个数为偶数：如果为奇数，则翻转第一个元素（安全索引）
    if ((sum1 & 1) != 0) {
        v[0][0] = 1 - v[0][0];
    }
    mData.insert(15,v);
    int array16[4][4] = { {0, 0, 0, 0},
                          {0, 1, 1, 1 },
                          {0, 1, 1, 1 },
                          {0, 1, 1, 1 },
                           };
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array16[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(16,v);

    int array17[4][4] = {  {1, 1, 0, 0},
                           {1, 1, 0, 0},
                           {1, 1, 0, 0 },
                           {1, 1, 0, 0},
                            };
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array17[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(17,v);


    int array18[4][4] = {  {0, 0, 0, 0},
                           {0, 0, 1, 0},
                           {0, 1, 1, 0},
                           {1, 0, 0, 1},
                            };
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array18[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(18,v);

    int array19[4][4] = {  {0, 0, 0, 0 },
                           {1, 0, 0, 0 },
                           {0, 0, 0, 0 },
                           {0, 0, 0, 0},
                           };
              
    v.clear();
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            v1.push_back(array19[i][j]);
        }
        v.push_back(v1);
    }

    mData.insert(19,v);

    //===============20随机关==================//
    v.clear();

    int num2=0;
    int sum2=0;
    for(int i = 0 ; i < 4;i++)
    {
        QVector<int>v1;
        for(int j = 0 ; j < 4;j++)
        {
            num2 = std::rand() % 2;
             v1.push_back(num2);
             if(num2==1){
                 sum2++;
             }
        }
        v.push_back(v1);
    }

    //还需要设置成偶数个，奇数个不行，可以利用vector的性质来做
    // 需要保证 1 的个数为偶数：如果为奇数，则翻转第一个元素（安全索引）
    if ((sum2 & 1) != 0) {
        v[0][0] = 1 - v[0][0];
    }
    mData.insert(20,v);}