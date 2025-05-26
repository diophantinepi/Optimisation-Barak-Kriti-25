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
mt19937 rng(time(nullptr)); // or mt19937_64
//const ll inf = LLONG_MAX;
//const int inf = INT_MAX;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t,l,r;
    string s;
    ofstream file;
    cout<<"Range of Testcases to Generate: ";
    cout.flush();
    cin >> l>>r;
    fe(t,l,r)
    {
        file.open("input"+ to_string(t)+".txt");
        int n1 = 1+rng()%10000;
        int n2 = 1+rng()%n1;
        n1-=n2;
        file<<n1<<endl;
        while(n1--){
            int x = rng()%1001,y = rng()%1001;
            ll c = rng()%1000000000;
            file<<x<<" "<<y<<" "<<c<<endl;
        }
        file<<n2<<endl;
        while(n2--){
            int x = rng()%1001,y = rng()%1001;
            ll c = rng()%1000000000;
            file<<x<<" "<<y<<" "<<c<<endl;
        }

        file.close();
    }
    return 0;
}