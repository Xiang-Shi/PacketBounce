//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package PacketBounce.simulations;
import inet.examples.inet.routerperf.BurstHost;
import inet.linklayer.ethernet.EtherHub;
import inet.node.ethernet.Eth1G;
import inet.node.ethernet.EtherHost;
import inet.node.ethernet.EtherHost2;
import inet.node.ethernet.EtherSwitch;
import inet.node.wireless.AccessPoint;
import ned.DatarateChannel;

//
// TODO documentation
//
network PacketBounce
{
    @display("bgb=864,601");
    types:
    submodules:

        etherSwitch1: EtherSwitch {
            @display("p=235,231");
        }
        etherSwitch2: EtherSwitch {
            @display("p=366,215");
        }
        etherSwitch3: EtherSwitch {
            @display("p=520,215");
        }        
        etherSwitch4: EtherSwitch {
            @display("p=247,322");
        }
        etherSwitch5: EtherSwitch {
            @display("p=385,313");
        }   
		etherSwitch6: EtherSwitch {
            @display("p=520,313");
        }
        etherSwitch7: EtherSwitch {
            @display("p=366,432");
        }             
        sender1: EtherHost2 {
            @display("p=208,131");
        }
        sender2: EtherHost2 {
            @display("p=378,115");
        }
        sender3: EtherHost2 {
            @display("p=552,115");
        }
        receiver: EtherHost2 {
            @display("p=378,513");
        }

        
    connections:
        sender1.ethg <--> Eth1G <--> etherSwitch1.ethg++;
        sender2.ethg <--> Eth1G <--> etherSwitch2.ethg++;
        sender3.ethg <--> Eth1G <--> etherSwitch3.ethg++;

        etherSwitch1.ethg++ <--> Eth1G <--> etherSwitch4.ethg++;
        etherSwitch2.ethg++ <--> Eth1G <--> etherSwitch5.ethg++;
        etherSwitch3.ethg++ <--> Eth1G <--> etherSwitch6.ethg++;
        etherSwitch4.ethg++ <--> Eth1G <--> etherSwitch7.ethg++;
        etherSwitch5.ethg++ <--> Eth1G <--> etherSwitch7.ethg++;
        etherSwitch6.ethg++ <--> Eth1G <--> etherSwitch7.ethg++;
        etherSwitch7.ethg++ <--> Eth1G <--> receiver.ethg;
        
}

channel LFNPath extends DatarateChannel
{
    parameters:
        datarate = 1Gbps;
        delay = 1ms;
        per = 0;
        ber = 0;
}
