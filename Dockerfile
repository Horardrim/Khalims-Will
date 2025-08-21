FROM m.daocloud.io/docker.io/library/ubuntu:24.04

LABEL maintainer="524948250@qq.com"

WORKDIR /app

ARG VERSION=1.0.0

ENV VERSION=${VERSION}

COPY output_release/khalims-will.$VERSION khalims-will

ENTRYPOINT ["/app/khalims-will"]

