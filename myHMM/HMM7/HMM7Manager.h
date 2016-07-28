#ifndef HMM7MANAGER_H
#define HMM7MANAGER_H

#include <fstream>
#include "HMM6.h"

class HMM7Manager{
public:
    HMM6** hmm;
    int numOfLabel;

    HMM7Manager(){
        hmm = NULL;
        observe = NULL;
        hidden = NULL;
        PI = NULL;
        A = NULL;
        B = NULL;
        trainO = NULL;
        numOfLabel = 0;
        M = 0;
    }

    HMM7Manager(string txtPath,bool showTrainProcesing = false, long time_limit = -1,double hiddenCoff = 1){
        hmm = NULL;
        observe = NULL;
        hidden = NULL;
        PI = NULL;
        A = NULL;
        B = NULL;
        trainO = NULL;
        numOfLabel = 0;
        M = 0;
        initAndTrainHMMsByTxt(txtPath, showTrainProcesing,time_limit,hiddenCoff);
    }

    ~HMM7Manager(){
        deleteHMM(hmm,numOfLabel);
    }

    int getNumOfLabel(){
        return numOfLabel;
    }

    HMM6** getHMMs(){
        return hmm;
    }

    void setHMMsFromTxt(string path){
        fin.open(path);
        if(fin.fail()){cout << "open fail in getHMMsFromTxt()" << endl; return;}
        string test;
        fin >> test;
        if(test != "HMMs"){ cout << "the file in " << path << " is not hmm file"; return;}

        fin >> M;
        observe = initObserve(fin,M);

        fin >> numOfLabel;
        hmm = new HMM6*[numOfLabel];

        int N;
        string label;
        for(int i = 0; i < numOfLabel; i++){
            fin >> label >> N;
            setPIAB(N,M,B,PI,A);
            setHidden(N,hidden);
            hmm[i] = new HMM6(N,observe,M,PI,A,B,label,hidden);
            deleteData(N);
        }
        fin.close();
    }

    void initAndTrainHMMsByTxt(string txtPath, bool showTrainProcesing = false, long time_limit = -1,double hiddenCoff = 1){
        bool haveInit = ((hmm == NULL) ? false : true);
        //let the first time init have effect, not been rewrite from all start,avoid train for same data
        fin.open(txtPath);
        if(fin.fail()){cout << "open fail" << endl; return;}

        fin >> M;
        observe = initObserve(fin,M);

        fin >> numOfLabel;
        if(haveInit == false) hmm = new HMM6*[numOfLabel];
        int N;
        int K;
        string label;
        for(int i = 0; i < numOfLabel; i++){
            fin >> label >> K;
            N = hiddenCoff * getNAndTrainS(fin, K, trainO);
            if(N <= 0) N = 1;
            initPIAB(N,M,B,PI,A);

            if(haveInit == false) hmm[i] = new HMM6(N,observe,M,PI,A,B,label);

            cout << "training data for " << label << "........................."<< endl;

            hmm[i] ->train(trainO,T,K,showTrainProcesing,time_limit);

            deleteData(N);
        }
        fin.close();
    }

    void TrainHMMsByTxt(string txtPath, bool showTrainProcesing = false){
        initAndTrainHMMsByTxt(txtPath, showTrainProcesing);
    }

    string findLabel(string * o, int T, bool showProcessing = false){
        int maxI = 0;
        double maxP = 0;
        for(int i = 0; i < numOfLabel; i++){
            double P = hmm[i] -> OProbability(o,T);
            if(P > maxP){
                maxI = i;
                maxP = P;
            }
            if(showProcessing) cout << "Probability of label " << i << " is " << P << endl;
        }
        return hmm[maxI] -> label;
    }

    void outputHMMs(string path){
        ofstream fout;
        fout.open(path);
        if(fout.fail()){cout << "file open faile() in outputHMM()" << endl; return;}

        if(hmm != NULL){
            fout << "HMMs" << endl << endl;
            fout << M << endl;
            for(int i = 0; i < M; i++){
                fout << observe[i] << " " ;
            }
            fout << endl << endl << endl;

            fout << numOfLabel << endl << endl << endl;

            for(int i = 0; i < numOfLabel; i++){
                //N,observe,M,PI,A,B,label,hidden;
                fout << hmm[i] -> label <<" " << hmm[i] -> N <<endl << endl;

                for(int j = 0; j < hmm[i] -> N; j++)
                    fout << hmm[i] -> PI[j] << " ";
                fout << endl << endl;

                for(int j = 0; j < hmm[i] -> N; j++){
                    for(int k =0; k < hmm[i] -> N; k++){
                        fout << hmm[i] -> A[j][k] << " ";
                    }
                    fout << endl;
                }
                fout << endl;

                for(int j = 0; j < hmm[i] -> N; j++){
                    for(int k =0; k < hmm[i] -> M; k++){
                        fout << hmm[i] -> B[j][k] << " ";
                    }
                    fout << endl;
                }
                fout << endl;

                if(hmm[i] -> S_H != NULL){
                    for(int j =0; j < hmm[i] -> N; j++)
                      fout << hmm[i] -> S_H[j] << " ";
                }
                else fout << "NULL";
                fout << endl << endl;

                fout << endl;
            }
        }
        fout.close();
    }

