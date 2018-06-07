#include<bits/stdc++.h>
using namespace std;

int i=0,f=0,sz;

string s;
void A() {
    if (s[i] == 'a') {
        i++;
        f=1;
    }
    else {
        f=0;
        return;
    }
    if (i < sz-1 ) A();
}
void B() {
    if (s[i] == 'b') {
        i++;
        f=1;
        return;
    }
    else {
        f=0;
        return;
    }
}
void S() {
    if (s[i] == 'b'){
        i++;
        f = 1;
        return;
    }
    else {
        A();
        if (f) { B(); return;}
    }
}

int main(){

    freopen("in1.txt","r",stdin);

    while(getline(cin,s)){
        f = 0; i = 0; sz = s.size();
        S();
        if( sz == i && f ){
            cout<<"valid\n";
        }
        else{
            cout<<"invalid\n";
        }
    }
}

