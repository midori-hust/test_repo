#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'prefs_base.ui'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFS_BASE_H
#define UI_PREFS_BASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kcolorbutton.h"
#include "kcombobox.h"

QT_BEGIN_NAMESPACE

class Ui_prefs_base
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *animationGroup;
    QFormLayout *formLayout;
    QLabel *animationSpeedLabel;
    KComboBox *kcfg_animationSpeed;
    QCheckBox *kcfg_animateBoard;
    QGroupBox *appearanceGroup;
    QFormLayout *formLayout_2;
    QLabel *showMarkersForLabel;
    QCheckBox *kcfg_showMarker;
    QCheckBox *kcfg_showMotion;
    QCheckBox *kcfg_showDanger;
    QLabel *label;
    KComboBox *kcfg_borderDisplayType;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *kcfg_flipBoard;
    QCheckBox *kcfg_askDiscard;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *prefs_base)
    {
        if (prefs_base->objectName().isEmpty())
            prefs_base->setObjectName(QString::fromUtf8("prefs_base"));
        prefs_base->resize(624, 501);
        verticalLayout = new QVBoxLayout(prefs_base);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        animationGroup = new QGroupBox(prefs_base);
        animationGroup->setObjectName(QString::fromUtf8("animationGroup"));
        formLayout = new QFormLayout(animationGroup);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        animationSpeedLabel = new QLabel(animationGroup);
        animationSpeedLabel->setObjectName(QString::fromUtf8("animationSpeedLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, animationSpeedLabel);

        kcfg_animationSpeed = new KComboBox(animationGroup);
        kcfg_animationSpeed->setObjectName(QString::fromUtf8("kcfg_animationSpeed"));

        formLayout->setWidget(0, QFormLayout::FieldRole, kcfg_animationSpeed);

        kcfg_animateBoard = new QCheckBox(animationGroup);
        kcfg_animateBoard->setObjectName(QString::fromUtf8("kcfg_animateBoard"));

        formLayout->setWidget(1, QFormLayout::FieldRole, kcfg_animateBoard);


        verticalLayout->addWidget(animationGroup);

        appearanceGroup = new QGroupBox(prefs_base);
        appearanceGroup->setObjectName(QString::fromUtf8("appearanceGroup"));
        formLayout_2 = new QFormLayout(appearanceGroup);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        showMarkersForLabel = new QLabel(appearanceGroup);
        showMarkersForLabel->setObjectName(QString::fromUtf8("showMarkersForLabel"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, showMarkersForLabel);

        kcfg_showMarker = new QCheckBox(appearanceGroup);
        kcfg_showMarker->setObjectName(QString::fromUtf8("kcfg_showMarker"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, kcfg_showMarker);

        kcfg_showMotion = new QCheckBox(appearanceGroup);
        kcfg_showMotion->setObjectName(QString::fromUtf8("kcfg_showMotion"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(kcfg_showMotion->sizePolicy().hasHeightForWidth());
        kcfg_showMotion->setSizePolicy(sizePolicy);
        kcfg_showMotion->setChecked(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, kcfg_showMotion);

        kcfg_showDanger = new QCheckBox(appearanceGroup);
        kcfg_showDanger->setObjectName(QString::fromUtf8("kcfg_showDanger"));
        kcfg_showDanger->setChecked(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, kcfg_showDanger);

        label = new QLabel(appearanceGroup);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label);

        kcfg_borderDisplayType = new KComboBox(appearanceGroup);
        kcfg_borderDisplayType->setObjectName(QString::fromUtf8("kcfg_borderDisplayType"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, kcfg_borderDisplayType);


        verticalLayout->addWidget(appearanceGroup);

        groupBox = new QGroupBox(prefs_base);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        kcfg_flipBoard = new QCheckBox(groupBox);
        kcfg_flipBoard->setObjectName(QString::fromUtf8("kcfg_flipBoard"));

        verticalLayout_2->addWidget(kcfg_flipBoard);

        kcfg_askDiscard = new QCheckBox(groupBox);
        kcfg_askDiscard->setObjectName(QString::fromUtf8("kcfg_askDiscard"));

        verticalLayout_2->addWidget(kcfg_askDiscard);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 133, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

#ifndef UI_QT_NO_SHORTCUT
        animationSpeedLabel->setBuddy(kcfg_animationSpeed);
        showMarkersForLabel->setBuddy(kcfg_showMarker);
#endif // QT_NO_SHORTCUT

        retranslateUi(prefs_base);

        QMetaObject::connectSlotsByName(prefs_base);
    } // setupUi

    void retranslateUi(QWidget *prefs_base)
    {
        animationGroup->setTitle(tr2i18n("Animations", 0));
        animationSpeedLabel->setText(tr2i18n("Animation &speed:", 0));
        kcfg_animationSpeed->clear();
        kcfg_animationSpeed->insertItems(0, QStringList()
         << tr2i18n("Instant (no animation)", 0)
         << tr2i18n("Fast", 0)
         << tr2i18n("Normal", 0)
         << tr2i18n("Slow", 0)
        );
        kcfg_animateBoard->setText(tr2i18n("Animate the board as well", 0));
        appearanceGroup->setTitle(tr2i18n("Appearance", 0));
        showMarkersForLabel->setText(tr2i18n("Show &markers for:", 0));
        kcfg_showMarker->setText(tr2i18n("Legal moves", "Option to show markers for"));
        kcfg_showMotion->setText(tr2i18n("Opponent's move", "Option to show markers for"));
        kcfg_showDanger->setText(tr2i18n("Check", "Option to show markers for"));
        label->setText(tr2i18n("Border display:", 0));
        kcfg_borderDisplayType->clear();
        kcfg_borderDisplayType->insertItems(0, QStringList()
         << tr2i18n("No borders", 0)
         << tr2i18n("Only borders", 0)
         << tr2i18n("Borders and notation", 0)
        );
        groupBox->setTitle(tr2i18n("Behavior", 0));
        kcfg_flipBoard->setText(tr2i18n("Flip the board in local matches between humans", 0));
        kcfg_askDiscard->setText(tr2i18n("Show confirmation dialog before closing", 0));
        Q_UNUSED(prefs_base);
    } // retranslateUi

};

namespace Ui {
    class prefs_base: public Ui_prefs_base {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PREFS_BASE_H

