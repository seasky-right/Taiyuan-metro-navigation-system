#pragma once

#include "MetroSystem.h"
#include "User.h"

class UserInterface {
private:
    MetroSystem metro;

public:
    UserInterface();
    void findRoute();
    void showAllStations();
    void User_showMenu();
};

void LoginInterface();

void Rigister_showMenu();

void Admin_showMenu();
