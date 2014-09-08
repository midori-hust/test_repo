#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'ficsdialog.ui'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FICSDIALOG_H
#define UI_FICSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "klineedit.h"
#include "kpushbutton.h"
#include "ktabwidget.h"
#include "proto/seekgraph.h"

QT_BEGIN_NAMESPACE

class Ui_FicsDialog
{
public:
    QVBoxLayout *verticalLayout;
    KTabWidget *tabWidget;
    QWidget *accountTab;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *logInGroup;
    QGridLayout *gridLayout_2;
    QLabel *logInStatusLabel;
    QLabel *usernameLabel;
    KLineEdit *usernameLineEdit;
    QCheckBox *registeredCheckBox;
    QLabel *passwordLabel;
    KLineEdit *passwordLineEdit;
    QCheckBox *rememberCheckBox;
    KPushButton *logInButton;
    QSpacerItem *horizontalSpacer_2;
    KPushButton *registerButton;
    QSpacerItem *verticalSpacer;
    QWidget *joinTab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *offerTable;
    QWidget *graphTab;
    QVBoxLayout *verticalLayout_5;
    Knights::SeekGraph *graphView;
    QWidget *challengeTab;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *ratedCheckBox;
    QCheckBox *autoCheckBox;
    QPushButton *seekButton;
    QListView *challengeListView;
    QWidget *consoleTab;
    QVBoxLayout *verticalLayout_4;

