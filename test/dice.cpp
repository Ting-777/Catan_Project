#include "dice.h"
#include<iostream>
#include <QString>
#include <QTime>
#include <QRandomGenerator>
Dice::Dice(QWidget *parent): QPushButton(parent)
{
    resize(180,85);
    x = 941;
    y = 644;
    diceLabel1 = new QLabel;
    diceLabel2 = new QLabel;
    diceLabel1->setPixmap(QPixmap(":/dice/picture_sources/dice/dice_6.png").scaled(75,75));
    diceLabel2->setPixmap(QPixmap(":/dice/picture_sources/dice/dice_6.png").scaled(75,75));
    diceLabel1->resize(85,85);
    diceLabel2->resize(85,85);
    diceNumber1 = 6;
    diceNumber2 = 6;
    layout = new QHBoxLayout;
    layout->addWidget(diceLabel1);
    layout->addWidget(diceLabel2);
    setLayout(layout);
    setFlat(true);
    setStyleSheet(("border:none;"));
    move(x,y);
    show();
}

void Dice::roll()
{
    diceNumber1 = QRandomGenerator::global()->bounded(1,6);
    diceNumber2 = QRandomGenerator::global()->bounded(1,6);
    QString pathStr1 = ":/dice/picture_sources/dice/dice_"+ QString::number(diceNumber1) +".png";
    QString pathStr2 = ":/dice/picture_sources/dice/dice_"+ QString::number(diceNumber2) +".png";
    diceLabel1->setPixmap(QPixmap(pathStr1).scaled(75,75));
    diceLabel2->setPixmap(QPixmap(pathStr2).scaled(75,75));
    show();
}
