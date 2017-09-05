#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include "GL_include.h"
#include "Countable.h"
#include "GLObject.h"
#include "Mesh.h"

namespace Lumos {

    enum class Type{
        COLOR4_BUFFER,
        POINT4_BUFFER,
        POINT3_BUFFER
    };

    class ArrayBuffer: public GLObject, public Countable{
    public:
        static Type type;
        ArrayBuffer( ):GLObject(), Countable(){}
        void setVertexBuffer( const std::vector<Patronus::Mesh> & shapes );
        void setVertexNormalBuffer( const std::vector<Patronus::Mesh> & shapes );
        void setColorBuffer( const std::vector<Patronus::Mesh> & shapes );
        virtual ~ArrayBuffer();

        /**
         * @brief getSizeInByte, get the size of buffer size, measured in bytes
         * @return number of bytes of the buffer
         */
        inline size_t
            getSizeInByte() const { return _numOfEntry*_bytesPerEntry; }

        inline size_t
            getNumOfEntry() const { return _numOfEntry; }

        void bind() const;

    protected:

    private:
        size_t _numOfEntry;
        size_t _bytesPerEntry;
    };
}

#endif // ARRAYBUFFER_H
