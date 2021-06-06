/********************************************************************************
** Form generated from reading UI file 'trade.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRADE_H
#define UI_TRADE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Trade
{
public:

    void setupUi(QDialog *Trade)
    {
        if (Trade->objectName().isEmpty())
            Trade->setObjectName(QString::fromUtf8("Trade"));
        Trade->resize(759, 580);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/card/picture_sources/card/card_wool.png"), QSize(), QIcon::Normal, QIcon::Off);
        Trade->setWindowIcon(icon);

        retranslateUi(Trade);

        QMetaObject::connectSlotsByName(Trade);
    } // setupUi

    void retranslateUi(QDialog *Trade)
    {
        Trade->setWindowTitle(QCoreApplication::translate("Trade", "Trade", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Trade: public Ui_Trade {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRADE_H
