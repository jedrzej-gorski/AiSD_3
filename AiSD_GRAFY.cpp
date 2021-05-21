#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
#include <fstream>

using namespace std;

vector<vector<int>> genAdjacency(int nVertices) {
    vector<vector<int>> resultVector;
    for (int i = 0; i < nVertices; i++) {
        vector<int> newRow;
        for (int j = 0; j < nVertices; j++) {
            if (j <= i) {
                newRow.push_back(0);
            }
            else {
                newRow.push_back(1);
            }
        }
        resultVector.push_back(newRow);
    }
    return resultVector;
}

vector<vector<int>> genGraph(int nVertices) {
    vector<vector<int>> resultVector;
    for (int i = 0; i <= nVertices - 1; i++) {
        vector<int> newRow;
        for (int j = 0; j <= nVertices + 2; j++) {
            if (j < nVertices) {
                if (i == j) {
                    newRow.push_back(-(i + 1));
                }
                else if (j < i) {
                    if (j == i - 1) {
                        newRow.push_back(j + nVertices + 1);
                    }
                    else {
                        newRow.push_back(j + nVertices + 2);
                    }
                }
                else {
                    if (j == nVertices - 1) {
                        newRow.push_back(nVertices);
                    }
                    else {
                        newRow.push_back(j + 2);
                    }
                }
            }
            else {
                if (j == nVertices) {
                    if (i != nVertices - 1) {
                        newRow.push_back(i + 2);
                    }
                    else {
                        newRow.push_back(0);
                    }
                }
                else if (j == nVertices + 1) {
                    if (i == 0) {
                        newRow.push_back(0);
                    }
                    else {
                        newRow.push_back(1);
                    }
                }
                else {
                    newRow.push_back(i + 1);
                }
            }
        }
        resultVector.push_back(newRow);
    }
    return resultVector;
}

bool DFS_msasiedztwa_main(vector<vector<int>>& adjacencyMatrix, stack<int>& controlStack, vector<bool>& visitedVector, vector<bool>& inStackVector, vector<int>& resVector, int vertex) {
    controlStack.push(vertex);
    inStackVector[vertex] = true;
    visitedVector[vertex] = true;
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        if (i != vertex) {
            if (adjacencyMatrix[vertex][i]) {
                if (inStackVector[i]) {
                    return false;
                }
                if (visitedVector[i]) {
                    continue;
                }
                if (!DFS_msasiedztwa_main(adjacencyMatrix, controlStack, visitedVector, inStackVector, resVector, i)) {
                    return false;
                }
            }
        }
        else {
            continue;
        }
    }
    inStackVector[vertex] = false;
    resVector.push_back(controlStack.top() + 1);
    controlStack.pop();
    return true;
}

vector<int> DFS_msasiedztwa_start(vector<vector<int>>& adjacencyMatrix) {
    vector<int> resVector;
    vector<bool> visitedVector(adjacencyMatrix.size(), false);
    vector<bool> inStackVector(adjacencyMatrix.size(), false);
    stack<int> controlStack;
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        if (visitedVector[i]) {
            continue;
        }
        else {
            if (!DFS_msasiedztwa_main(adjacencyMatrix, controlStack, visitedVector, inStackVector, resVector, i)) {
                resVector.push_back(adjacencyMatrix.size() + 1);
                return resVector;
            }
        }
    }
    reverse(resVector.begin(), resVector.end());
    return resVector;
}

bool DEL_msasiedztwa_main(vector<vector<int>>& adjacencyMatrix, vector<int>& resVector, vector<bool>& hasPredecessor, vector<bool>& isRemoved) {
    bool hasRemoved = true;
    while (hasRemoved) {
        hasRemoved = false;
        for (int j = 0; j < adjacencyMatrix.size(); j++) {
            if (isRemoved[j] or !hasPredecessor[j]) {
                continue;
            }
            for (int i = 0; i < adjacencyMatrix.size(); i++) {
                if (isRemoved[i]) {
                    continue;
                }
                if (adjacencyMatrix[i][j]) {
                    goto exitloop;
                }
            }
            hasPredecessor[j] = false;
            exitloop:;
        }
        for (int i = 0; i < adjacencyMatrix.size(); i++) {
            if (!hasPredecessor[i] && !isRemoved[i]) {
                for (int j = 0; j < adjacencyMatrix.size(); j++) {
                    adjacencyMatrix[i][j] = 0;
                }
                isRemoved[i] = true;
                resVector.push_back(i + 1);
                hasRemoved = true;
            }
        }
    }
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = 0; j < adjacencyMatrix.size(); j++) {
            if (adjacencyMatrix[i][j]) {
                resVector.push_back(adjacencyMatrix.size() + 1);
                return false;
            }
        }
    }
    return true;
}

