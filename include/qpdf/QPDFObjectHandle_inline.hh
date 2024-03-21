// Copyright (c) 2005-2024 Jay Berkenbilt
//
// This file is part of qpdf.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Versions of qpdf prior to version 7 were released under the terms
// of version 2.0 of the Artistic License. At your option, you may
// continue to consider qpdf to be licensed under those terms. Please
// see the manual for additional information.

#ifndef QPDFOBJECTHANDLE_INLINE_HH
#define QPDFOBJECTHANDLE_INLINE_HH

class QPDFObjectHandle::QPDFDictItems
{
    // This class allows C++-style iteration, including range-for iteration, around dictionaries.
    // You can write

    // for (auto iter: QPDFDictItems(dictionary_obj))
    // {
    //     // iter.first is a string
    //     // iter.second is a QPDFObjectHandle
    // }

    // See examples/pdf-name-number-tree.cc for a demonstration of using this API.

  public:
    QPDF_DLL
    QPDFDictItems(QPDFObjectHandle const& oh);

    class iterator
    {
        friend class QPDFDictItems;

      public:
        typedef std::pair<std::string, QPDFObjectHandle> T;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = long;
        using pointer = T*;
        using reference = T&;

        QPDF_DLL
        virtual ~iterator() = default;
        QPDF_DLL
        iterator& operator++();
        QPDF_DLL
        iterator
        operator++(int)
        {
            iterator t = *this;
            ++(*this);
            return t;
        }
        QPDF_DLL
        iterator& operator--();
        QPDF_DLL
        iterator
        operator--(int)
        {
            iterator t = *this;
            --(*this);
            return t;
        }
        QPDF_DLL
        reference operator*();
        QPDF_DLL
        pointer operator->();
        QPDF_DLL
        bool operator==(iterator const& other) const;
        QPDF_DLL
        bool
        operator!=(iterator const& other) const
        {
            return !operator==(other);
        }

      private:
        iterator(QPDFObjectHandle& oh, bool for_begin);
        void updateIValue();

        class Members
        {
            friend class QPDFDictItems::iterator;

          public:
            QPDF_DLL
            ~Members() = default;

          private:
            Members(QPDFObjectHandle& oh, bool for_begin);
            Members() = delete;
            Members(Members const&) = delete;

            QPDFObjectHandle& oh;
            std::set<std::string> keys;
            std::set<std::string>::iterator iter;
            bool is_end;
        };
        std::shared_ptr<Members> m;
        value_type ivalue;
    };

    QPDF_DLL
    iterator begin();
    QPDF_DLL
    iterator end();

  private:
    QPDFObjectHandle oh;
};

class QPDFObjectHandle::QPDFArrayItems
{
    // This class allows C++-style iteration, including range-for iteration, around arrays. You can
    // write

    // for (auto iter: QPDFArrayItems(array_obj))
    // {
    //     // iter is a QPDFObjectHandle
    // }

    // See examples/pdf-name-number-tree.cc for a demonstration of using this API.

  public:
    QPDF_DLL
    QPDFArrayItems(QPDFObjectHandle const& oh);

    class iterator
    {
        friend class QPDFArrayItems;

      public:
        typedef QPDFObjectHandle T;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = long;
        using pointer = T*;
        using reference = T&;

        QPDF_DLL
        virtual ~iterator() = default;
        QPDF_DLL
        iterator& operator++();
        QPDF_DLL
        iterator
        operator++(int)
        {
            iterator t = *this;
            ++(*this);
            return t;
        }
        QPDF_DLL
        iterator& operator--();
        QPDF_DLL
        iterator
        operator--(int)
        {
            iterator t = *this;
            --(*this);
            return t;
        }
        QPDF_DLL
        reference operator*();
        QPDF_DLL
        pointer operator->();
        QPDF_DLL
        bool operator==(iterator const& other) const;
        QPDF_DLL
        bool
        operator!=(iterator const& other) const
        {
            return !operator==(other);
        }

      private:
        iterator(QPDFObjectHandle& oh, bool for_begin);
        void updateIValue();

        class Members
        {
            friend class QPDFArrayItems::iterator;

