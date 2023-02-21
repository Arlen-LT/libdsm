#!/bin/bash
cmake --version
cmake --preset armv7
pushd armv7/build
cmake --build .
cmake --install .
popd