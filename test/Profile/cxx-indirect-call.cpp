// Check the value profiling instrinsics emitted by instrumentation.

// RUN: %clangxx %s -o - -emit-llvm -S -fprofile-instr-generate -mllvm -enable-value-profiling -fexceptions -target %itanium_abi_triple | FileCheck %s

void (*foo) (void);

int main(int argc, const char *argv[]) {
// CHECK:  [[REG1:%[0-9]+]] = load void ()*, void ()** @foo
// CHECK-NEXT:  [[REG2:%[0-9]+]] = ptrtoint void ()* [[REG1]] to i64
// CHECK-NEXT:  call void @__llvm_profile_instrument_target(i64 [[REG2]], i8* bitcast ({{.*}}* @__profd_main to i8*), i32 0)
// CHECK-NEXT:  invoke void [[REG1]]()
  try {
    foo();
  } catch (int) {}
  return 0;
}

// CHECK: declare void @__llvm_profile_instrument_target(i64, i8*, i32)



