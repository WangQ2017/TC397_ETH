#!/bin/bash

sudo ip link delete ens33.1
sudo ip link delete ens33.10
sudo ip link delete ens33.23

sudo ip link add link ens33 name ens33.1 type vlan id 1
sudo ip addr add 169.254.1.10/24 brd 169.254.1.255 dev ens33.1
sudo ip link set ens33.1 up
sudo ip route add default via 169.254.1.1 dev ens33.1
sudo ip route add 169.254.1.0/24 dev ens33.1

sudo ip link add link ens33 name ens33.10 type vlan id 10
sudo ip addr add 10.10.0.10/24 brd 10.10.0.255 dev ens33.10
sudo ip link set ens33.10 up


sudo ip link add link ens33 name ens33.23 type vlan id 23
sudo ip addr add 10.23.0.10/24 brd 10.23.0.255 dev ens33.23
sudo ip link set ens33.23 up

sudo ip addr add 192.168.1.10/24 brd 192.168.1.255 dev ens33
