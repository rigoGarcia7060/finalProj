#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include "network.h"
#include <QFileDialog>
#include <QFile>

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
    , isDarkTheme(true) //default to dark theme
{
    ui->setupUi(this);

    //default theme
    setTheme(":/dark_theme.qss");

    //hide everthing because of login page
    ui->errorLabel->hide();
    ui->friendsTable->hide();
    ui->postsLabel->hide();
    ui->returnButton->hide();
    ui->profileNameLabel->hide();
    ui->friendSuggestions->hide();
    ui->addFriendButton->hide();
    ui->pictureLabel->hide();
    ui->changePictureButton->hide();
    ui->friendSearchBar->hide();
    ui->themeToggleButton->hide();

    //hidden atm but set placeholder text
    ui->friendSearchBar->setPlaceholderText("Search For Friend:");

    //connections
    connect(ui->friendSearchBar, &QLineEdit::textChanged, this, &SocialNetworkWindow::onSearchTextChanged);
    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkWindow::onLoginClicked);
    connect(ui->friendsTable, &QTableWidget::itemClicked, this, &SocialNetworkWindow::onFriendClicked);
    connect(ui->friendSuggestions, &QTableWidget::itemClicked, this, &SocialNetworkWindow::onSuggestionClicked);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &SocialNetworkWindow::onAddFriendButtonClicked);
    connect(ui->returnButton, &QPushButton::clicked, this, [this]() {
        showProfile(origName);
    });
    connect(ui->changePictureButton, &QPushButton::clicked, this, &SocialNetworkWindow::onChangePictureButtonClicked);
    connect(ui->themeToggleButton, &QPushButton::clicked, this, &SocialNetworkWindow::toggleTheme);


    //load user/post data
    //files must be in running directory
    socialNetwork.readUsers("users.txt");
    socialNetwork.readPosts("posts.txt");

    //word wrapping for posts
    ui->postsLabel->setWordWrap(true);
}

SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}
void SocialNetworkWindow::showProfile(QString name) {
    ui->themeToggleButton->show(); //should always show once logged in

    if (name == origName) {
        ui->profileNameLabel->setText("My Profile");
        ui->profileNameLabel->show();
        ui->returnButton->hide();
        ui->changePictureButton->show();
        ui->friendSearchBar->show();
        ui->friendSuggestions->show();

        //only while on others profile
        ui->addFriendButton->hide();
        ui->returnButton->hide();
    }
    else {
        ui->profileNameLabel->setText(name);
        ui->profileNameLabel->show();
        ui->addFriendButton->show();
        ui->returnButton->show();
        ui->returnButton->show();

        // hidden while on others profiles
        ui->changePictureButton->hide();
        ui->friendSuggestions->hide();
    }

    //refreshing information displayed
    showFriends(name);
    showPosts(name);
    showFriendSuggestions(name);
    showProfilePicture(name);
    /*
    if (name != origName) {
        ui->returnButton->show();
    } else {
        ui->returnButton->hide();
    }
    */
}
void SocialNetworkWindow::onSearchTextChanged(const QString& searchText) {//could add a second parameter for name
    //whos profile are we on
    QString currentProfile = ui->profileNameLabel->text();
    int userId;

    // if "My Profile" is displayed use the logged-in user
    if (currentProfile == "My Profile") { //could also use origName global variable
        userId = socialNetwork.getId(origName.toStdString());
    } else {
        userId = socialNetwork.getId(currentProfile.toStdString());
    }

    auto friends = socialNetwork.getUser(userId)->getFriends();

    //clear table
    ui->friendsTable->clearContents();
    ui->friendsTable->setRowCount(0);

    //while search bar is empty display all friends of curr user
    if (searchText.trimmed().isEmpty()) {
        showFriends(currentProfile);
        return;
    }

    //filter friends list by the search term
    int row = 0;
    for (int friendId : friends) {
        User* friendUser = socialNetwork.getUser(friendId);
        if (friendUser != nullptr && QString::fromStdString(friendUser->getName()).contains(searchText, Qt::CaseInsensitive)) {
            ui->friendsTable->insertRow(row);
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(friendUser->getName()));
            item->setData(Qt::UserRole, friendId);
            ui->friendsTable->setItem(row, 0, item);
            row++;
        }
    }

    //no match, display empty list
    if (row == 0) {
        ui->friendsTable->setRowCount(0);
    }
}

void SocialNetworkWindow::onLoginClicked() {
    QString username = ui->textEdit->toPlainText();
    int userId = socialNetwork.getId(username.toStdString());

    if (userId != -1) { //user within system
        ui->loginButton->hide();
        ui->promptLabel->hide();
        ui->textEdit->hide();
        ui->errorLabel->hide();

        //set global variable and proceed to his profile
        origName = username;
        showProfile(origName);
    } else { //not in network
        //show error message
        ui->errorLabel->show();
        ui->promptLabel->hide();
       // ui->changePictureButton->hide();
    }
}

void SocialNetworkWindow::showProfilePicture(QString username) {
    int userId = socialNetwork.getId(username.toStdString());
    User* user = socialNetwork.getUser(userId);

    if (user != nullptr) {//user is in network
        QPixmap profilePicture = user->getProfilePicture();
        if (!profilePicture.isNull()) {
            ui->pictureLabel->setPixmap(profilePicture.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            ui->pictureLabel->repaint();
        }
        ui->pictureLabel->show();
    }
}

void SocialNetworkWindow::onChangePictureButtonClicked() {
    //open file dialog to select a new profile picture
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Profile Picture"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    if (!fileName.isEmpty()) {
        qDebug() << "Selected File Path: " << fileName; //debugging
        int userId = socialNetwork.getId(origName.toStdString());
        User* user = socialNetwork.getUser(userId);

        //user is in network
        if (user != nullptr) {
            user->setProfilePicturePath(fileName.toStdString()); //update users path
            user->setProfilePicture(); //set the path
            showProfilePicture(origName); //refresh
            saveUserChanges(); //save changes / rewrite users.txt file
            //qDebug() << "Updated and displayed new profile picture for user: " << origName;
        }
    }
}
//save changes made to user(s) by rewritting all the users properties on .txt file
void SocialNetworkWindow::saveUserChanges() {
    socialNetwork.writeUsers("users.txt");
}

