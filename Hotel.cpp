#include <iostream>
#include <fstream>
#include <stdlib.h> 
using namespace std;

ofstream RoomFile("Room_Reservation.txt");
ofstream RestaurantFile("Restaurant_order.txt");
ofstream CustomerFile("Customer_order.txt");

int reservation_count = 0,total = 0;
 
class Rooms;
class Services;

class Hotel{
    public:
        int ID,no_of_family_members,time_of_stay,outstanding_payment ;
        string First_name, Second_name;
        Hotel*next;
        Hotel*prev;
        Hotel(int ID,string First_name,string Second_name,int no_of_family_members,int time_of_stay){
            next = NULL;
            prev = NULL;
            this->ID = ID;
            this->First_name = First_name;
            this->Second_name = Second_name;
            this->no_of_family_members = no_of_family_members;
            this->time_of_stay = time_of_stay;
            this->outstanding_payment = 0;
        }
};
        void addathead(Hotel*&tail, Hotel*&head ,int ID,string First_name,string Second_name,int no_of_family_members,int time_of_stay){
            if(reservation_count<=19){
                Hotel*temp = new Hotel(ID,First_name,Second_name,no_of_family_members,time_of_stay);
                if(tail==NULL){
                    head=tail=temp;
                    return;
                }
                else{
                    temp->next = head;
                    head->prev = temp;
                    head = temp;
                    reservation_count++;
                }
            }
            else{
                cout<<"Hotel Full, No further reservations can be made!"<<endl;
            }
        }
        void deletefromtail(Hotel*&tail){
            if(tail!=NULL){
            Hotel*del = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete del;
            reservation_count--;
            }
        }
       
        void searchinLL(Hotel*&head,int cni){
            if(head!=NULL){
            Hotel*temp = head;
            while(temp!=NULL){
                if(temp->ID == cni){
                cout<<"ID Found"<<endl;
                return;
            }
            temp = temp->next;
            }
            cout<<"ID Not Found"<<endl;
            }
        }

        void sortrecords(Hotel*&head){
            if(head!=NULL){
                Hotel*current = head;
                while(current->next!=NULL){
                    Hotel*currloc = current->next;
                    while(currloc!=NULL){
                        if((current->ID)>(currloc->ID)){
                            Hotel*temp = new Hotel(0,"","",0,0);
                            temp->ID = current->ID;
                            current->ID = currloc->ID;
                            currloc->ID = temp->ID;
                            currloc = currloc->next;
                            current = current->next;
                        }
                    }
                }
            }
        }

        void display(Hotel*&head){
            Hotel*temp = head;
            while(temp!=NULL){
            cout<<"ID: "<<temp->ID<<endl;
            cout<<"First Name: "<<temp->First_name<<endl;
            cout<<"Last Name: "<<temp->Second_name<<endl;
            cout<<"Outstanding Payment-> "<<temp->outstanding_payment<<endl;
            cout<<endl;
            cout<<endl;
            temp = temp->next;
        }
    }






class Rooms{
    
    public:
    void single_room(Hotel*&head){
        head->outstanding_payment = head->outstanding_payment + (20*head->time_of_stay);
    }
    void double_room(Hotel*&head){
        head->outstanding_payment = head->outstanding_payment + (40*head->time_of_stay);
    }
    void connecting_room(Hotel*&head){
        head->outstanding_payment = head->outstanding_payment + (100*head->time_of_stay);
    }
};

class Services{
    public:
    void room_laundry(Hotel*&head){
        head->outstanding_payment = head->outstanding_payment + (15*head->no_of_family_members);
    }
    void room_makeup(Hotel*&head){
        head->outstanding_payment = head->outstanding_payment + 20;
    }
    void room_eatery(Hotel*&head){
        head->outstanding_payment = head->outstanding_payment + (7*head->no_of_family_members);
    }
};



class restaurant{
    public:
    int data;
    restaurant*next;
    restaurant(int d){
        data = d;
        next = NULL;
    }
};

void enqueue(restaurant*&tail, restaurant*&head, int d){
    restaurant*temp = new restaurant(d);
    if (tail == NULL) {
            head = tail = temp;
            return;
    }
    else{
    tail->next = temp;
    tail = temp;
    }
}

int deque(restaurant*&head){
    if(head!=NULL){
        int ret = head->data;
        restaurant*del = head;
        head = head->next;
        delete del;
        return ret;
    }
}

