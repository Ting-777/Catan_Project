#include "construction_button.h"
#include "player_enum.h"
#include "player.h"
extern vector<Player>players;
Construction_button::Construction_button(enum constructon facility,QWidget *parent) : QPushButton(parent)
{
    //按钮位置处理
    y_pos=802;
    if(facility==constructon::road)
        x_pos=697;
    else if(facility==constructon::small_house)
        x_pos=786;
    else if(facility==constructon::big_house)
        x_pos=875;
    //圆角显示
    rounded_corner=new QLabel(this);
    rounded_corner->resize(28,28);

    red_corner=QPixmap(":/player_related/assets/player_related/button_badge_background_red.png");
    red_corner=red_corner.scaled(28,28);

    green_corner=QPixmap(":/player_related/assets/player_related/button_badge_background_green.png");
    green_corner=green_corner.scaled(28,28);

    blue_corner=QPixmap(":/player_related/assets/player_related/button_badge_background_blue.png");
    blue_corner=blue_corner.scaled(28,28);

    rounded_corner->setPixmap(red_corner);
    rounded_corner->move(50,0);
    rounded_corner->show();

    //建筑设置图标显示
    facility_icon=new QLabel(this);
    facility_icon->resize(50,50);

    red_road=QPixmap(":/road/assets/road/road_red.png");
    red_road=red_road.scaled(50,50);
    red_small_house=QPixmap(":/settlements/assets/settlements/settlement_red.png");
    red_small_house=red_small_house.scaled(50,50);
    red_big_house=QPixmap(":/city/assets/city/city_red.png");
    red_big_house=red_big_house.scaled(50,50);

    green_road=QPixmap(":/road/assets/road/road_green.png");
    green_road=green_road.scaled(50,50);
    green_small_house=QPixmap(":/settlements/assets/settlements/settlement_green.png");
    green_small_house=green_small_house.scaled(50,50);
    green_big_house=QPixmap(":/city/assets/city/city_green.png");
    green_big_house=green_big_house.scaled(50,50);

    blue_road=QPixmap(":/road/assets/road/road_blue.png");
    blue_road=blue_road.scaled(50,50);
    blue_small_house=QPixmap(":/settlements/assets/settlements/settlement_blue.png");
    blue_small_house=blue_small_house.scaled(50,50);
    blue_big_house=QPixmap(":/city/assets/city/city_blue.png");
    blue_big_house=blue_big_house.scaled(50,50);

    if(facility==constructon::road)facility_icon->setPixmap(red_road);
    else if(facility==constructon::small_house)facility_icon->setPixmap(red_small_house);
    else if(facility==constructon::big_house)facility_icon->setPixmap(red_big_house);
    facility_icon->move(17,17);

    //圆角数字显示
    facility_remain=new QLabel(this);
    facility_remain->resize(28,28);
    QFont ft("Microsoft YaHei", 10);
    ft.setBold(true);
    facility_remain->setFont(ft);
    if(facility==constructon::road)facility_remain->setText(QString::number(players[0].get_constructions_remained()[constructon::road]));
    else if(facility==constructon::small_house)facility_remain->setText(QString::number(players[0].get_constructions_remained()[constructon::small_house]));
    else if(facility==constructon::big_house)facility_remain->setText(QString::number(players[0].get_constructions_remained()[constructon::big_house]));
    facility_remain->setStyleSheet("color:white;");
    facility_remain->move(56,0);
    facility_remain->show();

    //处理按钮显示
    resize(84,84);
    move(x_pos,y_pos);
    setIcon(QIcon(QPixmap(":/player_related/assets/player_related/bg_button.png")));
    setIconSize(QSize(84,84));
    setFlat(true);
    setStyleSheet(("border:none;"));
    show();
}

QLabel* Construction_button::get_facility_icon()
{
    return facility_icon;
}

QLabel* Construction_button::get_facility_remain()
{
    return facility_remain;
}

QPixmap Construction_button::get_facility_pic(int current_player_index,enum constructon facility)
{
    if(current_player_index==0)//red player
    {
        if(facility==constructon::road)return red_road;
        else if(facility==constructon::small_house)return red_small_house;
        else if(facility==constructon::big_house)return red_big_house;
    }
    else if(current_player_index==1)//green player
    {
        if(facility==constructon::road)return green_road;
        else if(facility==constructon::small_house)return green_small_house;
        else if(facility==constructon::big_house)return green_big_house;
    }
    else if(current_player_index==2)//blue player
    {
        if(facility==constructon::road)return blue_road;
        else if(facility==constructon::small_house)return blue_small_house;
        else if(facility==constructon::big_house)return blue_big_house;
    }
}

QPixmap Construction_button::get_corner_pic(int current_player_index)
{
    if(current_player_index==0)return red_corner;
    else if(current_player_index==1)return green_corner;
    else if(current_player_index==2)return blue_corner;
}

QLabel* Construction_button::get_rounded_corner()
{
    return rounded_corner;
}
