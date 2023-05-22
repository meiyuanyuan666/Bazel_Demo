EIGEN3_HEADERS = glob([
    "Eigen/*",
])
EIGEN3_SOURCES = glob([
    "Eigen/**/src/**/*.h",
])

cc_library(
    name = "eigen3",
    hdrs = EIGEN3_HEADERS,
    srcs = EIGEN3_SOURCES,
    visibility = ["//visibility:public"],
)