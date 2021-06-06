#include "road_disp.h"
#include "player_enum.h"
#include "player_state_enum.h"
#include "player.h"
#include <algorithm>
#include "mainwindow.h"
#include "road.h"
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include "construction_button.h"
#include "end_turn_button.h"
#include "tradebutton.h"

extern vector<int>road_x_pos;
extern vector<int>road_y_pos;
extern vector<int>road_angle;
extern player_type current_player;
extern player_state current_player_state;
extern vector<Road> roads;
extern vector<QGraphicsView*>roads_view;
extern vector<QGraphicsScene*>roads_scene;
extern vector<QLabel*>source_card_number;//顺序存放lumber grain brick wool ore的资源数QLabel
extern vector<QLabel*>score_labels;//顺序存放red green blue玩家的分数QLabel
extern vector<QLabel*>rescard_number_labels;//顺序存放red green blue玩家的手上资源牌总数QLabel
extern vector<QLabel*>longest_road_number_labels;//顺序存放　red green blue 玩家的路的长度QLabel
extern vector<Player>players;//顺序存放red green blue玩家对象
extern int game_status;
extern bool is_in_normal_round;
extern vector<Construction_button*>construction_buttons;//顺序存放建路、建小房子、建大房子按钮
extern End_turn_button* end_turn_button;
extern TradeButton *tradeButton;


Road_disp::Road_disp(int i,QWidget *parent) : QPushButton(parent)
{
    index=i;
    current_circle_index=0;
    angle = road_angle[i];
    rotateMatrix.rotate(angle);
    timer=new QTimer(this);
    timer->start(50);
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
    QString str=":/highlight_circle/assets/highlight_circle/icon_highlight_circle_white"+QString::number(current_circle_index%45+15)+".png";
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

        setIcon(QIcon());
        return;
    }
    switch (current_player) {
    case player_type::red_player:
    {
        set<int> occupiedPoints = players[0].get_occupied_points();
        if(occupiedPoints.find(roads[index].get_endpoints()[0]) != occupiedPoints.end() || occupiedPoints.find(roads[index].get_endpoints()[1]) != occupiedPoints.end())
        {
            setDisabled(false);
            setEnabled(true);
            construction_buttons[0]->setDisabled(true);
            construction_buttons[1]->setDisabled(true);
            construction_buttons[2]->setDisabled(true);
            tradeButton->setDisabled(true);
            end_turn_button->setDisabled(true);
            current_circle_index = 0;
            connect(timer,&QTimer::timeout,this,[this](){change_circle_index();});

            return;
        };
    }break;
    case player_type::green_player:
    {
        set<int> occupiedPoints = players[1].get_occupied_points();
        if(occupiedPoints.find(roads[index].get_endpoints()[0]) != occupiedPoints.end() || occupiedPoints.find(roads[index].get_endpoints()[1]) != occupiedPoints.end())
        {
            setDisabled(false);
            setEnabled(true);
            construction_buttons[0]->setDisabled(true);
            construction_buttons[1]->setDisabled(true);
            construction_buttons[2]->setDisabled(true);
            tradeButton->setDisabled(true);
            end_turn_button->setDisabled(true);
            current_circle_index = 0;
            connect(timer,&QTimer::timeout,this,[this](){change_circle_index();});
            return;
        };
    }break;
    case player_type::blue_player:
    {
        set<int> occupiedPoints = players[2].get_occupied_points();
        if(occupiedPoints.find(roads[index].get_endpoints()[0]) != occupiedPoints.end() || occupiedPoints.find(roads[index].get_endpoints()[1]) != occupiedPoints.end())
        {
            setDisabled(false);
            setEnabled(true);
            construction_buttons[0]->setDisabled(true);
            construction_buttons[1]->setDisabled(true);
            construction_buttons[2]->setDisabled(true);
            tradeButton->setDisabled(true);
            end_turn_button->setDisabled(true);
            current_circle_index = 0;
            connect(timer,&QTimer::timeout,this,[this](){change_circle_index();});
            return;
        };
    }break;
    default: break;
    }

    setDisabled(true);
    setEnabled(false);

    setIcon(QIcon());
    return;



}

void Road_disp::display_before_decide_in_opening_status(int point_index)
{
    if(roads[index].get_endpoints()[0]==point_index||roads[index].get_endpoints()[1]==point_index)
    {
        setDisabled(false);
        setEnabled(true);
        current_circle_index = 0;
        connect(timer,&QTimer::timeout,this,[this](){change_circle_index();});
        return;
    }
    else
    {
        setDisabled(true);
        setEnabled(false);

        setIcon(QIcon());
        return;
    }
}

void Road_disp::send_build_road_signal()
{
    emit has_built_road(index);
}


void Road_disp::disable_display()
{

        setDisabled(true);
        setEnabled(false);
        disconnect(timer,0,this,0);
        setIcon(QIcon());
        return;
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
            if(is_in_normal_round)
            {
                players[0].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1}});
            }
            players[0].consume_constructions(constructon::road);
            players[0].add_road(index);
            players[0].add_point(roads[index].get_endpoints()[0]);
            players[0].add_point(roads[index].get_endpoints()[1]);
            source_card_number[0]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[2]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::brick]));
            rescard_number_labels[0]->setText(QString::number(players[0].get_total_sources()));

            roads_scene[index]->addPixmap(QPixmap(tr(":/road/assets/road/road_red.png")).transformed(rotateMatrix,Qt::SmoothTransformation));
            roads[index].set_built();
            roads[index].set_owned_player(player_type::red_player);
            disconnect(this,0,this,0);

        }
        break;

     case player_type::blue_player:
        if(current_player_state==player_state::is_building_road)
        {
            if(is_in_normal_round)
            {
                players[2].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1}});
            }
            players[2].consume_constructions(constructon::road);
            source_card_number[0]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[2]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::brick]));
            players[2].add_road(index);
            players[2].add_point(roads[index].get_endpoints()[0]);
            players[2].add_point(roads[index].get_endpoints()[1]);
            rescard_number_labels[2]->setText(QString::number(players[2].get_total_sources()));

            roads_scene[index]->addPixmap(QPixmap(tr(":/road/assets/road/road_blue.png")).transformed(rotateMatrix,Qt::SmoothTransformation));
            roads[index].set_built();
            roads[index].set_owned_player(player_type::blue_player);

        }
        break;
      case player_type::green_player:
        if(current_player_state==player_state::is_building_road)
        {
            if(is_in_normal_round)
            {
                players[1].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1}});
            }
            players[1].consume_constructions(constructon::road);
            source_card_number[0]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[2]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::brick]));
            players[1].add_road(index);
            players[1].add_point(roads[index].get_endpoints()[0]);
            players[1].add_point(roads[index].get_endpoints()[1]);
            rescard_number_labels[1]->setText(QString::number(players[1].get_total_sources()));

            roads_scene[index]->addPixmap(QPixmap(tr(":/road/assets/road/road_green.png")).transformed(rotateMatrix,Qt::SmoothTransformation));
            roads[index].set_built();
            roads[index].set_owned_player(player_type::green_player);

        }
        break;
      default:break;
    }
    if(!is_in_normal_round)
    {
        game_status++;
        emit game_status_updated();
    }
}
