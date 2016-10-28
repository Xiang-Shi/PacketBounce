# PacketBounce

## 1. This is the source code of PacketBounce, which includes:
### (1) Inet.zip: 

The modified version of Inet (as reference project for PacketBounce)
 
### (2) "PacketBounce" repository: 

PacketBounce Project source code

## 2. How to set up simulation in OMNet++ ?
###  (1) Import "Inet" and "PacketBounce"

###  (2) Parameter setting

   i) Create your own mactable initialization file of each switch (specify the mac address of receiver), and put it under "PacketBounce/MactableData"
  
   ii) alter basic settings in "PacketBounce/simulations/omnetpp.ini"
  
   iii) change the parameter of probability function P at the beginning of "inet/src/inet/linklayer/ethernet/switch/MACRelayUnit.cc"

### 3. Then build two projects, and run "PacketBounce"
