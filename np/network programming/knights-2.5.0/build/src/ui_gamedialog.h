#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'gamedialog.ui'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEDIALOG_H
#define UI_GAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kcombobox.h"
#include "khistorycombobox.h"
#include "knuminput.h"
#include "kpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_GameDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *player1Box;
    QGridLayout *gridLayout_2;
    QRadioButton *player1Human;
    QGridLayout *gridLayout_3;
    QRadioButton *player1Comp;
    KComboBox *player1Program;
    QSpacerItem *horizontalSpacer_2;
    KPushButton *player1Engines;
    QGroupBox *colorGroup;
    QVBoxLayout *verticalLayout;
    QRadioButton *colorWhite;
    QRadioButton *colorBlack;
    QRadioButton *colorRandom;
    QGroupBox *player2Box;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *player2Human;
    QGridLayout *gridLayout_4;
    QRadioButton *player2Comp;
    KComboBox *player2Program;
    QToolButton *player2Engines;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *ficsLayout_2;
    QRadioButton *player2Fics;
    KHistoryComboBox *player2Server;
    QGroupBox *timeGroup;
    QFormLayout *formLayout_2;
    QLabel *numberOfMovesLabel;
    KIntSpinBox *numberOfMoves;
    QLabel *timeLimitLabel;
    KIntSpinBox *timeLimit;
    QLabel *timeIncrementLabel;
    KIntSpinBox *timeIncrement;

    void setupUi(QWidget *GameDialog)
    {
        if (GameDialog->objectName().isEmpty())
            GameDialog->setObjectName(QString::fromUtf8("GameDialog"));
        GameDialog->resize(642, 325);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GameDialog->sizePolicy().hasHeightForWidth());
        GameDialog->setSizePolicy(sizePolicy);
        GameDialog->setMinimumSize(QSize(600, 240));
        gridLayout = new QGridLayout(GameDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        player1Box = new QGroupBox(GameDialog);
        player1Box->setObjectName(QString::fromUtf8("player1Box"));
        gridLayout_2 = new QGridLayout(player1Box);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        player1Human = new QRadioButton(player1Box);
        player1Human->setObjectName(QString::fromUtf8("player1Human"));
        player1Human->setChecked(true);

        gridLayout_2->addWidget(player1Human, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        player1Comp = new QRadioButton(player1Box);
        player1Comp->setObjectName(QString::fromUtf8("player1Comp"));

        gridLayout_3->addWidget(player1Comp, 0, 0, 1, 1);

        player1Program = new KComboBox(player1Box);
        player1Program->setObjectName(QString::fromUtf8("player1Program"));

        gridLayout_3->addWidget(player1Program, 0, 1, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        player1Engines = new KPushButton(player1Box);
        player1Engines->setObjectName(QString::fromUtf8("player1Engines"));

        gridLayout_3->addWidget(player1Engines, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 1, 0, 1, 1);


        gridLayout->addWidget(player1Box, 0, 0, 1, 1);

        colorGroup = new QGroupBox(GameDialog);
        colorGroup->setObjectName(QString::fromUtf8("colorGroup"));
        sizePolicy.setHeightForWidth(colorGroup->sizePolicy().hasHeightForWidth());
        colorGroup->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(colorGroup);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        colorWhite = new QRadioButton(colorGroup);
        colorWhite->setObjectName(QString::fromUtf8("colorWhite"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(colorWhite->sizePolicy().hasHeightForWidth());
        colorWhite->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(colorWhite);

        colorBlack = new QRadioButton(colorGroup);
        colorBlack->setObjectName(QString::fromUtf8("colorBlack"));
        sizePolicy1.setHeightForWidth(colorBlack->sizePolicy().hasHeightForWidth());
        colorBlack->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(colorBlack);

        colorRandom = new QRadioButton(colorGroup);
        colorRandom->setObjectName(QString::fromUtf8("colorRandom"));
        sizePolicy1.setHeightForWidth(colorRandom->sizePolicy().hasHeightForWidth());
        colorRandom->setSizePolicy(sizePolicy1);
        colorRandom->setChecked(true);

        verticalLayout->addWidget(colorRandom);


        gridLayout->addWidget(colorGroup, 0, 1, 1, 1);

        player2Box = new QGroupBox(GameDialog);
        player2Box->setObjectName(QString::fromUtf8("player2Box"));
        verticalLayout_3 = new QVBoxLayout(player2Box);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        player2Human = new QRadioButton(player2Box);
        player2Human->setObjectName(QString::fromUtf8("player2Human"));
        player2Human->setChecked(true);

        verticalLayout_3->addWidget(player2Human);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        player2Comp = new QRadioButton(player2Box);
        player2Comp->setObjectName(QString::fromUtf8("player2Comp"));

        gridLayout_4->addWidget(player2Comp, 0, 0, 1, 1);

        player2Program = new KComboBox(player2Box);
        player2Program->setObjectName(QString::fromUtf8("player2Program"));

        gridLayout_4->addWidget(player2Program, 0, 1, 1, 2);

        player2Engines = new QToolButton(player2Box);
        player2Engines->setObjectName(QString::fromUtf8("player2Engines"));

        gridLayout_4->addWidget(player2Engines, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 1, 2, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);

        ficsLayout_2 = new QHBoxLayout();
        ficsLayout_2->setObjectName(QString::fromUtf8("ficsLayout_2"));
        player2Fics = new QRadioButton(player2Box);
        player2Fics->setObjectName(QString::fromUtf8("player2Fics"));

        ficsLayout_2->addWidget(player2Fics);

        player2Server = new KHistoryComboBox(player2Box);
        player2Server->setObjectName(QString::fromUtf8("player2Server"));
        player2Server->setEnabled(false);
        player2Server->setHistoryItems(QStringList());

        ficsLayout_2->addWidget(player2Server);


        verticalLayout_3->addLayout(ficsLayout_2);


        gridLayout->addWidget(player2Box, 1, 0, 1, 1);

        timeGroup = new QGroupBox(GameDialog);
        timeGroup->setObjectName(QString::fromUtf8("timeGroup"));
        timeGroup->setCheckable(true);
        timeGroup->setChecked(false);
        formLayout_2 = new QFormLayout(timeGroup);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        numberOfMovesLabel = new QLabel(timeGroup);
        numberOfMovesLabel->setObjectName(QString::fromUtf8("numberOfMovesLabel"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, numberOfMovesLabel);

        numberOfMoves = new KIntSpinBox(timeGroup);
        numberOfMoves->setObjectName(QString::fromUtf8("numberOfMoves"));
        numberOfMoves->setMinimumSize(QSize(120, 0));
        numberOfMoves->setMaximum(120);
        numberOfMoves->setValue(40);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, numberOfMoves);

        timeLimitLabel = new QLabel(timeGroup);
        timeLimitLabel->setObjectName(QString::fromUtf8("timeLimitLabel"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, timeLimitLabel);

        timeLimit = new KIntSpinBox(timeGroup);
        timeLimit->setObjectName(QString::fromUtf8("timeLimit"));
        timeLimit->setMinimumSize(QSize(120, 0));
        timeLimit->setMaximum(300);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, timeLimit);

        timeIncrementLabel = new QLabel(timeGroup);
        timeIncrementLabel->setObjectName(QString::fromUtf8("timeIncrementLabel"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, timeIncrementLabel);

        timeIncrement = new KIntSpinBox(timeGroup);
        timeIncrement->setObjectName(QString::fromUtf8("timeIncrement"));
        timeIncrement->setMinimumSize(QSize(120, 0));
        timeIncrement->setMaximum(900);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, timeIncrement);


        gridLayout->addWidget(timeGroup, 1, 1, 1, 1);

#ifndef UI_QT_NO_SHORTCUT
        numberOfMovesLabel->setBuddy(numberOfMoves);
        timeLimitLabel->setBuddy(timeLimit);
        timeIncrementLabel->setBuddy(timeIncrement);
#endif // QT_NO_SHORTCUT

        retranslateUi(GameDialog);
        QObject::connect(player2Fics, SIGNAL(toggled(bool)), player2Server, SLOT(setEnabled(bool)));
        QObject::connect(player2Fics, SIGNAL(toggled(bool)), numberOfMovesLabel, SLOT(setHidden(bool)));
        QObject::connect(player2Fics, SIGNAL(toggled(bool)), numberOfMoves, SLOT(setHidden(bool)));
        QObject::connect(player2Fics, SIGNAL(clicked(bool)), timeGroup, SLOT(setChecked(bool)));

        QMetaObject::connectSlotsByName(GameDialog);
    } // setupUi

    void retranslateUi(QWidget *GameDialog)
    {
        player1Box->setTitle(tr2i18n("Player 1", 0));
        player1Human->setText(tr2i18n("Human (You)", 0));
        player1Comp->setText(tr2i18n("Computer engine:", 0));
        player1Engines->setText(tr2i18n("Configure Engines", 0));
        colorGroup->setTitle(tr2i18n("Player 1's Color", 0));
        colorWhite->setText(tr2i18n("White", 0));
        colorBlack->setText(tr2i18n("Black", 0));
        colorRandom->setText(tr2i18n("Choose randomly", 0));
        player2Box->setTitle(tr2i18n("Player 2", 0));
        player2Human->setText(tr2i18n("Human", 0));
        player2Comp->setText(tr2i18n("Computer engine:", 0));
        player2Engines->setText(tr2i18n("Configure Engines", 0));
        player2Fics->setText(tr2i18n("Chess server:", 0));
        timeGroup->setTitle(tr2i18n("Use Time Control", 0));
        numberOfMovesLabel->setText(tr2i18n("Time control period", 0));
        numberOfMoves->setSpecialValueText(tr2i18n("Timer Only", "Time control mode"));
        timeLimitLabel->setText(tr2i18n("Initial time limit", 0));
        timeIncrementLabel->setText(tr2i18n("Increment per move", 0));
        Q_UNUSED(GameDialog);
    } // retranslateUi

};

namespace Ui {
    class GameDialog: public Ui_GameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GAMEDIALOG_H

