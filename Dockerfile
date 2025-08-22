FROM m.daocloud.io/docker.io/library/ubuntu:24.04

LABEL maintainer="524948250@qq.com"

WORKDIR /app

ARG VERSION=1.0.0

ENV VERSION=${VERSION}

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        libcurl4-openssl-dev \
        build-essential && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY output_release/khalims-will.$VERSION khalims-will

ENTRYPOINT ["/app/khalims-will"]

