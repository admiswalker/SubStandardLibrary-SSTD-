#!/bin/sh
docker run \
       -u `id -u`:`id -g` \
       -v /etc/group:/etc/group:ro \
       -v /etc/passwd:/etc/passwd:ro \
       -v /etc/shadow:/etc/shadow:ro \
       -v /etc/sudoers.d:/etc/sudoers.d:ro \
       --rm --name sstd_raspberry_pi_64 \
       -v $PWD:/home -w /home \
       --user root \
       sstd_raspberry_pi_64 ${@}

# removes the `-it` to avoid the following error:
# > the input device is not a TTY

# `--user root` is to avoid the following error:
# > $ apt install time
# > E: Could not open lock file /var/lib/dpkg/lock-frontend - open (13: Permission denied)
# > E: Unable to acquire the dpkg frontend lock (/var/lib/dpkg/lock-frontend), are you root?
