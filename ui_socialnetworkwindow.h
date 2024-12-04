/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworkWindow
{
public:
    QWidget *centralwidget;
    QLabel *promptLabel;
    QPushButton *loginButton;
    QTextEdit *textEdit;
    QLabel *errorLabel;
    QLabel *profileNameLabel;
    QTableWidget *friendsTable;
    QLabel *postsLabel;
    QPushButton *returnButton;
    QTableWidget *friendSuggestions;
    QPushButton *addFriendButton;
    QLabel *pictureLabel;
    QPushButton *changePictureButton;
    QPushButton *themeToggleButton;
    QLineEdit *friendSearchBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->resize(800, 600);
        SocialNetworkWindow->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        promptLabel = new QLabel(centralwidget);
        promptLabel->setObjectName("promptLabel");
        promptLabel->setGeometry(QRect(260, 160, 361, 41));
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(350, 240, 100, 32));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(300, 200, 201, 31));
        errorLabel = new QLabel(centralwidget);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setGeometry(QRect(270, 160, 301, 41));
        profileNameLabel = new QLabel(centralwidget);
        profileNameLabel->setObjectName("profileNameLabel");
        profileNameLabel->setGeometry(QRect(50, 20, 141, 16));
        friendsTable = new QTableWidget(centralwidget);
        friendsTable->setObjectName("friendsTable");
        friendsTable->setGeometry(QRect(600, 50, 181, 341));
        friendsTable->horizontalHeader()->setCascadingSectionResizes(false);
        friendsTable->horizontalHeader()->setStretchLastSection(true);
        friendsTable->verticalHeader()->setVisible(true);
        friendsTable->verticalHeader()->setStretchLastSection(false);
        postsLabel = new QLabel(centralwidget);
        postsLabel->setObjectName("postsLabel");
        postsLabel->setGeometry(QRect(50, 210, 541, 291));
        postsLabel->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignTop);
        returnButton = new QPushButton(centralwidget);
        returnButton->setObjectName("returnButton");
        returnButton->setGeometry(QRect(200, 50, 111, 31));
        friendSuggestions = new QTableWidget(centralwidget);
        friendSuggestions->setObjectName("friendSuggestions");
        friendSuggestions->setGeometry(QRect(600, 400, 181, 151));
        friendSuggestions->horizontalHeader()->setStretchLastSection(true);
        addFriendButton = new QPushButton(centralwidget);
        addFriendButton->setObjectName("addFriendButton");
        addFriendButton->setGeometry(QRect(200, 10, 100, 32));
        pictureLabel = new QLabel(centralwidget);
        pictureLabel->setObjectName("pictureLabel");
        pictureLabel->setGeometry(QRect(50, 50, 101, 91));
        changePictureButton = new QPushButton(centralwidget);
        changePictureButton->setObjectName("changePictureButton");
        changePictureButton->setGeometry(QRect(50, 160, 101, 24));
        themeToggleButton = new QPushButton(centralwidget);
        themeToggleButton->setObjectName("themeToggleButton");
        themeToggleButton->setGeometry(QRect(40, 520, 111, 21));
        friendSearchBar = new QLineEdit(centralwidget);
        friendSearchBar->setObjectName("friendSearchBar");
        friendSearchBar->setGeometry(QRect(600, 20, 171, 28));
        SocialNetworkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        SocialNetworkWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkWindow);

        QMetaObject::connectSlotsByName(SocialNetworkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkWindow)
    {
        SocialNetworkWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkWindow", "SocialNetworkWindow", nullptr));
        promptLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Please enter your first and last name to login below:", nullptr));
        loginButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Login", nullptr));
        errorLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Sorry, we cannot find your user. Please try again", nullptr));
        profileNameLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "TextLabel", nullptr));
        postsLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "TextLabel", nullptr));
        returnButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Return to Profile", nullptr));
        addFriendButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add Friend", nullptr));
        pictureLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "TextLabel", nullptr));
        changePictureButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Change Picture", nullptr));
        themeToggleButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Change Theme", nullptr));
        friendSearchBar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkWindow: public Ui_SocialNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
