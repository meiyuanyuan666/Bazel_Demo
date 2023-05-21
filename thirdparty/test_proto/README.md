# 下载不到zlib
.cache/bazel/540135163923dd7d5820f3ee4b306b32/external/rules_proto/proto/private
文件夹里的dependencies.bzl文件，将"zlib"的部分改成以下即可。

"zlib": {
        "sha256": "629380c90a77b964d896ed37163f5c3a34f6e6d897311f1df2a7016355c45eff",
        "build_file": "@com_google_protobuf//:third_party/zlib.BUILD",
        "strip_prefix": "zlib-1.2.11",
        "urls": [
            "https://github.com/madler/zlib/archive/v1.2.11.tar.gz",
        ],
    }


执行命令：
在src文件下编译成main可执行文件
 bazel run //src:main  