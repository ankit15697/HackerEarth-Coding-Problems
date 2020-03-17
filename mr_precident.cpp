/*
	You have recently started playing a brand new computer game called "Mr. President". The game is about ruling a country, building infrastructures and developing it.

Your country consists of N cities and M bidirectional roads connecting them. Each road has assigned a cost of its maintenance. The greatest achievement in the game is called "Great administrator" and it is given to a player who manage to have all cities in the country connected by roads in such a way that it is possible to travel between any two cities and that the sum of maintenance costs of these roads is not greater than K.

This is very hard to accomplish, but you are very close to do it. More precisely, you have just discovered a new method of transforming standard roads into super roads, with cost of maintenance just 1, due to their extreme durability.

The bad news is that it is very expensive to transform a standard road into a super road, but you are so excited that you are going to do it anyway.

In addition, because you have a lot of other expenses, you also want to first demolish as many roads as possible in order to safe some money on their maintenance first and then start working on getting the achievement. You can demolish any road in the country and that operation does not cost you anything.

Because you want to spend the absolutely minimum money in order to get the achievement, you are interested in the smallest number of transformations of standard roads into super roads in such a way that you can do that.
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
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
ll solveQuestion(pair<int,pair<int,int> > adj[], int n, int m, ll k) {
	vector<int> result;
	ll cost = 0;
	for (int i = 0; i < m ; i++) {
		ll w = adj[i].first;
		int u = adj[i].second.first;
		int v = adj[i].second.second;
		if(root(u) != root(v)) {
			cost +=w;
			result.push_back(w);
			doUnion(u,v);
		}
	}
	int c = result.size()-1;
	int cnt =0;
	while(cost > k && c>=0) {
		cost = cost - result[c] +1 ;
		cnt++;
		c--;
	}
	if(cost>k) {
		return -1;
	}
	return cnt;
}

int main(void) {
	int n,m;
	ll k;
	//cin>>n>>m>>k;
	scanf("%d %d %lld", &n,&m,&k);
	int u,v,w;
	pair<int,pair<int,int> > adj[m];
	vector<int> vec[n+1];
	for (int i =0;i<1000001;i++) {
		id[i] = i;
	}
	for(int i=0;i<m;i++) {
		//cin>>u>>v>>w;
		scanf("%d %d %d", &u,&v,&w);
		vec[u].push_back(v);
		vec[v].push_back(u);
		adj[i] = make_pair(w,make_pair(u,v));
	}
	if(!isConnected(vec,n)) {
		cout << "-1\n";
	}
	else {
			sort(adj,adj+m);
			printf( "%lld\n",solveQuestion(adj,n,m,k));
	}
} 