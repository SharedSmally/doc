# [Config](https://kubernetes.io/docs/concepts/configuration/)
- [Overview](https://kubernetes.io/docs/concepts/configuration/overview/)


## [ConfigMaps](https://kubernetes.io/docs/concepts/configuration/configmap/)
A ConfigMap is an API object used to store non-confidential data in key-value pairs. 
Pods can consume ConfigMaps as environment variables, command-line arguments, or as configuration files in a volume.

A ConfigMap allows you to decouple environment-specific configuration from your container images, so that your applications are easily portable.
```
apiVersion: v1
kind: ConfigMap
metadata:
  name: game-demo
data:
  # property-like keys; each key maps to a simple value
  player_initial_lives: "3"
  ui_properties_file_name: "user-interface.properties"

  # file-like keys
  game.properties: |
    enemy.types=aliens,monsters
    player.maximum-lives=5
  user-interface.properties: |
    color.good=purple
    color.bad=yellow
    allow.textmode=true
```

There are four different ways that you can use a ConfigMap to configure a container inside a Pod:
- Inside a container command and args
- Environment variables for a container
- Add a file in read-only volume, for the application to read
- Write code to run inside the Pod that uses the Kubernetes API to read a ConfigMap
```
apiVersion: v1
kind: Pod
metadata:
  name: configmap-demo-pod
spec:
  containers:
    - name: demo
      image: alpine
      command: ["sleep", "3600"]
      env:
        # Define the environment variable
        - name: PLAYER_INITIAL_LIVES # Notice that the case is different here
                                     # from the key name in the ConfigMap.
          valueFrom:
            configMapKeyRef:
              name: game-demo           # The ConfigMap this value comes from.
              key: player_initial_lives # The key to fetch.
        - name: UI_PROPERTIES_FILE_NAME
          valueFrom:
            configMapKeyRef:
              name: game-demo
              key: ui_properties_file_name
      volumeMounts:
      - name: config
        mountPath: "/config"
        readOnly: true
  volumes:
    # You set volumes at the Pod level, then mount them into containers inside that Pod
    - name: config
      configMap:
        # Provide the name of the ConfigMap you want to mount.
        name: game-demo
        # An array of keys from the ConfigMap to create as files
        items:
        - key: "game.properties"
          path: "game.properties"
        - key: "user-interface.properties"
          path: "user-interface.properties"
```
For this example, defining a volume and mounting it inside the demo container as /config creates two files, /config/game.properties and
/config/user-interface.properties, even though there are four keys in the ConfigMap. This is because the Pod definition specifies an 
items array in the volumes section. If you omit the items array entirely, every key in the ConfigMap becomes a file with the same name 
as the key, and you get 4 files

[See sample](https://ralph.blog.imixs.com/2020/07/19/kubernetes-how-to-map-config-files/)

To use the binay data, create 2 configmaps. One for binary files like ewallet and one for text config files  like sysctl.conf, init.ora....
```
kubectl create configmap walletconfigmap --from-file=ewallet1 --from-file=ewallet2
kubectl create configmap textconfigmap --from-file=sysctl.conf  --from-file=jdbc.xml  --from-file=init.ora  
kubectl get configmap walletconfigmap -o yaml . # You would see ewallet would be stored as binaryData
```

## [Secrets](https://kubernetes.io/docs/concepts/configuration/secret/)
A Secret is an object that contains a small amount of sensitive data such as a password, a token, or a key. 
Such information might otherwise be put in a Pod specification or in an image. Users can create Secrets and the system also creates some Secrets.

To use a Secret, a Pod needs to reference the Secret. A Secret can be used with a Pod in three ways:
- As files in a volume mounted on one or more of its containers.
- As container environment variable.
- By the kubelet when pulling images for the Pod.

When creating a Secret, you can specify its type using the type field of the Secret resource, or certain equivalent kubectl command line flags (if available). 
- **Opaque**:	arbitrary user-defined data
- **kubernetes.io/service-account-token**:	service account token
- **kubernetes.io/dockercfg**:	serialized ~/.dockercfg file
- **kubernetes.io/dockerconfigjson**:	serialized ~/.docker/config.json file
- **kubernetes.io/basic-auth**:	credentials for basic authentication
- **kubernetes.io/ssh-auth**:	credentials for SSH authentication
- **kubernetes.io/tls**:	data for a TLS client or server
- **bootstrap.kubernetes.io/token**:	bootstrap token data
```
kubectl create secret generic empty-secret
kubectl get secret empty-secret

apiVersion: v1
kind: Secret
metadata:
  name: secret-sa-sample
  annotations:
    kubernetes.io/service-account.name: "sa-name"
type: kubernetes.io/service-account-token
data:
  # You can include additional key value pairs as you do with Opaque Secrets
  extra: YmFyCg==
```

## [Managing Resources for Containers](https://kubernetes.io/docs/concepts/configuration/manage-resources-containers/)
Each Container of a Pod can specify one or more of the following:
- spec.containers[].resources.limits.cpu
- spec.containers[].resources.limits.memory
- spec.containers[].resources.limits.hugepages-<size>
- spec.containers[].resources.requests.cpu
- spec.containers[].resources.requests.memory
- spec.containers[].resources.requests.hugepages-<size>

```
apiVersion: v1
kind: Pod
metadata:
  name: frontend
spec:
  containers:
  - name: app
    image: images.my-company.example/app:v4
    resources:
      requests:
        memory: "64Mi"
        cpu: "250m"
      limits:
        memory: "128Mi"
        cpu: "500m"
  - name: log-aggregator
    image: images.my-company.example/log-aggregator:v6
    resources:
      requests:
        memory: "64Mi"
        cpu: "250m"
      limits:
        memory: "128Mi"
        cpu: "500m" 
```

## [Organizing Cluster Access Using kubeconfig Files](https://kubernetes.io/docs/concepts/configuration/organize-cluster-access-kubeconfig/)

Use kubeconfig files to organize information about clusters, users, namespaces, and authentication mechanisms. 
The kubectl command-line tool uses kubeconfig files to find the information it needs to choose a cluster and communicate with the API server of a cluster.

By default, kubectl looks for a file named config in the $HOME/.kube directory. You can specify other kubeconfig files by setting the KUBECONFIG environment
variable or by setting the --kubeconfig flag.
```
apiVersion: v1
clusters:
- cluster:
    certificate-authority: /home/wchen/.minikube/ca.crt
    server: https://192.168.49.2:8443
  name: minikube
contexts:
- context:
    cluster: minikube
    namespace: default
    user: minikube
  name: minikube
current-context: minikube
kind: Config
preferences: {}
users:
- name: minikube
  user:
    client-certificate: /home/wchen/.minikube/profiles/minikube/client.crt
    client-key: /home/wchen/.minikube/profiles/minikube/client.key
```

## [Pod Priority and Preemption](https://kubernetes.io/docs/concepts/configuration/pod-priority-preemption/)
