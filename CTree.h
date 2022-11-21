#ifndef _CTREE_H
#define _CTREE_H

#include <cstdlib>
#include <string>
#include <iostream>

// tree of characters, can be used to implement a trie

class CTree {
  friend class CTreeTest;
  
  char data;     // the value stored in the tree node

  CTree * kids;  // children - pointer to first child of list, maintain order & uniqueness

  CTree * sibs;  // siblings - pointer to rest of children list, maintain order & uniqueness
                 // this should always be null if the object is the root of a tree

  CTree * prev;  // pointer to parent if this is a first child, or left sibling otherwise
                 // this should always be null if the object is the root of a tree

 public:
  friend std::ostream& operator<<(std::ostream& os, CTree& rt);
  CTree(char ch);
  CTree(const CTree &t);

  ~CTree();  // clear siblings to right and children and this node
  
  CTree& operator+(CTree& rt);  //^ operator to do the same thing as addChild
  bool operator==(const CTree &root); // return true if two CTrees match node by node
  
  // siblings and children must be unique, return true if added, false otherwise
  bool addChild(char ch);

  // add tree root for better building, root should have null prev and sibs 
  // returns false on any type of failure, including invalid root
  bool addChild(CTree *root);

  std::string toString(); // all characters, separated by newlines, including at the end

    void dfTraverse(std::string &str) const;
    void dfTraverseDebug(std::string &str) const;
    CTree *copy(CTree *prev = nullptr) const;
    std::string debugString() const;

  
 private:
  // these should only be called from addChild, and have the same restrictions
  // the root of a tree should never have any siblings
  // returns false on any type of failure, including invalid root
  bool addSibling(char ch);
  bool addSibling(CTree *root);

  bool treeCompare(const CTree *a, const CTree *b) const;

};

#endif