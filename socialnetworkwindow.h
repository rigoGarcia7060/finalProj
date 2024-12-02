#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H
#include "network.h"
#include <QTableWidgetItem>


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkWindow;
}
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

private:
    Ui::SocialNetworkWindow *ui;
    Network socialNetwork;
    QString origName = "";
    void onLoginClicked();
    void showProfile(QString);
    void showFriends(QString);
    void showPosts(QString);
    void showFriendSuggestions(QString);
    void onFriendClicked(QTableWidgetItem*);
    void onSuggestionClicked(QTableWidgetItem*);
    void onAddFriendButtonClicked();
    void saveFriendChanges();
    void savePostsChanges();
    void showProfilePicture(QString);
    void onChangePictureButtonClicked();
    void saveUserChanges();
};

#endif // SOCIALNETWORKWINDOW_H
