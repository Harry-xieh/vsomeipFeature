// Copyright (C) 2021 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "../include/suspend_command.hpp"

namespace vsomeip_v3 { namespace protocol {

suspend_command::suspend_command() : simple_command(id_e::SUSPEND_ID) {}

}} // namespace vsomeip_v3::protocol
