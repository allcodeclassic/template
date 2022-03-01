// author: classic
// <3 NTV
#include <bits/stdc++.h>

namespace classic {
	struct Edmonds_Karp {
		int size;
		std::vector<std::vector<int>> adjacent;
		std::vector<std::vector<int>> capacity;

		Edmonds_Karp(int n) : size(n), adjacent(size + 1), capacity(size + 1, std::vector<int>(size + 1)) {}

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
			int maximum_flow = 0;
			std::vector<int> parent(size + 1);
			int delta;
			while (delta = bfs(start, ends, parent)) {
				maximum_flow += delta;
				int current = ends;
				while (current != start) {
					int previous = parent[current];
					capacity[previous][current] -= delta;
					capacity[current][previous] += delta;
					current = previous;
				}
			}
			return maximum_flow;
		}
	};
}; // template classic

int main() {
	using namespace std;
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	classic::Edmonds_Karp g(n);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g.add_edge(u, v, w);
	}
	cout << g.max_flow(s, t);
	return 0;
}