.PHONY: build-and-run

# load env vars from .env file
# include .env


build-and-run:
	@docker build -t fib . && docker run -it fib