void SocialNetworkWindow::showFriends(QString username) {
    int userId = socialNetwork.getId(username.toStdString());
    auto friends = socialNetwork.getUser(userId)->getFriends();

    //set up the table horizontally
    ui->friendsTable->clearContents();
    ui->friendsTable->setRowCount(friends.size());
    ui->friendsTable->setColumnCount(1);
    ui->friendsTable->setHorizontalHeaderLabels(QStringList() << "Friends");

    //populate it
    int row = 0;
    for (int friendId : friends) {
        User* friendUser = socialNetwork.getUser(friendId);
        if (friendUser) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(friendUser->getName()));
            item->setData(Qt::UserRole, friendId);
            ui->friendsTable->setItem(row, 0, item);
            row++;
        }
    }
    ui->friendsTable->show(); //showing for everyone
}

void SocialNetworkWindow::showPosts(QString username){
    int id = socialNetwork.getId(username.toStdString());

    if(username != origName){//we only show public
        std::string posts = socialNetwork.getUser(id)->getPostsString(5, true);
        ui->postsLabel->setText(QString::fromStdString(posts));
    }
    else{//were at the users profile so we show priv and public posts
        std::string posts = socialNetwork.getUser(id)->getPostsString(5, false);
        ui->postsLabel->setText(QString::fromStdString(posts));
    }
    ui->postsLabel->show();

}
void SocialNetworkWindow::onFriendClicked(QTableWidgetItem *item) {
    //get ID of friend clicked
    int friendId = item->data(Qt::UserRole).toInt();

    //use ID to get name of friend clicked
    QString friendName = QString::fromStdString(socialNetwork.getUser(friendId)->getName());

    //display
    showProfile(friendName);
}

void SocialNetworkWindow::showFriendSuggestions(QString username) {
    int closeness = 10;
    int user = socialNetwork.getId(username.toStdString());
    std::vector<int> suggestions = socialNetwork.suggestFriends(user, closeness);

    //set up friendSuggestions horizontally as well
    ui->friendSuggestions->setColumnCount(1);
    ui->friendSuggestions->setRowCount(suggestions.size());

    ui->friendSuggestions->setHorizontalHeaderLabels(QStringList() << "Suggested Friends"); //header

    //populate
    int row = 0;
    for (auto suggestionId : suggestions) {
        QString friendName = QString::fromStdString(socialNetwork.getUser(suggestionId)->getName());
        QTableWidgetItem* item = new QTableWidgetItem(friendName);
        item->setData(Qt::UserRole, suggestionId);
        ui->friendSuggestions->setItem(row, 0, item);
        row++;
    }

    //ui->friendSuggestions->show();
}

void SocialNetworkWindow::onSuggestionClicked(QTableWidgetItem *item) {
    int friendId = item->data(Qt::UserRole).toInt();  // retrieving the friend ID stored in UserRole
    int currentUserId = socialNetwork.getId(origName.toStdString());  //get the logged-in user’s ID

    //add the suggested friend to the user's friend list
    socialNetwork.getUser(currentUserId)->addFriend(friendId);

    //for mutural friendship
    socialNetwork.getUser(friendId)->addFriend(currentUserId);

    //save chages to frined list
    saveFriendChanges();

    //refresh the friends list on profile page
    showFriends(origName);
}
void SocialNetworkWindow::onAddFriendButtonClicked() {
    //get the ID of the logged-in user and the ID of the profile being viewed
    int loggedInUserId = socialNetwork.getId(origName.toStdString());
    int viewedUserId = socialNetwork.getId(ui->profileNameLabel->text().toStdString());

    //adding viewed user as a friend to the logged-in user
    socialNetwork.getUser(loggedInUserId)->addFriend(viewedUserId);
    //mutural friendship
    socialNetwork.getUser(viewedUserId)->addFriend(loggedInUserId);

    //save the changes
    saveFriendChanges();

    //refreshing friends list in case it's needed
    showFriends(ui->profileNameLabel->text());
}

void SocialNetworkWindow::toggleTheme() {
    if (isDarkTheme) { //change to light theme
        setTheme(":/light_theme.qss");
        ui->themeToggleButton->setText("Switch to Dark Mode");
    } else { //change to dark theme
        setTheme(":/dark_theme.qss");
        ui->themeToggleButton->setText("Switch to Light Mode");
    }
    isDarkTheme = !isDarkTheme;
}

void SocialNetworkWindow::setTheme(const QString &themePath) {
    QFile themeFile(themePath);
    if (themeFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(themeFile.readAll());
        qApp->setStyleSheet(styleSheet);
        themeFile.close();
        //qDebug() << "Applied theme:" << themePath;
    } else {
        //qDebug() << "Failed to load theme:" << themePath;
    }
}

void SocialNetworkWindow::saveFriendChanges(){
    //rewrites the file to incorporate any changes
    socialNetwork.writeUsers("users.txt");
}

void SocialNetworkWindow::savePostsChanges(){
    //rewrites the file to incorporate any changes
    socialNetwork.writePosts("posts.txt");
}
