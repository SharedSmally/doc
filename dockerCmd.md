
## Add user
```
RUN useradd -d /home/ubuntu -ms /bin/bash -g root -G sudo -p ubuntu ubuntu
USER ubuntu
WORKDIR /home/ubuntu

useradd options (see: man useradd):
-d, --home-dir HOME_DIR Home directory of the new account.
-m, --create-home Create the user's home directory.
-s, --shell SHELL Login shell of the new account.
-g, --gid GROUP Name or ID of the primary group.
-G, --groups GROUPS List of supplementary groups.
-p, --password PASSWORD Encrypted password of the new account (e.g. ubuntu).
```
