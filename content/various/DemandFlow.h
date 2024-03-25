/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Max Flow with demands
 * Status: Tested on kattis, SPOJ FASTFLOW, infoarena maxflow
 */

#pragma once

struct flow {
	struct edge {
		int to, flow, next;
	};
	vector <edge> edges;
	vector <int> head, act, h;
	int S, D;
	void add(int from, int to, int f, int rev_f = 0) {
		edges.push_back({ to, f, (int)edges.size() });
		swap(edges.back().next, head[from]);
		edges.push_back({ from, rev_f, (int)edges.size() });
		swap(edges.back().next, head[to]);
	}
	bool bfs() {
		fill(h.begin(), h.end(), -1);
		h[S] = 0;
		vector <int> q = { S };
		for (int it = 0; it < q.size() && h[D] == -1; it++) {
			int nod = q[it];
			for (int i = head[nod]; i != -1; i = edges[i].next)
				if (edges[i].flow && h[edges[i].to] == -1)
					h[edges[i].to] = 1 + h[nod], q.push_back(edges[i].to);
		}
		return h[D] != -1;
	}
	int dfs(int nod, int flow) {
		if (flow == 0 || nod == D)
			return flow;
		while (act[nod] != -1) {
			edge& e = edges[act[nod]];
			int d;
			if (e.flow && h[e.to] == 1 + h[nod] && (d = dfs(e.to, min(flow, e.flow))) != 0) {
				e.flow -= d;
				edges[act[nod] ^ 1].flow += d;
				return d;
			}
			act[nod] = edges[act[nod]].next;
		}
		return 0;
	}
	int get() {
		int f = 0;
		while (bfs()) {
			act = head;
			int d;
			while ((d = dfs(S, 1e9)) != 0)
				f += d;
		}
		return f;
	}
  init(int dim) {
    head.resize(dim + 1, -1);
    h.resize(dim + 1);
    S = 1;
    D = dim;
  }
};
 
struct demand_flow {
  int n;
  struct edge {
    int from;
    int to;
    int lo;
    int hi;
    int taken;
    int id;
  };
  vector<edge> edges;
  void init(int nn) {
    n = nn;
    edges.clear();
  }
  void add(int a, int b, int lo, int hi) {
    edge it;
    it.from = a;
    it.to = b;
    it.lo = lo;
    it.hi = hi;
    it.taken = 0;
    it.id = 0;
    edges.push_back(it);
  }
  int ret;
  bool good;
  void rec() {
    ret = 0;
    good = 1;
    flow gbig;
    gbig.init(n + 2);
    gbig.add(1 + n, 1 + 1, INF);
    int slo = 0;
    for (auto &it : edges) {
      if (it.lo > it.hi) {
        good = 0;
        return;
      }
      if (it.hi == 0) continue;
 
      slo += it.lo;
      it.taken = 0;
 
      it.id = (int) gbig.edges.size();
      assert(it.lo >= 0);
      gbig.add(1 + it.from, 1 + it.to, it.hi - it.lo);
 
      gbig.add(1, 1 + it.to, it.lo);
      gbig.add(1 + it.from, 2 + n, it.lo);
    }
    kek = slo;
    if (gbig.get() != slo) {
      good = 0;
      return;
    }
    flow rl;
    rl.init(n);
    for (auto &it : edges) {
      if (it.hi == 0) continue;
      /// momentan e efectiv cat am acum
      /// cat = cat a trecut in plus de flowmin
      int new_id = (int) rl.edges.size();
      rl.add(it.from, it.to, gbig.edges[it.id].flow, gbig.edges[it.id ^ 1].flow);
      it.id = new_id;
    }
    int val = rl.get();
    for (auto &it : edges) {
      if (it.hi == 0) continue;
      it.taken = it.lo + rl.edges[it.id ^ 1].flow;
      if (it.from == 1) {
        ret += it.taken;
      }
      if (it.to == 1) {
        ret -= it.taken;
      }
    }
  }
};