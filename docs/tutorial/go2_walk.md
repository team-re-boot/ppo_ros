# GO2 walk

## Run with simulation

**At first, launch ppo_ros with simulation mode.**

```bash
ros2 launch ppo_ros ppo_ros.launch.xml use_sim_time:=True use_cuda:=True simulation:=False
```

`use_cuda` option should be configured based on your environment.

**Second, launch genesis_ros**

```bash
uv run ppo_eval -e go2_walking -d gpu --ckpt 100 -i ros
```

**Wait...**

Genesis initialization takes about 20~30 seconds in my environment.

Please wait patiently.

**Walk!**

<iframe width="560" height="315" src="https://www.youtube.com/embed/cZdMWFHC0Es?si=OPDfk3Iw27dMhfWi" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
