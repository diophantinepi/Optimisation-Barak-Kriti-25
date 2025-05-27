// You have come a long way warrior
// Come rest with us
//
//    /\_/\       /\      (\__/)    A__A
//   ( ˶•o•)     /  \     (•ω• )   (•⤙• )
// ଘ(ა    )     /_/\_\     (ა  ૮)｡  (    )੭
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

using ll = long long;
using db = long double;
using str = string;
using pi = pair<int,int>;
using pll = pair<ll,ll>;
using ppi = pair<int,pair<int,int> >;
#define mp make_pair
#define pb push_back
#define f(i,a,b) for(ll i=a;i<b;i++)
#define fe(i,a,b) for(ll i=a;i<=b;i++)
#define ff(i,a,b) for(ll i=b-1;i>=a;i--)
#define each(a,x) for(auto& a: x)
#define rall(x) x.rbegin(),x.rend()
#define all(x) x.begin(),x.end()
#define PYES cout<<"YES"<<endl
#define PNO cout<<"NO"<<endl
#define PYes cout<<"Yes"<<endl
#define PNo cout<<"No"<<endl

template<class T> using V = vector<T>;
template<class T, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vvi = V<vi>;
using vll = V<ll>;
using vvll = V<vll>;
using vb = V<bool>;
using vvb = V<vb>;
using vpi = V<pi>;
using vpll = V<pll>;

mt19937 rng(time(nullptr));
const db onesecond = 2000000000;
#ifdef LOCAL
#include "D:/CPP Journey/imp/debug.h"
#else
#define debug(...) 42
#endif

ll BruteForceSurplus = 0;

struct pt {
    ll x, y;
    pt() {}
    pt(ll _x, ll _y) : x(_x), y(_y) {}
    pt operator-(const pt& p) const { return pt(x-p.x, y-p.y); }
    bool operator==(const pt& p) const { return x==p.x && y==p.y; }
    ll cross(const pt& p) const { return x*p.y - y*p.x; }
    ll cross(const pt& a, const pt& b) const { return (a-*this).cross(b-*this); }
};

inline int hashformap(const pt& a) {
    return int(a.x)*10001 + int(a.y);
}

// custom comparators
// x ascending, then y descending
bool cmpByXThenYDesc(const pair<int,pt>& A, const pair<int,pt>& B) {
    if (A.second.x != B.second.x) return A.second.x < B.second.x;
    return A.second.y > B.second.y;
}
// y ascending, then x descending
bool cmpByYThenXDesc(const pair<int,pt>& A, const pair<int,pt>& B) {
    if (A.second.y != B.second.y) return A.second.y < B.second.y;
    return A.second.x > B.second.x;
}
// value descending, then x ascending, then y descending
bool cmpByValueThenXThenY(const pair<int,pt>& A, const pair<int,pt>& B) {
    if (A.first != B.first) return A.first > B.first;
    if (A.second.x != B.second.x) return A.second.x < B.second.x;
    return A.second.y > B.second.y;
}

void print_ans(ofstream& output, pair<ll,V<pt> > ans) {
    output << ans.first << endl;
    int edges = ans.second.size();
    output << edges << ", " << edges << endl;
    f(i,0,edges-1) {
        output << "(" << ans.second[i].x/4.0 << ", " << ans.second[i].y/4.0 << "), ("
               << ans.second[i+1].x/4.0 << ", " << ans.second[i+1].y/4.0 << ")" << endl;
    }
    output << "(" << ans.second[edges-1].x/4.0 << ", " << ans.second[edges-1].y/4.0 << "), ("
           << ans.second[0].x/4.0 << ", " << ans.second[0].y/4.0 << ")" << endl;
}

