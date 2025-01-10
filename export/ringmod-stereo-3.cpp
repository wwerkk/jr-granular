/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_2062 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_2058 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2062;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_2058()
            {
            }
            
            ~RNBOSubpatcher_2058()
            {
            }
            
            virtual RNBOSubpatcher_2062* getPatcher() const {
                return static_cast<RNBOSubpatcher_2062 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                this->gen_01_perform(in1, this->gen_01_rampsamples, out1, this->dummyBuffer, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->gen_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_01_getPresetValue(getSubState(preset, "rampsamples"));
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_01_value_set(v);
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    {
                    return this->param_01_value;
                    }
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 1;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "rampsamples";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "p_obj-3/env.follower[1]/rampsamples";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = 1;
                        info->max = 48000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    {
                        value = (value < 1 ? 1 : (value > 48000 ? 48000 : value));
                        ParameterValue normalizedValue = (value - 1) / (48000 - 1);
                        return normalizedValue;
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 0:
                    {
                    {
                        {
                            return 1 + value * (48000 - 1);
                        }
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    return this->param_01_value_constrain(value);
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void param_01_value_set(number v) {
                v = this->param_01_value_constrain(v);
                this->param_01_value = v;
                this->sendParameter(0, false);
            
                if (this->param_01_value != this->param_01_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_01_lastValue = this->param_01_value;
                }
            
                this->intnum_01_input_number_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {
                this->gen_01_history_1_init();
                this->gen_01_history_2_init();
                this->gen_01_history_3_init();
                this->gen_01_counter_9_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
            
                {
                    this->scheduleParamInit(0, 0);
                }
            }
            
            void allocateDataRefs() {}
            
            number param_01_value_constrain(number v) const {
                v = (v > 48000 ? 48000 : (v < 1 ? 1 : v));
                return v;
            }
            
            number gen_01_rampsamples_constrain(number v) const {
                if (v < 1)
                    v = 1;
            
                return v;
            }
            
            void gen_01_rampsamples_set(number v) {
                v = this->gen_01_rampsamples_constrain(v);
                this->gen_01_rampsamples = v;
            }
            
            void intnum_01_out_set(number v) {
                this->gen_01_rampsamples_set(v);
            }
            
            void intnum_01_input_number_set(number v) {
                this->intnum_01_input_number = v;
                this->intnum_01_stored = v;
                this->intnum_01_out_set(trunc(v));
            }
            
            void gen_01_perform(
                const Sample * in1,
                number rampsamples,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                auto __gen_01_history_3_value = this->gen_01_history_3_value;
                auto __gen_01_history_2_value = this->gen_01_history_2_value;
                auto __gen_01_history_1_value = this->gen_01_history_1_value;
                Index i;
            
                for (i = 0; i < n; i++) {
                    out2[(Index)i] = rampsamples;
                    number abs_4_0 = rnbo_abs(in1[(Index)i]);
                    number gt_5_1 = abs_4_0 > __gen_01_history_1_value;
                    number gte_6_2 = __gen_01_history_2_value >= rampsamples;
                    number or_7_3 = (bool)(gt_5_1) || (bool)(gte_6_2);
                    number latch_8_5 = this->gen_01_latch_4_next(abs_4_0, or_7_3);
                    number latch_9_7 = this->gen_01_latch_6_next(__gen_01_history_3_value, or_7_3);
                    number sub_10_8 = latch_8_5 - latch_9_7;
                    number counter_11 = 0;
                    number counter_12 = 0;
                    number counter_13 = 0;
                    array<number, 3> result_10 = this->gen_01_counter_9_next(1, or_7_3 + gte_6_2, 0);
                    counter_13 = result_10[2];
                    counter_12 = result_10[1];
                    counter_11 = result_10[0];
                    number add_14_11 = counter_11 + 1;
                    number div_15_12 = (rampsamples == 0. ? 0. : add_14_11 / rampsamples);
                    number mul_16_13 = sub_10_8 * div_15_12;
                    number add_17_14 = latch_9_7 + mul_16_13;
                    out1[(Index)i] = add_17_14;
                    number history_1_next_18_15 = fixdenorm(latch_8_5);
                    number history_2_next_19_16 = fixdenorm(add_14_11);
                    number history_3_next_20_17 = fixdenorm(add_17_14);
                    __gen_01_history_1_value = history_1_next_18_15;
                    __gen_01_history_3_value = history_3_next_20_17;
                    __gen_01_history_2_value = history_2_next_19_16;
                }
            
                this->gen_01_history_1_value = __gen_01_history_1_value;
                this->gen_01_history_2_value = __gen_01_history_2_value;
                this->gen_01_history_3_value = __gen_01_history_3_value;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number gen_01_history_1_getvalue() {
                return this->gen_01_history_1_value;
            }
            
            void gen_01_history_1_setvalue(number val) {
                this->gen_01_history_1_value = val;
            }
            
            void gen_01_history_1_reset() {
                this->gen_01_history_1_value = 0;
            }
            
            void gen_01_history_1_init() {
                this->gen_01_history_1_value = 0;
            }
            
            number gen_01_history_2_getvalue() {
                return this->gen_01_history_2_value;
            }
            
            void gen_01_history_2_setvalue(number val) {
                this->gen_01_history_2_value = val;
            }
            
            void gen_01_history_2_reset() {
                this->gen_01_history_2_value = 0;
            }
            
            void gen_01_history_2_init() {
                this->gen_01_history_2_value = 0;
            }
            
            number gen_01_history_3_getvalue() {
                return this->gen_01_history_3_value;
            }
            
            void gen_01_history_3_setvalue(number val) {
                this->gen_01_history_3_value = val;
            }
            
            void gen_01_history_3_reset() {
                this->gen_01_history_3_value = 0;
            }
            
            void gen_01_history_3_init() {
                this->gen_01_history_3_value = 0;
            }
            
            number gen_01_latch_4_next(number x, number control) {
                if (control != 0.)
                    this->gen_01_latch_4_value = x;
            
                return this->gen_01_latch_4_value;
            }
            
            void gen_01_latch_4_dspsetup() {
                this->gen_01_latch_4_reset();
            }
            
            void gen_01_latch_4_reset() {
                this->gen_01_latch_4_value = 0;
            }
            
            number gen_01_latch_6_next(number x, number control) {
                if (control != 0.)
                    this->gen_01_latch_6_value = x;
            
                return this->gen_01_latch_6_value;
            }
            
            void gen_01_latch_6_dspsetup() {
                this->gen_01_latch_6_reset();
            }
            
            void gen_01_latch_6_reset() {
                this->gen_01_latch_6_value = 0;
            }
            
            array<number, 3> gen_01_counter_9_next(number a, number reset, number limit) {
                RNBO_UNUSED(limit);
                RNBO_UNUSED(a);
                number carry_flag = 0;
            
                if (reset != 0) {
                    this->gen_01_counter_9_count = 0;
                    this->gen_01_counter_9_carry = 0;
                } else {
                    this->gen_01_counter_9_count += 1;
                }
            
                return {this->gen_01_counter_9_count, carry_flag, this->gen_01_counter_9_carry};
            }
            
            void gen_01_counter_9_init() {
                this->gen_01_counter_9_count = -1;
            }
            
            void gen_01_counter_9_reset() {
                this->gen_01_counter_9_carry = 0;
                this->gen_01_counter_9_count = 0;
            }
            
            void gen_01_dspsetup(bool force) {
                if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->gen_01_setupDone = true;
                this->gen_01_latch_4_dspsetup();
                this->gen_01_latch_6_dspsetup();
            }
            
            void param_01_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_01_value;
            }
            
            void param_01_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_01_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                gen_01_in1 = 0;
                gen_01_rampsamples = 1;
                intnum_01_input_number = 0;
                intnum_01_value = 0;
                param_01_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                gen_01_history_1_value = 0;
                gen_01_history_2_value = 0;
                gen_01_history_3_value = 0;
                gen_01_latch_4_value = 0;
                gen_01_latch_6_value = 0;
                gen_01_counter_9_carry = 0;
                gen_01_counter_9_count = 0;
                gen_01_setupDone = false;
                intnum_01_stored = 0;
                param_01_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number gen_01_in1;
                number gen_01_rampsamples;
                number intnum_01_input_number;
                number intnum_01_value;
                number param_01_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number gen_01_history_1_value;
                number gen_01_history_2_value;
                number gen_01_history_3_value;
                number gen_01_latch_4_value;
                number gen_01_latch_6_value;
                int gen_01_counter_9_carry;
                number gen_01_counter_9_count;
                bool gen_01_setupDone;
                number intnum_01_stored;
                number param_01_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_2059 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2062;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_2059()
            {
            }
            
            ~RNBOSubpatcher_2059()
            {
            }
            
            virtual RNBOSubpatcher_2062* getPatcher() const {
                return static_cast<RNBOSubpatcher_2062 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                this->gen_02_perform(in1, this->gen_02_rampsamples, out1, this->dummyBuffer, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->gen_02_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_02_getPresetValue(getSubState(preset, "rampsamples"));
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_02_value_set(v);
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    {
                    return this->param_02_value;
                    }
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 1;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "rampsamples";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "p_obj-3/env.follower/rampsamples";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = 1;
                        info->max = 48000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    {
                        value = (value < 1 ? 1 : (value > 48000 ? 48000 : value));
                        ParameterValue normalizedValue = (value - 1) / (48000 - 1);
                        return normalizedValue;
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 0:
                    {
                    {
                        {
                            return 1 + value * (48000 - 1);
                        }
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    return this->param_02_value_constrain(value);
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void param_02_value_set(number v) {
                v = this->param_02_value_constrain(v);
                this->param_02_value = v;
                this->sendParameter(0, false);
            
                if (this->param_02_value != this->param_02_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_02_lastValue = this->param_02_value;
                }
            
                this->intnum_02_input_number_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {
                this->gen_02_history_1_init();
                this->gen_02_history_2_init();
                this->gen_02_history_3_init();
                this->gen_02_counter_9_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
            
                {
                    this->scheduleParamInit(0, 0);
                }
            }
            
            void allocateDataRefs() {}
            
            number param_02_value_constrain(number v) const {
                v = (v > 48000 ? 48000 : (v < 1 ? 1 : v));
                return v;
            }
            
            number gen_02_rampsamples_constrain(number v) const {
                if (v < 1)
                    v = 1;
            
                return v;
            }
            
            void gen_02_rampsamples_set(number v) {
                v = this->gen_02_rampsamples_constrain(v);
                this->gen_02_rampsamples = v;
            }
            
            void intnum_02_out_set(number v) {
                this->gen_02_rampsamples_set(v);
            }
            
            void intnum_02_input_number_set(number v) {
                this->intnum_02_input_number = v;
                this->intnum_02_stored = v;
                this->intnum_02_out_set(trunc(v));
            }
            
            void gen_02_perform(
                const Sample * in1,
                number rampsamples,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                auto __gen_02_history_3_value = this->gen_02_history_3_value;
                auto __gen_02_history_2_value = this->gen_02_history_2_value;
                auto __gen_02_history_1_value = this->gen_02_history_1_value;
                Index i;
            
                for (i = 0; i < n; i++) {
                    out2[(Index)i] = rampsamples;
                    number abs_4_0 = rnbo_abs(in1[(Index)i]);
                    number gt_5_1 = abs_4_0 > __gen_02_history_1_value;
                    number gte_6_2 = __gen_02_history_2_value >= rampsamples;
                    number or_7_3 = (bool)(gt_5_1) || (bool)(gte_6_2);
                    number latch_8_5 = this->gen_02_latch_4_next(abs_4_0, or_7_3);
                    number latch_9_7 = this->gen_02_latch_6_next(__gen_02_history_3_value, or_7_3);
                    number sub_10_8 = latch_8_5 - latch_9_7;
                    number counter_11 = 0;
                    number counter_12 = 0;
                    number counter_13 = 0;
                    array<number, 3> result_10 = this->gen_02_counter_9_next(1, or_7_3 + gte_6_2, 0);
                    counter_13 = result_10[2];
                    counter_12 = result_10[1];
                    counter_11 = result_10[0];
                    number add_14_11 = counter_11 + 1;
                    number div_15_12 = (rampsamples == 0. ? 0. : add_14_11 / rampsamples);
                    number mul_16_13 = sub_10_8 * div_15_12;
                    number add_17_14 = latch_9_7 + mul_16_13;
                    out1[(Index)i] = add_17_14;
                    number history_1_next_18_15 = fixdenorm(latch_8_5);
                    number history_2_next_19_16 = fixdenorm(add_14_11);
                    number history_3_next_20_17 = fixdenorm(add_17_14);
                    __gen_02_history_1_value = history_1_next_18_15;
                    __gen_02_history_3_value = history_3_next_20_17;
                    __gen_02_history_2_value = history_2_next_19_16;
                }
            
                this->gen_02_history_1_value = __gen_02_history_1_value;
                this->gen_02_history_2_value = __gen_02_history_2_value;
                this->gen_02_history_3_value = __gen_02_history_3_value;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number gen_02_history_1_getvalue() {
                return this->gen_02_history_1_value;
            }
            
            void gen_02_history_1_setvalue(number val) {
                this->gen_02_history_1_value = val;
            }
            
            void gen_02_history_1_reset() {
                this->gen_02_history_1_value = 0;
            }
            
            void gen_02_history_1_init() {
                this->gen_02_history_1_value = 0;
            }
            
            number gen_02_history_2_getvalue() {
                return this->gen_02_history_2_value;
            }
            
            void gen_02_history_2_setvalue(number val) {
                this->gen_02_history_2_value = val;
            }
            
            void gen_02_history_2_reset() {
                this->gen_02_history_2_value = 0;
            }
            
            void gen_02_history_2_init() {
                this->gen_02_history_2_value = 0;
            }
            
            number gen_02_history_3_getvalue() {
                return this->gen_02_history_3_value;
            }
            
            void gen_02_history_3_setvalue(number val) {
                this->gen_02_history_3_value = val;
            }
            
            void gen_02_history_3_reset() {
                this->gen_02_history_3_value = 0;
            }
            
            void gen_02_history_3_init() {
                this->gen_02_history_3_value = 0;
            }
            
            number gen_02_latch_4_next(number x, number control) {
                if (control != 0.)
                    this->gen_02_latch_4_value = x;
            
                return this->gen_02_latch_4_value;
            }
            
            void gen_02_latch_4_dspsetup() {
                this->gen_02_latch_4_reset();
            }
            
            void gen_02_latch_4_reset() {
                this->gen_02_latch_4_value = 0;
            }
            
            number gen_02_latch_6_next(number x, number control) {
                if (control != 0.)
                    this->gen_02_latch_6_value = x;
            
                return this->gen_02_latch_6_value;
            }
            
            void gen_02_latch_6_dspsetup() {
                this->gen_02_latch_6_reset();
            }
            
            void gen_02_latch_6_reset() {
                this->gen_02_latch_6_value = 0;
            }
            
            array<number, 3> gen_02_counter_9_next(number a, number reset, number limit) {
                RNBO_UNUSED(limit);
                RNBO_UNUSED(a);
                number carry_flag = 0;
            
                if (reset != 0) {
                    this->gen_02_counter_9_count = 0;
                    this->gen_02_counter_9_carry = 0;
                } else {
                    this->gen_02_counter_9_count += 1;
                }
            
                return {this->gen_02_counter_9_count, carry_flag, this->gen_02_counter_9_carry};
            }
            
            void gen_02_counter_9_init() {
                this->gen_02_counter_9_count = -1;
            }
            
            void gen_02_counter_9_reset() {
                this->gen_02_counter_9_carry = 0;
                this->gen_02_counter_9_count = 0;
            }
            
            void gen_02_dspsetup(bool force) {
                if ((bool)(this->gen_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->gen_02_setupDone = true;
                this->gen_02_latch_4_dspsetup();
                this->gen_02_latch_6_dspsetup();
            }
            
            void param_02_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_02_value;
            }
            
            void param_02_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_02_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                gen_02_in1 = 0;
                gen_02_rampsamples = 1;
                intnum_02_input_number = 0;
                intnum_02_value = 0;
                param_02_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                gen_02_history_1_value = 0;
                gen_02_history_2_value = 0;
                gen_02_history_3_value = 0;
                gen_02_latch_4_value = 0;
                gen_02_latch_6_value = 0;
                gen_02_counter_9_carry = 0;
                gen_02_counter_9_count = 0;
                gen_02_setupDone = false;
                intnum_02_stored = 0;
                param_02_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number gen_02_in1;
                number gen_02_rampsamples;
                number intnum_02_input_number;
                number intnum_02_value;
                number param_02_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number gen_02_history_1_value;
                number gen_02_history_2_value;
                number gen_02_history_3_value;
                number gen_02_latch_4_value;
                number gen_02_latch_6_value;
                int gen_02_counter_9_carry;
                number gen_02_counter_9_count;
                bool gen_02_setupDone;
                number intnum_02_stored;
                number param_02_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_2062()
    {
    }
    
    ~RNBOSubpatcher_2062()
    {
        delete this->p_01;
        delete this->p_02;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, 555692221, false);
        getEngine()->flushClockEvents(this, -161950333, false);
        getEngine()->flushClockEvents(this, 1793217402, false);
        getEngine()->flushClockEvents(this, 388042711, false);
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    number samplerate() const {
        return this->sr;
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * source_in = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        SampleValue * source_ratio = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
        const SampleValue * target_in = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * target_ratio = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        this->signalsend_01_perform(in1, this->signals[0], n);
        this->signalforwarder_01_perform(this->signals[0], source_in, n);
        this->ip_01_perform(this->signals[1], n);
        this->ip_02_perform(this->signals[2], n);
    
        this->selector_01_perform(
            this->selector_01_onoff,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            n
        );
    
        this->ip_03_perform(this->signals[2], n);
        this->dspexpr_04_perform(this->signals[2], this->dspexpr_04_in2, this->signals[1], n);
    
        this->selector_03_perform(
            this->selector_03_onoff,
            this->signals[2],
            this->signals[1],
            this->signals[4],
            n
        );
    
        this->signalsend_02_perform(this->signals[4], this->signals[1], n);
        this->signalforwarder_02_perform(this->signals[1], source_ratio, n);
        this->stackprotect_perform(n);
        this->signaladder_03_perform(target_in, this->signals[0], this->signals[2], n);
        this->signalreceive_01_perform(this->signals[2], this->signals[4], n);
        this->p_01_perform(this->signals[4], this->signals[5], n);
        this->signaladder_04_perform(target_in, this->signals[0], this->signals[0], n);
        this->signalreceive_03_perform(this->signals[0], this->signals[6], n);
        this->fzero_01_perform(this->signals[6], n);
        this->signaladder_05_perform(target_ratio, this->signals[1], this->signals[1], n);
        this->signalreceive_02_perform(this->signals[1], this->signals[6], n);
        this->dspexpr_02_perform(this->signals[3], this->signals[6], this->signals[7], n);
        this->p_02_perform(this->signals[7], this->signals[6], n);
    
        this->cycle_tilde_01_perform(
            this->signals[6],
            this->cycle_tilde_01_phase_offset,
            this->signals[7],
            this->dummyBuffer,
            n
        );
    
        this->dspexpr_03_perform(this->signals[7], this->signals[6], n);
    
        this->selector_02_perform(
            this->selector_02_onoff,
            this->signals[7],
            this->signals[6],
            this->signals[3],
            n
        );
    
        this->gen_03_perform(
            this->signals[4],
            this->signals[3],
            this->gen_03_diodeCurve,
            this->gen_03_diodeThresh,
            this->signals[6],
            n
        );
    
        this->dspexpr_01_perform(this->signals[5], this->signals[6], out1, n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 8; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->ip_01_sigbuf = resizeSignal(this->ip_01_sigbuf, this->maxvs, maxBlockSize);
            this->ip_02_sigbuf = resizeSignal(this->ip_02_sigbuf, this->maxvs, maxBlockSize);
            this->ip_03_sigbuf = resizeSignal(this->ip_03_sigbuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->ip_01_dspsetup(forceDSPSetup);
        this->ip_02_dspsetup(forceDSPSetup);
        this->ip_03_dspsetup(forceDSPSetup);
        this->fzero_01_dspsetup(forceDSPSetup);
        this->cycle_tilde_01_dspsetup(forceDSPSetup);
        this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_01 = new RNBOSubpatcher_2058();
        this->p_01->setEngineAndPatcher(this->getEngine(), this);
        this->p_01->initialize();
        this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
        this->p_02 = new RNBOSubpatcher_2059();
        this->p_02->setEngineAndPatcher(this->getEngine(), this);
        this->p_02->initialize();
        this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_03_getPresetValue(getSubState(preset, "ampEnv"));
        this->param_04_getPresetValue(getSubState(preset, "pitchFollow"));
        this->param_05_getPresetValue(getSubState(preset, "pitchGlide"));
        this->param_06_getPresetValue(getSubState(preset, "freq"));
        this->param_07_getPresetValue(getSubState(preset, "ampMod"));
        this->param_08_getPresetValue(getSubState(preset, "subharmonic"));
        this->param_09_getPresetValue(getSubState(preset, "pitchHold"));
        this->param_10_getPresetValue(getSubState(preset, "ratio"));
        this->param_11_getPresetValue(getSubState(preset, "pitchThresh"));
        this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "env.follower[1]"));
        this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "env.follower"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_03_value_set(v);
            break;
            }
        case 1:
            {
            this->param_04_value_set(v);
            break;
            }
        case 2:
            {
            this->param_05_value_set(v);
            break;
            }
        case 3:
            {
            this->param_06_value_set(v);
            break;
            }
        case 4:
            {
            this->param_07_value_set(v);
            break;
            }
        case 5:
            {
            this->param_08_value_set(v);
            break;
            }
        case 6:
            {
            this->param_09_value_set(v);
            break;
            }
        case 7:
            {
            this->param_10_value_set(v);
            break;
            }
        case 8:
            {
            this->param_11_value_set(v);
            break;
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_01->getNumParameters())
                this->p_01->setParameterValue(index, v, time);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                this->p_02->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_03_value;
            }
        case 1:
            {
            return this->param_04_value;
            }
        case 2:
            {
            return this->param_05_value;
            }
        case 3:
            {
            return this->param_06_value;
            }
        case 4:
            {
            return this->param_07_value;
            }
        case 5:
            {
            return this->param_08_value;
            }
        case 6:
            {
            return this->param_09_value;
            }
        case 7:
            {
            return this->param_10_value;
            }
        case 8:
            {
            return this->param_11_value;
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterValue(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 2;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 2;
    }
    
    ParameterIndex getNumParameters() const {
        return 9 + this->p_01->getNumParameters() + this->p_02->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "ampEnv";
            }
        case 1:
            {
            return "pitchFollow";
            }
        case 2:
            {
            return "pitchGlide";
            }
        case 3:
            {
            return "freq";
            }
        case 4:
            {
            return "ampMod";
            }
        case 5:
            {
            return "subharmonic";
            }
        case 6:
            {
            return "pitchHold";
            }
        case 7:
            {
            return "ratio";
            }
        case 8:
            {
            return "pitchThresh";
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterName(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "p_obj-3/ampEnv";
            }
        case 1:
            {
            return "p_obj-3/pitchFollow";
            }
        case 2:
            {
            return "p_obj-3/pitchGlide";
            }
        case 3:
            {
            return "p_obj-3/freq";
            }
        case 4:
            {
            return "p_obj-3/ampMod";
            }
        case 5:
            {
            return "p_obj-3/subharmonic";
            }
        case 6:
            {
            return "p_obj-3/pitchHold";
            }
        case 7:
            {
            return "p_obj-3/ratio";
            }
        case 8:
            {
            return "p_obj-3/pitchThresh";
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterId(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.1;
                info->min = 0;
                info->max = 1000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal1[] = {"0", "1"};
                info->enumValues = eVal1;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 2:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 0;
                info->max = 1000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 3:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = -100;
                info->max = 100;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 4:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal4[] = {"0", "1"};
                info->enumValues = eVal4;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 5:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal5[] = {"0", "1"};
                info->enumValues = eVal5;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 6:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal6[] = {"0", "1"};
                info->enumValues = eVal6;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 7:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 1;
                info->max = 32;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 8:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.1;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            default:
                {
                index -= 9;
    
                if (index < this->p_01->getNumParameters())
                    this->p_01->getParameterInfo(index, info);
    
                index -= this->p_01->getNumParameters();
    
                if (index < this->p_02->getNumParameters())
                    this->p_02->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_01)
            return 9;
    
        if (subpatcher == this->p_02)
            return 9 + this->p_01->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 8:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 1:
        case 4:
        case 5:
        case 6:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
    
                {
                    normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 2);
                }
    
                return normalizedValue;
            }
            }
        case 0:
        case 2:
            {
            {
                value = (value < 0 ? 0 : (value > 1000 ? 1000 : value));
                ParameterValue normalizedValue = (value - 0) / (1000 - 0);
                return normalizedValue;
            }
            }
        case 7:
            {
            {
                value = (value < 1 ? 1 : (value > 32 ? 32 : value));
                ParameterValue normalizedValue = (value - 1) / (32 - 1);
                return normalizedValue;
            }
            }
        case 3:
            {
            {
                value = (value < -100 ? -100 : (value > 100 ? 100 : value));
                ParameterValue normalizedValue = (value - -100) / (100 - -100);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 8:
            {
            {
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 1:
        case 4:
        case 5:
        case 6:
            {
            {
                {
                    value = this->applyStepsToNormalizedParameterValue(value, 2);
                }
    
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 0:
        case 2:
            {
            {
                {
                    return 0 + value * (1000 - 0);
                }
            }
            }
        case 7:
            {
            {
                {
                    return 1 + value * (32 - 1);
                }
            }
            }
        case 3:
            {
            {
                {
                    return -100 + value * (100 - -100);
                }
            }
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_03_value_constrain(value);
            }
        case 1:
            {
            return this->param_04_value_constrain(value);
            }
        case 2:
            {
            return this->param_05_value_constrain(value);
            }
        case 3:
            {
            return this->param_06_value_constrain(value);
            }
        case 4:
            {
            return this->param_07_value_constrain(value);
            }
        case 5:
            {
            return this->param_08_value_constrain(value);
            }
        case 6:
            {
            return this->param_09_value_constrain(value);
            }
        case 7:
            {
            return this->param_10_value_constrain(value);
            }
        case 8:
            {
            return this->param_11_value_constrain(value);
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->constrainParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case 555692221:
            {
            this->fzero_01_onset_bang_bang();
            break;
            }
        case -161950333:
            {
            this->fzero_01_onset_list_set(value);
            break;
            }
        case 1793217402:
            {
            this->fzero_01_amplitude_set(value);
            break;
            }
        case 388042711:
            {
            this->fzero_01_pitch_set(value);
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("p_obj-3/number_obj-30") == objectId)
                this->numberobj_01_valin_set(payload);
    
            if (TAG("p_obj-3/number_obj-62") == objectId)
                this->numberobj_02_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("p_obj-3/number_obj-30") == objectId)
                this->numberobj_01_format_set(payload);
    
            if (TAG("p_obj-3/number_obj-62") == objectId)
                this->numberobj_02_format_set(payload);
    
            break;
            }
        }
    
        this->p_01->processNumMessage(tag, objectId, time, payload);
        this->p_02->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processListMessage(tag, objectId, time, payload);
        this->p_02->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processBangMessage(tag, objectId, time);
        this->p_02->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("p_obj-3/number_obj-30"):
            {
            return "p_obj-3/number_obj-30";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("p_obj-3/number_obj-62"):
            {
            return "p_obj-3/number_obj-62";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        auto subpatchResult_0 = this->p_01->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_02->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 0) {
            this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
            this->cycle_tilde_01_bufferUpdated();
        }
    
        this->p_01->processDataViewUpdate(index, time);
        this->p_02->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
    }
    
    protected:
    
    void param_03_value_set(number v) {
        v = this->param_03_value_constrain(v);
        this->param_03_value = v;
        this->sendParameter(0, false);
    
        if (this->param_03_value != this->param_03_lastValue) {
            this->getEngine()->presetTouched();
            this->param_03_lastValue = this->param_03_value;
        }
    
        this->mstosamps_01_ms_set(v);
    }
    
    void param_04_value_set(number v) {
        v = this->param_04_value_constrain(v);
        this->param_04_value = v;
        this->sendParameter(1, false);
    
        if (this->param_04_value != this->param_04_lastValue) {
            this->getEngine()->presetTouched();
            this->param_04_lastValue = this->param_04_value;
        }
    
        this->expr_01_in1_set(v);
    }
    
    void param_05_value_set(number v) {
        v = this->param_05_value_constrain(v);
        this->param_05_value = v;
        this->sendParameter(2, false);
    
        if (this->param_05_value != this->param_05_lastValue) {
            this->getEngine()->presetTouched();
            this->param_05_lastValue = this->param_05_value;
        }
    
        this->mstosamps_02_ms_set(v);
    }
    
    void param_06_value_set(number v) {
        v = this->param_06_value_constrain(v);
        this->param_06_value = v;
        this->sendParameter(3, false);
    
        if (this->param_06_value != this->param_06_lastValue) {
            this->getEngine()->presetTouched();
            this->param_06_lastValue = this->param_06_value;
        }
    
        this->numberobj_01_value_set(v);
    }
    
    void param_07_value_set(number v) {
        v = this->param_07_value_constrain(v);
        this->param_07_value = v;
        this->sendParameter(4, false);
    
        if (this->param_07_value != this->param_07_lastValue) {
            this->getEngine()->presetTouched();
            this->param_07_lastValue = this->param_07_value;
        }
    
        this->expr_02_in1_set(v);
    }
    
    void param_08_value_set(number v) {
        v = this->param_08_value_constrain(v);
        this->param_08_value = v;
        this->sendParameter(5, false);
    
        if (this->param_08_value != this->param_08_lastValue) {
            this->getEngine()->presetTouched();
            this->param_08_lastValue = this->param_08_value;
        }
    
        this->expr_03_in1_set(v);
    }
    
    void param_09_value_set(number v) {
        v = this->param_09_value_constrain(v);
        this->param_09_value = v;
        this->sendParameter(6, false);
    
        if (this->param_09_value != this->param_09_lastValue) {
            this->getEngine()->presetTouched();
            this->param_09_lastValue = this->param_09_value;
        }
    
        this->expr_04_in1_set(v);
    }
    
    void param_10_value_set(number v) {
        v = this->param_10_value_constrain(v);
        this->param_10_value = v;
        this->sendParameter(7, false);
    
        if (this->param_10_value != this->param_10_lastValue) {
            this->getEngine()->presetTouched();
            this->param_10_lastValue = this->param_10_value;
        }
    
        this->ip_03_value_set(v);
    }
    
    void param_11_value_set(number v) {
        v = this->param_11_value_constrain(v);
        this->param_11_value = v;
        this->sendParameter(8, false);
    
        if (this->param_11_value != this->param_11_lastValue) {
            this->getEngine()->presetTouched();
            this->param_11_lastValue = this->param_11_value;
        }
    
        this->expr_05_in2_set(v);
    }
    
    void numberobj_01_valin_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void numberobj_01_format_set(number v) {
        this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_02_valin_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_format_set(number v) {
        this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void fzero_01_onset_bang_bang() {}
    
    void fzero_01_onset_list_set(const list& ) {}
    
    void fzero_01_amplitude_set(number v) {
        this->expr_05_in1_set(v);
    }
    
    void fzero_01_pitch_set(number v) {
        this->select_01_input_number_set(v);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 1;
    }
    
    Index getNumOutputChannels() const {
        return 1;
    }
    
    void initializeObjects() {
        this->ip_01_init();
        this->numberobj_01_init();
        this->ip_02_init();
        this->numberobj_02_init();
        this->ip_03_init();
        this->fzero_01_init();
        this->p_01->initializeObjects();
        this->p_02->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_01->startup();
        this->p_02->startup();
    
        {
            this->scheduleParamInit(0, 0);
        }
    
        {
            this->scheduleParamInit(1, 0);
        }
    
        {
            this->scheduleParamInit(2, 0);
        }
    
        {
            this->scheduleParamInit(3, 0);
        }
    
        {
            this->scheduleParamInit(4, 0);
        }
    
        {
            this->scheduleParamInit(5, 0);
        }
    
        {
            this->scheduleParamInit(6, 0);
        }
    
        {
            this->scheduleParamInit(7, 0);
        }
    
        {
            this->scheduleParamInit(8, 0);
        }
    }
    
    void allocateDataRefs() {
        this->p_01->allocateDataRefs();
        this->p_02->allocateDataRefs();
        this->cycle_tilde_01_buffer->requestSize(16384, 1);
        this->cycle_tilde_01_buffer->setSampleRate(this->sr);
        this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
    }
    
    number param_03_value_constrain(number v) const {
        v = (v > 1000 ? 1000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_01_rampsamples_set(number v) {
        {
            this->p_01->setParameterValue(0, v, this->_currentTime);
        }
    }
    
    void mstosamps_01_out1_set(number v) {
        this->p_01_rampsamples_set(v);
    }
    
    void mstosamps_01_ms_set(number ms) {
        this->mstosamps_01_ms = ms;
    
        {
            this->mstosamps_01_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    number param_04_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void selector_01_onoff_set(number v) {
        this->selector_01_onoff = v;
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->selector_01_onoff_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
        this->expr_01_out1_set(this->expr_01_in1 + this->expr_01_in2);//#map:p_obj-3/+_obj-26:1
    }
    
    number param_05_value_constrain(number v) const {
        v = (v > 1000 ? 1000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_02_rampsamples_set(number v) {
        {
            this->p_02->setParameterValue(0, v, this->_currentTime);
        }
    }
    
    void mstosamps_02_out1_set(number v) {
        this->p_02_rampsamples_set(v);
    }
    
    void mstosamps_02_ms_set(number ms) {
        this->mstosamps_02_ms = ms;
    
        {
            this->mstosamps_02_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    number param_06_value_constrain(number v) const {
        v = (v > 100 ? 100 : (v < -100 ? -100 : v));
        return v;
    }
    
    void ip_01_value_set(number v) {
        this->ip_01_value = v;
        this->ip_01_fillSigBuf();
        this->ip_01_lastValue = v;
    }
    
    void numberobj_01_output_set(number v) {
        this->ip_01_value_set(v);
    }
    
    void numberobj_01_value_set(number v) {
        this->numberobj_01_value_setter(v);
        v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("p_obj-3/number_obj-30"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_01_output_set(localvalue);
    }
    
    number param_07_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void selector_02_onoff_set(number v) {
        this->selector_02_onoff = v;
    }
    
    void expr_02_out1_set(number v) {
        this->expr_02_out1 = v;
        this->selector_02_onoff_set(this->expr_02_out1);
    }
    
    void expr_02_in1_set(number in1) {
        this->expr_02_in1 = in1;
        this->expr_02_out1_set(this->expr_02_in1 + this->expr_02_in2);//#map:p_obj-3/+_obj-22:1
    }
    
    number param_08_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void selector_03_onoff_set(number v) {
        this->selector_03_onoff = v;
    }
    
    void expr_03_out1_set(number v) {
        this->expr_03_out1 = v;
        this->selector_03_onoff_set(this->expr_03_out1);
    }
    
    void expr_03_in1_set(number in1) {
        this->expr_03_in1 = in1;
        this->expr_03_out1_set(this->expr_03_in1 + this->expr_03_in2);//#map:p_obj-3/+_obj-31:1
    }
    
    number param_09_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void gate_01_onoff_set(number v) {
        this->gate_01_onoff = v;
    }
    
    void expr_04_out1_set(number v) {
        this->expr_04_out1 = v;
        this->gate_01_onoff_set(this->expr_04_out1);
    }
    
    void expr_04_in1_set(number in1) {
        this->expr_04_in1 = in1;
        this->expr_04_out1_set(this->expr_04_in1 == 0);//#map:p_obj-3/!_obj-43:1
    }
    
    number param_10_value_constrain(number v) const {
        v = (v > 32 ? 32 : (v < 1 ? 1 : v));
        return v;
    }
    
    void ip_03_value_set(number v) {
        this->ip_03_value = v;
        this->ip_03_fillSigBuf();
        this->ip_03_lastValue = v;
    }
    
    number param_11_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void expr_05_in2_set(number v) {
        this->expr_05_in2 = v;
    }
    
    void ip_02_value_set(number v) {
        this->ip_02_value = v;
        this->ip_02_fillSigBuf();
        this->ip_02_lastValue = v;
    }
    
    void numberobj_02_output_set(number v) {
        this->ip_02_value_set(v);
    }
    
    void numberobj_02_value_set(number v) {
        this->numberobj_02_value_setter(v);
        v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("p_obj-3/number_obj-62"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void signalsend_01_perform(const SampleValue * input, SampleValue * send, Index n) {
        for (Index i = 0; i < n; i++) {
            send[(Index)i] = input[(Index)i];
        }
    }
    
    void signalforwarder_01_perform(const SampleValue * input, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = input[(Index)i];
        }
    }
    
    void ip_01_perform(SampleValue * out, Index n) {
        auto __ip_01_lastValue = this->ip_01_lastValue;
        auto __ip_01_lastIndex = this->ip_01_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_01_lastIndex ? __ip_01_lastValue : this->ip_01_sigbuf[(Index)i]);
        }
    
        __ip_01_lastIndex = 0;
        this->ip_01_lastIndex = __ip_01_lastIndex;
    }
    
    void ip_02_perform(SampleValue * out, Index n) {
        auto __ip_02_lastValue = this->ip_02_lastValue;
        auto __ip_02_lastIndex = this->ip_02_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_02_lastIndex ? __ip_02_lastValue : this->ip_02_sigbuf[(Index)i]);
        }
    
        __ip_02_lastIndex = 0;
        this->ip_02_lastIndex = __ip_02_lastIndex;
    }
    
    void selector_01_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void ip_03_perform(SampleValue * out, Index n) {
        auto __ip_03_lastValue = this->ip_03_lastValue;
        auto __ip_03_lastIndex = this->ip_03_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_03_lastIndex ? __ip_03_lastValue : this->ip_03_sigbuf[(Index)i]);
        }
    
        __ip_03_lastIndex = 0;
        this->ip_03_lastIndex = __ip_03_lastIndex;
    }
    
    void dspexpr_04_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = (in1[(Index)i] == 0. ? 0. : 1 / in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void selector_03_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void signalsend_02_perform(const SampleValue * input, SampleValue * send, Index n) {
        for (Index i = 0; i < n; i++) {
            send[(Index)i] = input[(Index)i];
        }
    }
    
    void signalforwarder_02_perform(const SampleValue * input, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = input[(Index)i];
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void signaladder_03_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signalreceive_01_perform(const SampleValue * receive, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = receive[(Index)i];
        }
    }
    
    void p_01_perform(const SampleValue * in1, SampleValue * out1, Index n) {
        ConstSampleArray<1> ins = {in1};
        SampleArray<1> outs = {out1};
        this->p_01->process(ins, 1, outs, 1, n);
    }
    
    void signaladder_04_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signalreceive_03_perform(const SampleValue * receive, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = receive[(Index)i];
        }
    }
    
    void receive_01_output_number_set(number v) {
        this->receive_01_output_number = v;
        this->numberobj_02_value_set(v);
    }
    
    void send_01_input_number_set(number v) {
        this->send_01_input_number = v;
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_05_source_detectedFreq_number_set(v);
        this->receive_01_output_number_set(v);
    }
    
    void floatnum_01_out_set(number v) {
        this->send_01_input_number_set(v);
    }
    
    void floatnum_01_input_bang_bang() {
        this->floatnum_01_out_set(this->floatnum_01_stored);
    }
    
    void gate_01_out1_bang_bang() {
        this->floatnum_01_input_bang_bang();
    }
    
    void gate_01_input_bang_bang() {
        if (this->gate_01_onoff == 1)
            this->gate_01_out1_bang_bang();
    }
    
    void select_02_match1_bang() {
        this->gate_01_input_bang_bang();
    }
    
    void select_02_nomatch_number_set(number ) {}
    
    void select_02_input_number_set(number v) {
        if (v == this->select_02_test1)
            this->select_02_match1_bang();
        else
            this->select_02_nomatch_number_set(v);
    }
    
    void expr_05_out1_set(number v) {
        this->expr_05_out1 = v;
        this->select_02_input_number_set(this->expr_05_out1);
    }
    
    void expr_05_in1_set(number in1) {
        this->expr_05_in1 = in1;
        this->expr_05_out1_set(this->expr_05_in1 >= this->expr_05_in2);//#map:p_obj-3/>=_obj-8:1
    }
    
    void select_01_match1_bang() {}
    
    void floatnum_01_value_set(number v) {
        this->floatnum_01_value = v;
        this->floatnum_01_stored = v;
    }
    
    void select_01_nomatch_number_set(number v) {
        this->floatnum_01_value_set(v);
    }
    
    void select_01_input_number_set(number v) {
        if (v == this->select_01_test1)
            this->select_01_match1_bang();
        else
            this->select_01_nomatch_number_set(v);
    }
    
    void fzero_01_perform(const SampleValue * input, Index n) {
        auto __fzero_01_periodCount = this->fzero_01_periodCount;
        auto __fzero_01_offset = this->fzero_01_offset;
    
        for (Index i = 0; i < n; i++) {
            this->fzero_01_wavelets[0][__fzero_01_offset] = input[(Index)i];
            __fzero_01_offset++;
            __fzero_01_offset = (BinOpInt)(__fzero_01_offset & (BinOpInt)(4096 - 1));
        }
    
        __fzero_01_periodCount = __fzero_01_periodCount + (long)(this->vectorsize());
    
        if (__fzero_01_periodCount >= 256) {
            __fzero_01_periodCount = 0;
            array<number, 4> result = this->fzero_01_doAnalysis(__fzero_01_offset);
    
            if (result[2] > -1) {
                {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        555692221,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;
                }
            }
    
            if (result[1] > -1) this->getEngine()->scheduleClockEventWithValue(
                this,
                1793217402,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                result[1]
            );;
    
            if (result[0] > -1) this->getEngine()->scheduleClockEventWithValue(
                this,
                388042711,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                result[0]
            );;
        }
    
        this->fzero_01_offset = __fzero_01_offset;
        this->fzero_01_periodCount = __fzero_01_periodCount;
    }
    
    void signaladder_05_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signalreceive_02_perform(const SampleValue * receive, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = receive[(Index)i];
        }
    }
    
    void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void p_02_perform(const SampleValue * in1, SampleValue * out1, Index n) {
        ConstSampleArray<1> ins = {in1};
        SampleArray<1> outs = {out1};
        this->p_02->process(ins, 1, outs, 1, n);
    }
    
    void cycle_tilde_01_perform(
        const Sample * frequency,
        number phase_offset,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        RNBO_UNUSED(phase_offset);
        auto __cycle_tilde_01_f2i = this->cycle_tilde_01_f2i;
        auto __cycle_tilde_01_buffer = this->cycle_tilde_01_buffer;
        auto __cycle_tilde_01_phasei = this->cycle_tilde_01_phasei;
        Index i;
    
        for (i = 0; i < n; i++) {
            {
                uint32_t uint_phase;
    
                {
                    {
                        uint_phase = __cycle_tilde_01_phasei;
                    }
                }
    
                uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
                number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                number y0 = __cycle_tilde_01_buffer[(Index)idx];
                number y1 = __cycle_tilde_01_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                number y = y0 + frac * (y1 - y0);
    
                {
                    uint32_t pincr = (uint32_t)(uint32_trunc(frequency[(Index)i] * __cycle_tilde_01_f2i));
                    __cycle_tilde_01_phasei = uint32_add(__cycle_tilde_01_phasei, pincr);
                }
    
                out1[(Index)i] = y;
                out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                continue;
            }
        }
    
        this->cycle_tilde_01_phasei = __cycle_tilde_01_phasei;
    }
    
    void dspexpr_03_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_abs(in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void selector_02_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void gen_03_perform(
        const Sample * in1,
        const Sample * in2,
        number diodeCurve,
        number diodeThresh,
        SampleValue * out1,
        Index n
    ) {
        RNBO_UNUSED(diodeThresh);
        RNBO_UNUSED(diodeCurve);
        Index i;
    
        for (i = 0; i < n; i++) {
            number ringround_0 = 0;
    
            {
                auto thresh_4 = 0.5;
                auto curve_3 = 0.5;
                auto carrier_2 = in2[(Index)i];
                auto input_1 = in1[(Index)i];
                number fdiode_5 = 0;
    
                {
                    auto thresh_8 = thresh_4;
                    auto curve_7 = curve_3;
                    auto x_6 = input_1 + carrier_2;
                    fdiode_5 = this->maximum(0, x_6 + thresh_8) * (1 - rnbo_exp(-curve_7 * this->maximum(0, x_6 + thresh_8)));
                }
    
                number d1_9 = fdiode_5;
                number fdiode_10 = 0;
    
                {
                    auto thresh_13 = thresh_4;
                    auto curve_12 = curve_3;
                    auto x_11 = input_1 - carrier_2;
                    fdiode_10 = this->maximum(0, x_11 + thresh_13) * (1 - rnbo_exp(-curve_12 * this->maximum(0, x_11 + thresh_13)));
                }
    
                number d2_14 = fdiode_10;
                number fdiode_15 = 0;
    
                {
                    auto thresh_18 = thresh_4;
                    auto curve_17 = curve_3;
                    auto x_16 = -input_1 + carrier_2;
                    fdiode_15 = this->maximum(0, x_16 + thresh_18) * (1 - rnbo_exp(-curve_17 * this->maximum(0, x_16 + thresh_18)));
                }
    
                number d3_19 = fdiode_15;
                number fdiode_20 = 0;
    
                {
                    auto thresh_23 = thresh_4;
                    auto curve_22 = curve_3;
                    auto x_21 = -input_1 - carrier_2;
                    fdiode_20 = this->maximum(0, x_21 + thresh_23) * (1 - rnbo_exp(-curve_22 * this->maximum(0, x_21 + thresh_23)));
                }
    
                number d4_24 = fdiode_20;
                ringround_0 = (d1_9 - d2_14 + d3_19 - d4_24) * 0.25;
            }
    
            number expr_1_25 = ringround_0;
            number fixdenorm_2_26 = fixdenorm(expr_1_25);
            out1[(Index)i] = fixdenorm_2_26;
        }
    }
    
    void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void numberobj_01_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_01_value = localvalue;
    }
    
    void numberobj_02_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_02_value = localvalue;
    }
    
    void param_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_03_value;
    }
    
    void param_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_03_value_set(preset["value"]);
    }
    
    void param_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_04_value;
    }
    
    void param_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_04_value_set(preset["value"]);
    }
    
    number cycle_tilde_01_ph_next(number freq, number reset) {
        {
            {
                if (reset >= 0.)
                    this->cycle_tilde_01_ph_currentPhase = reset;
            }
        }
    
        number pincr = freq * this->cycle_tilde_01_ph_conv;
    
        if (this->cycle_tilde_01_ph_currentPhase < 0.)
            this->cycle_tilde_01_ph_currentPhase = 1. + this->cycle_tilde_01_ph_currentPhase;
    
        if (this->cycle_tilde_01_ph_currentPhase > 1.)
            this->cycle_tilde_01_ph_currentPhase = this->cycle_tilde_01_ph_currentPhase - 1.;
    
        number tmp = this->cycle_tilde_01_ph_currentPhase;
        this->cycle_tilde_01_ph_currentPhase += pincr;
        return tmp;
    }
    
    void cycle_tilde_01_ph_reset() {
        this->cycle_tilde_01_ph_currentPhase = 0;
    }
    
    void cycle_tilde_01_ph_dspsetup() {
        this->cycle_tilde_01_ph_conv = (number)1 / this->sr;
    }
    
    void cycle_tilde_01_dspsetup(bool force) {
        if ((bool)(this->cycle_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->cycle_tilde_01_phasei = 0;
        this->cycle_tilde_01_f2i = (number)4294967296 / this->samplerate();
        this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
        this->cycle_tilde_01_setupDone = true;
        this->cycle_tilde_01_ph_dspsetup();
    }
    
    void cycle_tilde_01_bufferUpdated() {
        this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
    }
    
    void param_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_05_value;
    }
    
    void param_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_05_value_set(preset["value"]);
    }
    
    void param_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_06_value;
    }
    
    void param_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_06_value_set(preset["value"]);
    }
    
    void ip_01_init() {
        this->ip_01_lastValue = this->ip_01_value;
    }
    
    void ip_01_fillSigBuf() {
        if ((bool)(this->ip_01_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_01_lastIndex); i < k; i++) {
                if (this->ip_01_resetCount > 0) {
                    this->ip_01_sigbuf[(Index)i] = 1;
                    this->ip_01_resetCount--;
                } else {
                    this->ip_01_sigbuf[(Index)i] = this->ip_01_lastValue;
                }
            }
    
            this->ip_01_lastIndex = k;
        }
    }
    
    void ip_01_dspsetup(bool force) {
        if ((bool)(this->ip_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_01_lastIndex = 0;
        this->ip_01_setupDone = true;
    }
    
    void numberobj_01_init() {
        this->numberobj_01_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("p_obj-3/number_obj-30"), 1, this->_currentTime);
    }
    
    void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_01_value;
    }
    
    void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_01_value_set(preset["value"]);
    }
    
    void param_07_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_07_value;
    }
    
    void param_07_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_07_value_set(preset["value"]);
    }
    
    void ip_02_init() {
        this->ip_02_lastValue = this->ip_02_value;
    }
    
    void ip_02_fillSigBuf() {
        if ((bool)(this->ip_02_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_02_lastIndex); i < k; i++) {
                if (this->ip_02_resetCount > 0) {
                    this->ip_02_sigbuf[(Index)i] = 1;
                    this->ip_02_resetCount--;
                } else {
                    this->ip_02_sigbuf[(Index)i] = this->ip_02_lastValue;
                }
            }
    
            this->ip_02_lastIndex = k;
        }
    }
    
    void ip_02_dspsetup(bool force) {
        if ((bool)(this->ip_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_02_lastIndex = 0;
        this->ip_02_setupDone = true;
    }
    
    void numberobj_02_init() {
        this->numberobj_02_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("p_obj-3/number_obj-62"), 1, this->_currentTime);
    }
    
    void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_02_value;
    }
    
    void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_02_value_set(preset["value"]);
    }
    
    void param_08_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_08_value;
    }
    
    void param_08_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_08_value_set(preset["value"]);
    }
    
    void param_09_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_09_value;
    }
    
    void param_09_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_09_value_set(preset["value"]);
    }
    
    void param_10_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_10_value;
    }
    
    void param_10_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_10_value_set(preset["value"]);
    }
    
    void ip_03_init() {
        this->ip_03_lastValue = this->ip_03_value;
    }
    
    void ip_03_fillSigBuf() {
        if ((bool)(this->ip_03_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_03_lastIndex); i < k; i++) {
                if (this->ip_03_resetCount > 0) {
                    this->ip_03_sigbuf[(Index)i] = 1;
                    this->ip_03_resetCount--;
                } else {
                    this->ip_03_sigbuf[(Index)i] = this->ip_03_lastValue;
                }
            }
    
            this->ip_03_lastIndex = k;
        }
    }
    
    void ip_03_dspsetup(bool force) {
        if ((bool)(this->ip_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_03_lastIndex = 0;
        this->ip_03_setupDone = true;
    }
    
    void fzero_01_init() {
        this->fzero_01_onsetPitchCents = 0.8 * 100;
    }
    
    number fzero_01_fzero_ac(int level) {
        int tau = 0;
        int period;
        number tmp2 = 0.;
        number threshold = 0.1;
        number acData[128] = FIXEDSIZEARRAYINIT(128);
    
        for (tau = 1; tau < 128; tau++) {
            acData[(Index)tau] = 0.;
    
            for (int k = 0; k < 128; k++) {
                number tmp = this->fzero_01_wavelets[(Index)level][(Index)k] - this->fzero_01_wavelets[(Index)level][(Index)(k + tau)];
                acData[(Index)tau] += tmp * tmp;
            }
    
            tmp2 += acData[(Index)tau];
            acData[(Index)tau] *= tau / tmp2;
            period = tau - 3;
    
            if (tau > 4 && acData[(Index)period] < threshold && acData[(Index)period] < acData[(Index)(period + 1)]) {
                break;
            }
        }
    
        if (tau < 128 - 1) {
            int tmpMin = (int)(tau - 3);
            number interpMin = tmpMin - 0.5 * ((acData[(Index)tmpMin] - acData[(Index)(tmpMin + 1)] - (acData[(Index)tmpMin] - acData[(Index)(tmpMin - 1)])) / (acData[(Index)tmpMin] - acData[(Index)(tmpMin + 1)] + (acData[(Index)tmpMin] - acData[(Index)(tmpMin - 1)])));
    
            number autoPitch = ((BinOpInt)((BinOpInt)this->samplerate() >> imod_nocast(
                (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)level, 32), 32),
                32
            ))) / interpMin;
    
            return autoPitch;
        } else {
            return 0;
        }
    }
    
    long fzero_01_toCents(number f1, number f2) {
        if (f2 > 0) {
            return (long)(rnbo_floor(1200 * rnbo_fabs(rnbo_log2(f1 / f2)) + 0.5));
        } else {
            return 99999;
        }
    }
    
    array<number, 4> fzero_01_doAnalysis(number currentEnd) {
        long oldMode = 0;
        number maxThresh = 0.;
        number minThresh = 0.;
        number outPeak = 0.;
        Int maxCount[5] = FIXEDSIZEARRAYINIT(5);
        Int minCount[5] = FIXEDSIZEARRAYINIT(5);
        Int maxIndices[5][256] = FIXEDSIZEARRAYINIT(5, 256);
        Int minIndices[5][256] = FIXEDSIZEARRAYINIT(5, 256);
        number vecMin = 999999;
        number vecMax = -999999;
        number vecMean = 0;
        number vecSum = 0;
        auto samplerate = this->samplerate();
        array<number, 4> result = {-1, -1, -1, -1};
    
        if ((bool)(this->fzero_01_oldFreq)) {
            oldMode = trunc(samplerate / this->fzero_01_oldFreq);
        }
    
        this->fzero_01_freq = 0.;
        this->fzero_01_onsetReady -= 256;
        int currentStart = (int)((BinOpInt)((BinOpInt)(currentEnd - 2048) & (BinOpInt)(4096 - 1)));
    
        for (int i = 0; i < 2048; i++) {
            int readout = (int)((BinOpInt)((BinOpInt)(currentStart + i) & (BinOpInt)(4096 - 1)));
    
            if (this->fzero_01_wavelets[0][(Index)readout] > vecMax) {
                vecMax = this->fzero_01_wavelets[0][(Index)readout];
            } else if (this->fzero_01_wavelets[0][(Index)readout] < vecMin) {
                vecMin = this->fzero_01_wavelets[0][(Index)readout];
            }
    
            vecSum = vecSum + this->fzero_01_wavelets[0][(Index)readout];
        }
    
        vecMean = vecSum / (number)2048;
        minThresh = .75 * (vecMin - vecMean) + vecMean;
        maxThresh = .75 * (vecMax - vecMean) + vecMean;
        outPeak = vecMax;
    
        if (rnbo_fabs(vecMin) > vecMax) {
            outPeak = rnbo_fabs(vecMin);
        }
    
        if (outPeak > 9999) {
            outPeak = 0.;
        }
    
        if (outPeak > this->fzero_01_noisethresh) {
            float mode[5] = FIXEDSIZEARRAYINIT(5);
    
            for (int currentLevel = 1; currentLevel < 5; currentLevel++) {
                int peakLimit = 16;
    
                int levelBufSize = (int)((BinOpInt)((BinOpInt)2048 >> imod_nocast((UBinOpInt)imod_nocast(
                    (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)currentLevel, 32), 32),
                    32
                ), 32)));
    
                number lastLevelStartPoint = (currentLevel == 1 ? currentStart : 0);
    
                for (int k = 0; k < levelBufSize; k++) {
                    int sampleIndex1 = (int)((BinOpInt)((BinOpInt)(lastLevelStartPoint + k * 2) & (BinOpInt)(4096 - 1)));
                    int sampleIndex2 = (int)((BinOpInt)((BinOpInt)(lastLevelStartPoint + k * 2 + 1) & (BinOpInt)(4096 - 1)));
                    number lastLevel = currentLevel - 1;
                    this->fzero_01_wavelets[(Index)currentLevel][(Index)k] = (this->fzero_01_wavelets[(Index)lastLevel][(Index)sampleIndex1] + this->fzero_01_wavelets[(Index)lastLevel][(Index)sampleIndex2]) * 0.5;
                }
    
                if (currentLevel == 1) {
                    number autoPitch = this->fzero_01_fzero_ac((int)(currentLevel));
    
                    if (autoPitch >= 20 && autoPitch <= 2500) {
                        this->fzero_01_freq = autoPitch;
                        break;
                    }
                }
    
                int minDist = (int)((BinOpInt)((BinOpInt)(samplerate / (number)2500) >> imod_nocast(
                    (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)currentLevel, 32), 32),
                    32
                )));
    
                minDist = (minDist > 1 ? 1 : minDist);
                maxCount[(Index)currentLevel] = 0;
                minCount[(Index)currentLevel] = 0;
                int direction = 0;
                int extreme = 1;
                int tooClose = 0;
    
                if (this->fzero_01_wavelets[(Index)currentLevel][(Index)(levelBufSize - 1)] - this->fzero_01_wavelets[(Index)currentLevel][(Index)(levelBufSize - 2)] > 0) {
                    direction = 1;
                } else {
                    direction = -1;
                }
    
                for (int k = (int)(levelBufSize - 1); k >= 1; k--) {
                    number test = this->fzero_01_wavelets[(Index)currentLevel][(Index)(k - 1)] - this->fzero_01_wavelets[(Index)currentLevel][(Index)k];
    
                    if (direction >= 0 && test < 0.0) {
                        direction = -1;
    
                        if (this->fzero_01_wavelets[(Index)currentLevel][(Index)k] >= maxThresh && (bool)(extreme) && (bool)(!(bool)(tooClose))) {
                            maxCount[(Index)currentLevel]++;
                            maxIndices[(Index)currentLevel][(Index)maxCount[(Index)currentLevel]] = k;
                            extreme = 0;
                            tooClose = minDist;
                        }
                    } else if (direction <= 0 && test > 0.0) {
                        direction = 1;
    
                        if (this->fzero_01_wavelets[(Index)currentLevel][(Index)k] <= minThresh && (bool)(extreme) && (bool)(!(bool)(tooClose))) {
                            minCount[(Index)currentLevel]++;
                            minIndices[(Index)currentLevel][(Index)minCount[(Index)currentLevel]] = k;
                            extreme = 0;
                            tooClose = minDist;
                        }
                    }
    
                    if (maxCount[(Index)currentLevel] >= peakLimit || minCount[(Index)currentLevel] >= peakLimit) {
                        k = 0;
                    }
    
                    if ((bool)(!(bool)(extreme))) {
                        if ((direction > 0 && this->fzero_01_wavelets[(Index)currentLevel][(Index)k] >= vecMean) || (direction < 0 && this->fzero_01_wavelets[(Index)currentLevel][(Index)k] <= vecMean)) {
                            extreme = 1;
                        }
                    }
    
                    if ((bool)(tooClose)) {
                        tooClose--;
                    }
                }
    
                if (maxCount[(Index)currentLevel] >= 2 && minCount[(Index)currentLevel] >= 2) {
                    int diffLevs = 3;
                    int dCount = 0;
                    int numer;
                    Int differs[1024] = FIXEDSIZEARRAYINIT(1024);
    
                    for (int j = 1; j <= diffLevs; j++) {
                        for (int k = 1; k <= maxCount[(Index)currentLevel] - j; k++) {
                            differs[(Index)dCount] = maxIndices[(Index)currentLevel][(Index)k] - maxIndices[(Index)currentLevel][(Index)(k + j)];
                            dCount++;
                        }
    
                        for (int k = 1; k <= minCount[(Index)currentLevel] - j; k++) {
                            differs[(Index)dCount] = minIndices[(Index)currentLevel][(Index)k] - minIndices[(Index)currentLevel][(Index)(k + j)];
                            dCount++;
                        }
                    }
    
                    numer = 1;
                    mode[(Index)currentLevel] = 0;
                    mode[0] = 0;
    
                    for (int j = 0; j < dCount; j++) {
                        int numerJ = 0;
    
                        for (int k = 0; k < dCount; k++) {
                            numerJ += rnbo_abs(differs[(Index)k] - differs[(Index)j]) <= minDist;
                        }
    
                        if (numerJ >= numer && numerJ > rnbo_floor(levelBufSize / differs[(Index)j]) / (number)4) {
                            if (numerJ == numer) {
                                if ((bool)(oldMode) && rnbo_abs(differs[(Index)j] - ((BinOpInt)((BinOpInt)oldMode >> imod_nocast(
                                    (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)currentLevel, 32), 32),
                                    32
                                )))) < minDist)
                                    mode[(Index)currentLevel] = differs[(Index)j];
                                else if ((bool)(!(bool)(oldMode)) && (differs[(Index)j] > 1.95 * mode[(Index)currentLevel] && differs[(Index)j] < 2.05 * mode[(Index)currentLevel]))
                                    mode[(Index)currentLevel] = differs[(Index)j];
                            } else {
                                numer = numerJ;
                                mode[(Index)currentLevel] = differs[(Index)j];
                            }
                        } else if (numerJ == numer - 1 && (bool)(oldMode) && (bool)(rnbo_abs(differs[(Index)j] - ((BinOpInt)((BinOpInt)oldMode >> imod_nocast(
                            (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)currentLevel, 32), 32),
                            32
                        ))) < minDist)))
                            mode[(Index)currentLevel] = differs[(Index)j];
                    }
    
                    if ((bool)(mode[(Index)currentLevel])) {
                        float sumOfDiffers = 0;
                        int numberOfDiffers = 0;
    
                        for (int j = 1; j <= dCount; j++) {
                            if (rnbo_fabs(mode[(Index)currentLevel] - differs[(Index)j]) <= minDist) {
                                sumOfDiffers += differs[(Index)j];
                                numberOfDiffers++;
                            }
                        }
    
                        mode[(Index)currentLevel] = sumOfDiffers / numberOfDiffers;
                    }
    
                    if ((bool)(mode[(Index)(currentLevel - 1)]) && maxCount[(Index)(currentLevel - 1)] >= 2 && minCount[(Index)(currentLevel - 1)] >= 2) {
                        if (rnbo_fabs(mode[(Index)(currentLevel - 1)] - 2 * mode[(Index)currentLevel]) <= minDist) {
                            this->fzero_01_freq = samplerate / mode[(Index)(currentLevel - 1)] / rnbo_pow(2, currentLevel - 1);
                        } else {
                            this->fzero_01_freq = 0;
                        }
                    }
                }
            }
    
            if (this->fzero_01_onsetReady < 0) {
                if (this->fzero_01_freq >= 20 && this->fzero_01_freq <= 2500) {
                    if (outPeak - this->fzero_01_oldPeak > 0.1 || this->fzero_01_toCents(this->fzero_01_freq, this->fzero_01_onsetFreq) > this->fzero_01_onsetPitchCents) {
                        result[2] = this->fzero_01_freq;
                        result[3] = outPeak;
                        this->fzero_01_oldPeak = outPeak;
                        this->fzero_01_onsetFreq = this->fzero_01_freq;
                        this->fzero_01_onsetReady = 1024;
                    }
                }
            }
    
            result[1] = outPeak;
    
            if (this->fzero_01_freq >= 20) {
                result[0] = this->fzero_01_freq;
            } else if (this->fzero_01_freq > 0) {
                console->log("fzero: Estimated f0 is lower than freqMin.");
            }
        } else {
            oldMode = 0;
            this->fzero_01_oldPeak = 0;
            outPeak = 0;
            result[1] = 0;
            result[0] = 0;
        }
    
        this->fzero_01_oldFreq = this->fzero_01_freq;
        return result;
    }
    
    void fzero_01_dspsetup(bool force) {
        if ((bool)(this->fzero_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->fzero_01_offset = 0;
        this->fzero_01_setupDone = true;
    }
    
    void param_11_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_11_value;
    }
    
    void param_11_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_11_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        param_03_value = 0.1;
        mstosamps_01_ms = 0;
        p_01_target = 0;
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 0;
        gen_03_in1 = 0;
        gen_03_in2 = 0;
        gen_03_diodeCurve = 0.5;
        gen_03_diodeThresh = 0.5;
        p_02_target = 0;
        expr_01_in1 = 0;
        expr_01_in2 = 1;
        expr_01_out1 = 0;
        param_04_value = 0;
        selector_01_onoff = 1;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 1;
        cycle_tilde_01_frequency = 1;
        cycle_tilde_01_phase_offset = 0;
        selector_02_onoff = 1;
        param_05_value = 1;
        mstosamps_02_ms = 0;
        param_06_value = 1;
        ip_01_value = 0;
        ip_01_impulse = 0;
        numberobj_01_value = 0;
        numberobj_01_value_setter(numberobj_01_value);
        dspexpr_03_in1 = 0;
        expr_02_in1 = 0;
        expr_02_in2 = 1;
        expr_02_out1 = 0;
        param_07_value = 0;
        receive_01_output_number = 0;
        ip_02_value = 0;
        ip_02_impulse = 0;
        numberobj_02_value = 0;
        numberobj_02_value_setter(numberobj_02_value);
        param_08_value = 0;
        selector_03_onoff = 1;
        expr_03_in1 = 0;
        expr_03_in2 = 1;
        expr_03_out1 = 0;
        send_01_input_number = 0;
        expr_04_in1 = 0;
        expr_04_out1 = 0;
        param_09_value = 0;
        gate_01_onoff = 0;
        gate_01_out1_number = 0;
        floatnum_01_input_number = 0;
        floatnum_01_value = 0;
        param_10_value = 1;
        ip_03_value = 1;
        ip_03_impulse = 0;
        dspexpr_04_in1 = 0;
        dspexpr_04_in2 = 1;
        select_01_test1 = 0;
        fzero_01_noisethresh = 0.1;
        select_02_test1 = 1;
        expr_05_in1 = 0;
        expr_05_in2 = 0;
        expr_05_out1 = 0;
        param_11_value = 0.1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        signals[6] = nullptr;
        signals[7] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        param_03_lastValue = 0;
        param_04_lastValue = 0;
        cycle_tilde_01_wrap = 0;
        cycle_tilde_01_ph_currentPhase = 0;
        cycle_tilde_01_ph_conv = 0;
        cycle_tilde_01_setupDone = false;
        param_05_lastValue = 0;
        param_06_lastValue = 0;
        ip_01_lastIndex = 0;
        ip_01_lastValue = 0;
        ip_01_resetCount = 0;
        ip_01_sigbuf = nullptr;
        ip_01_setupDone = false;
        numberobj_01_currentFormat = 6;
        numberobj_01_lastValue = 0;
        param_07_lastValue = 0;
        ip_02_lastIndex = 0;
        ip_02_lastValue = 0;
        ip_02_resetCount = 0;
        ip_02_sigbuf = nullptr;
        ip_02_setupDone = false;
        numberobj_02_currentFormat = 6;
        numberobj_02_lastValue = 0;
        param_08_lastValue = 0;
        param_09_lastValue = 0;
        floatnum_01_stored = 0;
        param_10_lastValue = 0;
        ip_03_lastIndex = 0;
        ip_03_lastValue = 0;
        ip_03_resetCount = 0;
        ip_03_sigbuf = nullptr;
        ip_03_setupDone = false;
        fzero_01_offset = 0;
        fzero_01_periodCount = 0;
        fzero_01_freq = 0;
        fzero_01_oldFreq = 0;
        fzero_01_oldPeak = 0;
        fzero_01_onsetReady = 0;
        fzero_01_onsetPitchCents = 80;
        fzero_01_onsetFreq = 0;
        fzero_01_setupDone = false;
        param_11_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number param_03_value;
        number mstosamps_01_ms;
        number p_01_target;
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number gen_03_in1;
        number gen_03_in2;
        number gen_03_diodeCurve;
        number gen_03_diodeThresh;
        number p_02_target;
        number expr_01_in1;
        number expr_01_in2;
        number expr_01_out1;
        number param_04_value;
        number selector_01_onoff;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number cycle_tilde_01_frequency;
        number cycle_tilde_01_phase_offset;
        number selector_02_onoff;
        number param_05_value;
        number mstosamps_02_ms;
        number param_06_value;
        number ip_01_value;
        number ip_01_impulse;
        number numberobj_01_value;
        number dspexpr_03_in1;
        number expr_02_in1;
        number expr_02_in2;
        number expr_02_out1;
        number param_07_value;
        number receive_01_output_number;
        list receive_01_output_list;
        number ip_02_value;
        number ip_02_impulse;
        number numberobj_02_value;
        number param_08_value;
        number selector_03_onoff;
        number expr_03_in1;
        number expr_03_in2;
        number expr_03_out1;
        number send_01_input_number;
        list send_01_input_list;
        number expr_04_in1;
        number expr_04_out1;
        number param_09_value;
        number gate_01_onoff;
        number gate_01_out1_number;
        list gate_01_out1_list;
        number floatnum_01_input_number;
        number floatnum_01_value;
        number param_10_value;
        number ip_03_value;
        number ip_03_impulse;
        number dspexpr_04_in1;
        number dspexpr_04_in2;
        number select_01_test1;
        number fzero_01_noisethresh;
        number select_02_test1;
        number expr_05_in1;
        number expr_05_in2;
        number expr_05_out1;
        number param_11_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[8];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number param_03_lastValue;
        number param_04_lastValue;
        Float64BufferRef cycle_tilde_01_buffer;
        long cycle_tilde_01_wrap;
        uint32_t cycle_tilde_01_phasei;
        SampleValue cycle_tilde_01_f2i;
        number cycle_tilde_01_ph_currentPhase;
        number cycle_tilde_01_ph_conv;
        bool cycle_tilde_01_setupDone;
        number param_05_lastValue;
        number param_06_lastValue;
        SampleIndex ip_01_lastIndex;
        number ip_01_lastValue;
        SampleIndex ip_01_resetCount;
        signal ip_01_sigbuf;
        bool ip_01_setupDone;
        Int numberobj_01_currentFormat;
        number numberobj_01_lastValue;
        number param_07_lastValue;
        SampleIndex ip_02_lastIndex;
        number ip_02_lastValue;
        SampleIndex ip_02_resetCount;
        signal ip_02_sigbuf;
        bool ip_02_setupDone;
        Int numberobj_02_currentFormat;
        number numberobj_02_lastValue;
        number param_08_lastValue;
        number param_09_lastValue;
        number floatnum_01_stored;
        number param_10_lastValue;
        SampleIndex ip_03_lastIndex;
        number ip_03_lastValue;
        SampleIndex ip_03_resetCount;
        signal ip_03_sigbuf;
        bool ip_03_setupDone;
        long fzero_01_offset;
        long fzero_01_periodCount;
        number fzero_01_freq;
        number fzero_01_oldFreq;
        number fzero_01_oldPeak;
        number fzero_01_onsetReady;
        number fzero_01_onsetPitchCents;
        number fzero_01_onsetFreq;
        SampleValue fzero_01_wavelets[5][4096] = { };
        bool fzero_01_setupDone;
        number param_11_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_2058* p_01;
        RNBOSubpatcher_2059* p_02;
    
};