vector<int> DEL_msasiedztwa_start(vector<vector<int>>& adjacencyMatrix) {
    vector<int> resVector;
    vector<bool> hasPredecessor(adjacencyMatrix.size(), false);
    vector<bool> isRemoved(adjacencyMatrix.size(), false);
    for (int j = 0; j < adjacencyMatrix.size(); j++) {
        for (int i = 0; i < adjacencyMatrix.size(); i++) {
            if (adjacencyMatrix[i][j]) {
                hasPredecessor[j] = true;
            }
        }
    }
    DEL_msasiedztwa_main(adjacencyMatrix, resVector, hasPredecessor, isRemoved);
    return resVector;
}

bool DFS_mgrafu_main(vector<vector<int>>& graphMatrix, stack<int>& controlStack, vector<bool>& visitedVector, vector<bool>& inStackVector, vector<int>& resVector, int vertex) {
    controlStack.push(vertex);
    inStackVector[vertex] = true;
    visitedVector[vertex] = true;
    int i;
    if ((i = graphMatrix[vertex][graphMatrix.size()]) == 0) {
        inStackVector[vertex] = false;
        resVector.push_back(controlStack.top() + 1);
        controlStack.pop();
        return true;
    }
    else {
        while (graphMatrix[vertex][i - 1] != i) {
            if (inStackVector[i - 1]) {
                return false;
            }
            if (visitedVector[i - 1]) {
                i = graphMatrix[vertex][i - 1];
                continue;
            }
            if (!DFS_mgrafu_main(graphMatrix, controlStack, visitedVector, inStackVector, resVector, i - 1)) {
                return false;
            }
            i = graphMatrix[vertex][i - 1];
        }
        if (!visitedVector[i - 1]) {
            DFS_mgrafu_main(graphMatrix, controlStack, visitedVector, inStackVector, resVector, i - 1);
        }
    }
    inStackVector[vertex] = false;
    resVector.push_back(controlStack.top() + 1);
    controlStack.pop();
    return true;
}

vector<int> DFS_mgrafu_start(vector<vector<int>>& graphMatrix) {
    vector<int> resVector;
    vector<bool> visitedVector(graphMatrix.size(), false);
    vector<bool> inStackVector(graphMatrix.size(), false);
    stack<int> controlStack;
    for (int i = 0; i < graphMatrix.size(); i++) {
        if (visitedVector[i]) {
            continue;
        }
        else {
            if (!DFS_mgrafu_main(graphMatrix, controlStack, visitedVector, inStackVector, resVector, i)) {
                resVector.push_back(graphMatrix.size() + 1);
                return resVector;
            }
        }
    }
    reverse(resVector.begin(), resVector.end());
    return resVector;
}

void DEL_mgrafu_usuwanie(vector<vector<int>>& graphMatrix, int vertex, vector<bool>& isRemoved) {
    for (int i = 0; i < graphMatrix.size(); i++) {
        if (!isRemoved[i]) {
            if (i != vertex) {
                if (graphMatrix[i][vertex] > 0) {
                    if (graphMatrix[i][graphMatrix.size() + 1] == vertex + 1) {
                        if (graphMatrix[i][vertex] == vertex + 1 + graphMatrix.size()) {
                            graphMatrix[i][graphMatrix.size() + 1] = 0;
                        }
                        else {
                            graphMatrix[i][graphMatrix.size() + 1] = graphMatrix[i][vertex] - graphMatrix.size();
                        }
                    }
                    else {
                        int traversePredecessor = graphMatrix[i][graphMatrix.size() + 1];
                        while (graphMatrix[i][traversePredecessor - 1] - graphMatrix.size() != vertex + 1) {
                            traversePredecessor = graphMatrix[i][traversePredecessor - 1] - graphMatrix.size();
                        }
                        if (graphMatrix[i][vertex] == vertex + 1 + graphMatrix.size()) {
                            graphMatrix[i][traversePredecessor] = traversePredecessor + 1 + graphMatrix.size();
                        }
                        else {
                            graphMatrix[i][traversePredecessor] = graphMatrix[i][vertex];
                        }
                    }
                    int traverseNonIncident = graphMatrix[i][graphMatrix.size() + 2];
                    while (graphMatrix[i][traverseNonIncident - 1] != -traverseNonIncident) {
                        traverseNonIncident = -graphMatrix[i][traverseNonIncident - 1];
                    }
                    graphMatrix[i][traverseNonIncident - 1] = -(vertex + 1);
                    graphMatrix[i][vertex] = -(vertex + 1);
                }
            }
            else {
                queue<int> deleteQueue;
                for (int j = 0; j < graphMatrix.size(); j++) {
                    if (graphMatrix[vertex][j] > 0) {
                        deleteQueue.push(j);
                    }
                }
                int traverseNonIncident = graphMatrix[vertex][graphMatrix.size() + 2];
                while (graphMatrix[vertex][traverseNonIncident - 1] != -traverseNonIncident) {
                    traverseNonIncident = -graphMatrix[vertex][traverseNonIncident - 1];
                }
                while (deleteQueue.size() > 0) {
                    graphMatrix[vertex][traverseNonIncident - 1] = -(deleteQueue.front() + 1);
                    deleteQueue.pop();
                    traverseNonIncident = -graphMatrix[vertex][traverseNonIncident - 1];
                }
                graphMatrix[vertex][traverseNonIncident - 1] = -traverseNonIncident;
                graphMatrix[vertex][graphMatrix.size()] = 0;
            }
        }
    }
}

