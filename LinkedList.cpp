#include <iostream>
using namespace std;

class Node {
    private:
    Node *next;
    Node *previous;
    int data;
    
    public:
    Node (int d){
        data = d;
        next = nullptr;
        previous = nullptr;
        
    }
    Node (){
        next = previous = nullptr;
        
    }
friend class LinkedList;
};


class LinkedList{
private:
Node *head;
Node *tail;
int size;
public:
LinkedList(){
    head = tail = nullptr;
    size = 0;
}

void addNodeAtHead(int d){
    Node *newNode = new Node (d);
    newNode->next = head;
    head = newNode;
    size++;
}
void addNodeAtTail (int d){
    Node *temp= head;
    Node *newNode = new Node (d);
if (head==nullptr){
head = newNode;
size++;
return;
}
while (temp->next!=nullptr){
    temp = temp->next;
}
temp->next = newNode;
newNode->previous=temp;
size++;
}
void displayLists(){
    Node *temp = head;
    while (temp!=nullptr){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl << size;
}
void Delete(int d){
    Node *temp = head;
    Node *prev = head;
    if (head == nullptr){
        cout << "Cannot delete empty linked list";
        return;
    }
    while (temp->next !=nullptr && temp->data!=d){
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    temp->next->previous = prev;
    size--;
    delete temp;

}


void reverseKNodes(int k){
    
    Node * temp = head;
   int count =0;

   while ((count + k) < size-1)
   {
    Node *start, *end, *end2;
    int i=0;
    start = temp;
    end = start;
    while (i<k-1){
        end = end->next;
        i++;
        count ++;
    }
    end2 = end;
    while (end->next != start && start!=end){
        swap (end->data, start->data);
        end = end->previous;
        start = start->next;
    }
    temp = end2->next;
}
}

};
int main(){
LinkedList L;
L.addNodeAtHead (1);
L.addNodeAtHead(2);
L.addNodeAtHead(3);
L.addNodeAtHead(4);
L.addNodeAtHead(5);
L.reverseKNodes(4);

L.displayLists();

}