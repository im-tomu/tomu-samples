FROM ubuntu:trusty

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update
RUN apt-get install -yy software-properties-common python-software-properties
RUN apt-add-repository -y ppa:team-gcc-arm-embedded/ppa
RUN apt-get update
RUN apt-get install -yy gcc-arm-embedded build-essential git wget libc6-i386

RUN mkdir /code
WORKDIR /code
VOLUME /code

RUN useradd -ms /bin/bash tomu
RUN chown -R tomu /code
USER tomu

