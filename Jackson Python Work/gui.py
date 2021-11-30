# all necessary imports
import matplotlib.pyplot as plt
import networkx as nx
import random

''''
Graph Class

Data Members:
- graph adjacency list (self.graph)
- networkx graph object (self.G)
- a list of edge colors (self.colors)
'''
class Graph:

    '''
    Initialization:
    - empty adjacency list
    - blank graph object
    - no colors
    '''
    def __init__(self):
        self.graph = {  }
        self.G = nx.Graph()
        self.colors = [ ]
    
    '''
    insert
    Parameters: two nodes that need to be connected and a weight between them
    Returns: None
    Description: insert n1 and n2 with provided weight or update weight between them
    '''
    def insert(self, n1, n2, weight):
        # if n1 and n2 are the same, just return
        if (n1 == n2):
            return
        # if n1 is not yet in the graph and n2 is not provided, just create n1 and exit
        if n1 not in self.graph.keys() and n2 is None:
            self.graph[n1] = []
            return
        # if n1 does not exist (and n2 is not None) create n1
        if n1 not in self.graph.keys():
            self.graph[n1] = []
        # if n2 does not exist (and n1 is not None) create n1    
        if n2 not in self.graph.keys():
            self.graph[n2] = []
        # update the adjacency list, graph object, and colors
        self.graph[n1].append( (n2, weight) )
        self.graph[n2].append( (n1, weight) )
        self.G.add_edge(n1, n2, weight=weight)
        self.colors = ['b' for u,v in self.G.edges()]

    '''
    highlight_path
    Parameters: a list of tuples of edges and a color to make them
    Returns: None
    Description: update the color of all provided edges
    '''
    def highlight_path(self, edges, color):
        for edge in edges:
            self.change_path_color(edge, color)

    '''
    change_path_color
    Parameters: a single tuple representing an edge and a color to make it
    Returns: None
    Description: update the color of the edge connecting edge_pair[0] and edge_pair[1]
    '''
    def change_path_color(self, edge_pair, color):
        i = 0
        for u,v in self.G.edges():
            if (edge_pair[0] == u and edge_pair[1] == v) or (edge_pair[1] == u and edge_pair[0] == v):
                self.colors[i] = color
            i += 1
        
    '''
    __repr__
    Parameters: None
    Returns: None
    Description: print(self) will display the adjacency list in human readable format
    '''
    def __repr__(self):
        string = ""
        for key in self.graph.keys():
            string += key + ": "
            for value in self.graph[key]:
                string += f'({value[0]}, {value[1]}), '
            string = string[:len(string)-2]
            string += "\n"
        return string.rstrip()

    '''
    draw
    Parameters: None
    Returns: None
    Description: draw and display the graph object
    '''
    def draw(self):
        pos = nx.shell_layout(self.G)
        nx.draw(self.G, pos, edge_color=self.colors, with_labels=True)
        labels = nx.get_edge_attributes(self.G,'weight')
        nx.draw_networkx_edge_labels(self.G,pos, edge_labels=labels)
        plt.show()

    '''
    parse_file
    Parameters: a filename
    Returns: None
    Description: given a file 'filename' create the adjacency list and display any paths
    '''
    def parse_file(self, filename):
        with open(filename, 'r') as f:
            lines = [line.rstrip().split(',') for line in f.readlines()]
        for line in lines:
            if line[0] == 'D':
                path = [(line[i], line[i+1]) for i in range(1, len(line)-1)]
                print(path)
                self.highlight_path(path, 'r')
            elif line[0] == 'A':
                path = [(line[i], line[i+1]) for i in range(1, len(line)-1)]
                print(path)
                self.highlight_path(path, 'g')
            else:
                for i in range(1, len(line)-1, 2):
                    self.insert(line[0], line[i], line[i+1])

def main():

    my_graph = Graph()

    my_graph.parse_file("test.txt")

    my_graph.draw()

if __name__ == '__main__':
    main()