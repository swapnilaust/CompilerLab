#include<bits/stdc++.h>
#define pb push_back
#define mpp make_pair
#define PI acos(-1)
/*************NOTES*********************\
***************************************/
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair < int , int > pii;
const ll inf = 1e9;
const ll mod = 1e9 + 7;
const double eps = 1e-8;
const ll MAX = 1e7 + 20;

template< class T > T gcd(T a, T b) { return (b != 0 ? gcd<T>(b, a%b) : a); }
template< class T > T lcm(T a, T b) { return (a / gcd<T>(a, b) * b); }

/*----------------------Graph Moves----------------*/
//const int fx[]={+1,-1,+0,+0};
//const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
/*------------------------------------------------*/

inline const int EQ( double tmp ){ if( fabs( tmp ) < eps ) return 0; return tmp > eps ? 1 : -1;}
ll  BM(ll  B,ll  P,ll  M){ ll  R=1; while(P>0)  { if(P&1){ R=(R*B)%M;}P/=2;B=(B*B)%M;}return (ll )R;}
ll  MI(ll  x, ll m ){ return BM(x,m-2,m); }

/*-----------------------Bitmask------------------*/
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
//int countbit( int x ){ return __builtin_popcount( x );}
/*------------------------------------------------*/


map< string, string > mp, mp1, fs, follow;
queue < string > Q;
string ans = "", trim = "";

bool Isterminal(char ch ){
    if( ch >= 'A' && ch <= 'Z' )return false;
    return true;
}

void findFirst( string ky, string s ){
    if( Isterminal( s[0] ) ){
        ans = "{";
        ans += s[0];
        trim += s[0];
        ans += ",";
        trim += ",";
        ans += mp1[ky];
        trim += mp1[ky];
        ans += "}";
    }else{
        if( s[1] == '\'' ){
            string nxt = "";
            nxt += s[0];
            nxt += s[1];
            findFirst(nxt, mp[nxt] );
        }else{
            string nxt = "";
            nxt += s[0];
            findFirst(nxt, mp[nxt] );
        }
    }
}


void build_follow(){
    while( !Q.empty() ){
        bool done = false;
        string tp = Q.front();

        Q.pop();
        for( auto it: mp ){
            string val = it.second;
            if( it.first == tp )continue;
            if (val.find(tp) != string::npos) {//here matches
                for( int i = 0; i < val.size(); i++ ){
                    if( val[i] == tp[0]  ){
                        if( i+1 < val.size() ){
                            if( tp.size() == 1 && val[i+1] == '\'')break;
                        }

                        if( tp.size() > 1 ){//bar check
                            if( i+1 == val.size() ) break;
                            if( val[i+1] != tp[1] )break;
                            i++;
                        }

                        if( i + 1 == val.size() ){//last e ase, only follow copy hobe
                            if( follow.find( it.first ) != follow.end() ){
                                done = true;
                                follow[tp] = follow[it.first];
                                done = true;
                            }
                        }else if( i + 1 < val.size() && Isterminal(val[i+1] ) ){ // porer character terminal hoile
                            string ass  = "";
                            ass += val[i+1];
                            ass += ",$";
                            follow[tp] = ass;
                            done = true;
                        }else if( i + 1 < val.size() && !Isterminal(val[i+1] ) ){ // porer character terminal na hoile
                            string ass = "",aa = "";
                            ass += val[i+1];
                            if( i + 2 < val.size() && val[i+2] == '\'')ass += "'";
                            aa += fs[ass];
                            if( follow.find( it.first ) != follow.end() ){
                                done = true;
                                aa += follow[it.first];
                                follow[tp] = aa;
                            }
                        }
                    }
                }
            }
        }
        if( !done )Q.push( tp );
    }
}

int main ( ){

    freopen("in3.txt","r",stdin );


    string s;
    while( getline( cin, s ) ){
        string tmp = "";
        int now = 0;
        while( now < s.size() && s[now] != ' ' ){ tmp += s[now]; now++; }
        now += 3;
        string tmp1 = "";
        while( now < s.size() && s[now] != ' ' ){ tmp1 += s[now]; now++; }
        //cout << tmp << " " << tmp1 << "\n";
        mp[tmp] = tmp1;
        tmp1 = "";
        now  = s.size() - 1;
        while( now >= 0 && s[now] != ' ' ) { tmp1 += s[now]; now--; }
        bool ok = false;
        for( int i = 0; i < s.size(); i++ ) if( s[i] == '|' )ok = true;
        reverse( tmp1.begin(), tmp1.end() );
        if( ok )mp1[tmp] = tmp1;
    }

    for( auto it: mp ){
//        cout << it.first << " " << it.second << "\n";
        Q.push( it.first );
        ans = ""; trim = "";
        findFirst( it.first, it.second );
        cout << "FIRST(" << it.first << ") = " << ans << "\n";
        fs[it.first] = trim;
    }

    build_follow();
    cout << "\n\n\n";

    for( auto it: follow ){
        string tmp = "", tmp1 = it.second;
        for( int i = 0; i < tmp1.size(); i++ ){
            if( tmp1[i] != '#' )tmp += tmp1[i];
        }
        follow[it.first] = tmp;
    }
    for( auto it: follow ){
        cout << "FOLLOW(" << it.first << ") = {"<< it.second<< "}\n";
    }




    return 0;
}