void servedlist_orderlist(restaurant*head){
    restaurant*temp = head;
    if(temp!=NULL){
        cout<<"1:Mortadella/2:Grilledchicken/3:BBQ-----1:Flat/2:Fat/3:Wheat-----1:Rancher/2:Cheese/3:Meat/4:None"<<endl;
        cout<<"-->"<<endl;
    }
    while(temp!=NULL){
        cout<<"Order# "<<temp->data<<endl;
        cout<<endl;
        temp = temp->next;
    }
}

void serve_the_order(restaurant*&tails,restaurant*&heads, restaurant*&heado){
    if(heado!=NULL){
        enqueue(tails,heads,deque(heado));
    }
}

void new_order(restaurant*&tailo,restaurant*&heado){
    int terminate = 0;
    int flavor=1,dough = 1, topping = 1;
    do{
        cout<<"---------Menu----------"<<endl;
        do{
        cout<<"<-Select Pizza Flavor->"<<endl;
        cout<<"Enter 1 for MORTADELLA"<<endl;
        cout<<"Enter 2 for GRILLED CHICKEN"<<endl;
        cout<<"Enter 3 for BBQ"<<endl;
        cin>>flavor;
        }while(flavor<1 || flavor>3);
        do{
        cout<<"<-Select Pizza Dough->"<<endl;
        cout<<"Enter 1 for Flat pan"<<endl;
        cout<<"Enter 2 for Fat dough"<<endl;
        cout<<"Enter 3 for Whole Wheat"<<endl;
        cin>>dough;
        }while(dough<1 || dough>3);
        do{
        cout<<"<-Select Extra Toppings->"<<endl;
        cout<<"Enter 1 for Rancher Sauce"<<endl;
        cout<<"Enter 2 for Extra Cheese"<<endl;
        cout<<"Enter 3 for Extra meat"<<endl;
        cout<<"Enter 4 for No Extra topping"<<endl;
        cin>>topping;
        }while (topping<1 || topping>4);
        int d = (flavor*100) + (dough*10) + topping;
        RestaurantFile<<"Order: "<<d<<endl;
        enqueue(tailo,heado,d);
        cout<<"To finish order press -1, else press 0 !"<<endl;
        cin>>terminate;
    }while(terminate != -1);
}

class book{
public:
string title,author;
int ISBN,price;
book*right;
book*left;
book(int isb,string a, string t,int p){
ISBN = isb;
title = t;
author = a;
price = p;
right = left = NULL;
}
};
book* insert_in_bst(book*&root, int isb,string a, string t,int p){
if(root == NULL){
root = new book(isb,a,t,p);
return root;
}
if(isb > root->ISBN){
root->right = insert_in_bst(root->right,isb,a,t,p);
}
else{
root->left = insert_in_bst(root->left,isb,a,t,p);
}
return root;
}
void take_input(book*&root){
cout<<"Insert a number in ISBN then press enter, else if you want to exit,press -1 in ISBN,AUTHOR,TITLE, and enter!"<<endl;
int isbn,p;
string a,t;
while( isbn != -1){
insert_in_bst(root,isbn,a,t,p);
cout<<"ISBN: ";
cin>>isbn;
cout<<"Author: ";
cin>>a;
cout<<"Title: ";
cin>>t;
cout<<"Price: ";
cin>>p;

}
}
int min_value(book*&root){
book*temp = root;
while(temp->left!=NULL){
temp = temp->left;
}
return temp->ISBN;
}
book* delete_in_bst(book*&root, int isb){
if(root == NULL){
return NULL;
}
if (root->ISBN == isb){
if(root->left == NULL && root->right == NULL){
delete root;
return NULL;
}
if(root->left == NULL && root->right != NULL){
book*temp = root->right;
delete root;
return temp;
}
if(root->left != NULL && root->right == NULL){
book*temp = root->left;
delete root;
return temp;
}
if(root->left != NULL && root->right != NULL){
int min = min_value(root);
root->ISBN = min;
root->right = delete_in_bst(root->right,min);
return root;
}
}
else if(root->ISBN > isb){
root->left = delete_in_bst(root->left,isb);
return root;
}
else{
root->right = delete_in_bst(root->right,isb);
return root;
}
}
bool search_data(book*root, int isb){
book*temp = root;
while(temp!=NULL){
if(temp->ISBN == isb){
return true;
}
if(isb < temp->ISBN){
temp = temp->left;
}
else{
temp = temp->right;
}
}
return false;
}
void inorder(book* root) {
if(root == NULL) {
return;
}
inorder(root->left);
cout <<"ISBN: "<< root-> ISBN <<endl;
cout <<"Author: "<< root-> author <<endl;
cout <<"Title: "<< root-> title <<endl;
cout <<"Price: "<< root->price <<endl;
cout<<endl;
inorder(root->right);
}
void preorder(book* root) {
if(root == NULL) {
return;
}
cout <<"ISBN: "<< root-> ISBN <<endl;
cout <<"Author: "<< root-> author <<endl;
cout <<"Title: "<< root-> title <<endl;
cout <<"Price: "<< root->price <<endl;
cout<<endl;
preorder(root->left);
preorder(root->right);
}
void postorder(book* root) {
if(root == NULL) {
return;
}
postorder(root->left);
postorder(root->right);
cout <<"ISBN: "<< root-> ISBN <<endl;
cout <<"Author: "<< root-> author <<endl;
cout <<"Title: "<< root-> title <<endl;
cout <<"Price: "<< root->price <<endl;
cout<<endl;
}

