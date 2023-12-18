#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//structure for storing graph info
struct Edge
{
    int src,dest,wt;
};

//function to find shortest distance and path using bellman ford algo
void bellman_ford_algo(Edge edges[],int V,int E,int s)
{
    int dist[V];   // array to store shortest distance
    for(int i=0;i<V;i++)
    {
        dist[i]=INT_MAX;
    }
    dist[s]=0;
    vector<int>pred(V,0);   //vector which helps to get shortest path
    //Bellman ford algo
    for(int i=0;i<V-1;i++)
    {
        
        for(int j=0;j<E;j++)
        {
            int u=edges[j].src;
            int v=edges[j].dest;
            int w=edges[j].wt;
            if(dist[s]!=INT_MAX && dist[u]+w <dist[v])
            {
        
                dist[v]=dist[u]+w;
                pred[v]=u;
            }
        }

    }
    //for loop to detect negative cycle
    for(int j=0;j<E;j++)
    {
        int u=edges[j].src;
        int v=edges[j].dest;
        int w=edges[j].wt;
        if(dist[s]!=INT_MAX && dist[u]+w <dist[v])
        {
               cout<<"Graph contains negative cycle....Bellman ford Algo Fails !!";
               return;
        }
    }

    cout<<"Shortest distance of each vertex from "<<s<<" is as follows:"<<endl;
    cout<<endl;
    for(int i=0;i<V;i++)
    {
        cout<<"Shortest distance of vertex "<<i <<" from "<<s<<" : "<<dist[i]<<endl;
    }

    //to display shortest path
    int f=0;
    while(f!=-1)
    {
        cout<<endl;
        cout<<"for shortest path,enter vertex (-1 to exit):";
        cin>>f;
        if(f==0)
        {
            cout<<0<<endl;

        }
        else if(f!=-1 && f<V){
            cout<<f<<"<--";
            while(pred[f]!=0)
            {
                cout<<pred[f]<<"<--";
                f=pred[f];
            }
            cout<<0<<endl;
        }

    }

}
int main()
{
    //Scan data
    int V,E;
    cout<<"Enter number of vertices in graph:";
    cin>>V;
    cout<<"Enter number of edges in graph:";
    cin>>E;
    Edge edges[E];
    cout<<"Enter data of graph:"<<endl;
    cout<<"\n";
    for(int i=0;i<E;i++)
    {
        cout<<"Enter src vertex:";
        cin>>edges[i].src;
        cout<<"Enter dest vertex:";
        cin>>edges[i].dest;
        cout<<"Enter weight:";
        cin>>edges[i].wt;
        cout<<endl;
    }
    cout<<"Printing data of graph : "<<endl;
    cout<<"Src     Dest       Weight"<<endl;
    for(int i=0;i<E;i++)
    {
        cout<<edges[i].src<<"       "<<edges[i].dest<<"         "<<edges[i].wt<<endl;
    }


    int source;
    cout<<"Enter source vertex of graph:"<<endl;
    cin>>source;
    bellman_ford_algo(edges,V,E,source);
    return 0;
}