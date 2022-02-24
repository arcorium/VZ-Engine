#pragma once
#include "Core.h"
#include "layer.h"

namespace vz
{
	/**
	 * \brief Using double stack layout with first half is for layer and the second or last half for overlay layer
	 */
	typedef std::vector<Layer*> LayerList;

	class VZ_API LayerManager
	{
	public:
		LayerManager();
		~LayerManager();

		//Layer& Pop();
		//void Push(Layer*& layer);

		void Push(Layer* layer);

		/**
		 * \brief Erase or Delete the layer from list, but its not deleted yet from memory.
		 * The lifetime is same as the LayerManager attached to.
		 * \param layer Layer pointer
		 */
		void Pop(Layer* layer);
		/**
		 * \brief Erase or Delete the layer from list, but its not deleted yet from memory.
		 * The lifetime is same as the LayerManager attached to.
		 * \param layer Layer pointer
		 */
		void PopOverlay(Layer* layer);
		void PushOverlay(Layer* layer);


		Layer& GetLayer(unsigned id) const;
		Layer& GetLayer(const std::string& name) const;
		const std::vector<Layer*>& GetLayers() const;

		// Iterator wrapper
		LayerList::iterator begin() { return m_layers.begin(); }
		LayerList::iterator end() { return m_layers.end(); }

	private:
		LayerList m_layers;
		LayerList::iterator m_position;

		LayerList m_deletedLayers;		// Used to deallocate or freeing the memory or the memory will leaks

	};
}