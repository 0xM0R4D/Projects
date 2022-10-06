/*
This code for performing operations on strings, such as printing parts of one string (parts seperated by space) as seperated lines,
 checking validation of replacing String parts(ex: if a name: Mohamed Mahmoud Mourad, replacing(1,4) is false but replacing(1,3) is true;
 because my name contains only 3 parts).
*/
#include <iostream>
#include <vector>

using namespace std ;

class StudentName {
private:
    string name ;

public:
    vector<string>vec ;
    int vecCnt=0 ;

    StudentName(string =" " );    // parametarized constructor prototype
    void printNameParts(vector<string>&vec) ;    // print name parts function prototype
    bool replace(int ,int) ;    // replace function prototype
    void setName(string);  // setName function prototype
    string getName();   // getName function prototype
//    void printChecker(vector<string>&vec) ;      // only for testing
};

// parametarized constructor
StudentName::StudentName(string str ) {
    vec.push_back("");
    name = str ;
    bool spaceFlag = false ;
    for(int i=0; i<name.size(); i++){
        if (name[i]==' ' && spaceFlag==false){ // case: there is space after the specific part
            vec.push_back("") ;
            vecCnt++ ;
            spaceFlag= true ;
        }

        else if (name[i]==' ' && spaceFlag==true) // case: multiple space, continue
            continue;

        else{   // not space, this means that the new part from the name
            vec[vecCnt]+= name[i] ;
            spaceFlag = false ;
        }
    }
    if(vec[vecCnt][0]==' '){   // check if last element  is empty string
        vecCnt-- ;
        vec.pop_back() ;
    }

    // check num of name parts
    if (vec.size()==2){
        vec.push_back(vec[1]) ;
        vecCnt++ ;
    }
    else if(vec.size()==1){
        vec.push_back(vec[0]) ;
        vec.push_back(vec[0]) ;
        vecCnt+=2 ;
    }
    // updating name
    name= "";
    for (int i =0 ;i<vec.size();i++)
        name+=vec[i]+" ";
}
// function prints seperated parts
void StudentName:: printNameParts(vector<string>&vec){
    this->vec = vec ;
    for(int i=0;i<this->vec.size(); i++)
        cout<< i+1<<")"<<this->vec[i]<<"\n" ;
}

// replace function
bool StudentName::replace(int startPos, int endPos) {
    return (startPos-1>=0 && endPos-1<vec.size() ) ;
}

// getName function
string StudentName::getName() {
    return name ;
}

// setName function
void StudentName::setName(string name) {
    this->name= name ;
}
//void StudentName:: printChecker(vector<string>&vec){     // only for testing
//    this->vec = vec ;
//    for(int i=0;i<this->vec.size(); i++)
//        cout<< this->vec[i]<<" " ;
//}

int main() {


    string name ;
    cout<< "Enter Your Name:";
    getline(cin, name) ;
//    name  = "mohamed mahmoud mourad" ;
    StudentName st(name) ;

    cout<< "Menu:\n";
    cout<< "1. Print The Name As Parts.\n" ;
    cout<< "2. Check Validation For Replacing Parts.\n";
    cout<< "3.Exit\n";
    while (true) {
        cout << "Choose what you want from this menu: ";
        int chosen;
        cin >> chosen;

        if (chosen == 1) {
            st.printNameParts(st.vec);
        }
        else if (chosen==2){
            cout<< "Enter Parts Location That You Check Replace Between Them(ex: 1 3):\n";
            int part1,part2;
            cin>> part1>> part2;
            if(st.replace(part1,part2))
                cout<< "Replacing for "<<st.getName()<<" Is Valid.\n" ;
            else
                cout<< "Replacing for "<<st.getName()<<" Not Valid.\n";

        }
        else if (chosen==3)
            exit(0);
        else{
            cout<< "Chosen Not Found, Plz choose correct chosen from the menu.\n";
        }
    }

    return 0;
}
