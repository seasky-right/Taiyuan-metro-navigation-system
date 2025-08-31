#include "Head.h"

using namespace std;

User::User(string u, string p, bool admin)
    : username(u), password(p), isBanned(false), isAdmin(admin) {
}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
bool User::getIsBanned() const { return isBanned; }
bool User::getIsAdmin() const { return isAdmin; }
void User::setBanned(bool banned) { isBanned = banned; }
void User::setPassword(string newPassword) { password = newPassword; }
bool User::verifyPassword(string inputPassword) {
    return password == inputPassword;
}

UserManager::UserManager() {
    loadUsersFromFile();
}

UserManager::~UserManager() {
    saveUsersToFile();
}

void UserManager::loadUsersFromFile() {
    ifstream file(dataFile);
    if (!file.is_open()) {
        users.push_back(User("admin", "admin123", true));
        return;
    }

    string username, password;
    bool isBanned, isAdmin;

    while (file >> username >> password >> isBanned >> isAdmin) {
        users.push_back(User(username, password, isAdmin));
        users.back().setBanned(isBanned);
    }

    file.close();
}

void UserManager::saveUsersToFile() {
    ofstream file(dataFile);
    for (const User& user : users) {
        file << user.getUsername() << " "
            << user.getPassword() << " "
            << user.getIsBanned() << " "
            << user.getIsAdmin() << endl;
    }
    file.close();
}

bool UserManager::registerUser(const string& username, const string& password) {
    for (const User& user : users) {
        if (user.getUsername() == username) {
            return false;
        }
    }
    users.emplace_back(username, password);
    saveUsersToFile();
    return true;
}

User* UserManager::loginAdmin(const string& username, const string& password) {
    for (User& user : users) {
        if (user.getUsername() == username && user.verifyPassword(password)) {
            if (user.getIsAdmin()) {
                currentUser = &user;
                return currentUser;
            }
        }
    }
    return nullptr;
}

User* UserManager::loginUser(const string& username, const string& password) {
    for (User& user : users) {
        if (user.getUsername() == username && user.verifyPassword(password)) {
            if (user.getIsBanned()) {
                cout << "该账号已被封禁！" << endl;
                return nullptr;
            }
            currentUser = &user;
            return currentUser;
        }
    }
    return nullptr;
}

void UserManager::logout() {
    currentUser = nullptr;
}


User* UserManager::getCurrentUser() {
    return currentUser;
}

// 管理员功能：查询用户信息
User* UserManager::userSearch(string username) {
	User* temp = nullptr;
    for (User& user : users) {
        if (user.getUsername() == username) {
            temp = &user;
            return temp;
        }
    }
    return nullptr;
}

// 管理员功能：获取所有用户
vector<User*> UserManager::getAllUsers() {
    vector<User*> userList;
    for (User& user : users) {
        userList.push_back(&user);
    }
    return userList;
}

// 管理员功能：封禁/解封用户
bool UserManager::setUserBanStatus(string username, bool banned) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            user.setBanned(banned);
            saveUsersToFile();
            return true;
        }
    }
    return false;
}

// 管理员功能：删除用户
bool UserManager::deleteUser(string username) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getUsername() == username) {
            users.erase(it);
            saveUsersToFile();
            return true;
        }
    }
    return false;
}