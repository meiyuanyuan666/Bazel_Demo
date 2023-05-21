load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
 
cc_binary(
    name = "bazel_test",
    srcs = ["main.cc"],
    deps = ["//protoc:msg_proto"],
)