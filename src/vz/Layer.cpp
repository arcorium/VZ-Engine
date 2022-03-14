#include "vzpch.h"
#include "Layer.h"

namespace vz
{
	Layer::Layer(const std::string& name)
		: m_name(name), m_id(m_totalLayer++)
	{
	}
	Layer::~Layer()
	= default;

	void Layer::OnAttach()
	{
	}

	void Layer::OnDetach()
	{
	}

	void Layer::OnUpdate(Time& time)
	{
		//VZ_CORE_INFO("Update");
	}

	void Layer::OnEvent(Event& ev)
	{
		//VZ_CORE_INFO("{}", ev.ToString());
	}

	void Layer::OnDraw()
	{
		//VZ_CORE_INFO("Drawing");
	}

	void Layer::ImGuiDraw()
	{
	}

	const std::string& Layer::GetName() const
	{
		return m_name;
	}

	unsigned Layer::GetId() const
	{
		return m_id;
	}
}
