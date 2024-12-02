#ifndef POST_H
#define POST_H

#include<string> 
class Post{
    public:
       //Default constructor
       //pre: N/A
       //post: initialize members with default values
       Post();
       //parametrized constructor
       //pre: message is non empty 
       //post: creates a Post object with values given
       Post(int messageId, int ownerId, std::string message, int likes);
       //pre: none
       //post: returns string with posts content and like count
       virtual std::string toString() const;
       //pre: none
       //post: returns the messageId of the post
       int getMessageId() const;
       //pre: none
       //post:returns ownerId value
       int getOwnerId() const;
       //pre: none
       //post: returns content of post in string form
       std::string getMessage() const;
       //pre: none 
       //post: returns num of likes on a post
       int getLikes() const;
       //pre: none
       //post: returns empty string in parent class and auhtor name in child class
       virtual std::string getAuthor() const { return "";}
       //pre: none
       //post:  returns true in base class and visability status in derived class
       virtual bool getIsPublic() const { return true; } 
    private:
        int messageId_;
        int ownerId_;
        std::string message_;
        int likes_;
};

class IncomingPost: public Post{
    public:
        //Default constructor
        //pre: none
        //post: creates an IncomingPost object with default values
        IncomingPost();
        //Parameterized constructor
        //pre: mesageId, onwerId, likes >= 0
        //     author, message are non empty
        //post: creates IncomingPost object with specified parameters
        IncomingPost(int messageId, int ownerId, std::string message, int likes,
                    bool isPublic, std::string author);
        //pre: none
        //post:returns formatted string of post
        std::string toString() const override;
        //pre: none
        //post: returns  authors name in string form
        std::string getAuthor() const override;
        //pre: none
        //post: returns true if post is public & false if private
        bool getIsPublic() const override;
    private:
        std::string author_;
        bool isPublic_;
};

#endif