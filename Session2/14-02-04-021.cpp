#include<bits/stdc++.h>
using namespace std;
#define pb push_back
vector< string > st, ft, ans;
map< string , int > mp;
string s = "";

bool check( char c ){
    if( c == '=' ) return true;
    if( c == '+' || c == '-' || c == '*' || c == '/' ) return true;
    if( c == ';' || c == ',' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' ) return true;
    if( c == '\'' || c == '"' || c == '>' || c == '<' ) return true;
    if( c == ' ' ) return true;
    return false;
}
bool check1( char c ){
    if( c == '+' || c == '-' || c == '*' || c == '/' ) return true;
    if( c == '=' ) return true;
    if(  c == '>' || c == '<' ) return true;
    return false;
}
bool key( string tmp ){
    if( tmp == "char" || tmp == "bool" || tmp == "double" || tmp == "float" || tmp == "int" || tmp == "if" || tmp == "for" || tmp == "else") return true;
    return false;
}
bool sep( string tmp ){
    if( tmp == ";" || tmp == "," || tmp == "'" || tmp == "\"" )return true;
    return false;
}
bool oper( string tmp ){
    if( tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" )return true;
    if(  tmp == "=" || tmp == "==" || tmp == ">=" || tmp == "<=" ) return true;
    if( tmp == "+=" || tmp == "-=" || tmp == "*=" || tmp == "/=" ) return true;
    return false;
}
bool number( string tmp ){
    for( int i = 0; i < tmp.size(); i++ ){
        if( tmp[i] == '.' ) continue;
        if( tmp[i] >= '0' && tmp[i] <= '9' ) continue;
        return false;
    }
    return true;
}
bool paren( string tmp ){
    if( tmp == "(" || tmp == ")" || tmp == "[" || tmp == "]" || tmp == "{" || tmp == "}" ) return true;
    return false;
}
bool idd( string tmp ){
    if( ( tmp[0]  >= 'a' && tmp[0] <= 'z') || ( tmp[0] >= 'A' && tmp[0] <= 'Z' ) || tmp[0] != '_' ){
       for( int i = 1; i < tmp.size(); i++ ){
            if( tmp[i] >= '0' && tmp[i] <= '9' ) continue;
            if( tmp[i] >= 'a' && tmp[i] <= 'z' ) continue;
            if( tmp[i] >= 'A' && tmp[i] <= 'Z' ) continue;
            if( tmp[i] == '_' ) continue;
            return false;
       }
       return true;
    }else return false;
}
int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

    getline( cin, s );
    string tmp = "";
    for( int i = 0; i < s.size(); i++ ){
        if( s[i] == ' ' ){
            if( tmp != "" )st.pb( tmp );
            tmp = "";
        }
        else if( check( s[i] ) ){
            if( tmp != "" ) st.pb( tmp );
            string sa = "";
            sa += s[i];
            st.pb( sa );
            tmp = "";
        }else tmp += s[i];
    }
    if( tmp != "" )st.pb( tmp );
    for( int i = 0; i < st.size() - 1; i++ ){
        if( st[i].size() == 1 && st[i+1].size() == 1 ){
            if( check1( st[i][0] ) && check1( st[i+1][0] ) ){
                string p = "";
                 p += st[i][0];
                 p += st[i+1][0];
                ft.pb( p );
                i++;
            }else{
                ft.pb( st[i] );
            }
        }else ft.pb( st[i] );
    }
    ft.pb( st[st.size() - 1 ] );
    cout << "Step 1: \n";
    for( int i = 0; i < ft.size(); i++ ){
         cout << ft[i] << " ";
    }
    cout << "\n\n";
    int now = 0;
    for( int i = 0; i < ft.size(); i++ ){
        if( mp.find( ft[i] ) != mp.end() ){
            string ck = "";
            ck += "[id ";
            ck += ft[i];
            ck += "]";
            mp[ft[i]] = 1;
            ans.pb( ck );
        }else if(paren( ft[i] ) ){
            string ck = "";
            ck += "[par ";
            ck += ft[i];
            ck += "]";
            ans.pb( ck );
        }else if( key( ft[i] ) ){
            string ck = "";
            ck += "[kw ";
            ck += ft[i];
            ck += "]";
            ans.pb( ck );
            now = 1;
        }else if( sep( ft[i] ) ){
            string ck = "";
            ck += "[sep ";
            ck += ft[i];
            ck += "]";
            ans.pb( ck );
            if( ft[i] == ";" ) now = 0;
        }else if( oper( ft[i] ) ){
            string ck = "";
            ck += "[op ";
            ck += ft[i];
            ck += "]";
            ans.pb( ck );
        }else if( number( ft[i] ) ){
            string ck = "";
            ck += "[num ";
            ck += ft[i];
            ck += "]";
            ans.pb( ck );
        }else if( now == 1 && idd( ft[i] ) ){
            string ck = "";
            ck += "[id ";
            ck += ft[i];
            ck += "]";
            mp[ft[i]] = 1;
            ans.pb( ck );
        }else{
            string ck = "";
            ck += "[unkn ";
            ck += ft[i];
            ck += "]";
            ans.pb( ck );
        }
    }
    cout << "Step 2: \n";
    for( int i = 0; i < ans.size(); i++ ){
        cout << ans[i] << " ";
    }
    cout << "\n\n";
    return 0;
}
