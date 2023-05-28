# 前提条件
请先安装 Bazel（如果尚未安装）。本教程使用 Git 进行源代码控制，因此，为获得最佳结果，还应安装 Git。
接下来，在您选择的命令行工具中运行以下命令，从 Bazel 的 GitHub 代码库中检索示例项目：
git clone https://github.com/bazelbuild/examples
本教程的示例项目位于 examples/cpp-tutorial 目录中。
Bazel学习教材https://bazel.google.cn/start/cpp?hl=zh-cn
# Examples to build C++ code

This package will showcase how to build C++ code in stages.
虽然 Bazel 是一个支持多语言构建的构建系统，但本教程以 C++ 项目为例，并提供了适用于大多数语言的常规指南和流程。

### Stage 1
The first stage is really simple and shows you how to compile a binary with a single source file.
在第一阶段，您将构建位于单个软件包中的单个目标。
Bazel 会识别项目中的一些特殊文件：

1、WORKSPACE：用以将当前目录以及内容标识为 Bazel 工作空间，该文件可以为空，或者声明项目的外部依赖以及获取方式 ；
2、BUILD：告诉 Bazel 如何构建项目的每一个部分，工作区中包含 BUILD 文件的目录称为包 (package)；

在项目 stage1 中，项目根目录下的空文件 WORKSPACE 用以标识 Bazel 工作空间；
该项目有一个名为 main 的包，其中的 BUILD 文件定义了有关构建这个包的规则：

load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cc"],
)

BUILD 文件首先通过 load 函数将 @rules_cc//cc:defs.bzl 文件中的 cc_binary 函数导入，该函数用以定义构建 C++ 可执行文件的规则；
而后调用 cc_binary 函数定义构建目标 (target) hello-world 的规则，其中参数 src 指定了源文件。

### Stage 2
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
注意：:hello-greet 是标签 //main:hello-greet 的简略写法，因为 hello-greet 与 hello-world 在同一个包中；
这里的冒号可以省略，即也可以简写为 hello-greet。

### Stage 3
The third stage showcases how to link multiple build directories by building multiple libraries in different packages and then connecting it up with the main application.
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

### 常见的命令
### build
bazel  build  //path:object

### Debug
bazel build //path:object -c dbg

### 查看依赖关系
bazel query --notool_deps --noimplicit_deps "deps(//path:object)" --output graph

### Clean
bazel clean

### 构建规则基础

以上 C++ 案例中已经使用到了 cc_binary 与 cc_library 这两条规则，构建 C++ 项目时还有另外一些常用规则。
以下将对这些规则以及参数进行介绍，更为详细的介绍可见 Bazel官网。
### cc_binary

规则 cc_library 用来构建可执行文件，其可用参数如下：

cc_binary(name, deps, srcs, data, additional_linker_inputs, args, compatible_with, copts, defines, deprecation, distribs, env, exec_compatible_with, exec_properties, features, includes, licenses, linkopts, linkshared, linkstatic, local_defines, malloc, nocopts, output_licenses, restricted_to, stamp, tags, target_compatible_with, testonly, toolchains, visibility, win_def_file)

常用参数说明 (更为详细的说明可见 Bazel官网)：

    name：目标名称srcs：用以构建 C++ 目标所需要的文件列表 (包括头文件、源文件、编译中间文件)deps：需要链接到目标的库，通常是 cc_library 目标linkstatic：是否将依赖库静态编译到目标中

### cc_library

规则 cc_library 用来构建库，其可用参数如下：

cc_library(name, deps, srcs, data, hdrs, alwayslink, compatible_with, copts, defines, deprecation, distribs, exec_compatible_with, exec_properties, features, implementation_deps, include_prefix, includes, licenses, linkopts, linkstamp, linkstatic, local_defines, nocopts, restricted_to, strip_include_prefix, tags, target_compatible_with, testonly, textual_hdrs, toolchains, visibility, win_def_file)

常用参数说明 (更为详细的说明可见 Bazel官网)：

    name：目标名称srcs：用以构建 C++ 目标所需要的文件列表 (包括头文件、源文件、编译中间文件)hdrs：依赖该库的目标中可以直接包含的头文件列表

特别注意，习惯上 srcs 与 hdrs 中的文件是有区别的： 当 cc_library 规则构建的库作为另一规则的 deps 时，另一规则可以直接包含 (include) hdrs 中列举的头文件，而不能直接使用 srcs中列举的头文件。

例如在 stage3 案例中如果 lib/BUILD 中将 hello-time.h 放到了 srcs 列表中：

cc_library(
    name = "hello-time",
    srcs = ["hello-time.cc", "hello-time.h"],
    visibility = ["//main:__pkg__"],
)

则依赖 hello-time 库的目标中文件不能直接包含 hello-time.h 这一文件，即 hello-world.cc 中不应出现 #include "lib/hello-time.h" 类似语句。但很不幸目前 Bazel 并不能检测到这一错误，即使在 hello-world.cc 使用了 hello-time.h 头文件也依然能够成功构建项目。
### cc_import

规则 cc_import 用来导入预先编译的库 (静态库，共享库，接口库等)，其可用参数如下：

cc_import(name, data, hdrs, alwayslink, compatible_with, deprecation, distribs, features, interface_library, licenses, restricted_to, shared_library, static_library, system_provided, tags, target_compatible_with, testonly, visibility)

将预先编译的库使用 cc_import 导入后，其他规则可以在 deps 中像依赖 cc_library 规则一样依赖预先编译的库。例如有静态库 libmylib.a，共享库 libmylib.so，在目标 first 中需要链接静态库 libmylib.a，在目标 second 中需要链接动态库 libmylib.so，则可以制定以下规则：

cc_import(
  name = "mylib",
  hdrs = ["mylib.h"],
  static_library = "libmylib.a",
  shared_library = "libmylib.so",
)

cc_binary(
  name = "first",
  srcs = ["first.cc"],
  deps = [":mylib"],
  linkstatic = 1, # default value
)

cc_binary(
  name = "second",
  srcs = ["second.cc"],
  deps = [":mylib"],
  linkstatic = 0,
)

参数 linkstatic 来指定使用静态库还是共享库进行目标构建，更为详细的说明可见 Bazel官网。
