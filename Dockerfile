FROM ubuntu:20.04


ENV TZ=Asia/Tokyo
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get -y install \
    git \
    build-essential \
    python3.8 python3-pip python3-venv \
    lcov \
    clang-format \
    clang-tidy \
    curl && \
    curl -LO https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 && \
    chmod +x bazelisk-linux-amd64 && \
    mv bazelisk-linux-amd64 /usr/local/bin/bazelisk && \
    pip install pre-commit

ARG WORK_DIR=/app
WORKDIR $WORK_DIR

ARG HOST_UID
ARG HOST_GID
RUN groupadd -g $HOST_GID mygroup && \
    useradd -u $HOST_UID -g $HOST_GID -ms /bin/bash myuser
USER myuser

CMD ["bash"]
