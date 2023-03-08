# Use an official Python runtime as a parent image
FROM python:3.11-slim-buster

# Set the working directory to /app
WORKDIR /app

# Copy the Pipfile and Pipfile.lock to the container
COPY . /app/

RUN apt-get update && \
    apt-get install -y gcc && \
    apt-get clean

# Install Pipenv and your dependencies
RUN pip install pipenv && pipenv install --system

# Set the environment variable for your Python extension
ENV PYTHONPATH="/app"

# Run your Python script
CMD ["python", "fib.py"]

