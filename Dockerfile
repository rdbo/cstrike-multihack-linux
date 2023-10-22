FROM debian:testing

WORKDIR /app

COPY . .

RUN dpkg --add-architecture i386
RUN apt-get update
RUN apt-get -y install gcc gcc-multilib g++ g++-multilib gdb git cmake make python3 bash pkg-config vim libsdl2-dev libsdl2-dev:i386

CMD /bin/bash