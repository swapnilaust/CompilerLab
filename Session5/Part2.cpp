#include<bits/stdc++.h>
using namespace std;
string s;
bool ok = true, last = false;
void B( int pos ){
    if( pos == s.size() - 1 ){
        last = true;
        if( s[pos] != 'd' ){
            ok = false;
            return;
        }
    }
    if( pos <= s.size() - 3 ){
        if( s[pos] == 'b' && s[pos+1] == 'b' ){
            B( pos + 2 );
        }
        if( s[pos] == 'b' && s[pos+1] == 'c' ){
            B( pos + 2 );
        }
    }else if( pos != s.size() - 1 ){
        ok = false;
        return;
    }
}
void A(int pos){
    if( s[pos] != 'a' ){
        ok = false;
        return;
    }
    B(pos+1);
}

int main( ){

    freopen("in2.txt","r", stdin );

    while( cin >> s ){
        A(0);
        if( ok && last ){
            cout << "valid\n";
        }else cout << "invalid\n";
    }


}