class RNBOSubpatcher_2063 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_2060 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2063;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_2060()
            {
            }
            
            ~RNBOSubpatcher_2060()
            {
            }
            
            virtual RNBOSubpatcher_2063* getPatcher() const {
                return static_cast<RNBOSubpatcher_2063 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                this->gen_04_perform(in1, this->gen_04_rampsamples, out1, this->dummyBuffer, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->gen_04_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_12_getPresetValue(getSubState(preset, "rampsamples"));
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_12_value_set(v);
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    {
                    return this->param_12_value;
                    }
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 1;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "rampsamples";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "p_obj-8/env.follower[1]/rampsamples";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = 1;
                        info->max = 48000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    {
                        value = (value < 1 ? 1 : (value > 48000 ? 48000 : value));
                        ParameterValue normalizedValue = (value - 1) / (48000 - 1);
                        return normalizedValue;
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 0:
                    {
                    {
                        {
                            return 1 + value * (48000 - 1);
                        }
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    return this->param_12_value_constrain(value);
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void param_12_value_set(number v) {
                v = this->param_12_value_constrain(v);
                this->param_12_value = v;
                this->sendParameter(0, false);
            
                if (this->param_12_value != this->param_12_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_12_lastValue = this->param_12_value;
                }
            
                this->intnum_03_input_number_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {
                this->gen_04_history_1_init();
                this->gen_04_history_2_init();
                this->gen_04_history_3_init();
                this->gen_04_counter_9_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
            
                {
                    this->scheduleParamInit(0, 0);
                }
            }
            
            void allocateDataRefs() {}
            
            number param_12_value_constrain(number v) const {
                v = (v > 48000 ? 48000 : (v < 1 ? 1 : v));
                return v;
            }
            
            number gen_04_rampsamples_constrain(number v) const {
                if (v < 1)
                    v = 1;
            
                return v;
            }
            
            void gen_04_rampsamples_set(number v) {
                v = this->gen_04_rampsamples_constrain(v);
                this->gen_04_rampsamples = v;
            }
            
            void intnum_03_out_set(number v) {
                this->gen_04_rampsamples_set(v);
            }
            
            void intnum_03_input_number_set(number v) {
                this->intnum_03_input_number = v;
                this->intnum_03_stored = v;
                this->intnum_03_out_set(trunc(v));
            }
            
            void gen_04_perform(
                const Sample * in1,
                number rampsamples,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                auto __gen_04_history_3_value = this->gen_04_history_3_value;
                auto __gen_04_history_1_value = this->gen_04_history_1_value;
                auto __gen_04_history_2_value = this->gen_04_history_2_value;
                Index i;
            
                for (i = 0; i < n; i++) {
                    out2[(Index)i] = rampsamples;
                    number gte_4_0 = __gen_04_history_2_value >= rampsamples;
                    number abs_5_1 = rnbo_abs(in1[(Index)i]);
                    number gt_6_2 = abs_5_1 > __gen_04_history_1_value;
                    number or_7_3 = (bool)(gt_6_2) || (bool)(gte_4_0);
                    number latch_8_5 = this->gen_04_latch_4_next(abs_5_1, or_7_3);
                    number latch_9_7 = this->gen_04_latch_6_next(__gen_04_history_3_value, or_7_3);
                    number sub_10_8 = latch_8_5 - latch_9_7;
                    number counter_11 = 0;
                    number counter_12 = 0;
                    number counter_13 = 0;
                    array<number, 3> result_10 = this->gen_04_counter_9_next(1, or_7_3 + gte_4_0, 0);
                    counter_13 = result_10[2];
                    counter_12 = result_10[1];
                    counter_11 = result_10[0];
                    number add_14_11 = counter_11 + 1;
                    number div_15_12 = (rampsamples == 0. ? 0. : add_14_11 / rampsamples);
                    number mul_16_13 = sub_10_8 * div_15_12;
                    number add_17_14 = latch_9_7 + mul_16_13;
                    out1[(Index)i] = add_17_14;
                    number history_1_next_18_15 = fixdenorm(latch_8_5);
                    number history_2_next_19_16 = fixdenorm(add_14_11);
                    number history_3_next_20_17 = fixdenorm(add_17_14);
                    __gen_04_history_1_value = history_1_next_18_15;
                    __gen_04_history_3_value = history_3_next_20_17;
                    __gen_04_history_2_value = history_2_next_19_16;
                }
            
                this->gen_04_history_2_value = __gen_04_history_2_value;
                this->gen_04_history_1_value = __gen_04_history_1_value;
                this->gen_04_history_3_value = __gen_04_history_3_value;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number gen_04_history_1_getvalue() {
                return this->gen_04_history_1_value;
            }
            
            void gen_04_history_1_setvalue(number val) {
                this->gen_04_history_1_value = val;
            }
            
            void gen_04_history_1_reset() {
                this->gen_04_history_1_value = 0;
            }
            
            void gen_04_history_1_init() {
                this->gen_04_history_1_value = 0;
            }
            
            number gen_04_history_2_getvalue() {
                return this->gen_04_history_2_value;
            }
            
            void gen_04_history_2_setvalue(number val) {
                this->gen_04_history_2_value = val;
            }
            
            void gen_04_history_2_reset() {
                this->gen_04_history_2_value = 0;
            }
            
            void gen_04_history_2_init() {
                this->gen_04_history_2_value = 0;
            }
            
            number gen_04_history_3_getvalue() {
                return this->gen_04_history_3_value;
            }
            
            void gen_04_history_3_setvalue(number val) {
                this->gen_04_history_3_value = val;
            }
            
            void gen_04_history_3_reset() {
                this->gen_04_history_3_value = 0;
            }
            
            void gen_04_history_3_init() {
                this->gen_04_history_3_value = 0;
            }
            
            number gen_04_latch_4_next(number x, number control) {
                if (control != 0.)
                    this->gen_04_latch_4_value = x;
            
                return this->gen_04_latch_4_value;
            }
            
            void gen_04_latch_4_dspsetup() {
                this->gen_04_latch_4_reset();
            }
            
            void gen_04_latch_4_reset() {
                this->gen_04_latch_4_value = 0;
            }
            
            number gen_04_latch_6_next(number x, number control) {
                if (control != 0.)
                    this->gen_04_latch_6_value = x;
            
                return this->gen_04_latch_6_value;
            }
            
            void gen_04_latch_6_dspsetup() {
                this->gen_04_latch_6_reset();
            }
            
            void gen_04_latch_6_reset() {
                this->gen_04_latch_6_value = 0;
            }
            
            array<number, 3> gen_04_counter_9_next(number a, number reset, number limit) {
                RNBO_UNUSED(limit);
                RNBO_UNUSED(a);
                number carry_flag = 0;
            
                if (reset != 0) {
                    this->gen_04_counter_9_count = 0;
                    this->gen_04_counter_9_carry = 0;
                } else {
                    this->gen_04_counter_9_count += 1;
                }
            
                return {this->gen_04_counter_9_count, carry_flag, this->gen_04_counter_9_carry};
            }
            
            void gen_04_counter_9_init() {
                this->gen_04_counter_9_count = -1;
            }
            
            void gen_04_counter_9_reset() {
                this->gen_04_counter_9_carry = 0;
                this->gen_04_counter_9_count = 0;
            }
            
            void gen_04_dspsetup(bool force) {
                if ((bool)(this->gen_04_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->gen_04_setupDone = true;
                this->gen_04_latch_4_dspsetup();
                this->gen_04_latch_6_dspsetup();
            }
            
            void param_12_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_12_value;
            }
            
            void param_12_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_12_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                gen_04_in1 = 0;
                gen_04_rampsamples = 1;
                intnum_03_input_number = 0;
                intnum_03_value = 0;
                param_12_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                gen_04_history_1_value = 0;
                gen_04_history_2_value = 0;
                gen_04_history_3_value = 0;
                gen_04_latch_4_value = 0;
                gen_04_latch_6_value = 0;
                gen_04_counter_9_carry = 0;
                gen_04_counter_9_count = 0;
                gen_04_setupDone = false;
                intnum_03_stored = 0;
                param_12_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number gen_04_in1;
                number gen_04_rampsamples;
                number intnum_03_input_number;
                number intnum_03_value;
                number param_12_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number gen_04_history_1_value;
                number gen_04_history_2_value;
                number gen_04_history_3_value;
                number gen_04_latch_4_value;
                number gen_04_latch_6_value;
                int gen_04_counter_9_carry;
                number gen_04_counter_9_count;
                bool gen_04_setupDone;
                number intnum_03_stored;
                number param_12_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_2061 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2063;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_2061()
            {
            }
            
            ~RNBOSubpatcher_2061()
            {
            }
            
            virtual RNBOSubpatcher_2063* getPatcher() const {
                return static_cast<RNBOSubpatcher_2063 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                this->gen_05_perform(in1, this->gen_05_rampsamples, out1, this->dummyBuffer, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->gen_05_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_13_getPresetValue(getSubState(preset, "rampsamples"));
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_13_value_set(v);
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    {
                    return this->param_13_value;
                    }
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 1;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "rampsamples";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "p_obj-8/env.follower/rampsamples";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = 1;
                        info->max = 48000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    {
                        value = (value < 1 ? 1 : (value > 48000 ? 48000 : value));
                        ParameterValue normalizedValue = (value - 1) / (48000 - 1);
                        return normalizedValue;
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 0:
                    {
                    {
                        {
                            return 1 + value * (48000 - 1);
                        }
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    return this->param_13_value_constrain(value);
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void param_13_value_set(number v) {
                v = this->param_13_value_constrain(v);
                this->param_13_value = v;
                this->sendParameter(0, false);
            
                if (this->param_13_value != this->param_13_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_13_lastValue = this->param_13_value;
                }
            
                this->intnum_04_input_number_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {
                this->gen_05_history_1_init();
                this->gen_05_history_2_init();
                this->gen_05_history_3_init();
                this->gen_05_counter_6_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
            
                {
                    this->scheduleParamInit(0, 0);
                }
            }
            
            void allocateDataRefs() {}
            
            number param_13_value_constrain(number v) const {
                v = (v > 48000 ? 48000 : (v < 1 ? 1 : v));
                return v;
            }
            
            number gen_05_rampsamples_constrain(number v) const {
                if (v < 1)
                    v = 1;
            
                return v;
            }
            
            void gen_05_rampsamples_set(number v) {
                v = this->gen_05_rampsamples_constrain(v);
                this->gen_05_rampsamples = v;
            }
            
            void intnum_04_out_set(number v) {
                this->gen_05_rampsamples_set(v);
            }
            
            void intnum_04_input_number_set(number v) {
                this->intnum_04_input_number = v;
                this->intnum_04_stored = v;
                this->intnum_04_out_set(trunc(v));
            }
            
            void gen_05_perform(
                const Sample * in1,
                number rampsamples,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                auto __gen_05_history_3_value = this->gen_05_history_3_value;
                auto __gen_05_history_1_value = this->gen_05_history_1_value;
                auto __gen_05_history_2_value = this->gen_05_history_2_value;
                Index i;
            
                for (i = 0; i < n; i++) {
                    out2[(Index)i] = rampsamples;
                    number gte_4_0 = __gen_05_history_2_value >= rampsamples;
                    number abs_5_1 = rnbo_abs(in1[(Index)i]);
                    number gt_6_2 = abs_5_1 > __gen_05_history_1_value;
                    number or_7_3 = (bool)(gt_6_2) || (bool)(gte_4_0);
                    number latch_8_5 = this->gen_05_latch_4_next(abs_5_1, or_7_3);
                    number counter_9 = 0;
                    number counter_10 = 0;
                    number counter_11 = 0;
                    array<number, 3> result_7 = this->gen_05_counter_6_next(1, or_7_3 + gte_4_0, 0);
                    counter_11 = result_7[2];
                    counter_10 = result_7[1];
                    counter_9 = result_7[0];
                    number add_12_8 = counter_9 + 1;
                    number div_13_9 = (rampsamples == 0. ? 0. : add_12_8 / rampsamples);
                    number latch_14_11 = this->gen_05_latch_10_next(__gen_05_history_3_value, or_7_3);
                    number sub_15_12 = latch_8_5 - latch_14_11;
                    number mul_16_13 = sub_15_12 * div_13_9;
                    number add_17_14 = latch_14_11 + mul_16_13;
                    out1[(Index)i] = add_17_14;
                    number history_1_next_18_15 = fixdenorm(latch_8_5);
                    number history_2_next_19_16 = fixdenorm(add_12_8);
                    number history_3_next_20_17 = fixdenorm(add_17_14);
                    __gen_05_history_1_value = history_1_next_18_15;
                    __gen_05_history_3_value = history_3_next_20_17;
                    __gen_05_history_2_value = history_2_next_19_16;
                }
            
                this->gen_05_history_2_value = __gen_05_history_2_value;
                this->gen_05_history_1_value = __gen_05_history_1_value;
                this->gen_05_history_3_value = __gen_05_history_3_value;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number gen_05_history_1_getvalue() {
                return this->gen_05_history_1_value;
            }
            
            void gen_05_history_1_setvalue(number val) {
                this->gen_05_history_1_value = val;
            }
            
            void gen_05_history_1_reset() {
                this->gen_05_history_1_value = 0;
            }
            
            void gen_05_history_1_init() {
                this->gen_05_history_1_value = 0;
            }
            
            number gen_05_history_2_getvalue() {
                return this->gen_05_history_2_value;
            }
            
            void gen_05_history_2_setvalue(number val) {
                this->gen_05_history_2_value = val;
            }
            
            void gen_05_history_2_reset() {
                this->gen_05_history_2_value = 0;
            }
            
            void gen_05_history_2_init() {
                this->gen_05_history_2_value = 0;
            }
            
            number gen_05_history_3_getvalue() {
                return this->gen_05_history_3_value;
            }
            
            void gen_05_history_3_setvalue(number val) {
                this->gen_05_history_3_value = val;
            }
            
            void gen_05_history_3_reset() {
                this->gen_05_history_3_value = 0;
            }
            
            void gen_05_history_3_init() {
                this->gen_05_history_3_value = 0;
            }
            
            number gen_05_latch_4_next(number x, number control) {
                if (control != 0.)
                    this->gen_05_latch_4_value = x;
            
                return this->gen_05_latch_4_value;
            }
            
            void gen_05_latch_4_dspsetup() {
                this->gen_05_latch_4_reset();
            }
            
            void gen_05_latch_4_reset() {
                this->gen_05_latch_4_value = 0;
            }
            
            array<number, 3> gen_05_counter_6_next(number a, number reset, number limit) {
                RNBO_UNUSED(limit);
                RNBO_UNUSED(a);
                number carry_flag = 0;
            
                if (reset != 0) {
                    this->gen_05_counter_6_count = 0;
                    this->gen_05_counter_6_carry = 0;
                } else {
                    this->gen_05_counter_6_count += 1;
                }
            
                return {this->gen_05_counter_6_count, carry_flag, this->gen_05_counter_6_carry};
            }
            
            void gen_05_counter_6_init() {
                this->gen_05_counter_6_count = -1;
            }
            
            void gen_05_counter_6_reset() {
                this->gen_05_counter_6_carry = 0;
                this->gen_05_counter_6_count = 0;
            }
            
            number gen_05_latch_10_next(number x, number control) {
                if (control != 0.)
                    this->gen_05_latch_10_value = x;
            
                return this->gen_05_latch_10_value;
            }
            
            void gen_05_latch_10_dspsetup() {
                this->gen_05_latch_10_reset();
            }
            
            void gen_05_latch_10_reset() {
                this->gen_05_latch_10_value = 0;
            }
            
            void gen_05_dspsetup(bool force) {
                if ((bool)(this->gen_05_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->gen_05_setupDone = true;
                this->gen_05_latch_4_dspsetup();
                this->gen_05_latch_10_dspsetup();
            }
            
            void param_13_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_13_value;
            }
            
            void param_13_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_13_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                gen_05_in1 = 0;
                gen_05_rampsamples = 1;
                intnum_04_input_number = 0;
                intnum_04_value = 0;
                param_13_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                gen_05_history_1_value = 0;
                gen_05_history_2_value = 0;
                gen_05_history_3_value = 0;
                gen_05_latch_4_value = 0;
                gen_05_counter_6_carry = 0;
                gen_05_counter_6_count = 0;
                gen_05_latch_10_value = 0;
                gen_05_setupDone = false;
                intnum_04_stored = 0;
                param_13_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number gen_05_in1;
                number gen_05_rampsamples;
                number intnum_04_input_number;
                number intnum_04_value;
                number param_13_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number gen_05_history_1_value;
                number gen_05_history_2_value;
                number gen_05_history_3_value;
                number gen_05_latch_4_value;
                int gen_05_counter_6_carry;
                number gen_05_counter_6_count;
                number gen_05_latch_10_value;
                bool gen_05_setupDone;
                number intnum_04_stored;
                number param_13_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_2063()
    {
    }
    
    ~RNBOSubpatcher_2063()
    {
        delete this->p_03;
        delete this->p_04;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, 555692221, false);
        getEngine()->flushClockEvents(this, -161950333, false);
        getEngine()->flushClockEvents(this, 1793217402, false);
        getEngine()->flushClockEvents(this, 388042711, false);
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    number samplerate() const {
        return this->sr;
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * source_in = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        SampleValue * source_ratio = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
        const SampleValue * target_in = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * target_ratio = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        this->signalsend_03_perform(in1, this->signals[0], n);
        this->signalforwarder_03_perform(this->signals[0], source_in, n);
        this->ip_04_perform(this->signals[1], n);
        this->ip_05_perform(this->signals[2], n);
    
        this->selector_04_perform(
            this->selector_04_onoff,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            n
        );
    
        this->ip_06_perform(this->signals[2], n);
        this->dspexpr_08_perform(this->signals[2], this->dspexpr_08_in2, this->signals[1], n);
    
        this->selector_06_perform(
            this->selector_06_onoff,
            this->signals[2],
            this->signals[1],
            this->signals[4],
            n
        );
    
        this->signalsend_04_perform(this->signals[4], this->signals[1], n);
        this->signalforwarder_04_perform(this->signals[1], source_ratio, n);
        this->stackprotect_perform(n);
        this->signaladder_06_perform(target_in, this->signals[0], this->signals[2], n);
        this->signalreceive_04_perform(this->signals[2], this->signals[4], n);
        this->p_03_perform(this->signals[4], this->signals[5], n);
        this->signaladder_07_perform(target_in, this->signals[0], this->signals[0], n);
        this->signalreceive_06_perform(this->signals[0], this->signals[6], n);
        this->fzero_02_perform(this->signals[6], n);
        this->signaladder_08_perform(target_ratio, this->signals[1], this->signals[1], n);
        this->signalreceive_05_perform(this->signals[1], this->signals[6], n);
        this->dspexpr_06_perform(this->signals[3], this->signals[6], this->signals[7], n);
        this->p_04_perform(this->signals[7], this->signals[6], n);
    
        this->cycle_tilde_02_perform(
            this->signals[6],
            this->cycle_tilde_02_phase_offset,
            this->signals[7],
            this->dummyBuffer,
            n
        );
    
        this->dspexpr_07_perform(this->signals[7], this->signals[6], n);
    
        this->selector_05_perform(
            this->selector_05_onoff,
            this->signals[7],
            this->signals[6],
            this->signals[3],
            n
        );
    
        this->gen_06_perform(
            this->signals[4],
            this->signals[3],
            this->gen_06_diodeCurve,
            this->gen_06_diodeThresh,
            this->signals[6],
            n
        );
    
        this->dspexpr_05_perform(this->signals[5], this->signals[6], out1, n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 8; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->ip_04_sigbuf = resizeSignal(this->ip_04_sigbuf, this->maxvs, maxBlockSize);
            this->ip_05_sigbuf = resizeSignal(this->ip_05_sigbuf, this->maxvs, maxBlockSize);
            this->ip_06_sigbuf = resizeSignal(this->ip_06_sigbuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->ip_04_dspsetup(forceDSPSetup);
        this->ip_05_dspsetup(forceDSPSetup);
        this->ip_06_dspsetup(forceDSPSetup);
        this->fzero_02_dspsetup(forceDSPSetup);
        this->cycle_tilde_02_dspsetup(forceDSPSetup);
        this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_03 = new RNBOSubpatcher_2060();
        this->p_03->setEngineAndPatcher(this->getEngine(), this);
        this->p_03->initialize();
        this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
        this->p_04 = new RNBOSubpatcher_2061();
        this->p_04->setEngineAndPatcher(this->getEngine(), this);
        this->p_04->initialize();
        this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_14_getPresetValue(getSubState(preset, "ampEnv"));
        this->param_15_getPresetValue(getSubState(preset, "pitchFollow"));
        this->param_16_getPresetValue(getSubState(preset, "pitchGlide"));
        this->param_17_getPresetValue(getSubState(preset, "freq"));
        this->param_18_getPresetValue(getSubState(preset, "ampMod"));
        this->param_19_getPresetValue(getSubState(preset, "subharmonic"));
        this->param_20_getPresetValue(getSubState(preset, "pitchHold"));
        this->param_21_getPresetValue(getSubState(preset, "ratio"));
        this->param_22_getPresetValue(getSubState(preset, "pitchThresh"));
        this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "env.follower[1]"));
        this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "env.follower"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_14_value_set(v);
            break;
            }
        case 1:
            {
            this->param_15_value_set(v);
            break;
            }
        case 2:
            {
            this->param_16_value_set(v);
            break;
            }
        case 3:
            {
            this->param_17_value_set(v);
            break;
            }
        case 4:
            {
            this->param_18_value_set(v);
            break;
            }
        case 5:
            {
            this->param_19_value_set(v);
            break;
            }
        case 6:
            {
            this->param_20_value_set(v);
            break;
            }
        case 7:
            {
            this->param_21_value_set(v);
            break;
            }
        case 8:
            {
            this->param_22_value_set(v);
            break;
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_03->getNumParameters())
                this->p_03->setParameterValue(index, v, time);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                this->p_04->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_14_value;
            }
        case 1:
            {
            return this->param_15_value;
            }
        case 2:
            {
            return this->param_16_value;
            }
        case 3:
            {
            return this->param_17_value;
            }
        case 4:
            {
            return this->param_18_value;
            }
        case 5:
            {
            return this->param_19_value;
            }
        case 6:
            {
            return this->param_20_value;
            }
        case 7:
            {
            return this->param_21_value;
            }
        case 8:
            {
            return this->param_22_value;
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterValue(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 2;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 2;
    }
    
    ParameterIndex getNumParameters() const {
        return 9 + this->p_03->getNumParameters() + this->p_04->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "ampEnv";
            }
        case 1:
            {
            return "pitchFollow";
            }
        case 2:
            {
            return "pitchGlide";
            }
        case 3:
            {
            return "freq";
            }
        case 4:
            {
            return "ampMod";
            }
        case 5:
            {
            return "subharmonic";
            }
        case 6:
            {
            return "pitchHold";
            }
        case 7:
            {
            return "ratio";
            }
        case 8:
            {
            return "pitchThresh";
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterName(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "p_obj-8/ampEnv";
            }
        case 1:
            {
            return "p_obj-8/pitchFollow";
            }
        case 2:
            {
            return "p_obj-8/pitchGlide";
            }
        case 3:
            {
            return "p_obj-8/freq";
            }
        case 4:
            {
            return "p_obj-8/ampMod";
            }
        case 5:
            {
            return "p_obj-8/subharmonic";
            }
        case 6:
            {
            return "p_obj-8/pitchHold";
            }
        case 7:
            {
            return "p_obj-8/ratio";
            }
        case 8:
            {
            return "p_obj-8/pitchThresh";
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterId(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.1;
                info->min = 0;
                info->max = 1000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal1[] = {"0", "1"};
                info->enumValues = eVal1;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 2:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 0;
                info->max = 1000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 3:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = -100;
                info->max = 100;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 4:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal4[] = {"0", "1"};
                info->enumValues = eVal4;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 5:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal5[] = {"0", "1"};
                info->enumValues = eVal5;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 6:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal6[] = {"0", "1"};
                info->enumValues = eVal6;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 7:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 1;
                info->max = 32;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 8:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.1;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            default:
                {
                index -= 9;
    
                if (index < this->p_03->getNumParameters())
                    this->p_03->getParameterInfo(index, info);
    
                index -= this->p_03->getNumParameters();
    
                if (index < this->p_04->getNumParameters())
                    this->p_04->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_03)
            return 9;
    
        if (subpatcher == this->p_04)
            return 9 + this->p_03->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 8:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 1:
        case 4:
        case 5:
        case 6:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
    
                {
                    normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 2);
                }
    
                return normalizedValue;
            }
            }
        case 0:
        case 2:
            {
            {
                value = (value < 0 ? 0 : (value > 1000 ? 1000 : value));
                ParameterValue normalizedValue = (value - 0) / (1000 - 0);
                return normalizedValue;
            }
            }
        case 7:
            {
            {
                value = (value < 1 ? 1 : (value > 32 ? 32 : value));
                ParameterValue normalizedValue = (value - 1) / (32 - 1);
                return normalizedValue;
            }
            }
        case 3:
            {
            {
                value = (value < -100 ? -100 : (value > 100 ? 100 : value));
                ParameterValue normalizedValue = (value - -100) / (100 - -100);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 8:
            {
            {
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 1:
        case 4:
        case 5:
        case 6:
            {
            {
                {
                    value = this->applyStepsToNormalizedParameterValue(value, 2);
                }
    
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 0:
        case 2:
            {
            {
                {
                    return 0 + value * (1000 - 0);
                }
            }
            }
        case 7:
            {
            {
                {
                    return 1 + value * (32 - 1);
                }
            }
            }
        case 3:
            {
            {
                {
                    return -100 + value * (100 - -100);
                }
            }
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_14_value_constrain(value);
            }
        case 1:
            {
            return this->param_15_value_constrain(value);
            }
        case 2:
            {
            return this->param_16_value_constrain(value);
            }
        case 3:
            {
            return this->param_17_value_constrain(value);
            }
        case 4:
            {
            return this->param_18_value_constrain(value);
            }
        case 5:
            {
            return this->param_19_value_constrain(value);
            }
        case 6:
            {
            return this->param_20_value_constrain(value);
            }
        case 7:
            {
            return this->param_21_value_constrain(value);
            }
        case 8:
            {
            return this->param_22_value_constrain(value);
            }
        default:
            {
            index -= 9;
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->constrainParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case 555692221:
            {
            this->fzero_02_onset_bang_bang();
            break;
            }
        case -161950333:
            {
            this->fzero_02_onset_list_set(value);
            break;
            }
        case 1793217402:
            {
            this->fzero_02_amplitude_set(value);
            break;
            }
        case 388042711:
            {
            this->fzero_02_pitch_set(value);
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("p_obj-8/number_obj-30") == objectId)
                this->numberobj_03_valin_set(payload);
    
            if (TAG("p_obj-8/number_obj-62") == objectId)
                this->numberobj_04_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("p_obj-8/number_obj-30") == objectId)
                this->numberobj_03_format_set(payload);
    
            if (TAG("p_obj-8/number_obj-62") == objectId)
                this->numberobj_04_format_set(payload);
    
            break;
            }
        }
    
        this->p_03->processNumMessage(tag, objectId, time, payload);
        this->p_04->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_03->processListMessage(tag, objectId, time, payload);
        this->p_04->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_03->processBangMessage(tag, objectId, time);
        this->p_04->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("p_obj-8/number_obj-30"):
            {
            return "p_obj-8/number_obj-30";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("p_obj-8/number_obj-62"):
            {
            return "p_obj-8/number_obj-62";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        auto subpatchResult_0 = this->p_03->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_04->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 0) {
            this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
            this->cycle_tilde_02_bufferUpdated();
        }
    
        this->p_03->processDataViewUpdate(index, time);
        this->p_04->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
    }
    
    protected:
    
    void param_14_value_set(number v) {
        v = this->param_14_value_constrain(v);
        this->param_14_value = v;
        this->sendParameter(0, false);
    
        if (this->param_14_value != this->param_14_lastValue) {
            this->getEngine()->presetTouched();
            this->param_14_lastValue = this->param_14_value;
        }
    
        this->mstosamps_03_ms_set(v);
    }
    
    void param_15_value_set(number v) {
        v = this->param_15_value_constrain(v);
        this->param_15_value = v;
        this->sendParameter(1, false);
    
        if (this->param_15_value != this->param_15_lastValue) {
            this->getEngine()->presetTouched();
            this->param_15_lastValue = this->param_15_value;
        }
    
        this->expr_06_in1_set(v);
    }
    
    void param_16_value_set(number v) {
        v = this->param_16_value_constrain(v);
        this->param_16_value = v;
        this->sendParameter(2, false);
    
        if (this->param_16_value != this->param_16_lastValue) {
            this->getEngine()->presetTouched();
            this->param_16_lastValue = this->param_16_value;
        }
    
        this->mstosamps_04_ms_set(v);
    }
    
    void param_17_value_set(number v) {
        v = this->param_17_value_constrain(v);
        this->param_17_value = v;
        this->sendParameter(3, false);
    
        if (this->param_17_value != this->param_17_lastValue) {
            this->getEngine()->presetTouched();
            this->param_17_lastValue = this->param_17_value;
        }
    
        this->numberobj_03_value_set(v);
    }
    
    void param_18_value_set(number v) {
        v = this->param_18_value_constrain(v);
        this->param_18_value = v;
        this->sendParameter(4, false);
    
        if (this->param_18_value != this->param_18_lastValue) {
            this->getEngine()->presetTouched();
            this->param_18_lastValue = this->param_18_value;
        }
    
        this->expr_07_in1_set(v);
    }
    
    void param_19_value_set(number v) {
        v = this->param_19_value_constrain(v);
        this->param_19_value = v;
        this->sendParameter(5, false);
    
        if (this->param_19_value != this->param_19_lastValue) {
            this->getEngine()->presetTouched();
            this->param_19_lastValue = this->param_19_value;
        }
    
        this->expr_08_in1_set(v);
    }
    
    void param_20_value_set(number v) {
        v = this->param_20_value_constrain(v);
        this->param_20_value = v;
        this->sendParameter(6, false);
    
        if (this->param_20_value != this->param_20_lastValue) {
            this->getEngine()->presetTouched();
            this->param_20_lastValue = this->param_20_value;
        }
    
        this->expr_09_in1_set(v);
    }
    
    void param_21_value_set(number v) {
        v = this->param_21_value_constrain(v);
        this->param_21_value = v;
        this->sendParameter(7, false);
    
        if (this->param_21_value != this->param_21_lastValue) {
            this->getEngine()->presetTouched();
            this->param_21_lastValue = this->param_21_value;
        }
    
        this->ip_06_value_set(v);
    }
    
    void param_22_value_set(number v) {
        v = this->param_22_value_constrain(v);
        this->param_22_value = v;
        this->sendParameter(8, false);
    
        if (this->param_22_value != this->param_22_lastValue) {
            this->getEngine()->presetTouched();
            this->param_22_lastValue = this->param_22_value;
        }
    
        this->expr_10_in2_set(v);
    }
    
    void numberobj_03_valin_set(number v) {
        this->numberobj_03_value_set(v);
    }
    
    void numberobj_03_format_set(number v) {
        this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_04_valin_set(number v) {
        this->numberobj_04_value_set(v);
    }
    
    void numberobj_04_format_set(number v) {
        this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void fzero_02_onset_bang_bang() {}
    
    void fzero_02_onset_list_set(const list& ) {}
    
    void fzero_02_amplitude_set(number v) {
        this->expr_10_in1_set(v);
    }
    
    void fzero_02_pitch_set(number v) {
        this->select_03_input_number_set(v);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 1;
    }
    
    Index getNumOutputChannels() const {
        return 1;
    }
    
    void initializeObjects() {
        this->ip_04_init();
        this->numberobj_03_init();
        this->ip_05_init();
        this->numberobj_04_init();
        this->ip_06_init();
        this->fzero_02_init();
        this->p_03->initializeObjects();
        this->p_04->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_03->startup();
        this->p_04->startup();
    
        {
            this->scheduleParamInit(0, 0);
        }
    
        {
            this->scheduleParamInit(1, 0);
        }
    
        {
            this->scheduleParamInit(2, 0);
        }
    
        {
            this->scheduleParamInit(3, 0);
        }
    
        {
            this->scheduleParamInit(4, 0);
        }
    
        {
            this->scheduleParamInit(5, 0);
        }
    
        {
            this->scheduleParamInit(6, 0);
        }
    
        {
            this->scheduleParamInit(7, 0);
        }
    
        {
            this->scheduleParamInit(8, 0);
        }
    }
    
    void allocateDataRefs() {
        this->p_03->allocateDataRefs();
        this->p_04->allocateDataRefs();
        this->cycle_tilde_02_buffer->requestSize(16384, 1);
        this->cycle_tilde_02_buffer->setSampleRate(this->sr);
        this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();
    }
    
    number param_14_value_constrain(number v) const {
        v = (v > 1000 ? 1000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_03_rampsamples_set(number v) {
        {
            this->p_03->setParameterValue(0, v, this->_currentTime);
        }
    }
    
    void mstosamps_03_out1_set(number v) {
        this->p_03_rampsamples_set(v);
    }
    
    void mstosamps_03_ms_set(number ms) {
        this->mstosamps_03_ms = ms;
    
        {
            this->mstosamps_03_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    number param_15_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void selector_04_onoff_set(number v) {
        this->selector_04_onoff = v;
    }
    
    void expr_06_out1_set(number v) {
        this->expr_06_out1 = v;
        this->selector_04_onoff_set(this->expr_06_out1);
    }
    
    void expr_06_in1_set(number in1) {
        this->expr_06_in1 = in1;
        this->expr_06_out1_set(this->expr_06_in1 + this->expr_06_in2);//#map:p_obj-8/+_obj-26:1
    }
    
    number param_16_value_constrain(number v) const {
        v = (v > 1000 ? 1000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_04_rampsamples_set(number v) {
        {
            this->p_04->setParameterValue(0, v, this->_currentTime);
        }
    }
    
    void mstosamps_04_out1_set(number v) {
        this->p_04_rampsamples_set(v);
    }
    
    void mstosamps_04_ms_set(number ms) {
        this->mstosamps_04_ms = ms;
    
        {
            this->mstosamps_04_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    number param_17_value_constrain(number v) const {
        v = (v > 100 ? 100 : (v < -100 ? -100 : v));
        return v;
    }
    
    void ip_04_value_set(number v) {
        this->ip_04_value = v;
        this->ip_04_fillSigBuf();
        this->ip_04_lastValue = v;
    }
    
    void numberobj_03_output_set(number v) {
        this->ip_04_value_set(v);
    }
    
    void numberobj_03_value_set(number v) {
        this->numberobj_03_value_setter(v);
        v = this->numberobj_03_value;
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("p_obj-8/number_obj-30"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_03_output_set(localvalue);
    }
    
    number param_18_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void selector_05_onoff_set(number v) {
        this->selector_05_onoff = v;
    }
    
    void expr_07_out1_set(number v) {
        this->expr_07_out1 = v;
        this->selector_05_onoff_set(this->expr_07_out1);
    }
    
    void expr_07_in1_set(number in1) {
        this->expr_07_in1 = in1;
        this->expr_07_out1_set(this->expr_07_in1 + this->expr_07_in2);//#map:p_obj-8/+_obj-22:1
    }
    
    number param_19_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void selector_06_onoff_set(number v) {
        this->selector_06_onoff = v;
    }
    
    void expr_08_out1_set(number v) {
        this->expr_08_out1 = v;
        this->selector_06_onoff_set(this->expr_08_out1);
    }
    
    void expr_08_in1_set(number in1) {
        this->expr_08_in1 = in1;
        this->expr_08_out1_set(this->expr_08_in1 + this->expr_08_in2);//#map:p_obj-8/+_obj-31:1
    }
    
    number param_20_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void gate_02_onoff_set(number v) {
        this->gate_02_onoff = v;
    }
    
    void expr_09_out1_set(number v) {
        this->expr_09_out1 = v;
        this->gate_02_onoff_set(this->expr_09_out1);
    }
    
    void expr_09_in1_set(number in1) {
        this->expr_09_in1 = in1;
        this->expr_09_out1_set(this->expr_09_in1 == 0);//#map:p_obj-8/!_obj-43:1
    }
    
    number param_21_value_constrain(number v) const {
        v = (v > 32 ? 32 : (v < 1 ? 1 : v));
        return v;
    }
    
    void ip_06_value_set(number v) {
        this->ip_06_value = v;
        this->ip_06_fillSigBuf();
        this->ip_06_lastValue = v;
    }
    
    number param_22_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void expr_10_in2_set(number v) {
        this->expr_10_in2 = v;
    }
    
    void ip_05_value_set(number v) {
        this->ip_05_value = v;
        this->ip_05_fillSigBuf();
        this->ip_05_lastValue = v;
    }
    
    void numberobj_04_output_set(number v) {
        this->ip_05_value_set(v);
    }
    
    void numberobj_04_value_set(number v) {
        this->numberobj_04_value_setter(v);
        v = this->numberobj_04_value;
        number localvalue = v;
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("p_obj-8/number_obj-62"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_04_output_set(localvalue);
    }
    
    void receive_02_output_number_set(number v) {
        this->receive_02_output_number = v;
        this->numberobj_04_value_set(v);
    }
    
    void signalsend_03_perform(const SampleValue * input, SampleValue * send, Index n) {
        for (Index i = 0; i < n; i++) {
            send[(Index)i] = input[(Index)i];
        }
    }
    
    void signalforwarder_03_perform(const SampleValue * input, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = input[(Index)i];
        }
    }
    
    void ip_04_perform(SampleValue * out, Index n) {
        auto __ip_04_lastValue = this->ip_04_lastValue;
        auto __ip_04_lastIndex = this->ip_04_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_04_lastIndex ? __ip_04_lastValue : this->ip_04_sigbuf[(Index)i]);
        }
    
        __ip_04_lastIndex = 0;
        this->ip_04_lastIndex = __ip_04_lastIndex;
    }
    
    void ip_05_perform(SampleValue * out, Index n) {
        auto __ip_05_lastValue = this->ip_05_lastValue;
        auto __ip_05_lastIndex = this->ip_05_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_05_lastIndex ? __ip_05_lastValue : this->ip_05_sigbuf[(Index)i]);
        }
    
        __ip_05_lastIndex = 0;
        this->ip_05_lastIndex = __ip_05_lastIndex;
    }
    
    void selector_04_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void ip_06_perform(SampleValue * out, Index n) {
        auto __ip_06_lastValue = this->ip_06_lastValue;
        auto __ip_06_lastIndex = this->ip_06_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_06_lastIndex ? __ip_06_lastValue : this->ip_06_sigbuf[(Index)i]);
        }
    
        __ip_06_lastIndex = 0;
        this->ip_06_lastIndex = __ip_06_lastIndex;
    }
    
    void dspexpr_08_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = (in1[(Index)i] == 0. ? 0. : 1 / in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void selector_06_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void signalsend_04_perform(const SampleValue * input, SampleValue * send, Index n) {
        for (Index i = 0; i < n; i++) {
            send[(Index)i] = input[(Index)i];
        }
    }
    
    void signalforwarder_04_perform(const SampleValue * input, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = input[(Index)i];
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void signaladder_06_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signalreceive_04_perform(const SampleValue * receive, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = receive[(Index)i];
        }
    }
    
    void p_03_perform(const SampleValue * in1, SampleValue * out1, Index n) {
        ConstSampleArray<1> ins = {in1};
        SampleArray<1> outs = {out1};
        this->p_03->process(ins, 1, outs, 1, n);
    }
    
    void signaladder_07_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signalreceive_06_perform(const SampleValue * receive, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = receive[(Index)i];
        }
    }
    
    void send_02_input_number_set(number v) {
        this->send_02_input_number = v;
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_06_source_detectedFreq_number_set(v);
        this->receive_02_output_number_set(v);
    }
    
    void floatnum_02_out_set(number v) {
        this->send_02_input_number_set(v);
    }
    
    void floatnum_02_input_bang_bang() {
        this->floatnum_02_out_set(this->floatnum_02_stored);
    }
    
    void gate_02_out1_bang_bang() {
        this->floatnum_02_input_bang_bang();
    }
    
    void gate_02_input_bang_bang() {
        if (this->gate_02_onoff == 1)
            this->gate_02_out1_bang_bang();
    }
    
    void select_04_match1_bang() {
        this->gate_02_input_bang_bang();
    }
    
    void select_04_nomatch_number_set(number ) {}
    
    void select_04_input_number_set(number v) {
        if (v == this->select_04_test1)
            this->select_04_match1_bang();
        else
            this->select_04_nomatch_number_set(v);
    }
    
    void expr_10_out1_set(number v) {
        this->expr_10_out1 = v;
        this->select_04_input_number_set(this->expr_10_out1);
    }
    
    void expr_10_in1_set(number in1) {
        this->expr_10_in1 = in1;
        this->expr_10_out1_set(this->expr_10_in1 >= this->expr_10_in2);//#map:p_obj-8/>=_obj-8:1
    }
    
    void select_03_match1_bang() {}
    
    void floatnum_02_value_set(number v) {
        this->floatnum_02_value = v;
        this->floatnum_02_stored = v;
    }
    
    void select_03_nomatch_number_set(number v) {
        this->floatnum_02_value_set(v);
    }
    
    void select_03_input_number_set(number v) {
        if (v == this->select_03_test1)
            this->select_03_match1_bang();
        else
            this->select_03_nomatch_number_set(v);
    }
    
    void fzero_02_perform(const SampleValue * input, Index n) {
        auto __fzero_02_periodCount = this->fzero_02_periodCount;
        auto __fzero_02_offset = this->fzero_02_offset;
    
        for (Index i = 0; i < n; i++) {
            this->fzero_02_wavelets[0][__fzero_02_offset] = input[(Index)i];
            __fzero_02_offset++;
            __fzero_02_offset = (BinOpInt)(__fzero_02_offset & (BinOpInt)(4096 - 1));
        }
    
        __fzero_02_periodCount = __fzero_02_periodCount + (long)(this->vectorsize());
    
        if (__fzero_02_periodCount >= 256) {
            __fzero_02_periodCount = 0;
            array<number, 4> result = this->fzero_02_doAnalysis(__fzero_02_offset);
    
            if (result[2] > -1) {
                {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        555692221,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;
                }
            }
    
            if (result[1] > -1) this->getEngine()->scheduleClockEventWithValue(
                this,
                1793217402,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                result[1]
            );;
    
            if (result[0] > -1) this->getEngine()->scheduleClockEventWithValue(
                this,
                388042711,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                result[0]
            );;
        }
    
        this->fzero_02_offset = __fzero_02_offset;
        this->fzero_02_periodCount = __fzero_02_periodCount;
    }
    
    void signaladder_08_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signalreceive_05_perform(const SampleValue * receive, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = receive[(Index)i];
        }
    }
    
    void dspexpr_06_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void p_04_perform(const SampleValue * in1, SampleValue * out1, Index n) {
        ConstSampleArray<1> ins = {in1};
        SampleArray<1> outs = {out1};
        this->p_04->process(ins, 1, outs, 1, n);
    }
    
    void cycle_tilde_02_perform(
        const Sample * frequency,
        number phase_offset,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        RNBO_UNUSED(phase_offset);
        auto __cycle_tilde_02_f2i = this->cycle_tilde_02_f2i;
        auto __cycle_tilde_02_buffer = this->cycle_tilde_02_buffer;
        auto __cycle_tilde_02_phasei = this->cycle_tilde_02_phasei;
        Index i;
    
        for (i = 0; i < n; i++) {
            {
                uint32_t uint_phase;
    
                {
                    {
                        uint_phase = __cycle_tilde_02_phasei;
                    }
                }
    
                uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
                number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                number y0 = __cycle_tilde_02_buffer[(Index)idx];
                number y1 = __cycle_tilde_02_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                number y = y0 + frac * (y1 - y0);
    
                {
                    uint32_t pincr = (uint32_t)(uint32_trunc(frequency[(Index)i] * __cycle_tilde_02_f2i));
                    __cycle_tilde_02_phasei = uint32_add(__cycle_tilde_02_phasei, pincr);
                }
    
                out1[(Index)i] = y;
                out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                continue;
            }
        }
    
        this->cycle_tilde_02_phasei = __cycle_tilde_02_phasei;
    }
    
    void dspexpr_07_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_abs(in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void selector_05_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void gen_06_perform(
        const Sample * in1,
        const Sample * in2,
        number diodeCurve,
        number diodeThresh,
        SampleValue * out1,
        Index n
    ) {
        RNBO_UNUSED(diodeThresh);
        RNBO_UNUSED(diodeCurve);
        Index i;
    
        for (i = 0; i < n; i++) {
            number ringround_0 = 0;
    
            {
                auto thresh_4 = 0.5;
                auto curve_3 = 0.5;
                auto carrier_2 = in2[(Index)i];
                auto input_1 = in1[(Index)i];
                number fdiode_5 = 0;
    
                {
                    auto thresh_8 = thresh_4;
                    auto curve_7 = curve_3;
                    auto x_6 = input_1 + carrier_2;
                    fdiode_5 = this->maximum(0, x_6 + thresh_8) * (1 - rnbo_exp(-curve_7 * this->maximum(0, x_6 + thresh_8)));
                }
    
                number d1_9 = fdiode_5;
                number fdiode_10 = 0;
    
                {
                    auto thresh_13 = thresh_4;
                    auto curve_12 = curve_3;
                    auto x_11 = input_1 - carrier_2;
                    fdiode_10 = this->maximum(0, x_11 + thresh_13) * (1 - rnbo_exp(-curve_12 * this->maximum(0, x_11 + thresh_13)));
                }
    
                number d2_14 = fdiode_10;
                number fdiode_15 = 0;
    
                {
                    auto thresh_18 = thresh_4;
                    auto curve_17 = curve_3;
                    auto x_16 = -input_1 + carrier_2;
                    fdiode_15 = this->maximum(0, x_16 + thresh_18) * (1 - rnbo_exp(-curve_17 * this->maximum(0, x_16 + thresh_18)));
                }
    
                number d3_19 = fdiode_15;
                number fdiode_20 = 0;
    
                {
                    auto thresh_23 = thresh_4;
                    auto curve_22 = curve_3;
                    auto x_21 = -input_1 - carrier_2;
                    fdiode_20 = this->maximum(0, x_21 + thresh_23) * (1 - rnbo_exp(-curve_22 * this->maximum(0, x_21 + thresh_23)));
                }
    
                number d4_24 = fdiode_20;
                ringround_0 = (d1_9 - d2_14 + d3_19 - d4_24) * 0.25;
            }
    
            number expr_1_25 = ringround_0;
            number fixdenorm_2_26 = fixdenorm(expr_1_25);
            out1[(Index)i] = fixdenorm_2_26;
        }
    }
    
    void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void numberobj_03_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_03_value = localvalue;
    }
    
    void numberobj_04_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_04_value = localvalue;
    }
    
    void param_14_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_14_value;
    }
    
    void param_14_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_14_value_set(preset["value"]);
    }
    
    void param_15_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_15_value;
    }
    
    void param_15_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_15_value_set(preset["value"]);
    }
    
    number cycle_tilde_02_ph_next(number freq, number reset) {
        {
            {
                if (reset >= 0.)
                    this->cycle_tilde_02_ph_currentPhase = reset;
            }
        }
    
        number pincr = freq * this->cycle_tilde_02_ph_conv;
    
        if (this->cycle_tilde_02_ph_currentPhase < 0.)
            this->cycle_tilde_02_ph_currentPhase = 1. + this->cycle_tilde_02_ph_currentPhase;
    
        if (this->cycle_tilde_02_ph_currentPhase > 1.)
            this->cycle_tilde_02_ph_currentPhase = this->cycle_tilde_02_ph_currentPhase - 1.;
    
        number tmp = this->cycle_tilde_02_ph_currentPhase;
        this->cycle_tilde_02_ph_currentPhase += pincr;
        return tmp;
    }
    
    void cycle_tilde_02_ph_reset() {
        this->cycle_tilde_02_ph_currentPhase = 0;
    }
    
    void cycle_tilde_02_ph_dspsetup() {
        this->cycle_tilde_02_ph_conv = (number)1 / this->sr;
    }
    
    void cycle_tilde_02_dspsetup(bool force) {
        if ((bool)(this->cycle_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->cycle_tilde_02_phasei = 0;
        this->cycle_tilde_02_f2i = (number)4294967296 / this->samplerate();
        this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
        this->cycle_tilde_02_setupDone = true;
        this->cycle_tilde_02_ph_dspsetup();
    }
    
    void cycle_tilde_02_bufferUpdated() {
        this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
    }
    
    void param_16_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_16_value;
    }
    
    void param_16_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_16_value_set(preset["value"]);
    }
    
    void param_17_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_17_value;
    }
    
    void param_17_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_17_value_set(preset["value"]);
    }
    
    void ip_04_init() {
        this->ip_04_lastValue = this->ip_04_value;
    }
    
    void ip_04_fillSigBuf() {
        if ((bool)(this->ip_04_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_04_lastIndex); i < k; i++) {
                if (this->ip_04_resetCount > 0) {
                    this->ip_04_sigbuf[(Index)i] = 1;
                    this->ip_04_resetCount--;
                } else {
                    this->ip_04_sigbuf[(Index)i] = this->ip_04_lastValue;
                }
            }
    
            this->ip_04_lastIndex = k;
        }
    }
    
    void ip_04_dspsetup(bool force) {
        if ((bool)(this->ip_04_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_04_lastIndex = 0;
        this->ip_04_setupDone = true;
    }
    
    void numberobj_03_init() {
        this->numberobj_03_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("p_obj-8/number_obj-30"), 1, this->_currentTime);
    }
    
    void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_03_value;
    }
    
    void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_03_value_set(preset["value"]);
    }
    
    void param_18_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_18_value;
    }
    
    void param_18_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_18_value_set(preset["value"]);
    }
    
    void ip_05_init() {
        this->ip_05_lastValue = this->ip_05_value;
    }
    
    void ip_05_fillSigBuf() {
        if ((bool)(this->ip_05_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_05_lastIndex); i < k; i++) {
                if (this->ip_05_resetCount > 0) {
                    this->ip_05_sigbuf[(Index)i] = 1;
                    this->ip_05_resetCount--;
                } else {
                    this->ip_05_sigbuf[(Index)i] = this->ip_05_lastValue;
                }
            }
    
            this->ip_05_lastIndex = k;
        }
    }
    
    void ip_05_dspsetup(bool force) {
        if ((bool)(this->ip_05_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_05_lastIndex = 0;
        this->ip_05_setupDone = true;
    }
    
    void numberobj_04_init() {
        this->numberobj_04_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("p_obj-8/number_obj-62"), 1, this->_currentTime);
    }
    
    void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_04_value;
    }
    
    void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_04_value_set(preset["value"]);
    }
    
    void param_19_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_19_value;
    }
    
    void param_19_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_19_value_set(preset["value"]);
    }
    
    void param_20_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_20_value;
    }
    
    void param_20_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_20_value_set(preset["value"]);
    }
    
    void param_21_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_21_value;
    }
    
    void param_21_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_21_value_set(preset["value"]);
    }
    
    void ip_06_init() {
        this->ip_06_lastValue = this->ip_06_value;
    }
    
    void ip_06_fillSigBuf() {
        if ((bool)(this->ip_06_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_06_lastIndex); i < k; i++) {
                if (this->ip_06_resetCount > 0) {
                    this->ip_06_sigbuf[(Index)i] = 1;
                    this->ip_06_resetCount--;
                } else {
                    this->ip_06_sigbuf[(Index)i] = this->ip_06_lastValue;
                }
            }
    
            this->ip_06_lastIndex = k;
        }
    }
    
    void ip_06_dspsetup(bool force) {
        if ((bool)(this->ip_06_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_06_lastIndex = 0;
        this->ip_06_setupDone = true;
    }
    
    void fzero_02_init() {
        this->fzero_02_onsetPitchCents = 0.8 * 100;
    }
    
    number fzero_02_fzero_ac(int level) {
        int tau = 0;
        int period;
        number tmp2 = 0.;
        number threshold = 0.1;
        number acData[128] = FIXEDSIZEARRAYINIT(128);
    
        for (tau = 1; tau < 128; tau++) {
            acData[(Index)tau] = 0.;
    
            for (int k = 0; k < 128; k++) {
                number tmp = this->fzero_02_wavelets[(Index)level][(Index)k] - this->fzero_02_wavelets[(Index)level][(Index)(k + tau)];
                acData[(Index)tau] += tmp * tmp;
            }
    
            tmp2 += acData[(Index)tau];
            acData[(Index)tau] *= tau / tmp2;
            period = tau - 3;
    
            if (tau > 4 && acData[(Index)period] < threshold && acData[(Index)period] < acData[(Index)(period + 1)]) {
                break;
            }
        }
    
        if (tau < 128 - 1) {
            int tmpMin = (int)(tau - 3);
            number interpMin = tmpMin - 0.5 * ((acData[(Index)tmpMin] - acData[(Index)(tmpMin + 1)] - (acData[(Index)tmpMin] - acData[(Index)(tmpMin - 1)])) / (acData[(Index)tmpMin] - acData[(Index)(tmpMin + 1)] + (acData[(Index)tmpMin] - acData[(Index)(tmpMin - 1)])));
    
            number autoPitch = ((BinOpInt)((BinOpInt)this->samplerate() >> imod_nocast(
                (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)level, 32), 32),
                32
            ))) / interpMin;
    
            return autoPitch;
        } else {
            return 0;
        }
    }
    
    long fzero_02_toCents(number f1, number f2) {
        if (f2 > 0) {
            return (long)(rnbo_floor(1200 * rnbo_fabs(rnbo_log2(f1 / f2)) + 0.5));
        } else {
            return 99999;
        }
    }
    
    array<number, 4> fzero_02_doAnalysis(number currentEnd) {
        long oldMode = 0;
        number maxThresh = 0.;
        number minThresh = 0.;
        number outPeak = 0.;
        Int maxCount[5] = FIXEDSIZEARRAYINIT(5);
        Int minCount[5] = FIXEDSIZEARRAYINIT(5);
        Int maxIndices[5][256] = FIXEDSIZEARRAYINIT(5, 256);
        Int minIndices[5][256] = FIXEDSIZEARRAYINIT(5, 256);
        number vecMin = 999999;
        number vecMax = -999999;
        number vecMean = 0;
        number vecSum = 0;
        auto samplerate = this->samplerate();
        array<number, 4> result = {-1, -1, -1, -1};
    
        if ((bool)(this->fzero_02_oldFreq)) {
            oldMode = trunc(samplerate / this->fzero_02_oldFreq);
        }
    
        this->fzero_02_freq = 0.;
        this->fzero_02_onsetReady -= 256;
        int currentStart = (int)((BinOpInt)((BinOpInt)(currentEnd - 2048) & (BinOpInt)(4096 - 1)));
    
        for (int i = 0; i < 2048; i++) {
            int readout = (int)((BinOpInt)((BinOpInt)(currentStart + i) & (BinOpInt)(4096 - 1)));
    
            if (this->fzero_02_wavelets[0][(Index)readout] > vecMax) {
                vecMax = this->fzero_02_wavelets[0][(Index)readout];
            } else if (this->fzero_02_wavelets[0][(Index)readout] < vecMin) {
                vecMin = this->fzero_02_wavelets[0][(Index)readout];
            }
    
            vecSum = vecSum + this->fzero_02_wavelets[0][(Index)readout];
        }
    
        vecMean = vecSum / (number)2048;
        minThresh = .75 * (vecMin - vecMean) + vecMean;
        maxThresh = .75 * (vecMax - vecMean) + vecMean;
        outPeak = vecMax;
    
        if (rnbo_fabs(vecMin) > vecMax) {
            outPeak = rnbo_fabs(vecMin);
        }
    
        if (outPeak > 9999) {
            outPeak = 0.;
        }
    
        if (outPeak > this->fzero_02_noisethresh) {
            float mode[5] = FIXEDSIZEARRAYINIT(5);
    
            for (int currentLevel = 1; currentLevel < 5; currentLevel++) {
                int peakLimit = 16;
    
                int levelBufSize = (int)((BinOpInt)((BinOpInt)2048 >> imod_nocast((UBinOpInt)imod_nocast(
                    (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)currentLevel, 32), 32),
                    32
                ), 32)));
    
                number lastLevelStartPoint = (currentLevel == 1 ? currentStart : 0);
    
                for (int k = 0; k < levelBufSize; k++) {
                    int sampleIndex1 = (int)((BinOpInt)((BinOpInt)(lastLevelStartPoint + k * 2) & (BinOpInt)(4096 - 1)));
                    int sampleIndex2 = (int)((BinOpInt)((BinOpInt)(lastLevelStartPoint + k * 2 + 1) & (BinOpInt)(4096 - 1)));
                    number lastLevel = currentLevel - 1;
                    this->fzero_02_wavelets[(Index)currentLevel][(Index)k] = (this->fzero_02_wavelets[(Index)lastLevel][(Index)sampleIndex1] + this->fzero_02_wavelets[(Index)lastLevel][(Index)sampleIndex2]) * 0.5;
                }
    
                if (currentLevel == 1) {
                    number autoPitch = this->fzero_02_fzero_ac((int)(currentLevel));
    
                    if (autoPitch >= 20 && autoPitch <= 2500) {
                        this->fzero_02_freq = autoPitch;
                        break;
                    }
                }
    
                int minDist = (int)((BinOpInt)((BinOpInt)(samplerate / (number)2500) >> imod_nocast(
                    (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)currentLevel, 32), 32),
                    32
                )));
    
                minDist = (minDist > 1 ? 1 : minDist);
                maxCount[(Index)currentLevel] = 0;
                minCount[(Index)currentLevel] = 0;
                int direction = 0;
                int extreme = 1;
                int tooClose = 0;
    
                if (this->fzero_02_wavelets[(Index)currentLevel][(Index)(levelBufSize - 1)] - this->fzero_02_wavelets[(Index)currentLevel][(Index)(levelBufSize - 2)] > 0) {
                    direction = 1;
                } else {
                    direction = -1;
                }
    
                for (int k = (int)(levelBufSize - 1); k >= 1; k--) {
                    number test = this->fzero_02_wavelets[(Index)currentLevel][(Index)(k - 1)] - this->fzero_02_wavelets[(Index)currentLevel][(Index)k];
    
                    if (direction >= 0 && test < 0.0) {
                        direction = -1;
    
                        if (this->fzero_02_wavelets[(Index)currentLevel][(Index)k] >= maxThresh && (bool)(extreme) && (bool)(!(bool)(tooClose))) {
                            maxCount[(Index)currentLevel]++;
                            maxIndices[(Index)currentLevel][(Index)maxCount[(Index)currentLevel]] = k;
                            extreme = 0;
                            tooClose = minDist;
                        }
                    } else if (direction <= 0 && test > 0.0) {
                        direction = 1;
    
                        if (this->fzero_02_wavelets[(Index)currentLevel][(Index)k] <= minThresh && (bool)(extreme) && (bool)(!(bool)(tooClose))) {
                            minCount[(Index)currentLevel]++;
                            minIndices[(Index)currentLevel][(Index)minCount[(Index)currentLevel]] = k;
                            extreme = 0;
                            tooClose = minDist;
                        }
                    }
    
                    if (maxCount[(Index)currentLevel] >= peakLimit || minCount[(Index)currentLevel] >= peakLimit) {
                        k = 0;
                    }
    
                    if ((bool)(!(bool)(extreme))) {
                        if ((direction > 0 && this->fzero_02_wavelets[(Index)currentLevel][(Index)k] >= vecMean) || (direction < 0 && this->fzero_02_wavelets[(Index)currentLevel][(Index)k] <= vecMean)) {
                            extreme = 1;
                        }
                    }
    
                    if ((bool)(tooClose)) {
                        tooClose--;
                    }
                }
    
                if (maxCount[(Index)currentLevel] >= 2 && minCount[(Index)currentLevel] >= 2) {
                    int diffLevs = 3;
                    int dCount = 0;
                    int numer;
                    Int differs[1024] = FIXEDSIZEARRAYINIT(1024);
    
                    for (int j = 1; j <= diffLevs; j++) {
                        for (int k = 1; k <= maxCount[(Index)currentLevel] - j; k++) {
                            differs[(Index)dCount] = maxIndices[(Index)currentLevel][(Index)k] - maxIndices[(Index)currentLevel][(Index)(k + j)];
                            dCount++;
                        }
    
                        for (int k = 1; k <= minCount[(Index)currentLevel] - j; k++) {
                            differs[(Index)dCount] = minIndices[(Index)currentLevel][(Index)k] - minIndices[(Index)currentLevel][(Index)(k + j)];
                            dCount++;
                        }
                    }
    
                    numer = 1;
                    mode[(Index)currentLevel] = 0;
                    mode[0] = 0;
    
                    for (int j = 0; j < dCount; j++) {
                        int numerJ = 0;
    
                        for (int k = 0; k < dCount; k++) {
                            numerJ += rnbo_abs(differs[(Index)k] - differs[(Index)j]) <= minDist;
                        }
    
                        if (numerJ >= numer && numerJ > rnbo_floor(levelBufSize / differs[(Index)j]) / (number)4) {
                            if (numerJ == numer) {
                                if ((bool)(oldMode) && rnbo_abs(differs[(Index)j] - ((BinOpInt)((BinOpInt)oldMode >> imod_nocast(
                                    (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)currentLevel, 32), 32),
                                    32
                                )))) < minDist)
                                    mode[(Index)currentLevel] = differs[(Index)j];
                                else if ((bool)(!(bool)(oldMode)) && (differs[(Index)j] > 1.95 * mode[(Index)currentLevel] && differs[(Index)j] < 2.05 * mode[(Index)currentLevel]))
                                    mode[(Index)currentLevel] = differs[(Index)j];
                            } else {
                                numer = numerJ;
                                mode[(Index)currentLevel] = differs[(Index)j];
                            }
                        } else if (numerJ == numer - 1 && (bool)(oldMode) && (bool)(rnbo_abs(differs[(Index)j] - ((BinOpInt)((BinOpInt)oldMode >> imod_nocast(
                            (UBinOpInt)imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)currentLevel, 32), 32),
                            32
                        ))) < minDist)))
                            mode[(Index)currentLevel] = differs[(Index)j];
                    }
    
                    if ((bool)(mode[(Index)currentLevel])) {
                        float sumOfDiffers = 0;
                        int numberOfDiffers = 0;
    
                        for (int j = 1; j <= dCount; j++) {
                            if (rnbo_fabs(mode[(Index)currentLevel] - differs[(Index)j]) <= minDist) {
                                sumOfDiffers += differs[(Index)j];
                                numberOfDiffers++;
                            }
                        }
    
                        mode[(Index)currentLevel] = sumOfDiffers / numberOfDiffers;
                    }
    
                    if ((bool)(mode[(Index)(currentLevel - 1)]) && maxCount[(Index)(currentLevel - 1)] >= 2 && minCount[(Index)(currentLevel - 1)] >= 2) {
                        if (rnbo_fabs(mode[(Index)(currentLevel - 1)] - 2 * mode[(Index)currentLevel]) <= minDist) {
                            this->fzero_02_freq = samplerate / mode[(Index)(currentLevel - 1)] / rnbo_pow(2, currentLevel - 1);
                        } else {
                            this->fzero_02_freq = 0;
                        }
                    }
                }
            }
    
            if (this->fzero_02_onsetReady < 0) {
                if (this->fzero_02_freq >= 20 && this->fzero_02_freq <= 2500) {
                    if (outPeak - this->fzero_02_oldPeak > 0.1 || this->fzero_02_toCents(this->fzero_02_freq, this->fzero_02_onsetFreq) > this->fzero_02_onsetPitchCents) {
                        result[2] = this->fzero_02_freq;
                        result[3] = outPeak;
                        this->fzero_02_oldPeak = outPeak;
                        this->fzero_02_onsetFreq = this->fzero_02_freq;
                        this->fzero_02_onsetReady = 1024;
                    }
                }
            }
    
            result[1] = outPeak;
    
            if (this->fzero_02_freq >= 20) {
                result[0] = this->fzero_02_freq;
            } else if (this->fzero_02_freq > 0) {
                console->log("fzero: Estimated f0 is lower than freqMin.");
            }
        } else {
            oldMode = 0;
            this->fzero_02_oldPeak = 0;
            outPeak = 0;
            result[1] = 0;
            result[0] = 0;
        }
    
        this->fzero_02_oldFreq = this->fzero_02_freq;
        return result;
    }
    
    void fzero_02_dspsetup(bool force) {
        if ((bool)(this->fzero_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->fzero_02_offset = 0;
        this->fzero_02_setupDone = true;
    }
    
    void param_22_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_22_value;
    }
    
    void param_22_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_22_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        param_14_value = 0.1;
        mstosamps_03_ms = 0;
        p_03_target = 0;
        dspexpr_05_in1 = 0;
        dspexpr_05_in2 = 0;
        gen_06_in1 = 0;
        gen_06_in2 = 0;
        gen_06_diodeCurve = 0.5;
        gen_06_diodeThresh = 0.5;
        p_04_target = 0;
        expr_06_in1 = 0;
        expr_06_in2 = 1;
        expr_06_out1 = 0;
        param_15_value = 0;
        selector_04_onoff = 1;
        dspexpr_06_in1 = 0;
        dspexpr_06_in2 = 1;
        cycle_tilde_02_frequency = 1;
        cycle_tilde_02_phase_offset = 0;
        selector_05_onoff = 1;
        param_16_value = 1;
        mstosamps_04_ms = 0;
        param_17_value = 1;
        ip_04_value = 0;
        ip_04_impulse = 0;
        numberobj_03_value = 0;
        numberobj_03_value_setter(numberobj_03_value);
        dspexpr_07_in1 = 0;
        expr_07_in1 = 0;
        expr_07_in2 = 1;
        expr_07_out1 = 0;
        param_18_value = 0;
        receive_02_output_number = 0;
        ip_05_value = 0;
        ip_05_impulse = 0;
        numberobj_04_value = 0;
        numberobj_04_value_setter(numberobj_04_value);
        param_19_value = 0;
        selector_06_onoff = 1;
        expr_08_in1 = 0;
        expr_08_in2 = 1;
        expr_08_out1 = 0;
        send_02_input_number = 0;
        expr_09_in1 = 0;
        expr_09_out1 = 0;
        param_20_value = 0;
        gate_02_onoff = 0;
        gate_02_out1_number = 0;
        floatnum_02_input_number = 0;
        floatnum_02_value = 0;
        param_21_value = 1;
        ip_06_value = 1;
        ip_06_impulse = 0;
        dspexpr_08_in1 = 0;
        dspexpr_08_in2 = 1;
        select_03_test1 = 0;
        fzero_02_noisethresh = 0.1;
        select_04_test1 = 1;
        expr_10_in1 = 0;
        expr_10_in2 = 0;
        expr_10_out1 = 0;
        param_22_value = 0.1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        signals[6] = nullptr;
        signals[7] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        param_14_lastValue = 0;
        param_15_lastValue = 0;
        cycle_tilde_02_wrap = 0;
        cycle_tilde_02_ph_currentPhase = 0;
        cycle_tilde_02_ph_conv = 0;
        cycle_tilde_02_setupDone = false;
        param_16_lastValue = 0;
        param_17_lastValue = 0;
        ip_04_lastIndex = 0;
        ip_04_lastValue = 0;
        ip_04_resetCount = 0;
        ip_04_sigbuf = nullptr;
        ip_04_setupDone = false;
        numberobj_03_currentFormat = 6;
        numberobj_03_lastValue = 0;
        param_18_lastValue = 0;
        ip_05_lastIndex = 0;
        ip_05_lastValue = 0;
        ip_05_resetCount = 0;
        ip_05_sigbuf = nullptr;
        ip_05_setupDone = false;
        numberobj_04_currentFormat = 6;
        numberobj_04_lastValue = 0;
        param_19_lastValue = 0;
        param_20_lastValue = 0;
        floatnum_02_stored = 0;
        param_21_lastValue = 0;
        ip_06_lastIndex = 0;
        ip_06_lastValue = 0;
        ip_06_resetCount = 0;
        ip_06_sigbuf = nullptr;
        ip_06_setupDone = false;
        fzero_02_offset = 0;
        fzero_02_periodCount = 0;
        fzero_02_freq = 0;
        fzero_02_oldFreq = 0;
        fzero_02_oldPeak = 0;
        fzero_02_onsetReady = 0;
        fzero_02_onsetPitchCents = 80;
        fzero_02_onsetFreq = 0;
        fzero_02_setupDone = false;
        param_22_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number param_14_value;
        number mstosamps_03_ms;
        number p_03_target;
        number dspexpr_05_in1;
        number dspexpr_05_in2;
        number gen_06_in1;
        number gen_06_in2;
        number gen_06_diodeCurve;
        number gen_06_diodeThresh;
        number p_04_target;
        number expr_06_in1;
        number expr_06_in2;
        number expr_06_out1;
        number param_15_value;
        number selector_04_onoff;
        number dspexpr_06_in1;
        number dspexpr_06_in2;
        number cycle_tilde_02_frequency;
        number cycle_tilde_02_phase_offset;
        number selector_05_onoff;
        number param_16_value;
        number mstosamps_04_ms;
        number param_17_value;
        number ip_04_value;
        number ip_04_impulse;
        number numberobj_03_value;
        number dspexpr_07_in1;
        number expr_07_in1;
        number expr_07_in2;
        number expr_07_out1;
        number param_18_value;
        number receive_02_output_number;
        list receive_02_output_list;
        number ip_05_value;
        number ip_05_impulse;
        number numberobj_04_value;
        number param_19_value;
        number selector_06_onoff;
        number expr_08_in1;
        number expr_08_in2;
        number expr_08_out1;
        number send_02_input_number;
        list send_02_input_list;
        number expr_09_in1;
        number expr_09_out1;
        number param_20_value;
        number gate_02_onoff;
        number gate_02_out1_number;
        list gate_02_out1_list;
        number floatnum_02_input_number;
        number floatnum_02_value;
        number param_21_value;
        number ip_06_value;
        number ip_06_impulse;
        number dspexpr_08_in1;
        number dspexpr_08_in2;
        number select_03_test1;
        number fzero_02_noisethresh;
        number select_04_test1;
        number expr_10_in1;
        number expr_10_in2;
        number expr_10_out1;
        number param_22_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[8];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number param_14_lastValue;
        number param_15_lastValue;
        Float64BufferRef cycle_tilde_02_buffer;
        long cycle_tilde_02_wrap;
        uint32_t cycle_tilde_02_phasei;
        SampleValue cycle_tilde_02_f2i;
        number cycle_tilde_02_ph_currentPhase;
        number cycle_tilde_02_ph_conv;
        bool cycle_tilde_02_setupDone;
        number param_16_lastValue;
        number param_17_lastValue;
        SampleIndex ip_04_lastIndex;
        number ip_04_lastValue;
        SampleIndex ip_04_resetCount;
        signal ip_04_sigbuf;
        bool ip_04_setupDone;
        Int numberobj_03_currentFormat;
        number numberobj_03_lastValue;
        number param_18_lastValue;
        SampleIndex ip_05_lastIndex;
        number ip_05_lastValue;
        SampleIndex ip_05_resetCount;
        signal ip_05_sigbuf;
        bool ip_05_setupDone;
        Int numberobj_04_currentFormat;
        number numberobj_04_lastValue;
        number param_19_lastValue;
        number param_20_lastValue;
        number floatnum_02_stored;
        number param_21_lastValue;
        SampleIndex ip_06_lastIndex;
        number ip_06_lastValue;
        SampleIndex ip_06_resetCount;
        signal ip_06_sigbuf;
        bool ip_06_setupDone;
        long fzero_02_offset;
        long fzero_02_periodCount;
        number fzero_02_freq;
        number fzero_02_oldFreq;
        number fzero_02_oldPeak;
        number fzero_02_onsetReady;
        number fzero_02_onsetPitchCents;
        number fzero_02_onsetFreq;
        SampleValue fzero_02_wavelets[5][4096] = { };
        bool fzero_02_setupDone;
        number param_22_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_2060* p_03;
        RNBOSubpatcher_2061* p_04;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    delete this->p_05;
    delete this->p_06;
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

inline number safemod(number f, number m) {
    if (m != 0) {
        Int f_trunc = (Int)(trunc(f));
        Int m_trunc = (Int)(trunc(m));

        if (f == f_trunc && m == m_trunc) {
            f = f_trunc % m_trunc;
        } else {
            if (m < 0) {
                m = -m;
            }

            if (f >= m) {
                if (f >= m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f -= m;
                }
            } else if (f <= -m) {
                if (f <= -m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f += m;
                }
            }
        }
    } else {
        f = 0.0;
    }

    return f;
}

inline number safesqrt(number num) {
    return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
}

number samplerate() const {
    return this->sr;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 0;
}

void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->ip_07_perform(this->signals[0], n);
    this->feedbackreader_01_perform(this->signals[1], n);
    this->dspexpr_09_perform(this->signals[1], this->dspexpr_09_in2, this->signals[2], n);
    this->feedbackreader_02_perform(this->signals[1], n);
    this->dspexpr_10_perform(this->signals[1], this->dspexpr_10_in2, this->signals[3], n);
    this->stackprotect_perform(n);
    this->feedbackreader_03_perform(this->signals[1], n);
    this->feedbackreader_04_perform(this->signals[4], n);
    this->feedbackreader_05_perform(this->signals[5], n);
    this->signaladder_01_perform(this->signals[2], in1, this->signals[2], n);

    this->p_05_perform(
        this->signals[1],
        this->signals[5],
        this->signals[2],
        this->signals[6],
        this->signals[7],
        this->signals[8],
        n
    );

    this->feedbackwriter_04_perform(this->signals[6], n);
    this->feedbackwriter_06_perform(this->signals[7], n);
    this->limi_01_perform(this->signals[8], this->signals[7], n);
    this->xfade_tilde_01_perform(this->signals[0], in1, this->signals[7], out1, n);
    this->feedbackwriter_01_perform(this->signals[7], n);
    this->feedbackreader_06_perform(this->signals[7], n);
    this->signaladder_02_perform(this->signals[3], in2, this->signals[3], n);

    this->p_06_perform(
        this->signals[4],
        this->signals[7],
        this->signals[3],
        this->signals[8],
        this->signals[6],
        this->signals[5],
        n
    );

    this->feedbackwriter_03_perform(this->signals[8], n);
    this->feedbackwriter_05_perform(this->signals[6], n);
    this->limi_02_perform(this->signals[5], this->signals[6], n);
    this->xfade_tilde_02_perform(this->signals[0], in2, this->signals[6], out2, n);
    this->feedbackwriter_02_perform(this->signals[6], n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 9; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->ip_07_sigbuf = resizeSignal(this->ip_07_sigbuf, this->maxvs, maxBlockSize);
        this->feedbacktilde_01_feedbackbuffer = resizeSignal(this->feedbacktilde_01_feedbackbuffer, this->maxvs, maxBlockSize);
        this->feedbacktilde_02_feedbackbuffer = resizeSignal(this->feedbacktilde_02_feedbackbuffer, this->maxvs, maxBlockSize);
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->feedbacktilde_03_feedbackbuffer = resizeSignal(this->feedbacktilde_03_feedbackbuffer, this->maxvs, maxBlockSize);
        this->feedbacktilde_04_feedbackbuffer = resizeSignal(this->feedbacktilde_04_feedbackbuffer, this->maxvs, maxBlockSize);
        this->feedbacktilde_05_feedbackbuffer = resizeSignal(this->feedbacktilde_05_feedbackbuffer, this->maxvs, maxBlockSize);
        this->feedbacktilde_06_feedbackbuffer = resizeSignal(this->feedbacktilde_06_feedbackbuffer, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->ip_07_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->limi_01_dspsetup(forceDSPSetup);
    this->limi_02_dspsetup(forceDSPSetup);
    this->p_05->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_06->prepareToProcess(sampleRate, maxBlockSize, force);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 1;
}

void fillRNBODefaultSinus(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 0:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    }
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->p_05->processDataViewUpdate(index, time);
    this->p_06->processDataViewUpdate(index, time);
}

void initialize() {
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultSinus->setIndex(0);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    this->p_05 = new RNBOSubpatcher_2062();
    this->p_05->setEngineAndPatcher(this->getEngine(), this);
    this->p_05->initialize();
    this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));
    this->p_06 = new RNBOSubpatcher_2063();
    this->p_06->setEngineAndPatcher(this->getEngine(), this);
    this->p_06->initialize();
    this->p_06->setParameterOffset(this->getParameterOffset(this->p_06));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_23_getPresetValue(getSubState(preset, "wet"));
    this->param_24_getPresetValue(getSubState(preset, "freq"));
    this->param_25_getPresetValue(getSubState(preset, "ratio"));
    this->param_26_getPresetValue(getSubState(preset, "subharmonic"));
    this->param_27_getPresetValue(getSubState(preset, "feedback"));
    this->param_28_getPresetValue(getSubState(preset, "pitchHold"));
    this->param_29_getPresetValue(getSubState(preset, "pitchThresh"));
    this->param_30_getPresetValue(getSubState(preset, "pitchEnv"));
    this->param_31_getPresetValue(getSubState(preset, "pitchFollow"));
    this->param_32_getPresetValue(getSubState(preset, "ampEnv"));
    this->param_33_getPresetValue(getSubState(preset, "ampMod"));
    this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "p_obj-3"));
    this->p_06->getPreset(getSubState(getSubState(preset, "__sps"), "p_obj-8"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_23_setPresetValue(getSubState(preset, "wet"));
    this->param_24_setPresetValue(getSubState(preset, "freq"));
    this->param_25_setPresetValue(getSubState(preset, "ratio"));
    this->param_26_setPresetValue(getSubState(preset, "subharmonic"));
    this->param_27_setPresetValue(getSubState(preset, "feedback"));
    this->param_28_setPresetValue(getSubState(preset, "pitchHold"));
    this->param_29_setPresetValue(getSubState(preset, "pitchThresh"));
    this->param_30_setPresetValue(getSubState(preset, "pitchEnv"));
    this->param_31_setPresetValue(getSubState(preset, "pitchFollow"));
    this->param_32_setPresetValue(getSubState(preset, "ampEnv"));
    this->param_33_setPresetValue(getSubState(preset, "ampMod"));

    this->p_05->param_03_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "ampEnv")
    );

    this->p_05->param_04_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "pitchFollow")
    );

    this->p_05->param_05_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "pitchGlide")
    );

    this->p_05->param_06_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "freq"));

    this->p_05->param_07_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "ampMod")
    );

    this->p_05->param_08_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "subharmonic")
    );

    this->p_05->param_09_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "pitchHold")
    );

    this->p_05->param_10_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "ratio"));

    this->p_05->param_11_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "pitchThresh")
    );

    this->p_05->p_01->param_01_setPresetValue(
        getSubState(getSubState(getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "__sps"), "env.follower[1]"), "rampsamples")
    );

    this->p_05->p_02->param_02_setPresetValue(
        getSubState(getSubState(getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-3"), "__sps"), "env.follower"), "rampsamples")
    );

    this->p_06->param_14_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "ampEnv")
    );

    this->p_06->param_15_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "pitchFollow")
    );

    this->p_06->param_16_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "pitchGlide")
    );

    this->p_06->param_17_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "freq"));

    this->p_06->param_18_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "ampMod")
    );

    this->p_06->param_19_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "subharmonic")
    );

    this->p_06->param_20_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "pitchHold")
    );

    this->p_06->param_21_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "ratio"));

    this->p_06->param_22_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "pitchThresh")
    );

    this->p_06->p_03->param_12_setPresetValue(
        getSubState(getSubState(getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "__sps"), "env.follower[1]"), "rampsamples")
    );

    this->p_06->p_04->param_13_setPresetValue(
        getSubState(getSubState(getSubState(getSubState(getSubState(preset, "__sps"), "p_obj-8"), "__sps"), "env.follower"), "rampsamples")
    );
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_23_value_set(v);
        break;
        }
    case 1:
        {
        this->param_24_value_set(v);
        break;
        }
    case 2:
        {
        this->param_25_value_set(v);
        break;
        }
    case 3:
        {
        this->param_26_value_set(v);
        break;
        }
    case 4:
        {
        this->param_27_value_set(v);
        break;
        }
    case 5:
        {
        this->param_28_value_set(v);
        break;
        }
    case 6:
        {
        this->param_29_value_set(v);
        break;
        }
    case 7:
        {
        this->param_30_value_set(v);
        break;
        }
    case 8:
        {
        this->param_31_value_set(v);
        break;
        }
    case 9:
        {
        this->param_32_value_set(v);
        break;
        }
    case 10:
        {
        this->param_33_value_set(v);
        break;
        }
    default:
        {
        index -= 11;

        if (index < this->p_05->getNumParameters())
            this->p_05->setParameterValue(index, v, time);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            this->p_06->setParameterValue(index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_23_value;
        }
    case 1:
        {
        return this->param_24_value;
        }
    case 2:
        {
        return this->param_25_value;
        }
    case 3:
        {
        return this->param_26_value;
        }
    case 4:
        {
        return this->param_27_value;
        }
    case 5:
        {
        return this->param_28_value;
        }
    case 6:
        {
        return this->param_29_value;
        }
    case 7:
        {
        return this->param_30_value;
        }
    case 8:
        {
        return this->param_31_value;
        }
    case 9:
        {
        return this->param_32_value;
        }
    case 10:
        {
        return this->param_33_value;
        }
    default:
        {
        index -= 11;

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterValue(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterValue(index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 11 + this->p_05->getNumParameters() + this->p_06->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "wet";
        }
    case 1:
        {
        return "freq";
        }
    case 2:
        {
        return "ratio";
        }
    case 3:
        {
        return "subharmonic";
        }
    case 4:
        {
        return "feedback";
        }
    case 5:
        {
        return "pitchHold";
        }
    case 6:
        {
        return "pitchThresh";
        }
    case 7:
        {
        return "pitchEnv";
        }
    case 8:
        {
        return "pitchFollow";
        }
    case 9:
        {
        return "ampEnv";
        }
    case 10:
        {
        return "ampMod";
        }
    default:
        {
        index -= 11;

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterName(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "wet";
        }
    case 1:
        {
        return "freq";
        }
    case 2:
        {
        return "ratio";
        }
    case 3:
        {
        return "subharmonic";
        }
    case 4:
        {
        return "feedback";
        }
    case 5:
        {
        return "pitchHold";
        }
    case 6:
        {
        return "pitchThresh";
        }
    case 7:
        {
        return "pitchEnv";
        }
    case 8:
        {
        return "pitchFollow";
        }
    case 9:
        {
        return "ampEnv";
        }
    case 10:
        {
        return "ampMod";
        }
    default:
        {
        index -= 11;

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterId(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterId(index);

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = -100;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 1;
            info->max = 32;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal3[] = {"0", "1"};
            info->enumValues = eVal3;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 0.999;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal5[] = {"0", "1"};
            info->enumValues = eVal5;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal8[] = {"0", "1"};
            info->enumValues = eVal8;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.1;
            info->min = 0;
            info->max = 1000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal10[] = {"0", "1"};
            info->enumValues = eVal10;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 11;

            if (index < this->p_05->getNumParameters())
                this->p_05->getParameterInfo(index, info);

            index -= this->p_05->getNumParameters();

            if (index < this->p_06->getNumParameters())
                this->p_06->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_05)
        return 11;

    if (subpatcher == this->p_06)
        return 11 + this->p_05->getNumParameters();

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 3:
    case 5:
    case 8:
    case 10:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 2);
            }

            return normalizedValue;
        }
        }
    case 7:
    case 9:
        {
        {
            value = (value < 0 ? 0 : (value > 1000 ? 1000 : value));
            ParameterValue normalizedValue = (value - 0) / (1000 - 0);
            return normalizedValue;
        }
        }
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 0.999 ? 0.999 : value));
            ParameterValue normalizedValue = (value - 0) / (0.999 - 0);
            return normalizedValue;
        }
        }
    case 2:
        {
        {
            value = (value < 1 ? 1 : (value > 32 ? 32 : value));
            ParameterValue normalizedValue = (value - 1) / (32 - 1);
            return normalizedValue;
        }
        }
    case 1:
        {
        {
            value = (value < -100 ? -100 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - -100) / (100 - -100);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 11;

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertToNormalizedParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 6:
        {
        {
            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 3:
    case 5:
    case 8:
    case 10:
        {
        {
            {
                value = this->applyStepsToNormalizedParameterValue(value, 2);
            }

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 7:
    case 9:
        {
        {
            {
                return 0 + value * (1000 - 0);
            }
        }
        }
    case 4:
        {
        {
            {
                return 0 + value * (0.999 - 0);
            }
        }
        }
    case 2:
        {
        {
            {
                return 1 + value * (32 - 1);
            }
        }
        }
    case 1:
        {
        {
            {
                return -100 + value * (100 - -100);
            }
        }
        }
    default:
        {
        index -= 11;

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertFromNormalizedParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->convertFromNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_23_value_constrain(value);
        }
    case 1:
        {
        return this->param_24_value_constrain(value);
        }
    case 2:
        {
        return this->param_25_value_constrain(value);
        }
    case 3:
        {
        return this->param_26_value_constrain(value);
        }
    case 4:
        {
        return this->param_27_value_constrain(value);
        }
    case 5:
        {
        return this->param_28_value_constrain(value);
        }
    case 6:
        {
        return this->param_29_value_constrain(value);
        }
    case 7:
        {
        return this->param_30_value_constrain(value);
        }
    case 8:
        {
        return this->param_31_value_constrain(value);
        }
    case 9:
        {
        return this->param_32_value_constrain(value);
        }
    case 10:
        {
        return this->param_33_value_constrain(value);
        }
    default:
        {
        index -= 11;

        if (index < this->p_05->getNumParameters())
            return this->p_05->constrainParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->constrainParameterValue(index, value);

        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_05->processNumMessage(tag, objectId, time, payload);
    this->p_06->processNumMessage(tag, objectId, time, payload);
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_05->processListMessage(tag, objectId, time, payload);
    this->p_06->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_05->processBangMessage(tag, objectId, time);
    this->p_06->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    auto subpatchResult_0 = this->p_05->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    auto subpatchResult_1 = this->p_06->resolveTag(tag);

    if (subpatchResult_1)
        return subpatchResult_1;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

void param_23_value_set(number v) {
    v = this->param_23_value_constrain(v);
    this->param_23_value = v;
    this->sendParameter(0, false);

    if (this->param_23_value != this->param_23_lastValue) {
        this->getEngine()->presetTouched();
        this->param_23_lastValue = this->param_23_value;
    }

    this->ip_07_value_set(v);
}

void param_24_value_set(number v) {
    v = this->param_24_value_constrain(v);
    this->param_24_value = v;
    this->sendParameter(1, false);

    if (this->param_24_value != this->param_24_lastValue) {
        this->getEngine()->presetTouched();
        this->param_24_lastValue = this->param_24_value;
    }

    this->p_05_freq_set(v);
    this->p_06_freq_set(v);
}

void param_25_value_set(number v) {
    v = this->param_25_value_constrain(v);
    this->param_25_value = v;
    this->sendParameter(2, false);

    if (this->param_25_value != this->param_25_lastValue) {
        this->getEngine()->presetTouched();
        this->param_25_lastValue = this->param_25_value;
    }

    this->p_05_ratio_set(v);
    this->p_06_ratio_set(v);
}

void param_26_value_set(number v) {
    v = this->param_26_value_constrain(v);
    this->param_26_value = v;
    this->sendParameter(3, false);

    if (this->param_26_value != this->param_26_lastValue) {
        this->getEngine()->presetTouched();
        this->param_26_lastValue = this->param_26_value;
    }

    this->p_05_subharmonic_set(v);
    this->p_06_subharmonic_set(v);
}

void param_27_value_set(number v) {
    v = this->param_27_value_constrain(v);
    this->param_27_value = v;
    this->sendParameter(4, false);

    if (this->param_27_value != this->param_27_lastValue) {
        this->getEngine()->presetTouched();
        this->param_27_lastValue = this->param_27_value;
    }

    this->dspexpr_10_in2_set(v);
    this->dspexpr_09_in2_set(v);
}

void param_28_value_set(number v) {
    v = this->param_28_value_constrain(v);
    this->param_28_value = v;
    this->sendParameter(5, false);

    if (this->param_28_value != this->param_28_lastValue) {
        this->getEngine()->presetTouched();
        this->param_28_lastValue = this->param_28_value;
    }

    this->p_05_pitchHold_set(v);
    this->p_06_pitchHold_set(v);
}

void param_29_value_set(number v) {
    v = this->param_29_value_constrain(v);
    this->param_29_value = v;
    this->sendParameter(6, false);

    if (this->param_29_value != this->param_29_lastValue) {
        this->getEngine()->presetTouched();
        this->param_29_lastValue = this->param_29_value;
    }

    this->p_05_pitchThresh_set(v);
    this->p_06_pitchThresh_set(v);
}

void param_30_value_set(number v) {
    v = this->param_30_value_constrain(v);
    this->param_30_value = v;
    this->sendParameter(7, false);

    if (this->param_30_value != this->param_30_lastValue) {
        this->getEngine()->presetTouched();
        this->param_30_lastValue = this->param_30_value;
    }
}

void param_31_value_set(number v) {
    v = this->param_31_value_constrain(v);
    this->param_31_value = v;
    this->sendParameter(8, false);

    if (this->param_31_value != this->param_31_lastValue) {
        this->getEngine()->presetTouched();
        this->param_31_lastValue = this->param_31_value;
    }

    this->p_05_pitchFollow_set(v);
    this->p_06_pitchFollow_set(v);
}

void param_32_value_set(number v) {
    v = this->param_32_value_constrain(v);
    this->param_32_value = v;
    this->sendParameter(9, false);

    if (this->param_32_value != this->param_32_lastValue) {
        this->getEngine()->presetTouched();
        this->param_32_lastValue = this->param_32_value;
    }

    this->p_05_ampEnv_set(v);
    this->p_06_ampEnv_set(v);
}

void param_33_value_set(number v) {
    v = this->param_33_value_constrain(v);
    this->param_33_value = v;
    this->sendParameter(10, false);

    if (this->param_33_value != this->param_33_lastValue) {
        this->getEngine()->presetTouched();
        this->param_33_lastValue = this->param_33_value;
    }

    this->p_05_ampMod_set(v);
    this->p_06_ampMod_set(v);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    this->p_05->allocateDataRefs();
    this->p_06->allocateDataRefs();

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->ip_07_init();
    this->p_05->initializeObjects();
    this->p_06->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_05->startup();
    this->p_06->startup();

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 0);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    this->processParamInitEvents();
}

number param_23_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void ip_07_value_set(number v) {
    this->ip_07_value = v;
    this->ip_07_fillSigBuf();
    this->ip_07_lastValue = v;
}

number param_24_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < -100 ? -100 : v));
    return v;
}

void p_05_freq_set(number v) {
    {
        this->p_05->setParameterValue(3, v, this->_currentTime);
    }
}

void p_06_freq_set(number v) {
    {
        this->p_06->setParameterValue(3, v, this->_currentTime);
    }
}

number param_25_value_constrain(number v) const {
    v = (v > 32 ? 32 : (v < 1 ? 1 : v));
    return v;
}

void p_05_ratio_set(number v) {
    {
        this->p_05->setParameterValue(7, v, this->_currentTime);
    }
}

void p_06_ratio_set(number v) {
    {
        this->p_06->setParameterValue(7, v, this->_currentTime);
    }
}

number param_26_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void p_05_subharmonic_set(number v) {
    {
        this->p_05->setParameterValue(5, v, this->_currentTime);
    }
}

void p_06_subharmonic_set(number v) {
    {
        this->p_06->setParameterValue(5, v, this->_currentTime);
    }
}

number param_27_value_constrain(number v) const {
    v = (v > 0.999 ? 0.999 : (v < 0 ? 0 : v));
    return v;
}

void dspexpr_10_in2_set(number v) {
    this->dspexpr_10_in2 = v;
}

void dspexpr_09_in2_set(number v) {
    this->dspexpr_09_in2 = v;
}

number param_28_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void p_05_pitchHold_set(number v) {
    {
        this->p_05->setParameterValue(6, v, this->_currentTime);
    }
}

void p_06_pitchHold_set(number v) {
    {
        this->p_06->setParameterValue(6, v, this->_currentTime);
    }
}

number param_29_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void p_05_pitchThresh_set(number v) {
    {
        this->p_05->setParameterValue(8, v, this->_currentTime);
    }
}

void p_06_pitchThresh_set(number v) {
    {
        this->p_06->setParameterValue(8, v, this->_currentTime);
    }
}

number param_30_value_constrain(number v) const {
    v = (v > 1000 ? 1000 : (v < 0 ? 0 : v));
    return v;
}

number param_31_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void p_05_pitchFollow_set(number v) {
    {
        this->p_05->setParameterValue(1, v, this->_currentTime);
    }
}

void p_06_pitchFollow_set(number v) {
    {
        this->p_06->setParameterValue(1, v, this->_currentTime);
    }
}

number param_32_value_constrain(number v) const {
    v = (v > 1000 ? 1000 : (v < 0 ? 0 : v));
    return v;
}

void p_05_ampEnv_set(number v) {
    {
        this->p_05->setParameterValue(0, v, this->_currentTime);
    }
}

void p_06_ampEnv_set(number v) {
    {
        this->p_06->setParameterValue(0, v, this->_currentTime);
    }
}

number param_33_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void p_05_ampMod_set(number v) {
    {
        this->p_05->setParameterValue(4, v, this->_currentTime);
    }
}

void p_06_ampMod_set(number v) {
    {
        this->p_06->setParameterValue(4, v, this->_currentTime);
    }
}

void ip_07_perform(SampleValue * out, Index n) {
    auto __ip_07_lastValue = this->ip_07_lastValue;
    auto __ip_07_lastIndex = this->ip_07_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_07_lastIndex ? __ip_07_lastValue : this->ip_07_sigbuf[(Index)i]);
    }

    __ip_07_lastIndex = 0;
    this->ip_07_lastIndex = __ip_07_lastIndex;
}

void feedbackreader_01_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_01_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void dspexpr_09_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void feedbackreader_02_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_02_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void dspexpr_10_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void feedbackreader_03_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_03_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void feedbackreader_04_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_04_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void feedbackreader_05_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_05_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void signaladder_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void p_05_perform(
    const SampleValue * target_in,
    const SampleValue * target_ratio,
    const SampleValue * in1,
    SampleValue * source_in,
    SampleValue * source_ratio,
    SampleValue * out1,
    Index n
) {
    ConstSampleArray<3> ins = {in1, target_in, target_ratio};
    SampleArray<3> outs = {out1, source_in, source_ratio};
    this->p_05->process(ins, 3, outs, 3, n);
}

void feedbackwriter_04_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_04_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void feedbackwriter_06_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_06_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void limi_01_perform(const SampleValue * input1, SampleValue * output1, Index n) {
    RNBO_UNUSED(output1);
    RNBO_UNUSED(input1);
    auto __limi_01_lookaheadInv = this->limi_01_lookaheadInv;
    auto __limi_01_threshold = this->limi_01_threshold;
    auto __limi_01_lookahead = this->limi_01_lookahead;
    auto __limi_01_recover = this->limi_01_recover;
    auto __limi_01_last = this->limi_01_last;
    auto __limi_01_postamp = this->limi_01_postamp;
    auto __limi_01_lookaheadIndex = this->limi_01_lookaheadIndex;
    auto __limi_01_preamp = this->limi_01_preamp;
    auto __limi_01_dcblock = this->limi_01_dcblock;
    auto __limi_01_bypass = this->limi_01_bypass;
    ConstSampleArray<1> input = {input1};
    SampleArray<1> output = {output1};

    if ((bool)(__limi_01_bypass)) {
        for (Index i = 0; i < n; i++) {
            for (Index j = 0; j < 1; j++) {
                output[(Index)j][(Index)i] = input[(Index)j][(Index)i];
            }
        }
    } else {
        number v;

        for (Index i = 0; i < n; i++) {
            number hotSample = 0;

            for (Index j = 0; j < 1; j++) {
                auto smps = input[(Index)j];
                v = ((bool)(__limi_01_dcblock) ? this->limi_01_dc_next(j, smps[(Index)i], 0.9997) : smps[(Index)i]);
                v *= __limi_01_preamp;
                this->limi_01_lookaheadBuffers[(Index)j][__limi_01_lookaheadIndex] = v * __limi_01_postamp;
                v = rnbo_fabs(v);

                if (v > hotSample)
                    hotSample = v;
            }

            {
                if (__limi_01_last > 0.01)
                    v = __limi_01_last + __limi_01_recover * __limi_01_last;
                else
                    v = __limi_01_last + __limi_01_recover;
            }

            if (v > 1)
                v = 1;

            this->limi_01_gainBuffer[__limi_01_lookaheadIndex] = v;
            int lookaheadPlayback = (int)(__limi_01_lookaheadIndex - (int)(__limi_01_lookahead));

            if (lookaheadPlayback < 0)
                lookaheadPlayback += (int)(__limi_01_lookahead);

            if (hotSample * v > __limi_01_threshold) {
                number newgain;
                number curgain = __limi_01_threshold / hotSample;
                number inc = __limi_01_threshold - curgain;
                number acc = 0.0;
                number flag = 0;

                for (Index j = 0; flag == 0 && j < (Index)(__limi_01_lookahead); j++) {
                    int k = (int)(__limi_01_lookaheadIndex - (int)(j));

                    if (k < 0)
                        k += (int)(__limi_01_lookahead);

                    {
                        newgain = curgain + inc * (acc * acc);
                    }

                    if (newgain < this->limi_01_gainBuffer[(Index)k])
                        this->limi_01_gainBuffer[(Index)k] = newgain;
                    else
                        flag = 1;

                    acc = acc + __limi_01_lookaheadInv;
                }
            }

            for (Index j = 0; j < 1; j++) {
                output[(Index)j][(Index)i] = this->limi_01_lookaheadBuffers[(Index)j][(Index)lookaheadPlayback] * this->limi_01_gainBuffer[(Index)lookaheadPlayback];
            }

            __limi_01_last = this->limi_01_gainBuffer[__limi_01_lookaheadIndex];
            __limi_01_lookaheadIndex++;

            if (__limi_01_lookaheadIndex >= __limi_01_lookahead)
                __limi_01_lookaheadIndex = 0;
        }
    }

    this->limi_01_lookaheadIndex = __limi_01_lookaheadIndex;
    this->limi_01_last = __limi_01_last;
}

void xfade_tilde_01_perform(
    const Sample * pos,
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] * this->xfade_tilde_01_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_01_func_next(pos[(Index)i], 1);
    }
}

