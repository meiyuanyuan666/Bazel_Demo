load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
package(default_visibility = ["//visibility:public"])
 
 
cc_proto_library(
    name = "msg_proto",
    deps = [
        ":msg_proto_lib",
    ],
)
 
proto_library(
    name = "msg_proto_lib",
    srcs = [
        "msg.proto",
    ],
)