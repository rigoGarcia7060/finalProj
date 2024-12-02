#include "network.h"
#include "user.h"
#include<algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <queue>

Network::Network(){
    nextMessageId_ = 0;
}
User* Network::getUser(int id){
    for(auto user: users_){
        if(user->getId() == id)
            return user;
    }
    return nullptr; //user not found 
}

void Network::addUser(User* user){
    users_.push_back(user);
}
        
int Network::addConnection(std::string s1, std::string s2){
    User* user1 = nullptr;
    User* user2 = nullptr;

    //find each user using their name
    for(auto curr: users_){
        if(curr->getName() == s1)
            user1 = curr;
        if(curr->getName() == s2)
            user2 = curr;
    }
    //one of them wasnt it the network and therefor operation cant be done
    if(user1 == nullptr || user2 == nullptr){
        return -1;
    }
    user1->addFriend(user2->getId());
    user2->addFriend(user1->getId());
    return 0;
}
int Network::deleteConnection(std::string s1, std::string s2){
    User* user1 = nullptr;
    User* user2 = nullptr;

    //find each user using their name
    for(auto curr: users_){
        if(curr->getName() == s1)
            user1 = curr;
        if(curr->getName() == s2)
            user2 = curr;
    }
    //one of them wasnt it the network and therefor operation cant be done
    if(user1 == nullptr || user2 == nullptr){
        return -1;
    }
    user1->deleteFriend(user2->getId());
    user2->deleteFriend(user1->getId());
    return 0;
}
//pre:none 
//post:reutrns the id of the User with the matching name
int Network::getId(std::string name){
    for(auto curr: users_){
        if(curr->getName() == name)
            return curr->getId();
    }
    //not found in network 
    return -1;
}
//pre:none
//post:returns size of network
int Network::numUsers(){
    return users_.size();
}

void Network::readUsers(const char* fname) {
    std::ifstream infile(fname);

    if (!infile.is_open()) {
        std::cerr << "Error opening " << fname << std::endl;
        return;
    }

    int totalUsers;
    infile >> totalUsers;
    infile.ignore();

    for (int i = 0; i < totalUsers; i++) {
        int id, year, zip;
        std::string name, friends_line, path;
        std::set<int> friendList;

        // Read ID
        infile >> id;
        infile.ignore();

        // Read Name
        std::getline(infile, name);
        name = name.substr(name.find_first_not_of("\t")); // Trim leading tabs

        // Read Year and Zip
        infile >> year >> zip;
        infile.ignore();

        // Read Friends
        std::getline(infile, friends_line);
        std::istringstream friends_ss(friends_line);
        int friendId;
        while (friends_ss >> friendId) {
            friendList.insert(friendId);
        }

        // Read Path
        infile.get(); // Skip leading tab
        std::getline(infile, path);

        User* user = new User(id, name, year, zip, friendList, path);
        addUser(user);

        // Debugging output
        std::cout << "Loaded User: " << user->getName()
                  << ", Profile Picture Path: " << user->getProfilePicturePath() << std::endl;
    }

    infile.close();
}

void Network::writeUsers(const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    outFile << users_.size() << "\n";

    for (User* user : users_) {
        outFile << user->getId() << "\n\t"
                << user->getName() << "\n\t"
                << user->getYear() << "\n\t"
                << user->getZip() << "\n\t";

        for (int friendId : user->getFriends()) {
            outFile << friendId << " ";
        }
        outFile << "\n\t" << user->getProfilePicturePath() << "\n";
    }

    outFile.close();
}

