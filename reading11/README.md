Reading 11
==========

### Activity 1: Identify System Calls

**1.** Creating a file descriptor or endpoint for communicating over the 
network.

`socket()`

**2.** Lookup the address information for a particular machine or service.

`getaddrinfor()`

**3.** Assign an address to a server network file descriptor (aka assign a 
name to a socket).

`bind()`

**4.** Convert the network address structure into corresponding host and 
service strings.

`getnameinfo()`

**5.** Establish a client network file descriptor to a specified address.

`connect()`

**6.** Mark network file descriptor as waiting for incoming connections.

`listen()`

**7.** Create a new network file descriptor based on a incoming connection.

`accept()`

