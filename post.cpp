#include "post.h"
#include "network.h"

//default contructor
Post::Post(){
    messageId_ = 0;
    ownerId_ = 0;
    message_ = "";
    likes_ = 0;
}
//parametrized constructor
Post::Post(int messageId, int ownerId, std::string message, int likes){
    messageId_ = messageId;
    ownerId_ = ownerId;
    message_ = message;
    likes_ = likes;
}

std::string Post::toString() const{
    std::string output = "";
    output = message_ + " Liked by " + std::to_string(likes_) + " people"; //given format
    return output;
}
//getter function
int Post::getMessageId() const{
    return this->messageId_;
}
//getter function
int Post::getOwnerId() const{
    return ownerId_;
}
//getter function
std::string Post::getMessage() const{
    return message_;
}
//getter function
int Post::getLikes() const{
    return likes_;
}
//default contructor
IncomingPost::IncomingPost(){
    author_ = "Unkown";
    isPublic_ = false;
}
//parametrized constructor
//derived from Post class
IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author)
    : Post(messageId, ownerId, message, likes) {
        author_ = author;
        isPublic_ = isPublic;
}

std::string IncomingPost::toString() const {
    std::string output;
    if (!isPublic_) {
        output = author_ + " wrote (private): " + Post::toString();
    } 
    else
    {
        output = author_ + " wrote: " + Post::toString();
    }
    return output;
}

//getter function
std::string IncomingPost::getAuthor() const{
    return author_;
}
//getter function
bool IncomingPost::getIsPublic() const{
    return isPublic_;
}