pair<ll,V<pt> > BruteForce(V<pair<int,pt> >& crystals, int ncrystals, map<int,int> isLast) {
    V<pt> points;
    ll ans = 0;
    V<pair<int,pt> > selectedcryst(min(166, ncrystals));
    f(i,0,min(166,ncrystals)) {
        selectedcryst[i] = crystals[i];
        ans += crystals[i].first;
        if (isLast[hashformap(crystals[i].second)]) BruteForceSurplus += 2;
    }
    sort(selectedcryst.begin(), selectedcryst.end(), cmpByXThenYDesc);
    points.pb(pt(selectedcryst[0].second.x-2,1));
    points.pb(pt(selectedcryst[0].second.x-2,selectedcryst[0].second.y+1));
    points.pb(pt(selectedcryst[0].second.x+1,selectedcryst[0].second.y+1));
    points.pb(pt(selectedcryst[0].second.x+1,selectedcryst[0].second.y-1));
    points.pb(pt(selectedcryst[0].second.x-1,selectedcryst[0].second.y-1));
    f(i,1,min(166,ncrystals)) {
        if (selectedcryst[i].second.x == selectedcryst[i-1].second.x) {
            points.pb(pt(selectedcryst[i].second.x-1,selectedcryst[i].second.y+1));
            points.pb(pt(selectedcryst[i].second.x+1,selectedcryst[i].second.y+1));
            points.pb(pt(selectedcryst[i].second.x+1,selectedcryst[i].second.y-1));
            points.pb(pt(selectedcryst[i].second.x-1,selectedcryst[i].second.y-1));
        } else {
            points.pb(pt(selectedcryst[i-1].second.x-1,1));
            points.pb(pt(selectedcryst[i].second.x-2,1));
            points.pb(pt(selectedcryst[i].second.x-2,selectedcryst[i].second.y+1));
            points.pb(pt(selectedcryst[i].second.x+1,selectedcryst[i].second.y+1));
            points.pb(pt(selectedcryst[i].second.x+1,selectedcryst[i].second.y-1));
            points.pb(pt(selectedcryst[i].second.x-1,selectedcryst[i].second.y-1));
        }
    }
    points.pb(pt(selectedcryst[min(166,ncrystals)-1].second.x-1,1));
    return mp(ans, points);
}

pair<ll,V<pt> > PipelineOptimized(V<pair<int,pt> >& crystals, int ncrystals, map<int,db> rankmap, map<int,int> isLast) {
    V<pt> points;
    bool cond = false;
    ll ans = 0, last = 0, startIdx = 0;
    f(i,0,ncrystals) {
        if (rankmap[hashformap(crystals[i].second)] <= 166 + BruteForceSurplus/6) {
            ans += crystals[i].first;
            last = crystals[i].second.x;
            points.pb(pt(crystals[i].second.x-2,1));
            points.pb(pt(crystals[i].second.x-2,crystals[i].second.y+1));
            points.pb(pt(crystals[i].second.x+1,crystals[i].second.y+1));
            if (isLast[hashformap(crystals[i].second)]) {
                cond = true;
                if (rankmap[hashformap(crystals[i].second)] > 166) BruteForceSurplus += 2;
            } else {
                points.pb(pt(crystals[i].second.x+1,crystals[i].second.y-1));
                points.pb(pt(crystals[i].second.x-1,crystals[i].second.y-1));
            }
            startIdx = i;
            break;
        }
    }
    f(i,startIdx+1,ncrystals) {
        if (rankmap[hashformap(crystals[i].second)] <= 166 + BruteForceSurplus/6) {
            ans += crystals[i].first;
            if (crystals[i].second.x == last) {
                points.pb(pt(crystals[i].second.x-1,crystals[i].second.y+1));
                points.pb(pt(crystals[i].second.x+1,crystals[i].second.y+1));
                if (isLast[hashformap(crystals[i].second)]) {
                    cond = true;
                    if (rankmap[hashformap(crystals[i].second)] > 166) BruteForceSurplus += 2;
                } else {
                    points.pb(pt(crystals[i].second.x+1,crystals[i].second.y-1));
                    points.pb(pt(crystals[i].second.x-1,crystals[i].second.y-1));
                }
            } else {
                if (cond) {
                    points.pb(pt(last+1,1)); cond = false;
                } else points.pb(pt(last-1,1));
                points.pb(pt(crystals[i].second.x-2,1));
                points.pb(pt(crystals[i].second.x-2,crystals[i].second.y+1));
                points.pb(pt(crystals[i].second.x+1,crystals[i].second.y+1));
                if (isLast[hashformap(crystals[i].second)]) {
                    cond = true;
                    if (rankmap[hashformap(crystals[i].second)] > 166) BruteForceSurplus += 2;
                } else {
                    points.pb(pt(crystals[i].second.x+1,crystals[i].second.y-1));
                    points.pb(pt(crystals[i].second.x-1,crystals[i].second.y-1));
                }
            }
            last = crystals[i].second.x;
        }
    }
    if (cond) points.pb(pt(last+1,1)); else points.pb(pt(last-1,1));
    return mp(ans, points);
}