void enque(book*&tail, book*&head, book*root, int isb){
bool flag=false;
book*tempo = root;
while(tempo!=NULL){
if(tempo->ISBN == isb){
flag=true;
break;
}
if(isb < tempo->ISBN){
tempo = tempo->left;
}
else{
tempo = tempo->right;
}
}

    if(flag==true){
    book*temp = new book(tempo->ISBN,tempo->author,tempo->title,tempo->price);
    if (tail == NULL) {
            head = tail = temp;
            return;
    }
    else{
    tail->right = temp;
    tail = temp;
    }
    }
}

void deque(book*&head){
    if(head!=NULL){
        book*del = head;
        head = head->right;
        delete del;
    }
}

void recommendationdisplay(book*&head){
    book*temp = head;
    if(temp!=NULL){
        cout<<"Book Recommendations by Seller: "<<endl;
    }
    while(temp!=NULL){
        cout<<"ISBN: "<<temp->ISBN<<endl;
        cout<<endl;
        temp = temp->right;
    }
}


//---------------------------------------------------------------------
class customer{
    public:
    int isbnn;
    string customername;
    customer*next;
    customer(int d, string cn){
        isbnn = d;
        customername =cn;
        next = NULL;
    }
};

void enqueuebookorder(customer*&tail, customer*&head,int d, string cn){
    customer*temp = new customer(d,cn);
    if (tail == NULL) {
            head = tail = temp;
            return;
    }
    else{
    tail->next = temp;
    tail = temp;
    }
}

void dequebookorder(customer*&head){
    if(head!=NULL){
        customer*del = head;
        head = head->next;
        delete del;
    }
}

void outstanding_orders(customer*head){
    while (head!=NULL)
    {
        cout<<"Customer name: "<<head->customername<<endl;
        cout<<"Book ISBN: "<<head->isbnn<<endl;
        head=head->next;
    } 
}

void outstanding_book_payment(int isb,book*root){
    book*temp = root;
    while(temp!=NULL){
        if(temp->ISBN == isb){
        total=total+temp->price;
        }
        if(isb < temp->ISBN){
        temp = temp->left;
        }
        else{
        temp = temp->right;
        }
    }
}

