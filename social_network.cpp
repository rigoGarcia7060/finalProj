#include "network.h"
#include "user.h"
#include <iostream>

//main takes in termianl arguments
//the programs name and file name containing users
int main(int argc, char* argv[]){ 

    if (argc < 3) {
        std::cerr << "Using: " << argv[0] << " users.txt posts.txt\n";
        return 1;
    }
    Network network;

    //infinite loop until user decides to exit 
    while(true){
        // Main menu
        std::cout << "1. Add a user" << std::endl;
        std::cout << "2. Add friend " << std::endl;
        std::cout << "3. Delete friend " << std::endl;
        std::cout << "4. Write to file" << std::endl;
        std::cout << "5. View recent posts of a user " << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter Option: ";

        //record input
        int input = 0;
        std::cin >> input;

        //option 1 was selected ->add a new user
        if (input == 1) {
            //declare variables
            std::string firstName, lastName, fullName;
            int year, zip;

            // propt terminal user
            std::cout << "Enter new user details (name year zip): ";
            std::cin >> firstName >> lastName >> year >> zip;
            fullName = firstName + " " + lastName;
            
            // Create and add user to network
            User* user = new User(network.numUsers(), fullName, year, zip, {});
            network.addUser(user);
        }

        //option 2 was selected-> connect two users
        else if(input == 2){
            std::string user1, user2;
            std::cout << "Please enter the names of two users to connect" << std::endl;
            std::cout << "Enter the first name: ";
            std::cin.ignore();
            std::getline(std::cin, user1);
            std::cout << "Enter the second name: ";
            std::getline(std::cin, user2);
            // impliment the friend connection
            int result = network.addConnection(user1, user2);
            if (result == -1) {
                std::cout << "Whoops! It seems that one or both of the user names inputed could not be found." << std::endl;
            }
        }
        //option 3 was slected-> delete friend connection
        else if(input == 3){
            std::string user1, user2;
            std::cout << "Please enter the names of two users to disconnect" << std::endl;
            std::cout << "Enter the first username: ";
            std::cin.ignore();
            std::getline(std::cin, user1);
            std::cout << "Enter the second username: ";
            std::getline(std::cin, user2);
            // Delete friend connection
            int result = network.deleteConnection(user1, user2);
            if (result == -1) {
                std::cerr << "Whoops! It seems that one or both of the user names inputed could not be found." << std::endl;
            }
        }
        //option 4 was selected-> write to file 
        else if(input == 4){
            std::string fname;
            //prompt for file name
            std::cout << "Please enter the name of the file you would like to write to: ";
            std::cin >> fname;
            //write the users to the file 
            network.writeUsers(const_cast<char*>(fname.c_str()));
        }
        // option 5 was selected -> view posts for a user
        else if (input == 5) {
            std::string firstName, lastName;
            int num;

            // promt user for first and last name
            std::cout << "Enter the user's first name and last name: ";
            std::cin >> firstName >> lastName;

            // prompt user to enter number of recent posts to display
            std::cout << std::endl;
            std::cout << "Enter the number of posts to display: " << std::endl;;
            std::cin >> num;

            std::string name = firstName + " " + lastName;
            int userId = network.getId(name);

            if (userId == -1) {
                std::cout << "Whoops! User " << name << " seems to not exist in file" << std::endl;
            }
            else {
                // displaying the user's most recent posts
                std::string posts = network.getPostsString(userId, num, false);
                std::cout << "Posts for user: " << name << ":\n" << posts << '\n';
            }
        }

        //option 6 was selected-> exit program
        else if (input == 6) {
            std::cout << "Exiting the program. Thank you for using us!" << std::endl;
            break;
        } 
        //invalid input
        else {
            std::cerr << "Invalid value. Exiting program" << std::endl;
            break;
        }
    }
    return 0;
}