std::vector<int> Network::shortestPath(int from, int to){ //were using their ID's/Index's
    //declorations
    std::queue<int> q;
    std::vector<bool> visited (users_.size(), 0); //could use unordered_maps for
    std::vector<int> prev (users_.size(), -1);    //a better space complexity 

    visited[from] = true;
    q.push(from);
    //loop that iterates through the whole network
    while (q.size() > 0) {
      int cur = q.front();
      q.pop();
      for (auto neighbor : getUser(cur)->getFriends()) {
        if (!visited[neighbor]) {
          prev[neighbor] = cur;
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }
    }
    //trace steps uisng prev vector
    std::vector<int> output;
    int cur = to;
    while (cur != -1) {
      output.push_back(cur);
      cur = prev[cur];
    }
    //reverses the order so we start with 'from' and ends with 'to'
    reverse(output.begin(), output.end());
    return output;
}
//derived from BFS used in shortestPath but with the condition that 
//it stops when desired distance is reached 
std::vector<int> Network::distanceUser(int from, int& to, int distance){
    std::queue<int> q;
    std::vector<int> prev (users_.size(),-1);
    std::vector<int> dist (users_.size(), -1);
    std::vector<bool> visited(users_.size(), 0);
    std::vector<int> path;

    dist[from] = 0;
    prev[from] = -1;
    visited[from] = true;
    q.push(from);

    //loops while we still have users to reach and we 
    //havent reached our distance goal
    while(!q.empty()){
        int currID = q.front();
        q.pop();
        //if were at the distance we want 
        if(dist[currID] == distance){
            to = currID;
            for(int temp = to; temp != -1; temp = prev[temp]){
                path.push_back(temp);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        for(auto neighbor: getUser(currID)->getFriends()){
            if(!visited[neighbor]){
                visited[neighbor] = true;
                q.push(neighbor);
                dist[neighbor] = dist[currID] + 1;
                prev[neighbor] = currID;
            }
        }
    }
    //no user at specified distance found
    to = -1;
    return {};
}
std::vector<int> Network::suggestFriends(int who, int& score){ //we can also try iterate through the entire file since theyre small
    //declorations 
    std::set<int> existingFriends = getUser(who)->getFriends();
    std::vector<int> muturalFriendCounts(users_.size(), 0);
    std::vector<int> suggestions;

    //iterate through every friend on user 'who'
    for(int friendID : existingFriends){
        for(int friendOfFriendID : getUser(friendID)->getFriends()){
            //check that friendOfFriendID is not the same as 'who'
            //and if friendOfFriendID is already a friend of who 
           if (friendOfFriendID == who || std::find(existingFriends.begin(), existingFriends.end(), friendOfFriendID) != existingFriends.end()) {
                continue;
        }
            //increament the mutural friend count for potential friend
            muturalFriendCounts[friendOfFriendID]++;
        }
    }

    //get the max value in muturalFriendCounts vector which is
    //the highest number of mutural firends that any user shares with 'who'
    score = *std::max_element(muturalFriendCounts.begin(), muturalFriendCounts.end());

    //collect users who have mutural friends >= 'score'
    for (int i = 0; i < users_.size(); i++){
        if (muturalFriendCounts[i] == score && i != who) { 
            suggestions.push_back(i);
        }
    }

    //if no suggestions exist we set score to 0
    if(suggestions.empty()){
        score = 0;
    }
    return suggestions;
}

std::vector<std::vector<int>> Network::groups(){
    //delorations
    std::vector<std::vector<int>> connectedComponents;
    std::vector<bool> visited(users_.size(), false);

    //iteraiton through all users
    //we will need a helper function
    for(int i = 0; i < users_.size(); i++){
        if(!visited[i]){
            std::vector<int> component; //stores connected component
            dfs(i, visited, component); //call helper function to perform DFS from user 'i'
            connectedComponents.push_back(component); //add the component to list
        }
    }
    return connectedComponents;

}

//helper function: recusivley visits unvisited friends
void Network::dfs(int userID, std::vector<bool>& visited, std::vector<int>& component){
    visited[userID] = true; //mark original as visited
    component.push_back(userID); //passed by reference

    //iterate through all friends of current user
    for(int friendID: getUser(userID)->getFriends()){
        if(!visited[friendID]){
            dfs(friendID, visited, component); //recursion
        }
    }
}

void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic) {
    User* user = getUser(ownerId);
    if (user != nullptr) {
        int messageId = nextMessageId_++;  // Use and increment the unique ID counter
        Post* newPost;
        if (isIncoming) {
            newPost = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
        } else {
            newPost = new Post(messageId, ownerId, message, likes);
        }

        user->addPost(newPost);

        // Debugging statement to confirm post details
        std::cout << "Adding Post: ID=" << messageId 
                  << ", UserID=" << ownerId 
                  << ", Content=\"" << newPost->getMessage() << "\"" << std::endl;
    } else {
        std::cout << "User " << ownerId << " not found" << std::endl;
    }
}

std::string Network::getPostsString(int ownerId, int howMany,bool showOnlyPublic){
    //get the user
    User* user = getUser(ownerId);

    //if user is found we call their geTPostsString function
    if(user != nullptr){
        return user->getPostsString(howMany, showOnlyPublic);
    }
    else{//we couldnt find user in the network
        std::cout << "User " << ownerId << "not found" << std::endl;
        return "";
    }
}

int Network::readPosts(const char* fname) {
    std::ifstream infile(fname);

    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << fname << std::endl;
        return -1;
    }

    int totalPosts;
    infile >> totalPosts;
    infile.ignore();

    for (int i = 0; i < totalPosts; ++i) {
        int messageId, ownerId, likes;
        std::string message, authorName, line;
        bool isPublic = true, isIncoming = false;

        // Read messageId
        infile >> messageId;
        infile.ignore();

        // Read message
        std::getline(infile, line);
        message = line.substr(1); // Remove leading tab

        // Read ownerId
        infile >> ownerId;
        infile.ignore();

        // Read likes
        infile >> likes;
        infile.ignore();

        // Determine if it's an IncomingPost
        std::getline(infile, line);
        if (line == "\tpublic" || line == "\tprivate") {
            isIncoming = true;
            isPublic = (line == "\tpublic");

            // Read authorName
            std::getline(infile, line);
            authorName = line.substr(1); // Remove leading tab
        }

        // Add post
        addPost(ownerId, message, likes, isIncoming, authorName, isPublic);
    }

    infile.close();
    return 0;
}

bool comparePosts(Post* a, Post* b) {
    return a->getMessageId() < b->getMessageId();
}

int Network::writePosts(const char* fname) {
    std::ofstream outfile(fname);
    //check that it opened
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << fname << std::endl;
        return -1;
    }
    //vecotr of pointers for more memory efficiency and polymorphism 
    std::vector<Post*> allPosts;
    for (User* user : users_) { //populating 
        std::vector<Post*>& userPosts = user->getPosts();
        allPosts.insert(allPosts.end(), userPosts.begin(), userPosts.end());
    }
    sort(allPosts.begin(), allPosts.end(), comparePosts);
    // write total number of posts
    outfile << allPosts.size() << std::endl;

    // write each post's details with the format we need
    for (const Post* post : allPosts) {
        outfile << post->getMessageId() << std::endl;
        outfile << "\t" << post->getMessage() << std::endl;
        outfile << "\t" << post->getOwnerId() << std::endl;
        outfile << "\t" << post->getLikes() << std::endl;

        if (post->getAuthor() != "") {
            outfile << "\t" << (post->getIsPublic() ? "public" : "private") << std::endl;
            outfile << "\t" << post->getAuthor() << std::endl;
        } else {
            outfile << "\t" << std::endl;  // line 5: empty line for owner Post
            outfile << "\t" << std::endl;  // line 6: empty line for owner Post
        }
    }

    outfile.close();
    return 0;
}
