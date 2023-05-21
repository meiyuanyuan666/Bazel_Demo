#include <glog/logging.h>
#include <gflags/gflags.h>
//  https://blog.csdn.net/A_L_A_N/article/details/88018718
DEFINE_string(name, "meiyuanyuan", "your name");
 
int main(int argc, char *argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = 1;
    FLAGS_colorlogtostderr = 1;
    gflags::ParseCommandLineFlags(&argc, &argv, true);
 
    LOG(INFO) << "hello " << FLAGS_name;
 
    return 0;
}