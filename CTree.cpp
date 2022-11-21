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
    //otherwise add node in order

    if(root->prev || root->sibs)return false;

    if(kids){
        //has children add as sibling
        return kids->addSibling(root);
    }else{
        //no children, add new 
        std::cout << "no kids" << std::endl;
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
    str += '\n';
    if(kids){
        kids->dfTraverse(str);
    }

    if(sibs){
        sibs->dfTraverse(str);
    }
}

void CTree::dfTraverseDebug(std::string &str) const{
    str += debugString();
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

std::string CTree::debugString() const{
    std::string res;

    res = "data: " + data + '\n';
    res += "prev: " + (prev ? prev->data : '0') + '\n';
    res += "sibs: " + (sibs ? sibs->data : '0') + '\n';
    res += "kids: " + (kids ? kids->data : '0') + '\n';

    return res;
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
    //return false if sibling exists or root is invalid or root node
    //otherwise add in order and return true

    if(!prev || root->prev || root->sibs)return false;

    std::cout << "ADD SIB: " << root->data << std::endl;

    if(data == root->data){
        std::cout << "exists" << std::endl;
        //can't add if exists
        return false;
    }else if(sibs){
        if(root->data > sibs->data){
            //go to next recursively

            std::cout << root->data << " > " << sibs->data << std::endl;
            return sibs->addSibling(root);
        }else if(root->data < sibs->data){
                std::cout << root->data << " < " << sibs->data << std::endl;

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
        std::cout << root->data << " == " << sibs->data << std::endl;

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

std::ostream &operator<<(std::ostream &os, CTree &rt)
{
    //write toString to output stream
    std::string out;
    rt.dfTraverse(out);
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
