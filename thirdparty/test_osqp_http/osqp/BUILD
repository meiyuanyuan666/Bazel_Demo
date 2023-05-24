load("@rules_cc//cc:defs.bzl", "cc_library")


OSQP_HEADERS = glob([
    "osqp/*",
])

OSQP_SOURCES = glob([
    "osqp/**/src/**/*.h",
])

cc_library(
    name = "osqp",
    hdrs = OSQP_HEADERS,
    srcs = OSQP_SOURCES,
    visibility = ["//visibility:public"],
)
