//
// Copyright (C) 2015 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//
// Author: Andras Varga
//

#ifndef __INET_IEEE80211NEWMAC_H
#define __INET_IEEE80211NEWMAC_H

// uncomment this if you do not want to log state machine transitions
#define FSM_DEBUG

#include <list>

#include "inet/common/INETDefs.h"
#include "inet/physicallayer/contract/packetlevel/IRadio.h"
#include "inet/linklayer/ieee80211/mac/Ieee80211Consts.h"
#include "inet/linklayer/base/MACProtocolBase.h"
#include "inet/physicallayer/ieee80211/mode/IIeee80211Mode.h" //TODO not needed here
#include "inet/physicallayer/ieee80211/mode/Ieee80211ModeSet.h" //TODO not needed here
#include "IMacRadioInterface.h"

namespace inet {
namespace ieee80211 {

using namespace physicallayer;

class IUpperMacContext;
class IImmediateTx;
class IContentionTx;
class IRx;
class IUpperMac;
class Ieee80211Frame;


/**
 * IEEE 802.11b Media Access Control Layer.
 *
 * Various comments in the code refer to the Wireless LAN Medium Access
 * Control (MAC) and Physical Layer(PHY) Specifications
 * ANSI/IEEE Std 802.11, 1999 Edition (R2003)
 */
class INET_API Ieee80211NewMac : public MACProtocolBase, public IMacRadioInterface
{
  protected:
    MACAddress address; // only because createInterfaceEntry() needs it

    IUpperMac *upperMac = nullptr;
    IRx *rx = nullptr;
    IImmediateTx *immediateTx = nullptr;
    IContentionTx **contentionTx = nullptr;  // nullptr-terminated pointer array
    IRadio *radio = nullptr;

    IRadio::TransmissionState transmissionState = IRadio::TransmissionState::TRANSMISSION_STATE_UNDEFINED;

    // The last change channel message received and not yet sent to the physical layer, or NULL.
    cMessage *pendingRadioConfigMsg = nullptr;

    /** @name Statistics */
    //@{
    long numRetry;
    long numSentWithoutRetry;
    long numGivenUp;
    long numCollision;
    long numSent;
    long numReceived;
    long numSentBroadcast;
    long numReceivedBroadcast;
    static simsignal_t stateSignal;
    static simsignal_t radioStateSignal;
    //@}

  protected:
    virtual int numInitStages() const override {return NUM_INIT_STAGES;}
    virtual void initialize(int) override;

    void receiveSignal(cComponent *source, simsignal_t signalID, long value) override;
    void configureRadioMode(IRadio::RadioMode radioMode);
    virtual InterfaceEntry *createInterfaceEntry() override;
    virtual const MACAddress& isInterfaceRegistered();
    void transmissionStateChanged(IRadio::TransmissionState transmissionState);

    /** @brief Handle commands (msg kind+control info) coming from upper layers */
    virtual void handleUpperCommand(cMessage *msg) override;

    /** @brief Handle timer self messages */
    virtual void handleSelfMessage(cMessage *msg) override;

    /** @brief Handle messages from upper layer */
    virtual void handleUpperPacket(cPacket *msg) override;

    /** @brief Handle messages from lower (physical) layer */
    virtual void handleLowerPacket(cPacket *msg) override;

    virtual bool handleNodeStart(IDoneCallback *doneCallback) override;
    virtual bool handleNodeShutdown(IDoneCallback *doneCallback) override;
    virtual void handleNodeCrash() override;

  public:
    Ieee80211NewMac();
    virtual ~Ieee80211NewMac();

    virtual const MACAddress& getAddress() const {return address;}
    virtual void sendUp(cMessage *message) override;
    virtual void sendFrame(Ieee80211Frame *frameToSend) override;
    virtual void sendDownPendingRadioConfigMsg() override;
};

} // namespace ieee80211
} // namespace inet

#endif

