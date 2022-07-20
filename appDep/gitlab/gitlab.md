# Gitlab 

## Setup Giblab as Docker (https://docs.gitlab.com/ee/install/docker.html)
- Set up the volumes location: the directory to store the configuration, logs, and data files. 
```
export GITLAB_HOME=/srv/gitlab
```
- Install GitLab using Docker Engine
```
sudo docker run --detach \
  --hostname gitlab.example.com \
  --publish 443:443 --publish 80:80 --publish 22:22 \
  --name gitlab \
  --restart always \
  --volume $GITLAB_HOME/config:/etc/gitlab \
  --volume $GITLAB_HOME/logs:/var/log/gitlab \
  --volume $GITLAB_HOME/data:/var/opt/gitlab \
  --shm-size 256m \
  gitlab/gitlab-ee:latest  
```
Changed to:
```
  --publish 444:443 --publish 81:80 --publish 23:22 \
```  
- Delete the container
```
 git container rm gitlab
```
- Track the gitlab install process 
```
sudo docker logs -f gitlab
```
- Visit the GitLab URL, and log in with username root and the password from the following command:
```
sudo docker exec -it gitlab grep 'Password:' /etc/gitlab/initial_root_password
```
http://gitlab.example.com:81/