void feedbackwriter_01_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_01_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void feedbackreader_06_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_06_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void signaladder_02_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void p_06_perform(
    const SampleValue * target_in,
    const SampleValue * target_ratio,
    const SampleValue * in1,
    SampleValue * source_in,
    SampleValue * source_ratio,
    SampleValue * out1,
    Index n
) {
    ConstSampleArray<3> ins = {in1, target_in, target_ratio};
    SampleArray<3> outs = {out1, source_in, source_ratio};
    this->p_06->process(ins, 3, outs, 3, n);
}

void feedbackwriter_03_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_03_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void feedbackwriter_05_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_05_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void limi_02_perform(const SampleValue * input1, SampleValue * output1, Index n) {
    RNBO_UNUSED(output1);
    RNBO_UNUSED(input1);
    auto __limi_02_lookaheadInv = this->limi_02_lookaheadInv;
    auto __limi_02_threshold = this->limi_02_threshold;
    auto __limi_02_lookahead = this->limi_02_lookahead;
    auto __limi_02_recover = this->limi_02_recover;
    auto __limi_02_last = this->limi_02_last;
    auto __limi_02_postamp = this->limi_02_postamp;
    auto __limi_02_lookaheadIndex = this->limi_02_lookaheadIndex;
    auto __limi_02_preamp = this->limi_02_preamp;
    auto __limi_02_dcblock = this->limi_02_dcblock;
    auto __limi_02_bypass = this->limi_02_bypass;
    ConstSampleArray<1> input = {input1};
    SampleArray<1> output = {output1};

    if ((bool)(__limi_02_bypass)) {
        for (Index i = 0; i < n; i++) {
            for (Index j = 0; j < 1; j++) {
                output[(Index)j][(Index)i] = input[(Index)j][(Index)i];
            }
        }
    } else {
        number v;

        for (Index i = 0; i < n; i++) {
            number hotSample = 0;

            for (Index j = 0; j < 1; j++) {
                auto smps = input[(Index)j];
                v = ((bool)(__limi_02_dcblock) ? this->limi_02_dc_next(j, smps[(Index)i], 0.9997) : smps[(Index)i]);
                v *= __limi_02_preamp;
                this->limi_02_lookaheadBuffers[(Index)j][__limi_02_lookaheadIndex] = v * __limi_02_postamp;
                v = rnbo_fabs(v);

                if (v > hotSample)
                    hotSample = v;
            }

            {
                if (__limi_02_last > 0.01)
                    v = __limi_02_last + __limi_02_recover * __limi_02_last;
                else
                    v = __limi_02_last + __limi_02_recover;
            }

            if (v > 1)
                v = 1;

            this->limi_02_gainBuffer[__limi_02_lookaheadIndex] = v;
            int lookaheadPlayback = (int)(__limi_02_lookaheadIndex - (int)(__limi_02_lookahead));

            if (lookaheadPlayback < 0)
                lookaheadPlayback += (int)(__limi_02_lookahead);

            if (hotSample * v > __limi_02_threshold) {
                number newgain;
                number curgain = __limi_02_threshold / hotSample;
                number inc = __limi_02_threshold - curgain;
                number acc = 0.0;
                number flag = 0;

                for (Index j = 0; flag == 0 && j < (Index)(__limi_02_lookahead); j++) {
                    int k = (int)(__limi_02_lookaheadIndex - (int)(j));

                    if (k < 0)
                        k += (int)(__limi_02_lookahead);

                    {
                        newgain = curgain + inc * (acc * acc);
                    }

                    if (newgain < this->limi_02_gainBuffer[(Index)k])
                        this->limi_02_gainBuffer[(Index)k] = newgain;
                    else
                        flag = 1;

                    acc = acc + __limi_02_lookaheadInv;
                }
            }

            for (Index j = 0; j < 1; j++) {
                output[(Index)j][(Index)i] = this->limi_02_lookaheadBuffers[(Index)j][(Index)lookaheadPlayback] * this->limi_02_gainBuffer[(Index)lookaheadPlayback];
            }

            __limi_02_last = this->limi_02_gainBuffer[__limi_02_lookaheadIndex];
            __limi_02_lookaheadIndex++;

            if (__limi_02_lookaheadIndex >= __limi_02_lookahead)
                __limi_02_lookaheadIndex = 0;
        }
    }

    this->limi_02_lookaheadIndex = __limi_02_lookaheadIndex;
    this->limi_02_last = __limi_02_last;
}

