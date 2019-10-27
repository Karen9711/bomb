#include "map.h"
#include<iostream>
#include<string>
#include<time.h>

using namespace std;
//9*9 -- 10  低难度
//16*16 -- 40  中级难度
// 16*30 -- 99  高难度
// 自定义难度 -- row column bombNum
Map::Map()
{
    //默认为简单模式
    //动态分配内存
    this->row = EASY_ROW;
    this->column = EASY_COLUMN;
    this->bombNum = EASY;
    map = new int*[row];
    if (map == NULL) {
        cout << "初始化失败" << endl;
        return;
    }
    for (int i = 0; i < row; i++)
    {
        map[i] = new int[column]{0};//数值初始化
        if (map[i] == NULL)
        {
            cout << "初始化失败" << endl;
            return;
        }
    }
}

Map::Map(int level_row,int level_column)//1 = easy 2 = normal 3 = hard
{
    //初始化数据
    this->row = level_row;
    this->column = level_column;
    switch (level_row) {
    case EASY_ROW:this->bombNum = EASY; break;
    case NORMAL_ROW:this->bombNum = NORMAL; break;
    case HARD_ROW:this->bombNum = HARD; break;
    }
    //动态分配内存
    map = new int*[row];
    if (map == NULL)
    {
        cout << "初始化失败" << endl;
        return;
    }
    for (int i = 0; i < row; i++)
    {
        map[i] = new int[column]{ 0 };//数值初始化
        if (map[i] == NULL)
        {
            cout << "初始化失败" << endl;
            return;
        }
    }
}

Map::Map(int level)//1 = easy 2 = normal 3 = hard
{
    //初始化数据
    switch(level)
    {
    case 0:
        this->row = EASY_ROW;
        this->column = EASY_COLUMN;
        bombNum = EASY;
        break;
    case 1:
        this->row = NORMAL_ROW;
        this->column = NORMAL_COLUMN;
        bombNum = NORMAL;
        break;
    case 2:
        this->row = HARD_ROW;
        this->column = HARD_COLUMN;
        bombNum = HARD;
        break;
    }

    //动态分配内存
    map = new int*[row];
    if (map == NULL)
    {
        cout << "初始化失败" << endl;
        return;
    }
    for (int i = 0; i < row; i++)
    {
        map[i] = new int[column]{ 0 };//数值初始化
        if (map[i] == NULL)
        {
            cout << "初始化失败" << endl;
            return;
        }
    }
}

Map::Map(int row, int column, int bombCount)
{
    this->row = row;
    this->column = column;
    this->bombNum = bombCount;
    if (bombNum >= row * column) {
        cout << "初始化失败" << endl;
    }
    map = new int*[row];
    if (map == NULL) {
        cout << "初始化失败" << endl;
        return;
    }
    for (int i = 0; i < row; i++)
    {
        map[i] = new int[column] {0};
        if (map[i] == NULL) {
            return;
        }
    }
}

Map::~Map()//析构函数释放内存
{
    for (int i = 0; i < row; i++)
    {
        if (map[i] != NULL) {
            delete[] map[i];
        }
    }
    if (map != NULL) {
        delete[] map;
    }

}

void Map::showMap()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++) {
            cout.width(2);
            cout << map[i][j] << "  ";
        }
        cout << endl;
    }
}

void Map::setBomb()
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < bombNum; i++)
    {
        //产生地雷的位置 -- 需要将一维转换为二维
        int bombPos = rand() % (row * column);
        int x = bombPos / column;
        int y = bombPos - x * column;
        map[x][y] = -1;
    }
}

void Map::countBomb()
{
    int up, left, right, bottom;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (map[i][j] == -1) {
                up = i - 1 >= 0 ? i - 1 : i;
                bottom = i + 1 >= row ? i : i+1;
                left = j - 1 >= 0 ? j - 1 : j;
                right = j + 1 >= column  ? j  : j+1;
                for (int x = up; x <= bottom; x++)
                {
                    for (int y = left; y <= right; y++) {
                        if (map[x][y] == -1)
                        {
                            continue;
                        }
                        map[x][y]++;
                    }
                }
            }
        }
    }
}

void Map::initMap()
{
    setBomb();
    countBomb();
}
void Map::setMap(vector<vector<int> > &v)
{

    //先假设都是9*9
    for(int i=0;i<9;i++)
    {
        vector<int> temp;
        for(int j =0;j<9;j++)
        {
            temp.push_back(map[i][j]);
        }
        v.push_back(temp);
    }
}
void Map::playGame()
{
    int x, y;
    cout << "请输入坐标" << endl;
    cin >> x >> y;
    if (map[x][y] == -1) {
        cout << "你输了" << endl;
    }
}
