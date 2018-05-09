# compile gcc:

Building GCC requires GMP 4.2+, MPFR 2.4.0+ and MPC 0.8.0+.
Try the --with-gmp, --with-mpfr and/or --with-mpc options to specify
```
     yum install -y gmp-devel mpfr-devel libmpc-devel     
     yum install -y glibc-dev libstdc++-devel
```     

Missing ctn.o: No lib for 32bits; Only lib for 64bits
```
     --disable-multilib 
```

configure: error: error verifying int64_t uses long long:  Need to install gcc-c++:
```
     yum install -y gcc-c++
```
