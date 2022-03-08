#pragma once
#include "vz/Core.h"
#include "vz/Input.h"

namespace vz
{
    /**
     * \brief Implementation of Input for Windows platform
     */
    class VZ_API WindowsInput : public Input
    {
    public:
        bool IsKeyPressedImpl(int keycode) override;
        bool IsMouseButtonPressedImpl(int button) override;
        std::pair<float, float> GetMousePositionImpl() override;
    };
}