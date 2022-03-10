#pragma once
namespace vz
{

    namespace ctx
    {
        /**
         *
         * \brief Interface graphics context
         */
        class Context
        {
        public:
            /**
             * \brief public virtual destructor child class can be deleted from base class pointer, protected or private can't
             * Context* a = new OpenGLContext();
             * delete a;    // if public can, if protected and private cant. because it will be private or removed in child class
             */
            virtual ~Context() = default;
            /**
             * \brief Create context
             */
            virtual void Init() = 0;

            /**
             * \brief Swapping buffer
             */
            virtual void SwapBuffers() = 0;
        };
    }
}