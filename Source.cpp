#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<limits.h>
#include<algorithm>
#include<vector>

using namespace std;

#define INFINITY INT_MAX

class Node {
private:
	int distance;
	vector<int> neighbourIndexes;
	int parentNodeIndex;
	string nodeLabel;
	bool isVisited;
public:
	Node() {
		this->distance = INFINITY;
		this->neighbourIndexes = vector<int>();
		this->parentNodeIndex = -1;
		this->nodeLabel = "";
		this->isVisited = false;
	}

	void setDistance(int distance) {
		this->distance = distance;
	}

	int getDistance() {
		return this->distance;
	}

	void setNeighbours(vector<int>& neighbourIndexes) {
		this->neighbourIndexes = neighbourIndexes;
	}

	vector<int>& getNeighbours() {
		return this->neighbourIndexes;
	}

	void setParentNodeIndex(int parentNodeIndex) {
		this->parentNodeIndex = parentNodeIndex;
	}

	int getParentNodeIndex() {
		return this->parentNodeIndex;
	}

	void setNodeLabel(string nodeLabel) {
		this->nodeLabel = nodeLabel;
	}

	string getNodeLabel() {
		return this->nodeLabel;
	}

	void setIsVisited(bool isVisited) {
		this->isVisited = isVisited;
	}

	bool getIsVisited() {
		return this->isVisited;
	}
};

class Edge {
private:
	int sourceNodeIndex;
	int destinationNodeIndex;
	string edgeLabel;
	int edgeCost;
public:
	Edge(int sourceNodeIndex, int destinationNodeIndex, string edgeLabel, int edgeCost) {
		this->sourceNodeIndex = sourceNodeIndex;
		this->destinationNodeIndex = destinationNodeIndex;
		this->edgeLabel = edgeLabel;
		this->edgeCost = edgeCost;
	}

	void setSourceNodeIndex(int sourceNodeIndex) {
		this->sourceNodeIndex = sourceNodeIndex;
	}

	int getSourceNodeIndex() {
		return this->sourceNodeIndex;
	}

	void setDestinationNodeIndex(int destinationNodeIndex) {
		this->destinationNodeIndex = destinationNodeIndex;
	}

	int getDestinationNodeIndex() {
		return this->destinationNodeIndex;
	}

	void setEdgeCost(int edgeCost) {
		this->edgeCost = edgeCost;
	}

	int getEdgeCost() {
		return this->edgeCost;
	}

	void setEdgeLabel(string edgeLabel) {
		this->edgeLabel = edgeLabel;
	}

	string getEdgeLabel() {
		return this->edgeLabel;
	}
};

class Graph {
private:
	vector<Node> Nodes;
	vector<Edge> Edges;
public:
	Graph() {
		this->Nodes = vector<Node>();
		this->Edges = vector<Edge>();
	}

	void setNodes(vector<Node>& Nodes) {
		this->Nodes = Nodes;
	}

	vector<Node>& getNodes() {
		return this->Nodes;
	}

	void setEdges(vector<Edge>& Edges) {
		this->Edges = Edges;
	}

	vector<Edge>& getEdges() {
		return this->Edges;
	}
};

int insertNode(Graph& graph, string nodeLabel) {
	int index = graph.getNodes().size();

	if (graph.getNodes().empty()) {
		Node node;
		node.setNodeLabel(nodeLabel);
		graph.getNodes().push_back(node);
		return index;
	}

	for (int i = 0; i < graph.getNodes().size(); i++)
		if (graph.getNodes()[i].getNodeLabel() == nodeLabel)
			return i;


	Node node;
	node.setNodeLabel(nodeLabel);
	graph.getNodes().push_back(node);

	return index;
}

void insertNeighbour(Graph& graph, int nodeIndex, int neighbourIndex) {

	if (graph.getNodes()[nodeIndex].getNeighbours().empty()) {
		graph.getNodes()[nodeIndex].getNeighbours().push_back(neighbourIndex);
		return;
	}

	int neighboursSize = graph.getNodes()[nodeIndex].getNeighbours().size();
	for (int i = 0; i < neighboursSize; i++)
		if (graph.getNodes()[nodeIndex].getNeighbours()[i] == neighbourIndex)
			return;

	graph.getNodes()[nodeIndex].getNeighbours().push_back(neighbourIndex);
}

void insertEdge(Graph& graph, int sourceNodeIndex, int destinationNodeIndex, string edgeLabel, int edgeCost) {
	Edge tempEdge(sourceNodeIndex, destinationNodeIndex, edgeLabel, edgeCost);
	graph.getEdges().push_back(tempEdge);
}

int findNodeIndex(Graph& graph, string nodeLabel) {
	int index = -1;

	if (graph.getNodes().empty())
		return index;

	for (int i = 0; i < graph.getNodes().size(); i++)
		if (graph.getNodes()[i].getNodeLabel() == nodeLabel)
			return i;

	return index;
}

