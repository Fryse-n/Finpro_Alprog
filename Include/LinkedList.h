#pragma once
#include "Node.h"
#include <bits/stdc++.h>

template<typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    void pushBack(T* item) {
        Node<T>* newNode = new Node<T>(item);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = newNode;
        }
        size++;
    }

    void removeById(std::string id) {
        if (!head) return;

        if (head->data->getId() == id) {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp->data;
            delete tmp;
            size--;
            return;
        }

        Node<T>* curr = head;
        while (curr->next && curr->next->data->getId() != id) {
            curr = curr->next;
        }

        if (curr->next) {
            Node<T>* tmp = curr->next;
            curr->next = tmp->next;
            delete tmp->data;
            delete tmp;
            size--;
        }
    }

    std::vector<T*> toVector() const {
        std::vector<T*> result;
        Node<T>* curr = head;
        while (curr) {
            result.push_back(curr->data);
            curr = curr->next;
        }
        return result;
    }

    int getSize() const { return size; }
    Node<T>* getHead() const { return head; }

    ~LinkedList() {
        Node<T>* curr = head;
        while (curr) {
            Node<T>* next = curr->next;
            delete curr->data;
            delete curr;
            curr = next;
        }
    }
};