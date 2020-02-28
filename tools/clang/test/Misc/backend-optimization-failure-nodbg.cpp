// RUN: %clang_cc1 -triple x86_64-unknown-unknown %s -O3 -emit-llvm -S -verify -o /dev/null
// REQUIRES: x86-registered-target

// Test verifies optimization failures generated by the backend are handled
// correctly by clang. LLVM tests verify all of the failure conditions.

void test_switch(int *A, int *B, int Length, int J) { /* expected-warning {{loop not vectorized: the optimizer was unable to perform the requested transformation; the transformation might be disabled or specified as part of an unsupported transformation ordering}} */
#pragma clang loop vectorize(enable) unroll(disable)
  for (int i = 0; i < Length; i++) {
    switch (A[i]) {
    case 0:
      B[i] = 1;
      break;
    case 1:
      B[J] = 2;
      break;
    default:
      B[i] = 3;
    }
  }
}
