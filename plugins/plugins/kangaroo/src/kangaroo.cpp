#include <iostream>

#define KANGAROO_API extern "C" __declspec(dllexport)
#include "kangaroo.hpp"


KANGAROO_API pe::plugin* create_object() {
    return reinterpret_cast<pe::plugin*>(new kangaroo::kangaroo_plugin());
}


kangaroo::kangaroo_plugin::kangaroo_plugin() {

}


kangaroo::kangaroo_plugin::~kangaroo_plugin() {

}


void kangaroo::kangaroo_plugin::execute() const {
    std::cout << "kangaroo plugin loaded!\n";
}


void kangaroo::kangaroo_plugin::release() {
    delete this;
}
