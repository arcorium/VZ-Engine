#include <vzpch.h>
#include "LayerManager.h"

namespace vz
{
	LayerManager::LayerManager()
	{
		m_position = m_layers.begin();
	}

	LayerManager::~LayerManager()
	{
		// Delete all heap allocated layers
		for (Layer*& layer : m_layers)
		{
			VZ_SAFE_DELETE(layer);
		}

		// Delete all 'deleted layers'
		for (Layer*& layer : m_deletedLayers)
		{
			VZ_SAFE_DELETE(layer);
		}
	}

	void LayerManager::Push(Layer* layer)
	{
		// Pushing from front
		m_position = m_layers.emplace(m_layers.begin(), layer);
		layer->OnAttach();
	}

	void LayerManager::Pop(Layer* layer)
	{
		const auto it = std::ranges::find(m_layers, layer);
		if (it != m_layers.end())
		{
			(*it)->OnDetach();
			m_deletedLayers.emplace_back(*it);
			m_position = m_layers.erase(it);
			//--m_position;
			m_position = m_layers.begin();
		}
	}

	void LayerManager::PushOverlay(Layer* layer)
	{
		// Pushing to back or last position
		m_layers.emplace_back(layer);
		m_position = m_layers.begin();
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

	//Layer& LayerManager::Pop()
	//{
	//	return *m_layers.at(m_layers.size() - 1);

	//}

	//void LayerManager::Push(Layer*& layer)
	//{
	//	m_layers.emplace_back(layer);

	//}

	//Layer& LayerManager::Create(const std::string& name)
	//{
	//	Layer* temp = new Layer{ name };

	//	Push(temp);
	//}

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
