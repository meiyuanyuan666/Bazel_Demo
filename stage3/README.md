# Stage 3

In this stage we step it up and showcase how to integrate multiple ```cc_library``` targets from different packages.

Below, we see a similar configuration from Stage 2, except that this BUILD file is in a subdirectory called lib. In Bazel, subdirectories containing BUILD files are known as packages. The new property ```visibility``` will tell Bazel which package(s) can reference this target, in this case the ```//main``` package can use ```hello-time``` library. 

```
cc_library(
    name = "hello-time",
    srcs = ["hello-time.cc"],
    hdrs = ["hello-time.h"],
    visibility = ["//main:__pkg__"],
)
```

To use our ```hello-time``` library, an extra dependency is added in the form of //path/to/package:target_name, in this case, it's ```//lib:hello-time```

```
cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cc"],
    deps = [
        ":hello-greet",
        "//lib:hello-time",
    ],
)
```

To build this example, use
```
bazel build //main:hello-world
```
在第三阶段（也是最后一个阶段）中，您将构建包含多个软件包的项目，并构建具有多个目标的项目。

该案例中有 lib 和 main 两个子目录，每个目录下都有一个 BUILD 文件，因此在工作区中包含 lib 和 main 两个包。
目标 hello-world 依赖同一包中的 hello-greet 与 lib 包中的 hello-time。

在 lib/BUILD 中定义了如下规则：

cc_library(
    name = "hello-time",
    srcs = ["hello-time.cc"],
    hdrs = ["hello-time.h"],
    visibility = ["//main:__pkg__"],
)
注意 visibility = [“//main:pkg“] 表示hello-greet对于main/BUILD是可见的。

该规则构建一个名为 hello-time 的库，通过 visibility 参数声明了谁可以使用这个库，默认情况下 (即未添加 visibility 参数时) 
仅在同一个 BUILD 文件中可以使用；这里 //main:__pkg__ 表明 main 包可以使用这个库。

在 main/BUILD 中定义了如下规则：

cc_library(
    name = "hello-greet",
    srcs = ["hello-greet.cc"],
    hdrs = ["hello-greet.h"],
)

cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cc"],
    deps = [
        ":hello-greet",
        "//lib:hello-time",
    ],
)

仅有一点与 stage2 不同：hello-world 多了一个依赖项 //lib:hello-time。

特别注意 hello-world.cc 中包含 hello-time 库头文件的写法：

#include "lib/hello-time.h"

头文件格式为：包位置/文件名。对于同一包中的头文件则可以省略包名，
即 #include "main/hello-greet.h" 也可以写为 #include "hello-greet.h"。

例如，我们对案例目录结构稍作更改，在 lib 下新建 hello-time 目录用来存放 hello-time 库相关文件：

stage3-1
├── main
│   ├── BUILD
│   ├── hello-world.cc
│   ├── hello-greet.cc
│   └── hello-greet.h
├── lib
│   └── hello-time
│       ├── BUILD
│       ├── hello-time.cc
│       └── hello-time.h
└── WORKSPACE

这时 hello-time 的标签将变为 //lib/hello-time:hello-time (或简写为 //lib/hello-time，因为目标名与目录同名)，
因此需要对项目做出如下更改以构建目标：

1、lib/hello-time/hello-time.cc 中头文件包含改为 #include "lib/hello-time/hello-time.h" 或 #include "hello-time.h";
2、main/BUILD 中 cc_binary 规则的 deps 参数修改 hello-time 的标签为 //lib/hello-time:hello-time 或 //lib/hello-time;
3、main/hello-world.cc 中头文件包含改为 #include "lib/hello-time/hello-time.h";



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