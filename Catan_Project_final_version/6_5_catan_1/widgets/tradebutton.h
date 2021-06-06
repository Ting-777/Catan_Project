#ifndef TRADEBUTTON_H
#define TRADEBUTTON_H
#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <QLabel>

class TradeButton: public QPushButton
{
public:
    TradeButton(QWidget *parent = nullptr);
public slots:
    void pop();
private:
    int x;
    int y;
    QLabel *icon;
};

#endif // TRADEBUTTON_H
