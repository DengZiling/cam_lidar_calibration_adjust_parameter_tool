## cam_lidar_calibration_adjust_parameter_tool
在使用autoware的相机和激光雷达联合标定工具进行标定得到的外参（旋转矩阵R和平移矩阵t）并不能很好的使相机图像和激光雷达扫描结果契合，
因此需要进行手动调参，本工具是一个QT编写的cmake工程，可以用来辅助调参。


/*本工程的作用是手动调整相机与激光雷达之间的TF变换
 * 大致流程是：先输入autoware标定工具的结果：R、t
 * 然后将R转换成欧拉角的形式，手动输入调整量
 * 最后验证修正结果，以便决定是否再次调整。
 * 作者：DWM
 * 日期：2020-12-14
 */