vector<int> DEL_mgrafu_start(vector<vector<int>> graphMatrix) {
    vector<int> resVector;
    vector<bool> isRemoved(graphMatrix.size(), false);
    bool hasRemoved = true;
    while (hasRemoved) {
        hasRemoved = false;
        for (int i = 0; i < graphMatrix.size(); i++) {
            if (!graphMatrix[i][graphMatrix.size() + 1] && !isRemoved[i]) {
                DEL_mgrafu_usuwanie(graphMatrix, i, isRemoved);
                isRemoved[i] = true;
                hasRemoved = true;
                resVector.push_back(i + 1);
            }
        }
    }
    for (int i = 0; i < isRemoved.size(); i++) {
        if (!isRemoved[i]) {
            resVector.push_back(graphMatrix.size() + 1);
            return resVector;
        }
    }
    return resVector;
}

int main() {
    int menu;
    fstream file;
    string newLine;
    file.open("wyniki.txt", ios::out);
    while (true) {
        cout << "WYBIERZ OPCJE.\n";
        cout << "[0] - POMIARY DLA GRAFOW WYGENEROWANYCH.\n";
        cout << "[1] - POMIARY DLA GRAFU Z PARAMETRAMI WCZYTANYMI PRZEZ KONSOLE.\n";
        cin >> menu;
        if (menu == 0) {
            for (int i = 1; i <= 10; i++) {
                vector<vector<int>> adjacencyMatrix = genAdjacency(100 * i);
                vector<vector<int>> graphMatrix = genGraph(100 * i);

                auto start = chrono::high_resolution_clock::now();
                DFS_mgrafu_start(graphMatrix);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                newLine = to_string(i * 100) + " " + "DFS-G" + " " + to_string(duration) + "\n";
                cout << "DFS - MACIERZ GRAFU " << i * 100 << "\n";
                file << newLine;

                start = chrono::high_resolution_clock::now();
                DEL_mgrafu_start(graphMatrix);
                end = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                newLine = to_string(i * 100) + " " + "DEL-G" + " " + to_string(duration) + "\n";
                cout << "DEL - MACIERZ GRAFU " << i * 100 << "\n";
                file << newLine;

                start = chrono::high_resolution_clock::now();
                DFS_msasiedztwa_start(adjacencyMatrix);
                end = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                newLine = to_string(i * 100) + " " + "DFS-S" + " " + to_string(duration) + "\n";
                cout << "DFS - MACIERZ SASIEDZTWA " << i * 100 << "\n";
                file << newLine;

                start = chrono::high_resolution_clock::now();
                DEL_msasiedztwa_start(adjacencyMatrix);
                end = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                newLine = to_string(i * 100) + " " + "DEL-S" + " " + to_string(duration) + "\n";
                cout << "DEL - MACIERZ SASIEDZTWA " << i * 100 << "\n";
                file << newLine;
            }
            break;
        }
        else if (menu == 1) {
            int n, e;
            cout << "PODAJ ILOSC WIERZCHOŁKOW.\n";
            cin >> n;
            vector<vector <int>> adjacencyMatrix;
            for (int i = 0; i < n; i++) {
                vector<int> newRow(n, 0);
                adjacencyMatrix.push_back(newRow);
            }
            cout << "PODAJ ILOSC KRAWĘDZI.\n";
            cin >> e;
            cout << "WYPISZ LUKI:\n";
            for (int i = 0; i < e; i++) {
                int x, y;
                while (true) {
                    cin >> x >> y;
                    if (x != y) {
                        break;
                    }
                    cout << "PETLE NIE SA OBSLUGIWANE.\n";
                }
                adjacencyMatrix[x - 1][y - 1] = 1;
            }
            vector<int> result = DFS_msasiedztwa_start(adjacencyMatrix);
            cout << "SORTOWANIE TOPOLOGICZNE: METODA DFS.\n";
            for (int i = 0; i < result.size(); i++) {
                cout << result[i] << "\n";
            }
            result = DEL_msasiedztwa_start(adjacencyMatrix);
            cout << "SORTOWANIE TOPOLOGICZNE, METODA KAHNA.\n";
            for (int i = 0; i < result.size(); i++) {
                cout << result[i] << "\n";
            }
            break;
        }
        else {
            cout << "NIEPOPRAWNA OPCJA.\n";
        }
    }
    file.close();
}