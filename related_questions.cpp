#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;  
typedef pair<double, double> pii;


int n;  
vector<int> link1[100010];  
double childNum[100010], A[100010], f[100010], T[100010], sumOfChild[100010];  
bool ck[100010];

double dfs(int u) {  
    ck[u] = true;
    A[u] = T[u];
    int sz = link1[u].size();
    for (int i = 0; i < sz; ++i) {
        int v = link1[u][i];
        if (!ck[v]) {
            double tmp = dfs(v);
            sumOfChild[u] += tmp;
            double uNum = childNum[u];
            if (u!=0) --uNum;
            A[u] += tmp / uNum;
        }
    }
    return A[u];
}

void findRoot(int u) {  
    ck[u] = true;
    int sz = link1[u].size();
    for (int i = 0; i < sz; ++i) {
        int v = link1[u][i];
        if (!ck[v]) {
            double uNum = childNum[u];
            double vNum = childNum[v];
            double modifiedA_u = T[u];
            if (uNum > 1) {
                double sOfChildU = f[u] - T[u];
                modifiedA_u += (sOfChildU*uNum - A[v]) / (uNum - 1);
            }           
            f[v] = T[v] + (sumOfChild[v] + modifiedA_u) / vNum;
            findRoot(v);
        }
    }
}

int main() {  
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> T[i];
    }
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    int x, y;
    for (int i = 0; i < n - 1; ++i) {       
        cin >> x >> y;
        x--; y--;
        link1[x].push_back(y);
        link1[y].push_back(x);
        childNum[x] ++;
        childNum[y] ++;
    }
    dfs(0);
    f[0] = A[0];
    memset(ck, 0, sizeof ck);
    findRoot(0);
    double res = f[0];
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        if (f[i] < res) {
            res = f[i];
            pos = i;
        }
    }
    cout << pos + 1 << endl;

    return 0;
}
