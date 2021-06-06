#include "point_disp.h"
#include "player_enum.h"
#include "player_state_enum.h"
#include "point.h"
#include <QTimer>
#include <QDebug>
#include "player.h"
#include <QLabel>
#include "construction_button.h"
#include "end_turn_button.h"
#include "tradebutton.h"

extern vector<int>point_x_pos;
extern vector<int>point_y_pos;
extern player_type current_player;
extern player_state current_player_state;
extern vector<Point> points;
extern vector<QGraphicsView*>points_view;
extern vector<QGraphicsScene*>points_scene;
extern vector<Player>players;//顺序为红绿蓝玩家
extern vector<QLabel*>score_labels;//顺序存放red green blue玩家的分数QLabel
extern vector<QLabel*>source_card_number;//顺序存放lumber grain brick wool ore的资源数QLabel
extern vector<QLabel*>rescard_number_labels;//顺序存放red green blue玩家的手上资源牌总数QLabel
extern vector<Construction_button*>construction_buttons;
extern End_turn_button* end_turn_button;
extern TradeButton *tradeButton;
extern int game_status;
extern bool is_in_normal_round;
extern bool is_sea_shore_mode;
extern vector<int>sea_shore_point;

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
    QString str=":/highlight_circle/assets/highlight_circle/icon_highlight_circle_white"+QString::number(current_circle_index%45+15)+".png";
    circle=QPixmap(str);
    setIcon(QIcon(circle));
    current_circle_index=current_circle_index%30+1;
}

void Point_disp::display_befor_decide()
{
    if(current_player_state==player_state::is_building_small_house)
    {
        if(points[index].get_can_build_house_here()==false)
        {
            setDisabled(true);
            setEnabled(false);
            setIcon(QIcon());
            return;
        }
        switch (current_player) {
        case player_type::red_player:
            if(players[0].get_occupied_points().find(index)!=players[0].get_occupied_points().end())
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
            }
            break;
        case player_type::green_player:
            if(players[1].get_occupied_points().find(index)!=players[1].get_occupied_points().end())
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
            }
            break;
        case player_type::blue_player:
            if(players[2].get_occupied_points().find(index)!=players[2].get_occupied_points().end())
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
            }
            break;
        default: break;
        }
        setDisabled(true);
        setEnabled(false);

        setIcon(QIcon());
        return;
    }
    else if(current_player_state==player_state::is_building_big_house)
    {
        if(points[index].get_house_type_here()!=house_type::red_small_house&&points[index].get_house_type_here()!=house_type::green_small_house&&points[index].get_house_type_here()!=house_type::blue_small_house)
        {
            setDisabled(true);
            setEnabled(false);
            setIcon(QIcon());
            return;
        }
        switch (current_player) {
        case player_type::red_player:
            if(points[index].get_house_type_here()==house_type::red_small_house)
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
            }
            break;
         case player_type::green_player:
            if(points[index].get_house_type_here()==house_type::green_small_house)
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
            }
            break;
         case player_type::blue_player:
            if(points[index].get_house_type_here()==house_type::blue_small_house)
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
            }
            break;
         default: break;
        }
        setDisabled(true);
        setEnabled(false);

        setIcon(QIcon());
        return;
    }
}

