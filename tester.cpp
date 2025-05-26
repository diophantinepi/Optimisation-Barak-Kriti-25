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

ll ourscore,maxscore,printpolygon=1;

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


int solve(ifstream& input, ifstream& output){
    int ncrystals,nmines;
    maxscore=0;
    input>>ncrystals;
    V<pair<int,pt>> crystals(ncrystals); // < points, <x,y>>
    map<int,int> mapp;
    map<int,int> mappp;
    f(i,0,ncrystals){
        input>>crystals[i].second.x>>crystals[i].second.y>>crystals[i].first;
        maxscore+=crystals[i].first;
        mapp[crystals[i].second.x]++;
    }
    input>>nmines;
    V<pair<int,pt>> mines(nmines); // < -points, <x,y>>
    f(i,0,nmines){
        input>>mines[i].second.x>>mines[i].second.y>>mines[i].first;
    }
    
    ll score,edges;
    output>>score;
    ourscore=score;
    output>>edges>>edges; // input is actually V,E but for now this
    //if(edges>1000)return 0;
    V<pair<pt,pt>> edgelist(edges);
    f(i,0,edges){
        output>>edgelist[i].first.x>>edgelist[i].first.y>>edgelist[i].second.x>>edgelist[i].second.y;
    }
    if(!(edgelist[0].first==edgelist[edges-1].second)){
        return 1;
    }
    f(i,1,edges){
        if(!(edgelist[i-1].second==edgelist[i].first)){
            return 1;
        }
    }
    int dir=-1; // U D R L
    
    dir=orinentation(edgelist[edges-1].first,edgelist[edges-1].second);
    if(printpolygon==1)cout<<"polygon(";
    f(i,0,edges){
        int new_dir=orinentation(edgelist[i].first,edgelist[i].second);
        if(new_dir==-1){
            cout<<edgelist[i].first.x<<" "<<edgelist[i].first.y<<" "<<edgelist[i].second.x<<" "<<edgelist[i].second.y<<endl;
            return 2;
        }
        if(dir<2){
            if(dir+new_dir==1){
                cout<<edgelist[i].first.x<<" "<<edgelist[i].first.y<<" "<<edgelist[i].second.x<<" "<<edgelist[i].second.y<<endl;
                return 2;
            }
        }
        else{
            if(dir+new_dir==5){
                cout<<edgelist[i].first.x<<" "<<edgelist[i].first.y<<" "<<edgelist[i].second.x<<" "<<edgelist[i].second.y<<endl;
                return 2;
            }
        }
        dir=new_dir;
        if(printpolygon==1&&i!=0)cout<<",";
        if(printpolygon==1)cout<<"("<<edgelist[i].first.x<<","<<edgelist[i].first.y<<")";
        
    }
    if(printpolygon==1)cout<<")"<<endl;
    ll actualscore=0;
    f(i,0,ncrystals){
        bool inside = false,online=false;
        pt lastpt(10001,crystals[i].second.y);
        f(j,0,edges){
            if(check_inter(crystals[i].second,lastpt,edgelist[j].first,edgelist[j].second)){
                inside=!inside;
            }
        }
        if(inside||online){
            actualscore+=crystals[i].first;
        }
    }
    f(i,0,nmines){
        bool inside = false;
        pt lastpt(10001,mines[i].second.y);
        f(j,0,edges){
            if(check_inter(mines[i].second,lastpt,edgelist[j].first,edgelist[j].second)){
                inside=!inside;
            }
        }
        if(inside){
            actualscore-=mines[i].first;
        }
    }
    if(actualscore!=score){
        cout<<"got "<<actualscore<<" instead of"<<score<<endl;
        return 3;
    }
    return -1;
    // y=5\ \left\{1<x<4\right\}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l,r;
    ifstream output;
    ifstream input;
    string s;
    cout<<"Initiate real checking?: ";
    cout.flush();
    string real,poly;
    cin>>real;
    cout<<"Print Polygon (put in desmos)?: ";
    cout.flush();
    cin>>poly;
    if(poly[0]!='y'&&poly[0]!='Y')printpolygon=0;
    cout<<"Range of Outputs to Check: ";
    cout.flush();
    cin >>l>>r;
    
    fe(ttcase,l,r)
    {
        if(real[0]=='y'||real[0]=='Y'){
            string add=((ttcase<10)?"0":"");
            input.open("input"+ add + to_string(ttcase)+".txt");
            output.open("output"+add+ to_string(ttcase)+".txt");
        }
        else{
            input.open("input"+ to_string(ttcase)+".txt");
            output.open("output"+ to_string(ttcase)+".txt");
        }
        
    
        int status = solve(input,output);

        if(status==0){
            cout<<"Too many Edges on "<<ttcase<<endl;
            break;
        }
        else if(status==1){
            cout<<"Edges dont connect on "<<ttcase<<endl;
            break;
        }
        else if(status==2){
            cout<<"Edges connecting or not vertical or horizontal on "<<ttcase<<endl;
            break;
        }
        else if(status==3){
            cout<<"Wrong Solution on "<<ttcase<<endl;
            break;
        }
        else{
            cout<<"done "<<ttcase<<". Got "<<ourscore<<"/"<<maxscore<<" = "<<(ourscore*(db)100.0)/maxscore<<"%"<<endl;
        }

        input.close();
        output.close();
    }
    return 0;
}