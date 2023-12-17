#include <iostream>
#include "vector.h"
#include <String>
#include "map.h"
#include <fstream>

using namespace std;

struct edge {
    edge() : from(""), to(""), value(0){
    };
    edge(string from, string to, int value) {
        this->from = from;
        this->value = value;
        this->to = to;
    }
    bool operator > (const edge& edge2) {
        if (this->value > edge2.value)
            return 1;
        return 0;
    }
    bool operator < (const edge& edge2) {
        if (this->value < edge2.value)
            return 1;
        return 0;
    }
    string from;
    string to;
    int value;
};

struct disjointSet {
    disjointSet() {};
    string find(string x) {
        if (parent[x] == x)
            return x;
        return find(parent[x]);
    }
    void _union(string x, string y) {
        string rootX = find(x);
        string rootY = find(y);
        parent[rootX] = rootY;
        rank[rootY] += rank[rootX];
    }
    void makeSet(string x) {
        parent.insert(x, x);
        rank.insert(x, 1);
    }
    int rankOf(string x) {
        string rootX = find(x);
        return rank[rootX];
    }
private:
    Map <string, string> parent;
    Map <string, int> rank;

};

template <typename T>
int partition(vector<T> &a, int l, int r) {
    T v = a[(l + r) / 2];
    int i = l;
    int j = r;
    while (i <= j) {
        while (a[i] < v)
            i++;
        while (a[j] > v)
            j--;
        if (i >= j)
            break;
        swap(a[i++], a[j--]);
    }
    return j;
}

int partitionString(vector<string> &a, int l, int r) {
    string v = a[(l + r) / 2];
    int i = l;
    int j = r;
    while (i <= j) {
        while (a[i].compare(v) < 0)
            i++;
        while (a[j].compare(v) > 0)
            j--;
        if (i >= j)
            break;
        swap(a[i++], a[j--]);
    }
    return j;
}

template <typename T>
void qsort(vector<T> &a, int l, int r) {
    if (l < r) {
        int q = partition(a, l, r);
        qsort(a, l, q);
        qsort(a, q + 1, r);
    }
}

void qsortString(vector <string> &a, int l, int r) {
    if (l < r) {
        int q = partitionString(a, l, r);
        qsort(a, l, q);
        qsort(a, q + 1, r);
    }
}

void kruskal(vector<edge> edges) {
    int value = 0;
    qsort(edges, 0, edges.getLength() - 1);
    disjointSet ds;
    vector <string> edgesNames;
    for (int i = 0; i < edges.getLength(); i++) { // Создаем одиночные множества
        ds.makeSet(edges[i].from);
        ds.makeSet(edges[i].to);
    }
    for (int i = 0; i < edges.getLength(); i++) {  // Объединяем изолированные вершины
        if (ds.rankOf(edges[i].from) == 1 or ds.rankOf(edges[i].to) == 1) {
            //cout << edges[i].from  << ' ' << ds.rankOf(edges[i].from) << ' ' << edges[i].to  << ds.rankOf(edges[i].to) << '\n';
            ds._union(edges[i].from, edges[i].to);
            value += edges[i].value;
            edgesNames.push(edges[i].from + " " + edges[i].to);
        }
    }
    for (int i = 0; i < edges.getLength(); i++) {  // Объединяем неизолированные вершины
        if (ds.find(edges[i].from) != ds.find(edges[i].to)) {
            ds._union(edges[i].from, edges[i].to);
            value += edges[i].value;
            edgesNames.push(edges[i].from + " " + edges[i].to);
        }
    }
    qsortString(edgesNames, 0, edgesNames.getLength() - 1);
    for (int i = 0; i < edgesNames.getLength(); i++) {
        cout << edgesNames[i] << '\n';
    }
    cout << value << '\n';
}

int main()
{
    setlocale(0, "");
    string pathToFile;
    cout << "Введите путь к файлу: ";
    cin >> pathToFile;
    ifstream input;
    input.open(pathToFile);
    while (!input.is_open()) {
        cout << "Введите верный путь к файлу: ";
        cin >> pathToFile;
        input.open(pathToFile);
    }
    string line;
    getline(input, line);
    vector<string> elementsName;
    string token = "";
    int i = 0;
    while (i < line.length()) {
        if (line[i] == ' ' or line[i] == '\t' or line[i] == '\n') {
            if (token != "") {
                elementsName.push(token);
                token = "";
            }
        }
        else {
            token += line[i];
        }
        i++;
    }
    if (token != "") {
        elementsName.push(token);
        token = "";
    }
    int n = elementsName.getLength();
    vector<edge> edges;
    int counter = 0;
    while (!input.eof()) {
        string line;
        getline(input, line);
        vector<int> elements;
        string token = "";
        int i = 0;
        while (i < line.length()) {
            if (line[i] == ' ' or line[i] == '\t' or line[i] == '\n') {
                if (token != "") {
                    elements.push(stoi(token));
                    token = "";
                }
            }
            else {
                token += line[i];
            }
            i++;
        }
        if (token != "") {
            elements.push(stoi(token));
            token = "";
        }
        if (elements.getLength() != n) {
            cout << "Неверная матрица смежности!\n";
            system("pause");
            return 1;
        }
        for (int i = 0; i < counter; i++) {
            if (elements[i] != 0)
                edges.push(edge(elementsName[i], elementsName[counter], elements[i]));
        }
        counter++;
    }
    if (counter != n) {
        cout << "Неверная матрица смежности!\n";
        system("pause");
        return 1;
    }
    input.close();
    kruskal(edges);
    system("pause");
    return 0;
}
