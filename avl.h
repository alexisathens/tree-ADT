//
//  avl.h
//  Project2
//
//  Created by Alexis Athens on 12/1/17.
//  Copyright © 2017 Alexis Athens. All rights reserved.
//

#ifndef avl_h
#define avl_h
#include <iostream>

using namespace std;

namespace cop3530
{
    template<typename K, typename V, bool (*compare)(K,K), bool (*equals)(K,K)>
    class AVL
    {
    private:
        struct Node
        {
            K key;
            V value;
            int height;
            Node* left;
            Node* right;
            Node(K key, V value)
            {
                this -> key = key;
                this -> value = value;
                this -> height = 1;
                left = nullptr;
                right = nullptr;
            }
        };
        
        Node* root;
        Node* curr;
        Node* prev;
        V temp;
        
    public:
        AVL()
        {
            root = nullptr;
            curr = nullptr;
            prev = nullptr;
        }
        
        AVL(const AVL &src) //copy constructor
        {
            root = src.copy_BST(src.root);
        }
        
        Node* copy_BST(Node* &root)
        {
            Node* temp = nullptr;
            
            if(root)
            {
                temp = new Node(root -> key, root -> value);
                temp -> left = copy_BST(root -> left);
                temp -> right = copy_BST(root -> right);
            }
            
            return temp;
        }
        
        AVL(AVL &&src) //move constructor
        {
            root = src.root;
            src.root = nullptr;
        }
        
        AVL<K, V, compare, equals>& operator=(AVL& src) //copy assignment
        {
            if(this == &src)
            {
                return *this;
            }
            clear(root);
            root = nullptr;
            root = src.copy_BST(src.root);
        }
        
        AVL<K, V, compare, equals>& operator=(AVL&& src) //move assignment
        {
            if(this == &src)
            {
                return *this;
            }
            clear(root);
            root = src.root;
            src.root = nullptr;
        }
        
        ~AVL()
        {
            clear(root);
            delete root;
        }
        
        
        //============ Operations
        
        void insert(K key, V value)
        {
            insert_leaf(root, key, value);
        }
        
        Node* insert_leaf(Node* &root, K key, V value)
        {
            //BST insert_leaf
            if(root == nullptr) //base case
            {
                root = new Node(key, value);
                return root;
            }
            if(equals(key, root -> key)) //if key == root -> key, update
            {
                root -> value = value;
                return root; /// need?????
            }
            else if(compare(key, root -> key)) //if key < root -> key
            {
                insert_leaf(root -> left, key, value);
            }
            else
            {
                insert_leaf(root -> right, key, value);
            }
            
            //make AVL adjustments
            
            //update height
            root -> height = max(getHeight(root -> left), getHeight(root -> right)) + 1;

            //check balance factor
            int bf = getBalance(root);

            
            //rotate as needed
            if(bf > 1 && compare(key, root -> left -> key)) //left heavy & left insert
            {
                return LL(root); //rotate right
            }
            
            if(bf < -1 && !compare(key, root -> right -> key)) //right heavy & right insert
            {
                return RR(root); //rotate left
            }
            
            if(bf > 1 && !compare(key, root -> left -> key)) //left heavy & right insert
            {
                root -> left = RR(root -> left); //rotate left
                return LL(root); //then rotate right
            }
            
            if(bf < -1 && compare(key, root -> right -> key)) //right heavy & left insert
            {
                root -> right = LL(root -> right); //rotate right
                return RR(root); //then rotate left
            }

            
            return root;
        }
        
        Node* LL(Node* &root) //left heavy, rotate right
        {
            //cout << "Rotating right with root " << root -> key << endl;
            curr = root;
            root = root -> left;
            curr -> left = root -> right;
            root -> right = curr;
            return root; //updated root
        }
        
        Node* RR(Node* &root) //right heavy, rotate left
        {
            //cout << "Rotating left with root " << root -> key << endl;
            curr = root;
            root = root -> right;
            curr -> right = root -> left;
            root -> left = curr;
            return root; //updated root
        }
        
        int getHeight(Node* &root)
        {
            if(root == nullptr)
            {
                return 0;
            }
            
            return root -> height;
        }
        
