# Lem-In
Lem-In is a learning project about graphs, optimal flow, and pathfinding.


<img src="http://www.hugobally.me/host/img/lemin0.png" width="100%"></img>

From a given input graph and a number N of starting lemmings, lem-in finds the best combination of moves to carry all the lemmings from the source node to the destination node. 

The main constraint is that each node can only contain one lemming at a time. In order to find a quick and reasonable answer, we iterate using a classic Edmonds-Karps BFS, storing the resulting solution and total length at each iteration, ultimately choosing the best result.

The vizualization was made using d3.js's force layout.

Usage :
```
make
./lem-in -e < sample_maps/2_mid_A ; open viz/index.html
```

<img src="http://www.hugobally.me/host/img/lemin2.png" width="100%"></img>
