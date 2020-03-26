#!/bin/sh

GCCTAG=ubuntu1804
DOCKER_IMAGE=seabreeze:$GCCTAG

docker build -t ${DOCKER_IMAGE} docker.$GCCTAG
DOCKER="docker run --rm -it -v "$PWD":"$PWD" -w "$PWD" -v /etc/passwd:/etc/passwd:ro -u $(id -u):$(id -g)  ${DOCKER_IMAGE}"

mkdir -p cmake
test -x cmake/bin/cmake || $DOCKER /bin/sh -c 'echo "Download and install cmake in docker..." ; wget -qO- "https://cmake.org/files/v3.17/cmake-3.17.0-Linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C cmake/'

$DOCKER /bin/sh -x -c "
    export PATH=$PWD/cmake/bin:\$PATH
    mkdir -p SeaBreeze/build.$GCCTAG
    cd SeaBreeze/build.$GCCTAG
    cmake .. 
    make -j$(nproc)
"

