#pragma once
#include "Core.h"
#include "layer.h"

namespace vz
{
	/**
	 * \brief Using double stack layout with first half is for layer and the second or last half for overlay layer
	 */
	typedef std::vector<Layer*> LayerList;

	/**
	 * \brief class for managing layer for attach, detach, and delete
	 */
	class VZ_API LayerManager
	{
	public:
		/**
		 * \brief Constructor
		 */
		LayerManager();
		/**
		 * \brief Destructor
		 */
		~LayerManager();

		/**
		 * \brief Pushing layer into list
		 * \param layer layer child(heap allocated)
		 */
		void Push(Layer* layer);

		/**
		 * \brief Pushing overlay layer into layer list in last position
		 * \param layer layer child(heap allocated)
		 */
		void PushOverlay(Layer* layer);

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

		/**
		 * \brief Get the actual layer (not copy) by the id
		 * \param id layer unique id
		 * \return layer address or nullptr
		 */
		Layer& GetLayer(unsigned id) const;

		/**
		 * \brief Get all actual layer (not copy) by the name
		 * \param name layer name
		 * \return list of layer
		 */
		Layer& GetLayer(const std::string& name) const;

		/**
		 * \brief Get all pushed layers and overlay layers
		 * \return layer list
		 */
		const std::vector<Layer*>& GetLayers() const;

		// Iterator wrapper
		LayerList::iterator begin() { return m_layers.begin(); }
		LayerList::iterator end() { return m_layers.end(); }

	private:
		LayerList m_layers;
		unsigned m_position;

		LayerList m_deletedLayers;		// Used to deallocate or freeing the memory or the memory will leaks

	};
}