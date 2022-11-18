#include "CTree.h"

#include <iostream>

int main(){

    CTree tree('a');

    tree.addChild('b');
    tree.addChild('l');
    tree.addChild('e');

    std::cout << tree << std::endl;

    return 0;
}