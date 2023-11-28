# R-Type Project
___

Welcome to the R-Type Project repository! This is a simple guide to help you get started with building and running the server and client for the R-Type game.

# Install

Before you can run the server and client, please make sure you have CMake installed, and it's a recent version, preferably 3.13 or higher.

1. **Clone the Repository:**

   You can start by cloning this repository to your local machine using Git.

   ```bash
   git clone git@github.com:EpitechPromo2026/B-CPP-500-PAR-5-1-rtype-adam.bentaleb.git
   ```

2. **Build the project**

-Open a terminal:

On Windows:
   -Execute ```cmake .``` bash in the project's root directory.
   -Execute ```cmake --build``` to build the project and obtain the binaries.

On Linux:
  -Execute ```cmake .``` in the project's root directory.
  -Execute ```make``` bash in the project's root directory to build the entire project and obtain the binaries.

# Launch the server

- Execute "./Server/Server -p [port]"

# Launch the Client

Run the client executable and specify the IP address and port of the server you want to connect to. Replace [ip] and [port] with the server's IP address and port.
```bash
./Client/Client [ip] [port]
```
Then write the port of the lobby you want to join.
Now you can play

# Developer documentation

1. **Clone the Repository:**

   You can start by cloning this repository to your local machine using Git.

   ```bash
   git clone git@github.com:EpitechPromo2026/B-CPP-500-PAR-5-1-rtype-adam.bentaleb.git
   ```
2. **Build the documentation**

   ```bash
   cd SphinxDoc
   make html
   ```

3. **Open it**

   Open ```_build/html/index.html``` in your browser.
   