pair<ll,V<pt> > BruteForceRect(V<pair<int,pt> >& allPoints, int MAX_CAND) {
    V<pt> points(4);
    ll ans = 0;
    V<ll> candX, candY;
    for (auto p: allPoints) {
        if (p.first < 0) continue;
        candX.pb(p.second.x);
        candY.pb(p.second.y);
    }
    sort(candY.begin(), candY.end());
    candX.erase(unique(candX.begin(), candX.end()), candX.end());
    candY.erase(unique(candY.begin(), candY.end()), candY.end());
    vvll pre(4001, vll(4001,0));
    for (auto i: allPoints) {
        pre[i.second.x%4000+1][i.second.y%4000+1] += i.first;
    }
    fe(i,1,4000) fe(j,1,4000)
        pre[i][j] += pre[i][j-1] + pre[i-1][j] - pre[i-1][j-1];
    if ((int)candX.size() > MAX_CAND) {
        V<ll> newCand;
        int step = candX.size()/MAX_CAND;
        for (int i=0; i<(int)candX.size(); i+=step) newCand.pb(candX[i]);
        if (newCand.back() != candX.back()) newCand.pb(candX.back());
        candX = newCand;
    }
    if ((int)candY.size() > MAX_CAND) {
        V<ll> newCand;
        int step = candY.size()/MAX_CAND;
        for (int i=0; i<(int)candY.size(); i+=step) newCand.pb(candY[i]);
        if (newCand.back() != candY.back()) newCand.pb(candY.back());
        candY = newCand;
    }
    ll bestL=2, bestR=3, bestB=2, bestT=3;
    for (int x1=0; x1<(int)candX.size(); x1++)
     for (int x2=x1+1; x2<(int)candX.size(); x2++)
      for (int y1=0; y1<(int)candY.size(); y1++)
       for (int y2=y1+1; y2<(int)candY.size(); y2++) {
        ll L=candX[x1], R=candX[x2], B=candY[y1], T=candY[y2];
        ll currans = pre[(R%4000)+1][(T%4000)+1]
                     - pre[L%4000][(T%4000)+1]
                     - pre[(R%4000)+1][B%4000]
                     + pre[L%4000][B%4000];
        if (currans>ans) { ans=currans; bestL=L; bestR=R; bestB=B; bestT=T; }
    }
    bestR++; bestT++; bestB--; bestL--;
    points[0]=pt(bestL,bestB);
    points[1]=pt(bestR,bestB);
    points[2]=pt(bestR,bestT);
    points[3]=pt(bestL,bestT);
    return mp(ans, points);
}

pair<ll,V<pt> > DivideAndConquer(V<pair<int,pt> >& allPoints, int MAX_CAND) {
    V<pt> points;
    ll ans = 0;
    vector<vector<vector<pair<int,pt> > > > Field(10, vector<vector<pair<int,pt> > >(10));
    for (auto p: allPoints) {
        if (p.second.x==40000 || p.second.y==40000) continue;
        Field[p.second.x/4000][p.second.y/4000].pb(p);
    }
    points.pb(pt(1,1));
    f(iy,0,10) {
        points.pb(pt(40000,4000*iy+1));
        points.pb(pt(40000,4000*iy+2));
        ff(ix,0,10) {
            auto currRect = BruteForceRect(Field[ix][iy], MAX_CAND);
            ans += currRect.first;
            ll L=currRect.second[0].x, R=currRect.second[1].x;
            ll B=currRect.second[0].y, T=currRect.second[2].y;
            if (currRect.first==0) continue;
            R++;
            points.pb(pt(R,4000*iy+2));
            points.pb(pt(R,T));
            points.pb(pt(L,T));
            points.pb(pt(L,B));
            R--;
            points.pb(pt(R,B));
            points.pb(pt(R,4000*iy+2));
        }
        if (iy!=9) {
            points.pb(pt(2,4000*iy+2));
            points.pb(pt(2,4000*(iy+1)+1));
        } else {
            points.pb(pt(1,36000+2));
        }
    }
    return mp(ans, points);
}

