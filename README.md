# Description
Software that collects and stores data on the inventory of individual products in Aws DynamoDB to further analyzing. 
# Requirements
   * g++ 
   * AWS SDK C++ 
   * CMake Minimum version 3.13
   * DynamoDB database
# Configuration
Software is configured using Credentials.env file located in build folder containing fields: 

```accessKeyId:YourAwsAccessKey```

```secretKey:YourAwsAccessKy```
# Compile
 * Create build directory
```bash
mkdir build
cd build
```
* Build 
```bash
 cmake ..
 make 
```
* Run build app
```bash
./Castorama
```
# Usage
Software uses 2 databases:
* First one called names including 
  - id (Primary Key) - id of an object 
  - name - name of an object whose data are to be collected.
* Second one called quantities which is an output of an app includes 
  * lp (Primary key)
  * id - id of an object
  * quantity
  * date of recording.

By using crontab on linux app can be programmed to start every day to get the best results from the program.