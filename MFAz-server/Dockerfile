# Use a base image compatible with your project
FROM ubuntu:22.04

# Set environment variables for non-interactive installation
ENV DEBIAN_FRONTEND=noninteractive
# Install necessary runtime dependencies
RUN apt-get update && apt-get install -y \
    libboost-all-dev \
    libssl-dev \
    libz-dev \
    libpcre3-dev \
    libsqlite3-dev \
    libcurl4-openssl-dev \
    && apt-get clean

# Set the working directory in the container
WORKDIR /app

# Copy the entire project into the container
COPY . .

COPY lib /usr/local/lib/

ENV LD_LIBRARY_PATH=/usr/local/lib:/libs:$LD_LIBRARY_PATH

# Expose the port your server listens on
EXPOSE 8080

# Run your application (adjust the binary name/path if necessary)
CMD ["./test", "-c", "config.js"]
