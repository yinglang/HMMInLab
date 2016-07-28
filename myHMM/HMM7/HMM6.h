#ifndef HMM6_H
#define HMM6_H

#include <iostream>
#include <stdlib.h>
#include <map>
#include <limits>
using namespace std;
#define Max_Long (numeric_limits<long>::max)()

class HMM6{
public:
    int N;
    int M;
    double  * PI;
    double ** A;
    double ** B;

    string label;

    map<string,int> H;
    map<string,int> O;
    string* S_H;
    string* S_O;

    double *** FP;//FP[k][t][Ht] represent for Kth data ,when using froward Argrithm for Ot output by Ht and the O0,O1...Ot have given,the max exception when H0¡¢H1..Ht_1 is x(WeiZhiShu)
    double *** BP;
    double **** S;//S[k][t_1][Ht_1][Ht] represent for Kth data, when Ot_1 output by Ht_1 and Ot output by Ht and the output is O given, the max exception
    double *** Y;//Y[k][t][Ht] represent for Kth data, when Ot output by Ht and the output is O given, the max exception
    double* P_O;//P_O[k] when output is O , the exception for Kth data.

    double *maxPI;// using when training
    double **maxA;
    double **maxB;

    HMM6(int n, string * observe, int m, double *pi, double ** a, double ** b, string label = "",string* hidden = NULL){
        initHMM(n,observe,m,pi,a,b,label,hidden);
    }

    void initHMM(int n, string * observe, int m, double *pi, double ** a, double ** b, string label = "",string* hidden = NULL){
        this -> label = label;
        N = n;
        M = m;

        S_O = new string [M];
        S_H = NULL;
        if(hidden != NULL){
            S_H = new string [N];
            for(int i = 0; i < n; i ++) {
                H[hidden[i]] = i;
                S_H[i] = hidden[i];
            }
        }

        for(int i = 0; i < m; i ++){
            O[observe[i]] = i;
            S_O[i] = observe[i];
        }

        PI = (double*) malloc ( sizeof(double) * n);
        for(int i = 0; i < n; i ++) PI[i] = pi[i];

        A = (double**)malloc(sizeof(double*) * n);
        B = (double**)malloc(sizeof(double*) * n);
        for(int i =0; i < n; i ++){
            B[i] = (double*) malloc(sizeof(double) * m);
            for(int j =0; j < m; j++){
                B[i][j] = b[i][j];
            }

            A[i] = (double*) malloc(sizeof(double) * n);
            for(int j = 0; j < n; j++){
                A[i][j] = a[i][j];
            }
        }
    }

    void showHMM(){
        cout << "------------------------------------------------------------------" << endl;
        cout << "the HMM is : " << endl;
        cout << "N : " << N <<endl;
        cout << "M : " << M << endl;
        cout << "PI : " << endl;
        cout << "[ ";
        for(int i = 0; i < N; i ++){
            cout << PI[i] << ", ";
        }
        cout << "]" << endl;

        cout << "A(convert matrix) : \n[ ";
        for(int j = 0; j < N; j++) cout << A[0][j] << ", ";
        cout <<endl;

        for(int i = 1; i < N; i ++){
            cout << "  ";
            for(int j = 0; j < N; j++){
                cout << A[i][j] << ", ";
            }
            if(i == N-1) cout << "]" << endl;
            cout << endl;
        }

        cout << "B(mixture matrix) : \n[ ";
        for(int i = 0; i < M; i ++) cout << B[0][i] << ", ";
        cout << endl;
        for(int i = 1; i < N; i++){
                cout << "  ";
            for(int j =0; j < M; j++){
                cout << B[i][j] << ", ";
            }
            if(i == N-1) cout << "]" << endl;
            cout << endl;
        }

        cout << "string name of Hidden state : \n[ ";
        if(S_H != NULL){
            for(int i = 0; i < N; i++){
                cout << S_H[i] << ", ";
            }
        }
        cout << "\b]" << endl;

        cout << "string name of Observe state : \n[ ";
        for(int i = 0; i < M; i++){
            cout << S_O[i] << ", ";
        }
        cout << "]" << endl;
        cout << "------------------------------------------------------------------" << endl;
    }

     void assumeHMM(){
        double sumPI = 0;
        double * sumA = new double[N];
        double * sumB = new double[N];
        for(int i =0; i < N; i++){
            sumPI += PI[i];
            sumA[i] = 0;
            sumB[i] = 0;
            for(int j = 0; j < N; j++){
                sumA[i] += A[i][j];
            }
            for(int j = 0; j < M; j++){
                sumB[i] += B[i][j];
            }
        }

        cout << "------------------------------------------------------"<< endl;
        cout << "assumeHMM" <<endl;
        cout << "the sum of PI is : " << sumPI << endl;
        cout << "the sum of Ai is : " << endl;
        for(int i = 0; i < N; i++)
            cout << sumA[i] << endl;
        cout << "the sum of Bi is : " << endl;
        for(int i = 0; i < N; i++)
            cout << sumB[i] << endl;
        cout << "------------------------------------------------------"<< endl;
    }

