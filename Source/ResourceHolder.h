#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H
#pragma once
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template<typename Resource, typename ID> class ResourceHolder
{
public:

	bool load(typename ID id, const std::string& filename) {
		// Create and load resource
		std::unique_ptr<typename Resource> resource(new typename Resource());
		if (!resource->loadFromFile(filename)) {
			std::cout << "FAILED TO LAOD - " << filename << std::endl;
			return false;
		}

		// If loading successful, insert resource to map
		std::cout << "Loaded: " << filename << std::endl;
		insertResource(id, std::move(resource));
		return true;
	}
	typename Resource& get(typename ID id) {
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return *found->second;
	}

	const typename Resource& get(typename ID id) const
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return *found->second;
	}

private:
	void insertResource(typename ID id, std::unique_ptr<typename Resource> resource) {
		// Insert and check success
		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}

	std::map<ID, std::unique_ptr<typename Resource>>	mResourceMap;
};

#endif