    void setupUi(QWidget *FicsDialog)
    {
        if (FicsDialog->objectName().isEmpty())
            FicsDialog->setObjectName(QString::fromUtf8("FicsDialog"));
        FicsDialog->resize(568, 269);
        verticalLayout = new QVBoxLayout(FicsDialog);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new KTabWidget(FicsDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setMovable(true);
        tabWidget->setAutomaticResizeTabs(true);
        accountTab = new QWidget();
        accountTab->setObjectName(QString::fromUtf8("accountTab"));
        accountTab->setEnabled(true);
        verticalLayout_3 = new QVBoxLayout(accountTab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        logInGroup = new QGroupBox(accountTab);
        logInGroup->setObjectName(QString::fromUtf8("logInGroup"));
        gridLayout_2 = new QGridLayout(logInGroup);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        logInStatusLabel = new QLabel(logInGroup);
        logInStatusLabel->setObjectName(QString::fromUtf8("logInStatusLabel"));

        gridLayout_2->addWidget(logInStatusLabel, 0, 0, 1, 5);

        usernameLabel = new QLabel(logInGroup);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));

        gridLayout_2->addWidget(usernameLabel, 1, 0, 1, 1);

        usernameLineEdit = new KLineEdit(logInGroup);
        usernameLineEdit->setObjectName(QString::fromUtf8("usernameLineEdit"));
        usernameLineEdit->setUrlDropsEnabled(false);
        usernameLineEdit->setProperty("showClearButton", QVariant(true));

        gridLayout_2->addWidget(usernameLineEdit, 1, 1, 1, 3);

        registeredCheckBox = new QCheckBox(logInGroup);
        registeredCheckBox->setObjectName(QString::fromUtf8("registeredCheckBox"));
        registeredCheckBox->setChecked(true);

        gridLayout_2->addWidget(registeredCheckBox, 1, 4, 1, 1);

        passwordLabel = new QLabel(logInGroup);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));

        gridLayout_2->addWidget(passwordLabel, 2, 0, 1, 1);

        passwordLineEdit = new KLineEdit(logInGroup);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setUrlDropsEnabled(false);
        passwordLineEdit->setProperty("showClearButton", QVariant(true));
        passwordLineEdit->setPasswordMode(true);

        gridLayout_2->addWidget(passwordLineEdit, 2, 1, 1, 3);

        rememberCheckBox = new QCheckBox(logInGroup);
        rememberCheckBox->setObjectName(QString::fromUtf8("rememberCheckBox"));

        gridLayout_2->addWidget(rememberCheckBox, 2, 4, 1, 1);

        logInButton = new KPushButton(logInGroup);
        logInButton->setObjectName(QString::fromUtf8("logInButton"));

        gridLayout_2->addWidget(logInButton, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        registerButton = new KPushButton(logInGroup);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));

        gridLayout_2->addWidget(registerButton, 3, 3, 1, 1);


        verticalLayout_3->addWidget(logInGroup);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget->addTab(accountTab, QString());
        joinTab = new QWidget();
        joinTab->setObjectName(QString::fromUtf8("joinTab"));
        verticalLayout_2 = new QVBoxLayout(joinTab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        offerTable = new QTableWidget(joinTab);
        if (offerTable->columnCount() < 7)
            offerTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        offerTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        offerTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        offerTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        offerTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        offerTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        offerTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        offerTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        offerTable->setObjectName(QString::fromUtf8("offerTable"));
        offerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        offerTable->setProperty("showDropIndicator", QVariant(false));
        offerTable->setDragDropOverwriteMode(false);
        offerTable->setAlternatingRowColors(true);
        offerTable->setSelectionMode(QAbstractItemView::SingleSelection);
        offerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        offerTable->horizontalHeader()->setCascadingSectionResizes(true);
        offerTable->horizontalHeader()->setStretchLastSection(true);
        offerTable->verticalHeader()->setVisible(false);
        offerTable->verticalHeader()->setHighlightSections(false);

        verticalLayout_2->addWidget(offerTable);

        tabWidget->addTab(joinTab, QString());
        graphTab = new QWidget();
        graphTab->setObjectName(QString::fromUtf8("graphTab"));
        verticalLayout_5 = new QVBoxLayout(graphTab);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        graphView = new Knights::SeekGraph(graphTab);
        graphView->setObjectName(QString::fromUtf8("graphView"));
        graphView->setFrameShape(QFrame::StyledPanel);
        graphView->setFrameShadow(QFrame::Raised);

        verticalLayout_5->addWidget(graphView);

        tabWidget->addTab(graphTab, QString());
        challengeTab = new QWidget();
        challengeTab->setObjectName(QString::fromUtf8("challengeTab"));
        verticalLayout_6 = new QVBoxLayout(challengeTab);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        ratedCheckBox = new QCheckBox(challengeTab);
        ratedCheckBox->setObjectName(QString::fromUtf8("ratedCheckBox"));

        verticalLayout_6->addWidget(ratedCheckBox);

        autoCheckBox = new QCheckBox(challengeTab);
        autoCheckBox->setObjectName(QString::fromUtf8("autoCheckBox"));

        verticalLayout_6->addWidget(autoCheckBox);

        seekButton = new QPushButton(challengeTab);
        seekButton->setObjectName(QString::fromUtf8("seekButton"));
        seekButton->setCheckable(true);

        verticalLayout_6->addWidget(seekButton);

        challengeListView = new QListView(challengeTab);
        challengeListView->setObjectName(QString::fromUtf8("challengeListView"));

        verticalLayout_6->addWidget(challengeListView);

        tabWidget->addTab(challengeTab, QString());
        consoleTab = new QWidget();
        consoleTab->setObjectName(QString::fromUtf8("consoleTab"));
        verticalLayout_4 = new QVBoxLayout(consoleTab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabWidget->addTab(consoleTab, QString());

        verticalLayout->addWidget(tabWidget);

#ifndef UI_QT_NO_SHORTCUT
        usernameLabel->setBuddy(usernameLineEdit);
        passwordLabel->setBuddy(passwordLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(FicsDialog);
        QObject::connect(registeredCheckBox, SIGNAL(toggled(bool)), passwordLineEdit, SLOT(setEnabled(bool)));
        QObject::connect(registeredCheckBox, SIGNAL(toggled(bool)), ratedCheckBox, SLOT(setEnabled(bool)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FicsDialog);
    } // setupUi

    void retranslateUi(QWidget *FicsDialog)
    {
        logInGroup->setTitle(QString());
        logInStatusLabel->setText(QString());
        usernameLabel->setText(tr2i18n("&Username", 0));
        registeredCheckBox->setText(tr2i18n("This is a registered account", 0));
        passwordLabel->setText(tr2i18n("&Password", 0));
        rememberCheckBox->setText(tr2i18n("Log me in automatically", 0));
        logInButton->setText(tr2i18n("Log in", 0));
        registerButton->setText(tr2i18n("Create an account", 0));
        tabWidget->setTabText(tabWidget->indexOf(accountTab), tr2i18n("Account", 0));
        tabWidget->setTabToolTip(tabWidget->indexOf(accountTab), tr2i18n("Log in to the chess server", 0));
        QTableWidgetItem *___qtablewidgetitem = offerTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(tr2i18n("Player", 0));
        QTableWidgetItem *___qtablewidgetitem1 = offerTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(tr2i18n("Rating", 0));
        QTableWidgetItem *___qtablewidgetitem2 = offerTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(tr2i18n("Time", 0));
        QTableWidgetItem *___qtablewidgetitem3 = offerTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(tr2i18n("Increment", 0));
        QTableWidgetItem *___qtablewidgetitem4 = offerTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(tr2i18n("Rated", 0));
        QTableWidgetItem *___qtablewidgetitem5 = offerTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(tr2i18n("Variant", 0));
        QTableWidgetItem *___qtablewidgetitem6 = offerTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(tr2i18n("Your color", 0));
        tabWidget->setTabText(tabWidget->indexOf(joinTab), tr2i18n("Seek List", 0));
        tabWidget->setTabToolTip(tabWidget->indexOf(joinTab), tr2i18n("Current ads arranged in a list", 0));
        tabWidget->setTabText(tabWidget->indexOf(graphTab), tr2i18n("Seek Graph", 0));
        tabWidget->setTabToolTip(tabWidget->indexOf(graphTab), tr2i18n("Current ads arranged by rating and duration", 0));
        ratedCheckBox->setText(tr2i18n("Rated match", 0));
        autoCheckBox->setText(tr2i18n("Automatically start the game", 0));
        seekButton->setText(tr2i18n("Seek", "Start searching for opponents"));
        tabWidget->setTabText(tabWidget->indexOf(challengeTab), tr2i18n("Challenges", 0));
        tabWidget->setTabToolTip(tabWidget->indexOf(challengeTab), tr2i18n("Post an ad for other players", 0));
        tabWidget->setTabText(tabWidget->indexOf(consoleTab), tr2i18n("Console", 0));
        tabWidget->setTabToolTip(tabWidget->indexOf(consoleTab), tr2i18n("Use custom commands", 0));
        Q_UNUSED(FicsDialog);
    } // retranslateUi

};

namespace Ui {
    class FicsDialog: public Ui_FicsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FICSDIALOG_H

