//
//  main.c
//  Compile
//
//  Created by 孟冰川 on 2019/9/6.
//  Copyright © 2019 孟冰川. All rights reserved.
//

#include <stdio.h>
#include "LexicalAnalysis01.h"
#include "LexicalAnalysis02.h"

int main(int argc, const char * argv[]) {
//    LexicalAnalysis01("age >= 45", 9);
//    printf("====\n");
    LexicalAnalysis02("int intd = 32", 13);
    return 0;
    
}
