#pragma once

#include <memory>

namespace ostd {

template<typename T,
         typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
// member types
    using pointer      = T*;
    using element_type = T;
    using deleter_type = Deleter;


// member functions
    constexpr unique_ptr() noexcept 
        : _resource(nullptr) {
    }

    constexpr unique_ptr(std::nullptr_t) noexcept
        : unique_ptr() {
    }

    explicit unique_ptr(pointer ptr) noexcept 
        : _resource(ptr) {
    }

    unique_ptr(pointer ptr, deleter_type d) noexcept 
        : _resource(ptr), _deleter(d) {
    }

    unique_ptr(unique_ptr&& other) noexcept 
        : unique_ptr(other.release()) {
    }

    template<typename U, typename E >
    unique_ptr(unique_ptr<U, E>&& other) noexcept
        : unique_ptr(other.release()) {
    }

    ~unique_ptr() {
        _deleter(_resource);
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if(this != &other) {
            _resource = other.release();
        }
        return *this;
    }

    unique_ptr& operator=( std::nullptr_t ) noexcept {
        _resource = pointer();
        return *this;
    }


// modifiers
    pointer release() noexcept {
        auto tmp = _resource;
        _resource = pointer();
        return tmp;
    }

    void reset(pointer ptr = pointer()) noexcept {
        auto old_ptr = _resource;
        _resource = ptr;
        if(old_ptr) {
            _deleter(old_ptr);
        };
    }

    void swap(unique_ptr& other) noexcept {
        std::swap(_resource, other._resource);
    }


// observers
    pointer get() const noexcept {
        return _resource;
    }

    Deleter& get_deleter() noexcept {
        return _deleter;
    }

    const Deleter& get_deleter() const noexcept {
        return _deleter;
    }

    explicit operator bool() const noexcept {
        return get() != nullptr;
    }


    pointer operator->() const noexcept {
        return _resource;
    }

    typename std::add_lvalue_reference<T>::type operator*() const {
        return *_resource;
    }


private:
    pointer _resource;
    deleter_type _deleter;
};


template<typename ... Ts>
auto make_unique(Ts ... args) {
    return unique_ptr(new Ts(std::forward<Ts>(args)...));
}



template<class T1, class D1, class T2, class D2>
bool operator==(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y) {
    
}



} // namespace ostd
