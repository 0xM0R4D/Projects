/*
This Code contains a BigInt Class that can hold unlimited decimal integer values and performs
arithmetic operations on them.

Different variations of types int and float exist in C++ and other languages. They are usually limited by
minimum and maximum values. Sometimes it is desired to have versions of these types with unlimited
bounds. Java solves this problem by providing BigInteger and BigDecimal classes, but C++ still doesnot solve it; so i developed this class for solving it.
*/
#include <iostream>
#include <algorithm>
#include <string>
using namespace  std ;

// BigInt class
class BigInt {
    string strNum ;

public:
    BigInt(){           // default constructor
        strNum="" ;

    }
    BigInt(string num){     // parametrized constructor for string
        strNum = num ;

    }
    BigInt(int num){        // parametrized constructor for integer
        strNum = to_string(num) ;
    }

    BigInt operator+( BigInt& Obj2){            // + operator

        bool minusFlag = false ;
        bool helping= false ;

        BigInt ans ;
        BigInt obj3 ;

        if (strNum[0]!='-' && Obj2.strNum[0]=='-'){         // case: +, -
            //            BigInt obj3 ;
            Obj2.strNum.erase(0,1) ;
            if(isSmaller(strNum, Obj2.strNum)){
                minusFlag = true ;
                obj3 = Obj2 - *this ;
                obj3.strNum = '-' + obj3.strNum ;
            }
            else {
                obj3 = *this - Obj2 ;
                ans = obj3 ;
            }
            helping = true ;

        }

        else if (strNum[0]=='-' && Obj2.strNum[0]!='-'){         // case: -, +

            strNum.erase(0,1) ;
            if(isSmaller(Obj2.strNum, strNum)){
                minusFlag = true ;
                obj3 = *this - Obj2 ;
                obj3.strNum = '-' + obj3.strNum ;
            }
            else {
                obj3 =  Obj2 - *this ;
                ans = obj3 ;
            }
            helping = true ;

        }

        else{

            if(strNum[0]=='-' && Obj2.strNum[0]=='-'){
                strNum[0]='0' ;
                Obj2.strNum[0] = '0' ;
                minusFlag = true ;
            }

            // fixing for strings if size1 not equal size2

            if (strNum.size()>Obj2.strNum.size()){
                int size3= strNum.size() - Obj2.strNum.size() ;
                string str3 = "" ;
                for(int i=0; i<size3; i++){
                    str3+= '0' ;
                }
                Obj2.strNum = str3+ Obj2.strNum ;

            }
            else if (strNum.size() < Obj2.strNum.size()){
                int size3=  Obj2.strNum.size() - strNum.size() ;
                string str3 = "" ;
                for(int i=0; i<size3; i++){
                    str3+= '0' ;
                }
                strNum = str3+ strNum ;

            }
            // else continue(not needed to fixing )

            int mx = strNum.size() ;

            ans.strNum = "" ;
            int carry= 0 ;
            for(int i =mx-1 ;i>=0; i--){
                int dig1 = strNum[i] - 48 ;
                int dig2 = Obj2.strNum[i]  - 48 ;
                int sum = dig1 + dig2 + carry ;
                int res = sum % 10 ;
                char ch = char(res + 48) ;
                carry = sum / 10 ;

                ans.strNum += ch ;

                if (i==0 && carry){
                    ans.strNum+= '1' ;
                }
            }

            // reverse for the string
            reverse(ans.strNum.begin(), ans.strNum.end()); // reverse the string

            // erase extra zeros
            int fixedSize = ans.strNum.size() ;
            for(int i=0; i<fixedSize; i++ ){
                if (ans.strNum[0]=='0'){
                    ans.strNum.erase(0,1) ;
                }
                else
                    break;
            }

            if (minusFlag){
                ans.strNum= '-'+ ans.strNum ;
            }

        }

        if (helping)            // if needed for obj3
            ans.strNum  = obj3.strNum ;

        return ans ;
    }

    bool isSmaller(string str1, string str2)        // isSmaller function checks if str1 < str2
    {

        int str1Size = str1.length() ;
        int str2Size = str2.length();

        if (str1Size < str2Size)
            return true;
        if (str2Size < str1Size)
            return false;

        for (int i=0; i<str1Size; i++)
            if (str1[i] < str2[i])
                return true;
            else if (str1[i] > str2[i])
                return false;

        return false;
    }

    // - operator
    BigInt operator-( BigInt& obj)
    {
        bool minusFlag = false ;

        if (strNum[0]=='-' && obj.strNum[0]=='-'){

            strNum.erase(0,1) ;
            obj.strNum.erase(0,1) ;

        }

        if (isSmaller(strNum, obj.strNum)){
            swap(strNum, obj.strNum);
            minusFlag = true ;
        }

        BigInt ans ;

        string resStr = "";     // string for result

        int str1Size  = strNum.length() ;
        int str2Size  = obj.strNum.length();

        // reverse for the strings
        reverse(strNum.begin(), strNum.end());
        reverse(obj.strNum.begin(), obj.strNum.end());

        int carry = 0;

        for (int i=0; i<str2Size; i++)
        {
            int sub = ((strNum[i]-'0')-(obj.strNum[i]-'0')-carry);

            if (sub < 0)
            {
                sub = sub + 10;
                carry = 1;
            }
            else
                carry = 0;

            resStr.push_back(sub + '0');
        }

        for (int i=str2Size; i<str1Size; i++)
        {
            int sub = ((strNum[i]-'0') - carry);

            if (sub < 0)
            {
                sub = sub + 10;
                carry = 1;
            }
            else
                carry = 0;

            resStr.push_back(sub + '0');
        }

        // reverse resString
        reverse(resStr.begin(), resStr.end());

        // erase extra zeros
        int fixedSize = resStr.length() ;

        for(int i=0; i<fixedSize; i++ ){
            if (resStr[0]=='0'){
                resStr.erase(0,1) ;
            }
            else
                break;
        }
        if (minusFlag){
            ans.strNum = '-'+ resStr ;
        }

        else
            ans.strNum = resStr ;

        return ans ;
    }

    // << operator
    friend ostream &operator<<(ostream &out, const BigInt &res){
        out<<res.strNum ;
        return out;
    }

    // = operator
    BigInt &operator=(const BigInt & obj){
        strNum = obj.strNum ;
        return *this;
    }

    // size()  function
    int size(){
        return strNum.length() ;
    }
};


int main() {


    // testing
    BigInt num1("10000");
    BigInt num2("100") ;

    BigInt num12Res = num1 + num2 ;
    cout<< "Case1: 10000 + 100 = "<< num12Res << endl;     // case1

    BigInt num3("4000");
    BigInt num4("100") ;

    BigInt num34Res = num3 - num4 ;
    cout<< "Case2: 4000 - 100 = "<< num34Res << endl;          // case2


    BigInt num5("-3000");
    BigInt num6("100") ;

    BigInt num56Res = num5 + num6 ;
    cout<< "Case3: -3000 + 100 = "<< num56Res << endl;         //case3


    BigInt num7(1000);          // case if integers (not strings)
    BigInt num8(10000) ;

    BigInt num78Res = num7 - num8 ;
    cout<< "Case4: 1000 - 10000 = "<< num78Res << endl;        //case4


    BigInt num9("299999999");
    BigInt num0("100000000") ;

    BigInt num90Res = num9 + num0 ;
    cout<< "Case5: 299999999 + 100000000 = "<< num90Res << endl;   //case5

    return 0;
}
