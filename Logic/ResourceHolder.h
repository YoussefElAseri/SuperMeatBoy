#ifndef SUPERMEATBOY_RESOURCEHOLDER_H
#define SUPERMEATBOY_RESOURCEHOLDER_H


#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>


class ResourceHolder {
private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

public:
    void load(Identifier id, const std::string& filename);

    Resource& get(Identifier id);

    const Resource& get(Identifier id) const;

};

#include "ResourceHolder.inl"
#endif //SUPERMEATBOY_RESOURCEHOLDER_H
