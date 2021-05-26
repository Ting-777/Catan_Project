#include "construction_button.h"
#include "player_enum.h"
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
    QString temp_str_for_corner;
    switch (current_player) {
    case player_type::red_player:
        temp_str_for_corner=":/player_related/picture_sources/player_related/button_badge_background_red.png";
        break;
    case player_type::blue_player:
        temp_str_for_corner=":/player_related/picture_sources/player_related/button_badge_background_blue.png";
        break;
    case player_type::green_player:
        temp_str_for_corner=":/player_related/picture_sources/player_related/button_badge_background_green.png";
        break;
    default: break;
    }
    QPixmap corner_pic(temp_str_for_corner);
    corner_pic=corner_pic.scaled(28,28);
    rounded_corner->setPixmap(corner_pic);
    rounded_corner->move(50,0);
    rounded_corner->show();

    //建筑设置图标显示
    facility_icon=new QLabel(this);
    facility_icon->resize(50,50);
    QString temp_str_for_facility;
    switch (current_player) {
    case player_type::red_player:
        if(facility==constructon::road)
            temp_str_for_facility=":/road/picture_sources/road/road_red.png";
        else if(facility==constructon::small_house)
            temp_str_for_facility=":/settlements/picture_sources/settlements/settlement_red.png";
        else if(facility==constructon::big_house)
            temp_str_for_facility=":/city/picture_sources/city/city_red.png";
        break;
     case player_type::blue_player:
        if(facility==constructon::road)
            temp_str_for_facility=":/road/picture_sources/road/road_blue.png";
        else if(facility==constructon::small_house)
            temp_str_for_facility=":/settlements/picture_sources/settlements/settlement_blue.png";
        else if(facility==constructon::big_house)
            temp_str_for_facility=":/city/picture_sources/city/city_blue.png";
        break;
     case player_type::green_player:
        if(facility==constructon::road)
            temp_str_for_facility=":/road/picture_sources/road/road_green.png";
        else if(facility==constructon::small_house)
            temp_str_for_facility=":/settlements/picture_sources/settlements/settlement_green.png";
        else if(facility==constructon::big_house)
            temp_str_for_facility=":/city/picture_sources/city/city_green.png";
        break;
    }
    QPixmap facility_pic(temp_str_for_facility);
    facility_pic=facility_pic.scaled(50,50);
    facility_icon->setPixmap(facility_pic);
    facility_icon->move(17,17);

    //圆角数字显示
    facility_remain=new QLabel(this);
    facility_remain->resize(28,28);
    QFont ft("Microsoft YaHei", 10);
    ft.setBold(true);
    facility_remain->setFont(ft);
    facility_remain->setText("13");
    facility_remain->setStyleSheet("color:white;");
    facility_remain->move(56,0);
    facility_remain->show();

    //处理按钮显示
    resize(84,84);
    move(x_pos,y_pos);
    setIcon(QIcon(QPixmap(":/player_related/picture_sources/player_related/bg_button.png")));
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
