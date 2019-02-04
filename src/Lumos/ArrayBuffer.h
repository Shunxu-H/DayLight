/*
The MIT License (MIT)

Copyright (c) 2016-2018, Shunxu Huang, shunxuhuang@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#pragma once 

#include <Common/GL_include.h>
#include <Lumos/GLObject.h>
#include <Patronus/Mesh.h>


namespace Daylight{
    namespace Lumos {

        enum class Type{
            COLOR4_BUFFER,
            POINT4_BUFFER,
            POINT3_BUFFER
        };

        class ArrayBuffer: public GLObject{
        public:
            static Type type;
            ArrayBuffer( );
            ArrayBuffer( const ArrayBuffer & rhs);
            ArrayBuffer& operator = ( const ArrayBuffer & other );

            /**
             * [setVertexBuffer move vertex data from CPU to GPU]
             * @param shapes [list of meshes that will be loaded]
             */
            void setVertexBuffer( const std::vector<Daylight::Patronus::Mesh> & shapes );
            void setVertexNormalBuffer( const std::vector<Daylight::Patronus::Mesh> & shapes );
            void setColorBuffer( const std::vector<Daylight::Patronus::Mesh> & shapes );
            virtual ~ArrayBuffer();

            /**
             * @brief getSizeInByte, get the size of buffer size, measured in bytes
             * @return number of bytes of the buffer
             */
            inline size_t
                getSizeInByte() const { return _numOfEntry*_bytesPerEntry; }

            inline size_t
                getNumOfEntry() const { return _numOfEntry; }


            void use(void * data=nullptr) const override;
            bool isInUse() const override;
            void stopUsing(void * data=nullptr) const override;

        protected:

        private:
            size_t _numOfEntry;
            size_t _bytesPerEntry;


        };
    }
}

