#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include "network.h"
#include <QFileDialog>

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{
    // Set up the UI and hide elements initially
    ui->setupUi(this);
    ui->errorLabel->hide();
    ui->friendsTable->hide();
    ui->postsLabel->hide();
    ui->returnButton->hide();
    ui->profileNameLabel->hide();
    ui->friendSuggestions->hide();
    ui->addFriendButton->hide();
    ui->pictureLabel->hide();
    ui->changePictureButton->hide();

    // Connect UI buttons and widgets to respective slots
    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkWindow::onLoginClicked);
    connect(ui->friendsTable, &QTableWidget::itemClicked, this, &SocialNetworkWindow::onFriendClicked);
    connect(ui->friendSuggestions, &QTableWidget::itemClicked, this, &SocialNetworkWindow::onSuggestionClicked);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &SocialNetworkWindow::onAddFriendButtonClicked);
    connect(ui->returnButton, &QPushButton::clicked, this, [this]() {
        showProfile(origName);
    });
    connect(ui->changePictureButton, &QPushButton::clicked, this, &SocialNetworkWindow::onChangePictureButtonClicked);

    // Load user and post data from files
    socialNetwork.readUsers("users.txt");
    socialNetwork.readPosts("posts.txt");

    // Enable word wrapping for posts
    ui->postsLabel->setWordWrap(true);
}

SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}

void SocialNetworkWindow::onLoginClicked() {
    QString username = ui->textEdit->toPlainText();
    int userId = socialNetwork.getId(username.toStdString());

    if (userId != -1) {
        // Hide login elements
        ui->loginButton->hide();
        ui->promptLabel->hide();
        ui->textEdit->hide();
        ui->errorLabel->hide();

        // Proceed to the logged-in user's profile
        origName = username;
        showProfile(origName);
    } else {
        // Show error and prompt to try again
        ui->errorLabel->show();
        ui->promptLabel->hide();
        ui->changePictureButton->hide(); // Ensure button is hidden
    }
}

void SocialNetworkWindow::showProfile(QString name) {
    if (name == origName) {
        ui->profileNameLabel->setText("My Profile");
        ui->profileNameLabel->show();
        ui->addFriendButton->hide();
        ui->returnButton->hide();
        ui->changePictureButton->show(); // Show button for logged-in user
    } else {
        ui->profileNameLabel->setText(name);
        ui->profileNameLabel->show();
        ui->addFriendButton->show();
        ui->returnButton->show();
        ui->changePictureButton->hide(); // Hide button for other profiles
    }

    showFriends(name);
    showPosts(name);
    showFriendSuggestions(name);
    showProfilePicture(name);

    if (name != origName) {
        ui->returnButton->show();
    } else {
        ui->returnButton->hide();
    }
}

void SocialNetworkWindow::showProfilePicture(QString username) {
    int userId = socialNetwork.getId(username.toStdString());
    User* user = socialNetwork.getUser(userId);

    if (user != nullptr) {
        QPixmap profilePicture = user->getProfilePicture();
        if (!profilePicture.isNull()) {
            ui->pictureLabel->setPixmap(profilePicture.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            ui->pictureLabel->repaint(); // Force immediate update
            qDebug() << "Displayed profile picture for:" << username;
        } else {
            qDebug() << "Profile picture is null for:" << username;
        }
        ui->pictureLabel->show();
    } else {
        qDebug() << "User not found: " << username;
    }
}

void SocialNetworkWindow::onChangePictureButtonClicked() {
    // Open a file dialog to select a new profile picture
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Profile Picture"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    if (!fileName.isEmpty()) {
        qDebug() << "Selected File Path: " << fileName;  // Debugging output
        int userId = socialNetwork.getId(origName.toStdString());
        User* user = socialNetwork.getUser(userId);

        if (user != nullptr) {
            // Update the profile picture path
            user->setProfilePicturePath(fileName.toStdString());

            // Set the profile picture dynamically
            user->setProfilePicture();

            // Refresh the displayed profile picture
            showProfilePicture(origName);

            // Save changes to persist data
            saveUserChanges();

            qDebug() << "Updated and displayed new profile picture for user: " << origName;
        }
    }
}

void SocialNetworkWindow::saveUserChanges() {
    socialNetwork.writeUsers("users.txt");
}

void SocialNetworkWindow::showFriends(QString username){
    //get how mnay friends user has and set that to the size of the table
    int userId = socialNetwork.getId(username.toStdString());
    ui->friendsTable->setRowCount(socialNetwork.getUser(userId)->getFriends().size());
    ui->friendsTable->setColumnCount(1);


    //loop to populate the table with friend names
    int row = 0;
    for(int currFriend: socialNetwork.getUser(userId)->getFriends()){
        //get the name of friend from their ID
        QString friendName = QString::fromStdString(socialNetwork.getUser(currFriend)->getName());
        //create and set the name of the item for the table
        QTableWidgetItem *item = new QTableWidgetItem(friendName);
        item->setData(Qt::UserRole, currFriend);
        ui->friendsTable->setItem(row, 0, item);

        row++;
    }
    ui->friendsTable->show();
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
    // Retrieve the friend's ID from the item’s data
    int friendId = item->data(Qt::UserRole).toInt();

    // Retrieve the friend's name using the friend ID
    QString friendName = QString::fromStdString(socialNetwork.getUser(friendId)->getName());

    // Display the friend's profile
    showProfile(friendName);
}

void SocialNetworkWindow::showFriendSuggestions(QString username){
    int closeness = 10;
    int user = socialNetwork.getId(username.toStdString());
    std::vector<int> suggestions = socialNetwork.suggestFriends(user, closeness);

    //set the dimentions of friendSuggestions
    ui->friendSuggestions->setColumnCount(1);
    ui->friendSuggestions->setRowCount(suggestions.size());

    //add each suggestion to the tabel 'friendSuggestions'
    int row = 0;
    for(auto suggestionId: suggestions){
        QString friendName = QString::fromStdString(socialNetwork.getUser(suggestionId)->getName());
        QTableWidgetItem* item = new QTableWidgetItem(friendName);
        item->setData(Qt::UserRole, suggestionId);
        ui->friendSuggestions->setItem(row, 0, item); ///
        row++;
    }
    ui->friendSuggestions->show();
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

void SocialNetworkWindow::saveFriendChanges(){
    //rewrites the file to incorporate any changes
    socialNetwork.writeUsers("users.txt");
}

void SocialNetworkWindow::savePostsChanges(){
    //rewrites the file to incorporate any changes
    socialNetwork.writePosts("posts.txt");
}
