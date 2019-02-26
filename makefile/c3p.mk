PB_VERSION=3.6.1
GRPC_VERSION=1.18.0

################################################################
main: pb
	

################################################################
# release: https://github.com/protocolbuffers/protobuf/releases
pb: src/protobuf-all-${PB_VERSION}.tar.gz
	
src/protobuf-all-${PB_VERSION}.tar.gz:
	wget https://github.com/protocolbuffers/protobuf/releases/download/v3.6.1/protobuf-all-${PB_VERSION}.tar.gz -o $@ 
	cd protobuf-${PB_VERSION} && ./configure --prefix=$HOME/sdk/protobuf && make && make install
	
################################################################
# release: https://github.com/grpc/grpc/releases
grpc: src/grpc-${GRPC_VERSION}.targ.z

src/grpc-${GRPC_VERSION}.targ.z:
	wget https://github.com/grpc/grpc/archive/v1.18.0.tar.gz -O $@

################################################################
etcd:
