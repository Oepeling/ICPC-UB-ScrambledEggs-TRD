/**
 * Author: Tourist
 * License: CC0
 * Description: Hungarian Algorithm for Maximum Cost Maximum Matching when a perfect matching exists.
 * Time: $O(N^3)$

 */


struct Hungary {
	int n, m;
	vector<vector<int>> a;
	vector<int> potentiali, potentialj;
	vector<int> pairi, pairj;
	vector<int> way;
	vector<int> minv;
	vector<bool> used;
	Hungary(int nn, int mm) :
		n(nn),
		m(mm),
		a(nn + 1, vector<int>(mm + 1, 0)),
		potentiali(nn + 1, 0),
		potentialj(mm + 1, 0),
		pairi(nn + 1, -1),
		pairj(mm + 1, -1),
		way(mm + 1, -1) {
 
		assert(n <= m);
	}
	void pairup(int i, int j) {
		pairi[i] = j;
		pairj[j] = i;
	}
	void add_row(int row) {
		minv.clear();
		minv.resize(m + 1, INF);
		used.clear();
		used.resize(m + 1, 0);
		pairup(row, m);
		int j0 = m;
		do {
			used[j0] = 1;
			int i0 = pairj[j0];
			int j1 = -1, score = INF;
			for (int j = 0; j <= m; j++) {
				if (used[j] == 0) {
					int cur = a[i0][j] - potentiali[i0] - potentialj[j];
					if (cur < minv[j]) {
						minv[j] = cur;
						way[j] = j0;
					}
					if (minv[j] < score) {
						score = minv[j];
						j1 = j;
					}
				}
			}
			for (int j = 0; j <= m; j++) {
				if (used[j] == 1) {
					potentiali[pairj[j]] += score;
					potentialj[j] -= score;
				}
				else {
					minv[j] -= score;
				}
			}
			j0 = j1;
		} while (pairj[j0] != -1);
		do {
			int j1 = way[j0];
			pairup(pairj[j1], j0);
			j0 = j1;
		} while (j0 != m);
	}
	int solve() {
		for (int i = 0; i < n; i++) {
			add_row(i);
		}
		return -potentialj[m];
	}
};