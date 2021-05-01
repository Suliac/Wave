#include "Wave/Transport/Common/Buffer.h"
#include <memory.h>

namespace Wave
{
    Buffer::Buffer(size_t bufferSize)
    {
        m_data = new uint8_t[bufferSize];
        m_size = bufferSize;
        m_index = 0;
    }

    Buffer::Buffer(const Buffer& cpy)
    {
        m_data = new uint8_t[cpy.Size()];
        m_size = cpy.Size();
        m_index = 0;
        Insert(cpy);
    }

    bool Buffer::Insert(const uint8_t* dataToInsert, size_t dataSize)
    {
        if (m_index + dataSize <= m_size)
        {
            memcpy(m_data + m_index, dataToInsert, dataSize);
            m_index += dataSize;
            return true;
        }

        return false;
    }

    bool Buffer::Insert(const Buffer& bufferToInsert)
    {
        return Insert(bufferToInsert.Get(), bufferToInsert.GetIndex());
    }

    bool Buffer::CopyFrom(const Buffer& bufferCpy)
    {
        Reset();
        return Insert(bufferCpy);
    }

    void Buffer::Reset()
    {
        m_index = 0;
    }

    const uint8_t* Buffer::Get() const
    {
        return m_data;
    }

    uint8_t* Buffer::GetPtr()
    {
        return m_data;
    }

    bool Buffer::SetIndex(size_t value)
    {
        if (value < m_size)
        {
            m_index = value;
            return true;
        }

        return false;
    }
}
