#ifndef POINT_DISP_H
#define POINT_DISP_H

#include <QPushButton>
#include <QMovie>
#include <QPixmap>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
using namespace std;
class Point_disp : public QPushButton
{
    Q_OBJECT
public:
    explicit Point_disp(int i,QWidget *parent = nullptr);
    int get_index();
private:
    int index;
    int x_pos;
    int y_pos;
    QTimer* timer;
    QPixmap circle;
    int current_circle_index;
signals:
void has_built_small_house(int point_index);
void has_built_big_house(int point_index);
void construction_completed();
public slots:
    void send_build_small_house_signal();
    void send_build_big_house_signal();
    void display_befor_decide();
    void display_after_decide(int point_index);
    void change_circle_index();
};

#endif // POINT_DISP_H
