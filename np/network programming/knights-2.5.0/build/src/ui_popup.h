#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'popup.ui'
**
** Created: Thu Sep 26 16:52:39 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPUP_H
#define UI_POPUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "kpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_Popup
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    KPushButton *acceptButton;
    KPushButton *declineButton;
    KPushButton *closeButton;

    void setupUi(QWidget *Popup)
    {
        if (Popup->objectName().isEmpty())
            Popup->setObjectName(QString::fromUtf8("Popup"));
        Popup->resize(584, 33);
        horizontalLayout = new QHBoxLayout(Popup);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Popup);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        acceptButton = new KPushButton(Popup);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        horizontalLayout->addWidget(acceptButton);

        declineButton = new KPushButton(Popup);
        declineButton->setObjectName(QString::fromUtf8("declineButton"));

        horizontalLayout->addWidget(declineButton);

        closeButton = new KPushButton(Popup);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout->addWidget(closeButton);


        retranslateUi(Popup);

        QMetaObject::connectSlotsByName(Popup);
    } // setupUi

    void retranslateUi(QWidget *Popup)
    {
        label->setText(tr2i18n("TextLabel", "KDE::DoNotExtract"));
        acceptButton->setText(tr2i18n("Accept", 0));
        declineButton->setText(tr2i18n("Decline", 0));
        closeButton->setText(tr2i18n("Close", 0));
        Q_UNUSED(Popup);
    } // retranslateUi

};

namespace Ui {
    class Popup: public Ui_Popup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // POPUP_H

