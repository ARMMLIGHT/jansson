// Copyright (c) 2010 Sean Middleditch <sean@middleditch.us>
// Copyright (c) 2010 Petri Lehtinen <petri@digip.org>
//
// Jansson is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#ifndef IN_JANSSON_HPP
#error "jansson.ipp may only be included from jansson.hpp"
#endif

#include <string.h>

namespace json {
    namespace detail {
        // assignment operator
        template <typename _Base>
        ValueBase<_Base>& ValueBase<_Base>::operator=(const Value& value) {
            _Base::operator=(value);
            return *this;
        }

        // check value type
        template <typename _Base>
        bool ValueBase<_Base>::is_undefined() const {
            return _Base::as_json() == 0;
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_object() const {
            return json_is_object(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_array() const {
            return json_is_array(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_string() const {
            return json_is_string(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_integer() const {
            return json_is_integer(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_real() const {
            return json_is_real(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_number() const {
            return json_is_number(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_true() const {
            return json_is_true(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_false() const {
            return json_is_false(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_boolean() const {
            return json_is_boolean(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::is_null() const {
            return json_is_null(_Base::as_json());
        }

        // get size of array or object
        template <typename _Base>
        unsigned int ValueBase<_Base>::size() const {
            if (is_object())
                return json_object_size(_Base::as_json());
            else
                return json_array_size(_Base::as_json());
        }

        // get value at array index (const version)
        template <typename _Base>
        const Value ValueBase<_Base>::at(unsigned int index) const {
            return Value(json_array_get(_Base::as_json(), index));
        }

        template <typename _Base>
        const Value ValueBase<_Base>::operator[](signed int index) const { return at(index); }
        template <typename _Base>
        const Value ValueBase<_Base>::operator[](unsigned int index) const { return at(index); }
        template <typename _Base>
        const Value ValueBase<_Base>::operator[](signed short index) const { return at(index); }
        template <typename _Base>
        const Value ValueBase<_Base>::operator[](unsigned short index) const { return at(index); }
        template <typename _Base>
        const Value ValueBase<_Base>::operator[](signed long index) const { return at(index); }
        template <typename _Base>
        const Value ValueBase<_Base>::operator[](unsigned long index) const { return at(index); }

        // get value at array index (non-const version)
        template <typename _Base>
        ValueBase<ElementProxy> ValueBase<_Base>::at(unsigned int index) {
            return ElementProxy(_Base::as_json(), index);
        }

        template <typename _Base>
        ValueBase<ElementProxy> ValueBase<_Base>::operator[](signed int index) {
            return at(index);
        }

        template <typename _Base>
        ValueBase<ElementProxy> ValueBase<_Base>::operator[](unsigned int index) {
            return at(index);
        }

        template <typename _Base>
        ValueBase<ElementProxy> ValueBase<_Base>::operator[](signed short index) {
            return at(index);
        }

        template <typename _Base>
        ValueBase<ElementProxy> ValueBase<_Base>::operator[](unsigned short index) {
            return at(index);
        }

        template <typename _Base>
        ValueBase<ElementProxy> ValueBase<_Base>::operator[](signed long index) {
            return at(index);
        }

        template <typename _Base>
        ValueBase<ElementProxy> ValueBase<_Base>::operator[](unsigned long index) {
            return at(index);
        }

        // get object property (const version)
        template <typename _Base>
        const Value ValueBase<_Base>::get(const char* key) const {
            return Value(json_object_get(_Base::as_json(), key));
        }

        template <typename _Base>
        const Value ValueBase<_Base>::get(const std::string& key) const {
            return get(key.c_str());
        }

        template <typename _Base>
        const Value ValueBase<_Base>::operator[](const char* key) const {
            return get(key);
        }

        template <typename _Base>
        const Value ValueBase<_Base>::operator[](const std::string& key) const {
            return get(key.c_str());
        }

        // get object property (non-const version)
        template <typename _Base>
        ValueBase<PropertyProxy> ValueBase<_Base>::get(const char* key) {
            return PropertyProxy(_Base::as_json(), key);
        }

        template <typename _Base>
        ValueBase<PropertyProxy> ValueBase<_Base>::get(const std::string& key) {
            return get(key.c_str());
        }

        template <typename _Base>
        ValueBase<PropertyProxy> ValueBase<_Base>::operator[](const char* key) {
            return get(key);
        }

        template <typename _Base>
        ValueBase<PropertyProxy> ValueBase<_Base>::operator[](const std::string& key) {
            return get(key.c_str());
        }

        // clear all array/object values
        template <typename _Base>
        void ValueBase<_Base>::clear() {
            if (is_object())
                json_object_clear(_Base::as_json());
            else
                json_array_clear(_Base::as_json());
        }

        // get value cast to specified type
        template <typename _Base>
        const char* ValueBase<_Base>::as_cstring() const {
            return json_string_value(_Base::as_json());
        }

        template <typename _Base>
        std::string ValueBase<_Base>::as_string() const {
            const char* tmp = as_cstring();
            return tmp == 0 ? "" : tmp;
        }

        template <typename _Base>
        int ValueBase<_Base>::as_integer() const {
            return json_integer_value(_Base::as_json());
        }

        template <typename _Base>
        double ValueBase<_Base>::as_real() const {
            return json_real_value(_Base::as_json());
        }

        template <typename _Base>
        double ValueBase<_Base>::as_number() const {
            return json_number_value(_Base::as_json());
        }

        template <typename _Base>
        bool ValueBase<_Base>::as_boolean() const {
            return is_true();
        }

        // set an object property (converts value to object is not one already)
        template <typename _Base>
        _Base& ValueBase<_Base>::set_key(const char* key, const Value& value) {
            json_object_set(_Base::as_json(), key, value._Base::as_json());
            return *this;
        }

        template <typename _Base>
        _Base& ValueBase<_Base>::set_key(const std::string& key, const Value& value) {
            return set_key(key.c_str(), value);
        }

        // set an array index (converts value to object is not one already)
        template <typename _Base>
        _Base& ValueBase<_Base>::set_at(unsigned int index, const Value& value) {
            if (index == size())
                json_array_append(_Base::as_json(), value._Base::as_json());
            else
                json_array_set(_Base::as_json(), index, value._Base::as_json());
            return *this;
        }

        // delete an object key
        template <typename _Base>
        _Base& ValueBase<_Base>::del_key(const char* key) {
            json_object_del(_Base::as_json(), key);
            return *this;
        }

        template <typename _Base>
        _Base& ValueBase<_Base>::del_key(const std::string& key) {
            return del_key(key.c_str());
        }

        // delete an item from an array by index
        template <typename _Base>
        _Base& ValueBase<_Base>::del_at(unsigned int index) {
            json_array_remove(_Base::as_json(), index);
            return *this;
        }

        // insert an item into an array at a given index
        template <typename _Base>
        _Base& ValueBase<_Base>::insert_at(unsigned int index, const Value& value) {
            json_array_insert(_Base::as_json(), index, value._Base::as_json());
            return *this;
        }

        // write the value to a file
        template <typename _Base>
        int ValueBase<_Base>::dump_file(const char* path, int flags) const {
            return json_dump_file(_Base::as_json(), path, flags);
        }

        template <typename _Base>
        int ValueBase<_Base>::dump_file(const std::string& path, int flags) const {
            return dump_file(path.c_str(), flags);
        }

        // write the value to a string (caller must deallocate with free()!)
        template <typename _Base>
        char* ValueBase<_Base>::dumps(int flags) const {
            return json_dumps(_Base::as_json(), flags);
        }

        Basic::~Basic() {
            json_decref(_value);
        }

        // copy an existing Value
        Basic& Basic::operator=(const Basic& e) {
            if (&e != this) {
                json_decref(_value);
                _value = json_incref(e._value);
            }
            return *this;
        }

        // get the underlying json_t
        json_t* Basic::as_json() const {
            return _value;
        }

        // take ownership of a json_t (does not increase reference count)
        Basic Basic::take_ownership(json_t* json) {
            Basic v;
            v._value = json;
            return v;
        }

        ElementProxy::ElementProxy(json_t* array, unsigned int index)
            : _array(array), _index(index) {
            json_incref(_array);
        }

        ElementProxy::ElementProxy(const ElementProxy& other) 
            : _array(other._array), _index(other._index) {
            json_incref(_array);
        }

        ElementProxy::~ElementProxy() {
            json_decref(_array);
        }

        // assign value to proxied array element
        ElementProxy& ElementProxy::operator=(const Value& value) {
            json_array_set(_array, _index, value.as_json());
            return *this;
        }

        // get the proxied element
        json_t* ElementProxy::as_json() const {
            return json_array_get(_array, _index);
        }

        PropertyProxy::PropertyProxy(json_t* object, const char* key)
            : _object(object), _key(0) {
            _iter = json_object_iter_at(object, key);
            if(!_iter)
                _key = strdup(key);
            json_incref(_object);
        }

        PropertyProxy::PropertyProxy(const PropertyProxy& other)
            : _object(other._object), _iter(other._iter), _key(0) {
            if(other._key)
                _key = strdup(other._key);
            json_incref(_object);
        }

        PropertyProxy::~PropertyProxy() {
            free(_key);
            json_decref(_object);
        }

        // assign value to proxied object property
        PropertyProxy& PropertyProxy::operator=(const Value& value) {
            if(_iter)
                json_object_iter_set(_object, _iter, value.as_json());
            else
                json_object_set(_object, _key, value.as_json());
            return *this;
        }

        json_t* PropertyProxy::as_json() const {
            if(_iter)
                return json_object_iter_value(_iter);
            else
                return json_object_get(_object, _key);
        }

    } // namespace json::detail

    // construct Value::Value input
    Value::Value(const char* value) {
        _value = json_string(value);
    }

    Value::Value(const std::string& value) {
        _value = json_string(value.c_str());
    }

    Value::Value(bool value) {
        _value = value ? json_true() : json_false();
    }

    Value::Value(signed int value) {
        _value = json_integer(value);
    }

    Value::Value(unsigned int value) {
        _value = json_integer(value);
    }

    Value::Value(signed short value) {
        _value = json_integer(value);
    }

    Value::Value(unsigned short value) {
        _value = json_integer(value);
    }

    Value::Value(signed long value) {
        _value = json_integer(value);
    }

    Value::Value(unsigned long value) {
        _value = json_integer(value);
    }

    Value::Value(float value) {
        _value = json_real(value);
    }

    Value::Value(double value) {
        _value = json_real(value);
    }

    // construct a new iterator for a given object
    Iterator::Iterator(const Value& value) : _object(value), _iter(0) {
        _iter = json_object_iter(_object.as_json());
    }

    // construct a new iterator for a given object
    Iterator::Iterator(const detail::ValueBase<detail::PropertyProxy>& value) :
        _object(value.as_json()), _iter(0) {
        _iter = json_object_iter(_object.as_json());
    }

    // increment iterator
    void Iterator::next() {
        _iter = json_object_iter_next(_object.as_json(), _iter);
    }

    Iterator& Iterator::operator++() { next(); return *this; }

    // test if iterator is still valid
    bool Iterator::valid() const {
        return _iter != 0;
    }

    Iterator::operator bool() const {
        return valid();
    }

    // get key
    const char* Iterator::ckey() const {
        return json_object_iter_key(_iter);
    }

    std::string Iterator::key() const {
        return ckey();
    }

    // get value
    const Value Iterator::value() const {
        return Value(json_object_iter_value(_iter));
    }

    // dereference value
    const Value Iterator::operator*() const {
        return value();
    }

    // create a new empty object
    Value object() {
        return Value::take_ownership(json_object());
    }

    // create a new empty array
    Value array() {
        return Value::take_ownership(json_array());
    }

    // create a new null value
    Value null() {
        return Value::take_ownership(json_null());
    }

    // load a file as a JSON value
    Value load_file(const char* path, json_error_t* error) {
        return Value::take_ownership(json_load_file(path, error));
    }

    Value load_file(const std::string& path, json_error_t* error) {
        return load_file(path.c_str(), error);
    }

    // load a string as a JSON value
    Value loads(const char* string, json_error_t* error) {
        return Value::take_ownership(json_loads(string, error));
    }

    Value loads(const std::string& string, json_error_t* error) {
        return loads(string.c_str(), error);
    }

} // namespace json

// stream JSON value out
std::ostream& operator<<(std::ostream& os, const json::Value& value) {
    // get the temporary serialize string
    char* tmp = value.dumps();
    if (tmp != 0) {
        // stream temp string out and release it
        os << tmp;
        free(tmp);
    }
    return os;
}

// read JSON value
std::istream& operator>>(std::istream& is, json::Value& value) {
    // buffer the remaining bytes into a single string for Jansson
    std::stringstream tmp;
    while (is)
        tmp << static_cast<char>(is.get());
    // parse the buffered string
    value = json::loads(tmp.str().c_str());
    return is;
}
