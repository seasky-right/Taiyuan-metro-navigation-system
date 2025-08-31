#include "Head.h"

//��ʼ��
UserInterface::UserInterface() {
    initialize_Taiyuanmetro(metro);
}

void UserInterface::findRoute() {
    int startId, endId;

    cout << "���������վID: ";
    cin >> startId;
    cout << "�������յ�վID: ";
    cin >> endId;

    RouteResult result = metro.findShortestPath(startId, endId);

    cout << "�Ƽ�·��: ";
    for (int i = 0; i < result.path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << metro.get_Stationname(result.path[i]);
    }
    cout << endl;

    cout << "Ԥ��ʱ��: " << result.totalTime << " ����" << endl;

	cout << "���˴���: " << result.transferCount << " ��" << endl;
}

void UserInterface::showAllStations() {
    cout << "===== ����վ�� =====" << endl;
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
        cout << "===== ̫ԭ��������ϵͳ =====" << endl;
        cout << "1. ��ѯ·��" << endl;
        cout << "2. ��ʾ����վ��" << endl;
        cout << "0. �˳�" << endl;
        cout << "��ѡ��: ";
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

//��½����
void LoginInterface() {
    int choice;
    UserManager um;
    do {
        cout << "�Ʒ���� ��������\n";
        cout << "��ӭʹ��̫ԭ��������ϵͳ\n";
        cout << "=========================\n";
        cout << "��ѡ��Ҫ���еĲ���:\n";
        cout << "1.�û���¼\n";
        cout << "2.�û�ע��\n";
        cout << "0.�˳�ϵͳ\n";
        cout << "��ѡ��: ";

        cin >> choice;

        switch (choice) {
        case 1: {
            string username, password;
            cout << "�û���: ";
            cin >> username;
            cout << "����: ";
            cin >> password;

            if(um.loginAdmin(username, password)) {
                cout << "����Ա��¼�ɹ�!" << endl;
                Admin_showMenu();
            }else if(um.loginUser(username, password)) {
                cout << "��¼�ɹ�!" << endl;
                UserInterface ui;
                ui.User_showMenu();
            }
            else {
                cout << "�û�����������󣬻��˺��ѱ����!" << endl;
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
            cout << "��Чѡ������������!" << endl;
        }
    } while (choice != 0);
}

void Rigister_showMenu() {
    UserManager um;
    string username, password;
    cout << "===== �û�ע�� =====" << endl;
    cout << "�û���: ";
    cin >> username;
    cout << "����: ";
    cin >> password;
    if (!um.registerUser(username, password)) {
        cout << "�û����Ѵ��ڣ���ѡ�������û�����" << endl;
        return;
    }
    cout << "ע��ɹ����뷵�ص�¼�����¼��" << endl;
}

void Admin_showMenu() {
    int choice;
    UserManager um;
    do {
        cout << "===== ����Ա���� =====" << endl;
        cout << "1. ��ʾ�����û�" << endl;
        cout << "2. �û���Ϣ��ѯ" << endl;
        cout << "3. �޸��û�����" << endl;
        cout << "4. ����û��˺�" << endl;
        cout << "5. ɾ���û��˺�" << endl;
        cout << "0. ע��" << endl;
        cout << "��ѡ��: ";
        cin >> choice;

        switch (choice) {
        case 1:
            um.getAllUsers();
            break;
        case 2: {
            string username;
            cout << "������Ҫ��ѯ���û���: ";
            cin >> username;
            if (!um.userSearch(username)) {
                cout << "�û������ڣ�" << endl;
                break;
            }
            User* user = um.userSearch(username);
            cout << "�û���: " << user->getUsername() << ", �Ƿ���: " << (user->getIsBanned() ? "��" : "��") << endl;
            break;
        }case 3: {
            string username, newPassword;
            cout << "������Ҫ�޸ĵ��û���: ";
            cin >> username;
            if (!um.userSearch(username)) {
                cout << "�û������ڣ�" << endl;
                break;
            }
            cout << "������������: ";
            cin >> newPassword;
            User* user = um.userSearch(username);
            user->setPassword(newPassword);
            um.saveUsersToFile();
            cout << "�����޸ĳɹ���" << endl;
            break;
        }case 4: {
            string username;
            cout << "������Ҫ������û���: ";
            cin >> username;
            if (!um.userSearch(username)) {
                cout << "�û������ڣ�" << endl;
                break;
            }
            User* user = um.userSearch(username);
            if (user->getIsBanned()) {
                int choice1;
                cout << "���˺��ѱ�������Ƿ�Ҫ���н�⣿" << endl;
                cout << "1. ��" << endl;
                cout << "2. ��" << endl;
                cin >> choice1;
                switch (choice1) {
                case 1:
                    user->setBanned(false);
                case 2:
                    break;
                default:
                    cout << "��Чѡ������������!" << endl;
                }
            }
            else {
                user->setBanned(true);
                cout << "�û��ѷ����" << endl;
            }
            break;
        }case 5: {
            string username;
            cout << "������Ҫɾ�����û���: ";
            cin >> username;
            if (!um.userSearch(username)) {
                cout << "�û������ڣ�" << endl;
                break;
            }
            um.deleteUser(username);
            cout << "�û���ɾ����" << endl;
            break;
        }case 0:
            break;
        default:
            cout << "��Чѡ������������!" << endl;
        }
    }while (choice != 0);
}