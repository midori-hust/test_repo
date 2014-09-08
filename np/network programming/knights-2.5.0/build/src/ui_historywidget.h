#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'historywidget.ui'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYWIDGET_H
#define UI_HISTORYWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kcombobox.h"
#include "kpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_HistoryWidget
{
public:
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QFormLayout *formLayout;
    QLabel *notationLabel;
    KComboBox *notationComboBox;
    KPushButton *saveButton;

    void setupUi(QWidget *HistoryWidget)
    {
        if (HistoryWidget->objectName().isEmpty())
            HistoryWidget->setObjectName(QString::fromUtf8("HistoryWidget"));
        HistoryWidget->resize(541, 300);
        verticalLayout = new QVBoxLayout(HistoryWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listView = new QListView(HistoryWidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout->addWidget(listView);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        notationLabel = new QLabel(HistoryWidget);
        notationLabel->setObjectName(QString::fromUtf8("notationLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, notationLabel);

        notationComboBox = new KComboBox(HistoryWidget);
        notationComboBox->setObjectName(QString::fromUtf8("notationComboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, notationComboBox);


        verticalLayout->addLayout(formLayout);

        saveButton = new KPushButton(HistoryWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        verticalLayout->addWidget(saveButton);

#ifndef UI_QT_NO_SHORTCUT
        notationLabel->setBuddy(notationComboBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(HistoryWidget);

        QMetaObject::connectSlotsByName(HistoryWidget);
    } // setupUi

    void retranslateUi(QWidget *HistoryWidget)
    {
        notationLabel->setText(tr2i18n("&Notation:", 0));
        notationComboBox->clear();
        notationComboBox->insertItems(0, QStringList()
         << tr2i18n("Short Algebraic", 0)
         << tr2i18n("Long Algebraic", 0)
         << tr2i18n("Coordinate", 0)
        );
        saveButton->setText(tr2i18n("&Save History", 0));
        Q_UNUSED(HistoryWidget);
    } // retranslateUi

};

namespace Ui {
    class HistoryWidget: public Ui_HistoryWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // HISTORYWIDGET_H

