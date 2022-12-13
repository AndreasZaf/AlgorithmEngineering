#include <iostream>
#include <set>
#include <iterator>
#include <math.h>
#include <ctime>
#include <utility>
#include <algorithm>
#include <time.h>
#include <vector>
#include <string>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_traits.hpp"
#include "LEDA/graph/graph.h"
#include "LEDA/graph/shortest_path.h"

using namespace std;
using namespace boost;
using namespace leda;

pair<int,int> find_coordinates(int number_of_rows, int node)
{
  
  /*coordinates for each node of grid graph*/
  
  int count=-1;
  pair<int,int> pair1;
  
  for(int i=0; i<number_of_rows; i++)
  {
    for(int j=0; j<1000; j++)
    {
      count++;
      if(count ==node)
      {
        pair1=make_pair(i,j);
        break;
      }
    }
    if(count==node) 
    {
      break;
    }
  }
  
  return pair1;
  
}



void boost_weights_to_leda_weights(const leda::graph& G1,edge_array<int>&leda_weights,int*leda_helper_array)
{
   /*update the edge array of Leda graph with weights of graph using leda_helper_array*/
   
    leda::edge e1;
    int k=0;
    forall_edges(e1,G1)
    {
       leda_weights[e1]=leda_helper_array[k];
       k++;
    }
   
}

void initialization(set<int>&Q,int *dist,int *prev,int number_of_nodes,int& node)
{
  /* initialize set Q with all nodes, array dist with value INT_MAX for all nodes without start node,array prev with value -2 for all nodes withput start node 
     and start node dist[node]=0 and prev[node]=-1*/
   
   if(Q.size()>0){Q.clear();}
   
   for(int i=0; i<number_of_nodes;i++)
   {
       Q.insert(i); 
   }
   
   fill_n(dist,number_of_nodes,INT_MAX);
   fill_n(prev,number_of_nodes,-2);
  
   dist[node]=0;
   prev[node]=-1;
   
}


void dijkstra(const adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>G, adjacency_list<>::vertex_descriptor V[],pair
                  <adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>::edge_descriptor,bool> *edges1,int number_of_edges,set<int>& Q,int*dist,int*prev
                  ,property_map<adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>,edge_weight_t>::type weight_map,std::string type_of_dijkstra  
                   )
                   
{
        
        //dijkstra from source to others nodes or others nodes to source for directed graph
        
        int temp_node,pWeight,tmpDist,temp;
        
        typedef property_map<adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>,vertex_index_t>::type IndexMap;
        IndexMap name_map = get(vertex_index,G);
             
	      typedef graph_traits<adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>>::vertex_descriptor Vertex;
	      
      if(type_of_dijkstra=="source to all nodes")
      {         
        /*find distances from source node to other nodes*/
         typedef graph_traits<adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>>::out_edge_iterator oEdgeIter;
         oEdgeIter oei, oei_end;
         
         while(!Q.empty())
         {
	         set<int>::iterator min = Q.begin();
         
		       for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
           { 
	           if(dist[*it] < dist[*min]){min = it;}
           }
           temp_node=*min;
               
           Q.erase(min);
     
           for(tie(oei,oei_end) =out_edges(V[temp_node],G); oei != oei_end; ++oei)
           {
			       Vertex tmpTarget=target(*oei,G);//target node
			       for(int i=0; i<number_of_edges; i++){
				     if(source(edges1[i].first,G)==temp_node && target(edges1[i].first,G) == name_map[tmpTarget])
				     {
						    temp = i;          
						    break;
					   }
			    }

			    pWeight = 0;//weight of edge
			    pWeight=get(weight_map,edges1[temp].first);//weight of edge
      
			    tmpDist = dist[temp_node] + pWeight;//distance of node
			    if (tmpDist < dist[name_map[tmpTarget]]) 
          {
				    dist[name_map[tmpTarget]] = tmpDist;      
            prev[name_map[tmpTarget]] = temp_node;                  
			    }
		    }
     
     }
   }else if(type_of_dijkstra=="all nodes to source")
   {
      /* find distances from all nodes tou source*/
       typedef graph_traits<adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>>::edge_iterator EdgeIter;
       EdgeIter oei, oei_end;
   
       while(!Q.empty())
       {
	       set<int>::iterator min = Q.begin();
          
		     for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
         { 
           
	        if(dist[*it] < dist[*min]){min = it;}
         }
         temp_node=*min;
         
         Q.erase(min);
     
         /*for all edges of graph*/
         for(tie(oei,oei_end) =edges(G); oei != oei_end; ++oei)
         {
         
			    Vertex tmpSource=source(*oei,G); //source node
          Vertex tmptarget=target(*oei,G); //target node  
                  
         /*if target node of edge is the temp_node then update the distance of source node of edge*/         
         if(tmptarget==temp_node)
         {
                   
			    for(int i=0; i<number_of_edges; i++)
          {
            
				    if(source(edges1[i].first,G)==name_map[tmpSource] && target(edges1[i].first,G) == temp_node)
				    {
						  temp = i;
						  break;
					  }
          }

			    pWeight = 0;//weight of edge
			    pWeight=get(weight_map,edges1[temp].first);//weight of edge
      
			    tmpDist = dist[temp_node] + pWeight;//distance of node
			    if (tmpDist < dist[name_map[tmpSource]]) 
         {
				   dist[name_map[tmpSource]] = tmpDist;
				   prev[temp_node] = name_map[tmpSource];                         
			   }
	      }
       }
     
      }
   
   
   }
      
}

