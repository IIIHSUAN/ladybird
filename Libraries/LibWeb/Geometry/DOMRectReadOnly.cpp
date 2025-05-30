/*
 * Copyright (c) 2022, Andreas Kling <andreas@ladybird.org>
 * Copyright (c) 2024, Kenneth Myhra <kennethmyhra@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/DOMRectReadOnlyPrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Geometry/DOMRectReadOnly.h>
#include <LibWeb/HTML/StructuredSerialize.h>
#include <LibWeb/WebIDL/ExceptionOr.h>

namespace Web::Geometry {

GC_DEFINE_ALLOCATOR(DOMRectReadOnly);

WebIDL::ExceptionOr<GC::Ref<DOMRectReadOnly>> DOMRectReadOnly::construct_impl(JS::Realm& realm, double x, double y, double width, double height)
{
    return realm.create<DOMRectReadOnly>(realm, x, y, width, height);
}

// https://drafts.fxtf.org/geometry/#create-a-domrect-from-the-dictionary
GC::Ref<DOMRectReadOnly> DOMRectReadOnly::from_rect(JS::VM& vm, Geometry::DOMRectInit const& other)
{
    auto& realm = *vm.current_realm();
    return realm.create<DOMRectReadOnly>(realm, other.x, other.y, other.width, other.height);
}

GC::Ref<DOMRectReadOnly> DOMRectReadOnly::create(JS::Realm& realm)
{
    return realm.create<DOMRectReadOnly>(realm);
}

DOMRectReadOnly::DOMRectReadOnly(JS::Realm& realm, double x, double y, double width, double height)
    : PlatformObject(realm)
    , m_rect(x, y, width, height)
{
}

DOMRectReadOnly::DOMRectReadOnly(JS::Realm& realm)
    : PlatformObject(realm)
{
}

DOMRectReadOnly::~DOMRectReadOnly() = default;

void DOMRectReadOnly::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(DOMRectReadOnly);
    Base::initialize(realm);
}

// https://drafts.fxtf.org/geometry/#structured-serialization
WebIDL::ExceptionOr<void> DOMRectReadOnly::serialization_steps(HTML::SerializationRecord& serialized, bool, HTML::SerializationMemory&)
{
    // 1. Set serialized.[[X]] to value’s x coordinate.
    HTML::serialize_primitive_type(serialized, this->x());
    // 2. Set serialized.[[Y]] to value’s y coordinate.
    HTML::serialize_primitive_type(serialized, this->y());
    // 3. Set serialized.[[Width]] to value’s width.
    HTML::serialize_primitive_type(serialized, this->width());
    // 4. Set serialized.[[Height]] to value’s height.
    HTML::serialize_primitive_type(serialized, this->height());
    return {};
}

// https://drafts.fxtf.org/geometry/#structured-serialization
WebIDL::ExceptionOr<void> DOMRectReadOnly::deserialization_steps(ReadonlySpan<u32> const& serialized, size_t& position, HTML::DeserializationMemory&)
{
    // 1. Set value’s x coordinate to serialized.[[X]].
    auto x = HTML::deserialize_primitive_type<double>(serialized, position);
    // 2. Set value’s y coordinate to serialized.[[Y]].
    auto y = HTML::deserialize_primitive_type<double>(serialized, position);
    // 3. Set value’s width to serialized.[[Width]].
    auto width = HTML::deserialize_primitive_type<double>(serialized, position);
    // 4. Set value’s height to serialized.[[Height]].
    auto height = HTML::deserialize_primitive_type<double>(serialized, position);

    m_rect = { x, y, width, height };

    return {};
}

}
