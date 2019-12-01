# docker volume

## Tutorials
- [Share Data Between a Docker Container and Host](https://thenewstack.io/docker-basics-how-to-share-data-between-a-docker-container-and-host/)
```
mkdir ~/container-data	
docker run -dit -P --name ubuntu-test -v ~/container-data:/data ubuntu
```

