#ifndef GRAPHMTX_H
#define GRAPHMTX_H

#include "SeqQueue.h"
#include "MinSpanTree.h"
#include "UFset.h"
#include "minheap.h"
#include <iostream>
using namespace std;
#define DefaultVertices 30
template <class T, class E>
class Graphmtx
{
    friend istream &operator>>(istream &in, Graphmtx<T, E> &G)
    {
        int n, m; //  输入顶点数和边数
        in >> n >> m;
        T vertex1, vertex2;
        for (int i = 0; i < n; i++)
        {
            in >> vertex1;
            G.insertVertex(vertex1);
        }
        E weight;
        for (int i = 0; i < m; i++)
        {
            in >> vertex1 >> vertex2 >> weight;
            int pos1 = G.getVertexPos(vertex1), pos2 = G.getVertexPos(vertex2);
            if (pos1 == -1 || pos2 == -1)
                cout << "边端点信息有误" << endl;
            else
                G.insertEdge(pos1, pos2, weight);
        }
        return in;
    }
    friend ostream &operator<<(ostream &out, Graphmtx<T, E> &G)
    {
        int n = G.NumberOfVertices(), m = G.NumberOfEdges();
        out << n << "," << m << endl;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                E w = G.getWeight(i, j);
                if (w > 0 && w < G.maxWeight)
                {
                    T vertex1 = G.getValue(i), vertex2 = G.getValue(j);
                    out << "(" << vertex1 << "," << vertex2 << "," << w << ")" << endl;
                }
            }
        return out;
    }

public:
    const E maxWeight = 100;
    Graphmtx(int sz = DefaultVertices);
    ~Graphmtx()
    {
        delete[] VerticesList;
        delete[] Edge;
    }
    T getValue(int i)
    {
        return i >= 0 && i < numVertices ? VerticesList[i] : NULL;
    }
    E getWeight(int v1, int v2)
    {
        return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
    }
    int getFirstNeighbor(int v);
    int getNextNeighbor(int v, int w);
    bool insertVertex(const T vertex);
    bool insertEdge(int v1, int v2, E cost);
    bool removeVertex(int v);
    bool removeEdge(int v1, int v2);
    bool GraphEmpty() const
    {
        return numVertices == 0;
    }
    bool GraphFull() const
    {
        return numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2;
    }
    int NumberOfVertices() { return numVertices; }
    int NumberOfEdges() { return numEdges; }
    void DFS(Graphmtx<T, E> &G, const T v);
    void BFS(Graphmtx<T, E> &G, const T v);
    void Kruskal(MinSpanTree<T, E> &MST);
    void Prim(const T u0, MinSpanTree<T, E> &MST);
    void printShortestPath_Dij(T v0);
    void printShortestPath_BF(T v0);

private:
    T *VerticesList; //  顶点表
    E **Edge;        //  邻接矩阵
    int getVertexPos(T vertex)
    {
        for (int i = 0; i < numVertices; i++)
            if (VerticesList[i] == vertex)
                return i;
        return -1; //  找不到该值的顶点则返回-1
    }
    int maxVertices;
    int numEdges;
    int numVertices;
    void DFS(Graphmtx<T, E> &G, int v, bool visited[]);
    void Dijkstra(T v0, E dist[], int path[]);
    void Bellman_Ford(T v0, E dist[], int path[]);
};

template <class T, class E>
Graphmtx<T, E>::Graphmtx(int sz)
{
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    VerticesList = new T[sz];
    Edge = (E **)new E *[maxVertices];
    for (int i = 0; i < maxVertices; i++)
        Edge[i] = new E[maxVertices];
    for (int i = 0; i < maxVertices; i++)
        for (int j = 0; j < maxVertices; j++)
            Edge[i][j] = maxWeight;
}

template <class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v)
{
    if (v != -1)
        for (int col = 0; col < numVertices; col++)
            if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
                return col;
    return -1;
}

template <class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w)
{
    if (v != -1 && w != -1)
        for (int col = w + 1; col < numVertices; col++)
            if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
                return col;
    return -1;
}

