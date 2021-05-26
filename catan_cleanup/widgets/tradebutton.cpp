#include "tradebutton.h"
#include "trade.h"

TradeButton::TradeButton(QWidget *parent): QPushButton(parent)
{
    x = 964;
    y = 802;
    move(x,y);
    resize(84,84);
    icon=new QLabel(this);
    icon->setPixmap(QPixmap(":/player_related/picture_sources/player_related/icon_trade.png").scaled(50,50));
    icon->move(17,17);
    setIcon(QIcon(QPixmap(":/player_related/picture_sources/player_related/bg_button.png")));
    setIconSize(QSize(84,84));
    setFlat(true);
    setStyleSheet(("border:none;"));
    show();
}

void TradeButton::pop()
{
    Trade *trade = new Trade(this);
    trade->exec();
}
