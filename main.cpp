#include <iostream>
#include <set>
#include <queue>
#include <fstream>

using namespace std;

int row[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int col[] = { -1, 1, 1, -1, 2, -2, 2, -2 };

bool isValid(int x, int y, int N) {
    return (x >= 0 && x < N) && (y >= 0 && y < N);
}


class Vertex
{
public:
    int x, y, distance;

    Vertex(int x, int y, int distance = 0): x(x), y(y), distance(distance) {}

    bool operator<(const Vertex& vertex) const {
        return x < vertex.x || (x == vertex.x && y < vertex.y);
    }
};

int findShortestDistance(int N, Vertex start, Vertex finish) {
    set<Vertex> visited;

    queue<Vertex> queueOfVertex;
    queueOfVertex.push(start);

    while (!queueOfVertex.empty()) {
        Vertex vertex = queueOfVertex.front();
        queueOfVertex.pop();

        int x = vertex.x;
        int y = vertex.y;
        int distance = vertex.distance;

        if (x == finish.x && y == finish.y) {
            return distance;
        }

        if (!visited.count(vertex)) {
            visited.insert(vertex);

            for (int i = 0; i < 8; i++) {
                int x1 = x + row[i];
                int y1 = y + col[i];

                if (isValid(x1, y1, N)) {
                    queueOfVertex.push({x1, y1, distance + 1});
                }
            }
        }
    }
    return 0;
}


int main() {

    ofstream fileWrite;
    fileWrite.open("input.txt");
    if(!fileWrite.is_open()) {
        cout<<"errora"<<endl;
    } else {
        int N, x1, y1, x2, y2;
        cout<<"enter N"<<endl;
        cin>>N;
        fileWrite<<N<<endl;
        cout<<"enter the x-coordinate for the starting point"<<endl;
        cin>>x1;
        fileWrite<<x1<<" ";
        cout<<"enter the y-coordinate for the starting point"<<endl;
        cin>>y1;
        fileWrite<<y1<<endl;
        cout<<"enter the x-coordinate for the finish point"<<endl;
        cin>>x2;
        fileWrite<<x2<<" ";
        cout<<"enter the y-coordinate for the finish point"<<endl;
        cin>>y2;
        fileWrite<<y2<<endl;
    }
    fileWrite.close();

    ifstream fileRead;
    fileRead.open("input.txt");
    if(!fileRead.is_open()) {
        cout<<"something went wrong"<<endl;
    } else {
        vector<int> numbersList;
        int x = 0;
        fileRead>>x;
        while (fileRead) {
            numbersList.push_back(x);
            fileRead>>x;
        }

        Vertex start = {numbersList[1], numbersList[2]};
        Vertex finish = {numbersList[3], numbersList[4]};

        ofstream fileResult;
        fileResult.open("result.txt");
        if (!fileResult.is_open()) {
            cout << "something went wrong with result.txt"<<endl;
        } else {
            fileResult<<findShortestDistance(numbersList[0], start, finish);
        }
        fileResult.close();
    }
    fileRead.close();

    return 0;
}


