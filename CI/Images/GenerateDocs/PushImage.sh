#!/bin/bash

docker tag ers_generate_docs_image 10.1.3.11:5000/ers_generate_docs_image
docker push 10.1.3.11:5000/ers_generate_docs_image