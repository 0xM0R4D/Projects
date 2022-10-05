/*
Online Shopping System Project
 This system used by store seller, seller can add items in its store, sell items, search an item by its id and do other functions.
 */
#include <iostream>
using namespace std ;
class Item {
    string name ;
    int quantity ;
    double price ;
    int ID ;

public:
    static int generatedID  ;

    Item(){                                 // default constructor

        ID= generatedID ;
        generatedID++ ;
        name = "" ;
        quantity = 0 ;
        price= 0.0 ;
    }
    Item (string name , int quantity, double price){                        // parameterize constructor
        this->name = name ;
        this->quantity = quantity ;
        this->price = price ;
        this->ID = generatedID ;
        generatedID++ ;
    }

    Item(const Item &obj){                           // copy constructor
        name=obj.name ;
        quantity = obj.quantity ;
        price = obj.price;
        ID = obj.ID ;
    }

    // setters
    void setName(string name){
        this->name = name ;
    }
    void setQuantity (int quantity){
        this ->quantity = quantity;
    }
    void setPrice (double price ){
        this ->price = price ;
    }
    void setID(){
        this->ID = generatedID  ;
        generatedID++ ;
    }

    // getters
    string getName (){
        return name ;
    }
    int getQuantity(){
        return quantity;
    }
    double getPrice(){
        return price ;
    }
    int getID(){
        return ID ;
    }

    // == operator checks whether the item is found or not
    bool operator ==(const Item& ob){
        return(name==ob.name) ;
    }
    // += operator to increase quantity of items
    Item operator +=(const Item& ob){
        quantity += ob.quantity;
        return *this ;
    }
    // -= operator to decrease quantity of items
    Item operator -=(const Item& ob){
        quantity -=ob.quantity;
        return *this ;
    }
    // >> operator to read whole item
    friend istream& operator >> (istream& input,Item& ob){
        input>> ob.name>> ob.quantity>> ob.price ;
        return input ;
    }
    // << operator to output whole item
    friend ostream& operator<<(ostream& os ,const Item& ob){
        os << "Item Info.:\n" ;
        os <<"Item name: "<<ob.name<<"  ,Quantity: "<< ob.quantity<<"   ,Price: "<< ob.price<<"   ,ID: "<< ob.ID<<"\n";

        return os ;
    }

};

class Seller {

    string name ;
    string email ;
    int maxItems ;
    Item *items ;

public:
    Seller(string name =" " ,string email=" " ,int maxItems = 0 ){
        this->maxItems = maxItems ;
        items = new Item[this->maxItems] ;                               // dynamic array of item
        this ->name = name ;
        this ->email = email ;
        items[0].generatedID-= (maxItems-1) ;
    }

    static int inputCnt ;                                          //  counts items will be added by user (in addItem function)

    friend ostream& operator<<(ostream& output,const Seller& ob){
        output<< "Seller name: "<<ob.name<< "  ,email: "<< ob.email<<"  ,Capacity: "<<ob.maxItems<<"\n";

        return  output ;
    }

    bool addItem(Item ob){
        bool flag =0 ;                                 // to check if item found or no
        for (int i=0 ; i<inputCnt; i++){
            if(ob==items[i]){
                items[i]+= ob ;
                flag =1 ;
                break;
            }
        }

        if (flag==0 && inputCnt<maxItems){          // if item not found and there is place in items(arr of items), add item
            items[inputCnt] =ob ;
            items[inputCnt].setID() ;
            inputCnt++ ;
            flag =1;
        }

        return flag ;
    }
    int onlyQuantity=0 ;
     void setOnlyQuantity(int only ){
         onlyQuantity = only ;
    }
    int getOnlyQuantity(){
        return onlyQuantity;
     }

    bool sellItem(string name , int quantity){

        Item soldItem ;
        soldItem.setName(name);
        soldItem.setQuantity(quantity) ;
        bool flag =false ;

        for (int i=0;i<inputCnt;i++){
            if(soldItem==items[i]){                          // to check if item already found or no
                if (soldItem.getQuantity()<=items[i].getQuantity()){
                    items[i]-=soldItem  ;
                    flag =true ;
                }
                else
                    setOnlyQuantity(items[i].getQuantity()) ;
                break;                                    // break ; because i found the item
            }
        }

        return flag ;                                     // flag is 1 : the item was found, else was not found
    }

    void printItems(){                             // print Items and their details
        for (int i=0; i<inputCnt;i++){
            cout<<items[i]<<endl;
        }
    }


    Item findItem(int id){

        return items[id-1];                    // because first item: its id=1, its index=0 and so on
    }

    ~Seller(){
        delete [] items ;
    }
};

int Item:: generatedID=0 ;
int Seller:: inputCnt= 0;

int main(){

    string name, email ;
    int capacity;
    cout<< "Hello Seller\nPLz, enter your name: " ;
    cin>> name ;
    cout<< "PLz, enter your email: ";
    cin>> email ;
    cout<< "PLz, enter your store capacity: ";
    cin>> capacity ;
    cout<< endl;

    Seller seller(name, email,capacity) ;

    cout<< "Menu:\n";
    cout<< "1. Print My info.\n" ;
    cout<< "2. Add An Item.\n";
    cout<< "3. Sell An Item.\n" ;
    cout<< "4. Print Items.\n" ;
    cout<< "5. Find an Item by ID.\n" ;
    cout<< "6. Exit.\n\n" ;

    while (true){
        cout<< "Choose what you want from this menu: " ;
        int chosen ; cin>> chosen ;

        if (chosen==1){
            cout<< seller<< endl ;
        }

        else if (chosen==2){
            cout<< "PLz, enter item name ,Quantity and price: " ;
            Item item ;
            item.generatedID-- ;
            cin>> item ;
            bool getAddItem = seller.addItem(item) ;
            if (getAddItem){
                cout<< "Successful Addition \n" ;
            }
            else
                cout<< "Failed Addition \n" ;
        }

        else if (chosen== 3){
            cout<<"PLz, enter item name and Quantity : " ;
            string name ;
            int quantity ;
            cin>> name>> quantity ;
            bool getSellItem = seller.sellItem(name, quantity) ;
            if (getSellItem== true){
                cout<< "sale done\n" ;
            }

            else {
                cout<< "Sale Not Done, There is only "<<seller.getOnlyQuantity()<<" left for this item\n";
            }

        }

        else if (chosen==4){
            seller.printItems() ;
        }

        else if (chosen==5){
            cout<< "PLz, enter the ID: " ;
            int id ; cin>> id ;
            cout<<"The item: "<< seller.findItem(id) << "\n";
        }
        else if (chosen == 6){
            cout<< "Thanks for using our program.\n" ;
            exit(0) ;
        }
        else
            cout<< "Wrong choice!!\nPLz, enter another number that must greater than or equal 1 and less than or equal 6\n";

    }

    return 0 ;
}
