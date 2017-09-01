#ifndef COUNTABLE_H
#define COUNTABLE_H

namespace Lumos {

     /**
     * @brief The Countable class, used to keep check of the ref count for an object,
     *        designed such way to call appropriate openGL clean up function when the last reference is deleted
     */
    class Countable{
    public:
        Countable();
        Countable( const Countable & other );
        Countable & operator = (const Countable & other );
        ~Countable();

    protected:

    private:
        unsigned int *_refCount; // use to keep the reference count for the shader
        void _retain();
        void _release();
        virtual void _glCleanUp()=0;
    };

}


#endif // COUNTABLE_H
