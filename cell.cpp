#include "cell.h"
Cell::Cell(int x,int y)
{
    posX = x;
    posY = y;
    isMarked = false;
    isFlipped = false;
    QPixmap btnPix;
    btnPix.load(":/pics/0.png");
    this->setIcon(btnPix);
    this->setFixedSize(btnPix.width(),btnPix.height());
    this->setIconSize(QSize(btnPix.width(),btnPix.height()));
    this->setStyleSheet("QPushButton{border:0}");
}

void Cell::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton) //如果点击右键 -- 标记/取消标记
        //被翻开的格子能标记
    {
        QPixmap btnPix;
        if(isMarked == false)
        {
            btnPix.load(":/pics/10.png");
            isMarked = true;
        }
        else{
            btnPix.load(":/pics/0.png");
            isMarked = false;
        }
        this->setIcon(btnPix);
        this->setFixedSize(btnPix.width(),btnPix.height());
        this->setIconSize(QSize(btnPix.width(),btnPix.height()));
        this->setStyleSheet("QPushButton{border:0}");
    }
    if(e->button()==Qt::LeftButton && this->isMarked)//被标记的格子不能左键翻开
    {
        return;
    }

    QPushButton::mousePressEvent(e);
}
