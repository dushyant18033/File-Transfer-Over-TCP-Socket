# File-Transfer-Over-TCP-Socket
A simple C code for file transfer over TCP socket connection between client and server

### How to run?
1. In order to test transferring any file, plz copy it to the server root directory.
2. Run the server. (cd into the server directory and run ./server)
3. Run the client. (cd into the client directory and run ./client)
4. The client will connect immediately to the server.
5. On the client side, enter the path to the file relative to the server directory to begin file transfer.

### A few limitations
1. Currently, the client and server communicate via localhost interface but can be programmed to talk over any network.  
2. The code was designed and tested on Linux, hence may or may not work on Windows and Mac OS.
