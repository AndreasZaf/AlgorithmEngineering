#include<iostream>
#include<time.h>
#include"LEDA/graph/graph.h"
#include"LEDA/core/queue.h"
#include"LEDA/core/list.h"
#include"LEDA/system/timer.h"


/*WHITE color for initialization 
  GREEN color for even level 
  BLUE  color for odd level                          */
  
enum colors{GREEN,BLUE,WHITE};

using namespace std;
using namespace leda;

list<node>my_BFS(const graph& G,node s,node_array<int>& dist,node_array<edge>& pred,node_array<colors>& Color)
{
   node t,u;
   edge e;
   
   queue<node>Q; //queue for BFS
   list<node>re_list; // return list with all visited nodes 
   
   Q.append(s);
   re_list.append(s);
   dist[s]=0;
   pred[s]=nil;

   while(!Q.empty())
   {
     t=Q.pop();
     
     if(dist[t]%2==0)
     {
       Color[t]=GREEN;
       
     }else if(dist[t]%2==1)
     {
       Color[t]=BLUE;
     }
     
     forall_adj_edges(e,t)
     {
      u=G.target(e);
      
      if(dist[u]==-1)
      {  
        Q.append(u);
        re_list.append(u);
        dist[u]=dist[t]+1;
        pred[u]=e;
      }
        
     }
     
   }
   
   return re_list;
}

bool my_bipar_checker(const graph& G,list<node>& V1,list<node>& V2)
{
   bool bipar_checker=true;
   
   node s=G.choose_node();//random node
   node_array<int>dist(G,-1);
   node_array<edge>pred(G); 
   node_array<colors>Color(G,WHITE);//all nodes colored WHITE before BFS
      
   list<node>list1=my_BFS(G,s,dist,pred,Color);
   
   node u,t;
   edge e;
   
   
  while(!list1.empty())
  {
  
    u=list1.pop();
    
    if(pred[u]==nil)
    {
      // source node
      
      V1.append(u);
      
    }else
    {
    
      if(Color[u]==GREEN && (!V1.search(u)))
      {
              V1.append(u); 
              
      }else if(Color[u]==BLUE && (!V2.search(u)))
      {
              V2.append(u); 
      }
         
      forall_adj_edges(e,u)
      {
        t=G.target(e);
            
        if((Color[u])==(Color[t]))
        {
          V1.clear();
          V2.clear();
          
          node u1=G.source(pred[u]);
          node t1=G.source(pred[t]);
            
          V1.append(t);
          V1.append(u);
            
          while(true)
          {

             if(u1==t1)
             {
                V1.append(t1);
                break;
                
             }else if(u1!=t1)
             {
               V1.append(t1);
               V1.append(u1);
              }
              
             t1=G.source(pred[t1]);
             u1=G.source(pred[u1]);

            }
            
            bipar_checker=false;
            break;

          }else
          {
            if(Color[t]==GREEN && (!V1.search(t)))
            {
              V1.append(t); 
              
            }else if(Color[t]==BLUE && (!V2.search(t)))
            {
              V2.append(t); 
            }
             
          }
        }
          
    }
    
    if(bipar_checker==false)
    {
      break;
    }
     
  }
   
   if(bipar_checker==true)
   {
     return true;
     
   }else
   {
     return false;
   }
   
}

void create_graph1(graph& G,int number_of_nodes)
{
  /*nested squared graph*/
  
  node u[4];
  
  for(int j=0;j<number_of_nodes/4;j++)
  {
    u[0]=G.new_node();
    
    for(int i=1;i<4;i++)
    {
      u[i]=G.new_node();
      G.new_edge(u[i-1], u[i]);
      G.new_edge(u[i], u[i-1]);
      
    }
    G.new_edge(u[3], u[0]);
  }
  
    list<node> list1 = G.all_nodes();

  for (unsigned i = 0; i < (number_of_nodes/4 - 1)*4; i++)
  {
    G.new_edge(list1.inf(list1.get_item(i+4)), list1.inf(list1.get_item(i)));
    G.new_edge(list1.inf(list1.get_item(i)), list1.inf(list1.get_item(i+4)));
  }
  
}

void create_graph2(graph& G,int number_of_nodes)
{
  /*cycle graph*/
  
  list<node>list1;
  node u;
  
  for(int i=0; i<number_of_nodes;i++)
  {
    u=G.new_node();
    list1.append(u);
  }
  
  /*create edge between first node and last node  */
  
  G.new_edge(list1.inf(list1.first()), list1.inf(list1.last()));
  G.new_edge(list1.inf(list1.last()), list1.inf(list1.first()));
  
  /*create edges between other nodes*/
  
  node t;
  forall_nodes(t,G)
  {
    if(t!=list1.inf(list1.last()))
    {
      G.new_edge(t,list1.inf(list1.succ(list1.search(t))));
      G.new_edge(list1.inf(list1.succ(list1.search(t))),t);
    }
  }
  
}

