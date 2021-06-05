#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "terrain.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <QPushButton>
#include "point.h"
#include <random>
#include <chrono>
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
#include <QMessageBox>
#include "end_turn_button.h"
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
vector<Player>players;//顺序存放red green blue玩家对象
vector<QLabel*>bk_labels;//顺序存放red green blue玩家的面板显示label
vector<Construction_button*>construction_buttons;//顺序存放建路、建小房子、建大房子按钮
extern int current_player_index;
extern int game_status;
extern bool is_in_normal_round;
extern bool is_sea_shore_mode;



void MainWindow::slotReboot() {
music->stop();
qDebug() << "Performing application reboot...";
qApp->exit( -123456789 );
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    unsigned seed = chrono::system_clock::now ().time_since_epoch ().count ();
    shuffle (types.begin (), types.end (), default_random_engine (seed));
    seed = chrono::system_clock::now ().time_since_epoch ().count ();
    shuffle (numbers.begin (), numbers.end (), default_random_engine (seed));

    for(int i = 0;i < 19; i++)
    {
        Terrain t = Terrain(i);
        terrains.push_back(t);
        Terrain_disp td = Terrain_disp(i);
        terrain_disps.push_back(td);
    }


    ui->setupUi(this);
    this->setMinimumSize(1508, 914);
    this->setFixedSize(QSize(1508,914));
    setWindowTitle("Catan");
    setWindowIcon(QIcon(QPixmap(":/background/assets/background/colonist.png")));

    is_in_normal_round = false;

    //生成玩家
    Player player_red(player_type::red_player);
    Player player_green(player_type::green_player);
    Player player_blue(player_type::blue_player);
    players.push_back(player_red);
    players.push_back(player_green);
    players.push_back(player_blue);

    //显示背景(蓝色海洋)
    QGraphicsScene* bkscene=new QGraphicsScene(this);
    bkscene->addPixmap(QPixmap(":/background/assets/background/background.png"));
    QGraphicsView* bkview=new QGraphicsView(this);
    bkview->resize(1508,914);
    bkview->move(0,0);
    bkview->setStyleSheet("padding:0px;border:0px;background: transparent");
    bkview->setScene(bkscene);
    bkview->show();
    //生成海角，默认普通模式，海角不显示
    QLabel* sea_shore_label=new QLabel(this);
    QPixmap sea_shore_pic(":/background/assets/background/sea_shore.png");
    sea_shore_label->resize(1508,902);
    sea_shore_label->setPixmap(sea_shore_pic);
    sea_shore_label->move(0,0);

    sea_shore_label->hide();

    //BGM
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/background/assets/background/BGM.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    //music->play();

    //资源显示背景
    QGraphicsScene* source_bk=new QGraphicsScene(this);
    source_bk->addPixmap(QPixmap(":/player_related/assets/player_related/bg_section2.png"));
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
            temp_str=":/card/assets/card/card_lumber.png";
            break;
        case 1:
            temp_str=":/card/assets/card/card_grain.png";
            break;
        case 2:
            temp_str=":/card/assets/card/card_brick.png";
            break;
        case 3:
            temp_str=":/card/assets/card/card_wool.png";
            break;
        case 4:
            temp_str=":/card/assets/card/card_ore.png";
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
        QPixmap source_corner(":/player_related/assets/player_related/button_badge_background_blue.png");
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


    //做一个功能未实现的聊天室
    QLabel* chat_label=new QLabel(this);//聊天室背景
    QPixmap chat_pic(":/player_related/assets/player_related/bg_section1.png");
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
    QPixmap rule_bk_pic(":/player_related/assets/player_related/bg_section1.png");
    rule_bk_pic=rule_bk_pic.scaled(355,280);
    rule_bk_label->resize(355,280);
    rule_bk_label->setPixmap(rule_bk_pic);
    rule_bk_label->move(1148,5);
    for(int temp=0;temp<3;temp++)
    {
        QString temp_str;
        switch (temp) {
        case 0:
            temp_str=":/rules/assets/rules/road_rule.png";
            break;
        case 1:
            temp_str=":/rules/assets/rules/settlements_rule.png";
            break;
        case 2:
            temp_str=":/rules/assets/rules/city_rule.png";
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

     source_card_number[0]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::lumber]));
     source_card_number[1]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::grain]));
     source_card_number[2]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::brick]));
     source_card_number[3]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::wool]));
     source_card_number[4]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::ore]));


    //建筑按钮
    Construction_button* build_road=new Construction_button(constructon::road,this);//点击之后玩家资源修改，建筑数修改，玩家显示修改，道路激活点显示(在point类构造出来后处理)
    build_road->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::road]));
    build_road->setDisabled(true);

    Construction_button* build_small_house=new Construction_button(constructon::small_house,this);
    build_small_house->setDisabled(true);
    build_small_house->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::small_house]));

    Construction_button* build_big_house=new Construction_button(constructon::big_house,this);
    build_big_house->setDisabled(true);
    build_big_house->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::big_house]));

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
               default:
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
    connect(diceButton,&QPushButton::clicked,end_turn_button,[end_turn_button,tradeButton](){
        end_turn_button->setDisabled(false);
        end_turn_button->get_status_label()->setPixmap(end_turn_button->get_status_pic(1));
        tradeButton->setDisabled(false);
    });
    connect(end_turn_button,&QPushButton::clicked,[end_turn_button,diceButton,tradeButton](){
        current_player_index=(current_player_index+1)%3;
        current_player=players[current_player_index].get_player_type();
        source_card_number[0]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::lumber]));
        source_card_number[1]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::grain]));
        source_card_number[2]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::brick]));
        source_card_number[3]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::wool]));
        source_card_number[4]->setText(QString::number(players[current_player_index].get_owned_sources()[Terrain_type::ore]));
        for(int temp=0;temp<3;temp++)//修改高亮
        {
            if(temp==current_player_index) bk_labels[current_player_index]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_section1.png"));
            else  bk_labels[temp]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_player_inactive1.png"));
        }
        end_turn_button->get_status_label()->setPixmap(end_turn_button->get_status_pic(0));
        end_turn_button->setDisabled(true);
        diceButton->setDisabled(false);
        tradeButton->setDisabled(true);
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
    connect(build_road,&QPushButton::clicked,[](){
        construction_buttons[0]->setDisabled(true);
        construction_buttons[1]->setDisabled(true);
        construction_buttons[2]->setDisabled(true);
        switch (current_player) {
        case player_type::red_player:
            if(players[0].get_owned_sources()[Terrain_type::lumber] ==0 ||players[0].get_owned_sources()[Terrain_type::brick] == 0)
            {
                QMessageBox::about(NULL, "Construction Failed", "<h2>Insufficient resources!</h2>");
                construction_buttons[0]->setEnabled(true);
                construction_buttons[1]->setEnabled(true);
                construction_buttons[2]->setEnabled(true);
            };break;
        case player_type::green_player:
            if(players[1].get_owned_sources()[Terrain_type::lumber] ==0 ||players[1].get_owned_sources()[Terrain_type::brick] == 0)
            {
                QMessageBox::about(NULL, "Construction Failed", "<h2>Insufficient resources!</h2>");
                construction_buttons[0]->setEnabled(true);
                construction_buttons[1]->setEnabled(true);
                construction_buttons[2]->setEnabled(true);
            };break;
        case player_type::blue_player:
            if(players[2].get_owned_sources()[Terrain_type::lumber] ==0 ||players[2].get_owned_sources()[Terrain_type::brick] == 0)
            {
                QMessageBox::about(NULL, "Construction Failed", "<h2>Insufficient resources!</h2>");
                construction_buttons[0]->setEnabled(true);
                construction_buttons[1]->setEnabled(true);
                construction_buttons[2]->setEnabled(true);
            };break;
        default: break;
        }});
    for(int temp=0; temp<72;temp++)
        {
            Road_disp* temp_disp=roads_disp[temp];
            connect(build_road,&QPushButton::clicked,build_road,[temp_disp,build_road](){
                switch (current_player) {
                                case player_type::red_player:

                                if(players[0].get_owned_sources()[Terrain_type::lumber] ==0 ||players[0].get_owned_sources()[Terrain_type::brick] == 0)
                                {
                                    current_player_state= player_state::idle;
                                    return;
                                }break;
                                case player_type::green_player:
                                if(players[1].get_owned_sources()[Terrain_type::lumber] ==0 ||players[1].get_owned_sources()[Terrain_type::brick] == 0)
                                {
                                    current_player_state= player_state::idle;
                                    return;
                                }break;
                                case player_type::blue_player:
                                if(players[2].get_owned_sources()[Terrain_type::lumber] ==0 ||players[2].get_owned_sources()[Terrain_type::brick] == 0)
                                {
                                    current_player_state= player_state::idle;
                                    return;
                                }break;
                                default:return;break;
                }
                current_player_state=player_state::is_building_road;
                temp_disp->display_befor_decide();
            });
        }
    for(int temp=0;temp<72;temp++)
    {
         Road_disp* temp_disp=roads_disp[temp];
         connect(temp_disp,&Road_disp::clicked,[temp_disp](){temp_disp->send_build_road_signal();});
    }
    for(int temp=0;temp<72;temp++)
    {
        Road_disp* r1=roads_disp[temp];
        connect(r1,&Road_disp::has_built_road,[](){
            construction_buttons[0]->setEnabled(true);
            construction_buttons[1]->setEnabled(true);
            construction_buttons[2]->setEnabled(true);});
        for(int temp1=0;temp1<72;temp1++)
        {

            Road_disp* r2=roads_disp[temp1];
            connect(r1,SIGNAL(has_built_road(int)),r2,SLOT(display_after_decide(int)));
        }
    }

    QPushButton* actionReboot = new QPushButton( this );
    actionReboot->resize(75,75);
    actionReboot->setIconSize(QSize(75,75));

    actionReboot->setIcon(QIcon(QPixmap(":/background/assets/background/backbutton.png")));
    actionReboot->setFlat(true);
    actionReboot->setStyleSheet(("border:none;"));
    actionReboot->move(0,0);
    actionReboot->show();

    connect( actionReboot, &QPushButton::clicked,

                    this,&MainWindow::slotReboot          );
    QPushButton* musicButton = new QPushButton( this );
    //BGM播放暂停按钮
    musicButton->resize(75,75);
    musicButton->setIconSize(QSize(75,75));
    musicButton->setIcon(QIcon(QPixmap(":/background/assets/background/bgmon.png")));
    musicButton->setFlat(true);
    musicButton->setStyleSheet(("border:none;"));
    musicButton->move(0,80);
    musicButton->show();
    connect( musicButton, &QPushButton::clicked, this, [this,musicButton](){
        if(music->state() == QMediaPlayer::PlayingState)
        {
            music->pause();
            musicButton->setIcon(QIcon(QPixmap(":/background/assets/background/bgmoff.png")));
            musicButton->setIconSize(QSize(44,44));
        }
        else
        {
            music->play();
            musicButton->setIcon(QIcon(QPixmap(":/background/assets/background/bgmon.png")));
            musicButton->setIconSize(QSize(75,75));
        }
    });

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
    //建小房子的按钮连接关系建立
    connect(build_small_house,&QPushButton::clicked,build_small_house,[](){
        construction_buttons[0]->setDisabled(true);
        construction_buttons[1]->setDisabled(true);
        construction_buttons[2]->setDisabled(true);
        switch (current_player) {
        case player_type::red_player:
            if(players[0].get_owned_sources()[Terrain_type::lumber] <1 ||players[0].get_owned_sources()[Terrain_type::brick] <1||players[0].get_owned_sources()[Terrain_type::wool]<1 ||players[0].get_owned_sources()[Terrain_type::grain] <1)
            {
                QMessageBox::about(NULL, "Construction Failed", "<h2>Insufficient resources!</h2>");
                construction_buttons[0]->setEnabled(true);
                construction_buttons[1]->setEnabled(true);
                construction_buttons[2]->setEnabled(true);
            };break;
        case player_type::green_player:
            if(players[1].get_owned_sources()[Terrain_type::lumber] <1 ||players[1].get_owned_sources()[Terrain_type::brick] <1||players[1].get_owned_sources()[Terrain_type::wool]<1 ||players[1].get_owned_sources()[Terrain_type::grain] <1)
            {
                QMessageBox::about(NULL, "Construction Failed", "<h2>Insufficient resources!</h2>");
                construction_buttons[0]->setEnabled(true);
                construction_buttons[1]->setEnabled(true);
                construction_buttons[2]->setEnabled(true);
            };break;
        case player_type::blue_player:
            if(players[2].get_owned_sources()[Terrain_type::lumber] <1 ||players[2].get_owned_sources()[Terrain_type::brick] <1||players[2].get_owned_sources()[Terrain_type::wool]<1 ||players[2].get_owned_sources()[Terrain_type::grain] <1)
            {
                QMessageBox::about(NULL, "Construction Failed", "<h2>Insufficient resources!</h2>");
                construction_buttons[0]->setEnabled(true);
                construction_buttons[1]->setEnabled(true);
                construction_buttons[2]->setEnabled(true);
            };break;
        default: break;
        }});
    //建大房子按钮连接关系建立
    connect(build_big_house,&QPushButton::clicked,build_big_house,[](){
        switch (current_player) {
        construction_buttons[0]->setDisabled(true);
        construction_buttons[1]->setDisabled(true);
        construction_buttons[2]->setDisabled(true);
        case player_type::red_player:
            if(players[0].get_owned_sources()[Terrain_type::grain]<2||players[0].get_owned_sources()[Terrain_type::ore]<3)
            {
                QMessageBox::about(NULL, "Construction Failed", "<h2>Insufficient resources!</h2>");
                construction_buttons[0]->setEnabled(true);
                construction_buttons[1]->setEnabled(true);
                construction_buttons[2]->setEnabled(true);
            };break;
        case player_type::green_player:
            if(players[1].get_owned_sources()[Terrain_type::grain]<2||players[1].get_owned_sources()[Terrain_type::ore]<3)
            {
                QMessageBox::about(NULL, "Construction Failed", "<h2>Insufficient resources!</h2>");
                construction_buttons[0]->setEnabled(true);
                construction_buttons[1]->setEnabled(true);
                construction_buttons[2]->setEnabled(true);
            };break;
        case player_type::blue_player:
            if(players[2].get_owned_sources()[Terrain_type::grain]<2||players[2].get_owned_sources()[Terrain_type::ore]<3)
            {
                QMessageBox::about(NULL, "Construction Failed", "<h2>Insufficient resources!</h2>");
                construction_buttons[0]->setEnabled(true);
                construction_buttons[1]->setEnabled(true);
                construction_buttons[2]->setEnabled(true);
            };break;
        default: break;
        }});

    for(int temp=0;temp<54;temp++)
    {
        Point_disp* temp_disp=points_disp[temp];
        connect(build_small_house,&QPushButton::clicked,temp_disp,[temp_disp,build_small_house](){
            switch (current_player) {
                            case player_type::red_player:
                            if(players[0].get_owned_sources()[Terrain_type::lumber] <1 ||players[0].get_owned_sources()[Terrain_type::brick] <1||players[0].get_owned_sources()[Terrain_type::wool]<1 ||players[0].get_owned_sources()[Terrain_type::grain] <1)
                            {
                                current_player_state= player_state::idle;
                                return;
                            }break;
                            case player_type::green_player:
                            if(players[0].get_owned_sources()[Terrain_type::lumber] <1 ||players[0].get_owned_sources()[Terrain_type::brick] <1||players[0].get_owned_sources()[Terrain_type::wool]<1 ||players[0].get_owned_sources()[Terrain_type::grain] <1)
                            {
                                current_player_state= player_state::idle;
                                return;
                            }break;
                            case player_type::blue_player:
                            if(players[0].get_owned_sources()[Terrain_type::lumber] <1 ||players[0].get_owned_sources()[Terrain_type::brick] <1||players[0].get_owned_sources()[Terrain_type::wool]<1 ||players[0].get_owned_sources()[Terrain_type::grain] <1)
                            {
                                current_player_state= player_state::idle;
                                return;
                            }break;
                            default:return;break;
            }
            current_player_state=player_state::is_building_small_house;
            temp_disp->display_befor_decide();
        });
        connect(build_big_house,&QPushButton::clicked,temp_disp,[temp_disp,build_big_house](){
            switch (current_player) {
                            case player_type::red_player:
                            if(players[0].get_owned_sources()[Terrain_type::grain]<2||players[0].get_owned_sources()[Terrain_type::ore]<3)
                            {
                                current_player_state= player_state::idle;
                                return;
                            }break;
                            case player_type::green_player:
                            if(players[1].get_owned_sources()[Terrain_type::grain]<2||players[1].get_owned_sources()[Terrain_type::ore]<3)
                            {
                                current_player_state= player_state::idle;
                                return;
                            }break;
                            case player_type::blue_player:
                            if(players[2].get_owned_sources()[Terrain_type::grain]<2||players[2].get_owned_sources()[Terrain_type::ore]<3)
                            {
                                current_player_state= player_state::idle;
                                return;
                            }break;
                            default:return;break;
            }
            current_player_state=player_state::is_building_big_house;
            temp_disp->display_befor_decide();
        });
    }

    for(int temp=0;temp<54;temp++)
    {
        Point_disp* temp_disp=points_disp[temp];
        connect(temp_disp,&Point_disp::clicked,[temp_disp](){
            if(current_player_state==player_state::is_building_big_house)temp_disp->send_build_big_house_signal();
            else if(current_player_state==player_state::is_building_small_house)temp_disp->send_build_small_house_signal();
        });
    }

    for(int temp=0;temp<54;temp++)
    {
        Point_disp* p1=points_disp[temp];
        connect(p1,&Point_disp::has_built_small_house,[](){
            construction_buttons[0]->setEnabled(true);
            construction_buttons[1]->setEnabled(true);
            construction_buttons[2]->setEnabled(true);});
        for(int temp1=0;temp1<54;temp1++)
        {

            Point_disp* p2=points_disp[temp1];
            connect(p1,SIGNAL(has_built_small_house(int)),p2,SLOT(display_after_decide(int)));
        }
    }
    for(int temp=0;temp<54;temp++)
    {
        Point_disp* p1=points_disp[temp];
        connect(p1,&Point_disp::has_built_big_house,[](){
            construction_buttons[0]->setEnabled(true);
            construction_buttons[1]->setEnabled(true);
            construction_buttons[2]->setEnabled(true);});
        for(int temp1=0;temp1<54;temp1++)
        {

            Point_disp* p2=points_disp[temp1];
            connect(p1,SIGNAL(has_built_big_house(int)),p2,SLOT(display_after_decide(int)));
        }
    }
    //建路之后的显示更改
    for(int temp = 0; temp < 72; temp++)
    {
    connect(roads_disp[temp],&Road_disp::has_built_road,build_road,[build_road](){
        if(current_player==player_type::red_player)
        {
            build_road->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::road]));
        }
        else if(current_player==player_type::green_player)
        {

            build_road->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::road]));
        }
        else if(current_player==player_type::blue_player)
        {

            build_road->get_facility_remain()->setText(QString::number(players[2].get_constructions_remained()[constructon::road]));
        }
    });
    }

    vector<int>player_panel_ypos{758,626,494};
    for(int temp=0;temp<3;temp++)
    {
        QString temp_str;
        switch (temp) {
        case 0:
            temp_str=":/player_related/assets/player_related/player_bg_red.png";
            break;
        case 1:
            temp_str=":/player_related/assets/player_related/player_bg_green.png";
            break;
        case 2:
            temp_str=":/player_related/assets/player_related/player_bg_blue.png";
            break;
        }
        QLabel* bk_label=new QLabel(this);//背景板（白色渐变的圆角矩形）
        bk_label->resize(355,127);
        QPixmap bk_pic(":/player_related/assets/player_related/bg_section1.png");
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
        QPixmap man_pic(":/player_related/assets/player_related/icon_player.png");
        man_pic=man_pic.scaled(75,75);
        man_label->setPixmap(man_pic);
        man_label->move(1170,player_panel_ypos[temp]+32);

        QLabel* ribbon_label=new QLabel(this);//玩家得分背景栏（绸缎）
        ribbon_label->resize(75,21);
        QPixmap ribbon_pic(":/player_related/assets/player_related/ribbon_small.png");
        ribbon_pic=ribbon_pic.scaled(75,21);
        ribbon_label->setPixmap(ribbon_pic);
        ribbon_label->move(1172,player_panel_ypos[temp]+99);

        QFont ft("Microsoft YaHei", 10);
        ft.setBold(true);



        QLabel* rescard_label=new QLabel(this);//玩家手上牌数栏
        QPixmap rescard_pic(":/player_related/assets/player_related/card_rescardback.png");
        rescard_pic=rescard_pic.scaled(74,103);
        rescard_label->resize(74,103);
        rescard_label->setPixmap(rescard_pic);
        rescard_label->move(1267,player_panel_ypos[temp]+13);

        QLabel* rescard_corner=new QLabel(this);
        QPixmap rescard_corner_pic(":/player_related/assets/player_related/card_badge_background.png");
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
        QPixmap longest_road_pic(":/player_related/assets/player_related/icon_longest_road.png");
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
        for(int road_temp = 0; road_temp < 72; road_temp++)
        {
        connect(roads_disp[road_temp],&Road_disp::has_built_road,longest_road_number_label,[longest_road_number_label,temp](){
            longest_road_number_label->setText(QString::number(players[temp].caculate_road_length()));
            bool past_longest = players[temp].get_longest();
            bool set_longest = true;
            if(players[temp].caculate_road_length() < 5)
            {
                set_longest = false;
                players[temp].set_is_longest(set_longest);
                return;
            }
            for(int comp = 0; comp < 3; comp++)
            {
                if (comp == temp)
                    continue;
                if (players[comp].caculate_road_length()>=players[temp].caculate_road_length())
                    set_longest = false;
            }

                players[temp].set_is_longest(set_longest);
                if(!past_longest && set_longest)
                {
                    QMessageBox::about(NULL, "Yay!", "<h2>You've won longest road!</h2>");
                }

            return;
        });
        }
        for(int point_temp = 0; point_temp < 54; point_temp++)
        {
        connect(points_disp[point_temp],&Point_disp::has_built_small_house,longest_road_number_label,[longest_road_number_label,temp](){
            longest_road_number_label->setText(QString::number(players[temp].caculate_road_length()));
            bool past_longest = players[temp].get_longest();
            bool set_longest = true;
            if(players[temp].caculate_road_length() < 5)
            {
                set_longest = false;
                players[temp].set_is_longest(set_longest);
                return;
            }
            for(int comp = 0; comp < 3; comp++)
            {
                if (comp == temp)
                    continue;
                if (players[comp].caculate_road_length()>=players[temp].caculate_road_length())
                    set_longest = false;
            }
                players[temp].set_is_longest(set_longest);
                if(!past_longest && set_longest)
                {
                    QMessageBox::about(NULL, "Yay!", "<h2>You've won longest road!</h2>");
                }

            return;
        });
        }
        longest_road_number_labels.push_back(longest_road_number_label);

        QLabel* score_label=new QLabel(this);//玩家分数显示栏
        score_label->resize(75,21);
        score_label->move(1172,player_panel_ypos[temp]+99);
        score_label->setFont(ft);
        score_label->setAlignment(Qt::AlignCenter);
        score_label->setText("0");
        for(int road_temp = 0; road_temp < 72; road_temp++)
        {
        connect(roads_disp[road_temp],&Road_disp::has_built_road,score_label,[score_label,temp,this,sea_shore_label](){
            score_label->setText(QString::number(players[temp].caculate_score()));
            if(players[temp].caculate_score() >=8)
            {
                QMessageBox msgBox;
                string player_name;
                if(temp == 0)
                    msgBox.setText("Player red has won the game!");
                else if (temp == 1)
                    msgBox.setText("Player green has won the game!");
                else if (temp == 2)
                    msgBox.setText("Player blue has won the game!");

                msgBox.setInformativeText("Do you want to restart or quit the game?");
                QPushButton* restartButton = new QPushButton("restart");
                QPushButton* quitButton = new QPushButton("quit");
                msgBox.addButton(restartButton,QMessageBox::YesRole);
                msgBox.addButton(quitButton,QMessageBox::NoRole);
                connect(restartButton,&QPushButton::clicked,[this](){slotReboot();});
                connect(quitButton,&QPushButton::clicked,[this](){this->close();});
                msgBox.exec();
            }
        });
        }
        for(int point_temp = 0; point_temp < 54; point_temp++)
        {
        connect(points_disp[point_temp],&Point_disp::has_built_small_house,score_label,[score_label,temp,this,sea_shore_label](){
            score_label->setText(QString::number(players[temp].caculate_score()));
            if(players[temp].caculate_score() >=8)
            {
                QMessageBox msgBox;
                string player_name;
                if(temp == 0)
                    msgBox.setText("Player red has won the game!");
                else if (temp == 1)
                    msgBox.setText("Player green has won the game!");
                else if (temp == 2)
                    msgBox.setText("Player blue has won the game!");

                msgBox.setInformativeText("Do you want to restart or quit the game?");
                QPushButton* restartButton = new QPushButton("restart");
                QPushButton* quitButton = new QPushButton("quit");
                msgBox.addButton(restartButton,QMessageBox::YesRole);
                msgBox.addButton(quitButton,QMessageBox::NoRole);
                connect(restartButton,&QPushButton::clicked,[this](){slotReboot();});
                connect(quitButton,&QPushButton::clicked,[this](){this->close();});
                msgBox.exec();
            }
        });
        connect(points_disp[point_temp],&Point_disp::has_built_big_house,score_label,[score_label,temp,this,sea_shore_label](){
            score_label->setText(QString::number(players[temp].caculate_score()));
            if(players[temp].caculate_score() >=8)
            {
                QMessageBox msgBox;
                string player_name;
                if(temp == 0)
                    msgBox.setText("Player red has won the game!");
                else if (temp == 1)
                    msgBox.setText("Player green has won the game!");
                else if (temp == 2)
                    msgBox.setText("Player blue has won the game!");

                msgBox.setInformativeText("Do you want to restart or quit the game?");
                QPushButton* restartButton = new QPushButton("restart");
                QPushButton* quitButton = new QPushButton("quit");
                msgBox.addButton(restartButton,QMessageBox::YesRole);
                msgBox.addButton(quitButton,QMessageBox::NoRole);
                connect(restartButton,&QPushButton::clicked,[this](){slotReboot();});
                connect(quitButton,&QPushButton::clicked,[this](){this->close();});
                msgBox.exec();
            }
        });
        }
        score_labels.push_back(score_label);
    }



    //游戏开局阶段代码

    construction_buttons[0]->setDisabled(true);
    construction_buttons[1]->setDisabled(true);
    construction_buttons[2]->setDisabled(true);
    end_turn_button->setDisabled(true);
    diceButton->setDisabled(true);
    tradeButton->setDisabled(true);
    current_player_state=player_state::is_building_small_house;
    current_player=player_type::red_player;
    current_player_index=0;
    bk_labels[1]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_player_inactive1.png"));
    bk_labels[2]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_player_inactive1.png"));
    source_card_number[0]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::lumber]));
    source_card_number[1]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::grain]));
    source_card_number[2]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::brick]));
    source_card_number[3]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::wool]));
    source_card_number[4]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::ore]));
    for(int temp=0;temp<54;temp++)
    {
        Point_disp* temp_disp=points_disp[temp];
        connect(temp_disp,&Point_disp::game_status_updated,this,[](){
            switch (game_status) {
            case 1:
            {
                current_player_state=player_state::is_building_road;
                for(int temp=0;temp<72;temp++)
                    roads_disp[temp]->display_before_decide_in_opening_status(players[0].get_small_house_owned()[0]);
                break;
            }
            case 3:
            {
                current_player_index=1;
                current_player=player_type::green_player;
                current_player_state=player_state::is_building_road;
                for(int temp=0;temp<72;temp++)
                    roads_disp[temp]->display_before_decide_in_opening_status(players[1].get_small_house_owned()[0]);
                break;
            }
            case 5:
            {
                current_player_index=2;
                current_player=player_type::blue_player;
                current_player_state=player_state::is_building_road;
                for(int temp=0;temp<72;temp++)
                    roads_disp[temp]->display_before_decide_in_opening_status(players[2].get_small_house_owned()[0]);
                break;
            }
            case 7:
            {
                current_player_index=2;
                current_player=player_type::blue_player;
                current_player_state=player_state::is_building_road;
                int p_index=players[2].get_small_house_owned()[1];
                vector<int> t_index=points[p_index].get_index_for_neighbour_terrain();
                for(vector<int>::size_type temp=0;temp<t_index.size();temp++)//获取资源
                {
                    players[2].get_sources({{terrains[t_index[temp]].get_terrain_type(),1}});
                }
                source_card_number[0]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::lumber]));
                source_card_number[1]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::grain]));
                source_card_number[2]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::brick]));
                source_card_number[3]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::wool]));
                source_card_number[4]->setText(QString::number(players[2].get_owned_sources()[Terrain_type::ore]));
                rescard_number_labels[2]->setText(QString::number(players[2].get_total_sources()));
                for(int temp=0;temp<72;temp++)
                    roads_disp[temp]->display_before_decide_in_opening_status(players[2].get_small_house_owned()[1]);
                break;
            }
            case 9:
            {
                current_player_index=1;
                current_player=player_type::green_player;
                current_player_state=player_state::is_building_road;
                int p_index=players[1].get_small_house_owned()[1];
                vector<int> t_index=points[p_index].get_index_for_neighbour_terrain();
                for(vector<int>::size_type temp=0;temp<t_index.size();temp++)//获取资源
                {
                    players[1].get_sources({{terrains[t_index[temp]].get_terrain_type(),1}});
                }
                source_card_number[0]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::lumber]));
                source_card_number[1]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::grain]));
                source_card_number[2]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::brick]));
                source_card_number[3]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::wool]));
                source_card_number[4]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::ore]));
                rescard_number_labels[1]->setText(QString::number(players[1].get_total_sources()));
                for(int temp=0;temp<72;temp++)
                    roads_disp[temp]->display_before_decide_in_opening_status(players[1].get_small_house_owned()[1]);
                break;
            }
            case 11:
            {
                current_player_index=0;
                current_player=player_type::red_player;
                current_player_state=player_state::is_building_road;
                int p_index=players[0].get_small_house_owned()[1];
                vector<int> t_index=points[p_index].get_index_for_neighbour_terrain();
                for(vector<int>::size_type temp=0;temp<t_index.size();temp++)//获取资源
                {
                    players[0].get_sources({{terrains[t_index[temp]].get_terrain_type(),1}});
                }
                source_card_number[0]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::lumber]));
                source_card_number[1]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::grain]));
                source_card_number[2]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::brick]));
                source_card_number[3]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::wool]));
                source_card_number[4]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::ore]));
                rescard_number_labels[0]->setText(QString::number(players[0].get_total_sources()));
                for(int temp=0;temp<72;temp++)
                    roads_disp[temp]->display_before_decide_in_opening_status(players[0].get_small_house_owned()[1]);
                break;
            }
            default: break;
            }
        });
    }
    for(int temp=0;temp<72;temp++)
    {
        Road_disp* temp_disp=roads_disp[temp];
        connect(temp_disp,&Road_disp::game_status_updated,this,[diceButton](){
            switch (game_status) {
            case 2:
            {
                bk_labels[1]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_section1.png"));
                bk_labels[0]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_player_inactive1.png"));
                current_player=player_type::green_player;
                current_player_index=1;
                current_player_state=player_state::is_building_small_house;
                for(int temp=0;temp<54;temp++)
                    points_disp[temp]->display_before_decide_in_opening_status();
                construction_buttons[0]->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::road]));
                construction_buttons[1]->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::small_house]));
                construction_buttons[2]->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::big_house]));
                break;
            }
            case 4:
            {
                bk_labels[2]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_section1.png"));
                bk_labels[1]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_player_inactive1.png"));
                current_player=player_type::blue_player;
                current_player_index=2;
                current_player_state=player_state::is_building_small_house;
                for(int temp=0;temp<54;temp++)
                    points_disp[temp]->display_before_decide_in_opening_status();
                construction_buttons[0]->get_facility_remain()->setText(QString::number(players[2].get_constructions_remained()[constructon::road]));
                construction_buttons[1]->get_facility_remain()->setText(QString::number(players[2].get_constructions_remained()[constructon::small_house]));
                construction_buttons[2]->get_facility_remain()->setText(QString::number(players[2].get_constructions_remained()[constructon::big_house]));
                break;
            }
            case 6:
            {
                current_player=player_type::blue_player;
                current_player_index=2;
                current_player_state=player_state::is_building_small_house;
                for(int temp=0;temp<54;temp++)
                    points_disp[temp]->display_before_decide_in_opening_status();
                break;
            }
            case 8:
            {
                bk_labels[1]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_section1.png"));
                bk_labels[2]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_player_inactive1.png"));
                current_player=player_type::green_player;
                current_player_index=1;
                current_player_state=player_state::is_building_small_house;
                for(int temp=0;temp<54;temp++)
                    points_disp[temp]->display_before_decide_in_opening_status();
                construction_buttons[0]->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::road]));
                construction_buttons[1]->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::small_house]));
                construction_buttons[2]->get_facility_remain()->setText(QString::number(players[1].get_constructions_remained()[constructon::big_house]));
                source_card_number[0]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::lumber]));
                source_card_number[1]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::grain]));
                source_card_number[2]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::brick]));
                source_card_number[3]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::wool]));
                source_card_number[4]->setText(QString::number(players[1].get_owned_sources()[Terrain_type::ore]));
                break;
            }
            case 10:
            {
                bk_labels[0]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_section1.png"));
                bk_labels[1]->setPixmap(QPixmap(":/player_related/assets/player_related/bg_player_inactive1.png"));
                current_player=player_type::red_player;
                current_player_index=0;
                current_player_state=player_state::is_building_small_house;
                for(int temp=0;temp<54;temp++)
                    points_disp[temp]->display_before_decide_in_opening_status();
                construction_buttons[0]->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::road]));
                construction_buttons[1]->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::small_house]));
                construction_buttons[2]->get_facility_remain()->setText(QString::number(players[0].get_constructions_remained()[constructon::big_house]));
                source_card_number[0]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::lumber]));
                source_card_number[1]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::grain]));
                source_card_number[2]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::brick]));
                source_card_number[3]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::wool]));
                source_card_number[4]->setText(QString::number(players[0].get_owned_sources()[Terrain_type::ore]));
                break;
            }
            case 12:
            {
                current_player=player_type::red_player;
                current_player_index=0;
                current_player_state=player_state::idle;
                is_in_normal_round=true;
                diceButton->setDisabled(false);
            }
            }
        });
    }
    for(int temp=0;temp<54;temp++)
        points_disp[temp]->display_before_decide_in_opening_status();

    QLabel *opening_bg=new QLabel(this);//开始界面背景
    QPixmap opening_pic(":/background/assets/background/background.png");
    opening_pic=opening_pic.scaled(1508,914);
    opening_bg->resize(1508,914);
    opening_bg->setPixmap(opening_pic);
    opening_bg->move(0,0);
    opening_bg->show();
    QLabel* opening_logo=new QLabel(this);
    QPixmap opening_logo_pic(":/background/assets/background/logo.png");
    opening_logo->resize(500,250);
    opening_logo->setPixmap(opening_logo_pic);
    opening_logo->move(504,150);
    opening_logo->show();
    QLabel* printing_bg=new QLabel(this);
    QPixmap printing_pic(":/background/assets/background/page_bg.png");
    printing_bg->resize(1508,914);
    printing_bg->setPixmap(printing_pic);
    printing_bg->move(0,0);
    printing_bg->show();
    QPushButton* normal_game_button=new QPushButton(this);
    QPushButton* advanced_game_button=new QPushButton(this);
    QPushButton* quit_game_button=new QPushButton(this);
    normal_game_button->resize(270,40);
    normal_game_button->setIconSize(QSize(270,40));
    normal_game_button->setIcon(QIcon(QPixmap(":/background/assets/background/classic_mode_button.png")));
    normal_game_button->setFlat(true);
    normal_game_button->setStyleSheet(("border:none;"));
    normal_game_button->move(619,500);
    normal_game_button->show();
    connect(normal_game_button,&QPushButton::clicked,[opening_bg,opening_logo,printing_bg,normal_game_button,quit_game_button,advanced_game_button,this](){
        opening_bg->hide();
        opening_logo->hide();
        printing_bg->hide();
        normal_game_button->setDisabled(true);
        normal_game_button->hide();
        quit_game_button->setDisabled(true);
        quit_game_button->hide();
        advanced_game_button->setDisabled(true);
        advanced_game_button->hide();
        music->play();
    });
    advanced_game_button->resize(270,40);
    advanced_game_button->setIconSize(QSize(270,40));
    advanced_game_button->setIcon(QIcon(QPixmap(":/background/assets/background/advanced_mode.png")));
    advanced_game_button->setFlat(true);
    advanced_game_button->setStyleSheet(("border:none;"));
    advanced_game_button->move(619,600);
    advanced_game_button->show();
    connect(advanced_game_button,&QPushButton::clicked,[opening_bg,opening_logo,printing_bg,normal_game_button,quit_game_button,advanced_game_button,sea_shore_label,this](){
        opening_bg->hide();
        opening_logo->hide();
        printing_bg->hide();
        normal_game_button->setDisabled(true);
        normal_game_button->hide();
        quit_game_button->setDisabled(true);
        quit_game_button->hide();
        advanced_game_button->setDisabled(true);
        advanced_game_button->hide();
        is_sea_shore_mode=true;
        sea_shore_label->show();
        music->play();
    });
    quit_game_button->resize(270,40);
    quit_game_button->setIconSize(QSize(270,40));
    quit_game_button->setIcon(QIcon(QPixmap(":/background/assets/background/quit_bg.png")));
    quit_game_button->setFlat(true);
    quit_game_button->setStyleSheet(("border:none;"));
    quit_game_button->move(630,700);
    quit_game_button->show();
    connect(quit_game_button,&QPushButton::clicked,this,[this](){this->close();});



}

MainWindow::~MainWindow()
{
    delete ui;
    points_view = {};
    points_scene = {};
    roads_view = {};
    roads_scene = {};
    source_card_number = {};//顺序存放lumber grain brick wool ore的资源数QLabel
    score_labels = {};//顺序存放red green blue玩家的分数QLabel
    rescard_number_labels = {};//顺序存放red green blue玩家的手上资源牌总数QLabel
    longest_road_number_labels = {};//顺序存放　red green blue 玩家的路的长度QLabel
    players = {};//顺序存放red green blue玩家对象
    bk_labels = {};//顺序存放red green blue玩家的面板显示label
    construction_buttons = {};//顺序存放建路、建小房子、建大房子按钮
    points = {};
    points_disp = {};
    roads = {};
    roads_disp = {};
    current_player=player_type::red_player;
    current_player_state=player_state::idle;
    game_status=0;
}

