#include "point_disp.h"
#include "player_enum.h"
#include "player_state_enum.h"
#include "point.h"
#include <QTimer>
#include <QDebug>
#include "player.h"
#include <QLabel>
extern vector<int>point_x_pos;
extern vector<int>point_y_pos;
extern player_type current_player;
extern player_state current_player_state;
extern vector<Point> points;
extern vector<QGraphicsView*>points_view;
extern vector<QGraphicsScene*>points_scene;
extern vector<Player>players;//顺序为红绿蓝玩家
extern vector<QLabel*>score_labels;//顺序存放red green blue玩家的分数QLabel
Point_disp::Point_disp(int i,QWidget *parent) : QPushButton(parent)
{
    index=i;
    current_circle_index=0;
    timer=new QTimer(this);
    timer->start(100);
    setIcon(QIcon());
    setIconSize(QSize(30,30));
    resize(iconSize());
    setDisabled(true);
    setFixedSize(30,30);
    setFlat(true);
    setStyleSheet(("border:none;"));
    x_pos=point_x_pos[i];
    y_pos=point_y_pos[i];
    move(x_pos-15,y_pos-15);
    show();
}

int Point_disp::get_index()
{
    return index;
}
void Point_disp::change_circle_index()
{
    QString str=":/highlight_circle/picture_sources/highlight_circle/icon_highlight_circle_white"+QString::number(current_circle_index%45+15)+".png";
    circle=QPixmap(str);
    setIcon(QIcon(circle));
    current_circle_index=current_circle_index%30+1;
}

void Point_disp::display_befor_decide()
{
    setDisabled(false);
    setEnabled(true);
    connect(timer,&QTimer::timeout,this,[this](){change_circle_index();});

}

void Point_disp::send_build_small_house_signal()
{
    emit has_built_small_house(index);
}

void Point_disp::send_build_big_house_signal()
{
    emit has_built_big_house(index);
}


void Point_disp::display_after_decide(int point_index)
{
    setDisabled(true);
    setEnabled(false);
    disconnect(timer,0,this,0);
    if(point_index!=index)//说明没有在当前点上触发事件，而是在其他某个点上触发，此时当前点停止圆圈显示
    {
        disconnect(this,0,0,0);
        setIcon(QIcon());
        return;
    }
    //否则说明是当前点上触发了事件，进行触发后的处理工作
    setIcon(QIcon());
    switch (current_player) {
    case player_type::red_player:
        if(current_player_state==player_state::is_building_small_house)
        {
            points_scene[index]->addPixmap(QPixmap(tr(":/settlements/picture_sources/settlements/settlement_red.png")));
            points[index].set_already_house_here(true);
            points[index].set_can_build_house_here(false);
            points[index].set_house_type_here(house_type::red_small_house);
            points[index].set_owner_of_this_point(player_type::red_player);
            vector<int>temp_index=points[index].get_index_for_neighbour_point();
            points[temp_index[0]].set_can_build_house_here(false);
            points[temp_index[1]].set_can_build_house_here(false);
            points[temp_index[2]].set_can_build_house_here(false);
            players[0].add_small_house(index);
            players[0].add_point(index);
            players[0].caculate_score();
            score_labels[0]->setText(QString::number(players[0].get_score()));
        }
        else if(current_player_state==player_state::is_building_big_house)
        {
            points_scene[index]->clear();
            points_scene[index]->addPixmap(QPixmap(tr(":/city/picture_sources/city/city_red.png")));
            points[index].set_house_type_here(house_type::red_big_house);
            players[0].enhance_from_small_to_big(index);
            players[0].caculate_score();
            score_labels[0]->setText(QString::number(players[0].get_score()));
        }
        break;
     case player_type::blue_player://注意蓝色方在Players中存在最后面
        if(current_player_state==player_state::is_building_small_house)
        {
            points_scene[index]->addPixmap(QPixmap(tr(":/settlements/picture_sources/settlements/settlement_blue.png")));
            points[index].set_already_house_here(true);
            points[index].set_can_build_house_here(false);
            points[index].set_house_type_here(house_type::blue_small_house);
            points[index].set_owner_of_this_point(player_type::blue_player);
            vector<int>temp_index=points[index].get_index_for_neighbour_point();
            points[temp_index[0]].set_can_build_house_here(false);
            points[temp_index[1]].set_can_build_house_here(false);
            points[temp_index[2]].set_can_build_house_here(false);
            players[2].add_point(index);
            players[2].add_small_house(index);
            players[2].caculate_score();
            score_labels[2]->setText(QString::number(players[2].get_score()));
        }
        else if(current_player_state==player_state::is_building_big_house)
        {
            points_scene[index]->clear();
            points_scene[index]->addPixmap(QPixmap(tr(":/city/picture_sources/city/city_blue.png")));
            points[index].set_house_type_here(house_type::blue_big_house);
            players[2].enhance_from_small_to_big(index);
            players[2].caculate_score();
            score_labels[2]->setText(QString::number(players[2].get_score()));
        }
        break;
      case player_type::green_player:
        if(current_player_state==player_state::is_building_small_house)
        {
            points_scene[index]->addPixmap(QPixmap(tr(":/settlements/picture_sources/settlements/settlement_green.png")));
            points[index].set_already_house_here(true);
            points[index].set_can_build_house_here(false);
            points[index].set_house_type_here(house_type::green_small_house);
            points[index].set_owner_of_this_point(player_type::green_player);
            vector<int>temp_index=points[index].get_index_for_neighbour_point();
            points[temp_index[0]].set_can_build_house_here(false);
            points[temp_index[1]].set_can_build_house_here(false);
            points[temp_index[2]].set_can_build_house_here(false);
            players[1].add_point(index);
            players[1].add_small_house(index);
            players[1].caculate_score();
            score_labels[1]->setText(QString::number(players[1].get_score()));
        }
        else if(current_player_state==player_state::is_building_big_house)
        {
            points_scene[index]->clear();
            points_scene[index]->addPixmap(QPixmap(tr(":/city/picture_sources/city/city_green.png")));
            points[index].set_house_type_here(house_type::green_big_house);
            players[1].enhance_from_small_to_big(index);
            players[1].caculate_score();
            score_labels[1]->setText(QString::number(players[1].get_score()));
        }
        break;
      default:break;
    }
    current_player_state=player_state::idle;
}
