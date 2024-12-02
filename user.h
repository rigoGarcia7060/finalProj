#ifndef USER_H
#define USER_H
#include<string>
#include "post.h"
#include<set>
#include<QPixmap>

class User{
    private:
        int id_;
        std::string name_;
        int year_;
        int zip_;
        std::set<int>friends_;
        std::vector<Post*> messages_;
        std::string profilePicturePath_;
        QPixmap profilePicture_;
    public:
        //Defeault Contructor 
        User();
        //Initilized Constuctor
        User(int id, std::string name, int year, int zip, std::set<int> friends, std::string profilePicturePath_);
        //pre: none
        //post: an id was added to set<int> friends
        void addFriend(int id);
        //pre: none
        //post: an id from friend set id removed if found
        void deleteFriend(int id);
        //pre: none
        //post: returns the id value 
        int getId();
        //pre: none
        //post: returns name value
        std::string getName();
        //pre: none
        //post: returns year value
        int getYear();
        //pre: none 
        //post: returns zip value
        int getZip();
        //pre: none 
        //post: returns the set of friends 
        std::set<int>& getFriends();

        void addPost(Post*);
        std::vector<Post*>& getPosts();
        std::string getPostsString(int howMany, bool showOnlyPublic);
        void sortPostsByMessageId();
        void setProfilePicturePath(std::string path);
        std::string getProfilePicturePath();
        void setProfilePicture();
        QPixmap getProfilePicture();
};

#endif
