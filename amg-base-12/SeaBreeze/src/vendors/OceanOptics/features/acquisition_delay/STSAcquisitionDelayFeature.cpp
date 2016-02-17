/***************************************************//**
 * @file    STSAcquisitionDelayFeature.cpp
 * @date    November 2015
 * @author  Ocean Optics, Inc.
 *
 * This feature provides an interface to the acquisition
 * (trigger) delay feature of the STS.
 *
 * LICENSE:
 *
 * SeaBreeze Copyright (C) 2015, Ocean Optics Inc
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *******************************************************/

#include "common/globals.h"
#include "vendors/OceanOptics/features/acquisition_delay/STSAcquisitionDelayFeature.h"

using namespace seabreeze;
using namespace std;

#define STS_ACQUISITION_DELAY_INCREMENT_USEC    1
#define STS_ACQUISITION_DELAY_MINIMUM_USEC      0
#define STS_ACQUISITION_DELAY_MAXIMUM_USEC      335500

STSAcquisitionDelayFeature::STSAcquisitionDelayFeature(
        std::vector<ProtocolHelper *> helpers) : AcquisitionDelayFeature(helpers) {

}

STSAcquisitionDelayFeature::~STSAcquisitionDelayFeature() {

}

unsigned long STSAcquisitionDelayFeature::getAcquisitionDelayIncrementMicroseconds(
                    const Protocol &protocol, const Bus &bus)
                    throw (FeatureException) {
    return STS_ACQUISITION_DELAY_INCREMENT_USEC;
}

unsigned long STSAcquisitionDelayFeature::getAcquisitionDelayMaximumMicroseconds(
            const Protocol &protocol, const Bus &bus)
            throw (FeatureException) {
    return STS_ACQUISITION_DELAY_MAXIMUM_USEC;
}

unsigned long STSAcquisitionDelayFeature::getAcquisitionDelayMinimumMicroseconds(
            const Protocol &protocol, const Bus &bus)
            throw (FeatureException) {
    return STS_ACQUISITION_DELAY_MINIMUM_USEC;
}
