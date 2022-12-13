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

using namespace std;
using namespace boost;

pair<int,int> find_coordinates(int number_of_rows, int node)
{
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

void initialization(set<int>&Q,int *dist,int *prev,int number_of_nodes,int& node)
{
  
   
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

/*-------------------------------------------------------------dijkstra functions--------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void dijkstra_sp(const adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>G, adjacency_list<>::vertex_descriptor V[][1000],int number_of_rows,pair
                  <adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>::edge_descriptor,bool> edges1[],int number_of_edges,set<int>& Q,int*dist,int
                  *prev,int target1,int& visited_nodes,property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,edge_weight_t>::type                                  weight_map ,bool& is_path)
                   
{
        
        //dijkstra sp for grid graph
        
        int temp_node,x,y,temp,pWeight,tmpDist;
                
        typedef property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,vertex_index_t>::type IndexMap;
        IndexMap name_map = get(vertex_index,G);
             
        typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::out_edge_iterator oEdgeIter;
        oEdgeIter oei, oei_end;
        
	      typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::vertex_descriptor Vertex;
	      
               
       while(!Q.empty())
      {
	      set<int>::iterator min = Q.begin();
         
		    for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
        { 
	        if(dist[*it] < dist[*min]){min = it;}
        }
        temp_node=*min;
        visited_nodes++;
           
        if(temp_node==target1)  break;
       
        if(dist[temp_node] == INT_MAX)
        {     
              is_path=false;
			        break;
		   } 
    
       Q.erase(min);
     
		   tie(x,y) = find_coordinates(number_of_rows,temp_node);// find coordinates of node 
   
       for(tie(oei,oei_end) =out_edges(V[x][y],G); oei != oei_end; ++oei)
       {
			   Vertex tmpTarget=target(*oei,G); // target node
                   
			    for(int i=0; i<number_of_edges; i++){
				  if(source(edges1[i].first,G)==temp_node && target(edges1[i].first,G) == name_map[tmpTarget])
				  {
						 temp = i;
						 break;
					 }
			 }

			 pWeight = 0;//weight of edge
			 pWeight=get(weight_map,edges1[temp].first);// weight of edge
       
			 tmpDist = dist[temp_node] + pWeight;// distance of node
         
			 if (tmpDist < dist[name_map[tmpTarget]]) 
       {
				 dist[name_map[tmpTarget]] = tmpDist;
				 prev[name_map[tmpTarget]] = temp_node;                         
			 }
		 }
     
   }
      
}

void A_star(const adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>G, adjacency_list<>::vertex_descriptor V[][1000],int number_of_rows,pair
                  <adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>::edge_descriptor,bool> edges1[],int number_of_edges,set<int>& Q,int*dist,int
                  *prev,int *euclidean,int target1,int& visited_nodes,property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,edge_weight_t>                        ::type weight_map ,bool& is_path)
                   
{
        
        //A*for grid graph
        
        int temp_node,x,y,temp,pWeight,tmpDist;
                
        typedef property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,vertex_index_t>::type IndexMap;
        IndexMap name_map = get(vertex_index,G);
             
        typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::out_edge_iterator oEdgeIter;
        oEdgeIter oei, oei_end;
        
	      typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::vertex_descriptor Vertex;
	      
               
       while(!Q.empty())
      {
	      set<int>::iterator min = Q.begin();
         
		    for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
        { 
	        if(dist[*it] < dist[*min]){min = it;}
        }
        temp_node=*min;
        visited_nodes++;
           
        if(temp_node==target1)  break;
       
        if(dist[temp_node] == INT_MAX)
        {     
              is_path=false;
			        break;
		   } 
    
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

			 pWeight = 0;// weight of edge
			 pWeight=get(weight_map,edges1[temp].first);//edge of weight
       pWeight=pWeight+euclidean[name_map[tmpTarget]]-euclidean[temp_node];// edge of weight with use eiclidean distances
       
			 tmpDist = dist[temp_node] + pWeight;//distance of node
			 if (tmpDist < dist[name_map[tmpTarget]]) 
       {
				 dist[name_map[tmpTarget]] = tmpDist;
				 prev[name_map[tmpTarget]] = temp_node;                         
			 }
		 }
     
   }
      
}


void dijkstra_sp(const adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>G, adjacency_list<>::vertex_descriptor V[],pair
                  <adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>::edge_descriptor,bool> edges1[],int number_of_edges,set<int>& Q,int*dist,int*prev
                  ,int target1,int& visited_nodes,property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,edge_weight_t>::type  
                  weight_map,bool& is_path)
                   
{
        //dijkstra sp for random graph with source and target
        
        int temp_node,pWeight,tmpDist,temp;
        
        typedef property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,vertex_index_t>::type IndexMap;
        IndexMap name_map = get(vertex_index,G);
             
        typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::out_edge_iterator oEdgeIter;
        oEdgeIter oei, oei_end;
        
	      typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::vertex_descriptor Vertex;
	      
               
       while(!Q.empty())
      {
	      set<int>::iterator min = Q.begin();
         
		    for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
        { 
	        if(dist[*it] < dist[*min]){min = it;}
        }
        temp_node=*min;
        visited_nodes++;
        if(temp_node==target1)  break;
       
        if(dist[temp_node] == INT_MAX)
        {     
              
              is_path=false;
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
      
      
			 tmpDist = dist[temp_node] + pWeight;//distance of node
			 if (tmpDist < dist[name_map[tmpTarget]]) 
       {
				 dist[name_map[tmpTarget]] = tmpDist;
				 prev[name_map[tmpTarget]] = temp_node;                         
			 }
		 }
     
   }
      
}


void dijkstra_sp(const adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>G, adjacency_list<>::vertex_descriptor V[],pair
                  <adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>::edge_descriptor,bool> edges1[],int number_of_edges,set<int>& Q,int*dist,int*prev
                  ,property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,edge_weight_t>::type weight_map,string type_of_dijkstra  
                   )
                   
{
        
        //dijkstra sp for random graph from source to others nodes or others nodes to source
        
        int temp_node,pWeight,tmpDist,temp;
        
        typedef property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,vertex_index_t>::type IndexMap;
        IndexMap name_map = get(vertex_index,G);
             
	      typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::vertex_descriptor Vertex;
	      
      if(type_of_dijkstra=="source to all nodes")
      {         
         typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::out_edge_iterator oEdgeIter;
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
       typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::in_edge_iterator iEdgeIter;
       iEdgeIter oei, oei_end;
   
       while(!Q.empty())
       {
	       set<int>::iterator min = Q.begin();
          
		     for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
         { 
           
	        if(dist[*it] < dist[*min]){min = it;}
         }
         temp_node=*min;
         
         Q.erase(min);
     
         for(tie(oei,oei_end) =in_edges(V[temp_node],G); oei != oei_end; ++oei)
         {
         
			    Vertex tmpSource=source(*oei,G);//source node
         
                   
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

void A_star(const adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>G, adjacency_list<>::vertex_descriptor V[],pair
                  <adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>::edge_descriptor,bool> edges1[],int number_of_edges,set<int>& Q,int*dist,int*prev 
                  ,int *h,int target1,int& visited_nodes,property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,edge_weight_t>::type  
                  weight_map,bool& is_path)
                   
{
        //A* for random graph 
        
        int temp_node,pWeight,tmpDist,temp;
        
        typedef property_map<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>,vertex_index_t>::type IndexMap;
        IndexMap name_map = get(vertex_index,G);
             
        typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::out_edge_iterator oEdgeIter;
        oEdgeIter oei, oei_end;
        
	      typedef graph_traits<adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>>::vertex_descriptor Vertex;
	      
               
       while(!Q.empty())
      {
	      set<int>::iterator min = Q.begin();
         
		    for(set<int>::iterator it = Q.begin(); it!=Q.end(); ++it)
        { 
	        if(dist[*it] < dist[*min]){min = it;}
        }
        temp_node=*min;
        visited_nodes++;
        if(temp_node==target1)  break;
       
        if(dist[temp_node] == INT_MAX)
        {     
              
              is_path=false;
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

			 pWeight = 0;//weight of node
			 pWeight=get(weight_map,edges1[temp].first);//weight of node
       pWeight=pWeight+h[name_map[tmpTarget]]-h[temp_node];//weight of node using the best down boudary of each node of edge
      
			 tmpDist = dist[temp_node] + pWeight;//distance of node
			 if (tmpDist < dist[name_map[tmpTarget]]) 
       {
				 dist[name_map[tmpTarget]] = tmpDist;
				 prev[name_map[tmpTarget]] = temp_node;                         
			 }
		 }
     
   }
      
}



/*-------------------------------------------------------------dijkstra and A*functions----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


void check_graph(string type_of_graph)
{
  set<int>Q;// insert all nodes of graph
  int input,number_of_edges,number_of_nodes,maxweight,source1/*source node*/,target1/*target node*/,k,visited_nodes1,visited_nodes2,*prev,randweight,*dist,A_star_final_distance/*final distance for A* */,dijkstra_distance/*dijkstra distance*/;
  double duration1=0/*time for dijkstra*/,duration2=0/*time for A* */;
  bool path_dijkstra=true,path_A_star=true;
  
  typedef adjacency_list<listS,vecS,bidirectionalS,no_property,property<edge_weight_t,int>>Graph;
  
  Graph G;

  clock_t start,stop;
  
  visited_nodes1=0;
  visited_nodes2=0;

  if(type_of_graph=="grid graph")
  {
      /*--------------------------------------------GRID GRAPH-------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------*/
    

    
       
    int number_of_rows,xstart,ystart,xend,yend,x,y,x1,y1;
        
    cout<<"check grid graph with Dijkstra and A*\n\n";
    cout<<"choose rows and columns\n\n1.(30,1000)\n2.(60,1000)\n3.(80,1000)\n\n";
    cin>>input;
    
    if(input==1)
   {
     number_of_rows=30;
     number_of_nodes=30000;
     number_of_edges=58970;
     
   }else if(input==2)
   {
     number_of_rows=60;
     number_of_nodes=60000;
     number_of_edges=118940;
   }else if(input==3)
   {
     number_of_rows=80;
     number_of_nodes=80000;
     number_of_edges=158920;
   }
   
   cout<<"\nrange for weight of edges\n\n1.[1,100]\n2.[1,10000]\n\n";
   cin>>input;
  
   if(input==1)
   {
     maxweight=100;
    
   }else if(input==2)
   {
     maxweight=10000;
   }
   
   srand(time(NULL));
   source1=(rand()%number_of_rows)*1000;
   srand(time(NULL)+10);
   target1=((rand()%number_of_rows+1)*1000)-1;

  
   tie(xstart,ystart)=find_coordinates(number_of_rows,source1);
   tie(xend,yend)=find_coordinates(number_of_rows,target1);
   
   adjacency_list<>::vertex_descriptor V[number_of_rows][1000];
   pair<Graph::edge_descriptor,bool> edges1[number_of_edges];
   
   // create nodes
   for(int i=0;i<number_of_rows;i++)
   {
     for(int j=0; j<1000; j++)
     {
       V[i][j]=add_vertex(G);
     }
   }
  
   // create edges
   k=0;
   for(int i=0; i<number_of_rows;i++)
   {
     for(int j=0; j<1000;j++)
     {
       if(i==number_of_rows-1)
       {
         if(j<999)
         {
            randweight=rand()%maxweight+1;
            property<edge_weight_t,int>edge_property(randweight);
            edges1[k]=add_edge(V[i][j],V[i][j-1],edge_property,G);
            k++;
         }

       }else if(i<=number_of_rows-2)
       {
         if(j<999)
         {
            randweight=rand()%maxweight+1;
            property<edge_weight_t,int>edge_property(randweight);
            edges1[k]=add_edge(V[i][j],V[i][j+1],edge_property,G);
            k++;
         }
        
            randweight=rand()%maxweight+1;
            property<edge_weight_t,int>edge_property(randweight);
            edges1[k]=add_edge(V[i][j],V[i+1][j],edge_property,G);
            k++;
       }
     }
   }
  
   	 
   
   typedef graph_traits<Graph>::vertex_descriptor Vertex;
   
   typedef property_map<Graph,edge_weight_t>::type WeightMap;
   WeightMap weight_map=get(edge_weight, G);
   
   
   typedef property_map<Graph,vertex_index_t>::type IndexMap;
   IndexMap name_map = get(vertex_index,G);
         
   typedef graph_traits< Graph>::edge_iterator edgeIterator;
   edgeIterator e_it,e_end;
      
   dist=new int[number_of_nodes];//array with distances
   prev=new int[number_of_nodes];//array with previous nodes
   
      
  /*--------------------------------------------------------dijkstra--------------------------------------------------------------------------------------------
  --------------------------------------------------------------------------------------------------------------------------------------------------------------
  -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  
  cout<<"\nstart dijkstra sp\n";
  start=clock();
  initialization(Q,dist,prev,number_of_nodes,source1);
  dijkstra_sp(G,V,number_of_rows,edges1,number_of_edges,Q,dist,prev,target1,visited_nodes1,weight_map,path_dijkstra);
  stop=clock();
  duration1=(stop-start)/(double)CLOCKS_PER_SEC;
  cout<<"end  dijkstra sp\n\n";
  if(path_dijkstra==true){dijkstra_distance=dist[target1];}
  

/*------------------------------------------------------------------A*-------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------- */


   cout<<"start preprocessing of A*\n\n";
   
   int *euclidean=new int[number_of_nodes];//euclidean distances
   vector<int>used_nodes;// vector with used nodes 
   
   //compute euclidean distances
   cout<<"start of computing euclidean distance for  all nodes\n";
   for(tie(e_it,e_end)=edges(G); e_it != e_end; ++e_it)
   {
      Vertex source2=source(*e_it,G);//source node of edge
      Vertex target2=target(*e_it,G);//target node of edge
      
      //check if source node of edge has been used
      if(find(used_nodes.begin(), used_nodes.end(),name_map[source2]) == used_nodes.end())
      {
        tie(x,y)=find_coordinates(number_of_rows,name_map[source2]);//find coordinates of source node of edge
        used_nodes.push_back(name_map[source2]);//insert source node of edge to vector used_nodes
        euclidean[name_map[source2]]=(int)sqrt(pow((x-xend),2)+pow((y-yend),2));//compute euclidean distance of source of edge
      }
            
       // check if target node of edge has been used  
      if(find(used_nodes.begin(), used_nodes.end(),name_map[target2]) == used_nodes.end())
      {
        tie(x1,y1)=find_coordinates(number_of_rows,name_map[target2]);//find coordinates of target node of edge
        used_nodes.push_back(name_map[target2]);//insert target node of edge to vector used_nodes
        euclidean[name_map[target2]]=(int)sqrt(pow((x1-xend),2)+pow((y1-yend),2));//compute euclidean distance of target node of edge
      }
       
   }
   used_nodes.clear();
   cout<<"finally of computing Euclidean distance for all nodes\n\n";
       
   cout<<"end preprocessing of A*\n\n";
   
   cout<<"start A*\n";
   
   start=clock();
   initialization(Q,dist,prev,number_of_nodes,source1);
   A_star(G,V,number_of_rows,edges1,number_of_edges,Q,dist,prev,euclidean,target1,visited_nodes2,weight_map,path_A_star);
   stop=clock();
   duration2=(stop-start)/(double)CLOCKS_PER_SEC;
   cout<<"end A*\n\n";
   if(path_A_star==true){A_star_final_distance=dist[target1];}
  
 }else if (type_of_graph=="random graph")
 {
     /*--------------------------------------------RANDOM GRAPH-------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------
       ---------------------------------------------------------------------------------------------------------------*/
      
      
     int rand1/*random index for array of nodes*/,rand2/*random index for array of nodes*/,L1/*random node  */,L2/*node with biggest distance from L1*/,temp1;
     
      cout<<"check random graph with Dijkstra and A* \n\n";
    
      cout<<"choose number of nodes and edges\n1.(10000,20000)\n2.(20000,40000)\n3.(60000,120000)\n\n";
      cin>>input;
      
      srand(time(NULL));
  
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
       number_of_nodes=60000;
       number_of_edges=120000;
     }
   
     cout<<"\nrange for weight of edges\n1.[1,100]\n2.[1,10000]\n\n";
     cin>>input;
  
     if(input==1)
     {
        maxweight=100;
    
     }else if(input==2)
     {
        maxweight=10000;
     }
     

     
     adjacency_list<>::vertex_descriptor V[number_of_nodes];
     pair<Graph::edge_descriptor,bool> edges1[number_of_edges];
  
     // create nodes
     for(int i=0;i<number_of_nodes;i++)
     {
        V[i]=add_vertex(G);
     }
        
       
     //create edges

     k=0;
     pair<int,int> x;
     vector<pair<int,int>> duplicate;//vector with used edges
     vector<int>vn;//vector with used nodes
     
     while(k<number_of_edges)
     {   
        rand1=rand()%number_of_nodes+1;
        rand2=rand()%number_of_nodes+1;
        
        if(rand1!=rand2)
        {
           x=make_pair(rand1,rand2);
           
           if(k==0)
           {
               randweight=rand()%maxweight+1;
               property<edge_weight_t,int>edge_property(randweight);
               edges1[k]=add_edge(V[rand1],V[rand2],edge_property,G);
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
                         property<edge_weight_t,int>edge_property(randweight);
                         edges1[k]=add_edge(V[temp1],V[rand2],edge_property,G);
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
                         property<edge_weight_t,int>edge_property(randweight);
                         edges1[k]=add_edge(V[vn.back()],V[vn.front()],edge_property,G);
                         duplicate.push_back(x);
                         k++;
              }
              
              vn.clear();
                                                                               
           }else
           {
 
              if( find(duplicate.begin(), duplicate.end(), x) == duplicate.end())
              {
                  randweight=rand()%maxweight+1;
                  property<edge_weight_t,int>edge_property(randweight);
                  edges1[k]=add_edge(V[rand1],V[rand2],edge_property,G);
                  duplicate.push_back(x);
                  k++;
              
              }
           }
           

                      
        }
           
    }
             
 	  duplicate.clear();
                  
    //random source node and target node               
    while(true)
    {
       source1=rand()%number_of_nodes;
       target1=rand()%number_of_nodes;
       if(source1!=target1){break;}
    }
    
    
    
   typedef graph_traits<Graph>::vertex_descriptor Vertex;
    
   typedef property_map<Graph,vertex_index_t>::type IndexMap;
   IndexMap name_map = get(vertex_index,G);
  
   typedef property_map<Graph,edge_weight_t>::type WeightMap;
   WeightMap weight_map=get(edge_weight, G);
   
   typedef graph_traits< Graph>::edge_iterator edgeIterator;
   edgeIterator e_it,e_end;
         

      
   dist=new int[number_of_nodes];//array of distances
   prev=new int[number_of_nodes];//array with previous nodes
   
      
  /*--------------------------------------------------------dijkstra--------------------------------------------------------------------------------------------
  --------------------------------------------------------------------------------------------------------------------------------------------------------------
  -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  
  cout<<"\nstart dijkstra sp\n";
  
  start=clock();
  
  initialization(Q,dist,prev,number_of_nodes,source1);
          
  dijkstra_sp(G,V,edges1,number_of_edges,Q,dist,prev,target1,visited_nodes1,weight_map,path_dijkstra);
  stop=clock();
  duration1=(stop-start)/(double)CLOCKS_PER_SEC;
  cout<<"end  dijkstra sp\n\n";
  
  if(path_dijkstra==true){dijkstra_distance=dist[target1];}
  
  

/*------------------------------------------------------------------A*-------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------- */

     
   cout<<"start preprocessing of A*\n\n";
      
   int *bound1=new int[number_of_nodes]; // distances from L1 node to others nodes
   int *bound2=new int[number_of_nodes]; // distances from all nodes to L1 node
   int *bound3=new int[number_of_nodes]; // distances from L2 node to others nodes
   int *bound4=new int[number_of_nodes]; // distances from all nodes to L2 nodes
   int *h=new int[number_of_nodes];// best down boundaries for each node
   int h1;
       
   // random node L1    
   while(true)
   {
       L1=rand()%number_of_nodes;
       
       if(L1!=source1 &&  L1!=target1){break;}
   }
  
    //shortest paths from node L1 
   
   cout<<"start of process for finding shorter routes from node L1\n";
   
   initialization(Q,dist,prev,number_of_nodes,L1);
   
   dijkstra_sp(G,V,edges1,number_of_edges,Q,dist,prev,weight_map,"source to all nodes");
   cout<<"end of process for finding shorter routes from node L1\n\n";
   for(int i=0;i<number_of_nodes;i++){bound1[i]=dist[i];}//copy distances
   
   
   //shortest paths from all nodes to node L1 
   cout<<"start of process for finding shorter routes from all nodes to node L1\n";
  
   initialization(Q,dist,prev,number_of_nodes,L1);
  
   dijkstra_sp(G,V,edges1,number_of_edges,Q,dist,prev,weight_map,"all nodes to source");
   cout<<"end of process for finding shorter routes from all nodes to node L1\n\n";
   for(int i=0;i<number_of_nodes;i++){bound2[i]=dist[i];}//copy distances
  
   // find node L2 with maximum distance from node L1
   int max=bound1[0];
   for(int i=1; i<number_of_nodes;i++)
   {
     if(max<bound1[i] && i!= source1 && i!= target1)
      {
        L2=i;
      }
   }
   
   
   //shortest paths from node L2
   
    cout<<"start of process for finding shorter routes from node L2\n";
   
    initialization(Q,dist,prev,number_of_nodes,L2);
  
    dijkstra_sp(G,V,edges1,number_of_edges,Q,dist,prev,weight_map,"source to all nodes");
    cout<<"end of process for finding shorter routes from node L2\n\n";
    for(int i=0;i<number_of_nodes;i++){bound3[i]=dist[i];}//copy distances
    
    //shortest paths from all nodes to node L2 
    
   cout<<"start of process for finding shorter routes from all nodes to node L2\n";
   
   initialization(Q,dist,prev,number_of_nodes,L2);
   
   dijkstra_sp(G,V,edges1,number_of_edges,Q,dist,prev,weight_map,"all nodes to source");
   cout<<"end of process for finding shorter routes from all nodes to node L2\n\n";
   for(int i=0;i<number_of_nodes;i++){bound4[i]=dist[i];}//copy distances
   
   cout<<"start of computing the best down boundary of each node\n";
   vector<int>used_nodes;

   // best down boundary for each node
      
   for(tie(e_it,e_end)=edges(G); e_it != e_end; ++e_it)
   {
      
      h1=0;
      
      Vertex source2=source(*e_it,G);//source node of edge
      Vertex target2=target(*e_it,G);//target node of edge
      
      // check if source node of edge has been used
      if(find(used_nodes.begin(), used_nodes.end(),name_map[source2]) == used_nodes.end())
      {
        h1=bound1[target1]-bound1[name_map[source2]];//d(L1,target node )-d(L1,source node of edge)
        
        //check if h1 < d(source node of edge,L2)-d(target,L2)
        if(h1 < bound4[name_map[source2]]-bound4[target1]){h1=bound4[name_map[source2]]-bound4[target1];}
        
        used_nodes.push_back(name_map[source2]);//insert source node of edge to vector used_nodes
        h[name_map[source2]]=h1;//insert best down boundary of source node edge to array 
      }
      //check if target node of edge has been used
      if(find(used_nodes.begin(), used_nodes.end(),name_map[target2]) == used_nodes.end())
      {
        h1=bound1[target1]-bound1[name_map[target2]];//d(L1,target node )-d(L1,target node of edge)
        
        //check if h1 < d(target node of edge,L2)-d(target,L2)
        if(h1 < bound4[name_map[target2]]-bound4[target1]){h1=bound4[name_map[target2]]-bound4[target1];}
        used_nodes.push_back(name_map[target2]);//insert target node of edge to vector used_nodes
        h[name_map[target2]]=h1;//insert best down boundary of target node of edge to array 
      }
      
   }
   used_nodes.clear();
   cout<<"finally of computing the best down boundary of each node\n\n";
   
   cout<<"end preprocessing of A*\n\n";
   
   cout<<"start A*\n";
   start=clock(); 
   initialization(Q,dist,prev,number_of_nodes,source1);
   A_star(G,V,edges1,number_of_edges,Q,dist,prev,h,target1,visited_nodes2,weight_map,path_A_star);
   stop=clock();  
   duration2=(stop-start)/(double)CLOCKS_PER_SEC;
   cout<<"end A*\n\n";
   if(path_A_star==true){A_star_final_distance=dist[target1];}

 }
 
  if(path_dijkstra==true)
  {
        cout<<"Dijkstra\n";
        cout <<"path from node:\t" << source1 << " to node: " << target1 <<"\tvisited nodes are:\t"<<visited_nodes1<<"\n";
        cout<<"target node:\t"<<target1<<"\tfinal distance:\t"<<dijkstra_distance<<"\n\n";
        

   }else
   {
        cout<<"dijkstra\n";
        cout << "No path from node: "<< source1<< " to node: " << target1 << "\n\n";
   }  
   
   if(path_A_star==true)
   {
           cout<<"A*\n";
           cout <<"path from node:\t" <<source1<< " to node: " <<target1<<"\tvisited nodes are:\t"<<visited_nodes2<<"\n";
           cout<<"target node:\t"<<target1<<"\tfinal distance:\t"<<A_star_final_distance<<"\n\n";
   }else
   { 
          cout<<"A*\n";
          cout <<"No path from node: " << source1 << " to node: " << target1 << "\n\n";
   }
     
   cout<<"Running time for Dijkstra sp :\t"<<duration1*1000.0<<"\tms\n";
   cout<<"Running time for A*          :\t"<<duration2*1000.0<<"\tms\n\n";

}

int main()
{

  int input;
  
  cout<<"Choose graph\n\n";
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