void dijkstra(const adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>G, adjacency_list<>::vertex_descriptor V[][1000],int number_of_rows,pair
                  <adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>::edge_descriptor,bool> *edges1,int number_of_edges,set<int>& Q,int*dist,int*prev
                  ,property_map<adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>,edge_weight_t>::type weight_map )
                   
{
        
        //dijkstra from source to other nodes for undirected grid graph
        
        int temp_node,pWeight,tmpDist,temp,x,y;
        
        typedef property_map<adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>,vertex_index_t>::type IndexMap;
        IndexMap name_map = get(vertex_index,G);
             
	      typedef graph_traits<adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>>::vertex_descriptor Vertex;
	              
        typedef graph_traits<adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>>::out_edge_iterator oEdgeIter;
         oEdgeIter oei, oei_end;
         
         while(!Q.empty())
         {
	         set<int>::iterator min = Q.begin();
         
		       for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
           { 
	           if(dist[*it] < dist[*min]){min = it;}
           }
           temp_node=*min;
               
           Q.erase(min);
           
           tie(x,y) = find_coordinates(number_of_rows,temp_node);//coordinates of node
            
           for(tie(oei,oei_end) =out_edges(V[x][y],G); oei != oei_end; ++oei)
           {
           
			       Vertex tmpTarget=target(*oei,G);//target node       
			       for(int i=0; i<number_of_edges; i++){    
				     if(source(edges1[i].first,G)==temp_node && target(edges1[i].first,G) == name_map[tmpTarget])
				     {                        
						    temp = i;          
						    break;
					   }
			    }

			    pWeight = 0;//weight of edge
			    pWeight=get(weight_map,edges1[temp].first);//weight of edge
      
			    tmpDist = dist[temp_node] + pWeight;//distance of node
			    if (tmpDist < dist[name_map[tmpTarget]]) 
          {
				    dist[name_map[tmpTarget]] = tmpDist;      
            prev[name_map[tmpTarget]] = temp_node;                  
			    }
		    }
     
     }
   
      
}


void ALT(const adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>G, adjacency_list<>::vertex_descriptor V[],pair
                  <adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>::edge_descriptor,bool> *edges1,int number_of_edges,set<int>& Q,int*dist,int*prev 
                  ,int *heuristics,int target1,property_map<adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>,edge_weight_t>::type  
                  weight_map)
                   
{
        //ALT for directed graph
        
        int temp_node,pWeight,tmpDist,temp;
        
        typedef property_map<adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>,vertex_index_t>::type IndexMap;
        IndexMap name_map = get(vertex_index,G);
             
        typedef graph_traits<adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>>::out_edge_iterator oEdgeIter;
        oEdgeIter oei, oei_end;
        
	      typedef graph_traits<adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>>::vertex_descriptor Vertex;
	      
               
       while(!Q.empty())
      {
	      set<int>::iterator min = Q.begin();
         
		    for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
        { 
	        if(dist[*it] < dist[*min]){min = it;}
        }
        temp_node=*min;
        if(temp_node==target1)  
        {
           
           break;
        }
       
        if(dist[temp_node] == INT_MAX)
        {     
              
              
			        break;
		   } 
    
       Q.erase(min);
        
        
       
       for(tie(oei,oei_end) =out_edges(V[temp_node],G); oei != oei_end; ++oei)
       {
			   Vertex tmpTarget=target(*oei,G);//target node        
			    for(int i=0; i<number_of_edges; i++){
				  if(source(edges1[i].first,G)==temp_node && target(edges1[i].first,G) == name_map[tmpTarget])
				  {
						 temp = i;
						 break;
					 }
			 }

			 pWeight = 0;//weight of edge
			 pWeight=get(weight_map,edges1[temp].first);//weight of edge
        
       /*if new weight of edge using heuristic is positive or equal with zero */ 
       if(pWeight+heuristics[name_map[tmpTarget]]-heuristics[temp_node]>=0)
       {
         /*if new weight edge is better from old weight of edge*/
         if(pWeight+heuristics[name_map[tmpTarget]]-heuristics[temp_node]<pWeight)
         {
          pWeight=pWeight+heuristics[name_map[tmpTarget]]-heuristics[temp_node];//weight of edge using the best down boudary of each node of edge
          
         }
       }
       
        tmpDist = dist[temp_node] + pWeight;//distance of node
			 if (tmpDist < dist[name_map[tmpTarget]]) 
       {
				 dist[name_map[tmpTarget]] = tmpDist;
				 prev[name_map[tmpTarget]] = temp_node;                         
			 }
		 }
     
   }
      
}

