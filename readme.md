# 💻 Dijkstra’s Shortest Path Algorithm in C++

This project is a beginner-friendly implementation of **Dijkstra’s Algorithm** in C++, designed to find the shortest path between two cities.  
It uses simple object-oriented structures for **Nodes**, **Edges**, and a **Graph** to manage data efficiently.  

---

## 🚀 Features

- Implementation of **Dijkstra’s Algorithm** from scratch  
- Supports **custom graph data** via `cities.txt` input  
- Object-Oriented design using **Node**, **Edge**, and **Graph** classes  
- Option for **summary** or **detailed path trace** output  
- Beginner-friendly and easy to extend  

---

## 📄 Input File Format (`cities.txt`)

Each line in the file represents a route between two cities and looks like this:

```
"A" "B" R1 2
"B" "C" R2 4
"C" "D" R3 3
```

**Format:**
```
"SourceCity" "DestinationCity" RouteName Distance
```

Example meaning:
- City A is connected to City B via route **R1** with a distance of **2 miles**  
- City B is connected to City C via route **R2** with a distance of **4 miles**  

---

## ⚙️ How It Works

1. The program reads `cities.txt` and automatically builds a graph.  
2. You enter:
   - Starting city name  
   - Destination city name  
   - Whether you want a summary (`Y`) or a full path trace (`N`)  
3. The program runs Dijkstra’s algorithm and prints:
   - Total shortest distance  
   - (Optional) Full step-by-step route with intermediate cities and route names  

---

## 🧠 Example Run

**Input:**
```
Enter Starting City Name: A
Enter Destination City Name: D
Do you want summarized result (Y/N)? n
```

**Output:**
```
Graph Initialization Done Successfully!

A to D: 9 miles.
    A to B via R1 2 miles.
    B to C via R2 4 miles.
    C to D via R3 3 miles.
```

---

## 🧩 File Structure

```
📁 DijkstraShortestPath
│
├── info.txt              # Input data file 01
├── cities.txt            # Input data file 02
├── Source.cpp            # Source code implementing the algorithm
└── readme.md             # Project documentation
```

---

## 🧑‍💻 Author

Developed by **[mniCodingAxis](https://www.youtube.com/@mniCodingAxis/videos)**  
Part of the *Shortest Path Finding Series* on YouTube 🎥  

If you enjoyed this project, don’t forget to **⭐ Star the repository** and **Subscribe** to the channel for upcoming tutorials!

---
