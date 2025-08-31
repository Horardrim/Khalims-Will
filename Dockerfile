FROM m.daocloud.io/docker.io/library/ubuntu:24.04

LABEL maintainer="524948250@qq.com"

WORKDIR /app

ARG VERSION=1.0.0

ENV VERSION=${VERSION}

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        libcpp-httplib-dev \
        libpqxx-dev libpq-dev \
        libhiredis-dev \
        libcurl4-openssl-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY output_release/khalims-will.$VERSION khalims-will

EXPOSE 8080

ENTRYPOINT sh -c 'if [ -f /hdm_back_door/khalims_will_env.sh ]; then . /hdm_back_door/khalims_will_env.sh; echo "POSTGRES_HOST: " $POSTGRES_HOST; fi; exec /app/khalims-will'
