#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include <string>
#include "user.h"

class Network{
    private:
        std::vector<User*> users_;
        int nextMessageId_;
    public: 
        //default constructor 
        Network();
        //pre: populated the network
        //post: returns a User object from network
        //return nullptr if not found
        User* getUser(int id);
        //pre: created a newtwork
        //post: added a User object pointer to its list of Users
        void addUser(User*);
        //pre:s1 and s2 must be valid 
        //post:ands each other to their friends list
        //return -1 if invalid, 0 otherwise
        int addConnection(std::string s1, std::string s2);
        //pre:s1 and s2 must be valid
        //post:removes each other from their friends list
        int deleteConnection(std::string s1, std::string s2);
        //pre:none 
        //post:reutrns the id of the User with the matching name
        //return -1 if not found in network
        int getId(std::string name);
        //pre:none
        //post:returns size of network
        int numUsers();
        void readUsers(const char* fname);
        void writeUsers(const std::string& fname);
        std::vector<int> shortestPath(int from, int to);
        //pre: from must be valid
        //     distance must be non-neg
        //post: vector contaitning the shortest path of ID to a user 'distance' away
        //      if not user is to be found 'to' us set to -1
        std::vector<int> distanceUser(int from, int& to, int distance);
        //pre: who must be valid within Network
        //post: returns vector of ID's of the most compatible mutural friends
        std::vector<int> suggestFriends(int who, int& score);
        //pre: network is populated 
        //post: returns vector of vectors where each vector represents
        //a circular part of the network
        std::vector<std::vector<int>> groups();
        //helper function
        void dfs(int, std::vector<bool>&, std::vector<int>& );
        void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool usPublic);
        std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);
        int readPosts(const char* fname);
        int writePosts(const char* fname);
};

#endif
