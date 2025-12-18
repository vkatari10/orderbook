# Orderbook

Demo orderbook with server and client side operations using FIX protocol

# Setup

There several scripts to setup the docker image and run the project

1. Ensure you have docker desktop installed on your computer, open the application if already installed
2. Clone the repo to your local computer
3. Run `./scripts/docker_build.sh` (Builds the docker image, note this may take a while)
4. Run `./scripts/docker_start.sh` (Enters the docker image)
5. Run `./scripts/build_server.sh` (Compiles server side code)
6. Run `./scripts/build_client.sh` (Compiles client side code)
7. Run in two separate terminals:
    - `./scripts/run_client.sh` to start the client program 
    - `./scripts/run_server.sh` to start the server program 