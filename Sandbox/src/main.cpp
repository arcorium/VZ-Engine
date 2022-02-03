#include "vz/vz.h"
#include "vz/Window.h"

class App : public vz::Application
{
public:
	App()
	{
		vz::Window w{};
		w.Init();
	}
	~App() override
	{
		
	}

};

APP(App)
