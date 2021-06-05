#include <terrain.h>
#include <vector>
#include <QGraphicsView>
using namespace std;

vector<Terrain_type> types = {
    Terrain_type::desert,
    Terrain_type::ore, Terrain_type::ore, Terrain_type::ore,
    Terrain_type::brick, Terrain_type::brick, Terrain_type::brick,
    Terrain_type::lumber, Terrain_type::lumber, Terrain_type::lumber, Terrain_type::lumber,
    Terrain_type::wool, Terrain_type::wool, Terrain_type::wool, Terrain_type::wool,
    Terrain_type::grain, Terrain_type::grain, Terrain_type::grain, Terrain_type::grain};
vector<int> numbers = {2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12};
vector<int> xs = {377,509,641,311,443,575,707,245,377,509,641,773,311,443,575,707,377,509,641};
vector<int> ys = {91,91,91,206,206,206,206,321,321,321,321,321,436,436,436,436,551,551,551};
vector<Terrain> terrains;
vector<Terrain_disp> terrain_disps;


Terrain::Terrain(int i)
    : type{types[i]}
{
    if(types[i] == Terrain_type::desert)
        numbers.insert(numbers.begin()+i,1,0);
    number = numbers[i];
}

Terrain_disp::Terrain_disp(int i)
    : x{xs[i]}, y{ys[i]}
{
    switch(types[i]){
    case Terrain_type::brick:
        tile_pic = QPixmap(QString(":/tile/picture_sources/tile/tile_brick.png"));
        break;
    case Terrain_type::ore:
        tile_pic = QPixmap(QString(":/tile/picture_sources/tile/tile_ore.png"));
        break;
    case Terrain_type::desert:
        tile_pic = QPixmap(QString(":/tile/picture_sources/tile/tile_desert.png"));
        break;
    case Terrain_type::lumber:
        tile_pic = QPixmap(QString(":/tile/picture_sources/tile/tile_lumber.png"));
        break;
    case Terrain_type::wool:
        tile_pic = QPixmap(QString(":/tile/picture_sources/tile/tile_wool.png"));
        break;
    case Terrain_type::grain:
        tile_pic = QPixmap(QString(":/tile/picture_sources/tile/tile_grain.png"));
        break;
    }
    switch(numbers[i]){
    case 2:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_2.png"));
        break;
    case 3:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_3.png"));
        break;
    case 4:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_4.png"));
        break;
    case 5:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_5.png"));
        break;
    case 6:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_6.png"));
        break;
    case 8:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_8.png"));
        break;
    case 9:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_9.png"));
        break;
    case 10:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_10.png"));
        break;
    case 11:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_11.png"));
        break;
    case 12:
        num_pic = QPixmap(QString(":/prob/picture_sources/prob/prob_12.png"));
        break;
    }
}
void Terrain_disp::display(MainWindow *win){
    QGraphicsScene *scene1 = new QGraphicsScene;
    QGraphicsView *graph1 = new QGraphicsView(win);
    scene1->addPixmap(tile_pic);
    graph1->setScene(scene1);
    graph1->resize(132,152);
    graph1->move(x,y);
    graph1->scale(0.38,0.38);
    graph1->setStyleSheet("background:transparent;padding:0px;border:0px");
    graph1->show();
    QGraphicsScene *scene2 = new QGraphicsScene;
    QGraphicsView *graph2 = new QGraphicsView(win);
    scene2->addPixmap(num_pic);
    graph2->setScene(scene2);
    graph2->resize(60,60);
    graph2->move(x+36,y+72);
    graph2->scale(0.38,0.38);
    graph2->setStyleSheet("background:transparent;padding:0px;border:0px");
    graph2->show();
}

Terrain_type Terrain::get_terrain_type()
{
    return type;
}

int Terrain::get_source_point()
{
    return number;
}