    void showHMMs(){
        for(int i = 0; i < numOfLabel; i++){
            cout << "the " << i+1 << "th HMM for label " << hmm[i] -> label << endl;
            hmm[i]->showHMM();
        }
    }

private:
    ifstream fin;

    int M;
    string * observe;

    string * hidden;
    double * PI;
    double ** A;
    double ** B;

    string ** trainO;
    int * T;

    void showTrainData(int K){
        cout <<"-----------------------------------------------------" << endl;
        for(int i = 0; i < K; i++){
            cout << T[i] << endl;
            for(int j = 0; j < T[i]; j++){
                cout << trainO[i][j] << " " << endl;
            }
            cout << endl;
        }
        cout <<"-----------------------------------------------------" << endl;
    }

    void deleteData(int N){
        for(int i = 0; i < N; i++){
            delete[] A[i];
            delete[] B[i];
        }
        delete [] A;
        delete [] B;
        delete [] PI;
        if(hidden != NULL) delete[] hidden;
    }

    void deleteHMM(HMM6** hmm, int numOfLabel){
        for(int i = 0; i < numOfLabel; i++){
            delete hmm[i];
        }
        delete[] hmm;
    }

    //below is cut from dataget.h
    string* initObserve(ifstream& fin, int m){
        string* observe = new string[m];
        for(int i = 0; i < m; i++){
            fin >> observe[i];
        }
        return observe;
    }

    int getNAndTrainS(ifstream& fin,int K, string**& o){
        int t_N = 0;
        o = new string*[K];
        T = new int[K];
        for(int k = 0; k < K; k++){
            fin >> T[k];
            t_N += T[k];
            o[k] = new string[T[k]];
            for(int t = 0; t < T[k]; t++){
                fin >> o[k][t];
            }
        }

        return t_N / K;
    }

    void initPIAB(int n, int m,double**& b, double*& PI,double**& a,int maxTransite = 2){
        //init PI
        PI = new double[n];
        for(int i = 1; i < n; i++){
            PI[i] = 0;
        }
        PI[0] = 1;

        //inti A
        a = new double*[n];
        for(int i = 0; i < n; i++){
            a[i] = new double[n];
            for(int j = 0; j < i; j++){
                a[i][j] = 0;
            }
            for(int j = i; j < i + maxTransite + 1 && j < n; j++)
                a[i][j] = 1.0 / (maxTransite + 1);
            for(int j = i + maxTransite + 1; j < n; j++){
                a[i][j] = 0;
            }
        }

        //init B
        b = new double*[n];
        for(int i = 0; i < n; i ++){
            b[i] = new double [m];
            for(int j = 0; j < m - 1; j++){
                b[i][j] = 1.0/m;
            }
            b[i][m-1] = 1.0 - (1.0 / m)*(m - 1);
        }
    }

    void setHidden(int n, string* & hidden){
            //init hidden level name string
        string test;
        fin >> test;
        if(test == "NULL") return;
        hidden = new string[n];
        hidden[0] = test;
        for(int i = 1; i < n; i ++){
            fin >> hidden[i];
        }
    }

     void setPIAB(int n, int m,double**& b, double*& PI,double**& a){
         //init PI
        PI = new double[n];
        for(int i = 0; i < n; i++){
            fin >> PI[i];
        }

        //inti A
        a = new double*[n];
        for(int i = 0; i < n; i++){
            a[i] = new double[n];
            for(int j = 0; j < n; j++){
                fin >> a[i][j];
            }
        }

        //init B
        b = new double*[n];
        for(int i = 0; i < n; i ++){
            b[i] = new double [m];
            for(int j = 0; j < m; j++){
                fin >> b[i][j];
            }
        }
    }
};
#endif // HMM7MANAGER_H
