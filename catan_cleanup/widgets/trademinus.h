#ifndef TRADEMINUS_H
#define TRADEMINUS_H

#include <QPushButton>

class TradeMinus : public QPushButton
{
public:
    TradeMinus(bool is, int nn, int xx, int yy,QWidget *parent=nullptr);
private:
    friend class Trade;
    bool is_give;
    int n;
    int x;
    int y;
};

#endif // TRADEMINUS_H