template <class T, class E>
bool Graphmtx<T, E>::insertVertex(const T vertex)
{
    if (numVertices == maxVertices)
        return false;
    else
    {
        VerticesList[numVertices++] = vertex;
        return true;
    }
}

template <class T, class E>
bool Graphmtx<T, E>::removeVertex(int v)
{
    if (v < 0 || v >= numVertices)
        return false;
    if (numVertices == 1)
        return false;                     //  只剩一个顶点，不删除
    for (int i = 0; i < numVertices; i++) // 先统计和v有关的边数，修改 numEdges
        if (Edge[v][i] > 0 && Edge[v][i] < maxWeight)
            numEdges--;
    VerticesList[v] = VerticesList[numVertices--]; // 在顶点表中用最后一个顶点替换第v个顶点
    for (int i = 0; i < numVertices; i++)          // 用最后一行和最后一列覆盖第v行列
    {
        Edge[v][i] = Edge[numVertices][i];
        Edge[i][v] = Edge[i][numVertices];
    }
    return true;
}

template <class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)
{
    if (v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && Edge[v1][v2] == maxWeight)
    {
        Edge[v1][v2] = Edge[v2][v1] = cost;
        numEdges++;
        return true;
    }
    return false;
}

template <class T, class E>
void Graphmtx<T, E>::DFS(Graphmtx<T, E> &G, const T v)
{
    int n = G.NumberOfVertices();
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;
    int loc = G.getVertexPos(v);
    DFS(G, loc, visited);
    delete[] visited;
}

template <class T, class E>
void Graphmtx<T, E>::DFS(Graphmtx<T, E> &G, int v, bool visited[])
{
    cout << G.getValue(v) << " ";
    visited[v] = true;
    int w = G.getFirstNeighbor(v);
    while (w != -1)
    {
        if (visited[w] == false)
            DFS(G, w, visited);
        w = G.getNextNeighbor(v, w);
    }
}

template <class T, class E>
void Graphmtx<T, E>::BFS(Graphmtx<T, E> &G, const T v)
{
    int n = G.NumberOfVertices();
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;
    int loc = G.getVertexPos(v);
    SeqQueue<int> Q;
    Q.EnQueue(loc);
    while (!Q.IsEmpty())
    {
        Q.DeQueue(loc);
        if (visited[loc] == false)
        {
            cout << G.getValue(loc) << " ";
            visited[loc] = true;
        }
        int w = G.getFirstNeighbor(loc);
        while (w != -1)
        {
            if (visited[w] == false)
                Q.EnQueue(w);
            w = G.getNextNeighbor(loc, w);
        }
    }
    delete[] visited;
}

template <class T, class E>
void Graphmtx<T, E>::Kruskal(MinSpanTree<T, E> &MST)
{
    int n = numVertices;
    int m = numEdges;
    MSTEdgeNode<T, E> ed;
    MinHeap<MSTEdgeNode<T, E>> H(m); // 边集组成最小堆
    UFSets F(n);                     // 顶点集组成并查集
    for (int i = 0; i < n; i++)      // 遍历所有可能的边，插入到堆
        for (int j = i + 1; j < n; j++)
            if (getWeight(i, j) != maxWeight)
            {
                ed.head = i;
                ed.tail = j;
                ed.weight = getWeight(i, j);
                H.Insert(ed);
            }
    int count = 0;
    while (count < n - 1)
    {
        int root1, root2;
        H.RemoveMin(ed);
        root1 = F.Find(ed.head);
        root2 = F.Find(ed.tail);
        if (root1 != root2)
        {
            F.Union(root1, root2);
            MST.Insert(ed);
            count++;
        }
    }
}

template <class T, class E>
void Graphmtx<T, E>::Prim(const T u0, MinSpanTree<T, E> &MST)
{
    int n = numVertices;
    int m = numEdges;
    int u = getVertexPos(u0), v;
    MinHeap<MSTEdgeNode<T, E>> H(m);
    bool *Vmst = new bool[n];
    for (int i = 0; i < n; i++)
        Vmst[i] = false;
    Vmst[u] = true;

    MSTEdgeNode<T, E> ed;
    int count = 0;
    do
    {
        v = getFirstNeighbor(u);
        while (v != -1)
        {
            if (Vmst[v] == false)
            {
                ed.tail = u;
                ed.head = v;
                ed.weight = getWeight(u, v);
                H.Insert(ed);
            }
            v = getNextNeighbor(u, v);
        }
        while (!H.IsEmpty() && count < n - 1)
        {
            H.RemoveMin(ed);
            if (Vmst[ed.head] == false)
            {
                MST.Insert(ed);
                u = ed.head;
                Vmst[u] = true;
                count++;
                break;
            }
        }
    } while (count < n - 1);
}

