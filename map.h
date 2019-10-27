#ifndef MAP_H
#define MAP_H

#include <QObject>
#pragma once
#include<iostream>
#include<string>

#include<vector>

using namespace std;
//每个难度的雷数量
#define EASY 10
#define NORMAL 40
#define HARD 99

//每个难度的行数和列数
#define EASY_ROW 9
#define EASY_COLUMN 9

#define NORMAL_ROW 16
#define NORMAL_COLUMN 16

#define HARD_ROW 30
#define HARD_COLUMN 16

class Map: public QObject
{
    Q_OBJECT
private:
    int **map;
    int row;
    int column;
    int bombNum;
public:
    Map();//数值初始化
    Map(int row,int column);
    Map(int row, int column, int bombCount);
    Map(int level);
    ~Map();
    void initMap();//初始化地图
    void showMap();
    void playGame();
    void setMap(vector<vector<int>> &v);
private:
    void setBomb();//放置地雷
    void countBomb();//对地图进行处理，清算雷每个格子周围雷的数量
};


#endif // MAP_H
