# -*- coding: utf-8 -*-
import random

import networkx as nx
 


def generateGraph(p, q):
    G = nx.Graph()

    for i in range(400):
        for j in range(i,400):
            if(i//100 == j//100):
                if(random.random() < p ):
                    G.add_edge(i,j)
            elif(random.random() < q ):
                G.add_edge(i,j)
    nx.draw(G)



generateGraph(0.5,0.01)







                
            
    
        
        
    
        
    
