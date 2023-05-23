load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "binary",
    srcs = ["binary.cc"],
    hdrs = ["binary.h"],
)

cc_library(
    name = "log",
    hdrs = ["log.h"],
    deps = [
      "binary",
      "@com_github_gflags_gflags//:gflags",
      "@glog",
    ],
)

cc_library(
    name = "mpc_osqp",
    srcs = ["mpc_osqp.cc"],
    hdrs = ["mpc_osqp.h"],
    deps = [
      "@osqp",
      "@eigen3//:eigen3",
      "log",
    ],
)

cc_binary(
    name = "mpc_osqp_test",
    srcs = ["mpc_osqp_test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
      "@gtest",
      "mpc_osqp",
      "log",
    ],
)