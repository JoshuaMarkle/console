#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Object.h"
#include <string>

class OBJLoader {
public:
    static Object Load(const std::string& filename);
};

#endif // OBJLOADER_H
