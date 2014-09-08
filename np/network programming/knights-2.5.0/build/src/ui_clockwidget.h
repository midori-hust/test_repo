#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'clockwidget.ui'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOCKWIDGET_H
#define UI_CLOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QProgressBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <clock.h>

QT_BEGIN_NAMESPACE

class Ui_ClockWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupB;
    QVBoxLayout *verticalLayout_2;
    Knights::Clock *clockB;
    QProgressBar *progressB;
    QGroupBox *groupW;
    QVBoxLayout *verticalLayout_3;
    Knights::Clock *clockW;
    QProgressBar *progressW;

    void setupUi(QWidget *ClockWidget)
    {
        if (ClockWidget->objectName().isEmpty())
            ClockWidget->setObjectName(QString::fromUtf8("ClockWidget"));
        ClockWidget->resize(243, 660);
        verticalLayout = new QVBoxLayout(ClockWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupB = new QGroupBox(ClockWidget);
        groupB->setObjectName(QString::fromUtf8("groupB"));
        verticalLayout_2 = new QVBoxLayout(groupB);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        clockB = new Knights::Clock(groupB);
        clockB->setObjectName(QString::fromUtf8("clockB"));

        verticalLayout_2->addWidget(clockB);

        progressB = new QProgressBar(groupB);
        progressB->setObjectName(QString::fromUtf8("progressB"));
        QFont font;
        font.setPointSize(24);
        progressB->setFont(font);
        progressB->setValue(24);
        progressB->setInvertedAppearance(true);

        verticalLayout_2->addWidget(progressB);


        verticalLayout->addWidget(groupB);

        groupW = new QGroupBox(ClockWidget);
        groupW->setObjectName(QString::fromUtf8("groupW"));
        verticalLayout_3 = new QVBoxLayout(groupW);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        clockW = new Knights::Clock(groupW);
        clockW->setObjectName(QString::fromUtf8("clockW"));

        verticalLayout_3->addWidget(clockW);

        progressW = new QProgressBar(groupW);
        progressW->setObjectName(QString::fromUtf8("progressW"));
        progressW->setFont(font);
        progressW->setValue(24);
        progressW->setInvertedAppearance(true);

        verticalLayout_3->addWidget(progressW);


        verticalLayout->addWidget(groupW);


        retranslateUi(ClockWidget);

        QMetaObject::connectSlotsByName(ClockWidget);
    } // setupUi

    void retranslateUi(QWidget *ClockWidget)
    {
        groupB->setTitle(tr2i18n("Black", 0));
        groupW->setTitle(tr2i18n("White", 0));
        Q_UNUSED(ClockWidget);
    } // retranslateUi

};

namespace Ui {
    class ClockWidget: public Ui_ClockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CLOCKWIDGET_H

