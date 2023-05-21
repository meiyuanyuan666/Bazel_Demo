load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_import")

cc_import(
    name = "hello-greet",
    hdrs = ["hello-greet.h"],
    static_library = "libhello-greet.a",
    shared_library = "libhello-greet.so",
)

cc_import(
    name = "hello-time",
    hdrs = ["hello-time.h"],
    static_library = "libhello-time.a",
    shared_library = "libhello-time.so",
)


cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cc"],
    deps = [
        ":hello-greet",
        ":hello-time",
    ],
)
