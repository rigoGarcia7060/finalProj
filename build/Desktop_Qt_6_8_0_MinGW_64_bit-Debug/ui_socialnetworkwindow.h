/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
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
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->resize(800, 600);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        promptLabel = new QLabel(centralwidget);
        promptLabel->setObjectName("promptLabel");
        promptLabel->setGeometry(QRect(220, 110, 361, 41));
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(310, 190, 100, 32));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(260, 150, 201, 31));
        errorLabel = new QLabel(centralwidget);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setGeometry(QRect(220, 110, 301, 41));
        profileNameLabel = new QLabel(centralwidget);
        profileNameLabel->setObjectName("profileNameLabel");
        profileNameLabel->setGeometry(QRect(50, 20, 141, 16));
        friendsTable = new QTableWidget(centralwidget);
        friendsTable->setObjectName("friendsTable");
        friendsTable->setGeometry(QRect(600, 60, 181, 341));
        friendsTable->horizontalHeader()->setCascadingSectionResizes(false);
        postsLabel = new QLabel(centralwidget);
        postsLabel->setObjectName("postsLabel");
        postsLabel->setGeometry(QRect(40, 210, 541, 341));
        returnButton = new QPushButton(centralwidget);
        returnButton->setObjectName("returnButton");
        returnButton->setGeometry(QRect(610, 20, 161, 32));
        friendSuggestions = new QTableWidget(centralwidget);
        friendSuggestions->setObjectName("friendSuggestions");
        friendSuggestions->setGeometry(QRect(600, 410, 181, 141));
        addFriendButton = new QPushButton(centralwidget);
        addFriendButton->setObjectName("addFriendButton");
        addFriendButton->setGeometry(QRect(200, 10, 100, 32));
        pictureLabel = new QLabel(centralwidget);
        pictureLabel->setObjectName("pictureLabel");
        pictureLabel->setGeometry(QRect(50, 50, 101, 91));
        changePictureButton = new QPushButton(centralwidget);
        changePictureButton->setObjectName("changePictureButton");
        changePictureButton->setGeometry(QRect(50, 160, 101, 24));
        SocialNetworkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
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
        errorLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Sorry we cannot find youre user. Please try again", nullptr));
        profileNameLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "TextLabel", nullptr));
        postsLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "TextLabel", nullptr));
        returnButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Return to Profile", nullptr));
        addFriendButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add Friend", nullptr));
        pictureLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "TextLabel", nullptr));
        changePictureButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Change Picture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkWindow: public Ui_SocialNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
