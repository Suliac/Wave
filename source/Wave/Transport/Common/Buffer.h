#pragma once
#include <cstdint>

namespace Wave
{
    /**
     * \class Buffer
     * \brief Represents a basic byte's buffer
     */
    class Buffer
    {
    public:
        Buffer() = delete;
        Buffer(size_t bufferSize);
        Buffer(const Buffer& cpy);

        /**
         * \brief Insert data (as copy) at current index, and increase the index
         *
         * \param dataToInsert the data we want to add to our buffer, should be an array of uint8_t
         * \param dataSize the size of the data we want to take from dataToInsert
         * \return true if we successfully inserted the data
         */
        bool Insert(const uint8_t* dataToInsert, size_t dataSize);

        bool Insert(const Buffer& bufferToInsert);

        /**
         * \brief Select data from an extern buffer and copy its data
         *
         * \param bufferCpy The buffer where the data will be copied
         * \return true if we successfully copied the data
         */
        bool CopyFrom(const Buffer& bufferToCpy);

        void Reset();

        /**
         * \brief Get our current buffer of data
         * \return All the data our buffer contains
         */
        const uint8_t* Get() const;

        /**
         * \brief Get our current buffer of data
         * \return All the data our buffer contains
         */
        uint8_t* GetPtr();

        /**
         * \brief Get the current size of our buffer
         */
        inline size_t Size() const { return m_size; }
        
        /**
         * \brief Get the current index for our buffer, each Insert is increasing the index
         *
         * \return our current index value
         * \sa Insert(...)
         */
        inline size_t GetIndex() const { return m_index; }
        
        /**
         * \brief Set the index of our buffer, should be less than the size
         *
         * \param value our new index
         * \return true if we successfully set the index
         */
        bool SetIndex(size_t value);
    private:
        uint8_t* m_data;
        size_t m_size;
        size_t m_index;
    };
}