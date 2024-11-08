// Copyright (C) 2021 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "../include/subscribe_command_base.hpp"

#include <limits>
#include <vsomeip/constants.hpp>

namespace vsomeip_v3 { namespace protocol {

subscribe_command_base::subscribe_command_base(id_e _id)
    : command(_id),
      service_(ANY_SERVICE),
      instance_(ANY_INSTANCE),
      eventgroup_(0),
      major_(ANY_MAJOR),
      event_(ANY_EVENT),
      pending_id_(0)
{}

service_t subscribe_command_base::get_service() const
{
    return service_;
}

void subscribe_command_base::set_service(service_t _service)
{
    service_ = _service;
}

instance_t subscribe_command_base::get_instance() const
{
    return instance_;
}

void subscribe_command_base::set_instance(instance_t _instance)
{
    instance_ = _instance;
}

eventgroup_t subscribe_command_base::get_eventgroup() const
{
    return eventgroup_;
}

void subscribe_command_base::set_eventgroup(eventgroup_t _eventgroup)
{
    eventgroup_ = _eventgroup;
}

major_version_t subscribe_command_base::get_major() const
{
    return major_;
}

void subscribe_command_base::set_major(major_version_t _major)
{
    major_ = _major;
}

event_t subscribe_command_base::get_event() const
{
    return event_;
}

void subscribe_command_base::set_event(event_t _event)
{
    event_ = _event;
}

pending_id_t subscribe_command_base::get_pending_id() const
{
    return pending_id_;
}

void subscribe_command_base::set_pending_id(pending_id_t _pending_id)
{
    pending_id_ = _pending_id;
}

void subscribe_command_base::serialize(std::vector<byte_t>& _buffer, error_e& _error) const
{
    // serialize header
    command::serialize(_buffer, _error);
    if (_error != error_e::ERROR_OK)
        return;

    // serialize payload
    size_t its_offset(COMMAND_POSITION_PAYLOAD);
    std::memcpy(&_buffer[its_offset], &service_, sizeof(service_));
    its_offset += sizeof(service_);
    std::memcpy(&_buffer[its_offset], &instance_, sizeof(instance_));
    its_offset += sizeof(instance_);
    std::memcpy(&_buffer[its_offset], &eventgroup_, sizeof(eventgroup_));
    its_offset += sizeof(instance_);
    _buffer[its_offset] = major_;
    its_offset += sizeof(major_);
    std::memcpy(&_buffer[its_offset], &event_, sizeof(event_));
    its_offset += sizeof(event_);
    std::memcpy(&_buffer[its_offset], &pending_id_, sizeof(pending_id_));
}

void subscribe_command_base::deserialize(const std::vector<byte_t>& _buffer, error_e& _error)
{
    // deserialize header
    command::deserialize(_buffer, _error);
    if (_error != error_e::ERROR_OK)
        return;

    // deserialize payload
    size_t its_offset(COMMAND_POSITION_PAYLOAD);
    std::memcpy(&service_, &_buffer[its_offset], sizeof(service_));
    its_offset += sizeof(service_);
    std::memcpy(&instance_, &_buffer[its_offset], sizeof(instance_));
    its_offset += sizeof(instance_);
    std::memcpy(&eventgroup_, &_buffer[its_offset], sizeof(eventgroup_));
    its_offset += sizeof(eventgroup_);
    major_ = _buffer[its_offset];
    its_offset += sizeof(major_);
    std::memcpy(&event_, &_buffer[its_offset], sizeof(event_));
    its_offset += sizeof(event_);
    std::memcpy(&pending_id_, &_buffer[its_offset], sizeof(pending_id_));
}

}} // namespace vsomeip_v3::protocol
