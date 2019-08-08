#ifndef GRAPHLNK_H
#define GRAPHLNK_H

// 程序8.6 用邻接表表示的图的类定义
// 本程序中邻接矩阵和邻接表实现的图都是无向图，修改为有向图可能要考虑输入输出的重载、以及可能有些地方我没有区分边的头尾
// Dijkstra和Bellman-Ford算法实现还有问题
#include "SeqQueue.h"
#include "MinSpanTree.h"
#include "UFset.h"
#include "minheap.h"
#include <iostream>
using namespace std;
#define DefaultVertices 30

template <class T, class E>
struct Edge
{
    int dest;         //  边的另一顶点位置
    E cost;           // 权重
    Edge<T, E> *link; //  下一条边的指针
    Edge() {}
    Edge(int num, E weight) : dest(num), cost(weight), link(NULL) {}
};

template <class T, class E>
struct Vertex
{
    T data;            // 顶点的名字
    Edge<T, E> *first; // 边链表指针
    Vertex() : first(NULL) {}
};

template <class T, class E>
class Graphlnk
{
    friend istream &operator>>(istream &in, Graphlnk<T, E> &G)
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
    friend ostream &operator<<(ostream &out, Graphlnk<T, E> &G)
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
    Graphlnk(int sz = DefaultVertices);
    ~Graphlnk();
    T getValue(int i)
    {
        return (i >= 0 && i < numVertices) ? NodeTable[i].data : NULL;
    }
    E getWeight(int v1, int v2);
    bool insertVertex(const T vertex);
    bool removeVertex(int v);
    bool insertEdge(int v1, int v2, E cost);
    bool removeEdge(int v1, int v2);
    int getFirstNeighbor(int v);
    int getNextNeighbor(int v, int w);
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
    void DFS(Graphlnk<T, E> &G, const T v);
    void BFS(Graphlnk<T, E> &G, const T v);
    void Kruskal(MinSpanTree<T, E> &MST);
    void Prim(const T u0, MinSpanTree<T, E> &MST);
    void printShortestPath_Dij(T v0);
    void printShortestPath_BF(T v0);

private:
    Vertex<T, E> *NodeTable;
    int getVertexPos(const T vertex)
    {
        for (int i = 0; i < numVertices; i++)
            if (NodeTable[i].data == vertex)
                return i;
        return -1;
    }
    int numVertices;
    int numEdges;
    int maxVertices;
    void DFS(Graphlnk<T, E> &G, int v, bool visited[]);
    void Dijkstra(T v0, E dist[], int path[]);
    void Bellman_Ford(T v0, E dist[], int path[]);
    
};

template <class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)
{
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    NodeTable = new Vertex<T, E>[maxVertices];
}

template <class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
    for (int i = 0; i < numVertices; i++)
    {
        Edge<T, E> *p = NodeTable[i].first;
        while (p != NULL)
        {
            NodeTable[i].first = p->link;
            delete p;
            p = NodeTable[i].first;
        }
    }
    delete[] NodeTable;
}

template <class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)
{
    if (v != -1)
    {
        Edge<T, E> *p = NodeTable[v].first;
        if (p != NULL)
            return p->dest;
    }
    return -1;
}

template <class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{
    if (v != -1)
    {
        Edge<T, E> *p = NodeTable[v].first;
        while (p != NULL && p->dest != w)
            p = p->link;
        if (p != NULL && p->link != NULL)
            return p->link->dest;
    }
    return -1;
}

template <class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
    if (v1 != -1 && v2 != -1)
    {
        Edge<T, E> *p = NodeTable[v1].first;
        while (p != NULL && p->dest != v2)
            p = p->link;
        if (p != NULL)
            return p->cost;
    }
    return 0;
}

template <class T, class E>
bool Graphlnk<T, E>::insertVertex(const T vertex)
{
    if (numVertices == maxVertices)
        return false;
    NodeTable[numVertices++].data = vertex;
    return true;
}

