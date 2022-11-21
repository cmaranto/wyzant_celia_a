#include "CTree.h"

#include <iostream>
#include <assert.h>

int main(){

    CTree tree('a');

    assert(tree.addChild('b'));
    assert(!tree.addChild('b'));

    std::cout << tree << std::endl;

    return 0;
}