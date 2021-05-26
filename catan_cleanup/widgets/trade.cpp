#include "trade.h"
#include "ui_trade.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <iostream>
using namespace std;
Trade::Trade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Trade)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(759,580));
    setWindowTitle("Trade");
    setWindowIcon(QIcon(QPixmap(":/player_related/picture_sources/player_related/icon_trade.png")));
    //背景
    QGraphicsScene* bgscene=new QGraphicsScene(this);
    bgscene->addPixmap(QPixmap(":/background/picture_sources/background/trade_bg.png").scaled(759,580));
    QGraphicsView* bgview=new QGraphicsView(this);
    bgview->resize(759,580);
    bgview->move(0,0);
    //bgview->setStyleSheet("padding:0px;border:0px;background: transparent");
    bgview->setScene(bgscene);
    bgview->show();
    //资源加减
    for(int i = 0; i < 5; i++)
    {
        QLabel* label = new QLabel(this);
        label->setText(QString::number(give[i]));
        label->move(180 + 123 * i, 239);
        label->resize(50,18);
        QFont ft;
        ft.setPointSize(17);
        label->setFont(ft);
        label->show();
        numLabels.push_back(label);
        TradePlus* tradePlus = new TradePlus(true,i,210+123*i,238,this);
        tradePlus->show();
        connect(tradePlus,&TradePlus::clicked,[tradePlus,this](){this->plus(tradePlus->is_give,tradePlus->n);});
        pluses.push_back(tradePlus);
        TradeMinus* tradeMinus = new TradeMinus(true,i,140+123*i,238,this);
        tradeMinus->show();
        connect(tradeMinus,&TradeMinus::clicked,[tradeMinus,this](){this->minus(tradeMinus->is_give,tradeMinus->n);});
        minuses.push_back(tradeMinus);

    }
    for(int i = 0; i < 5; i++)
    {
        QLabel* label = new QLabel(this);
        label->setText(QString::number(want[i]));
        label->move(180 + 123 * i, 316);
        label->resize(50,18);
        QFont ft;
        ft.setPointSize(17);
        label->setFont(ft);
        label->show();
        numLabels.push_back(label);
        TradePlus* tradePlus = new TradePlus(false,i,210+123*i,315,this);
        tradePlus->show();
        connect(tradePlus,&TradePlus::clicked,[tradePlus,this](){this->plus(tradePlus->is_give,tradePlus->n);});
        pluses.push_back(tradePlus);
        TradeMinus* tradeMinus = new TradeMinus(false,i,140+123*i,315,this);
        tradeMinus->show();
        connect(tradeMinus,&TradeMinus::clicked,[tradeMinus,this](){this->minus(tradeMinus->is_give,tradeMinus->n);});
        minuses.push_back(tradeMinus);
    }
    //银行按钮
    bankButton = new QPushButton(this);
    bankButton->move(36,369);
    bankButton->resize(687,67);
    bankButton->setText("Trade with the Bank (4:1)");
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
    connect(bankButton,&QPushButton::clicked,[this](){this->trade_with_bank();});
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
    connect(blueButton,&QPushButton::clicked,[this](){this->trade_with_player(player_type::blue_player);});
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
    connect(redButton,&QPushButton::clicked,[this](){this->trade_with_player(player_type::red_player);});
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
    connect(greenButton,&QPushButton::clicked,[this](){this->trade_with_player(player_type::green_player);});
    greenButton->show();
    acceptButtons.push_back(greenButton);
}

Trade::~Trade()
{
    delete ui;
}

void Trade::plus(bool is_give, int i)
{
    if(is_give)
    {
        give[i]++;
        numLabels[i]->setText(QString::number(give[i]));
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
    int givesum = 0, wantsum = 0;
    for(auto it : give)
        givesum += it;
    for(auto it : want)
        wantsum += it;
    if(givesum != wantsum * 4)
    {
        QMessageBox::about(NULL, "Warning", "<h2>The ratio is incorrect!</h2>");
        return;
    }
}

void Trade::trade_with_player(player_type counterpartType)
{
    if (playerType == counterpartType)
    {
        QMessageBox::about(NULL, "Warning", "<h2>You cannot trade with yourself!</h2>");
        return;
    }
}
