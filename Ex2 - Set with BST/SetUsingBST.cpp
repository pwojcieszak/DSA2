#include <iostream>

using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node* left;
    Node* right;
    Node* parent;
    explicit Node(T d, Node* parentNode){
        data = d;
        left = nullptr;
        right = nullptr;
        parent = parentNode;
    }
};

template <typename T>
class BST{
public:
    Node<T>* root;
    BST(){root = nullptr;}

    void insert(int data) {
        Node<T> *cur_parent = root;
        Node<T> *prev_parent;
        while (cur_parent) {
            prev_parent = cur_parent;
            if (data < cur_parent->data)
                cur_parent = cur_parent->left;
            else
                cur_parent = cur_parent->right;
        }
        if (cur_parent == root) root = new Node<T>(data, nullptr);
        else if (prev_parent->data < data) prev_parent->right = new Node<T>(data, prev_parent);
        else prev_parent->left = new Node<T>(data, prev_parent);
    }

    Node<T>* search(int data) {
        Node<T>* parent = root;
        while(parent) {
            if (parent->data == data) return parent;
            else if(parent->data < data) parent = parent -> right;
            else parent = parent -> left;
        }
        return nullptr;
    }

    void deleteN(int data) {
        Node<T>* cur_parent = root;
        Node<T>* prev_parent;
        while(true){
            if(cur_parent == nullptr) break;
            if (data < cur_parent->data){
                prev_parent = cur_parent;
                cur_parent = cur_parent->left;
            }
            else if (data > cur_parent->data) {
                prev_parent = cur_parent;
                cur_parent = cur_parent->right;
            }
            else {
                Node<T>* temp;
                if (cur_parent->left == nullptr && cur_parent->right == nullptr)
                    temp = nullptr;
                else if (cur_parent->left == nullptr) {
                    temp = cur_parent->right;
                } else if (cur_parent->right == nullptr) {
                    temp = cur_parent->left;
                }
                else{
                    temp = cur_parent->right;
                    Node<T>* prev_temp = temp;
                    while(temp->left) {
                        prev_temp = temp;
                        temp = temp -> left;
                    }
                    cur_parent -> data = temp -> data;
                    if(prev_temp == cur_parent) prev_temp -> right = nullptr;
                    else prev_temp->left = nullptr;
                    delete(temp);
                    break;
                }
                if(cur_parent == root) {
                    root = temp;
                    delete(cur_parent);
                    break;
                }
                else{
                    delete(cur_parent);
                    if(prev_parent->data < data) prev_parent->right = temp;
                    else prev_parent->left = temp;
                    break;
                }
            }
        }
    }

    void inorder(Node<T> *parent) {
        if (parent != nullptr) {
            inorder(parent->left);
            std::cout<<parent->data<<" -> ";
            inorder(parent->right);
        }
    }
};


template <typename T>
class Set{
private:
    BST<T> tree;
public:
    Set<T>()= default;
    Set<T>(const Set<T> &anotherSet){
        copy(anotherSet.tree.root);
    }

    void copy(Node<T>* node){
        if(node == nullptr) return;
        else tree.insert(node->data);
        copy(node->left);
        copy(node->right);
    }

    Node<T>* locate(T value){
        return tree.search(value);
    }

    void add(T value){
        tree.insert(value);
    }

    void remove(Node<T>* node){
        tree.deleteN(node->data);
    }

    void print(){
        tree.inorder(tree.root);
    }

    void sumHelper(Set<T> &newSet, Node<T>* currentParent){
        if(currentParent == nullptr) return;
        if(!newSet.locate(currentParent->data)) newSet.add(currentParent->data);
        sumHelper(newSet, currentParent->left);
        sumHelper(newSet, currentParent->right);
    }

    Set<T> sum(Set<T> anotherSet){
        Set<T> newSet = *this;
        sumHelper(newSet, anotherSet.tree.root);
        return newSet;
    }

    void differenceHelper(Set<T> &newSet, Node<T>* currentParent){
        if(currentParent == nullptr) return;
        if(newSet.locate(currentParent->data)) newSet.remove(newSet.locate(currentParent->data));
        differenceHelper(newSet, currentParent->left);
        differenceHelper(newSet, currentParent->right);
    }

    Set<T> difference(Set<T> anotherSet){
        Set<T> newSet = *this;
        differenceHelper(newSet, anotherSet.tree.root);
        return newSet;
    }

    void intersectionHelper(Set<T> &newSet, Node<T>* currentParent, Set<T> anotherSet){
        if(currentParent == nullptr) return;
        if(anotherSet.locate(currentParent->data)) newSet.add(currentParent->data);
        intersectionHelper(newSet, currentParent->left, anotherSet);
        intersectionHelper(newSet, currentParent->right, anotherSet);
    }

    Set<T> intersection(Set<T> anotherSet){
        Set<T> newSet;
        intersectionHelper(newSet, tree.root, anotherSet);
        return newSet;
    }
};

int main() {
    Set<int> s1;
    s1.add(2);
    s1.add(4);
    s1.add(5);
    s1.add(3);
    cout<<"\nSET 1"<<endl;
    s1.print();
    Set<int> s2;
    s2.add(2);
    s2.add(7);
    s2.add(8);
    cout<<"\nSET 2"<<endl;
    s2.print();

    cout<<"\nSUMA"<<endl;
    Set<int> suma = s1.sum(s2);
    suma.print();

    cout<<"\nROZNICA"<<endl;
    Set<int> difference = s1.difference(s2);
    difference.print();

    cout<<"\nPrzeciecie"<<endl;
    Set<int> intersection = s1.intersection(s2);
    intersection.print();

    return 0;
}
