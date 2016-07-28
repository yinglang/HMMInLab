#include "HMM7Manager.h"
#include <stdlib.h>
#include <ctime>
#include <sstream>

string* random(int n, int);

int abs(int a){
    return ((a>0) ? a : (-a));
}

int main(){
    srand(time(0));
    HMM7Manager manager("text1.txt",false,-1,0.5);//hiddenCoff = 0 mean N = 1
    manager.outputHMMs("text1.hmm");
    //HMM7Manager manager;
    //manager.setHMMsFromTxt("text1.hmm");

    //manager.showHMMs();

    for(int ts = 0; ts < 30; ts++){
    int T = 30;
    int i = 0;
    int allData = 300;
    int wucha = 3;
    int* correct = new int [wucha];
    for(int i = 0; i < wucha; i++){correct[i]=0;}

    int time1 = time(0);
    while((i++) < allData){


        stringstream ss;//using for convert int to string
        int labelNumber = ((rand()%10) + 1);
        string label;
        ss << labelNumber;
        ss >> label;

        string* s = random(labelNumber, T - labelNumber);
        string testLabel = manager.findLabel(s,T);

        //cout << label << endl;
        //cout << "test " << i + 1 <<" is " << label << endl;
        //for(int i =0; i < T; i++) cout << s[i];
        //cout << endl;
        //cout << testLabel << endl;
        //cout << endl;

        for(int j = 0; j < wucha; j++)
        if(abs((testLabel[0] - label[0])) <= j){
            correct[j] ++;


        }
        delete [] s;

    }
    cout << "time is " << time(0) - time1 << endl;;
    //cout << "the rate of correct is "  << endl;
    for(int j = 0; j < wucha; j++)
        cout << "wucha " << j << " is " << ((correct[j] * 1.0) / allData)<< ",     ";
    cout << endl;

    delete[] correct;
    }
}

string* random(int numOf1, int numOf0){
    string * a  = new string[numOf0 + numOf1];
    for(int i = 0; i < (numOf0 + numOf1); i ++){
        a[i] = "0";
    }

    for(int i = 0; i < numOf1; i++){
        int pos = rand()%(numOf0 + numOf1);
        a[pos] = "1";
    }

    return a;
}