void xfade_tilde_02_perform(
    const Sample * pos,
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] * this->xfade_tilde_02_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_02_func_next(pos[(Index)i], 1);
    }
}

void feedbackwriter_02_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_02_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void p_06_target_detectedFreq_number_set(number v) {
    this->p_06->updateTime(this->_currentTime);
    this->p_06->receive_02_output_number_set(v);
}

void p_05_source_detectedFreq_number_set(number v) {
    this->p_06_target_detectedFreq_number_set(v);
}

void p_05_target_detectedFreq_number_set(number v) {
    this->p_05->updateTime(this->_currentTime);
    this->p_05->receive_01_output_number_set(v);
}

void p_06_source_detectedFreq_number_set(number v) {
    this->p_05_target_detectedFreq_number_set(v);
}

void limi_01_lookahead_setter(number v) {
    this->limi_01_lookahead = (v > 512 ? 512 : (v < 0 ? 0 : v));
    this->limi_01_lookaheadInv = (number)1 / this->limi_01_lookahead;
}

void limi_01_preamp_setter(number v) {
    this->limi_01_preamp = rnbo_pow(10., v * 0.05);
}

void limi_01_postamp_setter(number v) {
    this->limi_01_postamp = rnbo_pow(10., v * 0.05);
}

void limi_01_threshold_setter(number v) {
    this->limi_01_threshold = rnbo_pow(10., v * 0.05);
}

