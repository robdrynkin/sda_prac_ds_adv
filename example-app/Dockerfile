FROM rikorose/gcc-cmake:latest

RUN apt-get update
RUN apt-get install -y wget unzip libgtest-dev

RUN mkdir /usr/data
WORKDIR /usr/src/app

COPY http http
COPY src src
COPY tests tests
COPY CMakeLists.txt CMakeLists.txt


ADD https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip libtorch-shared-with-deps-latest.zip
RUN unzip libtorch-shared-with-deps-latest.zip

RUN mkdir build && cd build && cmake -DCMAKE_PREFIX_PATH=/usr/src/app/libtorch ..
RUN cd build && cmake --build . --config Release

CMD ["./build/example-app", "0.0.0.0", "8080", "/usr/data"]