int main(){

int type = 0;
cout<<endl;
cout<<"<---Welcome to Hotel Aryaduta Management System--->"<<endl;
cout<<"~If you are a Hotel Reservation Manager, press 1!"<<endl;
cout<<"~If you are a Restaurant order Manager, press 2!"<<endl;
cout<<"~If you are a Bookstore Manager, press 3!"<<endl;
cin>>type;
if(type==1){
   
    system("cls");
    int choice = 1;
    int ID, no_of_family_members,time_of_stay,outstanding_payment ;
    string First_name, Second_name;
    Hotel*head = NULL;
    Hotel*tail = NULL;
    cout<<endl;
    cout<<">>>> Welcome To Management Panel <<<<"<<endl;
    while(choice>=1 && choice<=5){
        cout<<"         Panel of Instructions: "<<endl;
        cout<<"Press 1 for Adding another customer in reservation queue"<<endl;
        cout<<"Press 2 for deleting at tail, the satisfied customer"<<endl;
        cout<<"Press 3 for Searching a customer's details "<<endl;
        cout<<"Press 4 for Sorting customer reservation for display purposes"<<endl;
        cout<<"Press 5 for Displaying the reservation confrimed Customers"<<endl;
        cout<<"Press 6 for TERMINATING PROGRAM"<<endl;

        cout<<endl;
        cin>>choice;
        cout<<endl;
        if(choice == 1){
            cout<<" Dear Receptionist, please enter your Customer's "<<endl;
            cout<<"ID: ";
            cin>>ID;
            RoomFile<<"ID: "<<ID<<endl;
            cout<<"First Name: ";
            cin>>First_name;
            RoomFile<<"First_name: "<<First_name<<endl;;
            cout<<"Last Name: ";
            cin>>Second_name;
            RoomFile<<"Second_name: "<<Second_name<<endl;
            cout<<"No. of Family Member: ";
            cin>>no_of_family_members;
            RoomFile<<"No_of_family_members: "<<no_of_family_members<<endl;
            cout<<"Duration of Stay: ";
            cin>>time_of_stay;
            RoomFile<<"Duration_of_stay: "<<time_of_stay<<endl;
            addathead(tail,head,ID,First_name,Second_name,no_of_family_members,time_of_stay);
            if(no_of_family_members == 1){
                Rooms c1;
                c1.single_room(head);
            }
            else if(no_of_family_members == 2){
                Rooms c1;
                c1.double_room(head);
            }
            else{
                Rooms c1;
                c1.connecting_room(head);
            }
            cout<<"Does the customer want services? Press Y/N: ";
            char choose;
            cin>>choose;
            if(choose == 'Y'){
                Services c1s;
                cout<<"Do you want to avail Eatery? Press Y/n: ";
                cin>>choose;
                if(choose = 'Y'){
                    c1s.room_eatery(head);
                }
                cout<<"Do you want to avail Laundry? Press Y/n: ";
                cin>>choose;
                if(choose = 'Y'){
                    c1s.room_laundry(head);
                }
                cout<<"Do you want to avail room makeup? Press Y/n: ";
                cin>>choose;
                if(choose = 'Y'){
                    c1s.room_makeup(head);
                }
            }
            RoomFile<<"Payment to be done: "<<head->outstanding_payment<<endl;
            RoomFile<<endl;
            cout<<"*DONE*"<<endl;
            cout<<endl;
        }
    
        if(choice == 2){
            deletefromtail(tail);
            cout<<"*DONE*"<<endl;
            cout<<endl;
        }
        if(choice == 3){
            cout<<"Enter ID to be searched: ";
            int num;
            cin>>num;
            searchinLL(head,num);
            cout<<"*DONE*"<<endl;
            cout<<endl;
        }
    
        if(choice == 4){
            sortrecords(head);
            cout<<"*DONE*"<<endl;
            cout<<endl;
        }
        if(choice == 5){
            display(head);
            cout<<"*DONE*"<<endl;
            cout<<endl;
        }
    }
    RoomFile.close();
}
else if(type==2){
    
    system("cls");
    restaurant*orderH = NULL;
    restaurant*orderT = NULL;
    restaurant*servedH = NULL;
    restaurant*servedT = NULL;
    int choice = 1;
    cout<<">>>> Welcome To Sardar Pizza Order System <<<<"<<endl;
    while(choice>=1 && choice<=4){
        cout<<"         Pallete of Commands: "<<endl;
        cout<<"Press 1 for checking Served Orders"<<endl;
        cout<<"Press 2 for checking Order list"<<endl;
        cout<<"Press 3 for serving the order"<<endl;
        cout<<"Press 4 for taking new order"<<endl;
        cout<<"Press 5 for TERMINATING PROGRAM"<<endl;
        
        cout<<endl;
        cin>>choice;
        cout<<endl;
        if(choice == 1){
            servedlist_orderlist(servedH);
            cout<<"*DONE*"<<endl;
            cout<<endl;
        }
        if(choice == 2){
            servedlist_orderlist(orderH);
            cout<<"*DONE*"<<endl;
            cout<<endl;
        }
        if(choice == 3){
            serve_the_order(servedT,servedH,orderH);
            cout<<"*DONE*"<<endl;
            cout<<endl;
        }
        if(choice == 4){
            new_order(orderT,orderH);
            cout<<"*DONE*"<<endl;
            cout<<endl;
        }
    }
    RestaurantFile.close();
}

else if(type==3){

    book*root = NULL;
    book*head = NULL;
    book*tail = NULL;

        int chosee = 1;
        system("cls");
        cout<<">>>> Welcome To inventory management system <<<<"<<endl;
        while(chosee>=1 && chosee<=7){
            cout<<"         Menu of Instructions: "<<endl;
            cout<<"Press 1 for Insertion"<<endl;
            cout<<"Press 2 for Deletion"<<endl;
            cout<<"Press 3 for Searching"<<endl;
            cout<<"Press 4 for finding Min ISBN"<<endl;
            cout<<"Press 5 for traversing in inorder"<<endl;
            cout<<"Press 6 for traversing in preorder"<<endl;
            cout<<"Press 7 for traversing in postorder"<<endl;
            cout<<"Press 8 for TERMINATING PROGRAM"<<endl;
        
            cout<<endl;
            cin>>chosee;
            cout<<endl;
            if(chosee == 1){
                take_input(root);
                cout<<"*DONE*"<<endl;
                cout<<endl;
            }
            if(chosee == 2){
                int num;
                cout<<"Enter Number you want to delete: ";
                cin>>num;
                delete_in_bst(root,num);
                cout<<"*DONE*"<<endl;
                cout<<endl;
            }
            if(chosee == 3){
                int num;
                cout<<"Enter Number you want to search: ";
                cin>>num;
                cout<<search_data(root,num);
                cout<<"*DONE*"<<endl;
                cout<<endl;
            }
            if(chosee == 4){
                cout<<"Min Value is: "<<min_value(root);

                cout<<"*DONE*"<<endl;
                cout<<endl;
            }
            if(chosee == 5){
                cout<<"Printing: "<<endl;
                inorder(root);
                cout<<"*DONE*"<<endl;
                cout<<endl;
            }
            if(chosee == 6){
                cout<<"Printing: "<<endl;
                preorder(root);
                cout<<"*DONE*"<<endl;
            cout<<endl;
            }
            if(chosee == 7){
            cout<<"Printing: "<<endl;
                postorder(root);
                cout<<"*DONE*"<<endl;
                cout<<endl;
            }
        }
        cout<<"If you want to update recommendation system, press 1, "<<endl;
        int reco;
        cin>>reco;
        if(reco==1){
            int choseee = 1;
            cout<<">>>> Welcome To Recommendation system <<<<"<<endl;
            while(choseee>=1 && choseee<=2){
                cout<<"         Menu of Instructions: "<<endl;
                cout<<"Press 1 for Insertion"<<endl;
                cout<<"Press 2 for Deletion"<<endl;
                cout<<"Press 3 to terminate system"<<endl;
                cout<<endl;
                cin>>choseee;
                if(choseee == 1){
                    cout<<"Enter ISBN of the book you want to add in hot sellers/Recommendation";
                    int isb;
                    cin>>isb;
                    enque(tail,head,root,isb);
                    cout<<"*DONE*"<<endl;
                    cout<<endl;
                }
                if(choseee == 2){
                    deque(head);
                    cout<<endl;
                }
            }
        }
        system("cls"); 
        cout<<">>>> Welcome To Customer management system <<<<"<<endl;
        cout<<endl;
        cout<<"<--Glossary of Books-->"<<endl;
        inorder(root);
        recommendationdisplay(head);

        customer*head1=NULL;
        customer*tail1=NULL;
        int choseeee = 1;
        while(choseeee>=1 && choseeee<=1){
                cout<<"         Menu of Instructions: "<<endl;
                cout<<"Press 1 to add an order"<<endl;
                cout<<"Press 2 to terminate system"<<endl;
                cout<<endl;
                cin>>choseeee;
                if(choseeee == 1){
                    total=0;
                    cout<<"Enter Customer Name: ";
                    string customernam;
                    cin>>customernam;
                    int buymore=0;
                    do{
                        cout<<"Enter Book ISBN that he wants to buy: ";
                        int isb;    
                        cin>>isb;
                        enqueuebookorder(tail1,head1,isb,customernam);
                        outstanding_book_payment(isb,root);
                        cout<<"Want to buy another book?, press 1: ";
                        cin>>buymore;   
                    }while(buymore==1);
                    cout<<endl;
                    outstanding_orders(head1);
                    cout<<"Total payment: "<<total<<endl;
                    CustomerFile<<"Total payment: "<<total<<endl;
                    cout<<endl;
                    while(head1!=NULL){
                        dequebookorder(head1);
                    }
                    cout<<"*DONE*"<<endl;
                    cout<<endl;
                }
            }
    }
  
CustomerFile.close();
RoomFile.close();
RestaurantFile.close();
}
