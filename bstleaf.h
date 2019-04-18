//
//  bstleaf.h
//  Project2
//
//  Created by Alexis Athens on 12/1/17.
//  Copyright © 2017 Alexis Athens. All rights reserved.
//

#ifndef bstleaf_h
#define bstleaf_h
#include <iostream>

using namespace std;

namespace cop3530
{
    template<typename K, typename V, bool (*compare)(K,K), bool (*equals)(K,K)>
    class Leaf
    {
    private:
        
        struct Node
        {
            K key;
            V value;
            Node* left;
            Node* right;
            Node(K key, V value)
            {
                this -> key = key;
                this -> value = value;
                left = nullptr;
                right = nullptr;
            }
        };
        Node* root;
        Node* curr;
        Node* prev;
        V temp;
        
    public:
        Leaf()
        {
            root = nullptr;
            curr = nullptr;
            prev = nullptr;
        }
        
        Leaf(const Leaf &src) //copy constructor
        {
            root = nullptr;
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
        
        Leaf(Leaf &&src) //move constructor
        {
            root = src.root;
            src.root = nullptr;
        }
        
        Leaf<K, V, compare, equals>& operator=(Leaf& src) //copy assignment
        {
            if(this == &src)
            {
                return *this;
            }
            clear(root);
            root = nullptr;
            root = src.copy_BST(src.root);
        }
        
        Leaf<K, V, compare, equals>& operator=(Leaf&& src) //move assignment
        {
            if(this == &src)
            {
                return *this;
            }
            clear(root);
            root = src.root;
            src.root = nullptr;
        }
        
        ~Leaf()
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
            if(root == nullptr) //create new node
            {
                root = new Node(key, value);
                return root;
            }
            
            if(equals(key, root -> key)) //if key == root -> key, update
            {
                root -> value = value;
            }
            else if(compare(key, root -> key)) //if key < root -> key
            {
                insert_leaf(root -> left, key, value);
            }
            else
            {
                insert_leaf(root -> right, key, value);
            }

            return root;
        }
    
        V remove(K key)
        {
            if(root == nullptr)
            {
                throw runtime_error("Error, tree does not exist");
            }
            
            if(lookup(key) != 0) //if key is valid
            {
                remove_leaf(root, key);
                return 1; //success
            }
            else //key does not exist in tree
            {
                return 0;
            }

        }
    
        Node* remove_leaf(Node* &root, K key)
        {
            if(root == nullptr) //base case
            {
                return root;
            }
            
            if(equals(key, root -> key)) //if key == root -> key
            {
                if(root -> left == nullptr) //if only has right child / no children
                {
                    //cout << "Deleting " << root -> key << endl;
                    curr = root -> right;
                    delete root;
                    return curr;
                }
                else if(root -> right == nullptr) //if only has left child
                {
                    //cout << "Deleting " << root -> key << endl;
                    curr = root -> left;
                    delete root;
                    return curr;
                }
                
                //else has two children
                curr = inorder_successor(root -> right); //get inorder successor of right subtree
                
                root -> key = curr -> key; //shift smallest value in left subtree to root
                root -> right = remove_leaf(root -> right, curr -> key); //delete lowest key
            }
            else if(compare(key, root -> key)) //if key < root -> key
            {
                root -> left = remove_leaf(root -> left, key);
            }
            else
            {
                root -> right = remove_leaf(root -> right, key);
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
                return 0; //key does not exist
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
            
            return 0; //key does not exist
        }
        
        V getLC(K key) //given a certain key, find its left child
        {
            //lookup iteratively
            curr = root;
            prev = nullptr;
            
            if(root == nullptr) //if tree empty
            {
                return 0; //key does not exist
            }
            
            while(curr != nullptr)
            {
                prev = curr;
                
                if(equals(key, curr -> key))
                {
                    curr = curr -> left;
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
            
            return 0; //key does not exist
        }
        
        V getRC(K key) //given a certain key, find its left child
        {
            //lookup iteratively
            curr = root;
            prev = nullptr;
            
            if(root == nullptr) //if tree empty
            {
                return 0; //key does not exist
            }
            
            while(curr != nullptr)
            {
                prev = curr;
                
                if(equals(key, curr -> key))
                {
                    curr = curr -> right;
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
            
            return 0; //key does not exist
        }

        
        Node* traverse(Node* &root, K key) //preorder traversal, finding given key
        {
            if(root -> key != key)
            {
                traverse(root -> left);
                traverse(root -> right);
            }
            
            return root;
        }
        
        void print()
        {
            print_preorder(root);
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
        
        Node* print_preorder(Node* &root) //print preorder
        {
            if(this -> root == nullptr)
            {
                cout << "List empty" << endl;
            }
            
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


#endif /* bstleaf_h */
