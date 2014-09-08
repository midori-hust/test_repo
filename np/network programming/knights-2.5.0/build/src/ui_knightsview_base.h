#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'knightsview_base.ui'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KNIGHTSVIEW_BASE_H
#define UI_KNIGHTSVIEW_BASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KnightsView
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *notificationWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *showAllOffers;
    QGraphicsView *canvas;

    void setupUi(QWidget *KnightsView)
    {
        if (KnightsView->objectName().isEmpty())
            KnightsView->setObjectName(QString::fromUtf8("KnightsView"));
        KnightsView->resize(489, 613);
        KnightsView->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(KnightsView);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        notificationWidget = new QWidget(KnightsView);
        notificationWidget->setObjectName(QString::fromUtf8("notificationWidget"));
        gridLayout = new QGridLayout(notificationWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        showAllOffers = new QPushButton(notificationWidget);
        showAllOffers->setObjectName(QString::fromUtf8("showAllOffers"));

        gridLayout->addWidget(showAllOffers, 1, 1, 1, 1);


        verticalLayout_2->addWidget(notificationWidget);

        canvas = new QGraphicsView(KnightsView);
        canvas->setObjectName(QString::fromUtf8("canvas"));
        canvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        canvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_2->addWidget(canvas);


        retranslateUi(KnightsView);

        QMetaObject::connectSlotsByName(KnightsView);
    } // setupUi

    void retranslateUi(QWidget *KnightsView)
    {
        KnightsView->setWindowTitle(tr2i18n("Knights", 0));
        showAllOffers->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class KnightsView: public Ui_KnightsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // KNIGHTSVIEW_BASE_H

