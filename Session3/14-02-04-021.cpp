#include<bits/stdc++.h>
using namespace std;
#define pb push_back
vector< string > giv, ft;
map< string, int > mp;
map< string , string > mtype;
map< string, int > cat;

string s = "" ;
int idno = 1;
bool found = false;

struct data{
    int id;
    string name,locglo, datatype, varfunc;
}arr[1000];

string trim( string tmp ){
    int now = 1;
    string ck = "";
    while( tmp[now] != ' ' ){ ck += tmp[now]; now++; }
    string ck2 = "";
    for( int i = now + 1; i < tmp.size() - 1; i++ ) ck2 += tmp[i];

    if( ck != "id" ){
        string ret = "[";
        ret += ck2;
        ret += "]";
        return ret;
    }
    return tmp;
}

int main(){
    freopen("in.txt","r",stdin );
    freopen("out.txt","w",stdout );

    getline( cin, s );
    string tmp = "";

    int now = 0;
    while( now < s.size() ){
        if( s[now] == ' ' && s[now-1] == ']' ){
            giv.pb( tmp );
            tmp = "";
        }else tmp += s[now];
        now++;
    }
    giv.pb( tmp );

    for( int i = 0; i < giv.size(); i++ ){
        ft.pb( trim( giv[i] ) );
    }

    cout << "Step 1:\n";
    for( int i = 0; i < ft.size(); i++ ){
        cout << ft[i] ;
    }
    cout << "\n\n\n";

    string function_name = "global";

    for( int i = 0; i < ft.size(); i++ ){
        string tmpp = ft[i];
        if( tmpp[1] == 'i' && tmpp[2] == 'd' ){
            string type = "var", data = "", name = "";
            int now = 0;
            while( tmpp[now] != ' ' )now++;
            for( int j = now + 1; j < tmpp.size() - 1; j++ ) name += tmpp[j];

            if( i + 1 < ft.size() ){ //forword
                string tmpp1 = ft[i+1];
                if( tmpp1[1] == '(' ){
                    function_name = "global";
                    type = "func";
                }
            }

            if( function_name == "main" )found = true;
            if( found && type == "var" )function_name = "main";

            string tmpp2 = ft[i-1];
            for( int j = 1; j < tmpp2.size() - 1; j++ )data += tmpp2[j]; // backword

            if( mtype.find( name ) == mtype.end() )mtype[name] = data;
            else data = mtype[name];

            if( mp.find( name ) == mp.end() ){
                arr[idno].id = idno;
                arr[idno].datatype = data;
                arr[idno].locglo = function_name;
                arr[idno].varfunc = type;
                arr[idno].name = name;
                mp[name] = idno;
                string nw = name+type+data+function_name;
                cat[nw] = idno;
                idno++;
            }else{
                int num = mp[name];
                if( arr[num].datatype != data || arr[num].locglo != function_name || arr[num].varfunc != type ){
                    arr[idno].id = idno;
                    arr[idno].datatype = data;
                    arr[idno].locglo = function_name;
                    arr[idno].varfunc = type;
                    arr[idno].name = name;
                    mp[name] = idno;
                    string nw = name+type+data+function_name;
                    cat[nw] = idno;
                    idno++;
                }
            }
            if( i + 1 < ft.size() ){ //forword
                string tmpp1 = ft[i+1];
                if( tmpp1[1] == '(' ){
                    function_name = name;
                    type = "func";
                }
            }
        }
    }

    cout << "Step 2:\n";

    for( int i = 1; i < idno ; i++ ){
        cout << i << " " << arr[i].name << " " << arr[i].varfunc << " " << arr[i].datatype << " " << arr[i].locglo << "\n";
    }
    cout << "\n\n\n\n";
//------------------------------------------------------------------------

    cout << "Step 3:\n";

    function_name = "global";
    found = false;
    for( int i = 0; i < ft.size(); i++ ){
       string tmpp = ft[i];
       if( tmpp[1] == 'i' && tmpp[2] == 'd' ){
            string type = "var", data = "", name = "";
            int now = 0;
            while( tmpp[now] != ' ' )now++;
            for( int j = now + 1; j < tmpp.size() - 1; j++ ) name += tmpp[j];

            if( i + 1 < ft.size() ){ //forword
                string tmpp1 = ft[i+1];
                if( tmpp1[1] == '(' ){
                    function_name = "global";
                    type = "func";
                }
            }

            if( function_name == "main" )found = true;
            if( found && type == "var" )function_name = "main";

            string tmpp2 = ft[i-1];
            for( int j = 1; j < tmpp2.size() - 1; j++ )data += tmpp2[j]; // backword

            if( mtype.find( name ) == mtype.end() ) mtype[name] = data;
            else data = mtype[name];

            string nw = name+type+data+function_name;
            cout << "[id " << cat[nw] <<  "]";

            if( i + 1 < ft.size() ){ //forword
                string tmpp1 = ft[i+1];
                if( tmpp1[1] == '(' ){
                    function_name = name;
                    type = "func";
                }
            }
       }else cout << ft[i];
    }
    cout << "\n\n\n";
    return 0;
}

