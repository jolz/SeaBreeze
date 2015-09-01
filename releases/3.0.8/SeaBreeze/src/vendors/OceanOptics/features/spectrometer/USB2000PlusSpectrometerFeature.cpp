/***************************************************//**
 * @file    USB2000PlusSpectrometerFeature.cpp
 * @date    May 2009
 * @author  Ocean Optics, Inc.
 *
 * LICENSE:
 *
 * SeaBreeze Copyright (C) 2014, Ocean Optics Inc
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
#include "vendors/OceanOptics/features/spectrometer/USB2000PlusSpectrometerFeature.h"
#include "vendors/OceanOptics/protocols/ooi/exchanges/IntegrationTimeExchange.h"
#include "vendors/OceanOptics/protocols/ooi/exchanges/ReadSpectrumExchange.h"
#include "vendors/OceanOptics/protocols/ooi/exchanges/USBFPGASpectrumExchange.h"
#include "vendors/OceanOptics/protocols/ooi/exchanges/RequestSpectrumExchange.h"
#include "vendors/OceanOptics/protocols/ooi/exchanges/TriggerModeExchange.h"
#include "vendors/OceanOptics/protocols/ooi/impls/OOISpectrometerProtocol.h"

using namespace seabreeze;
using namespace ooiProtocol;

const long USB2000PlusSpectrometerFeature::INTEGRATION_TIME_MINIMUM = 1000;
const long USB2000PlusSpectrometerFeature::INTEGRATION_TIME_MAXIMUM = 655350000;
const long USB2000PlusSpectrometerFeature::INTEGRATION_TIME_INCREMENT = 1000;
const long USB2000PlusSpectrometerFeature::INTEGRATION_TIME_BASE = 1;

USB2000PlusSpectrometerFeature::USB2000PlusSpectrometerFeature() {

    this->numberOfPixels = 2048;
    this->maxIntensity = 65535;

    this->integrationTimeMinimum = USB2000PlusSpectrometerFeature::INTEGRATION_TIME_MINIMUM;
    this->integrationTimeMaximum = USB2000PlusSpectrometerFeature::INTEGRATION_TIME_MAXIMUM;
    this->integrationTimeBase = USB2000PlusSpectrometerFeature::INTEGRATION_TIME_BASE;
    this->integrationTimeIncrement = USB2000PlusSpectrometerFeature::INTEGRATION_TIME_INCREMENT;

    // safest range for both USB2000+ and Flame-S is (6, 20)
    for(int i = 6; i < 21; i++) {
        this->electricDarkPixelIndices.push_back(i);
    }

    IntegrationTimeExchange *intTime = new IntegrationTimeExchange(
            USB2000PlusSpectrometerFeature::INTEGRATION_TIME_BASE);

    Transfer *unformattedSpectrum = new ReadSpectrumExchange(
            this->numberOfPixels * 2 + 1, this->numberOfPixels);

    Transfer *formattedSpectrum = new USBFPGASpectrumExchange(
            this->numberOfPixels * 2 + 1, this->numberOfPixels, this);

    Transfer *requestSpectrum = new RequestSpectrumExchange();

    TriggerModeExchange *triggerMode = new TriggerModeExchange();

    OOISpectrometerProtocol *ooiProtocol = new OOISpectrometerProtocol(
            intTime, requestSpectrum, unformattedSpectrum, formattedSpectrum,
            triggerMode);

    this->protocols.push_back(ooiProtocol);

    this->triggerModes.push_back(
        new SpectrometerTriggerMode(SPECTROMETER_TRIGGER_MODE_NORMAL));
    this->triggerModes.push_back(
        new SpectrometerTriggerMode(SPECTROMETER_TRIGGER_MODE_SOFTWARE));
    this->triggerModes.push_back(
        new SpectrometerTriggerMode(SPECTROMETER_TRIGGER_MODE_SYNCHRONIZATION));
    this->triggerModes.push_back(
        new SpectrometerTriggerMode(SPECTROMETER_TRIGGER_MODE_HARDWARE));

}

USB2000PlusSpectrometerFeature::~USB2000PlusSpectrometerFeature() {

}