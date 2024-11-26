# how to build a Miracl library

you can refer to https://github.com/hitfzyangdianshi/miracl_build_files.git for the bash file needed (.sh and mirdef.h) to build library (.a) on Pi or Linux. Also, there is an example to use VS2019 to build the library(.lib)

If you want to build the library from the source code https://github.com/miracl/MIRACL.git  , you can follow the steps below:

1. make a new folder "miracl_config" in the root of the MIRACL 
2. copy "config.c" into this folder
3. run "config.c", and select options according to your system. you can use default values for most options.

Alternative: follow this guide "https://adityagudimetla.medium.com/installing-miracl-for-dummies-7eb7192c3285"

# how to build FUSE library
Refer to: "https://github.com/AppImage/AppImageKit/wiki/FUSE" for dependency install in linux
For 22.04 ubuntu:
1. sudo add-apt-repository universe
2. sudo apt install libfuse2
3. sudo apt install libfuse-dev
4. sudo apt install pkg-config

after successfully install fuse in linux, create a test directory somewhere in your system named it custom_auth_fs.
change custom_auth.cpp root_path to your custom_auth_fs

To mount:
./custom_auth -d yourpathto/custom_auth_fs

-d is used to show detail verbose

Can check the custom_auth_fs directory by running ls -la to the directory, if the time is change to your mount time then it is successful.


# values: 

Ui : User i (userid)

Si : secret_seed for Ui

Oi : Operation i

Ri : Resource i

Ts : Timestamp

GAij : Granted Access from Ui in session j

SGAi : one selected historical Granted Access from Ui

VPij : Verification Point from Ui in session j







# functions:

## bf_check

0 - element is not present
1 - element is present(or false positive due to collision)
-1 - bloom not initialized

## bf_add

0 - element was not present and was added
1 - element(or a collision) had already been added previously
-1 - bloom not initialized

## getRequest
return Latest Bloom Filter from Blockchain

## postRequest
send the latest bloom filter to the Blockchain

## char* hashing
sha256(*str) -> hash

## secret_generate
return random 4 digits value

## convert_to_hexadecimal
str -> hex

## convert_from_hexadecimal
hex -> str (in bloomfilter datatype)

## concatenateData
return str(Ui + Oi + Ri + Ts)

## generateVerificationPoint
return VPi

## checkVerificationPoint
true - record "might" be present (Authorized Access)
false - record is not present (Unauthorized Access)

## addVerificationPoint
add new VPi to Bloom Filter

## userRequest
- Granted Access (represented by GAi value)
- Access Denied (represented by "Access Denied")

## authUserRequest (PoC only)
return Granted Access (represented by GAi value)
 
## userTimerRequest (time evaluation)
print out time needed to run the whole user request process

## userTimerGenerationRequest (time evaluation)
print out time needed to run the VP Generation Process

## userTimerVerificationRequest (time evaluation)
print out time needed to run the Verification Process





# files and folders
- [api.cpp](/Gateway_C++/api.cpp) : C++ Get and Post Request using libcurl
- [function.cpp](/Gateway_C++/function.cpp) : hashing, secret seeds read and write, conversion from hex to char and vice versa
- [gateway.cpp](/Gateway_C++/gateway.cpp) : Generate VPs, Add and Check VPs on Bloom Filter, access point (user/account/IOT device request)
- [gateway_auto.cpp](/Gateway_C++/gateway_auto.cpp) : Generate VPs, Add and Check VPs on Bloom Filter, access point (user/account/IOT device request) without the need of manually providing user id.
- [bloom_func.cpp](/Gateway_C++/bloom_func.cpp) : bloom filter function using [bloom.c] as its based.

- [user.cpp](/Gateway_C++/user.cpp) : act as end devices that connected to gateway
- [auth_user.cpp](/Gateway_C++/auth_user.cpp) : authenticated end devices (user) that connected to gateway (Does not required to have MFA) - Testing purpose only
- [user_timer.cpp](/Gateway_C++/user_timer.cpp) : run time testing for evaluation section
- [user_auto.cpp](/Gateway_C++/user_auto.cpp) : automize userid using getuid() in linux server.
- [custom_auth.cpp](/Gateway_C++/custom_auth.cpp) : custom authorization code using FUSE in linux 

- [granted_access](/Gateway_C++/granted_access/) : granted access (GA) history temporary database (Saved based on UserID) - Own by corresponding end devices based on their subfolder.

- [secred_seed](/Gateway_C++/secret_seed/) : secret seed generated and saved by gateway - Only accessible by Gateway

- [verification_point](/Gateway_C++/verification_point/) : verification point (VP) history temporarily saved by Gateway

- [custom_auth.sh] : is used to compile custom_auth.cpp generate [custom_auth]

- [auto_compile.sh] : is used to compile user_auto.cpp generate [user_auto]

- [time_compile.sh] : is used to compile user_timer.cpp generate [user_timer]

- [auth_compile.sh] : is used to compile auth_user.cpp generate [auth_user]

- [compile.sh] : is used to compile user.cpp generate [user]

- [run_user.sh] : is used to run [user] with parameters

- [auth_run.sh] : is used to run [auth_user] with parameters

- [timers.sh] : is used to run [user_timer] with parameters and choice of Time Evaluation

- [auto_run.sh] : is used to run [user_auto] with parameters (No Ui)

- [custom_auth.sh] : is used to compile custom_auth.cpp

- [custom_authorization.txt] : parameters used on custom_auth

#Step to run:
- run [custom_auth.sh], mount the custom_auth to the folder. access the folder using terminal to get result. 

- change [custom_authorization.txt] parameters to "0" and "0", this is to run pre authorization for starting value.

- get the [granted access] value based on the folder generated, copy the name of the [granted_access_xxx.txt] and pasted it on the first parameters on custom_authorization.txt

- change the 2nd parameters to run each time evaluation process
1: Generation + Storing + Verification (Not useful for testing)
2: Generation
3: Storing
4: Verification
0: No timer Evaluation

only required to run 2 & 4 on second parameters to get data for timer evaluation.