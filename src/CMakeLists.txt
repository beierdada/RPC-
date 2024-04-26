#aux_source_directory(. SRC_LIST)
set(SRC_LIST 
    mprpcapplication.cc 
    mprpcconfig.cc 
    rpcheader.pb.cc 
    rpcprovider.cc 
    mprpcchannel.cc
    mprpccontroller.cc
    logger.cc
    zookeeperutil.cc
    )
add_library(mprpc ${SRC_LIST})#生成库文件，默认为静态库，SHARED为动态库
target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)
#target_link_libraries(mprpc muduo_net muduo_base pthread)