          public:
            QPDF_DLL
            ~Members() = default;

          private:
            Members(QPDFObjectHandle& oh, bool for_begin);
            Members() = delete;
            Members(Members const&) = delete;

            QPDFObjectHandle& oh;
            int item_number;
            bool is_end;
        };
        std::shared_ptr<Members> m;
        value_type ivalue;
    };

    QPDF_DLL
    iterator begin();
    QPDF_DLL
    iterator end();

  private:
    QPDFObjectHandle oh;
};

inline int
QPDFObjectHandle::getObjectID() const
{
    return getObjGen().getObj();
}

inline int
QPDFObjectHandle::getGeneration() const
{
    return getObjGen().getGen();
}

inline bool
QPDFObjectHandle::isIndirect() const
{
    return (obj != nullptr) && (getObjectID() != 0);
}

inline bool
QPDFObjectHandle::isInitialized() const
{
    return obj != nullptr;
}

inline QPDFObjectHandle::Typed::Typed(QPDFObjectHandle const& oh, Flags flags) :
    oh(oh),
    flags(flags)
{
}

inline QPDFObjectHandle::Typed::Typed(QPDFObjectHandle&& oh, Flags flags) :
    oh(std::move(oh)),
    flags(flags)
{
}

inline QPDFObjectHandle::Typed::operator QPDFObjectHandle() const
{
    return oh;
}

inline QPDFObjectHandle::Typed::operator bool() noexcept
{
    return flags.test(fl_valid);
}

inline QPDFObjectHandle::Typed::operator bool() const noexcept
{
    return flags.test(fl_valid);
}

inline bool
QPDFObjectHandle::Typed::null() const noexcept
{
    return flags.test(fl_null);
}

inline QPDFObjGen
QPDFObjectHandle::Typed::getObjGen() const
{
    return oh.getObjGen();
}

inline QPDFObjectHandle::Integer::Integer(QPDFObjectHandle const& oh, Flags flags) :
    QPDFObjectHandle::Typed(oh, flags)
{
}

inline long long
QPDFObjectHandle::Integer::value()
{
    return *this;
}

class QPDFObjectHandle::Dictionary::iterator
    : public std::map<std::string, QPDFObjectHandle>::iterator
{
  public:
    value_type const&
    operator*() const noexcept
    {
        return objmap::iterator::operator*();
    }
    objmap::const_pointer
    operator->() const noexcept
    {
        return objmap::iterator::operator->();
    }

  private:
    friend class QPDFObjectHandle::Dictionary;

    iterator(objmap::iterator it) :
        objmap::iterator(it)
    {
    }
};

inline QPDFObjectHandle::Dictionary::iterator
QPDFObjectHandle::Dictionary::begin() const noexcept
{
    return {items.begin()};
}

inline QPDFObjectHandle::Dictionary::iterator
QPDFObjectHandle::Dictionary::end() const noexcept
{
    return {items.end()};
}

inline QPDFObjectHandle::Dictionary::reverse_iterator
QPDFObjectHandle::Dictionary::rbegin() const noexcept
{
    return items.rbegin();
}

inline QPDFObjectHandle::Dictionary::reverse_iterator
QPDFObjectHandle::Dictionary::rend() const noexcept
{
    return items.rend();
}

inline bool
QPDFObjectHandle::Dictionary::contains(std::string const& key, bool exclude_nulls) const
{
    if (!exclude_nulls) {
        return items.count(key);
    }
    auto it = items.find(key);
    return it != items.end() && !it->second.isNull();
}

inline QPDFObjectHandle::Dictionary::iterator
QPDFObjectHandle::Dictionary::erase(iterator pos)
{
    return items.erase(pos);
}

inline size_t
QPDFObjectHandle::Dictionary::erase(std::string const& key)
{
    return items.erase(key);
}

inline size_t
QPDFObjectHandle::Dictionary::size(bool exclude_nulls) const
{
    if (!exclude_nulls) {
        return items.size();
    }
    return static_cast<size_t>(
        std::count_if(items.begin(), items.end(), [](auto& p) { return !p.second.isNull(); }));
}

#endif // QPDFOBJECTHANDLE_INLINE_HH