        int getBalance(Node* &root)
        {
            if(root == nullptr)
            {
                return 0;
            }
            
            return getHeight(root -> left) - getHeight(root -> right);
        }
        
        void remove(K key)
        {
            if(root == nullptr)
            {
                throw runtime_error("Error, tree does not exist");
            }
            
            temp = lookup(key); //check if key exists
            if(temp != -1) //if key is valid
            {
                remove_leaf(root, key);
            }
            else
            {
                throw runtime_error("Error, key does not exist");
            }
        }
        
        Node* remove_leaf(Node* &root, K key)
        {
            //BST remove_leaf
            if(root == nullptr)
            {
                return root;
            }
            
            if(equals(key, root -> key)) //if key == root -> key
            {
                if(root -> left == nullptr && root -> right == nullptr) //no children
                {
                    curr = root;
                    root = nullptr;
                    delete curr;
                }
                else if(root -> left == nullptr) //right child only
                {
                    curr = root -> right;
                    *root = *curr; //move contents to root
                    delete curr;
                }
                else if(root -> right == nullptr) //left child only
                {
                    curr = root -> left;
                    *root = *curr; //move contents to root
                    delete curr;
                }
                else //two children
                {
                    curr = inorder_successor(root -> right); //get inorder successor of right subtree
                    
                    root -> key = curr -> key; //shift smallest value in left subtree to root
                    root -> right = remove_leaf(root -> right, curr -> key); //delete lowest key
                }
            }
            else if(compare(key, root -> key)) //if key < root -> key
            {
                root -> left = remove_leaf(root -> left, key);
            }
            else
            {
                root -> right = remove_leaf(root -> right, key);
            }
            
            if(root == nullptr) //tree now empty after removal
            {
                return root;
            }
            
            //make AVL adjustments
            
            //update height
            root -> height = max(getHeight(root -> left), getHeight(root -> right)) + 1;
            
            //check balance factor
            int bf = getBalance(root);
            
            //rotate as needed
            if(bf > 1 && compare(key, root -> left -> key)) //left heavy & left insert
            {
                return LL(root); //rotate right
            }
            
            if(bf < -1 && !compare(key, root -> right -> key)) //right heavy & right insert
            {
                return RR(root); //rotate left
            }
            
            if(bf > 1 && !compare(key, root -> left -> key)) //left heavy & right insert
            {
                root -> left = RR(root -> left); //rotate left
                return LL(root); //then rotate right
            }
            
            if(bf < -1 && compare(key, root -> right -> key)) //right heavy & left insert
            {
                root -> right = LL(root -> right); //rotate right
                return RR(root); //then rotate left
            }
            
            return root;            
        }
        
        Node* inorder_successor(Node* &root)
        {
            prev = root;
            
            while(prev -> left != nullptr) //find leftmost leaf
            {
                prev = prev -> left;
            }
            
            return prev;
        }
        
        V lookup(K key)
        {
            //lookup iteratively
            curr = root;
            prev = nullptr;
            
            if(root == nullptr) //if tree empty
            {
                return -1; //key does not exist
            }
            
            while(curr != nullptr)
            {
                prev = curr;
                
                if(equals(key, curr -> key))
                {
                    return curr -> value;
                }
                else if(compare(key, curr -> key)) //if key < curr -> key
                {
                    curr = curr -> left;
                }
                else
                {
                    curr = curr -> right;
                }
            }
            
            return -1; //key does not exist
            
        }
        
        void print()
        {
            print_preorder(root);
            //print_inorder(root);
            cout << endl;
        }
        
        Node* print_inorder(Node* &root) //print inorder
        {
            if(root != nullptr)
            {
                print_inorder(root -> left);
                cout << root -> key << " ";
                print_inorder(root -> right);
            }
            
            return root;
        }
        
        Node* print_preorder(Node* &root) //print prenorder
        {
            if(root != nullptr)
            {
                cout << root -> key << " ";
                print_preorder(root -> left);
                print_preorder(root -> right);
            }
            
            return root;
        }
        
        Node* clear(Node* &root)
        {
            curr = root;
            if(root == nullptr)
            {
                return curr;
            }
            
            clear(root -> left);
            clear(root -> right);
            
            root = nullptr;
            delete curr;
            
            return root;
        }
    };
    
}


#endif /* avl_h */
