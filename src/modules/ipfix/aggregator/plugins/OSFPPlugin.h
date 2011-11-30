/*
 * Vermont Aggregator Subsystem
 * Copyright (C) 2009 Vermont Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */
#ifdef PLUGIN_SUPPORT_ENABLED
#ifndef OSFPPLUGIN_H_
#define OSFPPLUGIN_H_

#include "modules/ipfix/aggregator/BasePlugin.h"
#include "OSFingerprint.h"
#include "OSFingerprintDetection.h"
#include "OSSamples.h"
#include <boost/unordered_map.hpp>
#include <iostream>
#include <fstream>


typedef boost::unordered_map <uint32_t, uint32_t> hashmap_t;

class OSFPPlugin : public BasePlugin{
public:
    OSFPPlugin();
    OSFPPlugin(const uint32_t maxPckts, std::string file, bool synackmode = false, bool osdetection = false);
    ~OSFPPlugin();
    void flowDeleted(const HashtableBucket* bucket);
    void newFlowReceived(const HashtableBucket* bucket);
    void newPacketReceived(const Packet* p, uint32_t hash);

    void initializeAggregator(uint32_t interval, std::string mode, std::string outputfile);

private:
    uint32_t maxPackets;
    std::string dumpFile;
    bool syn_ack_mode;
    hashmap_t packetcountmap;
    OSSamples* osSamples;
    ofstream filestream;
    OSFingerprintDetection detector;
    bool os_detection;
    void processPacket(const Packet* p, uint32_t hash);
    string parseTCPOptions(struct TCPOptions &options, const Packet* p, const uint32_t dataOffset);
    void writeToFile(OSFingerprint::Ptr fingerprint);
    void expireFlow(uint32_t hash);
};

#endif
#endif