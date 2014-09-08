#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'promotiondialog.ui'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROMOTIONDIALOG_H
#define UI_PROMOTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kbuttongroup.h"

QT_BEGIN_NAMESPACE

class Ui_PromotionWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *labelPawn;
    KButtonGroup *kbuttongroup;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonQueen;
    QRadioButton *radioButtonRook;
    QRadioButton *radioButtonBishop;
    QRadioButton *radioButtonKnight;

    void setupUi(QWidget *PromotionWidget)
    {
        if (PromotionWidget->objectName().isEmpty())
            PromotionWidget->setObjectName(QString::fromUtf8("PromotionWidget"));
        PromotionWidget->resize(135, 137);
        verticalLayout_2 = new QVBoxLayout(PromotionWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelPawn = new QLabel(PromotionWidget);
        labelPawn->setObjectName(QString::fromUtf8("labelPawn"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labelPawn->setFont(font);

        verticalLayout_2->addWidget(labelPawn);

        kbuttongroup = new KButtonGroup(PromotionWidget);
        kbuttongroup->setObjectName(QString::fromUtf8("kbuttongroup"));
        verticalLayout = new QVBoxLayout(kbuttongroup);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButtonQueen = new QRadioButton(kbuttongroup);
        radioButtonQueen->setObjectName(QString::fromUtf8("radioButtonQueen"));
        radioButtonQueen->setChecked(true);

        verticalLayout->addWidget(radioButtonQueen);

        radioButtonRook = new QRadioButton(kbuttongroup);
        radioButtonRook->setObjectName(QString::fromUtf8("radioButtonRook"));

        verticalLayout->addWidget(radioButtonRook);

        radioButtonBishop = new QRadioButton(kbuttongroup);
        radioButtonBishop->setObjectName(QString::fromUtf8("radioButtonBishop"));

        verticalLayout->addWidget(radioButtonBishop);

        radioButtonKnight = new QRadioButton(kbuttongroup);
        radioButtonKnight->setObjectName(QString::fromUtf8("radioButtonKnight"));

        verticalLayout->addWidget(radioButtonKnight);


        verticalLayout_2->addWidget(kbuttongroup);


        retranslateUi(PromotionWidget);

        QMetaObject::connectSlotsByName(PromotionWidget);
    } // setupUi

    void retranslateUi(QWidget *PromotionWidget)
    {
        PromotionWidget->setWindowTitle(tr2i18n("Pawn Promotion", 0));
        labelPawn->setText(tr2i18n("Promote pawn to:", 0));
        radioButtonQueen->setText(tr2i18n("Queen", 0));
        radioButtonRook->setText(tr2i18n("Rook", 0));
        radioButtonBishop->setText(tr2i18n("Bishop", 0));
        radioButtonKnight->setText(tr2i18n("Knight", 0));
    } // retranslateUi

};

namespace Ui {
    class PromotionWidget: public Ui_PromotionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PROMOTIONDIALOG_H

