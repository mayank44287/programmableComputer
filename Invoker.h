//
//  Invoker.h
//  Programmable Calculator
//
//  Created by Mayank Raj on 11/30/18.
//  Copyright © 2018 Mayank Raj. All rights reserved.
//  this is invoker part of the command pattern design

#include<array>
#include<sstream>
#include<vector>
#include<string>
#include "Header.h"
#include "ExpressionsList.h"

using namespace std;

#ifndef Invoker_h
#define Invoker_h

class Invoker{
public:
    Reciever item;
    Invoker(){
        item.exp = "";
        item.currVal = {0,0,0,0,0};
        item.tokens = {"","","","",""};
    }
    
    void implement();
    void setVals(string,array<double,5>);
};

/**this method sets the value of current state of registers**/
void Invoker::setVals(string str, array<double,5> a){
    item.exp = str;
    item.currVal = a;
    //item.tokens = {"","","","",""};
}

/**this method implements the evaluation of expression**/
void Invoker:: implement(){
    item.tokens = ExpressionList::makeTokens(item.exp);
    
    int len = static_cast<int>(item.tokens.size());
    if(len == 5){
        string lastToken = item.tokens.back();
        //bool has_only_digits = (lastToken.find_first_not_of( "0123456789" ) == string::npos);
        if(lastToken.compare("0") <= 9){
        //if(has_only_digits == true){        //type 2 expr
            
            //ExpressionList *bptr;
            ExpressionType2 dptr(item.tokens);
            //bptr = &dptr;
            //ExpressionType2 exp2(item.tokens);
            item.currVal = dptr.calExpression(item.currVal);
        }
        else{                               //type 1 expr
            //ExpressionList *bptr;
            ExpressionType1 dptr(item.tokens);
            //bptr = &dptr;
            item.currVal = dptr.calExpression(item.currVal);
        }
        //double last = stod(lastToken);
        
    }
    else{
        if(item.tokens[1] == "="){      //type 3 expr
            //ExpressionList *bptr;
            ExpressionType3 dptr(item.tokens);
            //bptr = &dptr;
            item.currVal = dptr.calExpression(item.currVal);
        }
        else{                           //type 4 expr
            //ExpressionList bptr;
            ExpressionType4 dptr(item.tokens);
            //bptr = &dptr;
            item.currVal = dptr.calExpression(item.currVal);
        }
    }
}

#endif /* Invoker_h */
