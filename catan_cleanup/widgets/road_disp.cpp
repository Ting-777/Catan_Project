#include "road_disp.h"
#include "player_enum.h"
#include "player_state_enum.h"
#include "road.h"
#include <QTimer>
#include <QDebug>

extern vector<int>road_x_pos;
extern vector<int>road_y_pos;
extern vector<int>road_angle;
extern player_type current_player;
extern player_state current_player_state;
extern vector<Road> roads;
extern vector<QGraphicsView*>roads_view;
extern vector<QGraphicsScene*>roads_scene;

Road_disp::Road_disp(int i,QWidget *parent) : QPushButton(parent)
{
    index=i;
    current_circle_index=0;
    angle = road_angle[i];
    rotateMatrix.rotate(angle);
    timer=new QTimer(this);
    timer->start(100);
    setIcon(QIcon());
    setIconSize(QSize(30,30));
    resize(iconSize());
    setDisabled(true);
    setFixedSize(30,30);
    setFlat(true);
    setStyleSheet(("border:none;"));
    x_pos=road_x_pos[i];
    y_pos=road_y_pos[i];
    move(x_pos-15,y_pos-15);
    if(roads[index].get_built())
        hide();
}

int Road_disp::get_index()
{
    return index;
}
void Road_disp::change_circle_index()
{
    QString str=":/highlight_circle/picture_sources/highlight_circle/icon_highlight_circle_white"+QString::number(current_circle_index%45+15)+".png";
    circle=QPixmap(str);
    setIcon(QIcon(circle));
    current_circle_index=current_circle_index%30+1;
}

void Road_disp::display_befor_decide()
{
    if(roads[index].get_built())
    {
        setDisabled(true);
        setEnabled(false);
        disconnect(timer,0,this,0);
        setIcon(QIcon());
        return;
    }
    setDisabled(false);
    setEnabled(true);

    connect(timer,&QTimer::timeout,this,[this](){change_circle_index();});



}

void Road_disp::send_build_road_signal()
{
    emit has_built_road(index);
}




void Road_disp::display_after_decide(int road_index)
{
    //disconnect(this,0,0,0);
    setDisabled(true);
    setEnabled(false);
    disconnect(timer,0,this,0);
    if(road_index!=index)//说明没有在当前点上触发事件，而是在其他某个点上触发，此时当前点停止圆圈显示
    {
        setIcon(QIcon());
        return;
    }
    //否则说明是当前点上触发了事件，进行触发后的处理工作
    setIcon(QIcon());
    switch (current_player) {
    case player_type::red_player:
        if(current_player_state==player_state::is_building_road)
        {
            roads_scene[index]->addPixmap(QPixmap(tr(":/road/picture_sources/road/road_red.png")).transformed(rotateMatrix,Qt::SmoothTransformation));
            roads[index].set_built();
            roads[index].set_owned_player(player_type::red_player);

        }
        break;

     case player_type::blue_player:
        if(current_player_state==player_state::is_building_road)
        {
            roads_scene[index]->addPixmap(QPixmap(tr(":/road/picture_sources/road/road_blue.png")).transformed(rotateMatrix,Qt::SmoothTransformation));
            roads[index].set_built();
            roads[index].set_owned_player(player_type::blue_player);

        }
        break;
      case player_type::green_player:
        if(current_player_state==player_state::is_building_road)
        {
            roads_scene[index]->addPixmap(QPixmap(tr(":/road/picture_sources/road/road_green.png")).transformed(rotateMatrix,Qt::SmoothTransformation));
            roads[index].set_built();
            roads[index].set_owned_player(player_type::green_player);

        }
        break;
      default:break;
    }
}
