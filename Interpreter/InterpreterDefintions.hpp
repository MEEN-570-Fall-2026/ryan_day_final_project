#ifndef INTERPRETERDEFINITIONS
#define INTERPRETERDEFINITIONS

#include <map>
#include <string>
#include <primitives3d/Object3d.hpp>

std::map<std::string, Object3d> parseStatementsToObjects3d = {
    {"Cube", Object3d}
};

std::map<std::string, Object3d> parseStatementsToMemberMethods3d = {
    {"Translate", Object3d.translate()}
};

#endif