# Getting Started

## Prerequisites

Before you set up the build environment in your local machine, please check the
following requirements:

* Operating system
  * Linux (Ubuntu 20.04 and later, x86_64)
* Docker
  * Docker must be able to [run without `sudo`](https://docs.docker.com/engine/install/linux-postinstall/#manage-docker-as-a-non-root-user)
* Installation
  * bash
  * curl
  * make

## Usage

### Installation

1. Clone this repository to your local machine
1. You can set up the build environment with the following command:

    ```bash
    make setup
    ```

    * If the command completed successfully, you would be able to find the Docker
    images created from Dockerfile as follows:

      ```bash
      $ docker image ls | grep car-app
      nino-kin/car-app            latest    f572acf8ada2   2 days ago    500MB
      ```

### Build

```bash
make build
```

### Testing

```bash
make tests
```

### Analyze Test Coverage

```bash
make coverage
```

### Packaging

```bash
make package
```

### Run the Application

You can run the car application by executing the following command:

```bash
make run-test-app
```

### Clean Up

```bash
make clean
```
