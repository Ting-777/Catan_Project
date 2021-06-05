#include "trade.h"
#include "ui_trade.h"
#include "player.h"
#include "player_enum.h"
#include "terrain_enum.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <iostream>
using namespace std;

extern player_type current_player;
extern int current_player_index;
extern vector<Player>players;

Trade::Trade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Trade)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(759,580));
    setWindowTitle("Trade");
    setWindowIcon(QIcon(QPixmap(":/player_related/assets/player_related/icon_trade.png")));
    //背景
    QGraphicsScene* bgscene=new QGraphicsScene(this);
    bgscene->addPixmap(QPixmap(":/background/assets/background/trade_bg.png").scaled(759,580));
    QGraphicsView* bgview=new QGraphicsView(this);
    bgview->resize(759,580);
    bgview->move(0,0);
    bgview->setScene(bgscene);
    bgview->show();
    int playerIndex = current_player_index;
    bankRules.push_back(players[playerIndex].get_trade_with_bank_rule().find(Terrain_type::brick)->second);
    bankRules.push_back(players[playerIndex].get_trade_with_bank_rule().find(Terrain_type::grain)->second);
    bankRules.push_back(players[playerIndex].get_trade_with_bank_rule().find(Terrain_type::lumber)->second);
    bankRules.push_back(players[playerIndex].get_trade_with_bank_rule().find(Terrain_type::ore)->second);
    bankRules.push_back(players[playerIndex].get_trade_with_bank_rule().find(Terrain_type::wool)->second);
    for(int i = 0; i < 5; i++)
    {
        QLabel* label = new QLabel(this);
        label->setText(QString::number(bankRules[i])+":1");
        label->move(170 + 123 * i, 200);
        label->resize(50,18);
        QFont ft;
        ft.setPointSize(14);
        label->setFont(ft);
        label->show();
    }

    //资源加减
    for(int i = 0; i < 5; i++)
    {
        QLabel* label = new QLabel(this);
        label->setText(QString::number(give[i]));
        label->move(180 + 123 * i, 239);
        label->resize(50,18);
        QFont ft;
        ft.setPointSize(15);
        label->setFont(ft);
        label->show();
        numLabels.push_back(label);
        TradePlus* tradePlus = new TradePlus(true,i,210+123*i,238,this);
        tradePlus->show();
        connect(tradePlus,&TradePlus::clicked,this,[tradePlus,this](){this->plus(tradePlus->is_give,tradePlus->n);});
        pluses.push_back(tradePlus);
        TradeMinus* tradeMinus = new TradeMinus(true,i,140+123*i,238,this);
        tradeMinus->show();
        connect(tradeMinus,&TradeMinus::clicked,this,[tradeMinus,this](){this->minus(tradeMinus->is_give,tradeMinus->n);});
        minuses.push_back(tradeMinus);

    }
    for(int i = 0; i < 5; i++)
    {
        QLabel* label = new QLabel(this);
        label->setText(QString::number(want[i]));
        label->move(180 + 123 * i, 316);
        label->resize(50,18);
        QFont ft;
        ft.setPointSize(15);
        label->setFont(ft);
        label->show();
        numLabels.push_back(label);
        TradePlus* tradePlus = new TradePlus(false,i,210+123*i,315,this);
        tradePlus->show();
        connect(tradePlus,&TradePlus::clicked,this,[tradePlus,this](){this->plus(tradePlus->is_give,tradePlus->n);});
        pluses.push_back(tradePlus);
        TradeMinus* tradeMinus = new TradeMinus(false,i,140+123*i,315,this);
        tradeMinus->show();
        connect(tradeMinus,&TradeMinus::clicked,this,[tradeMinus,this](){this->minus(tradeMinus->is_give,tradeMinus->n);});
        minuses.push_back(tradeMinus);
    }
    //银行按钮
    bankButton = new QPushButton(this);
    bankButton->move(36,369);
    bankButton->resize(687,67);
    bankButton->setText("Trade with the Bank");
    bankButton->setStyleSheet(
                   "QPushButton{"
                   "background-color:rgba(0,0,0,30);"      //背景色
                   "border-style:outset;"                  //边框样式（inset/outset）
                   "border-width:4px;"                     //边框宽度像素
                   "border-radius:10px;"                   //边框圆角半径像素
                   "border-color:rgba(255,255,255,30);"    //边框颜色
                   "font:bold 18px;"                       //字体，字体大小
                   "color:rgba(0,0,0,200);"                //字体颜色
                   "padding:6px;"                          //填衬
                   "}"
                   //鼠标按下样式
                   "QPushButton:pressed{"
                   "background-color:rgba(0,0,0,200);"
                   "border-color:rgba(255,255,255,30);"
                   "border-style:inset;"
                   "color:rgba(0,0,0,200);"
                   "}"
                   //鼠标悬停样式
                   "QPushButton:hover{"
                   "background-color:rgba(0,0,0,100);"
                   "border-color:rgba(255,255,255,200);"
                   "color:rgba(0,0,0,200);"
                   "}");
    connect(bankButton,&QPushButton::clicked,this,[this](){this->trade_with_bank();});
    bankButton->show();
    //接受交易按钮
    QPushButton *blueButton = new QPushButton(this);
    blueButton->move(134,460);
    blueButton->resize(123,80);
    blueButton->setText("Accept");
    blueButton->setStyleSheet(
                   "QPushButton{"
                   "background-color:rgba(100,100,255,30);"//背景色
                   "border-style:outset;"                  //边框样式（inset/outset）
                   "border-width:4px;"                     //边框宽度像素
                   "border-radius:10px;"                   //边框圆角半径像素
                   "border-color:rgba(255,255,255,30);"    //边框颜色
                   "font:bold 18px;"                       //字体，字体大小
                   "color:rgba(0,0,0,200);"                //字体颜色
                   "padding:6px;"                          //填衬
                   "}"
                   //鼠标按下样式
                   "QPushButton:pressed{"
                   "background-color:rgba(100,100,255,200);"
                   "border-color:rgba(255,255,255,30);"
                   "border-style:inset;"
                   "color:rgba(0,0,0,200);"
                   "}"
                   //鼠标悬停样式
                   "QPushButton:hover{"
                   "background-color:rgba(100,100,255,100);"
                   "border-color:rgba(255,255,255,200);"
                   "color:rgba(0,0,0,200);"
                   "}");
    connect(blueButton,&QPushButton::clicked,this,[this](){this->trade_with_player(player_type::blue_player);});
    blueButton->show();
    acceptButtons.push_back(blueButton);
    QPushButton *redButton = new QPushButton(this);
    redButton->move(368,460);
    redButton->resize(123,80);
    redButton->setText("Accept");
    redButton->setStyleSheet(
                   "QPushButton{"
                   "background-color:rgba(225,100,100,30);"//背景色
                   "border-style:outset;"                  //边框样式（inset/outset）
                   "border-width:4px;"                     //边框宽度像素
                   "border-radius:10px;"                   //边框圆角半径像素
                   "border-color:rgba(255,255,255,30);"    //边框颜色
                   "font:bold 18px;"                       //字体，字体大小
                   "color:rgba(0,0,0,200);"                //字体颜色
                   "padding:6px;"                          //填衬
                   "}"
                   //鼠标按下样式
                   "QPushButton:pressed{"
                   "background-color:rgba(225,100,100,200);"
                   "border-color:rgba(255,255,255,30);"
                   "border-style:inset;"
                   "color:rgba(0,0,0,200);"
                   "}"
                   //鼠标悬停样式
                   "QPushButton:hover{"
                   "background-color:rgba(225,100,100,100);"
                   "border-color:rgba(255,255,255,200);"
                   "color:rgba(0,0,0,200);"
                   "}");
    connect(redButton,&QPushButton::clicked,this,[this](){this->trade_with_player(player_type::red_player);});
    redButton->show();
    acceptButtons.push_back(redButton);
    QPushButton *greenButton = new QPushButton(this);
    greenButton->move(602,460);
    greenButton->resize(123,80);
    greenButton->setText("Accept");
    greenButton->setStyleSheet(
                   "QPushButton{"
                   "background-color:rgba(100,255,100,30);"//背景色
                   "border-style:outset;"                  //边框样式（inset/outset）
                   "border-width:4px;"                     //边框宽度像素
                   "border-radius:10px;"                   //边框圆角半径像素
                   "border-color:rgba(255,255,255,30);"    //边框颜色
                   "font:bold 18px;"                       //字体，字体大小
                   "color:rgba(0,0,0,200);"                //字体颜色
                   "padding:6px;"                          //填衬
                   "}"
                   //鼠标按下样式
                   "QPushButton:pressed{"
                   "background-color:rgba(100,255,100,200);"
                   "border-color:rgba(255,255,255,30);"
                   "border-style:inset;"
                   "color:rgba(0,0,0,200);"
                   "}"
                   //鼠标悬停样式
                   "QPushButton:hover{"
                   "background-color:rgba(100,255,100,100);"
                   "border-color:rgba(255,255,255,200);"
                   "color:rgba(0,0,0,200);"
                   "}");
    connect(greenButton,&QPushButton::clicked,this,[this](){this->trade_with_player(player_type::green_player);});
    greenButton->show();
    acceptButtons.push_back(greenButton);
    playerType = current_player;
    map<Terrain_type,int> playerResourcesMap;
    if(playerType == player_type::red_player) playerResourcesMap = players[0].get_owned_sources();
    else if (playerType == player_type::green_player) playerResourcesMap = players[1].get_owned_sources();
    else if (playerType == player_type::blue_player) playerResourcesMap = players[2].get_owned_sources();
    playerResources.push_back(playerResourcesMap.find(Terrain_type::brick)->second);
    playerResources.push_back(playerResourcesMap.find(Terrain_type::grain)->second);
    playerResources.push_back(playerResourcesMap.find(Terrain_type::lumber)->second);
    playerResources.push_back(playerResourcesMap.find(Terrain_type::ore)->second);
    playerResources.push_back(playerResourcesMap.find(Terrain_type::wool)->second);
}

