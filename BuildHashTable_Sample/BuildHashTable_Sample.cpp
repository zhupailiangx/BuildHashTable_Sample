
#include <sycl/sycl.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <dpct/dpct.hpp>
#if FPGA || FPGA_EMULATOR
#include <sycl/ext/intel/fpga_extensions.hpp>
#endif
using namespace sycl;
#define HASHTABLE_SIZE  10000

//定义哈希函数
int HashFunction(int x, int y, int z) {

    return (x * 73856096) ^ (y * 193649663) ^ (z * 83492791);
}

//定义点云数据类型
struct PointCloud {
    float x, y, z;
};

struct HashTableItem {
    bool empty = true;
    int index = -1;
};

void build_hash_table(std::vector<PointCloud> point_cloud, sycl::queue& queue) {
    //初始化哈希表
    HashTableItem hash_table[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        hash_table[i].empty = true;
        hash_table[i].index = -1;
    }
    try
    {
        //获取设备和队列信息
      /*  std::cout << "Running on device: "
            << queue.get_device().get_info<info::device::name>() << "\n";
        std::cout << "Running on version: "
            << queue.get_device().get_info<info::device::driver_version>() << "\n";*/



            //创建缓冲区域来存储数据和哈希表
        buffer<PointCloud, 1>point_cloud_buffer(point_cloud.data(), range<1>(point_cloud.size()));
        buffer<HashTableItem, 1> hash_table_buffer(hash_table, range<1>(HASHTABLE_SIZE));

        //发送内核函数到设备并执行

        queue.submit([&](handler& cgh) {
            auto point_cloud_accessor = point_cloud_buffer.get_access<access::mode::read>(cgh);
        auto hash_table_accessor = hash_table_buffer.get_access<access::mode::write>(cgh);

        cgh.parallel_for<class HashTableKernel>(range<1>(point_cloud.size()), [=](id<1> idx) {
            PointCloud point = point_cloud_accessor[idx];
        int bucket = static_cast<int>(HashFunction(point.x, point.y, point.z) * HASHTABLE_SIZE) % HASHTABLE_SIZE;
        //int bucket = static_cast<int>((point.x + point.y + point.z) * HASHTABLE_SIZE) % HASHTABLE_SIZE;

        //线程探测法解决哈希冲突
        int i = bucket;
        do {
            if (hash_table_accessor[i].empty) {
                hash_table_accessor[i].empty = false;
                hash_table_accessor[i].index = idx[0];
                break;

            }
            i = (i + 1) % HASHTABLE_SIZE;
        } while (i != bucket);
            });
            });

        //队列执行完毕后读取哈希表中的结果
        queue.wait_and_throw();

        auto result_accessor = hash_table_buffer.get_access<access::mode::read>();


        //输出测试结果
       /* for (int i = 0; i < HASHTABLE_SIZE; i++) {
            if (!result_accessor[i].empty) {
                std::cout << "Hash table at " << i << "contains point" << result_accessor[i].index << std::endl;
            }
        }*/



    }
    catch (sycl::exception e) {
        std::cerr << "SYCL exception caught:" << e.what() << std::endl;
    }


}

std::vector<PointCloud> random_cloud_point() {

    // //随机生成点云数据
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
    const int numPoints = 200000;
    //std::vector<std::vector<float>> point_cloud;
    std::vector<PointCloud> point_clouds;
    for (int i = 0; i < numPoints; i++) {
        PointCloud point_cloud;
        point_cloud.x = static_cast<float>(rand()) / RAND_MAX;
        point_cloud.y = static_cast<float>(rand()) / RAND_MAX;
        point_cloud.z = static_cast<float>(rand()) / RAND_MAX;
        point_clouds.push_back(point_cloud);
    }

    return point_clouds;
}

void test_build_hash_table_time(std::vector<PointCloud> point_clouds, sycl::queue& q) {

    build_hash_table(point_clouds, q);


}

int main() {

    std::vector<PointCloud> point_clouds;
    point_clouds = random_cloud_point();
    std::cout << "Test with default q_:\n";

    printf("\n");
    for (int i = 0; i < 5; i++) {

        queue q_;
       
        auto start = std::chrono::steady_clock::now();
        test_build_hash_table_time(point_clouds, q_);
        auto end = std::chrono::steady_clock::now();
        auto tt = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Loop = " << i + 1 << "\n";
        std::cout << " build hash table time=" << tt.count() / 1000 << "ms" << std::endl;
    }
    printf("\n");

    printf("_____________________________________________\n");
    printf("\n");

    std::cout << "Test with q_ = dpct::get_default_queue():\n";
    printf("\n");
    for (int i = 0; i < 5; i++) {

        queue q_ = dpct::get_default_queue();
        
        auto start = std::chrono::steady_clock::now();
        test_build_hash_table_time(point_clouds, q_);
        auto end = std::chrono::steady_clock::now();
        auto tt = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Loop = " << i + 1 << "\n";
        std::cout << " build hash table time=" << tt.count() / 1000 << "ms" << std::endl;
    }




    return 0;

}