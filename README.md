<p>
    <div align="center">
        <h1> AI Watch A1 </h1>
    </div>
    <div align="justify">
        <h3> AI Watch A1 uses one Intel RealSense D435 camera and OpenPose in order to achieve Multi-person 3D skeleton tracking. Once this task is completed, AI Watch A1 provides support to send each detected skeleton and its joint points' 3D coordinates (room and D435's details have to be specified) via Kafka, in order to let further detached computation possible.
        </h3>
    </div>
    <div align="center">
        <img src="https://github.com/dennewbie/AI_Watch_A1/blob/main/design/eye_big_white@2x.png" width="400">
    </div>
</p>

<p><div></div></p>

### Keynote
[Keynote](...)



### Demo
...



### Docs
[Doxygen Documentation](https://dennewbie.github.io/AI_Watch_A1/doc/index.html)



### Installation
1. Install [RealSense SDK 2.0](https://github.com/IntelRealSense/librealsense) and its own dependencies.

2. Install [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose) and its own dependencies.
3. `git clone --recursive git@github.com:dennewbie/AI_Watch_A1.git`
4. Go to `/AI_Watch_A1/src/AI_Watch_A1/` and set up your [Kafka](https://github.com/edenhill/librdkafka) parameters within the `configuration_file.ini` file
5. From `/AI_Watch_A1/src/AI_Watch_A1/` folder, run the following commands in your terminal:
   
   ```
   mkdir build && cd build
   ```
   
6. Copy OpenPose's `models` folder to the project's build folder.
7. Copy OpenPose's `BoostConfig.cmake`, `FindGFlags.cmake` and `FindGlog.cmake` files  to the `build/cmake/modules/` folder

8. Run the following commands in your terminal:
   
   ```
   cmake .. && make -j \`sysctl -n hw.logicalcpu\`
   ```
   
9. 
    - If internal OpenPose execution is chosen, then run the following command in your terminal:
   
        ```
        sudo ./hello_librealsense2.bin --num_gpu 1 --num_gpu_start 2 --image_dir rs_images/rgb --write_json op_output/op --logging_level 255
        ```
   
   - If external OpenPose execution is chosen, then set up your OpenPose parameters 
   within the "conf.conf" file, run the following command in your terminal:

        ```
        sudo ./hello_librealsense2.bin
        ```



### Tools
- [Intel RealSense SDK](https://github.com/IntelRealSense/librealsense)
- [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
- [Kafka](https://kafka.apache.org/)
- [Kafka C/C++ library](https://github.com/edenhill/librdkafka)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- [StarUML](https://staruml.io/)
- [Sketch](https://www.sketch.com/)

a.a. 2021/2022