int findEdgeIndex(Graph& graph, int sourceNodeIndex, int destinationNodeIndex) {
	int index = -1;

	if (graph.getEdges().empty())
		return index;

	for (int i = 0; i < graph.getEdges().size(); i++) {
		if (graph.getEdges()[i].getSourceNodeIndex() == sourceNodeIndex &&
			graph.getEdges()[i].getDestinationNodeIndex() == destinationNodeIndex)
			return i;
		if (graph.getEdges()[i].getSourceNodeIndex() == destinationNodeIndex &&
			graph.getEdges()[i].getDestinationNodeIndex() == sourceNodeIndex)
			return i;
	}

	return index;
}

int findMinimumDistanceNeighbourIndex(Graph& graph, vector<int>& nodes) {
	int index = -1;
	int minimumDistance = INFINITY;

	if (nodes.empty())
		return index;

	for (int i = 0; i < nodes.size(); i++) {
		if (graph.getNodes()[nodes[i]].getDistance() < minimumDistance) {
			minimumDistance = graph.getNodes()[nodes[i]].getDistance();
			index = i;
		}
	}

	return index;
}

bool checkDuplicate(vector<int>& nodes, int nodeIndex) {
	bool duplicate = false;

	if (nodes.empty())
		return duplicate;

	for (int i = 0; i < nodes.size(); i++)
		if (nodes[i] == nodeIndex)
			return true;

	return duplicate;
}

void exportMatlabScript(Graph& graph) {
	string filename = "graphCities.m"; //Compliant to MATLAB2016a 
	ofstream outputStream;
	outputStream.open(filename.c_str(), ios::app | ios::out);

	outputStream << "sources = zeros(1," << graph.getEdges().size() << ");" << endl;
	outputStream << "destinations = zeros(1," << graph.getEdges().size() << ");" << endl;
	outputStream << "weights = zeros(1," << graph.getEdges().size() << ");" << endl;

	for (int i = 0; i < graph.getNodes().size(); i++) {
		outputStream << "names{" << (i + 1) << "} = '" << graph.getNodes()[i].getNodeLabel() << "';" << endl;
	}

	for (int i = 0; i < graph.getEdges().size(); i++) {
		outputStream << "sources(" << (i + 1) << ") = " << (graph.getEdges()[i].getSourceNodeIndex() + 1) << ";" << endl;
		outputStream << "destinations(" << (i + 1) << ") = " << (graph.getEdges()[i].getDestinationNodeIndex() + 1) << ";" << endl;
		outputStream << "weights(" << (i + 1) << ") = " << graph.getEdges()[i].getEdgeCost() << ";" << endl;
		outputStream << "routes{" << (i + 1) << "} = '" << graph.getEdges()[i].getEdgeLabel() << " | " 
			<< graph.getEdges()[i].getEdgeCost() << "';" << endl;
	}

	outputStream << "G = graph(sources,destinations,weights,names);" << endl;
	outputStream << "LineWidths = 2.5*G.Edges.Weight / max(G.Edges.Weight);" << endl;
	outputStream << "h = plot(G,'LineWidth',LineWidths);" << endl;
	outputStream << "[T, p] = minspantree(G);" << endl;
	outputStream << "highlight(h,T,'EdgeColor','m','LineWidth',1.5,'Marker','.','NodeColor','r','MarkerSize',20,'LineStyle','-');" << endl;
	outputStream << "labeledge(h,sources,destinations,routes);" << endl;
	outputStream.close();
}

void tracePath(Graph& graph, int sourceNodeIndex, int destinationNodeIndex) {
	vector<pair<int, int>> hops;

	while (destinationNodeIndex != sourceNodeIndex) {
		int parentIndex = graph.getNodes()[destinationNodeIndex].getParentNodeIndex();
		hops.push_back(make_pair(parentIndex, destinationNodeIndex));
		destinationNodeIndex = parentIndex;
	}

	for (int i = hops.size() - 1; i >= 0; i--) {
		int edgeIndex = findEdgeIndex(graph, hops[i].first, hops[i].second);
		cout << "\t" << graph.getNodes()[hops[i].first].getNodeLabel() << " to "
			<< graph.getNodes()[hops[i].second].getNodeLabel() << " via " << graph.getEdges()[edgeIndex].getEdgeLabel()
			<< " " << graph.getEdges()[edgeIndex].getEdgeCost() << " miles." << endl;
	}
}

