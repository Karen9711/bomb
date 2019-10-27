#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QObject>
#include<QLabel>
#include<QPushButton>
#include<QPixmap>
#include <QMenuBar>
#include<QMessageBox>
#include"map.h"
class playScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit playScene(QWidget *parent = nullptr);
    playScene(int m_level);
    void createMap();//生成地图
    void flip();//翻动格子 -- 包括周围的格子
//    bool isSucceeded();//判断是否胜利
//    void mousePressEvent(QMouseEvent *e);//重写鼠标事件 -- 右键标识红旗
private:
    int level;//用于接受游戏难度设置
    Map *map;
    vector<vector<int>> vMap;//用于维护地图 -- 根据难度再构造函数中进行初始化
signals:
    void showMain();
public slots:
};

#endif // PLAYSCENE_H
