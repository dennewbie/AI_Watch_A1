<p>
    <div align="center">
        <h1> AI Watch A1 </h1>
    </div>
    <div align="justify">
        <h3> AI Watch A1 uses one Intel RealSense D435 camera and OpenPose in order to achieve multi-person 3D skeleton tracking. Once this task is completed, AI Watch A1 provides support to send each detected skeleton and its joint points' 3D coordinates (room and D435's details have to be specified) via Kafka, in order to let further detached computation possible.
        </h3>
    </div>
    <div align="center">
        <img src="https://github.com/dennewbie/AI_Watch_A1/blob/main/design/eye_big_white@2x.png" width="400">
    </div>
</p>

<p><div></div></p>

## Keynote 📋
...



## Demo 💻
- [Demo #1](https://youtu.be/Ac0V8Dj0FbI)
- [Demo #2]()



## Docs 📜
- [AI Watch A1 documentation](https://dennewbie.github.io/AI_Watch_A1/doc/index.html) is generated using [Doxygen](https://doxygen.nl/).
- BSc Computer Science's Thesis



## Installation 🚀
1. Install [RealSense SDK 2.0](https://github.com/IntelRealSense/librealsense) and its own dependencies.

2. Install [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose) and its own dependencies.

3. Install [Confluent](https://www.confluent.io/) and its own dependencies.

4. Run the following command in your terminal:
   ```
   git clone --recursive git@github.com:dennewbie/AI_Watch_A1.git
   ```

5. From `/AI_Watch_A1/src/AI_Watch_A1/` folder, run the following commands in your terminal:
   
   ```
   mkdir build && cd build
   ```
   
6. Copy OpenPose's `models` folder to the project's build folder.

7. Copy OpenPose's `BoostConfig.cmake`, `FindGFlags.cmake` and `FindGlog.cmake` files  to the `build/cmake/modules/` folder.

8. Run the following commands in your terminal:
   
   ```
   cmake .. && make -j \`sysctl -n hw.logicalcpu\`
   ```

9. Now let's tart the Kafka environment. Run the following commands in a new terminal session. Set the environment variable for the Confluent Platform home directory:
    ```
    export CONFLUENT_HOME=confluent-7.2.1
    ```
    Add the Confluent Platform bin directory to your PATH:
    ```
    export PATH=$PATH:$CONFLUENT_HOME/bin
    ```
    Test your installation by running the confluent command:
    ```
    confluent --help
    ```
    Your output should show the available commands for managing Confluent Platform.

    Start Confluent Platform by using the Confluent CLI confluent local services start command. This command starts all of the Confluent Platform components, including Kafka, ZooKeeper, Schema Registry, HTTP REST Proxy for Kafka, Kafka Connect, ksqlDB, and Control Center. 
    ```
    confluent local services start
    ```

    Your output should resemble:
    ```
    Starting Zookeeper
    Zookeeper is [UP]
    Starting Kafka
    Kafka is [UP]
    Starting Schema Registry
    Schema Registry is [UP]
    Starting Kafka REST
    Kafka REST is [UP]
    Starting Connect
    Connect is [UP]
    Starting KSQL Server
    KSQL Server is [UP]
    Starting Control Center
    Control Center is [UP]
    ```

    ### Important #1 📌
    The confluent local commands are intended for a single-node development environment and are not suitable for a production environment. The data that are produced are transient and are intended to be temporary. For production-ready workflows, see Install and Upgrade Confluent Platform.

    ### Important #2 📌
    The Confluent CLI requires Java version 1.8 or 1.11.
    See [Confluent versions interoperability](https://docs.confluent.io/current/installation/versions-interoperability.html)
   
10. Navigate to http://localhost:9021 and create a new topic `t1` with default settings. Now go to `/AI_Watch_A1/src/AI_Watch_A1/` and set up your [Kafka](https://github.com/edenhill/librdkafka) parameters within the `configuration_file.ini` file. At this point:
    - if internal OpenPose execution is chosen, then run the following command in your terminal:
   
        ```
        sudo ./hello_librealsense2.bin --num_gpu 1 --num_gpu_start 2 --image_dir rs_images/rgb --write_json op_output/op --logging_level 255
        ```
    - if external OpenPose execution is chosen, then set up your OpenPose parameters within the "conf.conf" file, run the following command in your terminal:

        ```
        sudo ./hello_librealsense2.bin
        ```



## Tools 🛠
- [Intel RealSense SDK](https://github.com/IntelRealSense/librealsense)
- [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
- [Kafka](https://kafka.apache.org/)
- [Kafka C/C++ library](https://github.com/edenhill/librdkafka)
- [Confluent](https://www.confluent.io/)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- [Doxygen](https://doxygen.nl/)
- [StarUML](https://staruml.io/)
- [Sketch](https://www.sketch.com/)



## Contributing 👨🏻👳🏾‍♂️👩🏼‍🦱👽
In order to contribute to AI Watch A1, please follow the [contribution guidelines](https://github.com/dennewbie/AI_Watch_A1/blob/main/CONTRIBUTING.md).



## License ☢️
AI Watch A1 is licensed under the Apache License, Version 2.0. Copyright 2022. Please, see the [license](https://github.com/dennewbie/AI_Watch_A1/blob/main/LICENSE) for further details and the `/licenses` folder for the used libraries' licenses details.



## Contacts 🪪
- [LinkedIn](https://www.linkedin.com/in/denny-caruso/)



## Supervisor
- Dr. Alessio Ferone, CS Assistant Professor at the University of Naples Parthenope



a.a. 2021/2022