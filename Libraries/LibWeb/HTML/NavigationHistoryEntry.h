/*
 * Copyright (c) 2023, Andrew Kaster <akaster@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/DOM/EventTarget.h>

namespace Web::HTML {

// https://html.spec.whatwg.org/multipage/nav-history-apis.html#navigationhistoryentry
class NavigationHistoryEntry : public DOM::EventTarget {
    WEB_PLATFORM_OBJECT(NavigationHistoryEntry, DOM::EventTarget);
    GC_DECLARE_ALLOCATOR(NavigationHistoryEntry);

public:
    [[nodiscard]] static GC::Ref<NavigationHistoryEntry> create(JS::Realm&, GC::Ref<SessionHistoryEntry>);

    Optional<String> url() const;
    String key() const;
    String id() const;
    i64 index() const;
    bool same_document() const;
    WebIDL::ExceptionOr<JS::Value> get_state();

    void set_ondispose(WebIDL::CallbackType*);
    WebIDL::CallbackType* ondispose();

    // Non-spec'd getter, not exposed to JS
    SessionHistoryEntry const& session_history_entry() const { return *m_session_history_entry; }
    SessionHistoryEntry& session_history_entry() { return *m_session_history_entry; }

    virtual ~NavigationHistoryEntry() override;

private:
    NavigationHistoryEntry(JS::Realm&, GC::Ref<SessionHistoryEntry>);

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(JS::Cell::Visitor&) override;

    GC::Ref<SessionHistoryEntry> m_session_history_entry;
};

}