void create_graph3(graph& G,int number_of_nodes)
{
   /*4-level graph k nodes and 2k edges */
   
   node node1[number_of_nodes],node2[number_of_nodes],node3[number_of_nodes],node4[number_of_nodes];
   
   for(int i=0; i<number_of_nodes;i++)
   {
     node1[i]=G.new_node();
     node2[i]=G.new_node();
     node3[i]=G.new_node();
     node4[i]=G.new_node();
     
     //edge between level 1 and level 2
     
     G.new_edge(node1[i], node2[i]);
     G.new_edge(node2[i], node1[i]);
     
     //edge between level 2 and level 3
     
     G.new_edge(node2[i], node3[i]);
     G.new_edge(node3[i], node2[i]);
     
     // edge between level 3 and level 4
     
     G.new_edge(node3[i], node4[i]);
     G.new_edge(node4[i], node3[i]);
   }
   
   srand(time(NULL));
   
   int r1=rand()%number_of_nodes;//random node for level 1 
   int r2=rand()%number_of_nodes;//random node for level 2
   int r3=rand()%number_of_nodes;//random node for level 3
   int r4=rand()%number_of_nodes;//random node for level 4
   
   for(int i=0; i<number_of_nodes;i++)
   {
     
     
     G.new_edge(node1[r1],node2[i]);
     G.new_edge(node2[i],node1[r1]);
     
     G.new_edge(node2[r2],node3[i]);
     G.new_edge(node3[i],node2[r2]);
     
     G.new_edge(node3[r3],node4[i]);
     G.new_edge(node4[i],node3[r3]);
     
   }
   
   r1=rand()%number_of_nodes; 
   r2=rand()%number_of_nodes;
   r3=rand()%number_of_nodes;
   
   //edge between level 1 and level 3 with random nodes
   
   G.new_edge(node1[r1],node3[r3]);
   G.new_edge(node3[r3],node1[r1]);
   
   //edge between level 2 and level 4 with random nodes
   G.new_edge(node2[r2],node4[r4]);
   G.new_edge(node4[r4],node2[r2]);
   

}

void create_graph(graph& G)
{
  int input;
  
  cout<<"\nChoose type of Graph\n\n";
  cout<<"1.Nested Square Graph \n2.Cyclic Graph \n3.Graph of 4-levels \n";
  cin>>input;
  
  if(input==1)
  {
    cout<<"Choose Number of Nodes and Edges \n";
    cout<<"1.(10000,19996)\n2.(40000,79996)\n3.(90000,179996)\n";
    
    cin>>input;
    
    if(input==1)
    {
      create_graph1(G,10000);
      
    }else if(input==2)
    {
     create_graph1(G,40000);
     
    }else if(input==3)
    {
     create_graph1(G,90000);
    }
    
    
  }else if(input==2)
  {
    cout<<"Choose Number of Nodes and Edges \n";
    cout<<"1.(10001,10001)\n2.(40001,40001)\n3.(90001,90001)\n";
    
    cin>>input;
    
    if(input==1)
    {
      create_graph2(G,10001);
      
    }else if(input==2)
    {
      create_graph2(G,40001);
      
    }else if(input==3)
    {
      create_graph2(G,90001);
    }
    
  }else if(input==3)
  {
    cout<<"Choose Number of Nodes\n";
    cout<<"1.(500)\n2.(1000)\n3.(1500)\n";
    
    cin>>input;
    
    if(input==1)
    {
      create_graph3(G,500);
      
    }else if(input==2)
    {
     create_graph3(G,1000);
     
    }else if(input==3)
    {
     create_graph3(G,1500);
    }
  }
  
}

int main()
{
  bool b1,b2;
  timer t1,t2;
  
  list<node> V1;
  list<node> V2;
  list<node> V3;
  list<node> V4;
  
  graph G;
  create_graph(G);
  
  t1.start();
  b1=my_bipar_checker(G,V1,V2);
  t1.stop();
  
  t2.start();
  b2=Is_Bipartite(G,V3,V4);
  t2.stop();
  
  cout<<"The result of my_bipar_checker is:\t"<< b1<<"\tand the time of computation is:\t"<<t1.elapsed_time() <<endl;
  cout<<"The result of Is_Bipartite is:\t\t"<< b2<<"\tand the time of computation is:\t"<<t2.elapsed_time()<<"\n" <<endl;
    
  if(b1==true && b2==true)
  {
  
   cout<<"The graph g is bipartite\n";
   cout<<"my_bipar_checker the size of V1 and V2 are:\t"<<V1.length()<<"\t"<<V2.size()<<endl;
   cout<<"Is_Bipartite the size of V3 and V4 are:\t\t"<<V3.length()<<"\t"<<V4.size()<<endl;
     
  }
    
  else if(b1==false && b2==false)
  {
    cout<<"The graph g is not bipartite\n";   
    cout<<"my_bipar_checker the size of V1 and V2 are:\t"<<V1.length()<<"\t"<<V2.size()<<endl;
    cout<<"Is_Bipartite the size of V3 and V4 are:\t\t"<<V3.size()<<"\t"<<V4.size()<<endl;    
  }
    
  return 0;
}