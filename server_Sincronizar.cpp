#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "Sincronizar.h"

Sincronizar::Sincronizar(std::mutex &m) : m(m) {
    m.lock();
}

Sincronizar::~Sincronizar() {
    m.unlock();
}
