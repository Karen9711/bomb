#include "playscene.h"

playScene::playScene(int m_level)
{
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

}

void playScene::createMap()
{
    //使用QLabel 生成底图

    //使用QPushButton 生成覆盖图
}

void playScene::flip()
{

}
