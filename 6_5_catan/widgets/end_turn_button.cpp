#include "end_turn_button.h"

End_turn_button::End_turn_button(QWidget *parent) : QPushButton(parent)
{
    pos_x=1053;
    pos_y=802;
    resize(84,84);
    move(pos_x,pos_y);
    wait_pic=QPixmap(":/player_related/picture_sources/player_related/icon_hourglass.png");
    wait_pic=wait_pic.scaled(54,54);
    ok_to_end_turn=QPixmap(":/player_related/picture_sources/player_related/icon_pass_turn.png");
    ok_to_end_turn=ok_to_end_turn.scaled(54,54);
    status_label=new QLabel(this);
    status_label->resize(54,54);
    status_label->move(15,15);
    status_label->setPixmap(wait_pic);
    setIcon(QIcon(QPixmap(":/player_related/picture_sources/player_related/bg_button.png")));
    setIconSize(QSize(84,84));
    setFlat(true);
    setStyleSheet(("border:none;"));
    setDisabled(true);
    show();
}

QLabel* End_turn_button::get_status_label()
{
    return status_label;
}

QPixmap End_turn_button::get_status_pic(int flag)
{
    if(flag==1)return ok_to_end_turn;
    else if(flag==0)return wait_pic;
}
