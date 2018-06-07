#include<bits/stdc++.h>
using namespace std;
vector< string > ans, errors, st;
string l = "";
bool mul = false, prin = false, iff = false;
int line = 1, nxt = 0, cnt = 0;

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
void duplicate(){
    for( int i = 0; i < st.size(); i++ ){
        if(st[i].size() == 1 && st[i] != ";" && st[i] != "," &&  check( st[i][0] ) ) continue;
        if( i < st.size() - 1 ){
            if( st[i] == st[i+1] ){
                string er = "Duplicate token '"; er += st[i]; er += "' at line "; er += l;
                errors.push_back( er );
            }
        }
    }
}
void seperate(string s ){
    st.clear();
    string tmp = "";
    for( int i = 0; i < s.size(); i++ ){
        if( s[i] == ' ' ){
            if( tmp != "" )st.push_back( tmp );
            tmp = "";
        }else if( i < s.size() - 1 && check1( s[i] ) && check1(s[i+1]) ){
            if( tmp != "" ) st.push_back( tmp );
            string sa = ""; sa += s[i]; sa += s[i+1];
            st.push_back( sa );
            tmp = "";
            i++;
        }else if( check( s[i] ) ){
            if( tmp != "" ) st.push_back( tmp );
            string sa = ""; sa += s[i];
            st.push_back( sa );
            tmp = "";
        }else tmp += s[i];
    }
    if( tmp != "" )st.push_back( tmp );
    duplicate();
}

void ifelse(string s ){
    for( int i = 0; i < s.size(); i++ ){
        if( i < s.size() - 1 && s[i] == 'i' && s[i+1] == 'f' ) iff = true;
        if( i < s.size() - 3 ){
            if( s[i] == 'e' && s[i+1] == 'l' && s[i+2] == 's' && s[i+3] == 'e' ){
                if( !iff ){
                    string er = "Unmatched 'else' at line " + l ;
                    errors.push_back( er );
                }else{
                    iff = false;
                }
            }
        }
    }
}

void check_parenthesis(string s ){
    for( int i = 0; i < s.size(); i++ ){
        if( s[i] == '{' )cnt++;
        else if( s[i] == '}' ){
            if( cnt == 0 ){
                string er = "Misplaces '}' at line " + l;
                errors.push_back( er );
            }else cnt--;
        }
    }
}
void printLine(string s ){
    string tmp = "";
    if( s != "" ){
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
    }
    if( !mul && tmp != "" ) ans.push_back( tmp );

    string tot = "";
    for( int i = nxt; i < ans.size(); i++ ){
        tot += ans[i]; tot += " ";
    }
    seperate( tot );

    cout << line++ << " ";
    for( int i = nxt; i < ans.size(); i++ ){
        if( ans[i] != "" )cout << ans[i] << " ";
    }cout << "\n";
    nxt = ans.size();
}
void convo( int x ){
    int num = x;
    l = "";
    while( num > 0 ){
        l += char(num%10+'0');
        num /= 10;
    }
    reverse( l.begin(), l.end() );
}

int main ( ){
    freopen("in.txt","r",stdin );
    freopen("out.txt","w",stdout );

    string s;
    cout << "Printing code with line Number: \n";
    while( getline( cin, s ) ){
        convo(line);
        check_parenthesis( s );
        printLine(s);
        ifelse(s);
    }
    cout << "\n\nErrors:\n";

    for( int i = 0; i < errors.size(); i++ ){
        cout << errors[i] << "\n";
    }
    if( cnt != 0 ){
        cout << "Unbalances parenthesis at line " << line - 1 << "\n";
    }
    return 0;
}
