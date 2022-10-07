/*
This code is a linked list class similar to that provided in the C++ STL, also it contains an iterator class as 
 an inner class in order to access the data stored in the list.
*/
#include <iostream>
using namespace std ;

template<class Type>
struct node {
    Type value ;
    node * next ;
    node * back ;
};

// MyList class
template<class Type>
class MyList {
private:
    node<Type> *first ;
    node<Type> * last ;
    int MyListSize ;

public:
    MyList() ;          // default constructor prototype
    MyList(Type, int) ;     // parameterized constructor prototype
    ~MyList() ;             // destructor
    const int size()  ;     // size function prototype

// inner iterator class
    template<class >
    class MyListIterator {
    public:
        node<Type>*nodeIt ;

        MyListIterator(){       // default constructor for iterator class
            nodeIt =NULL ;
        }

        void operator++(){      // prefix operator ++ (ex: ++it )
            if(nodeIt->next->next == NULL)
                throw"Error: iterator cannot iterate after this node\n";
            nodeIt = nodeIt->next ;
        }

        void operator++(Type){      // postfix operator ++ (ex: it++ )
            if(nodeIt->next->next == NULL)
                throw"Error: iterator cannot iterate after this node\n";
            nodeIt = nodeIt->next ;
        }

        void operator--(){      // prefix operator -- (ex: --it )
            if(nodeIt->back == NULL)
                throw"Error: iterator cannot iterate before this node\n";
            nodeIt = nodeIt->back ;
        }

        void operator--(Type){      // postfix operator -- (ex: it-- )
            if(nodeIt->back == NULL)
                throw"Error: iterator cannot iterate before this node\n";
            nodeIt = nodeIt->back ;
        }

        Type & operator*(){         // dereference operator
            return nodeIt->value ;
        }

        bool operator == (const MyListIterator<Type>& it2) {        // == operator
            return nodeIt==it2.nodeIt ;
        }

    };

    // begin function
    MyListIterator<Type> begin(){
        MyListIterator<Type> itBegin ;
        itBegin.nodeIt = first ;
        return itBegin ;
    }

    // end function
    MyListIterator<Type> end() {
        MyListIterator<Type> itEnd ;

        itEnd.nodeIt= last->next ;

        return itEnd ;
    }

    // erase function
    MyListIterator<Type> erase (MyListIterator<Type>& it ){     // erase function

        MyListIterator<Type> resIt ;

        if(it.nodeIt->next==NULL)     //  endNode =null
            throw "Error: cannot erase the end node \n" ;

        if(it.nodeIt== first){

            first=first->next ;
            first->back = NULL ;
            resIt.nodeIt = first ;
        }
        else if (it.nodeIt== last){
            last= last->back ;
            resIt.nodeIt = NULL ;
        }
        else{
            node<Type> *node1, *node2 ;
            node1 = it.nodeIt->back ;
            node2 = it.nodeIt->next ;
            node1->next = node2 ;
            node2->back = node1 ;
            resIt.nodeIt = node2 ;
        }

        MyListSize-- ;
        delete it.nodeIt ;
        return  resIt ;
    }

    //  insert function prototype
    void insert(Type, MyListIterator<Type>&) ;

    MyList<Type>& operator =(const MyList <Type>&);   // = operator prototype  for lists


};

// definitions of MyList class

// default constructor
template <class Type >
MyList<Type>:: MyList(){
    first = last = NULL ;
    MyListSize= 0 ;
}

// parametrized constructor
template<class Type >
MyList<Type> :: MyList(Type val , int initialSize){
    MyListSize= initialSize ;
    node<Type> *node1 ;
    node1 = new node<Type> ;    // create the first node in the list
    node1->value = val ;
    node1->next = NULL ;
    node1->back = NULL ;
    first = node1 ;
    last = node1 ;

    initialSize-- ;

    node<Type> *node2 ;
    while (initialSize--){
        node2 = new node<Type> ;
        node2->value = val ;
        node2->back = node1 ;
        node1->next = node2 ;
        node2->next = NULL ;
        last = node2 ;
        node1 = node2 ;
    }
    node<Type>*endNode=new node<Type> ;
    last->next = endNode ;
    endNode->back = last ;
    endNode->next = NULL ;

}

