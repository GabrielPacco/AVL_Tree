//
//  Red_Black_Tree.cpp
//  AVL
//
//  Created by Gabriel on 5/11/21.
//

/*
 Implemente la Clase Árbol Rojo-Negro (Red-Black tree) que contenga las siguientes operaciones:

 Minimum(y): Retorna el Nodo que contiene el menor elemento en el árbol y.
 Search(x): Retorna el Nodo que contiene x  en el árbol.
 leftRotate(x): rotar a la izquierda el nodo x.
 rightRotate(x): rotar a la derecha el nodo x.
 Insert(x): Insertar x en el árbol (implementar insertFix)
 Remove(x): Eliminar x del árbol (implementar removeFix)
*/

#include <iostream>

using namespace std;

class Node {
public:
    Node* left; // Izquierda
    int data;  // Contenido
    Node* right; // Derecha
    int height;  // Altura
};

class AVL{
public:
    Node* root;  // Raiz

    AVL(){ root = nullptr; }

    // Helper methods for inserting/deleting
    int Minimum(Node *p);
    int NodeHeight(Node* p);
    int Factor_Balance(Node* p);
    Node* LLRotation(Node* p);
    Node* RRRotation(Node* p);
    Node* LRRotation(Node* p);
    Node* RLRotation(Node* p);
    Node* InPre(Node* p);
    Node* InSucc(Node* p);

    // Insert
    Node* rInsert(Node* p, int key);

    // Traversal
    void Inorder(Node* p);
    void Inorder(){ Inorder(root); }
    Node* getRoot(){ return root; }

    // Delete
    Node* Delete(Node* p, int key);
    
};

int AVL::NodeHeight(Node *p) {
    int hl;
    int hr;

    hl = (p && p->left) ? p->left->height : 0;
    hr = (p && p->right) ? p->right->height : 0;
 
    return hl > hr ? hl + 1 : hr + 1;
}
 
int AVL::Factor_Balance(Node *p) {
    int hl;
    int hr;
 
    hl = (p && p->left) ? p->left->height : 0;
    hr = (p && p->right) ? p->right->height : 0;
 
    return hl - hr;
}
 
Node* AVL::LLRotation(Node *p) {
    Node* pl = p->left;
    Node* plr = pl->right;
 
    pl->right = p;
    p->left = plr;
 
    // Update height
    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);
 
    // Update root
    if (root == p){
        root = pl;
    }
    return pl;
}
 
Node* AVL::RRRotation(Node *p) {
    Node* pr = p->right;
    Node* prl = pr->left;
 
    pr->left = p;
    p->right = prl;
 
    // Update height
    p->height = NodeHeight(p);
    pr->height = NodeHeight(pr);
 
    // Update root
    if (root == p){
        root = pr;
    }
    return pr;
}
 
Node* AVL::LRRotation(Node *p) {
    Node* pl = p->left;
    Node* plr = pl->right;
 
    pl->right = plr->left;
    p->left = plr->right;
 
    plr->left = pl;
    plr->right = p;
 
    // Update height
    pl->height = NodeHeight(pl);
    p->height = NodeHeight(p);
    plr->height = NodeHeight(plr);
 
    // Update root
    if (p == root){
        root = plr;
    }
    return plr;
}
 
Node* AVL::RLRotation(Node *p) {
    Node* pr = p->right;
    Node* prl = pr->left;
 
    pr->left = prl->right;
    p->right = prl->left;
 
    prl->right = pr;
    prl->left = p;
 
    // Update height
    pr->height = NodeHeight(pr);
    p->height = NodeHeight(p);
    prl->height = NodeHeight(prl);
 
    // Update root
    if (root == p){
        root = prl;
    }
    return prl;
}

Node* AVL::InPre(Node *p) {
    while (p && p->right != nullptr){
        p = p->right;
    }
    return p;
}

Node* AVL::InSucc(Node *p) {
    while (p && p->left != nullptr){
        p = p->left;
    }
    return p;
}

Node* AVL::rInsert(Node *p, int key) {
    Node* t;
    if (p == nullptr){
        t = new Node;
        t->data = key;
        t->left = nullptr;
        t->right = nullptr;
        t->height = 1;  // Starting height from 1 onwards instead of 0
        return t;
    }
 
    if (key < p->data){
        p->left = rInsert(p->left, key);
    } else if (key > p->data){
        p->right = rInsert(p->right, key);
    }
 
    // Update height
    p->height = NodeHeight(p);
 
    // Balance Factor and Rotation
    if (Factor_Balance(p) == 2 && Factor_Balance(p->left) == 1) {
        return LLRotation(p);
    } else if (Factor_Balance(p) == 2 && Factor_Balance(p->left) == -1){
        return LRRotation(p);
    } else if (Factor_Balance(p) == -2 && Factor_Balance(p->right) == -1){
        return RRRotation(p);
    } else if (Factor_Balance(p) == -2 && Factor_Balance(p->right) == 1){
        return RLRotation(p);
    }
 
    return p;
}

void AVL::Inorder(Node *p) {
    if (p){
        Inorder(p->left);
        cout << p->data << ", " << flush;
        Inorder(p->right);
    }
}

Node* AVL::Delete(Node *p, int key) {
    if (p == nullptr){
        return nullptr;
    }

    if (p->left == nullptr && p->right == nullptr){
        if (p == root){
            root = nullptr;
        }
        delete p;
        return nullptr;
    }

    if (key < p->data){
        p->left = Delete(p->left, key);
    } else if (key > p->data){
        p->right = Delete(p->right, key);
    } else {
        Node* q;
        if (NodeHeight(p->left) > NodeHeight(p->right)){
            q = InPre(p->left);
            p->data = q->data;
            p->left = Delete(p->left, q->data);
        } else {
            q = InSucc(p->right);
            p->data = q->data;
            p->right = Delete(p->right, q->data);
        }
    }

    // Update height
    p->height = NodeHeight(p);
 
    // Balance Factor and Rotation
    if (Factor_Balance(p) == 2 && Factor_Balance(p->left) == 1) {  // L1 Rotation
        return LLRotation(p);
    } else if (Factor_Balance(p) == 2 && Factor_Balance(p->left) == -1){  // L-1 Rotation
        return LRRotation(p);
    } else if (Factor_Balance(p) == -2 && Factor_Balance(p->right) == -1){  // R-1 Rotation
        return RRRotation(p);
    } else if (Factor_Balance(p) == -2 && Factor_Balance(p->right) == 1){  // R1 Rotation
        return RLRotation(p);
    } else if (Factor_Balance(p) == 2 && Factor_Balance(p->left) == 0){  // L0 Rotation
        return LLRotation(p);
    } else if (Factor_Balance(p) == -2 && Factor_Balance(p->right) == 0){  // R0 Rotation
        return RRRotation(p);
    }
 
    return p;
}

int AVL::Minimum(Node *p)
{
    int min=p->data;
    
    while (p != nullptr){
        if (p->data < min){
            min=p->data;
        }else if (p->data == min){
            p = p->left;
        }else{
            p = p->right;
        }
    }
    return min;
}


int main() {
 
    AVL tree;
 
    int A[] = {1, 4, 6, 8, 3, 5, 7, 9};
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++){
        tree.root = tree.rInsert(tree.root, A[i]);
    }
 
    tree.Inorder();
    cout << endl;
 
    tree.Delete(tree.root, 28);
   
    tree.Inorder();
    cout << endl;
    
    cout << "\n\nMinimo Elemento de AVL: " << tree.Minimum(tree.root);
    cout << endl;

    return 0;
}

