FROM ubuntu:18.04

WORKDIR /home/app

COPY . /home/app

RUN apt update
RUN apt install -y make
RUN apt install -y g++
RUN apt install -y papi-tools
RUN apt install -y libpapi-dev

RUN make

ENTRYPOINT ["./bin/synthetic"]
CMD []

