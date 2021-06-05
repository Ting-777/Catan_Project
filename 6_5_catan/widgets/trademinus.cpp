#include "trademinus.h"

TradeMinus::TradeMinus(bool is, int nn, int xx, int yy,QWidget *parent): QPushButton(parent),
    is_give{is}, n{nn}, x{xx}, y{yy}
{
    setIcon(QIcon(QPixmap(":/player_related/picture_sources/player_related/icon_minus.png")));
    setIconSize(QSize(20,20));
    move(x,y);
}