void ALT(const adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>G, adjacency_list<>::vertex_descriptor V[][1000],int number_of_rows,pair
                  <adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>::edge_descriptor,bool> *edges1,int number_of_edges,set<int>& Q,int*dist,int*prev 
                  ,int *heuristics,int target1,property_map<adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>,edge_weight_t>::type  
                  weight_map)
                   
{
        //ALT for undirected grid graph
        
        int temp_node,pWeight,tmpDist,temp,x,y;
        
        typedef property_map<adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>,vertex_index_t>::type IndexMap;
        IndexMap name_map = get(vertex_index,G);
             
        typedef graph_traits<adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>>::out_edge_iterator oEdgeIter;
        oEdgeIter oei, oei_end;
        
	      typedef graph_traits<adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>>::vertex_descriptor Vertex;
	      
               
       while(!Q.empty())
      {
	      set<int>::iterator min = Q.begin();
         
		    for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
        { 
	        if(dist[*it] < dist[*min]){min = it;}
        }
        temp_node=*min;
        if(temp_node==target1)  
        {
        
           
           break;
        }
       
        if(dist[temp_node] == INT_MAX)
        {     
              
              
			        break;
		   } 
    
       Q.erase(min);
       
       tie(x,y) = find_coordinates(number_of_rows,temp_node);//coordinates of node
       
       
       
       for(tie(oei,oei_end) =out_edges(V[x][y],G); oei != oei_end; ++oei)
       {
			   Vertex tmpTarget=target(*oei,G);//target node
         Vertex tmpSource=source(*oei,G);//source node
          if(temp_node==tmpSource)
          { 
                   
			    for(int i=0; i<number_of_edges; i++){
				  if(source(edges1[i].first,G)==temp_node && target(edges1[i].first,G) == name_map[tmpTarget])
				  {
             
						 temp = i;
						 break;
					 }
			    }

			 pWeight = 0;//weight of edge
			 pWeight=get(weight_map,edges1[temp].first);//weight of edge
        
        /*if new weight of edge using heuristic is positive or equal with zero */
      if(pWeight+heuristics[name_map[tmpTarget]]-heuristics[temp_node]>=0)
       {
          /*if new weight of edge is better from old weight of edge*/
         if(pWeight+heuristics[name_map[tmpTarget]]-heuristics[temp_node]<pWeight)
         {
          pWeight=pWeight+heuristics[name_map[tmpTarget]]-heuristics[temp_node];//weight of edge using the best down boudary of each node of edge
          
         }
       }

        
			 tmpDist = dist[temp_node] + pWeight;//distance of node
    
			 if (tmpDist < dist[name_map[tmpTarget]]) 
       {
				 dist[name_map[tmpTarget]] = tmpDist;
				 prev[name_map[tmpTarget]] = temp_node;                         
			 }
		  }
    }
     
   }
      
}


