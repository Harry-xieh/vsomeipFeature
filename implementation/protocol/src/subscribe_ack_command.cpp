// Copyright (C) 2021 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "../include/subscribe_ack_command.hpp"

namespace vsomeip_v3 { namespace protocol {

subscribe_ack_command::subscribe_ack_command() : subscribe_ack_command_base(id_e::SUBSCRIBE_ACK_ID)
{}

}} // namespace vsomeip_v3::protocol
