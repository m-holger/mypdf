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

#ifndef QPDFOBJECTHANDLE_TYPED_HH
#define QPDFOBJECTHANDLE_TYPED_HH

#include <bitset>

class QPDFObjectHandle::Typed
{
  public:
    QPDF_DLL
    inline operator QPDFObjectHandle() const;

    QPDF_DLL
    inline operator bool() noexcept;

    QPDF_DLL
    inline operator bool() const noexcept;

    QPDF_DLL
    inline bool null() const noexcept;

    QPDF_DLL
    inline QPDFObjGen getObjGen() const;

    // ... and all the other methods applicable to all object types.

  protected:
    using Flags = std::bitset<3>;
    enum flags { fl_valid, fl_null, fl_no_type_check };

    Typed() = default;
    inline Typed(QPDFObjectHandle const& oh, Flags flags);
    inline Typed(QPDFObjectHandle&& oh, Flags flags);
    Typed(Typed const&) = default;
    Typed(Typed&&) = default;
    Typed& operator=(Typed const&) = default;
    Typed& operator=(Typed&&) = default;
    ~Typed() = default;

    QPDFObjectHandle oh;
    Flags flags{};
};

class QPDFObjectHandle::Integer: public QPDFObjectHandle::Typed
{
    friend class QPDFObjectHandle;

  public:
    QPDF_DLL
    operator long long();

    QPDF_DLL
    operator int();

    QPDF_DLL
    operator unsigned long long();

    QPDF_DLL
    operator unsigned int();

    QPDF_DLL
    inline long long value();

    template <typename T>
    bool
    assign_to(T& var)
    {
        if (flags.test(0)) {
            var = *this;
            return true;
        }
        return false;
    }

  private:
    Integer() = default;
    inline Integer(QPDFObjectHandle const& oh, Flags flags);
};

#endif // QPDFOBJECTHANDLE_TYPED_HH
