#ifndef CELL_H
#define CELL_H
#include<QDebug>
#include <QPushButton>
#include<QMouseEvent>
class Cell : public QPushButton
{
    Q_OBJECT
public:
    Cell(int x,int y);
    int posX;
    int posY;
    void mousePressEvent(QMouseEvent *e) override;
    bool isMarked;//记录是否被标记
    bool isFlipped;
signals:

public slots:
};

#endif // CELL_H
