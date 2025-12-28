#! /usr/bin/bash
docker run -it -v $(pwd):/app \
  -w /app \
  orderbook \
  bash