    ~HMM6(){
        deleteHMM();
        if(S_H != NULL) delete[] S_H;
        delete[] S_O;
    }

    void deleteHMM(){
        delete[] PI;
        for(int i = 0 ; i < N; i++){
            delete[] A[i];
            delete[] B[i];
        }
        delete[] A;
        delete[] B;
    }

    string getStr(int index,char type){
        if(type == 'O' || type == 'o'){
            return S_O[index];
        }
        else return S_H[index];
    }

    string* IndexToStr(int* index, int T, char type){
        string* s = new string[T];
        if(type == 'O' || type == 'o'){
            for(int i = 0; i < T; i++){
                s[i] = S_O[index[i]];
            }
        }
        else{
            for(int i = 0; i < T; i++){
                s[i] = S_H[index[i]];
            }
        }
        return s;
    }

    double HOProbability(string* o, int T, string *h){
        int H0 = H[h[0]];
        int O0 = O[o[0]];
        double p = PI[H0] * B[H0][O0];
        int Ht_1 = H0;
        for(int t = 1; t < T; t++){
            int Ht = H[h[t]];
            int Ot = O[o[t]];
            p *= A[Ht_1][Ht] * B[Ht][Ot];
            Ht_1 = Ht;
        }
        return p;
    }

    double OProbability(string * s, int T){
        double ** temp;
        double P = FPkinit(s,T,temp);
        for(int i = 0; i < T; i++) delete[] temp[i];
        delete[] temp;
        return P;
    }

    double FPkinit(string * s ,int T, double ** &FPk){
        FPk = (double**) malloc (sizeof(double*) * T);
        for(int  t = 0; t < T; t++) FPk[t] = (double*) malloc( sizeof(double) * N);
        for(int H0 = 0; H0 < N; H0 ++) {
            int O0 = O[s[0]];
            FPk[0][H0] = (PI[H0] * B[H0][O0]);
        }

        for(int t = 1; t < T; t ++){
            for(int Ht = 0; Ht < N; Ht ++){
                FPk[t][Ht] = 0;
                for(int Ht_1 = 0; Ht_1 < N; Ht_1++){
                    int Ot = O[s[t]];
                    FPk[t][Ht] += FPk[t - 1][Ht_1] * A[Ht_1][Ht] * B[Ht][Ot];
                }
            }
        }
        double p = 0;
        for(int i = 0; i < N; i++){
            p += FPk[T-1][i];
        }
        return p;
    }

    double BPkinit(string * s ,int T, double**& BPk){
        BPk = (double**) malloc (sizeof(double*) * T);
        for(int  t = 0; t < T; t++) BPk[t] = (double*) malloc( sizeof(double) * N);
        for(int H0 = 0; H0 < N; H0 ++){
            BPk[T-1][H0] = 1;
        }

        for(int t = T - 1; t > 0; t--){
            for(int Ht_1 = 0; Ht_1 < N; Ht_1 ++){
                BPk[t-1][Ht_1] = 0;

                for(int Ht = 0; Ht < N; Ht++){
                    int Ot = O[s[t]];
                    BPk[t-1][Ht_1] += BPk[t][Ht] * A[Ht_1][Ht] * B[Ht][Ot];
                }
            }
        }
        double p = 0;
        int O0 = O[s[0]];
        for(int i = 0; i < N; i++){
            p += PI[i] * B[i][O0] * BPk[0][i];
        }
        return p;
    }

    double FPAndBPinit(string ** o, int* T, int K){
        FP = new double**[K];
        BP = new double**[K];
        P_O = new double [K];

        double P = 1;
        for(int k = 0; k < K; k++){
            P_O[k] = FPkinit(o[k],T[k],FP[k]);
            P *= P_O[k];
            BPkinit(o[k],T[k],BP[k]);
        }
        return P;
    }

private:
    void SYkinit(string *o, int T,int k, double P_Ok){
        for(int t_1 = 0; t_1 < T - 1; t_1 ++){
            for(int Ht_1 = 0; Ht_1 < N; Ht_1 ++){
                //init Sk[t_1][Ht_1][*]
                for(int Ht = 0; Ht < N; Ht ++){
                    int Ot = O[o[t_1]];
                    S[k][t_1][Ht_1][Ht] = FP[k][t_1][Ht_1] * A[Ht_1][Ht] * B[Ht][Ot] * BP[k][t_1 + 1][Ht];
                    S[k][t_1][Ht_1][Ht] /= P_Ok;
                }
                //init Y[t_1][Ht_1] must after init S[t_1][Ht_1][*]
                Y[k][t_1][Ht_1] = 0;
                for(int Ht = 0; Ht < N; Ht ++){
                    Y[k][t_1][Ht_1] += S[k][t_1][Ht_1][Ht];
                }
            }//Ht_1
        }//t_1

        for(int HT_1 = 0; HT_1 < N; HT_1++){
            Y[k][T-1][HT_1] = FP[k][T-1][HT_1];
        }
    }

