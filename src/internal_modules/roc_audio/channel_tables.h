/*
 * Copyright (c) 2023 Roc Streaming authors
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

//! @file roc_audio/channel_tables.h
//! @brief Channel tables.

#ifndef ROC_AUDIO_CHANNEL_TABLES_H_
#define ROC_AUDIO_CHANNEL_TABLES_H_

#include "roc_audio/channel_defs.h"
#include "roc_audio/sample.h"

namespace roc {
namespace audio {

//! Defines string name for channel position.
struct ChannelPositionName {
    const char* name;    //!< Name.
    ChannelPosition pos; //!< Numeric ID.
};

//! Defines string name for pre-defined channel mask.
struct ChannelMaskName {
    const char* name; //!< Name.
    ChannelMask mask; //!< Bitmask.
};

//! Defines multiplication coefficient for a pair of channels.
struct ChannelMapRule {
    ChannelPosition out_ch; //!< Index of output channel.
    ChannelPosition in_ch;  //!< Index of input channel.
    sample_t coeff;         //!< Multiplication coefficient.
};

//! Defines multiplication matrix for two channel masks.
//! Instead of defining the whole matrix, it defines a list of pairs of
//! output and input channel numbers and corresponding coefficients.
//! Such representation allows more compact definition in the source
//! code. The actual matrix is built by channel mapper at runtime.
struct ChannelMapTable {
    const char* name; //!< Mapping name.

    ChannelMask in_mask;  //!< Channel mask of input stream.
    ChannelMask out_mask; //!< Channel mask of output stream.

    //! Transformation rules.
    //! Rules are used to fill channel mapping matrix.
    ChannelMapRule rules[24];
};

//! Defines ordered list of channels.
struct ChannelOrderTable {
    //! List of channels.
    //! Last channel is equal to ChanPos_Max.
    ChannelPosition chans[ChanPos_Max + 1];
};

//! Defines mapping between channel position and its name.
extern const ChannelPositionName ChanPositionNames[ChanPos_Max];

//! Defines mapping between channel mask and its name.
extern const ChannelMaskName ChanMaskNames[17];

//! Defines mapping of channel order identifier to list of channel positions
//! in corresponding order.
extern const ChannelOrderTable ChanOrderTables[ChanOrder_Max];

//! Defines list of mappings between all supported surround channel mask pairs.
//! Channel mapper will search for appropriate mapping in this list,
//! based on input and output channel masks.
extern const ChannelMapTable ChanMapTables[40];

} // namespace audio
} // namespace roc

#endif // ROC_AUDIO_CHANNEL_TABLES_H_