Trade::~Trade()
{
    delete ui;
}

void Trade::plus(bool is_give, int i)
{
    if(is_give)
    {
        if(give[i] < playerResources[i])
        {
            give[i]++;
            numLabels[i]->setText(QString::number(give[i]));
        }
    }
    else
    {
        want[i]++;
        numLabels[i+5]->setText(QString::number(want[i]));
    }
}

void Trade::minus(bool is_give, int i)
{
    if(is_give)
    {
        if(give[i] > 0)
        {
            give[i]--;
            numLabels[i]->setText(QString::number(give[i]));
        }
    }
    else
    {
        if(want[i] > 0)
        {
            want[i]--;
            numLabels[i+5]->setText(QString::number(want[i]));
        }
    }
}

void Trade::trade_with_bank()
{
    //防止零换零
    bool zeroFlag = true;
    for (auto it : give)
        if(it != 0)
        {
            zeroFlag = false;
            break;
        }
    if (zeroFlag == true)
        for (auto it : want)
            if(it != 0)
            {
                zeroFlag = false;
                break;
            }
    if(zeroFlag == true)
    {
        QMessageBox::about(NULL, "Warning", "<h2>You cannot trade nothing for nothing!</h2>");
        return;
    }
    //检查比例
    vector<int> givetemp = give;
    for(int i = 0; i < 5; i++)
    {
        int ruletemp = bankRules[i];
        for(int j = 0; j < want[i]; j++)
        {
            vector<int> giveabletemp = {0,0,0,0,0};
            for(int k = 0; k < 5; k++)
            {
                if (givetemp[k] >= ruletemp) giveabletemp[k] = givetemp[k];
            }
            bool isZerotemp = true;
            for(auto l:giveabletemp)
            {
                if (l != 0)
                {
                    isZerotemp = false;
                    break;
                }
            }
            if(isZerotemp == true)
            {
                QMessageBox::about(NULL, "Warning", "<h2>The ratio is incorrect!</h2>");
                return;
            }
            else
            {
                int min = 9999;
                int minIndex = -1;
                for(int m = 0; m < 5; m++)
                {
                    if(giveabletemp[m] != 0 && giveabletemp[m] < min)
                    {
                        minIndex = m;
                        min = giveabletemp[m];
                    }
                }
                if(minIndex >= 0)
                    givetemp[minIndex] -= ruletemp;
            }
        }
    }
    bool isZerotemp = true;
    for(auto l:givetemp)
    {
        if (l != 0)
        {
            isZerotemp = false;
            break;
        }
    }
    if(isZerotemp == false)
    {
        QMessageBox::about(NULL, "Warning", "<h2>The ratio is incorrect!</h2>");
        return;
    }

    map<Terrain_type,int> giveMap;
    map<Terrain_type,int> wantMap;
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::brick,give[0]));
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::grain,give[1]));
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::lumber,give[2]));
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::ore,give[3]));
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::wool,give[4]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::brick,want[0]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::grain,want[1]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::lumber,want[2]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::ore,want[3]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::wool,want[4]));
    if(playerType == player_type::red_player) players[0].exchange_sources(giveMap,wantMap);
    else if (playerType == player_type::green_player) players[1].exchange_sources(giveMap,wantMap);
    else if (playerType == player_type::blue_player) players[2].exchange_sources(giveMap,wantMap);
    reject();
}

