# Stage 2

### Library

Here, we introduce the ```cc_library``` rule for building C++ libraries. We have a ```cc_library``` named ```hello-greet``` and its header and source files are defined accordingly.
```
cc_library(
    name = "hello-greet",
    srcs = ["hello-greet.cc"],
    hdrs = ["hello-greet.h"],
)
```

### Binary

The ```cc_binary``` rule we saw in stage 1 has not changed, except that we now depend on the ```cc_library``` ```hello-greet```.
```
cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cc"],
    deps = [
        ":hello-greet",
    ],
)
```

To build this example, use
```
bazel build //main:hello-world
```

The second stage will showcase how to build an application with multiple source and header files, separated in a library and a binary.
在第二阶段，您将基于单个软件包构建二进制文件和库。

这里 hello-greet 作为 hello-world 的一项依赖。我们可以使用一条规则完成项目的构建：

cc_binary(
    name = "hello-world",
    srcs = glob(["*.cc", "*.h"]),
)

这里 glob 负责找到当前目录下所有 .cc 文件和 .h 文件。虽然这种方式可以完成构建目标，但很显然并没有体现 hello-greet 是 hello-world 的依赖这一点，当包的规模增大后会造成混乱；更重要的是，hello-greet 作为一个库，应当能够在其他包中使用，如果使用上述规则而不将 hello-greet 作为一个独立的目标，则其他包想要使用这个库将无从下手。

因此，更优的方案是建立一条规则将 hello-greet 编译成一个库，然后在 hello-world 中将 hello-greet 作为依赖项，形成了案例中以下两条规则：

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
    ],
)

cc_library 规则用来构建库 (静态库或动态库)，在 cc_binary 中使用 dep 参数引用依赖库。
注意：:hello-greet 是标签 //main:hello-greet 的简略写法，因为 hello-greet 与 hello-world 在同一个包中；这里的冒号可以省略，即也可以简写为 hello-greet。
