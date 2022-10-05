/*
This code read arrays from external file and perform tasks on it based on the asked input then display the output on another external file.
 example: if input: Sorted 3 10 3 7     output:  3| 3 7 10
 this means that the result array must be sorted. the first digit refer to size of array. and the reminded digits refer to elements of array 

 
 to use this code, firstly create .in file(say input.in) and add in it your input as the following:

Sorted 10 8.4 -4 2.3 11 80 7 77 95 12 100
Array 7 3.4 2 0 9 4.7 3 9
Front 5 8 4 7.9 0.44 1
Array 6 45 23 8.5 3.98 4 2.5
Sorted 4 90 6 4 111
Sorted 8 7 3 4 0 1.1 3.2 88 9
Array 6 13.5 7.6 9 33 1 0
Front 3 7 5 1.5
Positive 7 7.9 -1 -44 9.7 4.3 -1 0
Negative 8 88 -1.5 -40 -9.7 4.3 13 0 -11

after that enter your files names .
 finally check your output file 
 note: output file should be .out extension
 */
#include <iostream>
#include<fstream>
using namespace std ;

class  FloatArray {                 // FloatArray class

protected:
    int FloatArrSize ;      // size of dynamic array
    float *FloatArr ;       // declaration of dynamic array
    int cnt =0 ;                    // counter for counting the elements that will be written on file and used as index

public:

    FloatArray(int arrS=0){       // parameterized constructor
        // arrS: size of array that will be taken by parameterized constructor
        FloatArrSize = arrS ;
        FloatArr= new float [FloatArrSize]  ;         // dynamic memory allocation
    }

    virtual void Add (float number){        // virtual Add Function that adds elements to the array
        FloatArr[cnt] = number ;
        cnt++ ;                 // updating counter
    }

    friend ofstream& operator<< (ofstream& out,  FloatArray& obj){             //  insertion operator << to write the array to the file

        out<< obj.cnt <<"|" ;
        for (int j=0;j<obj.cnt;j++){                    // writing elements of array to the file
            out<<"\t"<<obj.FloatArr[j]  ;
        }

        out<<"\n" ;
        return  out ;
    }

    friend ifstream& operator >> (ifstream& inFile,  FloatArray& obj){          //  insertion Extraction operator to read the array from the file

        float num;
        for (int i=0;i<obj.FloatArrSize;i++){               // reading elements of array from the file
            inFile >> num ;
            obj.Add(num)  ;
        }

        return inFile ;
    }

    ~FloatArray(){                  // destructor to deallocate the array  from memory
        delete [] FloatArr ;
    }

};

// SortedArray class
class SortedArray : public FloatArray {

public:

    SortedArray(int arrS=0): FloatArray(arrS) {               // parameterized constructor
    }

    virtual void Add(float number){             // Add fun that add elements to the array sorted

        if (cnt==0){
            FloatArr[cnt] = number ;
            cnt++ ;
            return;
        }

        else {
            FloatArr[cnt]= number ;

            for (int j=cnt ;j>0; j--){

                if (FloatArr[j]<FloatArr[j-1]){
                    float temp = FloatArr[j] ;
                    FloatArr[j]= FloatArr[j-1] ;
                    FloatArr[j-1]= temp ;
                }
            }
            cnt++ ;             // updating counter
        }

    }

};

// FrontArray class
class FrontArray: public FloatArray {

public:

    FrontArray(int arrS=0): FloatArray(arrS)  {         // parameterized constructor
    }

    int j = FloatArrSize -1 ;           // j indicates to the last element in the array
    // last element in the original array is first element in front array  ;

    void Add(float number){         //      Add Function that add elements to the array

        FloatArr[j]= number ;
        j-- ;           // updating j
        cnt++ ;          // updating counter
    }

};

// PositiveArray class
class PositiveArray : public SortedArray {

public:
    PositiveArray(int arrS=0) : SortedArray(arrS) {         // parameterized constructor
    }

    void Add(float number){             //  Add Function that adds the positive elements to the array and sorted(by Add fun of sortedArray)

        if(number>0){
            FloatArr[cnt] = number ;
            SortedArray::Add(number) ;      // calling Add function of SortedArray
        }
    }

};

// NegativeArray class
class NegativeArray : public SortedArray {

public:

    NegativeArray(int arrS=0) : SortedArray(arrS) {         // parameterized constructor
    }

    void Add(float number){          //  Add Function that adds the Negative elements to the array and sorted(by Add fun of sortedArray)

        if(number<0){
            FloatArr[cnt] = number ;
            SortedArray::Add(number) ;              // calling the Add function of Sorted Array
        }

    }

};


int main(){
    FloatArray *Array[10] ;

    string inputFileName, outputFileName ;

    cout<<"PLz, enter name of the input file:\n";
    cin>> inputFileName;

    cout<<"PLz, enter name of the output file:\n";
    cin >> outputFileName ;

    ifstream inFile(inputFileName,ios::in | ios::binary) ;      // opening file for reading from it (that its name will be taken from user)
    ofstream outFile(outputFileName,ios::out | ios::binary) ;   // opening file for writing to it (that its name will be taken from user)


    // reading data from file
    for(int i=0;i<10;i++){
        string arrayType ;      // array type
        int arrSize ;           // size of array

        inFile>> arrayType>> arrSize ;         // reading the array type and array size from file

        // conditions for choosing the type of class that will be used
        if (arrayType=="Array"){
            Array[i]= new FloatArray(arrSize) ;
        }

        else if (arrayType=="Front"){

            Array[i]= new FrontArray(arrSize) ;

        }

        else if (arrayType=="Sorted"){

            Array[i]= new SortedArray(arrSize) ;

        }

        else if (arrayType=="Positive"){

            Array[i]= new PositiveArray(arrSize) ;
        }

        else {                                          // true if: else if (arrayType=="Negative")

            Array[i]= new NegativeArray(arrSize) ;

        }

        inFile>> *Array[i] ;        // reading the array from file to memory

    }

    // writing the arrays to the file
    for(int i=0;i<10;i++)
        outFile<< *Array[i] ;       // writing the array to the file

    // deallocating objects of classes
    for(int i=0;i<10 ; i++)
        delete Array[i] ;

    inFile.close() ;        // closing the reading file
    outFile.close() ;       // closing the writing file

    return 0 ;
}
