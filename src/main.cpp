// Copyright 2022 NNTU-CS
#include <cstdint>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>
#include <vector>

#include "tree.h"

int main() {
  std::vector<char> in1 = {'1', '2', '3'};
  PMTree tree1(in1);

  std::vector<std::vector<char>> perms_result = getAllPerms(tree1);
  std::vector<char> perm2_result = getPerm2(tree1, 2);

  (void)perms_result;
  (void)perm2_result;

  std::vector<char> in2 = {'A', 'B'};
  PMTree tree2(in2);
  std::vector<char> p_ab_1 = getPerm1(tree2, 1);
  (void)p_ab_1;

  return 0;
}

