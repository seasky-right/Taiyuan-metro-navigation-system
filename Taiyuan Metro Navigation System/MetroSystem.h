#pragma once
#include <vector>
#include <string>

using namespace std;

struct RouteResult {
    vector<int> path;
    int totalTime;
    int transferCount;
};

struct Station {
    int id;
    string name;
    vector<string> lines;

    Station(int id, string name, vector<string> lines);
    void display_Station();
    void add_line(string line);
};

struct Connection {
    int to_station;
    int time;
    string line;
    Connection(int to, int t, string line);
};

class MetroSystem {
private:
    vector<Station> stations;
    vector<vector<Connection>> adj_list;

public:
    Station getStation(int index) const;
    const vector<Station>& getAllStations() const;
    string get_Stationname(int stationId);
    void addStation(Station station);
    void addConnection(int from_id, int to_id, int time, string line);
    RouteResult findShortestPath(int startId, int endId);
};

void initialize_Taiyuanmetro(MetroSystem& metro);
