#ifndef DICE_H
#define DICE_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

class Dice : public QPushButton
{
public:
    Dice(QWidget *parent = nullptr);
public slots:
    void roll();
private:
    int x;
    int y;
    int diceNumber1;
    int diceNumber2;
    QLabel *diceLabel1;
    QLabel *diceLabel2;
    QHBoxLayout *layout;
};

#endif // DICE_H


