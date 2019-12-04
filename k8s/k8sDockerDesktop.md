# Docker Desktop
- Windows [Docker Desktop CE/Community Edition](https://hub.docker.com/editions/community/docker-ce-desktop-windows)
- Windows [Docker Desktop EE/Enterprise Edition](https://download.docker.com/win/enterprise/DockerDesktop.msi)

## [K8s Dashboard](https://collabnix.com/kubernetes-dashboard-on-docker-desktop-for-windows-2-0-0-3-in-2-minutes/)
- [MacOS](https://rominirani.com/tutorial-getting-started-with-kubernetes-with-docker-on-mac-7f58467203fd)
- Setting up Kubernetes Dashboard
Switch to K8s docker-desktop first,
```
> kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v1.10.1/src/deploy/recommended/kubernetes-dashboard.yaml
> kubectl proxy
Starting to serve on 127.0.0.1:8001
> curl http://localhost:8001/api
```
Go to http://localhost:8001/api/v1/namespaces/kube-system/services/https:kubernetes-dashboard:/proxy/ on Browser and you will get the below JSON output:

- Config Dashboard
Run the below command to set token:
```
> $TOKEN=((kubectl -n kube-system describe secret default | Select-String "token:") -split " +")[1]
> kubectl config set-credentials docker-for-desktop --token="${TOKEN}"
> echo $TOKEN > token.txt
```
Browse to http://:8001/api/v1/namespaces/kube-system/services/https:kubernetes-dashboard:/proxy/,
Click on Kubeconfig and select the “config” file under C:\Users<Username>.kube\config
or 
copy the $token using Token to login.
The k8s dashboard will be shown.
