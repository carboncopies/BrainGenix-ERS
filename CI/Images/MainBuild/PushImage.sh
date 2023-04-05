#!/bin/bash

docker tag ers_main_build_image 10.1.3.11:5000/ers_main_build_image
docker push 10.1.3.11:5000/ers_main_build_image