void Point_disp::display_before_decide_in_opening_status()//开局阶段的display_before_decide版本
{
    if(points[index].get_can_build_house_here())
    {
        setDisabled(false);
        setEnabled(true);
        current_circle_index = 0;
        connect(timer,&QTimer::timeout,this,[this](){change_circle_index();});
    }
    else
    {
        setDisabled(true);
        setEnabled(false);
        setIcon(QIcon());
        return;
    }
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
        setIcon(QIcon());
        return;
    }
    //否则说明是当前点上触发了事件，进行触发后的处理工作
    setIcon(QIcon());
    switch (current_player) {
    case player_type::red_player:
        if(current_player_state==player_state::is_building_small_house)
        {
            if(is_in_normal_round)
            {
                players[0].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1},{Terrain_type::grain,1},{Terrain_type::wool,1}});
            }
            players[0].consume_constructions(constructon::small_house);
            source_card_number[0]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[1]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::grain]));
            source_card_number[2]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::brick]));
            source_card_number[3]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::wool]));
            rescard_number_labels[0]->setText(QString::number(players[0].get_total_sources()));
            construction_buttons[1]->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::small_house]));

            points_scene[index]->addPixmap(QPixmap(tr(":/settlements/assets/settlements/settlement_red.png")));
            points[index].set_already_house_here(true);
            points[index].set_can_build_house_here(false);
            points[index].set_house_type_here(house_type::red_small_house);
            points[index].set_owner_of_this_point(player_type::red_player);

            vector<int>temp_index=points[index].get_index_for_neighbour_point();
            for (auto i : temp_index)
                points[i].set_can_build_house_here(false);

            players[0].add_small_house(index);
            players[0].add_point(index);
            players[0].caculate_score();
            if(is_sea_shore_mode&&std::find(sea_shore_point.begin(),sea_shore_point.end(),index)!=sea_shore_point.end())
                players[0].add_sea_shore_point(index);

            //score_labels[0]->setText(QString::number(players[0].get_score()));
        }
        else if(current_player_state==player_state::is_building_big_house)
        {
            players[0].consume_sources({{Terrain_type::grain,2},{Terrain_type::ore,3}});
            players[0].consume_constructions(constructon::big_house);
            source_card_number[4]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::ore]));
            source_card_number[1]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::grain]));
            rescard_number_labels[0]->setText(QString::number(players[0].get_total_sources()));
            construction_buttons[2]->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::big_house]));

            points_scene[index]->clear();
            points_scene[index]->addPixmap(QPixmap(tr(":/city/assets/city/city_red.png")));

            points[index].set_house_type_here(house_type::red_big_house);

            players[0].enhance_from_small_to_big(index);
            players[0].caculate_score();

           // score_labels[0]->setText(QString::number(players[0].get_score()));
        }
        break;
     case player_type::blue_player://注意蓝色方在Players中存在最后面
        if(current_player_state==player_state::is_building_small_house)
        {
            if(is_in_normal_round)
            {
                players[2].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1},{Terrain_type::grain,1},{Terrain_type::wool,1}});
            }
            players[2].consume_constructions(constructon::small_house);
            source_card_number[0]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[1]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::grain]));
            source_card_number[2]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::brick]));
            source_card_number[3]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::wool]));
            rescard_number_labels[2]->setText(QString::number(players[2].get_total_sources()));
            construction_buttons[1]->get_facility_remain()->setText(QString::number(players[2].get_constructions_remained()[constructon::small_house]));

            points_scene[index]->addPixmap(QPixmap(tr(":/settlements/assets/settlements/settlement_blue.png")));

            points[index].set_already_house_here(true);
            points[index].set_can_build_house_here(false);
            points[index].set_house_type_here(house_type::blue_small_house);
            points[index].set_owner_of_this_point(player_type::blue_player);

            vector<int>temp_index=points[index].get_index_for_neighbour_point();
            for (auto i : temp_index)
                points[i].set_can_build_house_here(false);


            players[2].add_point(index);
            players[2].add_small_house(index);
            players[2].caculate_score();
            if(is_sea_shore_mode&&std::find(sea_shore_point.begin(),sea_shore_point.end(),index)!=sea_shore_point.end())
                players[2].add_sea_shore_point(index);

           // score_labels[2]->setText(QString::number(players[2].get_score()));
        }
        else if(current_player_state==player_state::is_building_big_house)
        {
            players[2].consume_sources({{Terrain_type::grain,2},{Terrain_type::ore,3}});
            players[2].consume_constructions(constructon::big_house);
            source_card_number[4]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::ore]));
            source_card_number[1]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::grain]));
            rescard_number_labels[2]->setText(QString::number(players[2].get_total_sources()));
            construction_buttons[2]->get_facility_remain()->setText(QString::number(players[2].get_constructions_remained()[constructon::big_house]));

            points_scene[index]->clear();
            points_scene[index]->addPixmap(QPixmap(tr(":/city/assets/city/city_blue.png")));

            points[index].set_house_type_here(house_type::blue_big_house);

            players[2].enhance_from_small_to_big(index);
            players[2].caculate_score();

          //  score_labels[2]->setText(QString::number(players[2].get_score()));
        }
        break;
      case player_type::green_player:
        if(current_player_state==player_state::is_building_small_house)
        {
            if(is_in_normal_round)
            {
                players[1].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1},{Terrain_type::grain,1},{Terrain_type::wool,1}});
            }
            players[1].consume_constructions(constructon::small_house);
            source_card_number[0]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[1]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::grain]));
            source_card_number[2]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::brick]));
            source_card_number[3]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::wool]));
            rescard_number_labels[1]->setText(QString::number(players[1].get_total_sources()));
            construction_buttons[1]->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::small_house]));

            points_scene[index]->addPixmap(QPixmap(tr(":/settlements/assets/settlements/settlement_green.png")));

            points[index].set_already_house_here(true);
            points[index].set_can_build_house_here(false);
            points[index].set_house_type_here(house_type::green_small_house);
            points[index].set_owner_of_this_point(player_type::green_player);

            vector<int>temp_index=points[index].get_index_for_neighbour_point();
            for (auto i : temp_index)
                points[i].set_can_build_house_here(false);


            players[1].add_point(index);
            players[1].add_small_house(index);
            players[1].caculate_score();
            if(is_sea_shore_mode&&std::find(sea_shore_point.begin(),sea_shore_point.end(),index)!=sea_shore_point.end())
                players[1].add_sea_shore_point(index);

          //  score_labels[1]->setText(QString::number(players[1].get_score()));
        }
        else if(current_player_state==player_state::is_building_big_house)
        {
            players[1].consume_sources({{Terrain_type::grain,2},{Terrain_type::ore,3}});
            players[1].consume_constructions(constructon::big_house);
            source_card_number[4]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::ore]));
            source_card_number[1]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::grain]));
            rescard_number_labels[1]->setText(QString::number(players[1].get_total_sources()));
            construction_buttons[2]->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::big_house]));

            points_scene[index]->clear();
            points_scene[index]->addPixmap(QPixmap(tr(":/city/assets/city/city_green.png")));

            points[index].set_house_type_here(house_type::green_big_house);

            players[1].enhance_from_small_to_big(index);
            players[1].caculate_score();

         //   score_labels[1]->setText(QString::number(players[1].get_score()));
        }
        break;
      default:break;
    }
    current_player_state=player_state::idle;
    if(!is_in_normal_round)
    {
        game_status++;
        emit game_status_updated();
    }
}
