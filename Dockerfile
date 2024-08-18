FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y cmake
RUN apt-get install -y valgrind
RUN apt-get install -y g++ 
RUN apt-get install -y git
RUN git clone https://github.com/google/googletest.git /usr/src/googletest
RUN cd /usr/src/googletest && \
    cmake . && \
    make && \
    make install
RUN apt-get clean

COPY . /usr/src/app

WORKDIR /usr/src/app/src

RUN make test_docker


ENTRYPOINT ["valgrind", "--leak-check=full", "--track-origins=yes", "./s21_tests"]
