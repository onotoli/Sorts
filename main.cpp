#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <random>

int max(int * array, int len) {
    int m = array[0];
    for (int i = 0; i < len; i++) {
        if (array[i] > m)
            m = array[i];
    }
    return m;
}

int min(int * array, int len) {
    int m = array[0];
    for (int i = 0; i < len; i++) {
        if (array[i] < m)
            m = array[i];
    }
    return m;
}

void swap(int * array, int a, int b) {
    int c = array[a];
    array[a] = array[b];
    array[b] = c;
}

bool forward_step(int * array, int begin_idx, int end_idx, int step) {
    for (int i = begin_idx; i < end_idx - 1; i++) {
        if (array[i]  > array[i + step]) {
            swap(array, i, i + step);
            return true;
        }
    }
    return false;
}

void backward_step(int * array, int begin_idx, int end_idx, int step) {
    for (int i = end_idx - 1; i > begin_idx; i--) {
        if (array[i - step] > array[i])
            swap(array, i, i - step);
    }
}

std::vector<int> Fib(int size){
    std::vector<int> fib;
    int f1 = 1, f2 = 1;
    int f = f2;
    fib.push_back(f);
    while (size - f >= f1){
        f = f1 + f2;
        f1 = f2;
        f2 = f;
        fib.push_back(f);
        //std::cout<<f<<std::endl;
    }
    return fib;
}

void shaker_sort(int * array, int begin_idx, int end_idx) {
    for (begin_idx; begin_idx < end_idx; begin_idx++) {
        forward_step(array, begin_idx, end_idx, 1);
        backward_step(array, begin_idx, end_idx, 1);
    }
}

int comb_sort(int * array, int begin_idx, int end_idx) {
    int counter = 0;
    int n = (begin_idx - end_idx) / 2;
    while (n >= 1) {
        forward_step(array, begin_idx, end_idx, n);
        n = n / 2;
        counter++;

    }

    while (forward_step(array, begin_idx, end_idx, 1))
        counter++;

    return counter;
}

void shell_sort1(int * array, int begin_idx, int end_idx) {
    int len = end_idx - begin_idx;
    for (int step = len / 2; step > 0; step /= 2) {
        for (int i = step; i < len; i++) {
            int t = array[i];
            int j;
            for (j = i; j >= step && array[j - step] > t; j -= step)
                array[j] = array[j - step];
            array[j] = t;
        }
    }
}

void shell_sort2(int * array, int begin_idx, int end_idx) {
    int len = end_idx - begin_idx;
    int deg = (int) log2(len);
    for (; deg > 0; --deg) {
        int step = pow(2,deg)-1;
        for (int i = step; i < len; i++) {
            int t = array[i];
            int j;
            for (j = i; j >= step && array[j - step] > t; j -= step)
                array[j] = array[j - step];
            array[j] = t;
        }
    }
}

void shell_sort3(int * array, int begin_idx, int end_idx, std::vector<int> fib) {
    int len = end_idx - begin_idx;
    for (int step : fib) {
        for (int i = step; i < len; i++) {
            int t = array[i];
            int j;
            for (j = i; j >= step && array[j - step] > t; j -= step)
                array[j] = array[j - step];
            array[j] = t;
        }
    }
}

bool test_forward(int * array, int begin_idx, int end_idx) {
    bool flag = false;
    int len = end_idx - begin_idx;
    int m = max(array, len);
    int * b = new int [len];
    for (int i = 0; i < len; i++)
        b[i] = array[i];
    forward_step(b, begin_idx, end_idx, 1);
    if (b[len - 1] == m)
        flag = true;
    delete[] b;
    return flag;
}

bool test_backward(int * array, int begin_idx, int end_idx) {
    bool flag = false;
    int len = end_idx - begin_idx;
    int m = min(array, len);
    int * b = new int [len];
    for (int i = 0; i < len; i++)
        b[i] = array[i];
    backward_step(b, begin_idx, end_idx, 1);
    if (b[0] == m)
        flag = true;
    delete[] b;
    return flag;
}

bool test_shaker(int * array, int begin_idx, int end_idx) {
    bool flag = true;
    int len = end_idx - begin_idx;
    int * b = new int [len];
    for (int i = 0; i < len; i++)
        b[i] = array[i];
    shaker_sort(b, begin_idx,end_idx);
    for (int i = 0; i < len - 1; i++)
        if (b[i] > b[i + 1])
            flag = false;
    return flag;
}

int* rand_arr(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % 40;
    return arr;
}

void OUT (std::string file_name, int n, long long t){
    std::ofstream out(file_name, std::ios::app);
    if (out.is_open())
    {
        out << n << ";" << t <<std::endl;
    }
    out.close();
}


int main() {
    srand(time(nullptr));
    long long t;
    clock_t end, begin;
    begin = clock();
    for (int j = 100; j <= 5000; j = j + 100) {
        int *a = rand_arr(j);
        int n = 0;
        for (int i = 0; i < 3; ++i) {
            n = n + comb_sort(a, 0, j);
        }
        end = clock();
        t = (long long) (end - begin);
        std::cout << t << '\t' << n << '\t' << j << std::endl;
        OUT("comb_time.csv", j, t);
        OUT("comb_count.csv", j, n);
        delete[] a;
    }
    return 0;
}


/*
int main() {
    srand(time(nullptr));
    long long t;
    clock_t end, begin;
    begin = clock();
    for (int j = 2000; j <= 100000; j = j + 2000) {
        int *a = rand_arr(j);
        for (int i = 0; i < 10; ++i) {
            shell_sort3(a, 0, j, Fib(j));
        }
        end = clock();
        t = (long long) (end - begin);
        std::cout << t << '\t' << j << std::endl;
        OUT("shell3.csv", j, t);
        delete[] a;
    }
    srand(time(nullptr));
    int *a = rand_arr(10);
    for (int i = 0; i < 10; ++i) {
        std::cout << a[i] << std::endl;
    }
    shell_sort3(a, 0, 10, Fib(10));
    std::cout << "" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << a[i] << std::endl;
    }

    return 0;
}
*/