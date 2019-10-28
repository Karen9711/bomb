#include "playscene.h"

playScene::playScene(int m_level)
{
    QPixmap tmp;
    tmp.load(":/pics/0.png");
    this->setMinimumSize((m_level+1)*12*tmp.width(),18*tmp.height());
    //初始化Level
    this->level = m_level;
    //初始化Map;
    map = new Map(this->level);
    map->initMap();

    //初始化游戏维护的vMap;
    map->setMap(this->vMap);


    //设置菜单栏
    QMenuBar *menu = menuBar();
    QMenu *choices = menu->addMenu(QString::fromLocal8Bit("选项"));
    QAction *actionreturnmain = choices->addAction(QString::fromLocal8Bit("返回主菜单"));
    QAction *actionrestart = choices->addAction(QString::fromLocal8Bit("重新开始"));
    QAction *actionquit = choices->addAction(QString::fromLocal8Bit("退出"));

    //连接菜单栏各项的信号和槽
    connect(actionquit,&QAction::triggered,this,[=](){
        QMessageBox msg;
        msg.setWindowTitle(QString::fromLocal8Bit("退出游戏"));
        msg.setText(QString::fromLocal8Bit( "确定放弃当前进度退出游戏？"));
        msg.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msg.setDefaultButton(QMessageBox::Yes);
        int result = msg.exec();
        if(result == QMessageBox::Yes)
        {
            //如果是 yes -- 关闭当前窗口
            this->close();
        }
        else{
            //如果是 no -- 关闭当前对话框 继续进行游戏
            msg.close();
        }
    });


    //重新开始游戏项
    connect(actionrestart,&QAction::triggered,this,[=](){
        //弹出对话框确定重新开始
        QMessageBox msg;
        msg.setWindowTitle(QString::fromLocal8Bit("重新开始？"));
        msg.setText(QString::fromLocal8Bit( "确定放弃当前进度并重新开始游戏？"));
        msg.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msg.setDefaultButton(QMessageBox::Yes);
        int result = msg.exec();
        if(result == QMessageBox::Yes)
        {
            //如果是 yes -- 重新开始游戏
        }
        else{
            //如果是 no -- 关闭当前对话框 继续进行游戏
            msg.close();
        }

    });
    //返回主菜单项
    connect(actionreturnmain,&QAction::triggered,this,[=](){
        //弹出对话框确定放弃本局游戏并返回主菜单
        QMessageBox msg;
        msg.setWindowTitle(QString::fromLocal8Bit("返回主菜单？"));
        msg.setText(QString::fromLocal8Bit( "确定放弃当前进度并返回主菜单？"));
        msg.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msg.setDefaultButton(QMessageBox::Yes);
        int result = msg.exec();
        if(result == QMessageBox::Yes)
        {
            //如果是 yes -- 返回主菜单
            //发送信号 -- 主菜单接收后将此页面隐藏，主界面显示
            emit showMain();
        }
        else{
            //如果是 no -- 关闭当前对话框 继续进行游戏
            msg.close();
        }
    });

    //生成地图
    createMap();

}

void playScene::createMap()
{
    //使用QLabel 生成底图
    for(int i=0;i<map->getRow();i++)
    {
        vector<QLabel*> labeltmp;
        vector<Cell*> btntmp;
        for(int j=0;j<map->getColumn();j++)
        {

            QLabel *label = new QLabel(this);
            labeltmp.push_back(label);
            //拼接文件名
            QString picPath;
            if(vMap[i][j]==-1)
            {
                picPath = ":/pics/-1.png";//炸弹
            }
            else{
                picPath = QString(":/pics/%1.png").arg(QString::number(vMap[i][j]+1));  //空白底图或数字
            }
            //加载图片
            QPixmap pix;
            pix.load(picPath);
            //label显示图片并设置大小等
            label->setPixmap(pix);
            label->setFixedSize(pix.width(),pix.height());
            label->move((this->width()-pix.width()*map->getColumn())/2+j*pix.width(),(this->height()-pix.height()*map->getRow())/2+i*pix.height());

            //使用自定义 Cell 生成覆盖图
            Cell *cell = new Cell(i,j);
            cell->setParent(this);
            btntmp.push_back(cell);
            QPixmap btnPix;
            btnPix.load(":/pics/0.png");
            cell->move((this->width()-btnPix.width()*map->getColumn())/2+j*btnPix.width(),(this->height()-btnPix.height()*map->getRow())/2+i*btnPix.height());
            //连接点击事件
            connect(cell,&QPushButton::clicked,this,[=](){
                cell->setIcon(QIcon(""));
            });
        }
        this->labelArray.push_back(labeltmp);
        this->BtnArray.push_back(btntmp);
    }
}

void playScene::flip()
{
    //如果是格子中没有数字 == 继续反动周围八个格子 -- 反到有数字的格子即停止
}

bool playScene::isSucceeded()
{
    //所有的炸弹都被标记且其他格子都被翻开 -- 即胜利
    return true;
}