void limi_02_lookahead_setter(number v) {
    this->limi_02_lookahead = (v > 512 ? 512 : (v < 0 ? 0 : v));
    this->limi_02_lookaheadInv = (number)1 / this->limi_02_lookahead;
}

void limi_02_preamp_setter(number v) {
    this->limi_02_preamp = rnbo_pow(10., v * 0.05);
}

void limi_02_postamp_setter(number v) {
    this->limi_02_postamp = rnbo_pow(10., v * 0.05);
}

void limi_02_threshold_setter(number v) {
    this->limi_02_threshold = rnbo_pow(10., v * 0.05);
}

void ip_07_init() {
    this->ip_07_lastValue = this->ip_07_value;
}

void ip_07_fillSigBuf() {
    if ((bool)(this->ip_07_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_07_lastIndex); i < k; i++) {
            if (this->ip_07_resetCount > 0) {
                this->ip_07_sigbuf[(Index)i] = 1;
                this->ip_07_resetCount--;
            } else {
                this->ip_07_sigbuf[(Index)i] = this->ip_07_lastValue;
            }
        }

        this->ip_07_lastIndex = k;
    }
}

void ip_07_dspsetup(bool force) {
    if ((bool)(this->ip_07_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_07_lastIndex = 0;
    this->ip_07_setupDone = true;
}

void param_23_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_23_value;
}

void param_23_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_23_value_set(preset["value"]);
}

