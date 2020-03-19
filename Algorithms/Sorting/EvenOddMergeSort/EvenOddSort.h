#pragma once
#include<iostream>
#include<vector> 
#include<Windows.h>
#include<thread>
#include<cmath>

template<class T>
void Merge(std::vector<T>& a, int l, int r)
{
    int half = (l + r) / 2;
    std::vector<T> tmp(a.size());
    int i = l, j = half + 1;
    int k = l;
    while (i <= half && j <= r) {
        if (a[i] < a[j]) {
            tmp[k] = a[i];
            ++i;
            ++k;
        }
        else {
            tmp[k] = a[j];
            ++j;
            ++k;
        }
    }
    for (int n = i; n <= half; ++n) {
        tmp[k] = a[n];
        ++k;
    }

    for (int n = j; n <= r; ++n) {
        tmp[k] = a[n];
        ++k;
    }
    for (int i = l; i <= r; ++i) {
        a[i] = tmp[i];
    }
}

template<class T>
void Divide(std::vector<T>& a, int l, int r)
{
    int half = (l + r) / 2;
    std::vector<T> tmp(a.size());
    int i, j;
    for (i = l, j = 0; i <= r; i += 2, j++)
    {
        tmp[l + j] = a[i];
        tmp[half + j + 1] = a[i + 1];
    }
    for (int i = l; i <=r; i++)
        a[i] = tmp[i];
}
template<class T>
void compexch(T& a, T& b)
{
    if (b < a) {
        T temp = b;
        b = a;
        a = temp;
    }
}

template<class T>
void OddEvenMergeSortEx(std::vector<T>& a, int& n, int l, int r) {
    if (r == l + 1)
        compexch(a[l], a[r]);
    if (r < l + 2)
        return; 
    Divide<T>(a, l, r); 
    int half = (l + r) / 2;

    if (n > 1) {
        n -= 2;
        std::thread thread1(OddEvenMergeSortEx<T>, std::ref(a), std::ref(n), l, half);
        std::thread thread2(OddEvenMergeSortEx<T>, std::ref(a), std::ref(n), half + 1, r);
        thread1.join();
        thread2.join();
    }
    else if (n == 1) {
        --n;
        std::thread thread1(OddEvenMergeSortEx<T>, std::ref(a), std::ref(n), l, half);
        OddEvenMergeSortEx<T>(a, n, half + 1, r);
        thread1.join();
    }
    else {
        OddEvenMergeSortEx<T>(a, n, l, half);
        OddEvenMergeSortEx<T>(a, n, half + 1, r);
    }

    Merge<T>(a, l, r);
    for (int i = l + 1; i < r; i += 2)
        compexch(a[i], a[i + 1]);
    int halfSize = (r - l + 1) / 2 - 1;
    for (int i = l + 1; i + halfSize < r; i++)
        compexch(a[i], a[i + halfSize]);
}

template<class T>
void OddEvenMergeSort(std::vector<T>& a, int ThreadSCount, int l, int r) {
    OddEvenMergeSortEx<T>(a, ThreadSCount, l, r);
}