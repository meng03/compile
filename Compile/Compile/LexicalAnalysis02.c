//
//  LexicalAnalysis02.c
//  Compile
//
//  Created by 孟冰川 on 2019/9/6.
//  Copyright © 2019 孟冰川. All rights reserved.
//

#include "LexicalAnalysis02.h"
#include "stdbool.h"

//简单的情况，age >= 45
//initial可以向其他三种方向走,keyword可以向Identifier走
//其他三个都不会发生转换
enum DFAState {Initial = 1,Identifier,IntLiteral,KeyWord,Operation};

struct Token {
    enum DFAState state;
    //假设最大字符数是10，比较浪费空间，不熟悉C，凑合下
    char cs[10];
    int index;
    bool complete;
};
typedef struct Token Token;
typedef enum DFAState DFAState;

bool isIdentifier(char c) {
    if ((c >= 97) && (c <= 122)) {
        return true;
    }
    return false;
}

bool isIntLiteral(char c) {
    if ((c >= 48) && (c <= 57)) {
        return true;
    }
    return false;
}

//只用一个Int类型意思下
bool isKeyWord(Token t,char c) {
    t.cs[t.index] = c;
    t.index++;
    char intkey[3] = "int";
    if(t.index > 3) {
        return false;
    }
    for(int i = 0;i<t.index;i++) {
        if(t.cs[i] != intkey[i]) {
            return false;
        }
    }
    return true;
}

bool isEmpty(char c) {
    return c == ' ';
}

bool isOperation(Token t,char c) {
    t.cs[t.index] = c;
    t.index ++;
    //目前只有<=和>=,==，超过两位的，识别不了
    if (t.index > 2) {
        return false;
    }
    //第一个值不是小于或者大于号
    if (!(t.cs[0] == '<' || t.cs[0] == '>' || t.cs[0] == '=')) {
        return false;
    }
    //第二位有值，但不是等于号
    if((t.index == 2) && (t.cs[1] != '=')) {
        return false;
    }
    return true;
}

Token transfer(Token t,char c) {
    switch(t.state) {
        case Initial:
            if (isOperation(t,c)) {
                t.state = Operation;
            }else if(isKeyWord(t, c)) {
                t.state = KeyWord;
            } else if (isIdentifier(c)) {
                t.state = Identifier;
            }else if (isIntLiteral(c)) {
                t.state = IntLiteral;
            }
            t.cs[t.index] = c;
            t.index = t.index + 1;
            break;
        case Operation:
            if(isOperation(t,c)) {
                t.cs[t.index] = c;
                t.index = t.index + 1;
            }else {
                t.complete = true;
            }
            break;
        case IntLiteral:
            if(isIntLiteral(c)) {
                t.cs[t.index] = c;
                t.index = t.index + 1;
            }else {
                t.complete = true;
            }
            break;
        case KeyWord:
            if(isKeyWord(t, c)) {
                t.cs[t.index] = c;
                t.index = t.index + 1;
            }else if(isIdentifier(c)){
                t.cs[t.index] = c;
                t.index = t.index + 1;
                t.state = Identifier;
            }else {
                t.complete = true;
            }
            break;
        case Identifier:
            if (isIdentifier(c)) {
                t.cs[t.index] = c;
                t.index = t.index + 1;
            }else {
                t.complete = true;
            }
    }
    return t;
}

void LexicalAnalysis02(char* sentence,int len) {
    DFAState initial = Initial;
    Token start = {initial,"",0,false};
    Token current = start;
    for(int i = 0;i<len;i++) {
        current = transfer(current, sentence[i]);
        if(current.complete) {
            //如果结束了，就打印token
            printf("%s,%d\n",current.cs,current.state);
            if (isEmpty(sentence[i])) {
                i++;
            }
            //然后用初始化token，继续与该字符处理
            current = transfer(start, sentence[i]);
        }
    }
    current.complete = true;
    printf("%s,%d\n",current.cs,current.state);
}
