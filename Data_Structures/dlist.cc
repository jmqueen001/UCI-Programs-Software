#include "dlist.h"
#include <cstddef>

DList::DList(){
    head = NULL;
    tail = NULL;
}

void DList::add_to_front(int value){
    ListNode* newNode = new ListNode();
    newNode->val = value;
    if(head == NULL){
        head = newNode;
    } 
    else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}
  
void DList::add_to_back(int value){
    ListNode* newNode = new ListNode();
    newNode->val = value;
    if(head == NULL){
        head = newNode;
    } 
    else{
        ListNode* currNode = head;
        while(currNode->next != NULL){
            currNode = currNode->next;
        }
        currNode->next = newNode;
        newNode->prev = currNode;
    }
}
int DList::first(){
    return head->val;
}
int DList::last(){
    if(head->val == NULL){
        return NULL;
    }
    ListNode* currNode = head;
    while(currNode->next != NULL){
        currNode = currNode->next;
    }
    return currNode->val;
}
void DList::remove(ListNode* node){
    if(node == NULL || head == NULL){
        return;
    }
    if(node == head){
        head = head->next;
    }
    if(node->next != NULL){
        node->next->prev = node->prev;
    }
    if(node->prev != NULL){
        node->prev->next = node->next;
    }
    delete node;

}
ListNode* DList:: previous(ListNode* node){
    if(node == NULL || node == head){
        return NULL;
    }
    return node->prev;

}
ListNode* DList::next(ListNode* node){
    if(node == NULL){
        return NULL;
    }
    return node->next;
}
ListNode* DList::search_value(int value){
    ListNode* currNode = head;
    while(currNode != NULL){
        if(currNode->val == value){
            return currNode;
        }
        currNode = currNode->next;
    }
}
