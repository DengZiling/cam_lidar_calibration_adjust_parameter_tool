/*本工程的作用是手动调整相机与激光雷达之间的TF变换
 * 大致流程是：先输入autoware标定工具的结果：R、t
 * 然后将R转换成欧拉角的形式，手动输入调整量
 * 最后验证修正结果，以便决定是否再次调整。
 * 作者：邓旺敏
 * 日期：2020-12-14
 */
#include <QCoreApplication>
#include <iostream>
#include <ctime>
// Eigen 核心部分
#include <Eigen/Core>
// 稠密矩阵的代数运算（逆，特征值等）
#include <Eigen/Dense>
//空间几何运算
#include <Eigen/Geometry>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const double PI=3.1415926;
    //初始化旋转矩阵
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix<<-1.3039034368522051e-01, -6.3650693422965920e-02,
            9.8941747887351672e-01,-9.6017192070082102e-01, -2.4062690769042971e-01,
            -1.4201610469604475e-01,2.4711989189732686e-01, -9.6852840976510202e-01,
            -2.9740183364201478e-02;
    //初始化平移向量
    Eigen::Vector3d v_3d(2.9199475981113426e-01,-1.2543410130859670e-01,-2.1367384935267943e-02);

    //输出旋转矩阵
    cout << "原旋转矩阵为: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) cout << rotation_matrix(i, j) << "\t";
        cout << endl;
    }
    //旋转矩阵转换为欧拉角形式
    // ZYX顺序，即yaw-pitch-roll顺序
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    cout << "原欧拉角为: " << endl;
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;
    //手动修正欧拉角
    euler_angles(1)-=PI/14;
    euler_angles(0)+=PI/64;
    //euler_angles(0)-=PI;
    cout << "修正后的欧拉角为: " << endl;
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;
    //修正后的欧拉角转换为旋转矩阵形式
    Eigen::AngleAxisd x_temp (euler_angles[2], Eigen::Vector3d::UnitX());
    Eigen::AngleAxisd y_temp (euler_angles[1], Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd z_temp (euler_angles[0], Eigen::Vector3d::UnitZ());
    Eigen::Matrix3d NewRotationMatrix=(z_temp*y_temp*x_temp).matrix();
    //打印修正后的旋转矩阵
    cout << "修正后的旋转矩阵为: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) cout << NewRotationMatrix(i, j) << ",";
        cout << endl;
    }
    return a.exec();
}