number xfade_tilde_01_func_next(number pos, int channel) {
    {
        {
            number nchan_1 = 2 - 1;

            {
                pos = pos * nchan_1;
            }

            {
                if (pos > nchan_1)
                    pos = nchan_1;
                else if (pos < 0)
                    pos = 0;
            }

            pos = pos - channel;

            if (pos > -1 && pos < 1) {
                {
                    {
                        return this->safesqrt(1.0 - rnbo_abs(pos));
                    }
                }
            } else {
                return 0;
            }
        }
    }
}

void xfade_tilde_01_func_reset() {}

number limi_01_dc1_next(number x, number gain) {
    number y = x - this->limi_01_dc1_xm1 + this->limi_01_dc1_ym1 * gain;
    this->limi_01_dc1_xm1 = x;
    this->limi_01_dc1_ym1 = y;
    return y;
}

void limi_01_dc1_reset() {
    this->limi_01_dc1_xm1 = 0;
    this->limi_01_dc1_ym1 = 0;
}

void limi_01_dc1_dspsetup() {
    this->limi_01_dc1_reset();
}

number limi_01_dc_next(Index i, number x, number gain) {
    switch ((int)i) {
    default:
        {
        return this->limi_01_dc1_next(x, gain);
        }
    }

    return 0;
}

