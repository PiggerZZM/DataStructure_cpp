#ifndef GRAPH_H
#define GRAPH_H

// ����8.2 ��Ȩ����ͼ��ģ����
#define DefaultVertices 30
template<class T, class E>  // T�Ƕ����࣬E��Ȩֵ��
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
    virtual int getNextNeighbor(int v, int w);  //  �󶥵�v���ڽӶ���w����һ���ڽӶ���
    virtual bool insertVertex(const T vertex);
    virtual bool insertEdge(int v1, int v2, E cost);
    virtual bool removeVertex(int v);
    virtual bool removeEdge(int v1, int v2);
protected:
    int maxVertices;
    int numEdges;
    int numVertices;
    virtual int getVertexPos(T vertex); // ��ͨ��getVertexPos���ݶ����ֵȡ�������ڶ�����е��±꣬�����±���в���
};



#endif