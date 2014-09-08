#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'customdifficultydialog.ui'
**
** Created: Thu Sep 26 16:52:39 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMDIFFICULTYDIALOG_H
#define UI_CUSTOMDIFFICULTYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include "knuminput.h"

QT_BEGIN_NAMESPACE

class Ui_CustomDifficultyDialog
{
public:
    QFormLayout *formLayout_2;
    QLabel *searchDepthLabel;
    KIntSpinBox *searchDepthIntSpinBox;
    QLabel *memorySizeLabel;
    KIntSpinBox *memorySizeIntSpinBox;

    void setupUi(QWidget *CustomDifficultyDialog)
    {
        if (CustomDifficultyDialog->objectName().isEmpty())
            CustomDifficultyDialog->setObjectName(QString::fromUtf8("CustomDifficultyDialog"));
        CustomDifficultyDialog->resize(167, 56);
        formLayout_2 = new QFormLayout(CustomDifficultyDialog);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        searchDepthLabel = new QLabel(CustomDifficultyDialog);
        searchDepthLabel->setObjectName(QString::fromUtf8("searchDepthLabel"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, searchDepthLabel);

        searchDepthIntSpinBox = new KIntSpinBox(CustomDifficultyDialog);
        searchDepthIntSpinBox->setObjectName(QString::fromUtf8("searchDepthIntSpinBox"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, searchDepthIntSpinBox);

        memorySizeLabel = new QLabel(CustomDifficultyDialog);
        memorySizeLabel->setObjectName(QString::fromUtf8("memorySizeLabel"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, memorySizeLabel);

        memorySizeIntSpinBox = new KIntSpinBox(CustomDifficultyDialog);
        memorySizeIntSpinBox->setObjectName(QString::fromUtf8("memorySizeIntSpinBox"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, memorySizeIntSpinBox);

#ifndef UI_QT_NO_SHORTCUT
        searchDepthLabel->setBuddy(searchDepthIntSpinBox);
        memorySizeLabel->setBuddy(memorySizeIntSpinBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(CustomDifficultyDialog);

        QMetaObject::connectSlotsByName(CustomDifficultyDialog);
    } // setupUi

    void retranslateUi(QWidget *CustomDifficultyDialog)
    {
        searchDepthLabel->setText(tr2i18n("Search &depth:", 0));
        searchDepthIntSpinBox->setSpecialValueText(tr2i18n("Engine default", "Let the engine determine the search depth"));
        memorySizeLabel->setText(tr2i18n("Memory &size:", 0));
        memorySizeIntSpinBox->setSuffix(tr2i18n(" MB", "Megabytes"));
        Q_UNUSED(CustomDifficultyDialog);
    } // retranslateUi

};

namespace Ui {
    class CustomDifficultyDialog: public Ui_CustomDifficultyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CUSTOMDIFFICULTYDIALOG_H

