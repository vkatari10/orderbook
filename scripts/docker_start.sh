docker run -it \
  -u $(id -u):$(id -g) \
  -v $(pwd):/app \
  -w /app \
  orderbook \
  bash