void Trade::trade_with_player(player_type counterpartType)
{
    //不能零换零
    bool zeroFlag = true;
    for (auto it : give)
        if(it != 0)
        {
            zeroFlag = false;
            break;
        }
    if (zeroFlag == true)
        for (auto it : want)
            if(it != 0)
            {
                zeroFlag = false;
                break;
            }
    if(zeroFlag == true)
    {
        QMessageBox::about(NULL, "Warning", "<h2>You cannot trade nothing for nothing!</h2>");
        return;
    }
    //不能自己与自己交易
    if (playerType == counterpartType)
    {
        QMessageBox::about(NULL, "Warning", "<h2>You cannot trade with yourself!</h2>");
        return;
    }
    //检查另一方资源是否足够
    map<Terrain_type,int> counterResourcesMap;
    vector<int> counterResources;
    if(counterpartType == player_type::red_player) counterResourcesMap = players[0].get_owned_sources();
    else if (counterpartType == player_type::green_player) counterResourcesMap = players[1].get_owned_sources();
    else if (counterpartType == player_type::blue_player) counterResourcesMap = players[2].get_owned_sources();
    counterResources.push_back(counterResourcesMap.find(Terrain_type::brick)->second);
    counterResources.push_back(counterResourcesMap.find(Terrain_type::grain)->second);
    counterResources.push_back(counterResourcesMap.find(Terrain_type::lumber)->second);
    counterResources.push_back(counterResourcesMap.find(Terrain_type::ore)->second);
    counterResources.push_back(counterResourcesMap.find(Terrain_type::wool)->second);
    for (int i = 0; i < 5; i++)
        if(want[i] > counterResources[i])
        {
            QMessageBox::about(NULL, "Warning", "<h2>You don't have sufficient resources to trade!</h2>");
            return;
        }
    map<Terrain_type,int> giveMap;
    map<Terrain_type,int> wantMap;
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::brick,give[0]));
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::grain,give[1]));
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::lumber,give[2]));
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::ore,give[3]));
    giveMap.insert(pair<Terrain_type,int> (Terrain_type::wool,give[4]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::brick,want[0]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::grain,want[1]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::lumber,want[2]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::ore,want[3]));
    wantMap.insert(pair<Terrain_type,int> (Terrain_type::wool,want[4]));
    if(playerType == player_type::red_player) players[0].exchange_sources(giveMap,wantMap);
    else if (playerType == player_type::green_player) players[1].exchange_sources(giveMap,wantMap);
    else if (playerType == player_type::blue_player) players[2].exchange_sources(giveMap,wantMap);
    if(counterpartType == player_type::red_player) players[0].exchange_sources(wantMap,giveMap);
    else if (counterpartType == player_type::green_player) players[1].exchange_sources(wantMap,giveMap);
    else if (counterpartType == player_type::blue_player) players[2].exchange_sources(wantMap,giveMap);
    reject();
}