void Dijkstra(Graph& graph, int sourceNodeIndex, int destinationNodeIndex, bool summary = true) {
	//Make a vector of unvisited nodes
	vector<int> unvisitedNodes;
	//Mark distance of source node as zero
	graph.getNodes()[sourceNodeIndex].setDistance(0);
	//Add source node into this vector
	unvisitedNodes.push_back(sourceNodeIndex);
	int currentSourceNodeIndex = sourceNodeIndex;
	//while unvisited nodes are not empty
	while (!unvisitedNodes.empty()) {
		for(int i=0; i<graph.getNodes()[currentSourceNodeIndex].getNeighbours().size(); i++){
			int neighbourIndex = graph.getNodes()[currentSourceNodeIndex].getNeighbours()[i];
			//Make sure the neighbour node is not visited
			if (!graph.getNodes()[neighbourIndex].getIsVisited()) {
				//update source node's neighbour distances
				int edgeIndex = findEdgeIndex(graph, currentSourceNodeIndex, neighbourIndex);
				
				int currentDistance = graph.getNodes()[neighbourIndex].getDistance();
				int approachingDistance = graph.getNodes()[currentSourceNodeIndex].getDistance();
				int cost = graph.getEdges()[edgeIndex].getEdgeCost();
				int newDistance = min(currentDistance, approachingDistance + cost);
				//Here update the distance 
				//Also set the parent node index
				if (newDistance < currentDistance) {
					graph.getNodes()[neighbourIndex].setDistance(newDistance);
					graph.getNodes()[neighbourIndex].setParentNodeIndex(currentSourceNodeIndex);
				} 
				//Add this neighbour into unvisited nodes
				if (!checkDuplicate(unvisitedNodes, neighbourIndex))
					unvisitedNodes.push_back(neighbourIndex);
			}
		}
		//mark the source node as visited
		graph.getNodes()[currentSourceNodeIndex].setIsVisited(true);
		//remove source node from unvisited nodes 
		unvisitedNodes.erase(remove(unvisitedNodes.begin(), unvisitedNodes.end(), currentSourceNodeIndex), unvisitedNodes.end());
		//choose next node to become source node
		int newIndex = findMinimumDistanceNeighbourIndex(graph, unvisitedNodes);
		if (newIndex == -1)
			break;
		currentSourceNodeIndex = unvisitedNodes[newIndex];
		//if destination node is found or unvisited nodes are empty -> end
		if (currentSourceNodeIndex == destinationNodeIndex)
			break;
	}

	cout << endl << endl << graph.getNodes()[sourceNodeIndex].getNodeLabel() << " to "
		<< graph.getNodes()[destinationNodeIndex].getNodeLabel() << ": "
		<< graph.getNodes()[destinationNodeIndex].getDistance() << " miles." << endl;

	if (!summary)
		tracePath(graph, sourceNodeIndex, destinationNodeIndex);

}

int main() {
	Graph graph;
	ifstream sourceCitiesfile("cities.txt");

	string line;
	if (sourceCitiesfile.is_open()) {
		//"A" "B" R1 2
		while (getline(sourceCitiesfile, line)) {
			string sourceNodeLabel;
			string destinationNodeLabel;
			string edgeLabel;
			int edgeCost;

			stringstream ss(line);
			// Read the first quoted string (source city)
			getline(ss, sourceNodeLabel, '"'); // skip until first quote
			getline(ss, sourceNodeLabel, '"'); // read inside the quotes

			// Read the second quoted string (destination city)
			getline(ss, destinationNodeLabel, '"'); // skip until next quote
			getline(ss, destinationNodeLabel, '"'); // read inside the quotes

			ss >> edgeLabel >> edgeCost;

			int sourceNodeIndex = insertNode(graph, sourceNodeLabel);
			int destinationNodeIndex = insertNode(graph, destinationNodeLabel);

			insertNeighbour(graph, sourceNodeIndex, destinationNodeIndex);
			insertNeighbour(graph, destinationNodeIndex, sourceNodeIndex);

			insertEdge(graph, sourceNodeIndex, destinationNodeIndex, edgeLabel, edgeCost);
		}
		sourceCitiesfile.close();
	}
	
	cout << "Graph Initialization Done Successfully!" << endl << endl;

	string sourceCityName;
	string destinationCityName;
	char summaryChar;

	int sourceCityIndex;
	int destinationCityIndex;
	bool summaryMode = false;

	cout << "Enter Starting City Name: ";
	getline(cin, sourceCityName);

	sourceCityIndex = findNodeIndex(graph, sourceCityName);

	if (sourceCityIndex == -1) {
		cout << "No such city found..." << endl;
		return 1;
	}

	cout << "Enter Destination City Name: ";
	getline(cin, destinationCityName);

	destinationCityIndex = findNodeIndex(graph, destinationCityName);

	if (destinationCityIndex == -1) {
		cout << "No such city found..." << endl;
		return 1;
	}

	cout << "Do you want summarized result (Y/N)?";
	cin >> summaryChar;

	if (summaryChar == 'Y' || summaryChar == 'y' || summaryChar == 'N' || summaryChar == 'n') {
		if (summaryChar == 'Y' || summaryChar == 'y')
			Dijkstra(graph, sourceCityIndex, destinationCityIndex);
		else
			Dijkstra(graph, sourceCityIndex, destinationCityIndex, false);
	}
	else {
		cout << "Invalid Input" << endl;
		return 1;
	}

	return 0;
}