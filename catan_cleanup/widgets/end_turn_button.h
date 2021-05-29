#ifndef END_TURN_BUTTON_H
#define END_TURN_BUTTON_H

#include <QPushButton>
#include <QLabel>

class End_turn_button : public QPushButton
{
    Q_OBJECT
public:
    explicit End_turn_button(QWidget *parent = nullptr);
    QLabel* get_status_label();
    QPixmap get_status_pic(int flag);//flag=1返回ok_to_end_turn图片
signals:
private:
    int pos_x;
    int pos_y;
    QPixmap wait_pic;
    QPixmap ok_to_end_turn;
    QLabel* status_label;
};

#endif // END_TURN_BUTTON_H
