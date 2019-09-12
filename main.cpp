//
//  main.cpp
//  Programmable Calculator
//
//  Created by Mayank Raj on 11/28/18.
//  Copyright © 2018 Mayank Raj. All rights reserved.
//
#include "Header.h"
#include "Invoker.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <array>


using namespace std;

/**vector<string> split(const char* str, char c = ' '){
    vector<string> result;
    do{
        const char* begin = str;
        while (*str != c && *str) {
            str++;
        }
        result.push_back(string(begin,str));
    }while(0!= *str++);
    
    return result;
}**/

/**this method prints the registers w x y z **/

void printRegisters(array<double,5> a){
    cout<<"w = "<<a[0]<<endl;
    cout<<"x = "<<a[1]<<endl;
    cout<<"y = "<<a[2]<<endl;
    cout<<"z = "<<a[3]<<endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    map<int,string> tempDict;               //temporary map instance
    //map<int,string> dictToken;
    ifstream  file;// = new ofstream();
    string line;
    array<double,5> cState;
    for (int i =0; i<5; i++) {              //array holding current state of the registers
        cState[i] = 0;
    }
    cState[4] = 1;
    int static tot_exec = 1;                //to keep track of number of executions
    int flag = 0;
    //Invoker invokerObj ;
    Invoker invokerObj;
    map<int,string>::iterator it;
    int pc = 1;
    char c;
    int countDebug = 0;
    int countNormal = 0;
    int checkFileChosen = 0;
    /**the snippet for accepting user input**/
    do {
        cout<<"Please choose appropriate command"<<endl;
        cout << "i <filename>"<<endl;
        cout << "Debug Mode - d" << endl;
        cout << "Nomral MOode -r" << endl;
        cout << "Comtinue -c" << endl;
        cout << "Print - p" << endl;
        cout << "Quit -q" << endl;
        cin>>c;
        
        switch (c) {
            case 'i':{
                string fileName;
                cin.ignore();
                getline(cin,fileName);
                
                file.open(fileName,ios::in);
                if(!file){
                    cout <<"error in opening file, please provide appropriate file name"<<endl;
                    flag = 1;
                    break;
                }
                int i = 1;
                while(!file.eof()){
                    
                    getline(file,line,'\n');
                    tempDict.insert(pair<int, string>(i,line));
                    i++;
                }
                checkFileChosen = 1;
                file.close();
                
                
                map<int,string>:: iterator it;
                for(it=tempDict.begin(); it!= tempDict.end();++it){
                    cout<<it->first<<": "<<it->second<< endl;
                }
                cout<<"Press 1 to continue and 2 to exit" << endl;
                int keepOn;
                cin>>keepOn;
                if(keepOn == 1){
                    flag = 1;
                }
                else
                    flag = 0;
                break;
        }
                
            case 'r':{
                if(checkFileChosen == 0){
                    cout<<"Warning: Please use command i first to choose a file with expressions"<<endl;
                    flag = 1;
                }
                else{
                int size = static_cast<int>(tempDict.size());
                if(countDebug != 0){
                    //pc = 1;
                    tot_exec = 1;
                }
                while ((pc <=  size) && (tot_exec <=100)){
                    pc = cState[4];
                    if(pc <= size){
                        //cout<<tempDict[pc]<<endl;
                        invokerObj.setVals(tempDict[pc], cState);
                    
                        invokerObj.implement();
                        cState = invokerObj.item.currVal;
                        tot_exec++;
                        countNormal++;
                    }
                    //pc++;
                    //cout<<"1"<<endl;
                }
                //tot_exec--;
                printRegisters(cState);
                    cout<<tot_exec<<endl;
                    cout<<cState[4]<<endl;
                flag = 1;
                }
            
                break;
                }
            
            case 'c':{
                if(countNormal == 0 && countDebug == 0){
                    cout<<"Please run r or d first"<<endl;
                    flag = 1;
                    break;
                }
                if(checkFileChosen == 0){
                    cout<<"Warning: Please use command i first to choose a file with expressions"<<endl;
                    flag = 1;
                    break;
                }
                int size = static_cast<int>(tempDict.size());
                
                int z = tot_exec - 1;
                if (tot_exec >= 100){
                    while((pc <= size) && tot_exec <= 200 /**(tot_exec <= (z + 100))**/){
                        pc = cState[4];
                        if(pc > size){
                            break;
                            flag = 1;
                        }
                        invokerObj.setVals(tempDict[pc], cState);
                        invokerObj.implement();
                        cState = invokerObj.item.currVal;
                    
                        tot_exec++;
                    
                }
                }
                printRegisters(cState);
                
                break;
            }
            case 'd':{
                if(checkFileChosen == 0){
                    cout<<"Warning: Please use command i first to choose a file with expressions"<<endl;
                    flag = 1;
                }
                else{
                int size = static_cast<int>(tempDict.size());
                if(tot_exec >= 200){
                    pc = 1;
                    for(int j = 0; j < 5; j++){
                        cState[j] = 0;
                    }
                    cState[4] = pc;
                    tot_exec = 1;
                }
                 if((pc <=  size) ){
                    pc = cState[4];
                    if(pc <= size){
                        //cout<<tempDict[pc]<<endl;
                        invokerObj.setVals(tempDict[pc], cState);
                        
                        invokerObj.implement();
                        cState = invokerObj.item.currVal;
                        tot_exec++;
                        countDebug++;
                    }
                    //pc++;
                    //cout<<"1"<<endl;
                }
                //tot_exec--;
                printRegisters(cState);
                cout<<"Mext Instruction Index: "<< cState[4]<<endl;
                cout<<"Press d in the next prompt to continue debugging mode"<<endl;
                cout<<"Or press r in the prompt to finish the execution in one go"<<endl;
                flag = 1;
                }
                break;
        }
            case 'q':{
                cout<<"Press 1 if you are sure to quit" << endl;
                int keepOn;
                cin>>keepOn;
                if(keepOn == 1){
                    flag = 0;
                }
                else
                    flag = 1;
                break;
                
            case 'p':
                printRegisters(cState);
                flag = 1;
                break;
        }
            default:
                cout<<"Please enter valid entry"<<endl;
                flag = 1;
                break;
        }
    } while (flag == 1);
    
    
   
    
    return 0;
}
