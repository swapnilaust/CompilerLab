#include<bits/stdc++.h>
using namespace std;
vector< string > ans;

int main ( ){
    freopen("in.txt","r",stdin );
    freopen("out.txt","w",stdout );

    string s, tmp ;

    bool mul = false, prin = false;


    while( getline( cin, s ) ){
        string tmp = "";
        cout << s << "\n";
        if( s == "" )continue;

        for( int i = 0; i < s.size(); i++ ){
            if( i + 1 < s.size() && s[i] == '/' && s[i+1] == '*' ){ i++; mul = true; ans.push_back( tmp ) ; tmp = "";continue; }
            if( i + 1 < s.size() && s[i] == '*' && s[i+1] == '/' ) { i++; mul = false; tmp = ""; continue; }
            if( s[i] == '"' && !prin ){ tmp += s[i]; prin = true; continue; }
            if( s[i] == '"' && prin ){ tmp += s[i]; prin = false; continue; }
            if( prin ){ tmp += s[i]; continue; }

            if( !mul ){
                if( i + 1 < s.size() && s[i] == '/' && s[i+1] == '/' ){
                    if( tmp != "" ) ans.push_back( tmp );
                    tmp = "";
                    break;
                }
                if( s[i] == ' ' && tmp == "" ) continue;
                if( s[i] == ' ' ){
                    if( tmp != "" ) ans.push_back( tmp );
                    tmp = "";
                }else{
                    tmp += s[i];
                }
            }

        }
        if( !mul && tmp != "" ) ans.push_back( tmp );
    }
    for( int i = 0; i < ans.size(); i++ ){
        cerr << ans[i] << " ";
        cout << ans[i] << " ";

    }



}
