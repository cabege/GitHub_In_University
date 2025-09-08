#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

// 2272027 전자전기공학과 심희윤


// AVL 트리의 노드 정의
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    int balance; // 균형 값

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1), balance(0) {}
};

// 노드의 높이 반환
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// 노드의 높이와 균형 값 업데이트
void updateNode(Node* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->balance = getHeight(node->left) - getHeight(node->right);
    }
}

// 오른쪽 회전
Node* rotateRight(Node* y) {
    Node *x = y->left; // x는 y의 왼쪽 자식
    Node *T = x->right; // T는 x의 오른쪽 서브트리

    x->right = y; // x를 y보다 위로 올리면서 x의 오른쪽 자식으로 y를 붙인다.
    y->left = T; // y는 빈 왼쪽 자식 부분에 x의 오른쪽 서브트리를 붙인다.

    //노드 높이 갱신
    updateNode(x);
    updateNode(y);

    //루트 노트 x 반환
    return x;
}

// 왼쪽 회전
Node* rotateLeft(Node* x) {
    Node *y = x->right; // y는 x의 오른쪽 자식
    Node *T = y->left; // T는 y의 왼쪽 서브트리

    y->left = x; // y를 x보다 위로 올리면서 y의 왼쪽 자식으로 x를 붙인다.
    x->right = T; // x는 빈 오른쪽 자식 부분에 y의 왼쪽 서브트리를 붙인다.

    //노드 높이 갱신
    updateNode(x);
    updateNode(y);

    //루트 노트 x 반환
    return y;
}

// 균형 노드 처리
Node* balanceNode(Node* node, const set<int>& validBalances) {
    updateNode(node);

    int bal = node->balance;
    int min = *validBalances.begin();
    int max = *validBalances.rbegin();
    // set의 최소값과 최대값을 저장하는 변수
    
    
    // 균형 노드 처리 코드
    // balance 값이 max 보다 큰 경우 LX case 이다.
    if (bal > max) {
        if (!node->left) return node;
        // 왼쪽 자식이 NULL 노드일때의 예외처리
        
        // LR case: 왼쪽 자식의 balance가 음수인 경우
        if (node->left->balance < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // LL case
        return rotateRight(node);
    }
    
    // balance 값이 min 보다 큰 경우 RX case 이다.
    if (bal < min) {
        if (!node->right) return node;
        // 오른쪽 자식이 NULL 노드일때의 예외처리
        
        // RL case: 오른쪽 자식의 balance가 양수인 경우
        if (node->right->balance > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        // RR case
        return rotateLeft(node);
    }

    return node;
}

// 노드 삽입
Node* insert(Node* node, int key, const set<int>& validBalances) {
    if (!node) {
        return new Node(key);
    }

    // 키 삽입
    if(key > node->key)
        node->right = insert(node->right, key, validBalances);
    else if(key < node->key)
        node->left = insert(node->left, key, validBalances);
    else
        return node;

    // 균형 노드 처리
    return balanceNode(node, validBalances);
}

// BFS로 트리 출력
void bfsPrint(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    cout << "BFS traversal: ";
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->key << " ";

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    cout << endl;
}

// 트리 상태 및 결과 출력
void printResults(const vector<int>& keys, const vector<set<int>>& subsets) {
    for (const auto& subset : subsets) {
        cout << "Valid balances: { ";
        for (int b : subset) cout << b << " ";
        cout << "}\n";

        Node* root = nullptr;
        for (int key : keys) {
            root = insert(root, key, subset);
            cout << "Key inserted: " << key << ", Tree height: " << root->height << endl;
        }
        bfsPrint(root); // BFS 출력
        cout << "-------------------------" << endl;
    }
}

// 메인 함수
int main() {
    vector<int> keys = {11, 1, 12, 5, 15, 8, 13, 17}; // 삽입할 키
    vector<set<int>> subsets = {
        {-2, -1, 0, 1, 2},  // 모든 균형 허용
        {-1, 0, 1}           // 기본적인 AVL 트리 균형 허용
    };

    printResults(keys, subsets);

    return 0;
}
