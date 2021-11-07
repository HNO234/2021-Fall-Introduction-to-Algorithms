#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    set<int> s;
    for (int i=1;i*i<=1000000000;i++) s.insert(i*i);

    for (int i=1;i<=t;i++){
	    int a=inf.readInt(0,1000000000,"a_"+to_string(i));
        inf.readSpace();
        int b=inf.readInt(0,1000000000,"b_"+to_string(i));
        inf.readSpace();
        int c=inf.readInt(2,1000000000,"c_"+to_string(i));
        inf.readSpace();
        int k=inf.readInt(1,1000000000,"k_"+to_string(i));

        ensuref(s.find(c)==s.end(),"c is a perfect square");

        inf.readEoln();
    }
    inf.readEof();
}
