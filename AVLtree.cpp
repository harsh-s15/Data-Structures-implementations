#include <bits/stdc++.h>
using namespace std;

typedef struct node{
    int id;
    node* left; node* right;
    int height;
    node(int x){
        id = x;
        left = right = nullptr;
        height = 0;
    }
} node;

int height(node* r){
    if(!r) return 0;
    return r->height;
}

node* rightRotate(node* r){
    if(!r->left) return r;

    node* x = r->left;
    node* T = x->right;

    x->right = r;
    r->left = T;

    r->height = 1 + max(height(r->left),height(r->right));
    x->height = 1 + max(height(x->left),height(x->right));

    return x;
}

node* leftRotate(node* r){
    if(!r->right) return r;

    node* x = r->right;
    node* T = x->left;

    x->left = r;
    r->right = T;

    r->height = 1 + max(height(r->left),height(r->right));
    x->height = 1 + max(height(x->left),height(x->right));

    return x;
}

int bal(node* r){
    int b = 0;
    if(r->left) b += r->left->height;
    if(r->right) b -= r->right->height;
    return b;
}

node* balance(node* r,int x){
    int b = bal(r);
    if(-1<=b and b<=1) return r;

    if(b<-1 and r->right->id<x) return leftRotate(r);
    if(1<b and x<r->left->id) return rightRotate(r);

    if(b<-1 and x<r->right->id){
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }
    if(1<b and r->left->id<x){
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }

    return r;
}

node* insert(node* r, int x){
    if(!r) return new node(x);
    if(x<r->id){
        r->left = insert(r->left,x);
        r->height = max(1+r->left->height,r->height);
    }

    else if(x>r->id){
        r->right = insert(r->right,x);
        r->height = max(1+r->right->height,r->height);
    }
    return balance(r,x);
}




void inorder(node* r){
    if(!r) return;
    inorder(r->left);
    printf("%d(%d) ",r->id, bal(r));
    inorder(r->right);
}
int main(){

    node* root = new node(17);
    for(int y : {72,12,23,54,76,9,14,19,24,67}){
        root = insert(root,y);
        inorder(root); cout << '\n';
    }

//    inorder(root); cout << '\n';

    return 0;
}
