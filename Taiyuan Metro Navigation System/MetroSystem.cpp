#include "Head.h"

Station::Station(int id, string name, vector<string> lines)
    : id(id), name(name), lines(lines) {
}

void Station::display_Station() {
    cout << "Station ID: " << id << ", Name: " << name << ", Lines: ";
    for (string line : lines) {
        cout << line << " ";
    }
    cout << endl;
}

void Station::add_line(string line) {
    lines.push_back(line);
}

Connection::Connection(int to, int t, string line)
    : to_station(to), time(t), line(line) {
}

Station MetroSystem::getStation(int index) const {
    if (index >= 0 && index < stations.size()) {
        return stations[index];
    }
    return Station(-1, "δ֪վ��", {});
}

const vector<Station>& MetroSystem::getAllStations() const {
    return stations;
}

string MetroSystem::get_Stationname(int stationId) {
    if (stationId >= 0 && stationId < stations.size()) {
        return stations[stationId].name;
    }
    return "";
}

void MetroSystem::addStation(Station station) {
    stations.push_back(station);
    adj_list.resize(stations.size());
}

void MetroSystem::addConnection(int from_id, int to_id, int time, string line) {
    if (from_id >= stations.size() || to_id >= stations.size()) {
        cerr << "Invalid station ID" << endl;
        return;
    }
    adj_list[from_id].push_back(Connection(to_id, time, line));
    adj_list[to_id].push_back(Connection(from_id, time, line)); // ����ͼ
}

//BFS�㷨Ѱ�����·��
RouteResult MetroSystem::findShortestPath(int startId, int endId) {
	vector<bool> visited(stations.size(), false);
	vector<int> previous(stations.size(), -1);
	vector<int> distance(stations.size(), INT_MAX);



	queue<int> q;
	q.push(startId);
	visited[startId] = true;
	distance[startId] = 0;

	while (!q.empty()) {
		int current = q.front();
		q.pop();

		if (current == endId) {
			break; 
		}

		for (const Connection& conn : adj_list[current]) {
			if (!visited[conn.to_station]) {
				visited[conn.to_station] = true;
				distance[conn.to_station] = distance[current] + conn.time;
				previous[conn.to_station] = current;
				q.push(conn.to_station);
			}
		}
	}

	// �ؽ�·��
	vector<int> path;
	for (int at = endId; at != -1; at = previous[at]) {
		path.push_back(at);
	}
	reverse(path.begin(), path.end());


	int totalTime = 0;
	int transferCount = 0;
	string currentLine = "";

	for (int i = 0; i < path.size() - 1; i++) {
		for (const Connection& conn : adj_list[path[i]]) {
			if (conn.to_station == path[i + 1]) {
				totalTime += conn.time;

				// ����Ƿ񻻳�
				if (!currentLine.empty() && conn.line != currentLine) {
					transferCount++;
				}
				currentLine = conn.line;
				break;
			}
		}
	}

	return { path, totalTime, transferCount };

}

