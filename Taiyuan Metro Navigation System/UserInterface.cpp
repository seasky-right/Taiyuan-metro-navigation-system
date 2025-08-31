#include "Head.h"

//初始化
UserInterface::UserInterface() {
    initialize_Taiyuanmetro(metro);
}

void UserInterface::findRoute() {
    int startId, endId;

    cout << "请输入起点站ID: ";
    cin >> startId;
    cout << "请输入终点站ID: ";
    cin >> endId;

    RouteResult result = metro.findShortestPath(startId, endId);

    cout << "推荐路径: ";
    for (int i = 0; i < result.path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << metro.get_Stationname(result.path[i]);
    }
    cout << endl;

    cout << "预计时间: " << result.totalTime << " 分钟" << endl;

	cout << "换乘次数: " << result.transferCount << " 次" << endl;
}

void UserInterface::showAllStations() {
    cout << "===== 所有站点 =====" << endl;
    const vector<Station>& stations = metro.getAllStations();
    for (const Station& station : stations) {
        cout << station.id << ": " << station.name << " (";
        for (const string& line : station.lines) {
            cout << line ;
        }
        cout << ")" << endl;
    }
}

void UserInterface::User_showMenu() {
    int choice;
    do {
        cout << "===== 太原地铁导航系统 =====" << endl;
        cout << "1. 查询路径" << endl;
        cout << "2. 显示所有站点" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择: ";
        cin >> choice;

        switch (choice) {
        case 1:
            findRoute();
            break;
        case 2:
            showAllStations();
            break;
        }
    } while (choice != 0);
}

//登陆界面
void LoginInterface() {
    int choice;
    UserManager um;
    do {
        cout << "唐风晋韵 锦绣龙城\n";
        cout << "欢迎使用太原地铁导航系统\n";
        cout << "=========================\n";
        cout << "请选择要进行的操作:\n";
        cout << "1.用户登录\n";
        cout << "2.用户注册\n";
        cout << "0.退出系统\n";
        cout << "请选择: ";

        cin >> choice;

        switch (choice) {
        case 1: {
            string username, password;
            cout << "用户名: ";
            cin >> username;
            cout << "密码: ";
            cin >> password;

            if(um.loginAdmin(username, password)) {
                cout << "管理员登录成功!" << endl;
                Admin_showMenu();
            }else if(um.loginUser(username, password)) {
                cout << "登录成功!" << endl;
                UserInterface ui;
                ui.User_showMenu();
            }
            else {
                cout << "用户名或密码错误，或账号已被封禁!" << endl;
            }
            break;
        }
        case 2: {
            Rigister_showMenu();
            break;
        }
        case 0:
            exit(0);
        default:
            cout << "无效选择，请重新输入!" << endl;
        }
    } while (choice != 0);
}

void Rigister_showMenu() {
    UserManager um;
    string username, password;
    cout << "===== 用户注册 =====" << endl;
    cout << "用户名: ";
    cin >> username;
    cout << "密码: ";
    cin >> password;
    if (!um.registerUser(username, password)) {
        cout << "用户名已存在，请选择其他用户名！" << endl;
        return;
    }
    cout << "注册成功！请返回登录界面登录。" << endl;
}

void Admin_showMenu() {
    int choice;
    UserManager um;
    do {
        cout << "===== 管理员操作 =====" << endl;
        cout << "1. 显示所有用户" << endl;
        cout << "2. 用户信息查询" << endl;
        cout << "3. 修改用户密码" << endl;
        cout << "4. 封禁用户账号" << endl;
        cout << "5. 删除用户账号" << endl;
        cout << "0. 注销" << endl;
        cout << "请选择: ";
        cin >> choice;

        switch (choice) {
        case 1:
            um.getAllUsers();
            break;
        case 2: {
            string username;
            cout << "请输入要查询的用户名: ";
            cin >> username;
            if (!um.userSearch(username)) {
                cout << "用户不存在！" << endl;
                break;
            }
            User* user = um.userSearch(username);
            cout << "用户名: " << user->getUsername() << ", 是否封禁: " << (user->getIsBanned() ? "是" : "否") << endl;
            break;
        }case 3: {
            string username, newPassword;
            cout << "请输入要修改的用户名: ";
            cin >> username;
            if (!um.userSearch(username)) {
                cout << "用户不存在！" << endl;
                break;
            }
            cout << "请输入新密码: ";
            cin >> newPassword;
            User* user = um.userSearch(username);
            user->setPassword(newPassword);
            um.saveUsersToFile();
            cout << "密码修改成功！" << endl;
            break;
        }case 4: {
            string username;
            cout << "请输入要封禁的用户名: ";
            cin >> username;
            if (!um.userSearch(username)) {
                cout << "用户不存在！" << endl;
                break;
            }
            User* user = um.userSearch(username);
            if (user->getIsBanned()) {
                int choice1;
                cout << "该账号已被封禁，是否要进行解封？" << endl;
                cout << "1. 是" << endl;
                cout << "2. 否" << endl;
                cin >> choice1;
                switch (choice1) {
                case 1:
                    user->setBanned(false);
                case 2:
                    break;
                default:
                    cout << "无效选择，请重新输入!" << endl;
                }
            }
            else {
                user->setBanned(true);
                cout << "用户已封禁！" << endl;
            }
            break;
        }case 5: {
            string username;
            cout << "请输入要删除的用户名: ";
            cin >> username;
            if (!um.userSearch(username)) {
                cout << "用户不存在！" << endl;
                break;
            }
            um.deleteUser(username);
            cout << "用户已删除！" << endl;
            break;
        }case 0:
            break;
        default:
            cout << "无效选择，请重新输入!" << endl;
        }
    }while (choice != 0);
}