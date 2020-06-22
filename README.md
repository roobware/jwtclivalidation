# jwtclivalidation example


## Little notes :)

The Json Webtoken is a really fine thing. Good security and easy to use.  
All big players use this and you can use some data with the token for your application, backen or API.  

If you are using Keycloak, then you have normally an App or API, where the token is granting the access.  

Compilng under Archlinux is really easy.

Under macOS you need to install the OpenSSL package. With [Homebrew](https://brew.sh) is this easy.
I have tested the same with [Anaconda](https://anaconda.org), but i was not happy.  

With homebrew you can easely add the library to yur project (Thx to [Botje on stackoverflow](https://stackoverflow.com/questions/59229392/how-can-i-edit-a-cmakelist-txt-file-on-clion-to-take-ldflags-and-cppflags)).
I think, this is generally a good practice to including libraries from homebrew packages.

This example use C++17.



## Platform tested

- macOS 10.15.4  
- Archlinux Manjaro Kernel 5.7.0



## Dependencis

- Thx to [jwt-cpp](https://github.com/Thalhammer/jwt-cpp) on Github.  
- OpenSSL 1.1.  



## Archlinux

### Packages

`pacman -S base-devel linux-headers`

### Compile

- Clone the repository  
- Change into folder `cd jwtclivalidation`  
- Create build folder `mkdir build`  
- Create cmake configuration `cmake -Wno-dev ..`  
- Compile `make`  

#### Output

```shell script
[~ build]# cmake -Wno-dev ..
-- The C compiler identification is GNU 10.1.0
-- The CXX compiler identification is GNU 10.1.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc - works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ - works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found OpenSSL: /usr/lib/libcrypto.so (found version "1.1.1g")
-- Configuring done
-- Generating done
-- Build files have been written to: /root/jwtclivalidation/build
[ build]# make
Scanning dependencies of target jwtclivalidation
[ 50%] Building CXX object CMakeFiles/jwtclivalidation.dir/main.cpp.o
[100%] Linking CXX executable jwtclivalidation
[100%] Built target jwtclivalidation
```



## macOS 10.15.5

### Packages

`brew install pkg-config`  
`brew install openssl`  

### Compile

Similar to Archlinux or you use an IDE.  
In my case i use [CLion](https://www.jetbrains.com/clion/) from Jetbrains for this.

#### Output

*Cmake output*

```shell script
"/Users/<user>/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/201.7846.88/CLion.app/Contents/bin/cmake/mac/bin/cmake" -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" /Volumes/<path>/jwtclivalidation
-- The C compiler identification is AppleClang 11.0.3.11030032
-- The CXX compiler identification is AppleClang 11.0.3.11030032
-- Check for working C compiler: /Library/Developer/CommandLineTools/usr/bin/cc
-- Check for working C compiler: /Library/Developer/CommandLineTools/usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /Library/Developer/CommandLineTools/usr/bin/c++
-- Check for working CXX compiler: /Library/Developer/CommandLineTools/usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found PkgConfig: /usr/local/bin/pkg-config (found version "0.29.2") 
-- Checking for module 'openssl'
--   Found openssl, version 1.1.1g
-- Configuring done
-- Generating done
-- Build files have been written to: /Volumes/<path>/jwtclivalidation/cmake-build-debug

[Finished]
```

*Compile output*

```shell script
====================[ Build | jwtclivalidation | Release ]======================
"/Users/<user>/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/201.7846.88/CLion.app/Contents/bin/cmake/mac/bin/cmake" --build /Volumes/PRIV/YOSE/jwtclivalidation/cmake-build-release --target jwtclivalidation -- -j 8
[ 50%] Building CXX object CMakeFiles/jwtclivalidation.dir/main.cpp.o
[100%] Linking CXX executable jwtclivalidation
[100%] Built target jwtclivalidation

Build finished
```


## Usage

```shell script
jwtclivalitation  Argument1 Argument2 [Argument3]
jwtclivalidation  <issuer>  <jwt>     <private_key>  
jwtclivalidation  https://<keycloak>/auth/realms/<realm> <token>
```

If private key beginning with a slash '/' or tilde '~', then will this as path used. Or else as key string.
If this argument empty, then will search for a file 'jwt.key' in the current home folder.  


## Keycloak

On Keycloak you should generate your owen key. Log in as Admin and add the private key.  
You have to generate a PEM key.  

Look this example:  
```shell script
ssh-keygen -t rsa -b 4096 -m PEM -f jwt.key
openssl rsa -in jwt.key -pubout -outform PEM -out jwt.pub
```


## Ideas and more...

You are welcome!  
You have Cmake settings for other platforms and necessary dependencies, then submit this :)