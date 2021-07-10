#include <iostream>

#define BIRD_API extern "C" __declspec(dllexport)
#include "bird.hpp"


BIRD_API pe::plugin* create_object() {
    return reinterpret_cast<pe::plugin*>(new bird::bird_plugin());
}


bird::bird_plugin::bird_plugin() {

}


bird::bird_plugin::~bird_plugin() {

}


void bird::bird_plugin::execute() const {
    std::cout << "bird plugin loaded!\n";
}


void bird::bird_plugin::release() {
    delete this;
}