// MyList destructor
template<class Type>
MyList<Type>::~MyList(){
    node<Type>* deletedNode ;

    while(first!=NULL){         // deleting nodes starting from first node in the list
        deletedNode = first ;
        first= first->next ;
        delete deletedNode ;
    }
    // after finishing first=last = NULL
    MyListSize = 0 ;
}

// size function
template<class Type>
const int MyList<Type>::size(){
    return MyListSize ;
}

// insert function
template <class Type>
void MyList<Type>::insert(Type val , MyListIterator<Type>  &it) {

    if(it.nodeIt== first){
        node<Type>*newNode = new node<Type> ;
        newNode->value= val ;
        newNode->next= first ;
        first->back = newNode ;
        first = newNode ;
        newNode->back = NULL ;
    }
    else if (it.nodeIt== last){
        node<Type>*newNode = new node<Type> ;
        newNode->value= val ;
        newNode->back = last ;
        last->next = newNode ;
        last = newNode ;
    }
    else{
        node<Type>*node1  ; // node before it
        node1 = it.nodeIt->back ;
        node<Type>*newNode ;
        newNode= new node<Type>;
        newNode->value = val ;
        newNode->back = node1 ;
        node1->next = newNode ;
        newNode->next = it.nodeIt ;
    }

    MyListSize++ ;
}

// = operator for list  (assignment operator)
template<class Type>
MyList<Type>& MyList<Type>::operator=(const MyList<Type> & mainlyList) {

    int cnt = mainlyList.MyListSize ;  // variable to know size of newList
    node<Type>*node1 = new node<Type> ;
    node1->value =mainlyList.first->value ;
    first = node1 ;
    last = node1 ;
    cnt-- ;     // first node was created

    node<Type>* node2 ;

    node<Type> *traverser= mainlyList.first ;      // to traverse in mainly list (point to next node )
    while (cnt--){
        traverser = traverser->next ;  // move to next node
        node2 = new node<Type> ;
        node1->next = node2 ;
        node2->back = node1 ;
        node2->value = traverser->value ;
        last = node2 ;
        node1 = node2 ;
    }
    MyListSize = mainlyList.MyListSize ;

    node<Type>*endNode=new node<Type> ;
    last->next = endNode ;
    endNode->back = last ;
    endNode->next = NULL ;

    return *this ;
}

int main() {

    // testing
    MyList<int>list1(50,3) ;    // test parametrized constructor
    MyList<int>list2 ;      // test default constructor
    list2 = list1 ;     // test assignment operator

    cout<< "list1 size: "<< list1.size() <<"\n" ;     // test size function
    cout<< "list2 size: "<< list2.size() <<"\n" ;

    MyList<int> :: MyListIterator<int> it ;
    it = list1.begin() ; // test begin function
    list1.insert(55,it) ;   // test insert function
    cout<<"size of list1 after adding node with value 55 at begin: "<< list1.size()<<endl;

    it = list1.begin() ;
    *it += 5 ; // test dereference operator
    cout<< "value of the first node after adding 5 to it: "<< *it << endl;

    it = list1.end() ; // test end function
    if (it==list1.end())// test == operator
        cout<< "(true condition)this iterator points to the end node\n" ;

    try {
        it= list1.end()  ;
        it-- ;      // test --operator  (now the iterator points to the last node)
        cout<< "value of the last node(accessed by --operator): "<< *it <<endl;

        it = list1.begin() ;
        it++ ; // test ++ operator
        cout<< "The second node (accessed by ++operator): "<< *it<< endl;

        list1.erase(it) ;
        cout<< "size of list1 after erasing one node: "<< list1.size() << endl;

        it = list1.end();
        list1.erase(it) ;    // try to erase the end node

    }
    catch (const char * msg){
        cerr<< msg <<endl;
    }
    cout<< "all is done\n" ;

    return 0;
}