void initialize_Taiyuanmetro(MetroSystem& metro) {
	metro.addStation(Station(0, "̫��", { "2����" }));
	metro.addStation(Station(1, "���ƺ", { "2����" }));
	metro.addStation(Station(2, "����", { "2����" }));
	metro.addStation(Station(3, "ʤ����", { "2����" }));
	metro.addStation(Station(4, "����", { "2����" }));
	metro.addStation(Station(5, "����Ӫ", { "2����" }));
	metro.addStation(Station(6, "������", { "2����" }));
	metro.addStation(Station(7, "������", { "2����" }));
	metro.addStation(Station(8, "������", { "1����","2����" }));
	metro.addStation(Station(9, "������", { "2����" }));
	metro.addStation(Station(10, "���ڻ�", { "2����" }));
	metro.addStation(Station(11, "�����Ͻ�", { "2����" }));
	metro.addStation(Station(12, "�����", { "2����" }));
	metro.addStation(Station(13, "ѧ����", { "2����" }));
	metro.addStation(Station(14, "���л�", { "2����" }));
	metro.addStation(Station(15, "������", { "2����" }));
	metro.addStation(Station(16, "���˽�", { "2����" }));
	metro.addStation(Station(17, "���ǹ�԰", { "2����" }));
	metro.addStation(Station(18, "�ν�", { "2����" }));
	metro.addStation(Station(19, "��������", { "2����" }));
	metro.addStation(Station(20, "������", { "2����" }));
	metro.addStation(Station(21, "ͨ���", { "2����" }));
	metro.addStation(Station(22, "��������", { "2����" }));
	metro.addStation(Station(23, "����", { "2����" }));

	metro.addStation(Station(24, "������", { "1����" }));
	metro.addStation(Station(25, "����·", { "1����" }));
	metro.addStation(Station(26, "����վ", { "1����" }));
	metro.addStation(Station(27, "����·", { "1����" }));
	metro.addStation(Station(28, "С����", { "1����" }));
	metro.addStation(Station(29, "̫ԭ����ѧ", { "1����" }));
	metro.addStation(Station(30, "��԰·", { "1����" }));
	metro.addStation(Station(31, "����", { "1����" }));
	metro.addStation(Station(32, "��һ�㳡", { "1����" }));
	metro.addStation(Station(33, "̫ԭվ���㳡", { "1����" }));
	metro.addStation(Station(34, "̫ԭվ���㳡", { "1����" }));
	metro.addStation(Station(35, "�¼ҹ�", { "1����" }));
	metro.addStation(Station(36, "������", { "1����" }));
	metro.addStation(Station(37, "˫����", { "1����" }));
	metro.addStation(Station(38, "��ʮ����", { "1����" }));
	metro.addStation(Station(39, "���綫��", { "1����" }));
	metro.addStation(Station(40, "ѧ������", { "1����" }));
	metro.addStation(Station(41, "��̹����", { "1����" }));
	metro.addStation(Station(42, "̫ԭ��վ���㳡", { "1����" }));
	metro.addStation(Station(43, "��Ӫ", { "1����" }));
	metro.addStation(Station(44, "����", { "1����" }));
	metro.addStation(Station(45, "����1��2�ź�վ¥", { "1����" }));
	metro.addStation(Station(46, "����3�ź�վ¥", { "1����" }));


	metro.addConnection(0, 1, 3, "2����");
	metro.addConnection(1, 2, 3, "2����");
	metro.addConnection(2, 3, 3, "2����");
	metro.addConnection(3, 4, 3, "2����");
	metro.addConnection(4, 5, 3, "2����");
	metro.addConnection(5, 6, 3, "2����");
	metro.addConnection(6, 7, 3, "2����");
	metro.addConnection(7, 8, 3, "2����");
	metro.addConnection(8, 9, 3, "2����");
	metro.addConnection(9, 10, 3, "2����");
	metro.addConnection(10, 11, 3, "2����");
	metro.addConnection(11, 12, 3, "2����");
	metro.addConnection(12, 13, 3, "2����");
	metro.addConnection(13, 14, 3, "2����");
	metro.addConnection(14, 15, 3, "2����");
	metro.addConnection(15, 16, 3, "2����");
	metro.addConnection(16, 17, 3, "2����");
	metro.addConnection(17, 18, 3, "2����");
	metro.addConnection(18, 19, 3, "2����");
	metro.addConnection(19, 20, 3, "2����");
	metro.addConnection(20, 21, 3, "2����");
	metro.addConnection(21, 22, 3, "2����");
	metro.addConnection(22, 23, 3, "2����");

	metro.addConnection(24, 25, 2, "1����");
	metro.addConnection(25, 26, 2, "1����");
	metro.addConnection(26, 27, 2, "1����");
	metro.addConnection(27, 28, 2, "1����");
	metro.addConnection(28, 29, 2, "1����");
	metro.addConnection(29, 30, 2, "1����");
	metro.addConnection(30, 8, 2, "1����");
	metro.addConnection(8, 31, 2, "1����");
	metro.addConnection(31, 32, 2, "1����");
	metro.addConnection(32, 33, 2, "1����");
	metro.addConnection(33, 34, 2, "1����");
	metro.addConnection(34, 35, 2, "1����");
	metro.addConnection(35, 36, 2, "1����");
	metro.addConnection(36, 37, 2, "1����");
	metro.addConnection(37, 38, 2, "1����");
	metro.addConnection(38, 39, 2, "1����");
	metro.addConnection(39, 40, 2, "1����");
	metro.addConnection(40, 41, 2, "1����");
	metro.addConnection(41, 42, 2, "1����");
	metro.addConnection(42, 43, 2, "1����");
	metro.addConnection(43, 44, 2, "1����");
	metro.addConnection(44, 45, 2, "1����");
	metro.addConnection(45, 46, 2, "1����");
}