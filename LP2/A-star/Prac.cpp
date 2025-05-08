#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int ROOM_WIDTH = 10;
const int ROOM_HEIGHT = 10;
class Object {
    public:
        int width, height;
        string type;
    
        Object(int w, int h, string t) {
            width = w;
            height = h;
            type = t;
        }
    };
class State{
    public:
        vector<vector<int>> room;
        int objIndex;
        int g;
        int h;

        State(){
            room = vector<vector<int>>(ROOM_HEIGHT, vector<int>(ROOM_WIDTH, 0));
            objIndex = 0;
            g = 0;
            h = 0;
        }

        bool operator > (const State&other) const {
            return (g + h) > (other.g + other.h);
        }
};

vector<Object> objects = {
    {2, 3, "Rect"}, {2, 3, "Rect"}, {2, 3, "Rect"}, {2, 3, "Rect"}, {2, 3, "Rect"}, 
    {2, 2, "Square"}, {2, 2, "Square"}, {2, 2, "Square"}, {2, 2, "Square"}
};

bool canPlace(vector<vector<int>>& room, int x, int y, int w, int h){
    if(x + h > ROOM_HEIGHT || y + w > ROOM_WIDTH){
        return false;
    }
    for(int i = x; i < x + h; i++){
        for(int j = y; j < y + w; j++){
            if(room[i][j]){
                return false;
            }
        }
    }
    return true;
}

void placeObject(vector<vector<int>>& room, int x, int y, int w, int h, int id){
    for(int i = x; i < x + h; i++){
        for(int j = y; j < y + w; j++){
            room[i][j] = id;
        }
    }
}

int heuristic(int index){
    int h = 0;
    for(int i = index; i < objects.size(); i++){
        h += objects[i].width * objects[i].height;
    }
    return h;
}

void print(vector<vector<int>>& room){
    for(int i = 0; i < ROOM_HEIGHT; i++){
        for(int j = 0; j < ROOM_WIDTH; j++){
            if(room[i][j] == 0){
                cout<<". ";
            }else{
                cout<<room[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}

void arrangeObjectAStar(){
    priority_queue<State, vector<State>, greater<State>> pq;

    State start;
    start.objIndex = 0;
    start.g = 0;
    start.h = heuristic(0);

    pq.push(start);

    while(!pq.empty()){
        State current = pq.top();
        pq.pop();
        if(current.objIndex == objects.size()){
            cout<<"Final Arranged Room"<<endl;
            print(current.room);
            return;
        }

        Object obj = objects[current.objIndex];

        for(int i = 0; i < ROOM_HEIGHT; i++){
            for(int j = 0; j < ROOM_WIDTH; j++){
                 if(canPlace(current.room, i, j, obj.width, obj.height)){
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
    cout<<"Arrangement not possible"<<endl;
    
}
int main(){
    arrangeObjectAStar();
    return 0;
}