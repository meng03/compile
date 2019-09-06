////
////  LexicalAnalysis01.c
////  Compile
////
////  Created by 孟冰川 on 2019/9/6.
////  Copyright © 2019 孟冰川. All rights reserved.
////
//
//#include "LexicalAnalysis01.h"
//#include "stdbool.h"
//
////简单的情况，age >= 45
////initial可以向其他三种方向走
////其他三个都不会发生转换，属于最简单的情况
//enum DFAState {Initial,Identifier,IntLiteral,Operation};
//
//struct Token {
//    enum DFAState state;
//    //假设最大字符数是10，比较浪费空间，不熟悉C，凑合下
//    char cs[10];
//    int index;
//    bool complete;
//};
//typedef struct Token Token;
//typedef enum DFAState DFAState;
//
//bool isIdentifier(char c) {
//    if ((c >= 97) && (c <= 122)) {
//        return true;
//    }
//    return false;
//}
//
//bool isIntLiteral(char c) {
//    if ((c >= 48) && (c <= 57)) {
//        return true;
//    }
//    return false;
//}
//
//bool isOperation(Token t,char c) {
//    t.cs[t.index] = c;
//    t.index ++;
//    //目前只有<=和>=，超过两位的，识别不了
//    if (t.index > 2) {
//        return false;
//    }
//    //第一个值不是小于或者大于号
//    if (!(t.cs[0] == '<' || t.cs[0] == '>')) {
//        return false;
//    }
//    //第二位有值，但不是等于号
//    if((t.index == 2) && (t.cs[1] != '=')) {
//        return false;
//    }
//    return true;
//}
//
//Token transfer(Token t,char c) {
//    if(c == ' ') {
//        t.complete = true;
//    }
//    switch(t.state) {
//        case Initial:
//            if (isOperation(t,c)) {
//                t.state = Operation;
//            }else if (isIdentifier(c)) {
//                t.state = Identifier;
//            }else if (isIntLiteral(c)) {
//                t.state = IntLiteral;
//            }
//            t.cs[t.index] = c;
//            t.index = t.index + 1;
//            break;
//        case Operation:
//            if(isOperation(t,c)) {
//                t.cs[t.index] = c;
//                t.index = t.index + 1;
//            }else {
//                t.complete = true;
//            }
//            break;
//        case IntLiteral:
//            if(isIntLiteral(c)) {
//                t.cs[t.index] = c;
//                t.index = t.index + 1;
//            }else {
//                t.complete = true;
//            }
//            break;
//        case Identifier:
//            if (isIdentifier(c)) {
//                t.cs[t.index] = c;
//                t.index = t.index + 1;
//            }else {
//                t.complete = true;
//            }
//    }
//    return t;
//}
//
//void LexicalAnalysis01(char* sentence,int len) {
//    DFAState initial = Initial;
//    Token start = {initial,"",0,false};
//    Token current = start;
//    for(int i = 0;i<len;i++) {
//        if (sentence[i] == ' ') {
//            current.complete = true;
//            continue;
//        }
//        current = transfer(current, sentence[i]);
//        if(current.complete) {
//            //如果结束了，就打印次token
//            printf("%s\n",current.cs);
//            //然后用初始化token，继续与该字符处理
//            current = transfer(start, sentence[i]);
//        }
//    }
//    current.complete = true;
//    printf("%s\n",current.cs);
//}
