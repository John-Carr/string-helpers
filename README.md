# String Helpers
A collection of compile time conversations from strings to integer
representations.
## Examples
### UUID
```cpp
// Create a UUID
UUID test = "89ede841-12aa-49e0-8727-79f2ce8552df"_uuid;
```
### IPv4
```cpp
// Create a IPv4
IPV4 test = "a.168.1.1"_ipv4;
```
### IPv6
```cpp
// Create a IPv6
IPV6 test = "2001:db8:3333:4444:5555:6666:7777:8888"_ipv6;
```
### MAC Address
```cpp
// Create a MAC Address
MAC test = "FF:FF:FF:FF:FF:FF"_mac;
```

## Building
This is a CMake based project but wrapped by a makefile to simplify building.  
To build run `make`  
To clean run `make clean`  
To run tests run `make run-test`  
Test results are located under `build/Testing/Temporary/LastTest.log`  
To generate code coverage report run `make gen-cov`  
The html report of code coverage can be found under `build/code-cov/index.html`

## Contributing
**TODO (John Carr):**