void solve(ifstream& input, ofstream& output) {
    int ncrystals, nmines;
    input >> ncrystals;
    V<pair<int,pt> > crystals(ncrystals);
    f(i,0,ncrystals) {
        input >> crystals[i].second.x >> crystals[i].second.y >> crystals[i].first;
        crystals[i].second.x *= 4;
        crystals[i].second.y *= 4;
    }
    input >> nmines;
    V<pair<int,pt> > mines(nmines);
    f(i,0,nmines) {
        input >> mines[i].second.x >> mines[i].second.y >> mines[i].first;
        mines[i].second.x *= 4;
        mines[i].second.y *= 4;
    }
    // initial sorting & dedup by coordinate
    sort(crystals.begin(), crystals.end(), cmpByXThenYDesc);
    sort(mines.begin(), mines.end(), cmpByXThenYDesc);
    ff(i,1,ncrystals) if (crystals[i].second==crystals[i-1].second) {
        crystals[i-1].first += crystals[i].first;
        swap(crystals[i], crystals[ncrystals-1]); ncrystals--;
    }
    ff(i,1,nmines) if (mines[i].second==mines[i-1].second) {
        mines[i-1].first += mines[i].first;
        swap(mines[i], mines[nmines-1]); nmines--;
    }
    ff(i,0,ncrystals) ff(j,0,nmines) if (crystals[i].second==mines[j].second) {
        if (crystals[i].first == mines[j].first) {
            swap(crystals[i], crystals[ncrystals-1]); ncrystals--;
            swap(mines[j], mines[nmines-1]); nmines--;
        } else if (crystals[i].first > mines[j].first) {
            crystals[i].first -= mines[j].first;
            swap(mines[j], mines[nmines-1]); nmines--;
        } else {
            mines[j].first -= crystals[i].first;
            swap(crystals[i], crystals[ncrystals-1]); ncrystals--;
        }
    }
    crystals.resize(ncrystals);
    mines.resize(nmines);
    // sort by score
    sort(crystals.begin(), crystals.end(), cmpByValueThenXThenY);
    sort(mines.begin(), mines.end(), cmpByValueThenXThenY);
    // prepare combined lists
    V<pair<int,pt> > everything_xsorted(ncrystals+nmines), everything_ysorted(ncrystals+nmines);
    f(i,0,ncrystals) {
        everything_xsorted[i] = crystals[i];
        everything_ysorted[i] = crystals[i];
    }
    f(i,0,nmines) {
        everything_xsorted[i+ncrystals] = mines[i];
        everything_xsorted[i+ncrystals].first *= -1;
        everything_ysorted[i+ncrystals] = mines[i];
        everything_ysorted[i+ncrystals].first *= -1;
    }
    sort(everything_xsorted.begin(), everything_xsorted.end(), cmpByXThenYDesc);
    sort(everything_ysorted.begin(), everything_ysorted.end(), cmpByYThenXDesc);
    // detect last-in-column
    map<int,int> isLast;
    ff(i,0, ncrystals+nmines-1) {
        if (everything_xsorted[i].second.x != everything_xsorted[i+1].second.x)
            isLast[hashformap(everything_xsorted[i].second)] = 1;
    }
    isLast[hashformap(everything_xsorted.back().second)] = 1;
    // rank map
    map<int,db> rankmap;
    f(i,0,ncrystals) rankmap[hashformap(crystals[i].second)] = i+1;
    f(i,0,nmines)   rankmap[hashformap(mines[i].second)]    = 10000;
    // run strategies
    ll bestScore = LLONG_MIN;
    pair<ll,V<pt> > bestAns;
    BruteForceSurplus = 0;
    auto a1 = BruteForce(crystals, ncrystals, isLast);
    bestScore = a1.first; bestAns = a1;
    auto a2 = PipelineOptimized(crystals, ncrystals, rankmap, isLast);
    if (a2.first > bestScore) { bestScore = a2.first; bestAns = a2; }
    auto a3 = DivideAndConquer(everything_xsorted, 100);
    if (a3.first > bestScore) { bestScore = a3.first; bestAns = a3; }
    print_ans(output, bestAns);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l,r;
    cout<<"Range of Outputs to Solve:"<<endl;
    cin>>l>>r;
    for(int tt=l; tt<=r; tt++){
        char inbuf[32], outbuf[32];
        sprintf(inbuf,  "input%02d.txt",  tt);
        sprintf(outbuf, "78_optimization_output%02d.txt", tt);
        ifstream input(inbuf);
        ofstream output(outbuf);
        if(!input.is_open()||!output.is_open()){
            cerr<<"Failed to open files for case "<<tt<<"\n";
            continue;
        }
        auto t0 = chrono::high_resolution_clock::now();
        solve(input, output);
        auto t1 = chrono::high_resolution_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
        cout << "Time for case " << tt << ": " << ms << " ms\n";
        input.close(); output.close();
    }
    return 0;
}
