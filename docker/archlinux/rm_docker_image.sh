#!/bin/bash
IMAGE_ID=$(docker images | grep 'sstd_archlinux' | awk '{print $3}')
echo $IMAGE_ID
docker rmi ${IMAGE_ID}