void limi_01_dc_reset(Index i) {
    switch ((int)i) {
    default:
        {
        return this->limi_01_dc1_reset();
        }
    }
}

void limi_01_dc_dspsetup(Index i) {
    switch ((int)i) {
    default:
        {
        return this->limi_01_dc1_dspsetup();
        }
    }
}

void limi_01_reset() {
    this->limi_01_recover = (number)1000 / (this->limi_01_release * this->samplerate());

    {
        this->limi_01_recover *= 0.707;
    }
}

void limi_01_dspsetup(bool force) {
    if ((bool)(this->limi_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->limi_01_reset();
    this->limi_01_setupDone = true;
    this->limi_01_dc1_dspsetup();
}

number xfade_tilde_02_func_next(number pos, int channel) {
    {
        {
            number nchan_1 = 2 - 1;

            {
                pos = pos * nchan_1;
            }

            {
                if (pos > nchan_1)
                    pos = nchan_1;
                else if (pos < 0)
                    pos = 0;
            }

            pos = pos - channel;

            if (pos > -1 && pos < 1) {
                {
                    {
                        return this->safesqrt(1.0 - rnbo_abs(pos));
                    }
                }
            } else {
                return 0;
            }
        }
    }
}

void xfade_tilde_02_func_reset() {}

number limi_02_dc1_next(number x, number gain) {
    number y = x - this->limi_02_dc1_xm1 + this->limi_02_dc1_ym1 * gain;
    this->limi_02_dc1_xm1 = x;
    this->limi_02_dc1_ym1 = y;
    return y;
}

void limi_02_dc1_reset() {
    this->limi_02_dc1_xm1 = 0;
    this->limi_02_dc1_ym1 = 0;
}

void limi_02_dc1_dspsetup() {
    this->limi_02_dc1_reset();
}

number limi_02_dc_next(Index i, number x, number gain) {
    switch ((int)i) {
    default:
        {
        return this->limi_02_dc1_next(x, gain);
        }
    }

    return 0;
}

void limi_02_dc_reset(Index i) {
    switch ((int)i) {
    default:
        {
        return this->limi_02_dc1_reset();
        }
    }
}

void limi_02_dc_dspsetup(Index i) {
    switch ((int)i) {
    default:
        {
        return this->limi_02_dc1_dspsetup();
        }
    }
}

void limi_02_reset() {
    this->limi_02_recover = (number)1000 / (this->limi_02_release * this->samplerate());

    {
        this->limi_02_recover *= 0.707;
    }
}

void limi_02_dspsetup(bool force) {
    if ((bool)(this->limi_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->limi_02_reset();
    this->limi_02_setupDone = true;
    this->limi_02_dc1_dspsetup();
}

void param_24_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_24_value;
}

void param_24_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_24_value_set(preset["value"]);
}

void param_25_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_25_value;
}

void param_25_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_25_value_set(preset["value"]);
}