    bool SYinit(string ** o, int * T, int K){
        S = new double***[K];
        Y = new double**[K];
        for(int k = 0; k < K; k++){

            if(T[k] < 2) {
                cout << "the length of  O sequvence must longer than 2" << endl;
                return 0;
            }

            S[k] = new double**[T[k]];
            Y[k] = new double*[T[k]];

            for(int t = 0; t < T[k]; t++){
                S[k][t] = new double*[N];
                Y[k][t] = new double[N];
                for(int Ht = 0; Ht < N; Ht++)
                    S[k][t][Ht] = new double[N];
            }
        }


        for(int k = 0; k < K; k++){
            SYkinit(o[k],T[k],k,P_O[k]);
        }

        return 1;
    }

    void reEmstimation(string ** o, int* T, int K, bool refreshMax){
        if(refreshMax){
            //store the max HMM before reesmatition
            maxA = A;
            maxB = B;
            maxPI = PI;
            PI = new double[N];
            A = new double*[N];
            B = new double*[N];
            for(int i = 0; i < N; i++){
                A[i] = new double[N];
                B[i] = new double[M];
            }
        }

        //reemtimation PI[]
        double sumY0 = 0;
        for(int k = 0; k < K; k++){
            for(int H0 = 0; H0 < N; H0++){
                sumY0 += Y[k][0][H0];
            }
        }

        for(int H0 = 0; H0 < N; H0++){
            double sumY0H0 = 0;
            for(int k = 0; k < K; k++){
                sumY0H0 += Y[k][0][H0];
            }
            PI[H0] = sumY0H0/sumY0;
        }

        //reemastimation A[][]
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j ++){
                double sumY = 0;
                double sumS = 0;
                for(int k = 0; k < K; k++){
                    double sumYk = 0;
                    double sumSk = 0;
                    for(int t  =0; t < T[k]-1; t++){
                        sumYk += Y[k][t][i];
                        sumSk += S[k][t][i][j];
                    }
                    sumYk /= P_O[k];
                    sumSk /= P_O[k];

                    sumY += sumYk;
                    sumS += sumSk;
                }
                A[i][j] = sumS / sumY;
            }
        }

        //reemastimation B[][]
        for(int j = 0; j < N; j++){
            for(int i = 0; i < M; i++){
                double sumOi = 0;
                double sumY = 0;

                for(int k = 0; k < K; k++){
                    double sumOik = 0;
                    double sumYk = 0;
                    for(int t  = 0; t < T[k]; t++){
                        sumYk += Y[k][t][j];
                        int Ot = O[o[k][t]];
                        if(Ot == i){
                            sumOik += Y[k][t][j];
                        }
                    }

                    sumOik /= P_O[k];
                    sumYk /= P_O[k];

                    sumOi += sumOik;
                    sumY += sumYk;
                }
                B[j][i] = sumOi / sumY;
            }
        }
    }

public:
    void train(string ** o, int* T, int K, bool showProcess = true, long time_limit = -1){
        cout << "-----------------------------------------------------" << endl;
        long i = 0;
        double MaxP = 0;
        double Maxi = 0;
        double P = FPAndBPinit(o, T, K);
        if(showProcess == true) cout <<"train " << i << ",    II(Pk(O|HMM)) is : " << P << endl;
        i++;
        do{
            if(!SYinit(o,T,K)) return;
            reEmstimation(o, T, K, (MaxP < P));
            if(MaxP < P) {
                MaxP = P;
                Maxi = i - 1;
            }
            P = FPAndBPinit(o, T, K);
            if(showProcess == true) cout <<"train " << i << ",    II(Pk(O|HMM)) is : " << P << endl;
            i++;
        }while((time_limit == -1 && MaxP < P) || (time_limit != -1 && i < time_limit));

        deleteHMM();
        A = maxA;
        B = maxB;
        PI = maxPI;

        cout << "the max II(Pk(O|HMM)) is : " << MaxP << "  in train " << Maxi << endl;
        cout << "-----------------------------------------------------" << endl;
    }
};

#endif // HMM6
