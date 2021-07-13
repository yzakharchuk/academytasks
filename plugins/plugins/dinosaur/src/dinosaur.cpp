#include <iostream>

#define DINOSAUR_API extern "C" __declspec(dllexport)
#include "dinosaur.hpp"


DINOSAUR_API pe::plugin* create_object() {
    return new dinosaur::dinosaur_plugin();
}


dinosaur::dinosaur_plugin::dinosaur_plugin() {

}


dinosaur::dinosaur_plugin::~dinosaur_plugin() {

}


void dinosaur::dinosaur_plugin::execute() const {
    std::wcout << "dinosaur plugin loaded!\n";
}


void dinosaur::dinosaur_plugin::release() {
    delete this;
}