template <class T, class E>
void Graphmtx<T, E>::Dijkstra(T v0, E dist[], int path[])
{
    int v = getVertexPos(v0);
    int n = numVertices;
    bool *S = new bool[n];
    for (int i = 0; i < n; i++) // 初始化S,dist,path
    {
        dist[i] = getWeight(v, i);
        S[i] = false;
        if (i != v && dist[i] < maxValue)
            path[i] = v;
        else
            path[i] = -1;
    }

    S[v] = true;
    dist[v] = 0;
    for (int i = 0; i < n - 1; i++) // 计数循环，除了初始点外还要加入n-1个点
    {
        int min = maxValue;
        int u = v;
        for (int j = 0; j < n; j++) // 选出还不在集合S中的离v最近的点
        {
            if (S[j] == false && dist[j] < min)
            {
                u = j;
                min = dist[j];
            }
        }
        S[u] = true;
        for (int k = 0; k < n; k++) //  用u作为中继点缩短其他点到v0的距离
        {
            E w = getWeight(u, k);
            if (S[k] == false && w < maxValue && w + dist[u] < dist[k])
            {
                dist[k] = w + dist[u];
                path[k] = u;
            }
        }
    }
}

template <class T, class E>
void Graphmtx<T, E>::printShortestPath_Dij(T v0)
{
    cout << "从顶点" << v0 << "到其他顶点的最短路径为：" << endl;
    int n = numVertices;
    int v = getVertexPos(v0);
    E *dist = new E[n];
    int path[n];
    int j, k;
    Dijkstra(v0, dist, path);
    int p[n];
    for (int i = 0; i < n; i++)
    {
        if (i != v)
        {
            j = i;
            k = 0;
            while (j != v)
            {
                p[k++] = j;
                j = path[j];
            }
            cout << "顶点" << getValue(i) << "的最短路径为：" << getValue(v);
            while (k > 0)
                cout << " " << getValue(p[--k]);
            cout << endl;
        }
    }
}

template <class T, class E>
void Graphmtx<T, E>::Bellman_Ford(T v0, E dist[], int path[])
{
    int v = getVertexPos(v0);
    int n = NumberOfVertices();
    E w;
    for (int i = 0; i < n; i++)
    {
        dist[i] = getWeight(v, i);
        if (i != v && dist[i] < maxValue)
            path[i] = v;
        else
            path[i] = -1;
    }
    for (int k = 2; k < n; k++) //  计数n-2次,同时也是将dist^1逐渐变为dist^k
    {
        for (int u = 0; u < n; u++) //  以所有顶点作为中继点，更新dist
        {
            if (u != v)
                for (int i = 0; i < n; i++)
                {
                    w = getWeight(i, u);
                    if (dist[u] > dist[i] + w)
                    {
                        dist[u] = dist[i] + w;
                        path[u] = i;
                    }
                }
        }
    }
}

template <class T, class E>
void Graphmtx<T, E>::printShortestPath_BF(T v0)
{
    cout << "从顶点" << v0 << "到其他顶点的最短路径为：" << endl;
    int n = numVertices;
    int v = getVertexPos(v0);
    E *dist = new E[n];
    int path[n];
    int j, k;
    Bellman_Ford(v0, dist, path);
    int p[n];
    for (int i = 0; i < n; i++)
    {
        if (i != v)
        {
            j = i;
            k = 0;
            while (j != v)
            {
                p[k++] = j;
                j = path[j];
            }
            cout << "顶点" << getValue(i) << "的最短路径为：" << getValue(v);
            while (k > 0)
                cout << " " << getValue(p[--k]);
            cout << endl;
        }
    }
}

#endif