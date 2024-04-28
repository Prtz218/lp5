g++ -fopenmp -o output filename.cpp
./output

#include <bits/stdc++.h>
#include <omp.h>

using namespace std;
class Graph
{
public:
    int vertices;
    vector<vector<int>> adj;
    vector<bool> visited;
    Graph(int v) : vertices(v), adj(v), visited(v, false) {}
    void addEgde(int v, int w)
    {
        adj[v].push_back(w);
        adj[w].push_back(w);
    }

    void initialize(){
        for(int i=0;i<vertices;i++){
            visited[i]=false;
        }
    }

    void dfs(int i){
        stack<int>s;
        s.push(i);
        visited[i]=true;

        while(!s.empty()){
            int current=s.top();
            cout<<current<<" ";
            s.pop();

            for(int j=0;j<adj[current].size();j++){
                int neighbours=adj[current][j];
                if(!visited[neighbours]){
                    s.push(neighbours);
                    visited[neighbours]=true;
                }
            }
        }
    }
   
   void pdfs(int i){
        stack<int>s;
        s.push(i);
        visited[i]=true;

        while(!s.empty()){
            int current=s.top();
            cout<<current<<" ";
            #pragma omp critical
            s.pop();
             
             #pragma omp parallel for
            for(int j=0;j<adj[current].size();j++){
                int neighbours=adj[current][j];
                if(!visited[neighbours]){
                    #pragma omp critical
                    s.push(neighbours);
                    visited[neighbours]=true;
                }
            }
        }
    }



    void bfs(int i){
        queue<int>q;
        q.push(i);
        visited[i]=true;

        while(!q.empty()){
            int current=q.front();
            q.pop();
            cout<<current<<" ";

            for(int j=0;j<adj[current].size();j++){
                int neighbour=adj[current][j];
                if(!visited[neighbour])
                {
                    q.push(neighbour);
                    visited[neighbour]=true;
                }
            }
        }
    }
    
    void pbfs(int i){
        queue<int>q;
        q.push(i);
        visited[i]=true;

        while(!q.empty()){
            int current=q.front();
            #pragma omp critical
            q.pop();
            cout<<current<<" ";
            
            #pragma omp parallel for
            for(int j=0;j<adj[current].size();j++){
                int neighbour=adj[current][j];
                if(!visited[neighbour])
                {
                    #pragma omp critical
                    q.push(neighbour);
                    visited[neighbour]=true;
                }
            }
        }
    }

};


int main(){
    
    int n,e;
    cout<<"enter number of edges"<<endl;
    cin>>n;
    Graph g(n);
    cout<<"enter number of edges"<<endl;
    cin>>e;
    for(int i=0;i<e;i++){
        int x,y;
           cout<<"enter edge"<<endl;
           cin>>x>>y;
           g.addEgde(x,y);

    }

    cout<<"dfs"<<endl;
    int start_time = omp_get_wtime();
    g.dfs(0);
    int end_time = omp_get_wtime();
    cout << "Dfs" << end_time - start_time << " seconds\n";
    g.initialize();
    cout<<endl;
    start_time = omp_get_wtime();
    cout<<"pdfs"<<endl;
    g.pdfs(0);
      end_time = omp_get_wtime();
    cout << "PDfs" << end_time - start_time << " seconds\n";
    
    g.initialize();
    cout<<endl;
    cout<<"bfs"<<endl;
    start_time = omp_get_wtime();
    g.bfs(0);
     end_time = omp_get_wtime();
    cout << "Bfs" << end_time - start_time << " seconds\n";
    
    g.initialize();
    cout<<endl;
    cout<<"pbfs"<<endl;
    start_time = omp_get_wtime();
    g.pbfs(0);
      end_time = omp_get_wtime();
    cout << "PBfs" << end_time - start_time << " seconds\n";
    
    g.initialize();
    cout<<endl;
    return 0;
}