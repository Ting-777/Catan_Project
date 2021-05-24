#ifndef CONSTRUCTION_BUTTON_H
#define CONSTRUCTION_BUTTON_H
#include "construction_enum.h"
#include <QPushButton>
#include <QLabel>
#include "player_enum.h"
extern player_type current_player;
class Construction_button : public QPushButton
{
    Q_OBJECT
public:
    explicit Construction_button(enum constructon facility,QWidget *parent = nullptr);
private:
    int x_pos;
    int y_pos;
    QLabel* rounded_corner;//右上角的圆角背景
    QLabel* facility_remain;//右上角圆角上的数字
    QLabel* facility_icon;//中间的建筑类型图标显示（路、小房子、大房子）

signals:
public slots:
    //要有一个redraw()槽函数，当玩家点击end turn按钮后先更改current player type，再调用这个槽函数重画三个建筑按钮

};

#endif // CONSTRUCTION_BUTTON_H
