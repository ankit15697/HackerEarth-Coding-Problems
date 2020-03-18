/*
	Let's consider some weird country with N cities and M bidirectional roads of 3 types. It's weird because of some unusual rules about using these roads: men can use roads of types 1 and 3 only and women can use roads of types 2 and 3 only. Please answer the following very interesting question: what is maximum number of roads it's possible to destroy that the country will be still connected for both men and women? Connected country is country where it's possible to travel from any city to any other using existing roads.
*/
#include <bits/stdc++.h>

using namespace std;
int id[1000001];
bool isConnected(vector<int> adj[], int nodes) {
    vector<bool> visited(nodes+1, false);
	visited[0]=true;
	stack<int> st;
	st.push(1);
	while(!st.empty()){
		int t=st.top();
		st.pop();
		if(visited[t]==false){
			visited[t]=true;
		}
		for (auto it = adj[t].begin(); it != adj[t].end(); ++it)
			if (!visited[*it])
				st.push(*it);
		}
	for(int i=1;i<=nodes;i++)
		if(visited[i]==false)
			return false;
	return true;
}
int root(int x) {
	while(x!= id[x]) {
		id[x] = id[id[x]];
		x = id[x];
	}
	return x;
}
void doUnion(int u, int v) {
	int p = root(u);
	int q = root(v);
	id[p] = id[q];
}
int solveQuestion(pair<int,pair<int,int> > adj[], int n, int m) {
	int m_three=0,m_one=0;
	int w_three =0,w_two=0;
		for (int i =0;i<1000001;i++) {
		id[i] = i;
	}
	for (int i = m-1; i >= 0 ; i--) {
		int c = adj[i].first;
		int u = adj[i].second.first;
		int v = adj[i].second.second;
		if(c==3 || c==1) {
			if(root(u) != root(v)) {
				if(c==1) {
					m_one++;
				}
				else{
					m_three++;
				}
				doUnion(u,v);
			}
		}
	}
	if(m_one+m_three != n-1) {
		return -1;
	}
	for (int i =0;i<1000001;i++) {
		id[i] = i;
	}
	for (int i = m-1; i >= 0 ; i--) {
		int c = adj[i].first;
		int u = adj[i].second.first;
		int v = adj[i].second.second;
		if(c==3 || c==2) {
			if(root(u) != root(v)) {
				if(c==2) {
					w_two++;
				}
				else{
					w_three++;
				}
				doUnion(u,v);
			}
		}
	}
	if(w_two+w_three != n-1) {
		return -1;
	}

	int max_three;
	max_three = m_three>w_three?m_three:w_three;
	int result = m - max_three - w_two -m_one;
	return result;

}
int main() {
	int n,m;
	cin>>n>>m;
	int a,b,c;
	pair<int,pair<int,int> > adj[m];
	vector<int> vec[n+1];
	int three = 0;
	for (int i=0;i<m;i++) {
		cin>>a>>b>>c;
		vec[a].push_back(b);
		vec[b].push_back(a);
		adj[i] = make_pair(c,make_pair(a,b));
	}
	if(!isConnected(vec,n)) {
		cout << "-1\n";
	}
	else {
			sort(adj,adj+m);
			cout<<solveQuestion(adj,n,m)<<endl;
	}
}
