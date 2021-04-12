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

    bool Buffer::Copy(uint8_t* data, size_t dataSize) const
    {
        if (m_index + dataSize <= m_size)
        {
            memcpy(data, m_data + m_index, dataSize);
            return true;
        }
        return false;
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
