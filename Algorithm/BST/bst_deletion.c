#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *left, *right, *parent;
} Node;

Node* new_node(int key){
    Node* n = malloc(sizeof(Node));
    if (n == NULL){
        perror("malloc");
        exit(1);
    }
    n->key = key;
    n->left = n->right = n->parent = NULL;
    return n;     // 새로 생성한 n 노드의 주소를 반환
}

Node* search(Node *root, int key) {
    if (root == NULL)  //없음 -> 삽입할 자리
        return NULL;

    //printf("%d ", root->key);

    if (root->key == key)
        return root;

    // left subtree
    if (root->key > key){
        return search(root->left, key);
    }
    //right subtree
    else{
        return search(root->right, key);
    }
}

void insert(Node** root, int key){
    Node* x = *root;  //탐색용: x에는 root 노드의 주소가 담김
    Node* parent = NULL;

    while(x != NULL){
        if (x->key == key){
            return;
        }
        if (x->key > key){
            parent = x;
            x = x->left;
        }
        else {
            parent = x;
            x = x->right;
        }
    }

    // x가 NULL인 경우, 루프를 빠져나옴. (삽입 위치에 도착)
    Node* n = new_node(key);

    //연결
    if(parent == NULL)  //아예 비어있는 트리의 경우 -> root가 됨
        *root = n;
    else if(parent->key > key) {
        parent->left = n;
        n->parent = parent;
    }
    else {
        parent->right = n; 
        n->parent = parent;
    }
}

Node* tree_min(Node* x){
    if(x == NULL) return NULL;
    while(x->left != NULL){
        x = x->left;
    }
    return x;   //최솟값 노드 반환
}

Node* tree_max(Node* x){
    if(x == NULL) return NULL;
    while(x->right != NULL){
        x = x->right;
    }
    return x;   // 최댓값 노드 반환
}

Node* succ(Node* x){
    if (x->right != NULL){   // case 1: 오른쪽 노드가 있는 경우
        return tree_min(x->right);
    }
    else {      // case 2: 오른쪽 노드가 없음
        Node* parent = x->parent;
        while (parent != NULL && x == parent->right){
            parent = parent->parent;
            x = x->parent;
        }
        return parent;
    }
}

Node* pred(Node* x){
    if (x->left != NULL){   // case 1: 왼쪽 자식이 있는 경우 -> 왼쪽 subtree 최댓값이 pred 
        return tree_max(x->left);
    }
    else {      // case 2: 왼쪽 노드가 없음
        Node* parent = x->parent;
        while (parent != NULL && x == parent->left){
            parent = parent->parent;
            x = x->parent;
        }
        return parent;
    }
}

int bst_delete(Node** root, Node* z){
    Node* k = z;
    
    Node* p = k->parent;
    Node* lc = k->left;
    Node* rc = k->right;

    // case 1: 자식이 없는 경우
    if (lc == NULL && rc == NULL) {
        if (p == NULL) {
            free(k); *root = NULL;
        }
        else if (p->left == k) {p->left = NULL; free(k); }
        else                   {p->right = NULL; free(k); }
        return 1;
    }
    // case 2: 자식이 1개
    else if (lc != NULL && rc == NULL){     // 왼쪽 자식만 있는 경우
        if (p == NULL){
            *root = lc;
            lc->parent = NULL;
            free(k);
        }
        else if (p->left == k){
            p->left = lc;
            lc->parent = p;
            free(k);
        }
        else {
            p->right = lc;
            lc->parent = p;
            free(k);
        }
        return 2;
    }
    else if (rc != NULL && lc == NULL){     // 오른쪽 자식만 있는 경우
        if (p == NULL){
            *root = rc;
            rc->parent = NULL;
            free(k);
        }
        else if (p->left == k){
            p->left = rc;
            rc->parent = p;
            free(k);
        }
        else {
            p->right = rc;
            rc->parent = p;
            free(k);
        }
        return 2;
    }
    // case 3: k의 자식이 2개 있는 경우
    else{
        Node* s = succ(k);    //succ 활용
        int y = s->key;       // pointer 이동없이 key만 복사 후 변겅
        k->key = y;
        bst_delete(root, s);
        return 3;
    }
}

void inorder(Node *x){
    if (x == NULL) return;
    inorder(x->left);
    printf("%d ", x->key);
    inorder(x->right);

}

int height(Node* x){
    if (x == NULL){
        return -1;
    }

    int L = height(x->left);
    int R = height(x->right);

    if (L >= R){
        return L+1;
    }
    else{
        return R+1;
    }
}

void free_tree(Node* x){
    if (x == NULL) return ;

    free_tree(x->left);
    free_tree(x->right);
    free(x);
}

void print_key(Node* x){
    if (x == NULL) printf("NIL");
    else           printf("%d", x->key);
}



int main(void){

    int n, q, key = 0;
    if(scanf("%d", &n) != 1) return 1;

    Node* root = NULL;
    for(int i = 0; i < n; i++){
        
        scanf("%d", &key);
        insert(&root, key);  //값을 바꾸기 위해 노드의 주소를 넘겨서 바꿈
    }

    // 2. 정렬
    printf("inorder: ");
    inorder(root);
    printf("\n");
    printf("height: %d\n", height(root));

    printf("min: ");
    print_key(tree_min(root));
    printf("\n");

    printf("max: ");
    print_key(tree_max(root));
    printf("\n");

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &key);
        Node *x = search(root, key);      // key로 node 찾기
    
        if (x == NULL) {                  // 없으면 not found
            printf("%d: not found\n", key);
            continue;                     
        }
    
        printf("%d: pred=", key);         // 있으면 그 node의 Pred/succ
        print_key(pred(x));
        printf(" succ=");
        print_key(succ(x));
        printf("\n");
    }

    // 4. 메모리 해제
    free_tree(root);
    return 0;
}