template <class T, class E>
bool Graphlnk<T, E>::removeVertex(int v)
{
    if (numVertices == 1 || v < 0 || v >= numVertices)
        return false;
    Edge<T, E> *p, *s, *t;
    int k, i;
    while (NodeTable[v].first != NULL)
    {
        p = NodeTable[v].first;
        k = p->dest;
        s = NodeTable[k].first;
        t = NULL;
        while (s != NULL && s->dest != NULL) // 找对称存放的边结点
        {
            t = s;
            s = s->link;
        }
        if (s != NULL)
        {
            if (t == NULL)
                NodeTable[k].first = s->link;
            else
                t->link = s->link;
            delete s;
        }
        NodeTable[v].first = p->link;
        delete p;
        numEdges--;
    }
    numVertices--;
    NodeTable[v].data = NodeTable[numVertices].data;
    p = NodeTable[v].first = NodeTable[numVertices].first;
    while (p != NULL)
    {
        s = NodeTable[p->dest].first;
        while (s != NULL)
        {
            if (s->dest == numVertices)
            {
                s->dest = v;
                break;
            }
            else
                s = s->link;
        }
    }
    return true;
}

template <class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        Edge<T, E> *q, *p = NodeTable[v1].first;
        while (p != NULL && p->dest != v2)
            p = p->link;
        if (p != NULL)
            return false;
        p = new Edge<T, E>;
        q = new Edge<T, E>;
        p->dest = v2;
        p->cost = weight;
        p->link = NodeTable[v1].first;
        NodeTable[v1].first = p;
        q->dest = v1;
        q->cost = weight;
        q->link = NodeTable[v2].first;
        NodeTable[v2].first = q;
        numEdges++;
        return true;
    }
}

template <class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
    if (v1 != -1 && v2 != -1)
    {
        Edge<T, E> *p = NodeTable[v1].first, *q = NULL, *s = p;
        while (p != NULL && p->dest != v2) // 在v1的边链表中删除
        {
            q = p;
            p = p->link;
        }
        if (p != NULL)
        {
            if (p == s)
                NodeTable[v1].first = p->link;
            else
                q->link = p->link;
            delete p;
        }
        else
            return false;
        p = NodeTable[v2].first; // 在v2的边链表中删除
        q = NULL, s = p;
        while (p->dest != v1)
        {
            q = p;
            p = p->link;
        }
        if (p == s)
            NodeTable[v2].first = p->link;
        else
            q->link = p->link;
        delete p;
        return true;
    }
    return false;
}

template <class T, class E>
void Graphlnk<T, E>::DFS(Graphlnk<T, E> &G, const T v)
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
void Graphlnk<T, E>::DFS(Graphlnk<T, E> &G, int v, bool visited[])
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
void Graphlnk<T, E>::BFS(Graphlnk<T, E> &G, const T v)
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
void Graphlnk<T, E>::Kruskal(MinSpanTree<T, E> &MST)
{
    int n = numVertices;
    int m = numEdges;
    MSTEdgeNode<T, E> ed;
    MinHeap<MSTEdgeNode<T, E>> H(m); // 边集组成最小堆
    UFSets F(n);                     // 顶点集组成并查集
    for (int i = 0; i < n; i++)      // 遍历所有可能的边，插入到堆
    {
        int head = NodeTable[i].data;
        Edge<T, E> *p = NodeTable[i].first;
        MSTEdgeNode<T, E> ed;
        while (p != NULL)
        {
            int tail = p->dest;
            if (head < tail)
            {
                ed.head = head;
                ed.tail = tail;
                ed.weight = p->cost;
                H.Insert(ed);
            }
            p = p->link;
        }
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
void Graphlnk<T, E>::Prim(const T u0, MinSpanTree<T, E> &MST)
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
void Graphlnk<T, E>::Dijkstra(T v0, E dist[], int path[])
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
void Graphlnk<T, E>::printShortestPath_Dij(T v0)
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
void Graphlnk<T, E>::Bellman_Ford(T v0, E dist[], int path[])
{
    int v = getVertexPos(v0);
    int n = NumberOfVertices();
    E w;
    Edge<T, E> *p = NodeTable[v].first;
    while (p != NULL)
    {
        dist[p->dest] = p->cost;
        if (p->cost < maxValue)
            path[p->dest] = v;
        else
            path[p->dest] = -1;
        p = p->link;
    }
    for (int k = 2; k < n; k++) //  计数n-2次,同时也是将dist^1逐渐变为dist^k
    {
        for (int i = 0; i < n; i++) //  以所有顶点作为中继点，更新dist
        {
            p = NodeTable[i].first;
            w = p->cost;
            while (p != NULL)
            {
                if (dist[i] + w < dist[p->dest])
                {
                    dist[p->dest] = dist[i] + w;
                    path[p->dest] = i;
                }
                p = p->link;
            }
        }
    }
}

template<class T, class E>
void Graphlnk<T,E>::printShortestPath_BF(T v0)
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