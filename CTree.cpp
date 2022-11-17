#include "CTree.h"

CTree::CTree(char ch)
{
    //init values
    data = ch;
    kids = nullptr;
    sibs = nullptr;
    prev = nullptr;
}

CTree::~CTree()
{
    //clear all children and all siblings to the right, free dynamically allocated memory, use recursion
    if(sibs){
        //will call destructor recursively
        delete sibs;
    }

    if(kids){
        //same thing here
        delete kids;
    }
}

bool CTree::addChild(char ch)
{
    //store char in new child
    //return false if child exists
    //otherwise add in order and return true

    return addChild(new CTree(ch));
}

bool CTree::addChild(CTree *root)
{
    //add root as child
    //return false if root has prev or siblings or if data already exists as child
    //otherwise add node in order

    if(root->prev || root->sibs)return false;

    if(kids){
        if(kids->data < root->data){
            //go to next
            return kids->addChild(root);
        }else if(kids->data > root->data){
            //insert
            root->kids
            newChild->kids = kids;
            newChild->prev = this;
            kids->prev = newChild;
            kids = newChild;
            return true;
        }else{
            //equals already exists
            return false;
        }
    }else{
        //reached end of children, add to end
        CTree *newChild = new CTree(ch);
        newChild->prev = this;
        kids = newChild;

        return true;
    }
}

std::string CTree::toString()
{
    //return elements in all nodes of the tree separated by \n
    //ordering is determined by a depth first pre-order traversal
}

CTree *CTree::lastSib()
{
    CTree *curr = sibs;
    while(curr){
        if(curr->sibs == nullptr){
            return curr;
        }else{
            curr = curr->sibs;
        }
    }
    return curr;
}

CTree *CTree::lastKid()
{
    CTree *curr = kids;
    while(curr){
        if(curr->kids == nullptr){
            return curr;
        }else{
            curr = curr->kids;
        }
    }
    return curr;
}

bool CTree::addSibling(char ch)
{
    //store char in new sibling
    //return false if sibling exists
    //otherwise add in order and return true
}

bool CTree::addSibling(CTree *root)
{
    //store root in siblings
    //return false if sibling exists or root is invalid
    //otherwise add in order and return true
}

bool CTree::treeCompare(const CTree *a, const CTree *b) const
{
    //determine if a == b
}

std::ostream &CTree::operator<<(const CTree &root)
{
    //write toString to output stream
}

CTree &CTree::operator+(CTree &rt)
{
    //call addChild, returning the resulting tree
}

bool CTree::operator==(const CTree &root)
{
    //call tree compare
}
