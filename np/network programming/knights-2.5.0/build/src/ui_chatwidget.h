#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'chatwidget.ui'
**
** Created: Thu Sep 26 16:52:39 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include "klineedit.h"
#include "kpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QGridLayout *gridLayout;
    KLineEdit *line;
    KPushButton *sendButton;
    QHBoxLayout *hLayout;
    QHBoxLayout *extraButtonsLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton;
    QHBoxLayout *consoleLayout;

    void setupUi(QWidget *ChatWidget)
    {
        if (ChatWidget->objectName().isEmpty())
            ChatWidget->setObjectName(QString::fromUtf8("ChatWidget"));
        ChatWidget->resize(264, 258);
        gridLayout = new QGridLayout(ChatWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        line = new KLineEdit(ChatWidget);
        line->setObjectName(QString::fromUtf8("line"));

        gridLayout->addWidget(line, 6, 0, 1, 1);

        sendButton = new KPushButton(ChatWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setDefault(true);

        gridLayout->addWidget(sendButton, 6, 1, 1, 1);

        hLayout = new QHBoxLayout();
        hLayout->setObjectName(QString::fromUtf8("hLayout"));
        hLayout->setSizeConstraint(QLayout::SetMinimumSize);
        extraButtonsLayout = new QHBoxLayout();
        extraButtonsLayout->setObjectName(QString::fromUtf8("extraButtonsLayout"));

        hLayout->addLayout(extraButtonsLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLayout->addItem(horizontalSpacer);

        toolButton = new QToolButton(ChatWidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        hLayout->addWidget(toolButton);


        gridLayout->addLayout(hLayout, 4, 0, 1, 2);

        consoleLayout = new QHBoxLayout();
        consoleLayout->setObjectName(QString::fromUtf8("consoleLayout"));
        consoleLayout->setSizeConstraint(QLayout::SetMaximumSize);

        gridLayout->addLayout(consoleLayout, 0, 0, 4, 2);


        retranslateUi(ChatWidget);
        QObject::connect(line, SIGNAL(returnPressed()), sendButton, SLOT(click()));

        QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
        sendButton->setText(tr2i18n("Send", 0));
        toolButton->setText(tr2i18n("...", 0));
        Q_UNUSED(ChatWidget);
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CHATWIDGET_H

