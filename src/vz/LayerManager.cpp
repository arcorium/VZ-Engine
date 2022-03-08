#include <vzpch.h>
#include "LayerManager.h"

namespace vz
{
	LayerManager::LayerManager()
		: m_position(0)
	{
	}

	LayerManager::~LayerManager()
	{
		// Delete all heap allocated layers
		for (Layer*& layer : m_layers)
		{
			VZ_DELETE(layer);
		}

		// Delete all 'deleted layers'
		for (Layer*& layer : m_deletedLayers)
		{
			VZ_DELETE(layer);
		}
	}

	void LayerManager::Push(Layer* layer)
	{
		// Pushing from front
		m_layers.emplace(m_layers.begin() + m_position, layer);
		++m_position;
		layer->OnAttach();
	}

	void LayerManager::Pop(Layer* layer)
	{
		const auto it = std::ranges::find(m_layers, layer);
		if (it != m_layers.end())
		{
			(*it)->OnDetach();
			m_deletedLayers.emplace_back(*it);
			// return iterator next of erased data [ 0, 1, 2, *3, 4] -> will return iterator to 4 (* means delete)
			m_layers.erase(it);
			--m_position;
		}
	}

	void LayerManager::PushOverlay(Layer* layer)
	{
		// Pushing to back or last position
		m_layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerManager::PopOverlay(Layer* layer)
	{
		const auto it = std::ranges::find(m_layers, layer);
		if (it != m_layers.end())
		{
			(*it)->OnDetach();
			m_deletedLayers.emplace_back(*it);
			m_layers.erase(it);
		}
	}

	Layer& LayerManager::GetLayer(unsigned id) const
	{
		for(auto it = m_layers.begin(); it != m_layers.end(); ++it)
		{
			if((*it)->GetId() == id)
			{
				return **it;
			}
		}

		VZ_CORE_CRITICAL("Layer with id ({}) is not exist", id);
		exit(-1);
	}

	Layer& LayerManager::GetLayer(const std::string& name) const
	{
		for (auto it = m_layers.begin(); it != m_layers.end(); ++it)
		{
			if ((*it)->GetName() == name)
			{
				return **it;
			}
		}

		VZ_CORE_CRITICAL("Layer with name ({}) is not exist", name);
		exit(-1);
	}

	const std::vector<Layer*>& LayerManager::GetLayers() const
	{
		return m_layers;
	}
}