void check_graph(std:: string type_of_graph)
{

   set<int>Q;// insert all nodes of graph
   
   int maxweight,randweight,number_of_nodes,number_of_edges,input,k,*leda_helper_array,source1,target1,counter_landmarks,landmark,number_of_landmarks=5,*boost_dist,*prev,*heuristics, 
   helper,n=100;//number of pair source target;
   
   
   std::vector<int> used_landmarks;// vector with used landamrks
   std::vector<int>used_nodes; //vector with used nodes 
   std::vector<pair<int,int>>used_s_t; //vector with used pair of source and target node
   pair<int,int> s_t;//pair source and target node
   
   double duration1/*ALT duration*/,duration2/*leda duration*/,sum1/*ALT average time*/,sum2/*leda average time*/;
   
    clock_t start,stop;
    
   cout<<"\nrange for weight of edges\n[1,1000000]\n\n";
   maxweight=1000000;
   

   if(type_of_graph=="grid graph")
   {
      /*undirected grid graph*/
   
       typedef adjacency_list<listS,vecS,undirectedS,no_property,property<edge_weight_t,int>>Boost_Graph;
       
       int number_of_rows,xstart,ystart,xend,yend,k1;
      
      Boost_Graph G2;//Boost graph
      leda::graph G1;//Leda graph
      
      cout<<"grid graph\n\n";
      
    cout<<"choose rows and columns\n\n1.(20,1000)\n2.(25,1000)\n3.(35,1000)\n\n";
    cin>>input;
    
    if(input==1)
   {
     number_of_rows=20;
     number_of_nodes=20000;
     number_of_edges=38980;
     
   }else if(input==2)
   {
     number_of_rows=25;
     number_of_nodes=25000;
     number_of_edges=48975;
     
   }else if(input==3)
   {
     number_of_rows=35;
     number_of_nodes=35000;
     number_of_edges=68965;
   }
      
   adjacency_list<>::vertex_descriptor V[number_of_rows][1000];//boost nodes
   pair<Boost_Graph::edge_descriptor,bool>* edges1=new pair<Boost_Graph::edge_descriptor,bool>[number_of_edges];//boost edges
   
   node nodes[number_of_rows][1000];
   
    // create nodes for Boost graph and Leda graph
   for(int i=0;i<number_of_rows;i++)
   {
     for(int j=0; j<1000; j++)
     {
       V[i][j]=add_vertex(G2);
       nodes[i][j]=G1.new_node();
     }
   }
   
   
  
   // create edges for Boost graph and Leda graph
   leda_helper_array=new int[2*number_of_edges];
   k=0;//index for Boost graph
   k1=0;//index for Leda graph
   for(int i=0; i<number_of_rows;i++)
   {
     for(int j=0; j<1000;j++)
     {
       if(i==number_of_rows-1)
       {
         if(j<999)
         {
            randweight=rand()%maxweight+1;//random weight of edge
            
            // edge of Boost graph
            property<edge_weight_t,int>edge_property(randweight);
            edges1[k]=add_edge(V[i][j],V[i][j-1],edge_property,G2);
            k++;
            
            //edge of Leda graph
            G1.new_edge(nodes[i][j],nodes[i][j-1]);
            leda_helper_array[k1]=randweight;
            k1++;
                   
            //reverse edge of Leda graph       
            G1.new_edge(nodes[i][j-1],nodes[i][j]);
            leda_helper_array[k1]=randweight;
            k1++;
            
         }

       }else if(i<=number_of_rows-2)
       {
         if(j<999)
         {
            randweight=rand()%maxweight+1;//random weight of edge
            
            // edge of Boost graph
            property<edge_weight_t,int>edge_property(randweight);
            edges1[k]=add_edge(V[i][j],V[i][j+1],edge_property,G2);
            k++;
            
            //edge of Leda graph
            G1.new_edge(nodes[i][j],nodes[i][j+1]);
            leda_helper_array[k1]=randweight;
            k1++;
            
            //reverse edge of Leda graph
            G1.new_edge(nodes[i][j+1],nodes[i][j]);
            leda_helper_array[k1]=randweight;
            k1++;
            
         }
        
            randweight=rand()%maxweight+1;//rabdim weight of edge
            
            //Boost edge of graph
            property<edge_weight_t,int>edge_property(randweight);
            edges1[k]=add_edge(V[i][j],V[i+1][j],edge_property,G2);
            k++;
            
            //edge of Leda graph
            G1.new_edge(nodes[i][j],nodes[i+1][j]);
            leda_helper_array[k1]=randweight;
            k1++;
            
            //reverse edge of Leda graph
            G1.new_edge(nodes[i+1][j],nodes[i][j]);
            leda_helper_array[k1]=randweight;
            k1++;
            
            
       }
     }
   }
   
    
   typedef graph_traits<Boost_Graph>::vertex_descriptor Vertex;
    
   typedef property_map<Boost_Graph,vertex_index_t>::type IndexMap;
   IndexMap name_map = get(vertex_index,G2);
  
   typedef property_map<Boost_Graph,edge_weight_t>::type WeightMap;
   WeightMap weight_map=get(edge_weight, G2);
   
   typedef graph_traits<Boost_Graph>::edge_iterator edgeIterator;
   edgeIterator e_it,e_end; 
   
      
   boost_dist=new int[number_of_nodes];//array of distances
   prev=new int[number_of_nodes];//array with previous nodes
   heuristics=new int[number_of_nodes];//best heuristics
   std::vector<int> *distancefromnode=new std::vector<int>[number_of_nodes];// vector of array with distances from landmark to others nodes
  
   
   
  
   cout<<"start proceess for find 5 random landmarks\n\n";
   counter_landmarks=1;
  
  // choose random landmark different from source node target node and previous landmarks
  while(counter_landmarks<=number_of_landmarks)
  {
       
       while(true)
       {
             srand(time(NULL));
             landmark=(rand()%number_of_rows)*1000;
            
           if((find(used_landmarks.begin(),used_landmarks.end(),landmark)==used_landmarks.end()))
           { 
              used_landmarks.push_back(landmark);
              break;
           }
                    
       }
       cout<<"start process for find distances from landmark\t :\t\t"<<landmark<<"\t to other nodes"<<"\n\n";
       initialization(Q,boost_dist,prev,number_of_nodes,landmark);
       dijkstra(G2,V,number_of_rows,edges1,number_of_edges,Q,boost_dist,prev,weight_map);//distances from landamrk to other nodes
       cout<<"end process for find distances from landmark\t :\t\t"<<landmark<<"\t to other nodes"<<"\n\n";
       for(int i=0;i<number_of_nodes;i++){distancefromnode[counter_landmarks-1].push_back(boost_dist[i]);}//copy distances
       counter_landmarks++;
       
  }
  cout<<"end proceess for find 5 random landmarks\n\n";  
  
  // for n random source and target nodes 
    
  for(int i=1;i<=n;i++)
  {
     /*random start node and end node*/
     while(true)
     {
        srand(time(NULL));
        source1=(rand()%number_of_rows)*1000;
        srand(time(NULL)+10);
        target1=((rand()%number_of_rows+1)*1000)-1;
        
        s_t=make_pair(source1,target1);
        
        // source and target node different from landmarks and next pair source node and target node different from previous pairs 
           if((find(used_landmarks.begin(),used_landmarks.end(),source1)==used_landmarks.end())&&(find(used_landmarks.begin(),used_landmarks.end(),target1)==used_landmarks.end())&&
              (find(used_s_t.begin(),used_s_t.end(),s_t)==used_s_t.end()))
           { 
              used_s_t.push_back(s_t);
              break;
           }
     }
     
       cout <<"path from node:\t" << source1 << " to node: " << target1 <<"\n\n"; 
        
       tie(xstart,ystart)=find_coordinates(number_of_rows,source1);
       tie(xend,yend)=find_coordinates(number_of_rows,target1);
     
       
        
  /*compute best down boundary for each node of no directed*/           
   cout<<"start proceess for best down boundary\n\n";
   counter_landmarks=1;    
  while(counter_landmarks<=number_of_landmarks)  
  {  
          
       for(tie(e_it,e_end)=edges(G2); e_it != e_end; ++e_it)
      {
            helper=0;
            Vertex source2=source(*e_it,G2);//source node of edge
            Vertex target2=target(*e_it,G2);//target node of edge
            
         /*check if source node of edge has been used */   
         if(find(used_nodes.begin(),used_nodes.end(),name_map[source2]) == used_nodes.end())
         {
            helper=abs(distancefromnode[counter_landmarks-1][name_map[source2]]-distancefromnode[counter_landmarks-1][target1]);//abs(D(landmark,node)-D(landmark,targetnode))
            
            /*first landmark*/
            if(counter_landmarks==1)
            {
               heuristics[name_map[source2]]=helper;
               
            /*next landmarks*/   
            }else
            {
               /*if helper > previous down boundary of node*/
               if(helper>heuristics[name_map[source2]]){heuristics[name_map[source2]]=helper;}
               
            }
            
            used_nodes.push_back(name_map[source2]);//insert source node of edge to vector used_nodes
         }
         
         helper=0;
         /*check if source node of edge has been used */  
         if(find(used_nodes.begin(),used_nodes.end(),name_map[target2]) == used_nodes.end())
         {
            helper=abs(distancefromnode[counter_landmarks-1][name_map[target2]]-distancefromnode[counter_landmarks-1][target1]);//abs(D(landmark,node)-D(landmark,targetnode))
            
            /*first landmark*/
            if(counter_landmarks==1)
            {
              
               heuristics[name_map[target2]]=helper;
               
            /*next landmarks*/
            }else
            {
                /*if helper > previous down boundary of node*/
               if(helper>heuristics[name_map[target2]]){heuristics[name_map[target2]]=helper;}
            }
            
            used_nodes.push_back(name_map[target2]);//insert target node of edge to vector used_nodes
         }
            
      }
      
      
       used_nodes.clear();
       counter_landmarks++;

  }
   

   cout<<"end proceess for best down boundary\n\n";
   
   //ALT algorithm
    cout<<"start ALT\n\n";
    start=clock();
    initialization(Q,boost_dist,prev,number_of_nodes,source1);
    ALT(G2,V,number_of_rows,edges1,number_of_edges,Q,boost_dist,prev,heuristics,target1,weight_map);
    stop=clock();
    cout<<"end ALT\n\n";
    duration1=(stop-start)/(double)CLOCKS_PER_SEC;
    sum1=sum1+duration1;
    
    edge_array<int>leda_weights(G1,0);//leda graph weights
    boost_weights_to_leda_weights(G1,leda_weights,leda_helper_array);//update edge array leda_weights using leda_helper_array
       
    node_array<leda::edge> pred(G1,nil); //leda graph previous edge for node
    node_array<int> dist(G1,-1);//leda graph distances
    
    leda::node leda_source_node=nodes[xstart][ystart]; //source node for leda fraph
    leda::node leda_target_node=nodes[xend][yend]; //target node for leda graph
    
    cout<<"start LEDA \n\n";
    //Leda SHORTEST_PATH
    start=clock();
    if(SHORTEST_PATH(G1,leda_source_node,leda_weights,dist,pred))
    {
        node node1;
        forall_nodes(node1,G1)
        {
            
           if(node1==leda_target_node)
           {
               if(pred[node1]!=nil)
               {
                  COMPUTE_SHORTEST_PATH(G1,leda_source_node,leda_target_node,pred);
               }
               
               break;
           
           }
        }
    }

    stop=clock();
    cout<<"end LEDA\n\n";  
    duration2=(stop-start)/(double)CLOCKS_PER_SEC;
    sum2=sum2+duration2;
   }
    
   }else if(type_of_graph=="random graph")
   {
   
      srand(time(NULL));
    
      int temp1,rand1,rand2,*distances_for_next_landmark,max;
      
      typedef adjacency_list<listS,vecS,directedS,no_property,property<edge_weight_t,int>>Boost_Graph;
      
      Boost_Graph G2;
      leda::graph G1;
      
      cout<<"random graph\n\n";
      cout<<"choose number of nodes and edges\n1.(10000,20000)\n2.(20000,40000)\n3.(30000,60000)\n\n";
      cin>>input;
      
      if(input==1)
     {
       number_of_nodes=10000;
       number_of_edges=20000;
     
     }else if(input==2)
     {
      number_of_nodes=20000;
      number_of_edges=40000;
     
     }else if(input==3)
     {
       number_of_nodes=30000;
       number_of_edges=60000;
     }
     
     adjacency_list<>::vertex_descriptor V[number_of_nodes];//boost nodes
     pair<Boost_Graph::edge_descriptor,bool>* edges1=new pair<Boost_Graph::edge_descriptor,bool>[number_of_edges];//boost edges
     
     node nodes[number_of_nodes]; 
     
     for(int i=0;i<number_of_nodes;i++)
     {
        V[i]=add_vertex(G2); // boost nodes
        nodes[i]=G1.new_node(); // leda nodes
     }
     
     //create edges
     
     
     leda_helper_array=new int[number_of_edges];
     k=0;
     pair<int,int> x;
     std::vector<pair<int,int>> duplicate;//vector with used edges
     std::vector<int>vn;//vector with used nodes
     
     while(k<number_of_edges)
     {   
        rand1=rand()%number_of_nodes;
        rand2=rand()%number_of_nodes;
        
        if(rand1!=rand2)
        {
           x=make_pair(rand1,rand2);
           
           if(k==0)
           {
               randweight=rand()%maxweight+1;
               
               //boost edge
               property<edge_weight_t,int>edge_property(randweight);
               edges1[k]=add_edge(V[rand1],V[rand2],edge_property,G2);
               
               // leda edge
               
               G1.new_edge(nodes[rand1],nodes[rand2]);
               
               leda_helper_array[k]=randweight;
               
               duplicate.push_back(x);
               vn.push_back(rand1);
               vn.push_back(rand2);
               
               k++;
               
               temp1=rand2;

               while(k<number_of_nodes-1)
               {
                  rand2=rand()%number_of_nodes;
                  
                 if(find(vn.begin(), vn.end(), rand2) == vn.end() && temp1!=rand2)
                 {
                         x=make_pair(temp1,rand2);
                         randweight=rand()%maxweight+1;
                         
                         //boost edge
                         property<edge_weight_t,int>edge_property(randweight);
                         edges1[k]=add_edge(V[temp1],V[rand2],edge_property,G2);
                         
                         // leda edge
                         G1.new_edge(nodes[temp1],nodes[rand2]);
                         leda_helper_array[k]=randweight;
                         
                         duplicate.push_back(x);
                         temp1=rand2;
                         vn.push_back(temp1);
                         k++;
                 }
                  
              }
              
              if(k==number_of_nodes-1)
              {
                         x=make_pair(vn.back(),vn.front());
                         randweight=rand()%maxweight+1;
                         
                         //boost edge
                         property<edge_weight_t,int>edge_property(randweight);
                         edges1[k]=add_edge(V[vn.back()],V[vn.front()],edge_property,G2);
                         
                          // leda edge
                         G1.new_edge(nodes[vn.back()],nodes[vn.front()]);
                         leda_helper_array[k]=randweight;
                         
                         duplicate.push_back(x);
                         k++;
              }
              
              vn.clear();
                                                                               
           }else
           {
 
              if( find(duplicate.begin(), duplicate.end(), x) == duplicate.end())
              {
                  randweight=rand()%maxweight+1;
                  
                  //boost edge
                  property<edge_weight_t,int>edge_property(randweight);
                  edges1[k]=add_edge(V[rand1],V[rand2],edge_property,G2);
                  
                  //leda edge
                  G1.new_edge(nodes[rand1],nodes[rand2]);
                  leda_helper_array[k]=randweight;
                  
                  duplicate.push_back(x);
                  k++;
              
              }
           }
           

                      
        }
           
    }
             
 	  duplicate.clear();
      
      
   typedef graph_traits<Boost_Graph>::vertex_descriptor Vertex;
    
   typedef property_map<Boost_Graph,vertex_index_t>::type IndexMap;
   IndexMap name_map = get(vertex_index,G2);
  
   typedef property_map<Boost_Graph,edge_weight_t>::type WeightMap;
   WeightMap weight_map=get(edge_weight, G2);
   
   typedef graph_traits<Boost_Graph>::edge_iterator edgeIterator;
   edgeIterator e_it,e_end; 
      
   boost_dist=new int[number_of_nodes];//array of distances
   prev=new int[number_of_nodes];//array with previous nodes
    
   std::vector<int> *distancefromnode=new std::vector<int>[number_of_nodes];// vector of array with distances from landmark to others nodes
   std::vector<int> *distancetonode=new std::vector<int>[number_of_nodes];// vector of array with distances from others nodes to landmark
   heuristics=new int[number_of_nodes];//best heuristics
   distances_for_next_landmark=new int[number_of_nodes]; // using for find next landmark
   
   cout<<"start proceess for find 5 random landmarks\n\n";
   counter_landmarks=1;
   while(counter_landmarks<=number_of_landmarks)
   {
    
         while(true)
       {
             landmark=rand()%number_of_nodes;
            
           if((find(used_landmarks.begin(),used_landmarks.end(),landmark)==used_landmarks.end()))
           { 
              used_landmarks.push_back(landmark);
              break;
           }
                    
        }
      
       cout<<"start process for find distances from landmark\t :\t\t"<<landmark<<"\t to other nodes"<<"\n\n";
       initialization(Q,boost_dist,prev,number_of_nodes,landmark);
       dijkstra(G2,V,edges1,number_of_edges,Q,boost_dist,prev,weight_map,"source to all nodes");//distances from landamrk to other nodes
       cout<<"end process for find distances from landmark\t :\t\t"<<landmark<<"\t to other nodes"<<"\n\n";
       for(int i=0;i<number_of_nodes;i++){distancefromnode[counter_landmarks-1].push_back(boost_dist[i]);}//copy distances
       
       cout<<"start process for find distances to landmark\t :\t\t"<<landmark<<"\t from other nodes"<<"\n\n";
       initialization(Q,boost_dist,prev,number_of_nodes,landmark);
       dijkstra(G2,V,edges1,number_of_edges,Q,boost_dist,prev,weight_map,"all nodes to source");//distances from other nodes to landmark
       cout<<"end process for find distances to landmark\t :\t\t"<<landmark<<"\t from other nodes"<<"\n\n";
       for(int i=0;i<number_of_nodes;i++){distancetonode[counter_landmarks-1].push_back(boost_dist[i]);}//copy distances
       
      counter_landmarks++;
       
   }
    cout<<"end proceess for find 5 random landmarks\n\n";
   
     // for n random source and target nodes 
    
  for(int i=1;i<=n;i++)
  {
    //random source node and target node               
    while(true)
    {
       source1=rand()%number_of_nodes;
       target1=rand()%number_of_nodes;
       
       s_t=make_pair(source1,target1);
        
         //source and target node different from landmarks and next pair source node and target node different from previous pairs and source node different target node
        if((find(used_landmarks.begin(),used_landmarks.end(),source1)==used_landmarks.end())&&(find(used_landmarks.begin(),used_landmarks.end(),target1)==used_landmarks.end())&&
            (find(used_s_t.begin(),used_s_t.end(),s_t)==used_s_t.end())&&(source1!=target1))
        { 
              used_s_t.push_back(s_t);
              break;
        }
    }
  
   
   cout <<"path from node:\t" << source1 << " to node: " << target1 <<"\n\n"; 

    
    
    /*best down boundary of nodes using farthest node from set of used landamrks */
    counter_landmarks=1;
    
    cout<<"start proceess for best down boundary\n\n";
    while(counter_landmarks<=number_of_landmarks)
    {
      
       for(tie(e_it,e_end)=edges(G2); e_it != e_end; ++e_it)
      {
      
         helper=0;
      
         Vertex source2=source(*e_it,G2);//source node of edge
         Vertex target2=target(*e_it,G2);//target node of edge
      
         // check if source node of edge has been used
         if(find(used_nodes.begin(), used_nodes.end(),name_map[source2]) == used_nodes.end())
         {
            
            helper=distancetonode[counter_landmarks-1][name_map[source2]]-distancetonode[counter_landmarks-1][target1]; //D(node,Landmark)-D(target,Landmark)
            
            /*if D(node,Landmark)-D(target,Landmark)< D(Landmark,target)-D(Landmark,node) */
            if(helper<distancefromnode[counter_landmarks-1][target1]-distancefromnode[counter_landmarks-1][name_map[source2]])
               {
                  helper=distancefromnode[counter_landmarks-1][target1]-distancefromnode[counter_landmarks-1][name_map[source2]];
               }
            
            /*first landmark*/
            if(counter_landmarks==1)
            {
                   heuristics[name_map[source2]]=helper;
                 
              /*next landmarks*/   
            }else
            {
                /*helper>previous down boundary of node*/
                if(helper>heuristics[name_map[source2]]){heuristics[name_map[source2]]=helper;}
            }
               
            used_nodes.push_back(name_map[source2]);//insert source node of edge to vector used_nodes
            
             
         }
         
         helper=0;
      
         //check if target node of edge has been used
         if(find(used_nodes.begin(), used_nodes.end(),name_map[target2]) == used_nodes.end())
         {
         
            helper=distancetonode[counter_landmarks-1][name_map[target2]]-distancetonode[counter_landmarks-1][target1];//D(node,Landmark)-D(target,Landmark)
            
            /*if D(node,Landmark)-D(target,Landmark)< D(Landmark,target)-D(Landmark,node) */
            if(helper<distancefromnode[counter_landmarks-1][target1]-distancefromnode[counter_landmarks-1][name_map[target2]])
              {
                 helper=distancefromnode[counter_landmarks-1][target1]-distancefromnode[counter_landmarks-1][name_map[target2]];
              }
            
            /*first landamark*/
            if(counter_landmarks==1)
            {
                   heuristics[name_map[target2]]=helper;
                 
             /*next landmarks*/    
            }else
            {
                /*helper>previous down boundary of node*/
                if(helper>heuristics[name_map[target2]]){heuristics[name_map[target2]]=helper;}
            }
               
            used_nodes.push_back(name_map[target2]);//insert target node of edge to vector used_nodes
         
         
         }
         

     }
     
     used_nodes.clear();
           
     counter_landmarks++;
    }
    
   
    cout<<"end proceess for best down boundary\n\n";
    
    //ALT
    cout<<"start ALT\n\n";
    start=clock();
    initialization(Q,boost_dist,prev,number_of_nodes,source1);
    ALT(G2,V,edges1,number_of_edges,Q,boost_dist,prev,heuristics,target1,weight_map);
    stop=clock();
    cout<<"end ALT\n\n";
    duration1=(stop-start)/(double)CLOCKS_PER_SEC;
    sum1=sum1+duration1;
     
    edge_array<int>leda_weights(G1,0);//leda graph weights
    boost_weights_to_leda_weights(G1,leda_weights,leda_helper_array);//update edge array leda_weights using leda_helper_array
        
    node_array<leda::edge> pred(G1,nil); //leda graph previous edge for node
    node_array<int> dist(G1,-1);//leda graph distances
    
    leda::node leda_source_node=nodes[source1]; //source node for leda fraph
    leda::node leda_target_node=nodes[target1]; //target node for leda graph
    
    
    //Leda SHORTEST_PATH
    cout<<"start LEDA \n\n";
    start=clock();
    if(SHORTEST_PATH(G1,leda_source_node,leda_weights,dist,pred))
    {
        node node1;
        forall_nodes(node1,G1)
        {
           if(node1==leda_target_node)
           {
               if(pred[node1]!=nil)
               {
                  
                  COMPUTE_SHORTEST_PATH(G1,leda_source_node,leda_target_node,pred);
               }
               
               break;
           
           }
        }
    }
    
    
     stop=clock();  
     cout<<"end LEDA\n\n";
     duration2=(stop-start)/(double)CLOCKS_PER_SEC;
     sum2=sum2+duration2;
    }
    
     
   }
   
   used_s_t.clear();
   used_landmarks.clear();
  
   //average time for n different pair source target nodes
   cout<<"ALT           :\t"<<(sum1/n)*1000.0<<"\tms\n";
   cout<<"LEDA          :\t"<<(sum2/n)*1000.0<<"\tms\n\n";

    
}

int main()
{

    int input;
  
    cout<<"1.grid graph\n2.random graph\n\n";
  
    cin>>input;
  
    if(input==1)
   {
    check_graph("grid graph");
   
   }else if(input==2)
   {

    check_graph("random graph");
   }
   return 0;
}
