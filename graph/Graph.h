#ifndef GRAPH_H
#define GRAPH_H

// 程序8.2 带权无向图的模板类
#define DefaultVertices 30
template<class T, class E>  // T是顶点类，E是权值类
class Graph
{
public:
    const E maxWeight = 100;
    Graph(int sz = DefaultVertices);
    ~Graph();
    bool GraphEmpty() const
        {return numVertices == 0;}
    bool GraphFull() const 
        {return numVertices == maxVertices || numEdges == maxVertices*(maxVertices-1)/2;}
    int NumberOfVertices() {return numVertices;}
    int NumberOfEdges() {return numEdges;}
    virtual T getValue(int i);
    virtual E getWeight(int v1, int v2);
    virtual int getFirstNeighbor(int v);
    virtual int getNextNeighbor(int v, int w);  //  求顶点v的邻接顶点w的下一个邻接顶点
    virtual bool insertVertex(const T vertex);
    virtual bool insertEdge(int v1, int v2, E cost);
    virtual bool removeVertex(int v);
    virtual bool removeEdge(int v1, int v2);
protected:
    int maxVertices;
    int numEdges;
    int numVertices;
    virtual int getVertexPos(T vertex); // 先通过getVertexPos根据顶点的值取出顶点在顶点表中的下标，再用下标进行操作
};



#endif