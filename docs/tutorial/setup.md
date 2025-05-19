# Setup 

## Environment

### Install ROS 2 Humble

This step is required.

Please check [official documentation.](https://docs.ros.org/en/humble/Installation.html)

### Install nvidia driver

This step is optional.

Please refer [Nvidia's official documentation.](https://www.nvidia.com/en-us/drivers/)

Maintainer of this package use version 550.144.03 and Nvidia RTX 3900 GPU.

```bash
Wed May 14 00:08:19 2025       
+-----------------------------------------------------------------------------------------+
| NVIDIA-SMI 550.144.03             Driver Version: 550.144.03     CUDA Version: 12.4     |
|-----------------------------------------+------------------------+----------------------+
| GPU  Name                 Persistence-M | Bus-Id          Disp.A | Volatile Uncorr. ECC |
| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |
|                                         |                        |               MIG M. |
|=========================================+========================+======================|
|   0  NVIDIA GeForce RTX 3090        Off |   00000000:01:00.0  On |                  N/A |
|  0%   44C    P8             30W /  420W |    1837MiB /  24576MiB |     16%      Default |
|                                         |                        |                  N/A |
+-----------------------------------------+------------------------+----------------------+
                                                                                         
+-----------------------------------------------------------------------------------------+
| Processes:                                                                              |
|  GPU   GI   CI        PID   Type   Process name                              GPU Memory |
|        ID   ID                                                               Usage      |
|=========================================================================================|
|    0   N/A  N/A      1113      G   /usr/lib/xorg/Xorg                            895MiB |
|    0   N/A  N/A      1402      G   /usr/bin/gnome-shell                          161MiB |
|    0   N/A  N/A   3733146      G   ...seed-version=20250506-180209.207000        251MiB |
|    0   N/A  N/A   3733155      G   ...erProcess --variations-seed-version        514MiB |
+-----------------------------------------------------------------------------------------+
```

### Install cuda/cudnn

This step is optional.

ppo_ros package depends on [libtorch_vendor package](https://github.com/team-re-boot/libtorch_vendor).  
libtorch_vendor package support CUDA/CUDNN acceleration 

Please refer [Nvidia's official documentation.](https://developer.nvidia.com/cuda-downloads)

Maintainer of this package use CUDA 12.4

### Build

```bash
mkdir -p ros2_ws/src
cd ros2_ws/src
git clone https://github.com/team-re-boot/ppo_ros.git
vcs import . < ppo_ros/dependency.repos
cd ../
colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
```

### Install genesis_ros

Please refer genesis_ros documentation.
