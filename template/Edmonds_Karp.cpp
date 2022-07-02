// author: classic
#include <bits/stdc++.h>

// https://github.com/allcodeclassic/template
namespace classic {
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
	int num_vertices, num_edges, start, ends;
	cin >> num_vertices >> num_edges >> start >> ends;
	start--;
	ends--;
	classic::Edmonds_Karp g(num_vertices);
	for (int i = 0; i < num_edges; i++) {
		int u, v, weight;
		cin >> u >> v >> weight;
		u--;
		v--;
		g.add_edge(u, v, weight);
	}
	cout << g.max_flow(start, ends);
	return 0;
}
