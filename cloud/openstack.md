# [OpenStack](https://www.openstack.org/)

## Architecture
![Conceptual Arch](https://docs.openstack.org/install-guide/_images/openstack_kilo_conceptual_arch.png)

## Deployment
![Hardware Requirements](https://docs.openstack.org/install-guide/_images/hwreqs.png)

- **Controller node**: runs the Identity service, Image service, Placement service, management portions of Compute, management portion of Networking, various Networking agents, and the Dashboard. Also includes supporting services such as an SQL database, message queue, and NTP.
- **Compute node**: runs the hypervisor portion of Compute that operates instances. Also runs a Networking service agent that connects instances to virtual networks and provides firewalling services to instances via security groups.
- **Block Storage**: contains the disks that the Block Storage and Shared File System services provision for instances.service traffic between compute nodes and this node uses the management network. 
- **Object Storage**: contain the disks that the Object Storage service uses for storing accounts, containers, and objects. Service traffic between compute nodes and this node uses the management network. 

## Networking
### Provider networks:
![provider](https://docs.openstack.org/install-guide/_images/network1-services.png)

The simplest way with primarily layer-2 (bridging/switching) services and VLAN segmentation of networks, bridges virtual networks to physical networks and relies on physical network infrastructure for layer-3 (routing) services. Additionally, a DHCP service provides IP address information to instances.

### Self-service networks: 
![self-service](https://docs.openstack.org/install-guide/_images/network2-services.png)

Augments the provider networks option with layer-3 (routing) services that enable self-service networks using overlay segmentation methods such as VXLAN. routes virtual networks to physical networks using NAT, provides the foundation for advanced services such as LBaaS and FWaaS.

## Components
### Compute
- Nova: Compute Service
- Zun: Containers Service

### Storage
- Swift: Object store
- Cinder: Block Storage
- Manila: Shared filesystems

### Networking
- Neutron: Networking
- Octavia: Load balancer
- Designate: DNS service

### Shared Services
- Keystone: Identity service
- Placement: Placement service
- Glance: Image service
- Barbican: Key management

### Web Frontend
- Horizon: Dashboard

### Orchestration
- Heat: Orchestration
- Senlin: Clustering service
- Mistral: Workflow service
- Zaqar: Messaging Service
- Blazar: Resource reservation service
- Aodh: Alarming Service

### Workload Provisioning
- Magnum: Container Orchestration Engine Provisioning
- Sahara: Big Data Processing Framework Provisioning
- Trove: Database as a Service

### Hardware Lifecycle
- Ironic: Bare Metal Provisioning Service
- Cyborg: Lifecycle management of accelerators

### Application Lifecycle
- Masakari: Instances High Availability Service
- Murano: Application Catalog
- Solum: Software Development Lifecycle Automation
- Freeze Backup: Restore, and Disaster Recovery

### API Proxies
- EC2API: EC2 API proxy

## Prerequisits
- Network Time Protocol (NTP)
- OpenStack packages
- SQL database
- Message queue
- Memcached
- Etcd

### services that require passwords
- Service passwords
| Password name | Description |
|---------------|--------------|
| RABBIT_PASS | Password of RabbitMQ user openstack |
| ADMIN_PASS | Password of user admin |
| DEMO_PASS | Password of user demo |
| KEYSTONE_DBPASS | Database password of Identity service |
| GLANCE_PASS | Password of Image service user glance |
| CINDER_PASS | Password of Block Storage service user cinder |
| NEUTRON_PASS | Password of Networking service user neutron |
| NOVA_PASS | 	Password of Compute service user nova |
| METADATA_SECRET | Secret for the metadata proxy |

- Service Database passwords
| Password name | Description |
|---------------|--------------
| Database password | Root password for the database |
| GLANCE_DBPASS | Database password for Image service |
| PLACEMENT_PASS | Password of the Placement service user placement |
| DASH_DBPASS | Database password for the Dashboard |
| NOVA_DBPASS | Database password for Compute service |
| NEUTRON_DBPASS | Database password for the Networking service |
| CINDER_DBPASS | Database password for the Block Storage service |

- User admin (for services) openstack environment variables: admin-openrc in admin project
```
export OS_PROJECT_DOMAIN_NAME=Default
export OS_USER_DOMAIN_NAME=Default
export OS_PROJECT_NAME=admin
export OS_USERNAME=admin
export OS_PASSWORD=ADMIN_PASS
export OS_AUTH_URL=http://controller:5000/v3
export OS_IDENTITY_API_VERSION=3
export OS_IMAGE_API_VERSION=2
```

- User demo openstack environment variables: demo-openrc in myproj project
```
export OS_PROJECT_DOMAIN_NAME=Default
export OS_USER_DOMAIN_NAME=Default
export OS_PROJECT_NAME=myproject
export OS_USERNAME=myuser
export OS_PASSWORD=DEMO_PASS
export OS_AUTH_URL=http://controller:5000/v3
export OS_IDENTITY_API_VERSION=3
export OS_IMAGE_API_VERSION=2
```
