#ifndef TRADEPLUS_H
#define TRADEPLUS_H

#include <QPushButton>

class TradePlus : public QPushButton
{
public:
    TradePlus(bool is, int nn, int xx, int yy,QWidget *parent=nullptr);
private:
    friend class Trade;
    bool is_give;
    int n;
    int x;
    int y;
};

#endif // TRADEPLUS_H
