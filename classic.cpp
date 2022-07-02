// author: classic
#include <bits/stdc++.h>

// https://github.com/allcodeclassic/wiki
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
	
	struct Edmonds_Karp {
		// Edmonds-Karp algorithm
		// find max flow on graph
		// time complextity O(egde * egde * vertex)
		int size;
		std::vector<std::vector<int>> adjacent;
		std::vector<std::vector<int>> capacity;

		Edmonds_Karp(int num_vertices) : size(num_vertices), adjacent(size), capacity(size, std::vector<int>(size, 0)) {}

		void add_edge(int u, int v, int weight) {
			adjacent[u].emplace_back(v);
			adjacent[v].emplace_back(u);
			capacity[u][v] = weight;
		}

		int bfs(int start, int ends, std::vector<int> &parent) {
			fill(parent.begin(), parent.end(), -1);
			parent[start] = -2;
			std::queue<std::pair<int, int>> que;
			que.emplace(start, 1e9);
			while (!que.empty()) {
				int current = que.front().first;
				int delta = que.front().second;
				que.pop();
				for (int next : adjacent[current]) {
					if (parent[next] == -1 && capacity[current][next] > 0) {
						parent[next] = current;
						int new_delta = std::min(delta, capacity[current][next]);
						if (next == ends) {
							return new_delta;
						}
						que.emplace(next, new_delta);
					}
				}
			}
			return 0;
		}

		int max_flow(int start, int ends) {
			int max_flow = 0;
			std::vector<int> parent(size);
			int delta;
			while (delta = bfs(start, ends, parent)) {
				max_flow += delta;
				int current = ends;
				while (current != start) {
					int previous = parent[current];
					capacity[previous][current] -= delta;
					capacity[current][previous] += delta;
					current = previous;
				}
			}
			return max_flow;
		}
	};
} // template classic

int main() {
	using namespace std;
	ios::sync_with_stdio(false);
	cin.tie(0);
	return 0;
}
