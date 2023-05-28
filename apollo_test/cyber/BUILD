load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
package(default_visibility = ["//visibility:public"])

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
    name = "file",
    srcs = ["file.cc"],
    hdrs = ["file.h"],
    deps = [
      "log",
      "@com_google_protobuf//:protobuf_lite",
    ],
)

cc_library(
    name = "macro",
    hdrs = ["macro.h"],
)

cc_library(
    name = "macros",
    hdrs = ["macros.h"],
    deps = [
      "macro",
    ],
)

cc_library(
    name = "types",
    hdrs = ["types.h"],
)




