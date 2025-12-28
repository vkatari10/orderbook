# Orderbook

Demo orderbook with server and client side operations using FIX protocol

## Setup
1. Ensure you have docker desktop installed on your computer, open the application if already installed
2. Clone the repo to your local computer
3. Run `./scripts/docker_build.sh` (Builds the docker image, note this may take a while)
4. Run `./scripts/docker_mount.sh` (Enters the docker image)

**Note:** You should always use the second script when trying to compile or run code using this project since other scripts use the docker image's respective working directory. 

## Tests

Unit tests can be ran using `./scripts/tests_unit_run.sh` and performance tests can be ran using `./scripts/test_perf_run.sh`. Google test and Google benchmark are used for unit tests and performance tests, respectively.