// You have come a long way warrior
// Come rest with us
//
//    /\_/\       /\      (\__/)    A__A
//   ( ˶•o•)     /  \     (•ω• )   (•⤙• )
// ଘ(ა    )     /_/\_\     (ა  ૮)｡  (    )੭
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define tcT template<class T
tcT> using ordered_set = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;
using ll = long long;
using db = long double;
using str = string;
using pi = pair<int,int>;
using pll = pair<ll,ll>;
using ppi = pair<int,pair<int,int>>;
#define mp make_pair
#define pb push_back
#define f(i,a,b) for(ll i=a;i<b;i++)
#define fe(i,a,b) for(ll i=a;i<=b;i++)
#define ff(i,a,b) for(ll i=b-1;i>=a;i--)
#define each(a,x) for (auto& a: x)
#define rall(x) x.rbegin(),x.rend()
#define all(x) x.begin(),x.end()
#define PYES cout<<"YES"<<endl
#define PNO cout<<"NO"<<endl
#define PYes cout<<"Yes"<<endl
#define PNo cout<<"No"<<endl
#define tcT template<class T
tcT> using V = vector<T>; 
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vvi = V<vi>;
using vll = V<ll>;
using vvll = V<vll>;
using vb = V<bool>;
using vvb = V<vb>;
using vpi = V<pi>;
using vpll = V<pll>;
//const int MOD = 1e9+7;
//const db PI = acos((db)-1);
//mt19937 rng(0); // or mt19937_64
//const ll inf = LLONG_MAX;
//const int inf = INT_MAX;
#ifdef LOCAL
#include "imp/debug.h"
#else
#define debug(...) 42
#endif

struct pt {
    db x, y;
    pt() {}
    pt(db _x, db _y) : x(_x), y(_y) {}
    pt operator-(const pt& p) const { return pt(x - p.x, y - p.y); }
    bool operator==(const pt& p) const { return ((x==p.x)&&(y==p.y)); }
    db cross(const pt& p) const { return x * p.y - y * p.x; }
    db cross(const pt& a, const pt& b) const { return (a - *this).cross(b - *this); }
};
int sgn(const db& x) { return x >= 0 ? x ? 1 : 0 : -1; }

int orinentation(const pt& a, const pt& b){
    if(a.x==b.x){
        if(a.y<b.y){
            return 0;
        }
        else if(a.y>b.y){
            return 1;
        }
        else{
            return -1;
        }
    }
    else if(a.y==b.y){
        if(a.x<b.x){
            return 2;
        }
        else if(a.x>b.x){
            return 3;
        }
        else{
            return -1;
        }
    }
    else return -1;
}

bool inter1(db a, db b, db c, db d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

bool check_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
        return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
           sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}

void solve(){
    ll n;
    ifstream input;
    input.open("input"+ to_string(03)+".txt");
    int ncrystals,nmines;
    input>>ncrystals;
    V<pair<int,pt>> crystals(ncrystals); // < points, <x,y>>
    f(i,0,ncrystals){
        input>>crystals[i].second.x>>crystals[i].second.y>>crystals[i].first;
    }
    input>>nmines;
    V<pair<int,pt>> mines(nmines); // < -points, <x,y>>
    f(i,0,nmines){
        input>>mines[i].second.x>>mines[i].second.y>>mines[i].first;
    }
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