void param_26_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_26_value;
}

void param_26_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_26_value_set(preset["value"]);
}

void param_27_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_27_value;
}

void param_27_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_27_value_set(preset["value"]);
}

void param_28_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_28_value;
}

void param_28_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_28_value_set(preset["value"]);
}

void param_29_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_29_value;
}

void param_29_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_29_value_set(preset["value"]);
}

void param_30_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_30_value;
}

void param_30_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_30_value_set(preset["value"]);
}

void param_31_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_31_value;
}

void param_31_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_31_value_set(preset["value"]);
}

void param_32_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_32_value;
}

void param_32_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_32_value_set(preset["value"]);
}

void param_33_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_33_value;
}

void param_33_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_33_value_set(preset["value"]);
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    ip_07_value = 0;
    ip_07_impulse = 0;
    param_23_value = 0.5;
    xfade_tilde_01_pos = 0;
    limi_01_bypass = 0;
    limi_01_dcblock = 0;
    limi_01_lookahead = 100;
    limi_01_lookahead_setter(limi_01_lookahead);
    limi_01_preamp = 0;
    limi_01_preamp_setter(limi_01_preamp);
    limi_01_postamp = 0;
    limi_01_postamp_setter(limi_01_postamp);
    limi_01_threshold = 0;
    limi_01_threshold_setter(limi_01_threshold);
    limi_01_release = 1000;
    p_05_target = 0;
    xfade_tilde_02_pos = 0;
    limi_02_bypass = 0;
    limi_02_dcblock = 0;
    limi_02_lookahead = 100;
    limi_02_lookahead_setter(limi_02_lookahead);
    limi_02_preamp = 0;
    limi_02_preamp_setter(limi_02_preamp);
    limi_02_postamp = 0;
    limi_02_postamp_setter(limi_02_postamp);
    limi_02_threshold = 0;
    limi_02_threshold_setter(limi_02_threshold);
    limi_02_release = 1000;
    p_06_target = 0;
    param_24_value = 1;
    param_25_value = 1;
    dspexpr_09_in1 = 0;
    dspexpr_09_in2 = 0;
    dspexpr_10_in1 = 0;
    dspexpr_10_in2 = 0;
    param_26_value = 0;
    param_27_value = 0;
    param_28_value = 0;
    param_29_value = 0.1;
    param_30_value = 1;
    param_31_value = 0;
    param_32_value = 0.1;
    param_33_value = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    signals[4] = nullptr;
    signals[5] = nullptr;
    signals[6] = nullptr;
    signals[7] = nullptr;
    signals[8] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    ip_07_lastIndex = 0;
    ip_07_lastValue = 0;
    ip_07_resetCount = 0;
    ip_07_sigbuf = nullptr;
    ip_07_setupDone = false;
    param_23_lastValue = 0;
    limi_01_last = 0;
    limi_01_lookaheadIndex = 0;
    limi_01_recover = 0;
    limi_01_lookaheadInv = 0;
    limi_01_dc1_xm1 = 0;
    limi_01_dc1_ym1 = 0;
    limi_01_setupDone = false;
    limi_02_last = 0;
    limi_02_lookaheadIndex = 0;
    limi_02_recover = 0;
    limi_02_lookaheadInv = 0;
    limi_02_dc1_xm1 = 0;
    limi_02_dc1_ym1 = 0;
    limi_02_setupDone = false;
    param_24_lastValue = 0;
    param_25_lastValue = 0;
    feedbacktilde_01_feedbackbuffer = nullptr;
    feedbacktilde_02_feedbackbuffer = nullptr;
    param_26_lastValue = 0;
    param_27_lastValue = 0;
    param_28_lastValue = 0;
    param_29_lastValue = 0;
    param_30_lastValue = 0;
    param_31_lastValue = 0;
    param_32_lastValue = 0;
    param_33_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    feedbacktilde_03_feedbackbuffer = nullptr;
    feedbacktilde_04_feedbackbuffer = nullptr;
    feedbacktilde_05_feedbackbuffer = nullptr;
    feedbacktilde_06_feedbackbuffer = nullptr;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number ip_07_value;
    number ip_07_impulse;
    number param_23_value;
    number xfade_tilde_01_pos;
    number limi_01_bypass;
    number limi_01_dcblock;
    number limi_01_lookahead;
    number limi_01_preamp;
    number limi_01_postamp;
    number limi_01_threshold;
    number limi_01_release;
    number p_05_target;
    number xfade_tilde_02_pos;
    number limi_02_bypass;
    number limi_02_dcblock;
    number limi_02_lookahead;
    number limi_02_preamp;
    number limi_02_postamp;
    number limi_02_threshold;
    number limi_02_release;
    number p_06_target;
    number param_24_value;
    number param_25_value;
    number dspexpr_09_in1;
    number dspexpr_09_in2;
    number dspexpr_10_in1;
    number dspexpr_10_in2;
    number param_26_value;
    number param_27_value;
    number param_28_value;
    number param_29_value;
    number param_30_value;
    number param_31_value;
    number param_32_value;
    number param_33_value;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[9];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    SampleIndex ip_07_lastIndex;
    number ip_07_lastValue;
    SampleIndex ip_07_resetCount;
    signal ip_07_sigbuf;
    bool ip_07_setupDone;
    number param_23_lastValue;
    SampleValue limi_01_lookaheadBuffers[1][512] = { };
    SampleValue limi_01_gainBuffer[512] = { };
    number limi_01_last;
    int limi_01_lookaheadIndex;
    number limi_01_recover;
    number limi_01_lookaheadInv;
    number limi_01_dc1_xm1;
    number limi_01_dc1_ym1;
    bool limi_01_setupDone;
    SampleValue limi_02_lookaheadBuffers[1][512] = { };
    SampleValue limi_02_gainBuffer[512] = { };
    number limi_02_last;
    int limi_02_lookaheadIndex;
    number limi_02_recover;
    number limi_02_lookaheadInv;
    number limi_02_dc1_xm1;
    number limi_02_dc1_ym1;
    bool limi_02_setupDone;
    number param_24_lastValue;
    number param_25_lastValue;
    signal feedbacktilde_01_feedbackbuffer;
    signal feedbacktilde_02_feedbackbuffer;
    number param_26_lastValue;
    number param_27_lastValue;
    number param_28_lastValue;
    number param_29_lastValue;
    number param_30_lastValue;
    number param_31_lastValue;
    number param_32_lastValue;
    number param_33_lastValue;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    signal feedbacktilde_03_feedbackbuffer;
    signal feedbacktilde_04_feedbackbuffer;
    signal feedbacktilde_05_feedbackbuffer;
    signal feedbacktilde_06_feedbackbuffer;
    DataRef RNBODefaultSinus;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_2062* p_05;
    RNBOSubpatcher_2063* p_06;

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

