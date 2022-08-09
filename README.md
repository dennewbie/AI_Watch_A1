# AI Watch A1

![projectLogo](https://github.com/dennewbie/AI_Watch_A1/blob/main/design/eye_small_white%402x.png)

AI Watch A1 uses one Intel RealSense D435 camera and OpenPose in order to achieve 3D human-skeleton tracking.

### Keynote
[Keynote](...)

### Demo
...




### Docs
[Doxygen Documentation](https://dennewbie.github.io/AI_Watch_A1/doc/index.html)


### Installation
1. Install RealSense SDK 2.0 and its own dependencies.
2. Install OpenPose and its own dependencies.
3. Go to the downloaded project folder.
4. Set up your Kafka parameters within "configuration_file.ini"
5. Run the following commands in your terminal:
   
   mkdir build && cd build
   
6. Copy OpenPose's "models" folder to the project's build folder.
7. Copy OpenPose's "BoostConfig.cmake", "FindGFlags.cmake" and "FindGlog.cmake" files  to the build/cmake/modules/ folder

8. Run the following commands in your terminal:
   
   cmake .. && make -j`sysctl -n hw.logicalcpu`
   
9.1. If internal OpenPose execution is chosen, then run the following command in your terminal:
   
   sudo ./hello_librealsense2.bin --num_gpu 1 --num_gpu_start 2 --image_dir rs_images/rgb --write_json op_output/op --logging_level 255
   
9.2. If external OpenPose execution is chosen, then set up your OpenPose parameters 
   within the "conf.conf" file, run the following command in your terminal:
   


### Tools
- [Intel RealSense SDK](https://github.com/IntelRealSense/librealsense)
- [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
- [StarUML](https://staruml.io/)
- [Sketch](https://www.sketch.com/)

a.a. 2021/2022