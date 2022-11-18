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

CTree::CTree(const CTree &t){
    data = t.data;
    kids = t.kids->copy(this);
    sibs = t.sibs->copy(this);
}

bool CTree::addChild(char ch)
{
    //store char in new child
    //return false if child exists
    //otherwise add in order and return true

    CTree *tree = new CTree(ch);
    if(addChild(tree)){
        return true;
    }else{
        delete tree;
        return false;
    }
}

bool CTree::addChild(CTree *root)
{
    //add root as child
    //return false if root has prev or siblings or if data already exists as child
    //can't trivially add a new node with children? can add with sibilings or add with no children?
    //otherwise add node in order

    //to add child with children, break them up and insert individually?

    if(root->prev || root->sibs || root->kids/*added this????*/)return false;

    if(kids){
        if(kids->data < root->data){
            //go to next recursively
            return kids->addChild(root);
        }else if(kids->data > root->data){
            //insert
            //old child becomes child of new node
            root->kids = kids;
            //new node prev becomes old childs prev
            root->prev = kids->prev;
            //old childs prev becomes new node
            kids->prev = root;
            //current node becomes new node
            kids = root;

            return true;
        }else{
            //equals, already exists
            return false;
        }
    }else{
        //reached end of children, add to end        
        root->prev = this;
        kids = root;

        return true;
    }
}

std::string CTree::toString()
{
    //return elements in all nodes of the tree separated by \n
    //ordering is determined by a depth first pre-order traversal

    std::string result;

    dfTraverse(result);

    return result;
}

void CTree::dfTraverse(std::string &str) const{
    str += data;
    if(kids){
        kids->dfTraverse(str);
    }

    if(sibs){
        sibs->dfTraverse(str);
    }
}

CTree *CTree::copy(CTree *prev) const{
    CTree *tree = new CTree(data);
    tree->prev = prev;

    if(kids){
        tree->kids = kids->copy(tree);
    }

    if(sibs){
        tree->sibs = sibs->copy(tree);
    }

    return tree;
}

bool CTree::addSibling(char ch)
{
    //store char in new sibling
    //return false if sibling exists
    //otherwise add in order and return true

    CTree *tree = new CTree(ch);
    if(addSibling(tree)){
        return true;
    }else{
        delete tree;
        return false;
    }
}

bool CTree::addSibling(CTree *root)
{
    //store root in siblings
    //return false if sibling exists or root is invalid
    //otherwise add in order and return true

    if(root->prev || root->sibs || root->kids)return false;

    if(sibs){
        if(sibs->data < root->data){
            //go to next recursively
            return sibs->addSibling(root);
        }else if(sibs->data > root->data){
            //insert
            //old sib becomes sib of new node
            root->sibs = sibs;
            //new node prev becomes old sibs prev
            root->prev = sibs->prev;
            //old sibs prev becomes new node
            sibs->prev = root;
            //current node becomes new node
            sibs = root;
            return true;
        }else{
            //equals, already exists
            return false;
        }
    }else{
        //reached end of sibs, add to end        
        root->prev = this;
        sibs = root;

        return true;
    }
    
}

bool CTree::treeCompare(const CTree *a, const CTree *b) const
{
    std::string dftA,dftB;

    a->dfTraverse(dftA);
    b->dfTraverse(dftB);

    return dftA == dftB;
}

std::ostream &operator<<(std::ostream &os, const CTree &root)
{
    //write toString to output stream
    std::string out;
    root.dfTraverse(out);
    os << out;
    return os;
}

CTree &CTree::operator+(CTree &rt)
{
    //call addChild, returning the resulting tree

    addChild(&rt);
    return *copy();    
}

bool CTree::operator==(const CTree &root)
{
    return treeCompare(this,&root);
}
