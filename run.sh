
#docker run -it --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix/:/tmp/.X11-unix:ro -v /data/project/openvslam/input:/openvslam/build/input -v /data/project/openvslam/output:/openvslam/build/output --gpus all openvslam-desktop

docker stop openvslam-server
docker stop openvslam-socket

docker run --rm -d --name openvslam-server --net=host openvslam-server
docker run --rm -it --name openvslam-socket --net=host --gpus all \
    -v /data/project/openvslam/input:/openvslam/build/input \
    -v /data/project/openvslam/output:/openvslam/build/output \
    -v /data/project/openvslam/build:/openvslam/build \
    -v /data/project/openvslam/example:/openvslam/example \
    -v /data/project/AutoCamera/control/data/rgb:/openvslam/build/input/images \
    openvslam-socket

#./run_image_slam -v ./input/orb_vocab.dbow2 -c ./input/config.yaml -i ./input/images --map-db ./output/map.msg
#./run_image_localization -v ./input/orb_vocab.dbow2 -c ./input/config.yaml -i ./input/images --map-db ./output/map.msg

# ./run_video_slam -v ./input/orb_vocab.dbow2 -c ./input/aist_living_lab_1/config.yaml -m ./input/aist_living_lab_1/video.mp4 --frame-skip 3 --map-db ./output/aist_living_lab_1/map.msg
# ./run_video_slam -v ./input/orb_vocab.dbow2 -c ./input/config.yaml -m ./input/video.mp4 --frame-skip 3 --map-db ./output/map.msg
