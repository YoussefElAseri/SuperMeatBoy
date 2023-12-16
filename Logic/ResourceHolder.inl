
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
                                                const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }
    std::pair<Identifier, std::unique_ptr<Resource>> pair = std::make_pair(id, std::move(resource));

    auto inserted = mResourceMap.insert(std::move(pair));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) {
    auto found = mResourceMap.find(id);
    return *found->second;
}

template<typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second;
}