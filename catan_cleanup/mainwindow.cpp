#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "terrain.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <QPushButton>
#include "point.h"
#include "point_disp.h"
#include "player_enum.h"
#include "player_state_enum.h"
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include "construction_button.h"
#include "construction_enum.h"
#include "dice.h"
#include "trade.h"
#include "tradebutton.h"
#include "player.h"
#include "road.h"
#include "road_disp.h"
#include "end_turn_button.h"

using namespace std;

extern vector<Terrain_type> types;
extern vector<int> numbers;
extern vector<int> xs;
extern vector<int> ys;

extern vector<Terrain> terrains;
extern vector<Terrain_disp> terrain_disps;
vector<Point> points;
vector<Point_disp*>points_disp;
vector<Road> roads;
vector<Road_disp*>roads_disp;
extern vector<int>road_x_pos;
extern vector<int>road_y_pos;
extern int current_player_index;
extern vector<int>point_x_pos;
extern vector<int>point_y_pos;
extern vector<vector<int>>points_neighbour_points;
extern vector<vector<int>>points_neighbour_terrain;
extern player_type current_player;
extern player_state current_player_state;
vector<QGraphicsView*>points_view;
vector<QGraphicsScene*>points_scene;
vector<QGraphicsView*>roads_view;
vector<QGraphicsScene*>roads_scene;
vector<QLabel*>source_card_number;//顺序存放lumber grain brick wool ore的资源数QLabel
vector<QLabel*>score_labels;//顺序存放red green blue玩家的分数QLabel
vector<QLabel*>rescard_number_labels;//顺序存放red green blue玩家的手上资源牌总数QLabel
vector<QLabel*>longest_road_number_labels;//顺序存放　red green blue 玩家的路的长度QLabel
vector<QLabel*>bk_labels;//顺序存放red green blue玩家的面板显示label
vector<Player>players;//顺序存放red green blue玩家对象
vector<Construction_button*>construction_buttons;//顺序存放建路、建小房子、建大房子按钮

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setMinimumSize(1508, 914);
    this->setFixedSize(QSize(1508,914));
    setWindowTitle("Catan");
    setWindowIcon(QIcon(QPixmap(":/background/picture_sources/background/colonist.png")));

    //生成玩家
    Player player_red(player_type::red_player);
    Player player_green(player_type::green_player);
    Player player_blue(player_type::blue_player);
    players.push_back(player_red);
    players.push_back(player_green);
    players.push_back(player_blue);

    //显示背景(蓝色海洋)
    QGraphicsScene* bkscene=new QGraphicsScene(this);
    bkscene->addPixmap(QPixmap(":/background/picture_sources/background/background.png"));
    QGraphicsView* bkview=new QGraphicsView(this);
    bkview->resize(1508,914);
    bkview->move(0,0);
    bkview->setStyleSheet("padding:0px;border:0px;background: transparent");
    bkview->setScene(bkscene);
    bkview->show();

    //资源显示背景
    QGraphicsScene* source_bk=new QGraphicsScene(this);
    source_bk->addPixmap(QPixmap(":/player_related/picture_sources/player_related/bg_section2.png"));
    QGraphicsView* source_view=new QGraphicsView(this);
    source_view->resize(610,92);
    source_view->move(0,802);
    source_view->setStyleSheet("padding:0px;border:0px;background: transparent");
    source_view->setScene(source_bk);
    source_view->show();

    //资源卡显示
    vector<QGraphicsScene*>source_card_scene;
    vector<QGraphicsView*>source_card_view;
    vector<QLabel*>source_card_corner;
    vector<int>source_card_scene_x_pos{90,180,270,360,450};
    for(int temp=0;temp<5;temp++)
    {
        QString temp_str;
        switch (temp) {
        case 0:
            temp_str=":/card/picture_sources/card/card_lumber.png";
            break;
        case 1:
            temp_str=":/card/picture_sources/card/card_grain.png";
            break;
        case 2:
            temp_str=":/card/picture_sources/card/card_brick.png";
            break;
        case 3:
            temp_str=":/card/picture_sources/card/card_wool.png";
            break;
        case 4:
            temp_str=":/card/picture_sources/card/card_ore.png";
            break;
        }
        QGraphicsScene* card=new QGraphicsScene(this);
        card->addPixmap(QPixmap(temp_str));
        QGraphicsView* view=new QGraphicsView(this);
        view->resize(60,84);
        view->move(source_card_scene_x_pos[temp],802);
        view->setStyleSheet("padding:0px;border:0px;background: transparent");
        view->setScene(card);
        view->scale(0.2,0.2);
        view->show();
        source_card_scene.push_back(card);
        source_card_view.push_back(view);
        QLabel* corner_label=new QLabel(this);
        corner_label->resize(28,28);
        QPixmap source_corner(":/player_related/picture_sources/player_related/button_badge_background_blue.png");
        source_corner=source_corner.scaled(28,28);
        corner_label->setPixmap(source_corner);
        corner_label->move(source_card_scene_x_pos[temp]+30,802);
        source_card_corner.push_back(corner_label);
        QLabel* number_label=new QLabel(this);
        number_label->resize(28,28);
        QFont ft("Microsoft YaHei", 10);
        ft.setBold(true);
        number_label->setFont(ft);
        number_label->setText("13");
        number_label->setStyleSheet("color:white;");
        number_label->move(source_card_scene_x_pos[temp]+35,802);
        number_label->show();
        source_card_number.push_back(number_label);
    }

    //玩家面板显示
    vector<int>player_panel_ypos{758,626,494};
    for(int temp=0;temp<3;temp++)
    {
        QString temp_str;
        switch (temp) {
        case 0:
            temp_str=":/player_related/picture_sources/player_related/player_bg_red.png";
            break;
        case 1:
            temp_str=":/player_related/picture_sources/player_related/player_bg_green.png";
            break;
        case 2:
            temp_str=":/player_related/picture_sources/player_related/player_bg_blue.png";
            break;
        }
        QLabel* bk_label=new QLabel(this);//背景板（白色渐变的圆角矩形）
        bk_label->resize(355,127);
        QPixmap bk_pic;
        if(temp==0) bk_pic=QPixmap(":/player_related/picture_sources/player_related/bg_section1.png");//初始化的时候默认红方高亮
        else bk_pic=QPixmap(":/player_related/picture_sources/player_related/bg_player_inactive1.png");
        bk_pic=bk_pic.scaled(355,127);
        bk_label->setPixmap(bk_pic);
        bk_label->move(1148,player_panel_ypos[temp]);
        bk_labels.push_back(bk_label);

        QLabel* circle_label=new QLabel(this);//玩家头像圆圈（红绿蓝）
        circle_label->resize(75,75);
        QPixmap circle_pic(temp_str);
        circle_pic=circle_pic.scaled(75,75);
        circle_label->setPixmap(circle_pic);
        circle_label->move(1170,player_panel_ypos[temp]+32);

        QLabel* man_label=new QLabel(this);//玩家头像（小人）
        man_label->resize(75,75);
        QPixmap man_pic(":/player_related/picture_sources/player_related/icon_player.png");
        man_pic=man_pic.scaled(75,75);
        man_label->setPixmap(man_pic);
        man_label->move(1170,player_panel_ypos[temp]+32);

        QLabel* ribbon_label=new QLabel(this);//玩家得分背景栏（绸缎）
        ribbon_label->resize(75,21);
        QPixmap ribbon_pic(":/player_related/picture_sources/player_related/ribbon_small.png");
        ribbon_pic=ribbon_pic.scaled(75,21);
        ribbon_label->setPixmap(ribbon_pic);
        ribbon_label->move(1172,player_panel_ypos[temp]+99);

        QLabel* score_label=new QLabel(this);//玩家分数显示栏
        score_label->resize(75,21);
        score_label->move(1172,player_panel_ypos[temp]+99);
        QFont ft("Microsoft YaHei", 10);
        ft.setBold(true);
        score_label->setFont(ft);
        score_label->setAlignment(Qt::AlignCenter);
        score_label->setText("0");
        score_labels.push_back(score_label);

        QLabel* rescard_label=new QLabel(this);//玩家手上牌数栏
        QPixmap rescard_pic(":/player_related/picture_sources/player_related/card_rescardback.png");
        rescard_pic=rescard_pic.scaled(74,103);
        rescard_label->resize(74,103);
        rescard_label->setPixmap(rescard_pic);
        rescard_label->move(1267,player_panel_ypos[temp]+13);

        QLabel* rescard_corner=new QLabel(this);
        QPixmap rescard_corner_pic(":/player_related/picture_sources/player_related/card_badge_background.png");
        rescard_corner_pic=rescard_corner_pic.scaled(37,37);
        rescard_corner->resize(37,37);
        rescard_corner->setPixmap(rescard_corner_pic);
        rescard_corner->move(1304,player_panel_ypos[temp]+13);

        QLabel* rescard_number_label=new QLabel(this);
        rescard_number_label->resize(37,37);
        rescard_number_label->move(1308,player_panel_ypos[temp]+13);
        rescard_number_label->setFont(ft);
        rescard_number_label->setAlignment(Qt::AlignCenter);
        rescard_number_label->setStyleSheet("color:white;");
        rescard_number_label->setText("0");
        rescard_number_labels.push_back(rescard_number_label);

        QLabel* longest_road_label=new QLabel(this);
        QPixmap longest_road_pic(":/player_related/picture_sources/player_related/icon_longest_road.png");
        longest_road_pic=longest_road_pic.scaled(100,100);
        longest_road_label->resize(100,100);
        longest_road_label->setPixmap(longest_road_pic);
        longest_road_label->move(1361,player_panel_ypos[temp]+13);

        QLabel* longest_road_number_label=new QLabel(this);
        longest_road_number_label->resize(100,21);
        longest_road_number_label->move(1361,player_panel_ypos[temp]+97);
        longest_road_number_label->setFont(ft);
        longest_road_number_label->setAlignment(Qt::AlignCenter);
        longest_road_number_label->setText("0");
        longest_road_number_labels.push_back(longest_road_number_label);
    }

    //做一个功能未实现的聊天室
    QLabel* chat_label=new QLabel(this);//聊天室背景
    QPixmap chat_pic(":/player_related/picture_sources/player_related/bg_section1.png");
    chat_pic=chat_pic.scaled(355,200);
    chat_label->resize(355,200);
    chat_label->setPixmap(chat_pic);
    chat_label->move(1148,289);
    QLineEdit* chat_input_box=new QLineEdit(this);
    chat_input_box->resize(315,33);
    chat_input_box->move(1168,446);
    chat_input_box->setText("Say hello");

    //游戏规则显示面板
    QLabel* rule_bk_label=new QLabel(this);
    QPixmap rule_bk_pic(":/player_related/picture_sources/player_related/bg_section1.png");
    rule_bk_pic=rule_bk_pic.scaled(355,280);
    rule_bk_label->resize(355,280);
    rule_bk_label->setPixmap(rule_bk_pic);
    rule_bk_label->move(1148,5);
    for(int temp=0;temp<3;temp++)
    {
        QString temp_str;
        switch (temp) {
        case 0:
            temp_str=":/rules/picture_sources/rules/road_rule.png";
            break;
        case 1:
            temp_str=":/rules/picture_sources/rules/settlements_rule.png";
            break;
        case 2:
            temp_str=":/rules/picture_sources/rules/city_rule.png";
            break;
        }
        QLabel* rule_label=new QLabel(this);
        QPixmap rule_lable_pic(temp_str);
        rule_lable_pic=rule_lable_pic.scaled(292,92);
        rule_label->resize(292,92);
        rule_label->setPixmap(rule_lable_pic);
        rule_label->move(1148,5+temp*92);
    }

    //显示terrain
    for(int i = 0; i < 19; i++)
        terrain_disps[i].display(this);


    //建筑按钮
    //点击建路按钮后玩家分数不会立马更新，要等玩家放好路之后才更新各个玩家的分数
    Construction_button* build_road=new Construction_button(constructon::road,this);//点击之后玩家资源修改，建筑数修改，玩家显示修改，道路激活点显示(在point类构造出来后处理)
    connect(build_road,&QPushButton::clicked,[build_road](){
        if(current_player==player_type::red_player)
        {
            players[0].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1}});
            players[0].consume_constructions(constructon::road);
            source_card_number[0]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[2]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::brick]));
            rescard_number_labels[0]->setText(QString::number(players[0].get_total_sources()));
            build_road->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::road]));
        }
        else if(current_player==player_type::green_player)
        {
            players[1].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1}});
            players[1].consume_constructions(constructon::road);
            source_card_number[0]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[2]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::brick]));
            rescard_number_labels[1]->setText(QString::number(players[1].get_total_sources()));
            build_road->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::road]));
        }
        else if(current_player==player_type::blue_player)
        {
            players[2].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1}});
            players[2].consume_constructions(constructon::road);
            source_card_number[0]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[2]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::brick]));
            rescard_number_labels[2]->setText(QString::number(players[2].get_total_sources()));
            build_road->get_facility_remain()->setText(QString::number(players[2].get_constructions_remained()[constructon::road]));
        }
    });
    build_road->setDisabled(true);
    //点击建大小房子按钮之后玩家的分数更新放到point_disp.cpp文件中处理
    Construction_button* build_small_house=new Construction_button(constructon::small_house,this);
    connect(build_small_house,&QPushButton::clicked,[build_small_house](){
        if(current_player==player_type::red_player)
        {
            players[0].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1},{Terrain_type::grain,1},{Terrain_type::wool,1}});
            players[0].consume_constructions(constructon::small_house);
            source_card_number[0]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[1]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::grain]));
            source_card_number[2]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::brick]));
            source_card_number[3]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::wool]));
            rescard_number_labels[0]->setText(QString::number(players[0].get_total_sources()));
            build_small_house->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::small_house]));
        }
        else if(current_player==player_type::green_player)
        {
            players[1].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1},{Terrain_type::grain,1},{Terrain_type::wool,1}});
            players[1].consume_constructions(constructon::small_house);
            source_card_number[0]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[1]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::grain]));
            source_card_number[2]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::brick]));
            source_card_number[3]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::wool]));
            rescard_number_labels[1]->setText(QString::number(players[1].get_total_sources()));
            build_small_house->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::small_house]));
        }
        else if(current_player==player_type::blue_player)
        {
            players[2].consume_sources({{Terrain_type::lumber,1},{Terrain_type::brick,1},{Terrain_type::grain,1},{Terrain_type::wool,1}});
            players[2].consume_constructions(constructon::small_house);
            source_card_number[0]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::lumber]));
            source_card_number[1]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::grain]));
            source_card_number[2]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::brick]));
            source_card_number[3]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::wool]));
            rescard_number_labels[2]->setText(QString::number(players[2].get_total_sources()));
            build_small_house->get_facility_remain()->setText(QString::number(players[2].get_constructions_remained()[constructon::small_house]));
        }
    });
    build_small_house->setDisabled(true);
    Construction_button* build_big_house=new Construction_button(constructon::big_house,this);
    connect(build_big_house,&QPushButton::clicked,[build_big_house](){
        if(current_player==player_type::red_player)
        {
            players[0].consume_sources({{Terrain_type::grain,2},{Terrain_type::ore,3}});
            players[0].consume_constructions(constructon::big_house);
            source_card_number[4]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::ore]));
            source_card_number[3]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::wool]));
            rescard_number_labels[0]->setText(QString::number(players[0].get_total_sources()));
            build_big_house->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::big_house]));
        }
        else if(current_player==player_type::green_player)
        {
            players[1].consume_sources({{Terrain_type::grain,2},{Terrain_type::ore,3}});
            players[1].consume_constructions(constructon::big_house);
            source_card_number[4]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::ore]));
            source_card_number[3]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::wool]));
            rescard_number_labels[1]->setText(QString::number(players[1].get_total_sources()));
            build_big_house->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::big_house]));
        }
        else if(current_player==player_type::blue_player)
        {
            players[2].consume_sources({{Terrain_type::grain,2},{Terrain_type::ore,3}});
            players[2].consume_constructions(constructon::big_house);
            source_card_number[4]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::ore]));
            source_card_number[3]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::wool]));
            rescard_number_labels[2]->setText(QString::number(players[2].get_total_sources()));
            build_big_house->get_facility_remain()->setText(QString::number(players[2].get_constructions_remained()[constructon::big_house]));
        }
    });
    build_big_house->setDisabled(true);
    build_road->show();
    build_big_house->show();
    build_small_house->show();
    construction_buttons.push_back(build_road);
    construction_buttons.push_back(build_small_house);
    construction_buttons.push_back(build_big_house);

    //骰子按钮
    Dice *diceButton = new Dice(this);
    diceButton->show();
    connect(diceButton,&Dice::clicked,[diceButton](){
        diceButton->roll();
        players[0].get_sources(diceButton->get_dice_number());
        players[1].get_sources(diceButton->get_dice_number());
        players[2].get_sources(diceButton->get_dice_number());
        rescard_number_labels[0]->setText(QString::number(players[0].get_total_sources()));
        rescard_number_labels[1]->setText(QString::number(players[1].get_total_sources()));
        rescard_number_labels[2]->setText(QString::number(players[2].get_total_sources()));
        int temp=0;
        switch (current_player) {
        case player_type::red_player:
            temp=0;
            break;
        case player_type::green_player:
            temp=1;
            break;
        case player_type::blue_player:
            temp=2;
            break;
        }
        source_card_number[0]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::lumber]));
        source_card_number[1]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::grain]));
        source_card_number[2]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::brick]));
        source_card_number[3]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::wool]));
        source_card_number[4]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::ore]));
        diceButton->setDisabled(true);
        for(int temp=0;temp<3;temp++)
            construction_buttons[temp]->setDisabled(false);
    });

    //交易按钮
    TradeButton *tradeButton = new TradeButton(this);
    tradeButton->show();
    connect(tradeButton,&TradeButton::clicked,[tradeButton](){
        tradeButton->pop();
        int temp=0;
        switch (current_player) {
        case player_type::red_player:
            temp=0;
            break;
        case player_type::green_player:
            temp=1;
            break;
        case player_type::blue_player:
            temp=2;
            break;
        }
        source_card_number[0]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::lumber]));
        source_card_number[1]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::grain]));
        source_card_number[2]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::brick]));
        source_card_number[3]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::wool]));
        source_card_number[4]->setText(QString::number(players[temp].get_owned_sources()[Terrain_type::ore]));
        rescard_number_labels[0]->setText(QString::number(players[0].get_total_sources()));
        rescard_number_labels[1]->setText(QString::number(players[1].get_total_sources()));
        rescard_number_labels[2]->setText(QString::number(players[2].get_total_sources()));
    });

    //结束轮次按钮
    End_turn_button* end_turn_button=new End_turn_button(this);
    end_turn_button->show();
    connect(diceButton,&QPushButton::clicked,end_turn_button,[end_turn_button](){
        end_turn_button->setDisabled(false);
        end_turn_button->get_status_label()->setPixmap(end_turn_button->get_status_pic(1));
    });
    connect(end_turn_button,&QPushButton::clicked,[end_turn_button,diceButton](){
        current_player_index=(current_player_index+1)%3;
        current_player=players[current_player_index].get_player_type();
        source_card_number[0]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::lumber]));
        source_card_number[1]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::grain]));
        source_card_number[2]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::brick]));
        source_card_number[3]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::wool]));
        source_card_number[4]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::ore]));
        for(int temp=0;temp<3;temp++)//修改高亮
        {
            if(temp==current_player_index) bk_labels[current_player_index]->setPixmap(QPixmap(":/player_related/picture_sources/player_related/bg_section1.png"));
            else  bk_labels[temp]->setPixmap(QPixmap(":/player_related/picture_sources/player_related/bg_player_inactive1.png"));
        }
        end_turn_button->get_status_label()->setPixmap(end_turn_button->get_status_pic(0));
        end_turn_button->setDisabled(true);
        diceButton->setDisabled(false);
        for(int temp=0;temp<3;temp++)
            construction_buttons[temp]->setDisabled(true);
        construction_buttons[0]->get_facility_icon()->setPixmap(construction_buttons[0]->get_facility_pic(current_player_index,constructon::road));
        construction_buttons[1]->get_facility_icon()->setPixmap(construction_buttons[1]->get_facility_pic(current_player_index,constructon::small_house));
        construction_buttons[2]->get_facility_icon()->setPixmap(construction_buttons[2]->get_facility_pic(current_player_index,constructon::big_house));
        construction_buttons[0]->get_facility_remain()->setText(QString::number(players[current_player_index].get_constructions_remained()[constructon::road]));
        construction_buttons[1]->get_facility_remain()->setText(QString::number(players[current_player_index].get_constructions_remained()[constructon::small_house]));
        construction_buttons[2]->get_facility_remain()->setText(QString::number(players[current_player_index].get_constructions_remained()[constructon::big_house]));
        construction_buttons[0]->get_rounded_corner()->setPixmap(construction_buttons[0]->get_corner_pic(current_player_index));
        construction_buttons[1]->get_rounded_corner()->setPixmap(construction_buttons[1]->get_corner_pic(current_player_index));
        construction_buttons[2]->get_rounded_corner()->setPixmap(construction_buttons[2]->get_corner_pic(current_player_index));
    });

    //显示Road相关
    for(int temp=0;temp<72;temp++)
    {
       QGraphicsScene* p_scene=new QGraphicsScene(this);
       QGraphicsView* p_view=new QGraphicsView(this);
       p_view->resize(230,230);
       p_view->move(road_x_pos[temp]-115,road_y_pos[temp]-115);
       p_view->setStyleSheet("padding:0px;border:0px;background: transparent");
       p_view->setScene(p_scene);
       p_view->scale(0.375,0.375);
       p_view->show();
       roads_view.push_back(p_view);
       roads_scene.push_back(p_scene);
    }
    for (int i=0; i<72;i++)
    {
        Road r=Road(i);
        roads.push_back(r);
        Road_disp* r_disp=new Road_disp(i,this);
        roads_disp.push_back(r_disp);
    }
    for(int temp=0; temp<72;temp++)
        {
            Road_disp* temp_disp=roads_disp[temp];
            connect(build_road,&QPushButton::clicked,build_road,[temp_disp,build_road](){current_player_state=player_state::is_building_road;
                temp_disp->display_befor_decide();
                disconnect(build_road,0,temp_disp,0);
                connect(temp_disp,&Road_disp::clicked,[temp_disp](){temp_disp->send_build_road_signal();});
            });
        }
    for(int temp=0;temp<72;temp++)
    {
        for(int temp1=0;temp1<72;temp1++)
        {
            Road_disp* r1=roads_disp[temp];
            Road_disp* r2=roads_disp[temp1];
            connect(r1,SIGNAL(has_built_road(int)),r2,SLOT(display_after_decide(int)));
        }
    }


    //显示Point相关
    for(int temp=0;temp<54;temp++)
    {
       QGraphicsScene* p_scene=new QGraphicsScene(this);
       QGraphicsView* p_view=new QGraphicsView(this);
       p_view->resize(48,48);
       p_view->move(point_x_pos[temp]-24,point_y_pos[temp]-24);
       p_view->setStyleSheet("padding:0px;border:0px;background: transparent");
       p_view->setScene(p_scene);
       p_view->scale(0.375,0.375);
       p_view->show();
       points_view.push_back(p_view);
       points_scene.push_back(p_scene);
    }
    for(int i=0;i<54;i++)
    {
        Point p=Point(i);
        points.push_back(p);
        Point_disp* p_disp=new Point_disp(i,this);
        points_disp.push_back(p_disp);
    }
    for(int temp=0;temp<54;temp++)
    {
        Point_disp* temp_disp=points_disp[temp];
        connect(build_small_house,&QPushButton::clicked,temp_disp,[temp_disp,build_small_house](){current_player_state=player_state::is_building_small_house;
            temp_disp->display_befor_decide();
            disconnect(build_small_house,0,temp_disp,0);
            for(int temp=0;temp<54;temp++)
            {
                for(int temp1=0;temp1<54;temp1++)
                {
                    Point_disp* p1=points_disp[temp];
                    Point_disp* p2=points_disp[temp1];
                    connect(p1,SIGNAL(has_built_small_house(int)),p2,SLOT(display_after_decide(int)));
                }
            }
            connect(temp_disp,&Point_disp::clicked,[temp_disp](){temp_disp->send_build_small_house_signal();});
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

