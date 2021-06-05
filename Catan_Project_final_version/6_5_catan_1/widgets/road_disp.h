#ifndef ROAD_DISP_H
#define ROAD_DISP_H
#include <QPushButton>
#include <QMovie>
#include <QPixmap>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
using namespace std;
class Road_disp : public QPushButton
{
    Q_OBJECT
public:
    explicit Road_disp(int i,QWidget *parent = nullptr);
    int get_index();
    virtual ~Road_disp(){};
private:
    int index;
    int x_pos;
    int y_pos;
    int angle;
    QTimer* timer;
    QPixmap circle;
    QMatrix rotateMatrix;
    int current_circle_index;
signals:
void has_built_road(int road_index);
void game_status_updated();
public slots:
    void send_build_road_signal();
    void display_befor_decide();
    void display_before_decide_in_opening_status(int point_index);
    void display_after_decide(int road_index);
    void change_circle_index();
    void disable_display();

};


#endif // ROAD_DISP_H
