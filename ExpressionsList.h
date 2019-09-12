//
//  ExpressionsList.h
//  Programmable Calculator
//
//  Created by Mayank Raj on 11/30/18.
//  Copyright © 2018 Mayank Raj. All rights reserved.
//

#ifndef ExpressionsList_h
#define ExpressionsList_h
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

/**this is an abstract class for the epressions**/
class ExpressionList{
private:
    //string temp;
    
protected:
    ExpressionList(){};
public:
    virtual array<double, 5> calExpression(array<double,5>)=0;
    
    int returnIndex(string token);
    
    inline vector<string> static makeTokens(string str){       //return token as a collection of strings
        vector<string> temp;
        istringstream token(str);
        
        do{
            string temp2;
            token >> temp2;
            
            temp.push_back(temp2);
        }while(token);
        
        temp.pop_back();            //popping out extra  null entry due ro do while
        string t = temp.back();
        temp.pop_back();
        t.pop_back();
        //tring::iterator p = t.begin();
        //string t1 = to_string(t.at(0));
        
        temp.push_back(t);
       
        
        for (int l = 0; l < t.length(); l++){
            
        }
        t.pop_back();
        temp.push_back(t);
        temp.pop_back();
        return temp;
        
    }
    
};
//derived classes for different types of expression
int ExpressionList::returnIndex(string str){
    
    //returns the index to be inserted into, given w,x,y or z
    int i = 0;
    if (str == "w")
        i = 0;
    if (str == "x")
        i = 1;
    if (str == "y")
        i = 2;
    if (str == "z")
        i = 3;
    
    
    return i;
}

class ExpressionType1: public ExpressionList{             //  id= id op id.
public:
    array<double, 5> calExpression(array<double,5>);
    vector<string> tokenVector;
    ExpressionType1(vector<string> s){
        tokenVector = s;
    }
    void print(){
        cout<<"aaa"<<endl;
    }
};

class ExpressionType2: public ExpressionList{           // id = id op constant.
public:
    array<double, 5> calExpression(array<double,5>);
    vector<string> tokenVector;
    ExpressionType2(vector<string> s){
        tokenVector = s;
    }
};

class ExpressionType3: public ExpressionList{           // id = constant.
public:
    array<double, 5> calExpression(array<double,5>);
    vector<string> tokenVector;
    ExpressionType3(vector<string> s){
        tokenVector = s;
    }
};

class ExpressionType4: public ExpressionList{           // id ? go int.
public:
    array<double, 5> calExpression(array<double,5>);
    vector<string> tokenVector;
    ExpressionType4(vector<string> s){
        tokenVector = s;
    }
};

//imlements the evaluation of the expression type 1
array<double, 5> ExpressionType1:: calExpression(array<double,5> rCollection){
    string id1;
    double result = 0.0;
    id1 = tokenVector[0];
    int index = returnIndex(id1);
    int pc = rCollection[4];
    string operatorExp = tokenVector[3];
    int i = returnIndex(tokenVector[2]);
    int j = returnIndex(tokenVector[4]);
    double id2 = rCollection[i];
    double id3 = rCollection[j];
    
    if(operatorExp == "+"){
        result = id2 + id3;
    }
    if (operatorExp == "-") {
        result = id2 - id3;
    
    }
    if (operatorExp == "*") {
        result = id2 * id3;
    }
    if (operatorExp == "**") {
        result = pow(id2,id3);
    }
    
    if (operatorExp == "/") {
        if(id3 != 0)
        {
            result = id2/id3;
        }
        else{
            cout<<"cannot divide by zero"<<endl;
        }
    }
    pc++;
    rCollection[4] = pc;
    rCollection[index] = result;
    return rCollection;
    
    
}

//imlements the evaluation of the expression type 2
array<double, 5> ExpressionType2:: calExpression(array<double,5> rCollection) {
    
    string id1;
    double result = 0.0;
    id1 = tokenVector[0];
    int index = returnIndex(id1);
    int pc = rCollection[4];
    string operatorExp = tokenVector[3];
    int i = returnIndex(tokenVector[2]);
    double j = stod(tokenVector[4]);
    double id2 = rCollection[i];
    double id3 = j;
    
    if(operatorExp == "+"){
        result = id2 + id3;
    }
    if (operatorExp == "-") {
        result = id2 - id3;
        
    }
    if (operatorExp == "*") {
        result = id2 * id3;
    }
    if (operatorExp == "**") {
        result = pow(id2,id3);
    }
    
    if (operatorExp == "/") {
        if(id3 != 0)
        {
            result = id2/id3;
        }
        else{
            cout<<"cannot divide by zero"<<endl;
        }
    }
    pc++;
    rCollection[4] = pc;
    rCollection[index] = result;
    return rCollection;
}

//imlements the evaluation of the expression type 3
array<double, 5> ExpressionType3:: calExpression(array<double,5> rCollection){
    string id1 = tokenVector[0];
    double  constant = stod(tokenVector[2]);
    int index = returnIndex(id1);
    int pc = rCollection[4];
    //id1 = constant;
    pc++;
    rCollection[4] = pc;
    rCollection[index] = constant;
    return rCollection;
    
}

//imlements the evaluation of the expression type 4
array<double, 5> ExpressionType4:: calExpression(array<double,5> rCollection){
    string id1 = tokenVector[0];
    //int index = returnIndex(id1);
    int left = rCollection[returnIndex(id1)];
    int right = stod(tokenVector[2]);
    //int pc = rCollection[4];
    if(left == 0){
        //pc++;// = stoi(tokenVector[2]);
        rCollection[4]++;
    }
    else{
        rCollection[4] = right;
    }
    //rCollection[4] = pc;
    return rCollection;
    
    
}


#endif /* ExpressionsList_h */
