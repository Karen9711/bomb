#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include<QPixmap>
#include <QPushButton>
#include<QDebug>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化主界面
    this->setWindowTitle(QString::fromLocal8Bit("扫雷"));
    ui->confirmLevel->setStyleSheet("QPushButton.confirmLevel{border:0}");
    //连接菜单项
    //退出项
    connect(ui->actionquit,&QAction::triggered,this,[=](){
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
    connect(ui->actionrestart,&QAction::triggered,this,[=](){
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
    connect(ui->actionreturnMain,&QAction::triggered,this,[=](){
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
        }
        else{
            //如果是 no -- 关闭当前对话框 继续进行游戏
            msg.close();
        }
    });

    //设置难度范围
    ui->spinBox->setRange(0,2);
    //设置默认难度
    ui->spinBox->setValue(0);
    //初始化m_level
    m_level = ui->spinBox->value();
    //spinBox 选择关卡连接 -- 将关卡难度赋值给m_level作为内部维护的当前关卡难度
    void (QSpinBox::*spinBoxSignal)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox,spinBoxSignal,this,[=](int value){
        this->m_level = value;
        qDebug()<<m_level;
    });

    //点击选择难度按钮 spinbox 失去焦点
    connect(ui->confirmLevel,&QPushButton::clicked,this,[=](){
        ui->spinBox->clearFocus();
    });

    //点击退出游戏则退出
    connect(ui->quitBtn,&QPushButton::clicked,this,[=](){
        QMessageBox msg;
        msg.setWindowTitle(QString::fromLocal8Bit("退出游戏"));
        msg.setText(QString::fromLocal8Bit( "退出游戏？"));
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


    //初始化游戏界面指针
    playscene = NULL;
    //接受从游戏界面传来的信号 -- showMain()

    //点击开始按钮开始游戏
    connect(ui->startBtn,&QPushButton::clicked,this,[=](){
        //创建游戏界面
        playscene = new playScene(this->m_level);
        //连接游戏界面发送的showMain 信号 -- 返回主界面
        connect(playscene,&playScene::showMain,this,[=](){
            QTimer::singleShot(300,this,[=](){
                //关闭游戏界面
                playscene->close();
                delete playscene;
                playscene = NULL;

                //显示主界面
                this->show();

            });
        });

       //延时关闭当前界面
        QTimer::singleShot(200,this,[=](){
            this->hide();
            //进入游戏界面
            playscene->setGeometry(this->x(),this->y(),playscene->width(),playscene->height());
            playscene->show();
        });

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

