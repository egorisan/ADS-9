// Copyright 2022 NNTU-CS
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <vector>

#include "tree.h"

Node::Node(char val) : value(val) {}

Node::~Node() {
  for (Node* child : children) {
    delete child;
  }
}

void PMTree::buildSubtree(Node* parent,
                          std::vector<char> available_chars) {
  if (available_chars.empty()) {
    return;
  }

  for (char current_char : available_chars) {
    Node* child_node = new Node(current_char);
    parent->children.push_back(child_node);

    std::vector<char> next_available_chars;
    for (char c : available_chars) {
      if (c != current_char) {
        next_available_chars.push_back(c);
      }
    }
    buildSubtree(child_node, next_available_chars);
  }
}

PMTree::PMTree(std::vector<char> in)
    : initial_size_(static_cast<int>(in.size())) {
  std::vector<char> sorted_in = in;
  std::sort(sorted_in.begin(), sorted_in.end());

  for (char root_char : sorted_in) {
    Node* root_child_node = new Node(root_char);
    root_children_.push_back(root_child_node);

    std::vector<char> remaining_chars;
    for (char c : sorted_in) {
      if (c != root_char) {
        remaining_chars.push_back(c);
      }
    }
    buildSubtree(root_child_node, remaining_chars);
  }
}

PMTree::~PMTree() {
  for (Node* node : root_children_) {
    delete node;
  }
}

namespace {

void getAllPermsRecursive(
    Node* node,
    std::vector<char>& current_perm,
    std::vector<std::vector<char>>& all_perms_list) {
  current_perm.push_back(node->value);

  if (node->children.empty()) {
    all_perms_list.push_back(current_perm);
  } else {
    for (Node* child : node->children) {
      getAllPermsRecursive(child, current_perm, all_perms_list);
    }
  }
  current_perm.pop_back();
}

int64_t factorial(int n) {
  if (n < 0) {
    return 0;
  }
  if (n == 0) {
    return 1;
  }
  int64_t res = 1;
  for (int i = 1; i <= n; ++i) {
    if (__builtin_mul_overflow(res, i, &res)) {
      return -1;
    }
  }
  return res;
}

}  // namespace

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> all_perms_list;
  std::vector<char> current_perm;
  for (Node* root_child : tree.getRootChildren()) {
    getAllPermsRecursive(root_child, current_perm, all_perms_list);
  }
  return all_perms_list;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  if (num <= 0) {
    return {};
  }
  std::vector<std::vector<char>> all_perms = getAllPerms(tree);
  if (num > static_cast<int>(all_perms.size())) {
    return {};
  }
  return all_perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result_perm;
  const int n = tree.getInitialSize();

  if (num <= 0) {
    return {};
  }

  const int64_t total_perms = factorial(n);
  if (total_perms == -1 || num > total_perms) {
    return {};
  }

  if (n == 0) {
      return {};
  }

  std::vector<Node*> current_level_nodes = tree.getRootChildren();
  int64_t k = num - 1;

  result_perm.reserve(static_cast<size_t>(n));

  for (int i = 0; i < n; ++i) {
    if (current_level_nodes.empty()) {
      return {};
    }

    const int remaining_elements_to_permute = n - 1 - i;
    int64_t permutations_per_branch =
        factorial(remaining_elements_to_permute);

    if (permutations_per_branch == -1) {
      return {};
    }

    if (permutations_per_branch == 0) {
      if (remaining_elements_to_permute > 0) {
        return {};
      }
      permutations_per_branch = 1;
    }

    int child_index = 0;
    if (permutations_per_branch > 0) {
      child_index = static_cast<int>(k / permutations_per_branch);
    }

    if (child_index >= static_cast<int>(current_level_nodes.size())) {
      return {};
    }

    Node* chosen_node = current_level_nodes[child_index];
    result_perm.push_back(chosen_node->value);

    if (i < n - 1) {
      k %= permutations_per_branch;
      current_level_nodes = chosen_node->children;
    }
  }
  return result_perm;
}


