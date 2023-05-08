#ifndef MYQUEUE_H
#define MYQUEUE_H
#include "undo.h"
class MyQueue {
private:
    Undo** arr;
    int front;
    int rear;
    int capacity;
    int size;
public:
    ~MyQueue(){
        if(!isEmpty()){
            int i=rear+1;
            for(;i!=front; (i+ 1)%capacity){
                delete arr[i];
            }
            delete arr[i];
            delete arr;
        }
    }
    MyQueue(int capacity) {
        this->capacity = capacity;
        arr = new Undo*[capacity];
        front = -1;
        rear = -1;
        size = 0;
    }
    bool isEmpty() {
        return size == 0;
    }
    void enqueue(Undo *item) {
        if (isEmpty()) {
            front = 0;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = item;
        size++;
    }
    void dequeue() {
        if (isEmpty()) {
            return;
        }
        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % capacity;
        }
        size--;
    }
    Undo* peek() {
        return arr[front];
    }
};


#endif // MYQUEUE_H
