# K8S Node Affinity
Kubernetes scheduling is the process of selecting a suitable node to run pods.
- Node Selector: define label-key value pairs in nodes and use these labels to match when scheduling pods.
- Node Affinity
- Node Anti-Affinity

## Node Selector: Simple
```
kubectl label nodes <node-name> <key>=<value>
spec:
  containers:
  - name: nginx
    image: nginx
  nodeSelector:
    <key>: <value>
```
## Node affinity ; Pod affinity/anti-affinity: Advanced & Complexed features
- Define rules, including conditions with logical operators.
- Create “preferred” and “required” rules for a greater variety of matching conditions.
- Match labels of pods running within nodes and determine the scheduling location of new pods.

There are two types of affinity: Kubernetes node affinity and Kubernetes pod affinity:
- Node affinity attracts pods to nodes, enables administrators to match pods according to the labels on nodes.Node affinity is specified in the PodSpec using the nodeAffinity field in the affinity section.
- Pod affinity attracts pods to pods, provides administrators with a way to configure the scheduling process using labels configured on the existing pods within a node. Use podAffinity and podAntiAffinity fields in the PodSpec.

### Required vs. preferred rulesPermalink

Both node affinity and pod affinity can set required and preferred rules that act as hard and soft rules. You can configure these rules with the following fields in a pod manifest:
- requiredDuringSchedulingIgnoredDuringExecution
- preferredDuringSchedulingIgnoredDuringExecution
These rules are valid for both node and pod affinity and can be configured using the respective affinity fields.

### anti-affinity vs taints and tolerations
Both features prevent pods from being scheduled on specific nodes. The primary difference is that anti-affinity uses matching conditions based 
on labels while taints are applied to the node and match tolerations defined in pod manifests.

 taints and tolerations are a better option to stop pods from being scheduled on specific nodes. affinity, anti-affinity, taints, and tolerations are not mutually exclusive
 
 
