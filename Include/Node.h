#pragma once

template<typename T>
struct Node {
    T* data;
    Node<T>* next;

    Node(T* d) : data(d), next(nullptr) {}
};