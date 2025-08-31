#pragma once

#include <string>
#include <vector>
#include <fstream>

using namespace std;

// �û���
class User {
private:
    string username;
    string password;
    bool isBanned;
    bool isAdmin;

public:
    User(string u, string p, bool admin = false);
    string getUsername() const;
    string getPassword() const;
    bool getIsBanned() const;
    bool getIsAdmin() const;
    void setBanned(bool banned);
    void setPassword(string newPassword);
    bool verifyPassword(string inputPassword);
};

// �û�������
class UserManager {
private:
    vector<User> users;
    string dataFile = "users.dat";
    User* currentUser = nullptr;

public:
    UserManager();
    ~UserManager();
    void loadUsersFromFile();
    void saveUsersToFile();
    bool registerUser(const string& username, const string& password);
    User* loginUser(const string& username, const string& password);
    void logout();
    User* getCurrentUser();
    User* userSearch(string username);
    vector<User*> getAllUsers();
	bool setUserBanStatus(string username, bool banned);
    bool deleteUser(string username);
    User* loginAdmin(const string& username, const string& password);
};
