//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//


#include "unique_ptr.hpp"
#include <cassert>

__declspec(noinline) void call_something() {}

struct Node {
  int* shared_val;

  explicit Node(int* ptr) : shared_val(ptr) {}
  ~Node() { ++(*shared_val); }
};

__declspec(noinline) bool get_val(std::unique_ptr<Node> /*unused*/) {
  call_something();
  return true;
}

__declspec(noinline) void expect_1(int* shared, bool /*unused*/) {
  assert(*shared == 1);
}

__declspec(noinline) bool get_val(std::unique_ptr<Node[]> /*unused*/) {
  call_something();
  return true;
}

__declspec(noinline) void expect_3(int* shared, bool /*unused*/) {
  assert(*shared == 3);
}


void unique_ptr_test() {
    {
        int shared = 0;
        // Without trivial-abi, the unique_ptr is deleted at the end of this
        // statement; expect_1 will see shared == 0 because it's not incremented (in
        // ~Node()) until expect_1 returns.
        //
        // With trivial-abi, expect_1 will see shared == 1 because shared_val is
        // incremented before get_val returns.
        expect_1(&shared, get_val(std::unique_ptr<Node>(new Node(&shared))));

        // Check that the shared-value is still 1.
        expect_1(&shared, true);
    }
    {
        int shared = 0;

        // Without trivial-abi, the unique_ptr is deleted at the end of this
        // statement, expect_3 will see shared == 0 because it's not incremented (in
        // ~Node()) until the end of this statement.
        //
        // With trivial-abi, shared_val is incremented 3 times before get_val returns
        // because ~Node() was called 3 times.
        expect_3(&shared, get_val(std::unique_ptr<Node[]>(new Node[3]{
                                Node(&shared), Node(&shared), Node(&shared)})));

        // Check that shared_value is still 3 (ie., ~Node() isn't called again by the end of the full-expression above)
        expect_3(&shared, true);
    }
}