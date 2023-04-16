#include <iostream>

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
class Bst{
public:
    Node<T>* root;
    Bst(){root = nullptr;}
    void insert(int);
    Node<T>* search(int);
    void deleteN(int);
    void inorder(Node<T>*);
};

template <typename T>
void Bst<T>::insert(int data) {
    Node<T>* cur_parent = root;
    Node<T>* prev_parent;
    while(cur_parent){
        prev_parent = cur_parent;
        if (data < cur_parent->data)
            cur_parent = cur_parent->left;
        else
            cur_parent = cur_parent->right;
    }
    if(cur_parent == root) root = new Node<T>(data, nullptr);
    else if(prev_parent->data < data) prev_parent->right = new Node<T>(data, prev_parent);
    else prev_parent->left = new Node<T>(data, prev_parent);

}

template <typename T>
Node<T>* Bst<T>::search(int data) {
    Node<T>* parent = root;
    while(parent) {
        if (parent->data == data) return parent;
        else if(parent->data < data) parent = parent -> right;
        else parent = parent -> left;
    }
    return nullptr;
}

template <typename T>
void Bst<T>::deleteN(int data) {
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
                Node<T>* prev_temp = cur_parent;
                while(temp->left != nullptr) {
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

template <typename T>
void Bst<T>::inorder(Node<T> *parent) {
    if (parent != nullptr) {
        inorder(parent->left);
        std::cout<<parent->data<<" -> ";
        inorder(parent->right);
    }
}

int main() {
    Bst<int> tree;
    tree.insert(2);
    tree.insert(4);
    tree.insert(5);
    tree.insert(3);
    tree.inorder(tree.root);
    if(tree.search(1)) std::cout<<"\nFound"<<std::endl;
    else std::cout<<"\nNot Found"<<std::endl;
    tree.deleteN(2);
    tree.inorder(tree.root);
    return 0;
}
