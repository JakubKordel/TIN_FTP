# TIN FTP

## About the project

FTP client and server system in C++.

## Getting started

To get a local copy up and running follow these simple steps.

### Installation

Clone the repo.
```sh
git clone https://github.com/JakubKordel/TIN_FTP.git
cd TIN_FTP
make
make mainUI
```

## Usage

Run two or more terminals. One of them is going to be the server.
```sh
./Server
```
Make note of the IP address and port number the server application displays when starting. You can also set your own IP address and port by providing them as arguments:
```sh
./Server 127.0.0.1 44344
```
The server is all set now. Now you can run the client applications in other windows.
```sh
./ftp_ui
```
In the client interface you can display all commands at any time by using `help`. Let's set up connection to the server by using
the server's IP address and port number.
```
connect 127.0.0.1 44344
```
The message you receive should confirm if you've been able to successfully connect to the server.
Before being able to fully utilise the server you need to authenticate yourself. The accounts provided for testing are as followed:

| **Login** | **Password** |
| :-------- | :----------- |
| zbigniew.zuch | zuch |
| wm | wm |
| ckonopcz | ck |
| kacpernowak | nowak |
| j.kowalski | haslo |

<br/>

Example authentication:
```
login wm wm
```
If you provided unmatching credentials you'll be informed about it with a message.

Successful authentication enables usage of all the other commands. To check how to use each command use:
```
<command_name> --help
```

Commands:

* Creating a new directory:

    `mkd <directory_name>`

* Switching to the new directory:

    `cd <directory_name>`

* Uploading a file to the current directory:

    `put <file_name>`

* Downloading a file from the current directory:

    `get <file_name>`

* Listing the current directory:

    `ls`

* Logging out:

    `logout`

* Closing the connection to the server:
    
    `close`

* Exiting the application:

    `exit`
