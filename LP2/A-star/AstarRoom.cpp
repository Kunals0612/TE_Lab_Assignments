#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int ROOM_WIDTH = 10;
const int ROOM_HEIGHT = 10;

class Object {
public:
    int width, height;
    string type;

    Object(int w, int h, string t) : width(w), height(h), type(t) {}
};

class State {
public:
    vector<vector<int>> room;  // 2D room grid
    int objIndex;              // next object to place
    int g, h;                  // cost and heuristic

    State() : objIndex(0), g(0), h(0) {
        room = vector<vector<int>>(ROOM_HEIGHT, vector<int>(ROOM_WIDTH, 0));
    }

    bool operator>(const State& other) const {
        return g + h > other.g + other.h;
    }
};

// Define object list
vector<Object> objects = {
    {2, 3, "Rect"}, {2, 3, "Rect"}, {2, 3, "Rect"},
    {2, 3, "Rect"}, {2, 3, "Rect"},
    {2, 2, "Square"}, {2, 2, "Square"},
    {2, 2, "Square"}, {2, 2, "Square"}
};

// Check if object can be placed at position (x, y)
bool canPlace(vector<vector<int>>& room, int x, int y, int w, int h) {
    if (x + h > ROOM_HEIGHT || y + w > ROOM_WIDTH) return false;
    for (int i = x; i < x + h; i++)
        for (int j = y; j < y + w; j++)
            if (room[i][j]) return false;
    return true;
}

// Place object in room
void placeObject(vector<vector<int>>& room, int x, int y, int w, int h, int id) {
    for (int i = x; i < x + h; i++)
        for (int j = y; j < y + w; j++)
            room[i][j] = id;
}

// Heuristic: remaining area to fill
int heuristic(int index) {
    int h = 0;
    for (int i = index; i < objects.size(); i++)
        h += objects[i].width * objects[i].height;
    return h;
}

// Print final room arrangement
void printRoom(vector<vector<int>>& room) {
    for (int i = 0; i < ROOM_HEIGHT; i++) {
        for (int j = 0; j < ROOM_WIDTH; j++) {
            if (room[i][j] == 0) cout << ". ";
            else cout << room[i][j] << " ";
        }
        cout << endl;
    }
}

void arrangeObjectsAStar() {
    priority_queue<State, vector<State>, greater<State>> pq;

    // Initial empty room
    State start;
    start.objIndex = 0;
    start.g = 0;
    start.h = heuristic(0);

    pq.push(start);

    while (!pq.empty()) {
        State current = pq.top(); pq.pop();

        if (current.objIndex == objects.size()) {
            cout << "Final Room Arrangement:\n";
            printRoom(current.room);
            return;
        }

        Object obj = objects[current.objIndex];

        // Try all positions
        for (int i = 0; i < ROOM_HEIGHT; i++) {
            for (int j = 0; j < ROOM_WIDTH; j++) {
                if (canPlace(current.room, i, j, obj.width, obj.height)) {
                    State next = current;
                    placeObject(next.room, i, j, obj.width, obj.height, current.objIndex + 1);
                    next.objIndex++;
                    next.g += obj.width * obj.height;
                    next.h = heuristic(next.objIndex);
                    pq.push(next);
                }
            }
        }
    }

    cout << "Failed to arrange all objects." << endl;
}

int main() {
    arrangeObjectsAStar();
    return 0;
}
