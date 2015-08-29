#include "flowgraph.cpp"
// g.add_edge(u,v_index,cap,cost); g.add_edge(v,u_index,0,-cost)
struct Q{ int u; ll c,w;}; // target, maxflow and total weight (cost)
bool operator>(const Q &l, const Q &r){return l.w > r.w;}
struct Edmonds_Karp_Dijkstra{
	FlowGraph &g; int V,s,t; vector<ll> pot;
	Edmonds_Karp_Dijkstra(FlowGraph &g, int s, int t) :
		g(g), V(g.size()), s(s), t(t), pot(V) {}
	pair<ll,ll> run() { // return pair<f, cost>
		ll maxflow = 0, cost = 0;
		fill(F(pot), INF); pot[s]=0; // Bellman-Ford for potentials
		REP(i,V-1) REP(u,V) for(auto &e : g[u])
			if(e.cap>e.f) pot[e.v] = min(pot[e.v], pot[u] + e.cost);
		while (true) {
			priority_queue<Q,vector<Q>,greater<Q>> q;
			vector<vector<S>::iterator> p(V,g.front().end());
			vector<ll> dist(V, INF); ll f;
			q.push({s, INF, 0}); dist[s]=0;
			while(!q.empty()){
				auto u = q.top().u; ll w = q.top().w,d;
				f = q.top().c; q.pop();
				if(w!=dist[u]) continue; if(u==t) break;
				for(auto it = g[u].begin(); it!=g[u].end(); it++){
					const auto &e = *it;
					d =  w + e.cost + pot[u] - pot[e.v];
					if(e.cap>e.f && d < dist[e.v]){
						q.push({e.v, min(f, e.cap-e.f),dist[e.v] = d});
						p[e.v]=it;
			}	}	}
			auto it = p[t];
			if(it == g.front().end()) return {maxflow,cost};
			while(it != g.front().end()){
				auto & r = g[it->v][it->r];
				cost += f * it->cost; it->f+=f;
				r.f -= f; it = p[r.v];
			}
			maxflow += f;
	}	}
};
