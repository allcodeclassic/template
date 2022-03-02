// author: classic
#include <bits/stdc++.h>

namespace classic {
	long long Dijkstra(int start, int ends, std::vector<std::vector<std::pair<long long, int>>> &adjacent) {
		// Dijkstra's algorithm
		// shortest path weight from start to ends
		// time complexity O(vertex + egde * log(vertex))
		int size = (int)adjacent.size();
		std::vector<long long> dist(size, 1e15);
		std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> min_heap;
		min_heap.emplace(0, start);
		dist[start] = 0;
		while (!min_heap.empty()) {
			std::pair<long long, int> current = min_heap.top(); 
			long long dist_current = current.first;
			int vertex_current = current.second;
			min_heap.pop();
			if (dist_current > dist[vertex_current]) {
				continue;
			}
			for (std::pair<long long, int> next : adjacent[vertex_current]) {
				long long dist_current_to_next = next.first;
				int vertex_next = next.second;
				if (dist[vertex_next] > dist[vertex_current] + dist_current_to_next) {
					dist[vertex_next] = dist[vertex_current] + dist_current_to_next;
					min_heap.emplace(dist[vertex_next], vertex_next);
				}
			}
		}
		return dist[ends];
	}

	std::vector<long long> Dijkstra(int start, std::vector<std::vector<std::pair<long long, int>>> &adjacent) {
		// Dijkstra's algorithm
		// shortest path weight from start to all vertices
		// time complexity O(vertex + egde * log(vertex))
		int size = (int)adjacent.size();
		std::vector<long long> dist(size, 1e15);
		std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> min_heap;
		min_heap.emplace(0, start);
		dist[start] = 0;
		while (!min_heap.empty()) {
			std::pair<long long, int> current = min_heap.top(); 
			min_heap.pop();
			long long dist_current = current.first;
			int vertex_current = current.second;
			if (dist_current > dist[vertex_current]) {
				continue;
			}
			for (std::pair<long long, int> next : adjacent[vertex_current]) {
				long long dist_current_to_next = next.first;
				int vertex_next = next.second;
				if (dist[vertex_next] > dist[vertex_current] + dist_current_to_next) {
					dist[vertex_next] = dist[vertex_current] + dist_current_to_next;
					min_heap.emplace(dist[vertex_next], vertex_next);
				}
			}
		}
		return dist;
	}
} // template classic

int main() {
	using namespace std;
	ios::sync_with_stdio(false);
	cin.tie(0);
	int num_vertices, num_edges;
	cin >> num_vertices >> num_edges;
	vector<vector<pair<long long, int>>> adjacent(num_vertices);
	for (int i = 0; i < num_edges; i++) {
		int u, v;
		long long weight;
		cin >> u >> v >> weight;
		u--;
		v--;
		adjacent[u].emplace_back(weight, v);
		// adjacent[v].emplace_back(weight, u); // undirected graph
	}
	vector<long long> dist = classic::Dijkstra(0, 3, adjacent);
	for (int i = 0; i < num_vertices; i++) {
		cout << dist[i] << ' ';
	}
	return 0;
}