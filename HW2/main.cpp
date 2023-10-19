#include <array>
#include <cstdio>
#include <thread>
#include <unistd.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define MAX 500
#define THREADCOUNT 12

#define STEP (MAX / THREADCOUNT)

consteval std::array<int, THREADCOUNT + 1> generateThreadBoundArray() {
    std::array<int, THREADCOUNT + 1> temp;
    for (int i = 0; i < THREADCOUNT; i++)
        temp[i] = STEP * i;
    temp[THREADCOUNT] = MAX;
    return temp;
}

static constexpr const std::array<int, THREADCOUNT + 1> line{ generateThreadBoundArray() };

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication

pthread_t thread1[THREADCOUNT];
pthread_t thread2[THREADCOUNT];

void *LineAdd(void *data) {
    int startLine = *(int *)data;
    int endLine = *(((int *)data) + 1);
    for (int i = startLine; i < endLine; i++) {
        for (int j = 0; j < MAX; j++) {
            matC[i][j] = matA[i][j] + matB[i][j];
        }
    }
    pthread_exit(NULL); // exit child thread
}

inline void Addition() {
    // Addition -> matC
    for (int i = 0; i < THREADCOUNT; i++) {
        pthread_create(&thread1[i], NULL, &LineAdd, (void *)&line[i]);
    }
}

void *LineMulti(void *data) {
    int startLine = *(int *)data;
    int endLine = *(((int *)data) + 1);
    for (int i = startLine; i < endLine; i++) {
        for (int j = 0; j < MAX; j++) {
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    pthread_exit(NULL); // exit child thread
}

inline void Multiplication() {
    // Multiplication -> matD
    for (int i = 0; i < THREADCOUNT; i++) {
        pthread_create(&thread2[i], NULL, &LineMulti, (void *)&line[i]);
    }
}

inline void fastGetInput(int &value) {
    bool isNegative{ false };
    char c = std::getchar();
    if (c == '-') {
        isNegative = true;
        c = std::getchar();
    }
    do {
        // value *= 10;
        // value += c - '0';
        value = (value << 1) + (value << 3) + (c - '0');
        c = std::getchar();
    } while (c != ' ' && c != EOF);

    if (isNegative)
        value *= -1;
}

int main() {
    // get input

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            // scanf("%d", &matA[i][j]);
            fastGetInput(matA[i][j]);
        }
    }

    getchar(); // ignore newline character

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            // scanf("%d", &matB[i][j]);
            fastGetInput(matB[i][j]);
        }
    }
    Addition();
    Multiplication();

    // Waiting for join threads after compute
    for (int i = 0; i < THREADCOUNT; i++)
        pthread_join(thread1[i], NULL);
    //    calculate SUM of matC
    long long sum_C = 0;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_C += matC[i][j];
    }
    printf("%lld\n", sum_C);

    // Waiting for join threads after compute
    for (int i = 0; i < THREADCOUNT; i++)
        pthread_join(thread2[i], NULL);
    // calculate SUM of matD
    long long sum_D = 0;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_D += matD[i][j];
    }
    printf("%lld\n", sum_D);

    return 0;
}
