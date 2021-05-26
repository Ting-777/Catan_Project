#ifndef TRADE_H
#define TRADE_H

#include <QDialog>
#include <QLabel>
#include <vector>
#include "tradeplus.h"
#include "trademinus.h"
#include "player_enum.h"
using namespace std;

namespace Ui {
class Trade;
}

class Trade : public QDialog
{
    Q_OBJECT

public:
    Trade(QWidget *parent = nullptr);
   ~Trade();
public slots:
    void plus(bool is_give, int i);
    void minus(bool is_give, int i);
    void trade_with_bank();
    void trade_with_player(player_type);
private:
    Ui::Trade *ui;
    vector<int> give = {0,0,0,0,0};
    vector<int> want = {0,0,0,0,0};
    vector<QLabel*> numLabels;
    vector<TradePlus*> pluses;
    vector<TradeMinus*> minuses;
    QPushButton* bankButton;
    player_type playerType = player_type::red_player;
    vector<QPushButton*> acceptButtons;
};

#endif // TRADE_H
