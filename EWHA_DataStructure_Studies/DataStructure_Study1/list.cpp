#include <iostream>

// 2272027 전자전기공학 심희윤

class Node {
public:
    Node* front;
    Node* rear;
    int data;

    Node(int value) : data(value), front(nullptr), rear(nullptr) {}
};

class List {
private:
    Node* head;
    Node* tail;
    int size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    void insertFront(int value) {
        Node* node = new Node(value); //새로운 노드 생성
        node->front = head; // 새로운 노드는 기존의 맨 앞에 있는 노드를 front로 가르키게 된다.
        head = node; // head 포인터가 리스트의 맨 앞에 있는 노드를 가르키게 한다.

        if(size == 0){ // 리스트가 비어있었을 경우
            tail = node; // 맨 처음 앞으로 들어온 노드를 tail 포인터가 가르키게 한다.
        }
        else{ // 리스트가 비어있지 않을 경우
            node->front->rear = node; // 새로 들어온 노드의 front가 가르키는 노드의
            // rear 포인터는 새로 들어온 노드 즉 node를 가르키게 된다.
        }
        size++; // 리스트 길이 +1
    }

    void insertBack(int value) {
        Node* node = new Node(value); //새로운 노드 생성
        node->rear = tail; // 새로운 노드는 기존의 맨 뒤에 있는 노드를 rear로 가르키게 된다.
        tail = node; // head 포인터가 리스트의 맨 앞에 있는 노드를 가르키게 한다.

        if(size == 0){ // 리스트가 비어있었을 경우
            head = node; // 맨 처음 뒤로 들어온 노드를 head 포인터가 가르키게 한다.
        }
        else{ // 리스트가 비어있지 않을 경우
            node->rear->front = node; // 새로 들어온 노드의 front가 가르키는 노드의
            // rear 포인터는 새로 들어온 노드 즉 node를 가르키게 된다.
        }
        size++; // 리스트 길이 +1
    }

    void insert(int index, int value) {
        if(index == 0){ // 맨 앞에 넣는 경우
            insertFront(value);
            return;
        }
        if(index == size){ // 맨 뒤에 넣는 경우
            insertBack(value);
            return;
        }

        if(index < 0 || index > size){ // 에러 처리
            return;
        }

        Node* node = new Node(value); // 삽입할 노드 생성
        Node *n = head;
        for(int i = 1; i < index; i++){// index 만큼 노드를 움직인다.
            n = n->front; 
        }

        node->front = n->front; // 삽입할 노드의 front에 n 노드의 front가 가르키는 노드를 할당
        n->front = node; // n 노드의 front가 새로 삽입할 노드를 가르키게 한다.
        node->rear = n; // 삽입할 노드의 rear에 n 노드를 할당
        node->front->rear = node; // 삽입할 노드의 앞에 있는 노드의 rear가 새로 삽입하는 노드를 가르키게 한다.

        size++; // 리스트 길이 +1
    }

    int erase(int value) {
        for(Node *n = head; n != nullptr ; n = n->front){// 맨 앞에서부터 리스트의 끝까지 서치한다.
            if(n->data == value){ // 만약 찾는 값을 가진 노드가 있는 경우
                n->front->rear = n->rear; // 해당 노드의 앞에 붙은 노드의 rear 포인터를 수정한다.
                n->rear->front = n->front; // 해당 노드의 뒤에 붙은 노드의 front 포인터를 수정한다.
                if(n == head){ // 지운 노드가 헤드였을 경우
                    head = n->front; // 지운 노드의 front 포인터가 가르키는 노드가 새 head가 된다.
                }
                if(n == tail){ // 지운 노드가 tail였을 경우
                    tail = n->rear; // 지운 노드의 rear 포인터가 가르키는 노드가 새 tail가 된다.
                }
                size--; // 리스트의 크기 줄이기
                delete n; // 메모리 해제
                return 1; // 지웠다는 뜻의 1 반환
            }
        }
        return 0; // 지울 노드를 찾지 못했다는 뜻의 0 반환
    }

    int find(int value) {
        for(Node *n = head; n != nullptr ; n = n->front){// 맨 앞에서부터 리스트의 끝까지 서치한다.
            if(n->data == value){
                printf("%d is in the list\n", value);
                return 1; // 찾는 노드가 존재헌다는 뜻의 1 반환
            }
        }
        printf("%d is not in the list\n", value);
        return 0; // 찾는 노드가 존재하지 않는 뜻의 0 반환
    }

    void printList() {
        for(Node *n = head; n != nullptr ; n = n->front){// 맨 앞에서부터 리스트의 끝까지 서치한다.
            printf("%d ", n->data);
        }
        printf("\n");
    }
};

int main() {
    List list;

    list.find(1);
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);
    list.printList();

    list.insertBack(10);
    list.insertBack(11);
    list.insertBack(12);
    list.printList();

    list.insert(3, 0);
    list.printList();

    list.find(1);
    list.erase(1);
    list.find(1);

    return 0;
}
