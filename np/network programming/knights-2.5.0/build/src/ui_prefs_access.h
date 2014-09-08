#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'prefs_access.ui'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFS_ACCESS_H
#define UI_PREFS_ACCESS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_prefs_access
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *external_box;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *kcfg_speakOpponentsMoves;
    QCheckBox *kcfg_allowExternalControl;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *prefs_access)
    {
        if (prefs_access->objectName().isEmpty())
            prefs_access->setObjectName(QString::fromUtf8("prefs_access"));
        prefs_access->resize(455, 260);
        verticalLayout = new QVBoxLayout(prefs_access);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        external_box = new QGroupBox(prefs_access);
        external_box->setObjectName(QString::fromUtf8("external_box"));
        verticalLayout_2 = new QVBoxLayout(external_box);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        kcfg_speakOpponentsMoves = new QCheckBox(external_box);
        kcfg_speakOpponentsMoves->setObjectName(QString::fromUtf8("kcfg_speakOpponentsMoves"));

        verticalLayout_2->addWidget(kcfg_speakOpponentsMoves);

        kcfg_allowExternalControl = new QCheckBox(external_box);
        kcfg_allowExternalControl->setObjectName(QString::fromUtf8("kcfg_allowExternalControl"));

        verticalLayout_2->addWidget(kcfg_allowExternalControl);


        verticalLayout->addWidget(external_box);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(prefs_access);

        QMetaObject::connectSlotsByName(prefs_access);
    } // setupUi

    void retranslateUi(QWidget *prefs_access)
    {
        external_box->setTitle(tr2i18n("External Programs", 0));
        kcfg_speakOpponentsMoves->setText(tr2i18n("Speak opponent's moves", 0));
        kcfg_allowExternalControl->setText(tr2i18n("Allow other programs to control Knights", 0));
        Q_UNUSED(prefs_access);
    } // retranslateUi

};

namespace Ui {
    class prefs_access: public Ui_prefs_access {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PREFS_ACCESS_H

