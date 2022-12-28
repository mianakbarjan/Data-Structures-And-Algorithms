#include <iostream>
using namespace std;

class Node{
private:
Node *right;
Node *left;
int height;
int key;

public:
Node (int k){
right = nullptr;
left = nullptr;
height = 0;
key = k;
}
friend class AVLTree;
};

class AVLTree{
private:
Node *root;
void inOrder(Node *temp){
    if (temp!=nullptr){
        inOrder(temp->left);
        cout << temp->key << " ";
        inOrder(temp->right);
    }
}
public:
AVLTree(){
    root = nullptr;
}
AVLTree(int x){
    root = new Node (x);
}
void showListInOrder(){
    inOrder(root);
}
Node *rotateRight (Node *z);
Node *rotateLeft (Node *z);
Node *doubleLeft(Node *K1);
Node *doubleRight(Node *K1);
Node *insertNodeHelper(int key, Node *temp);
Node *deleteNodeHelper(int key, Node *temp);
void insertNode(int x){
    root = insertNodeHelper(x,root);
}
void deleteNode(int x){
    root = deleteNodeHelper(x, root);
}
Node *minValueNode(Node *node){
    Node *current = node;
    while (current->left!= nullptr){
        current = current->left;
    }
    return current;
}


int height (Node *N){
    if (N==nullptr){
        return 0;
    }
    return N->height;
}
int max (int a, int b){
    if (a>b){
        return a;
    }
    else {
        return b;
    }
}
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
};


Node* AVLTree:: rotateRight(Node *K2){
    Node *K1 = K2->right;
    K2->right = K1->left;
    K1->left = K2;
    K1->height = max(height(K1->left), height(K1->right))+1;
    K1->height = max(height(K1->left), height(K1->right))+1;
    return K1;
}
Node *AVLTree::rotateLeft(Node *K2){
    Node *K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;
    K2->height = max(height(K2->left), height(K2->right))+1;
    K1->height = max(height(K1->left), height(K1->right))+1;
    return K1;
}

Node *AVLTree::doubleLeft(Node *K1){
    K1->left = rotateRight (K1->left);
    return rotateLeft(K1);
}
Node *AVLTree::doubleRight(Node *K1){
    K1->right = rotateLeft (K1->left);
    return rotateRight(K1);
}

Node* AVLTree:: insertNodeHelper(int x, Node *temp){
    if (temp == nullptr){
        Node *newNode = new Node(x);
        temp = newNode;
    }
    else if (x<temp->key){
        temp->left = insertNodeHelper(x, temp->left);
        if (height(temp->left) - height(temp->right)==2){
            if (x<temp->left->key){
                temp=rotateLeft(temp);
            }
            else {
                // temp = doubleLeft(temp);
                temp->left = rotateLeft(temp->left);
            return rotateRight(temp);
            }
        }
        
    }
    else if (x>temp->key){
        temp->right=insertNodeHelper(x, temp->right);
        if (height(temp->left) - height(temp->right)==2){
            if (x>temp->right->key){
            temp = rotateRight(temp);
            }
            else {
                // temp = doubleRight(temp);
                temp ->right = rotateRight(temp->right);
            return rotateLeft(temp);
            }
        }
    }
        temp->height = max(height(temp->left), height(temp->right))+1;
        return temp;

}
Node *AVLTree::deleteNodeHelper(int key, Node *root){
    if (root==nullptr){
    return root; 
    }
    if (key<root->key){
        root->left = deleteNodeHelper(key, root->left);
    }

    else if (key>root->key){
        root->right = deleteNodeHelper(key, root->right);
    }

    else{
        if ((root->left == nullptr) || (root->right == nullptr)){
            Node *temp = root->left ? root->left : root->right;

            if (temp == nullptr){
                temp = root;
                root = nullptr;
            }
            else{
                *root = *temp;
            }
            free(temp);

        }
        else{
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNodeHelper(temp->key, root->right);
        }
    }
    if (root == nullptr){
        return root;
    }
    root -> height = 1+max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (key<root->key){
        root->left = insertNodeHelper(key, root->left);
        if (height(root->left) - height(root->right)==2){
            if (key<root->left->key){
                root=rotateLeft(root);
            }
            else {
                // root = doubleLeft(root);
                root->left = rotateLeft(root->left);
            return rotateRight(root);
            }
        }
        
    }
    else if (key>root->key){
        root->right=insertNodeHelper(key, root->right);
        if (height(root->left) - height(root->right)==2){
            if (key>root->right->key){
            root = rotateRight(root);
            }
            else {
                // root = doubleRight(root);
                root ->right = rotateRight(root->right);
            return rotateLeft(root);
            }
        }
    }
    return root;    
}


int main(){

    AVLTree t;
    t.insertNode(13);
    t.insertNode(10);
    t.insertNode(5);
    t.insertNode(4);
    t.insertNode(8);
    t.insertNode(11);
    t.insertNode(15);
    t.insertNode(16);
    t.insertNode(13);
    t.insertNode(3);
    t.insertNode(45);
    t.insertNode(7);
    t.insertNode(15);
    t.showListInOrder();
    t.deleteNode(3);
    cout << endl;
    t.showListInOrder();

}

