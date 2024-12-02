#include "user.h"
#include <filesystem>
#include <iostream>

User::User() { //default constructor
    id_ = 0;
    name_ = "";
    year_ = 0;
    zip_ = 0;
    friends_ = std::set<int>();

    //set deault picture
    profilePicture_ = QPixmap("pfp/default.jpeg");
}

User::User(int id, std::string name, int year, int zip, std::set<int> friends, std::string path){
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = friends;
    profilePicturePath_ = path;

    setProfilePicture();

    //set profilePucure is path is provided, else set to default
    if(!profilePicturePath_.empty()){
        QString qPath = QString::fromStdString(profilePicturePath_);
        QPixmap pixmap;
        if(pixmap.load(qPath)){ //valid path set
            profilePicture_ = pixmap;
        }
        else{ //error loading path
            profilePicture_ = QPixmap("pfp/default.jpeg");
        }
    } else { //if no path is provided, use a default profile picture
        profilePicture_ = QPixmap("pfp/default.jpeg");
    }

}

void User::addFriend(int id){ 
    friends_.insert(id);
}

void User::deleteFriend(int id){
    friends_.erase(id);
}
 
int User::getId(){
    return id_;
}
       
std::string User::getName(){
    return name_;
}
       
int User::getYear(){
    return year_;
}
        
int User::getZip(){
    return zip_;
}

std::set<int>& User::getFriends(){
    return friends_;
}

void User::addPost(Post* post){
    messages_.push_back(post);
}

std::vector<Post*>& User::getPosts(){
    return messages_;
}

std::string User::getPostsString(int howMany, bool showOnlyPublic){
    std::string result;
    int count = 0;

    for (auto it = messages_.rbegin(); it != messages_.rend() && count < howMany; ++it) {
        Post* post = *it;
        
        if (showOnlyPublic && !post->getIsPublic()) {
            continue;
        }

        if (!result.empty()) {
            result += "\n\n";
        }
        
        result += post->toString();
        count++;
    }
    return result;
}

void User::sortPostsByMessageId() {
    std::sort(messages_.begin(), messages_.end(), [](const Post* a, const Post* b) {
        return a->getMessageId() < b->getMessageId();
    });
}

void User::setProfilePicturePath(std::string path) {
    std::filesystem::path filePath(path);
    if (!path.empty()) {
        std::string fileName = filePath.filename().string();
        profilePicturePath_ = "pfp/" + fileName;
    } else {
        profilePicturePath_ = "pfp/default.jpeg";
    }
}

std::string User::getProfilePicturePath() {
    return profilePicturePath_;
}

void User::setProfilePicture() {
    QString qPath = QString::fromStdString(profilePicturePath_);
    QPixmap pixmap;
    if (!pixmap.load(qPath)) {
        std::cerr << "Failed to load profile picture from: " << profilePicturePath_ << std::endl;
        profilePicture_ = QPixmap("pfp/default.jpeg");
        profilePicturePath_ = "pfp/default.jpeg";
    } else {
        profilePicture_ = pixmap;
        std::cout << "Profile picture loaded successfully from: " << profilePicturePath_ << std::endl;
    }
}

QPixmap User::getProfilePicture() {
    return profilePicture_;
}
