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
        virtual ~Countable();

    protected:
        unsigned int *_refCount; // use to keep the reference count for the shader

    private:
        void _retain();
        void _release();
    };

}


#endif // COUNTABLE_H
