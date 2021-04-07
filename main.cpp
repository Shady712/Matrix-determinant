#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>
#include <sysinfoapi.h>

using namespace std;

const float eps = 1e-6;

int n, numThreads, i, j, k;
vector<float *> array;

float getAns() {
    float ans = 1, maxElem, tmp;
    for (i = 0; i < n - 1; i++) {
        maxElem = i;
        for (j = i + 1; j < n; j++) {
            if (abs(array[j][i]) > abs(array[i][i])) {
                maxElem = j;
            }
        }
        if (maxElem != i) {
            ans = -ans;
            swap(array[i], array[maxElem]);
        }
        if (abs(array[i][i]) > eps) {
#pragma omp parallel for schedule(static) private(j, k, tmp)
            for (j = i + 1; j < n; j++) {
                tmp = array[j][i] / array[i][i];
                for (k = 0; k < n; k++) {
                    array[j][k] -= tmp * array[i][k];
                }
            }
        } else {
            return 0;
        }
    }
#pragma omp parallel for schedule(static) reduction(*:ans)
    for (i = 0; i < n; i++) {
        ans *= array[i][i];
    }
    return ans;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    {
        string s = argv[1];
        for (i = 0; i < (int) s.size(); i++) {
            numThreads = numThreads * 10 + s[i] - '0';
        }
    }
    omp_set_dynamic(0);
    omp_set_num_threads(numThreads);
    freopen(argv[2], "r", stdin);
    ofstream output;
    if (argc == 4) {
        output.open(argv[3]);
    }
    cin >> n;
    //n = 2000;
    array.resize(n);
    for (i = 0; i < n; i++) {
        array[i] = new float[n];
    }
    srand(1);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cin >> array[i][j];
            //array[i][j] = rand() % 10;
        }
    }
    float start, end, ans;
    start = GetTickCount();
    ans = getAns();
    end = GetTickCount();
    if (output.is_open()) {
        output << "Determinant: " << ans << '\n';
        output.close();
    } else {
        cout << "Determinant: " << ans << '\n';
    }
    cout << "Time: " << end - start;
}
