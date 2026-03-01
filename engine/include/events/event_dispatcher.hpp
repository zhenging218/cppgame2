#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP
#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "memory/object_handle.hpp"

namespace cppengine {
    template <typename T>
    class EventDispatcher {
    private:
        struct EventListener {
            virtual void dispatch(T const &event) const = 0;
            virtual ~EventListener() = default;

            virtual void *getListener() const = 0;
        };

        template <typename U>
        struct EventListenerImpl : EventListener {
            U *listener;
            void (U::*handler)(T const &);

            EventListenerImpl(U *listener_, void(U::*handler_)(T const &)) : listener(listener_), handler(handler_) {}
            EventListenerImpl(EventListenerImpl const &) = default;
            EventListenerImpl &operator=(EventListenerImpl const &) = default;

            void dispatch(T const &event) const override {
                (listener->*handler)(event);
            }

            void *getListener() const override {
                return listener;
            }
        };

        std::unordered_map<std::uint64_t, std::vector<ObjectHandle<EventListener>>> listeners;
    public:

        EventDispatcher() = default;
        EventDispatcher(EventDispatcher const &) = delete;
        EventDispatcher &operator=(EventDispatcher const &) = delete;

        template <typename U>
        void addEventListener(std::uint64_t id, U *listener, void (U::*handler)(T const &));

        template <typename U>
        void removeEventListener(std::uint64_t id, U *listener, void (U::*handler)(T const &));

        void dispatch(std::uint64_t target, T const &event) const;
        void broadcast(T const &event) const;

        static EventDispatcher &getInstance();
    };

    template<typename T>
    template<typename U>
    void EventDispatcher<T>::addEventListener(std::uint64_t id, U *listener, void (U::*handler)(T const &)) {
        auto &entityListeners = listeners[id];
        auto result = std::ranges::find_if(entityListeners, [listener](auto const &registeredListener) {
            return registeredListener->getListener() == listener;
        });

        if (result == entityListeners.end()) {
            entityListeners.emplace_back(new EventListenerImpl<U>(listener, handler));
        }
    }

    template<typename T>
    template<typename U>
    void EventDispatcher<T>::removeEventListener(std::uint64_t id, U *listener, void (U::*)(T const &)) {
        auto entity = listeners.find(id);
        if (entity != listeners.end()) {
            auto result = std::ranges::find_if(entity->second, [listener](auto const &registeredListener) {
                return registeredListener->getListener() == listener;
            });

            if (result != entity->second.end()) {
                entity->second.erase(result);
            }
        }
    }

    template<typename T>
    void EventDispatcher<T>::dispatch(std::uint64_t target, T const &event) const {
        auto t = listeners.find(target);
        if (t != listeners.end()) {
            std::ranges::for_each(t->second, [&event](auto const &listener) {
                listener->dispatch(event);
            });
        }
    }

    template<typename T>
    void EventDispatcher<T>::broadcast(T const &event) const {
        std::ranges::for_each(listeners, [&event](auto const &entities) {
            std::ranges::for_each(entities.second, [&event](auto const &listener) {
                listener->dispatch(event);
            });
        });
    }

    template<typename T>
    EventDispatcher<T> &EventDispatcher<T>::getInstance() {
        static EventDispatcher instance;
        return instance;
    }
}

#endif