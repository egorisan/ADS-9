// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdint>

struct Node {
    char value;
    std::vector<Node*> children;

    explicit Node(char val);
    ~Node();

    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(Node&&) = delete;
    Node& operator=(Node&&) = delete;
};

class PMTree {
 private:
    std::vector<Node*> root_children_;
    int initial_size_;

    void buildSubtree(Node* parent, std::vector<char> available_chars);

 public:
    explicit PMTree(std::vector<char> in);
    ~PMTree();

    PMTree(const PMTree&) = delete;
    PMTree& operator=(const PMTree&) = delete;
    PMTree(PMTree&&) = delete;
    PMTree& operator=(PMTree&&) = delete;

    const std::vector<Node*>& getRootChildren() const { return root_children_; }
    int getInitialSize() const { return initial_size_; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_

