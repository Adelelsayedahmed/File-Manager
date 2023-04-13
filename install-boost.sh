#!/bin/bash

# Specify Boost version and installation directory
boost_version=1.81.0
install_dir=/usr/local
output=boost_1_81_0.tar.gz
if [ -f "$output" ]; then
	 echo "File already exists."
else
# Download Boost source code
	wget https://boostorg.jfrog.io/artifactory/main/release/$boost_version/source/boost_1_81_0.tar.gz
fi
sudo tar -xvf boost_1_81_0.tar.gz
cd boost_1_81_0

# Build and install Boost
sudo ./bootstrap.sh --prefix=$install_dir
sudo ./b2 install

# Clean up
cd ..
rm boost_1_81_0.tar.gz
