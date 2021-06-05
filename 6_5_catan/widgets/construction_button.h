#ifndef CONSTRUCTION_BUTTON_H
#define CONSTRUCTION_BUTTON_H
#include "construction_enum.h"
#include <QPushButton>
#include <QLabel>
#include "player_enum.h"
#include <map>
#include "terrain.h"
extern player_type current_player;
class Construction_button : public QPushButton
{
    Q_OBJECT
public:
    explicit Construction_button(enum constructon facility,QWidget *parent = nullptr);
    QLabel* get_facility_icon();
    QLabel* get_facility_remain();
    QLabel* get_rounded_corner();
    QPixmap get_facility_pic(int current_player_index,enum constructon facility);
    QPixmap get_corner_pic(int current_player_index);
private:
    int x_pos;
    int y_pos;
    QLabel* rounded_corner;//右上角的圆角背景
    QLabel* facility_remain;//右上角圆角上的数字
    QLabel* facility_icon;//中间的建筑类型图标显示（路、小房子、大房子）
    QPixmap red_road;
    QPixmap red_small_house;
    QPixmap red_big_house;
    QPixmap green_road;
    QPixmap green_small_house;
    QPixmap green_big_house;
    QPixmap blue_road;
    QPixmap blue_small_house;
    QPixmap blue_big_house;
    QPixmap red_corner;
    QPixmap green_corner;
    QPixmap blue_corner;
};

#endif // CONSTRUCTION_BUTTON_H
