#include <iostream>
#include "truck_simulation.hpp"

#include <gflags/gflags.h>
#include <glog/logging.h>
// DEFINE_string(test_tmpdir, "", "Dir we use for temp files");
// DEFINE_string(srcdir, StringFromEnv("SRCDIR", "."), "Source-dir root, needed
// to find gflags_unittest_flagfile"); DEFINE_bool(test_bool, false, "tests
// bool-ness"); DEFINE_int32(test_int32, -1, ""); DEFINE_int64(test_int64, -2,
// ""); DEFINE_uint32(test_uint32, 1, ""); DEFINE_uint64(test_uint64, 2, "");
// DEFINE_double(test_double, -1.0, "");
// DEFINE_string(test_string, "initial", "");

// Can also use DECLARE_string(test_string) if flag is defined in another .o
int main(int argc, char *argv[]) {
  // init GFlags
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  LOG(INFO) << "Running Truck_simulation" << std::endl;
  return 0;
}
