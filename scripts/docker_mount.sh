#! /usr/bin/bash
docker run -it -p 5001:5001 -v $(pwd):/app \
  -w /app orderbook bash