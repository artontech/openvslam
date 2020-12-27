docker build -t openvslam-socket -f Dockerfile.socket . --build-arg NUM_THREADS=16

cd viewer
docker build -t openvslam-server .
