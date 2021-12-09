# COP3530 Project 3
## Created by: Alyssa Caples, Benjamin Hicks, Jackson Fugate

The goal of this code is to construct a graph where nodes represent actors and edges + edge weights represent the inverse of the number of movies shared by actors. Therefore, when running shortest path algorithms such as Dijkstra's or A-star, we are able to put an interesting spin on the concept of "degrees of separation". In order to execute this code, you will need access to [this dataset](https://www.kaggle.com/rounakbanik/the-movies-dataset) specifically movies_metadata.csv and credits.csv. Place them in csv_files before running any scripts. You can then run various scripts (listed in order below of execution below) to generate an output.

### Generate an Output
- begin in the folder csv_files, which contains the Jupyter Notebook used to parse our database but DOES NOT contain the csv files themselves as they take up too much space to be stored on GitHub. Download these from the Kaggle link above.
- src contains all of the cpp source and header files utilized to process and run graph algorithms (Dijkstra's and A-star). Compile and execute main.cpp passing command line arguments with the actors IDs you wish to find.
- output contains the files written by the cpp code that will be read in and processed using python
- python contains the script utilized to generate a GUI to illustrate the shortest path found between two actors. Simply run this script to display the graph.
- EXAMPLE OUTPUTS contains example png files produced by running our code with different nodes
